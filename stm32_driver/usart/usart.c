#include "main.h"

#include "usart.h"
#include "rcc.h"
#include "port.h"
#include "gpio.h"
#include "memory_management.h"

typedef struct {
    uint16_t count;
    uint16_t length;
    uint8_t buffer[USART1_RX_BUFFER_SIZE];
    uint8_t* user_buffer;
    void (*callback)(usart_info_t*);
}   usart_rx_t;

typedef struct  {
    uint16_t count;
    uint16_t length;
    uint8_t buffer[USART1_TX_BUFFER_SIZE];
    void (*callback)(usart_info_t*);
}   usart_tx_t;

struct usart_info  {
    usart_num_t usart_num;
    USART_TypeDef* base;

    usart_tx_t tx_info;
    usart_rx_t rx_info;
};

static struct usart_info* u_ptr[USART_NUM_MAX];

static usart_auto_baudrate_t usart_auto_baudrate_mode_get(USART_TypeDef* usart)
{
    if(usart->CR2 & USART_CR2_ABREN)    {
        return USART_AUTO_BAUDRATE_ENABLE;
    }
    return USART_AUTO_BAUDRATE_DISABLE;
}

static usart_mode_t usart_mode_get(USART_TypeDef* usart)
{
    if(usart->CR3 & USART_CR3_SCEN) {
        return USART_MODE_SMART_CARD;
    }
    else if(usart->CR3 & USART_CR3_IREN)    {
        return USART_MODE_IrDA;
    }
    return USART_MODE_NORMAL;
}

static uint8_t usart_clock_enable(usart_num_t en, usart_clock_source_t source)
{
    uint32_t usart[USART_NUM_MAX] = {
        RCC_APB2ENR_USART1EN,
        RCC_APB1ENR1_USART2EN,
        RCC_APB1ENR1_USART3EN,
        RCC_APB1ENR1_UART4EN,
        RCC_APB1ENR1_UART5EN,
        RCC_APB1ENR1_LPTIM1EN,
    };
    uint16_t shift;

    if(USART_NUM_MAX <= en)  {
        return 0;
    }

    if(en == USART_NUM_1)   {
        RCC->APB2ENR |= usart[en];
    }
    else {
        RCC->APB1ENR1 |= usart[en];
    }

    shift = 2 * en;
    RCC->CCIPR &= ~(3 << shift);
    RCC->CCIPR |= source << shift;

    return 1;
}

static uint8_t usart_baudrate_set(usart_config_t* config, USART_TypeDef* usart)
{
    uint32_t clock;
    uint32_t brr;

    if(config->usart_num == USART_NUM_1)   {
        clock = rcc_apb2_peripheral_clock_get();
    }
    else {
        clock = rcc_apb1_peripheral_clock_get();
    }

    if(config->over_sampling == USART_OVER_8)   {
        brr = (2 * clock) / config->baudrate;
        usart->BRR = (brr & 0xfff0);
        usart->BRR |= ((brr & 0xf) >> 1);
    }
    else {
        usart->BRR = clock / config->baudrate;
    }
    
    return 1;
}

static uint8_t usart_data_bit_set(usart_config_t* config, USART_TypeDef* usart)
{
    uint32_t bit[DATA_BIT__NUM] = {
        USART_CR1_M1, // 7
        0x00, // 8
        USART_CR1_M0 // 9
    };
    usart_data_bit_t index = config->frame_format.data_bit;
    usart_mode_t mode = usart_mode_get(usart);

    if(index == DATA_BIT__7)    { // data bit 7 is not supported
        if(mode == USART_MODE_SMART_CARD || mode == USART_MODE_LIN)  {
            return 0;
        }
        if(usart_auto_baudrate_mode_get(usart) == USART_AUTO_BAUDRATE_ENABLE)   {
            return 0;
        }

    }

    usart->CR1 &= ~(1 << USART_CR1_M0_Pos);
    usart->CR1 &= ~(1 << USART_CR1_M1_Pos);
    usart->CR1 |= bit[index];

    return 1;
}

static uint8_t usart_stop_bit_set(usart_config_t* config, USART_TypeDef* usart)
{
    uint32_t stop_bit = (config->frame_format.stop_bit << USART_CR2_STOP_Pos);
    usart->CR2 &= ~stop_bit;
    usart->CR2 |= stop_bit;
    return 1;
}

static uint8_t usart_over_sampling_mode_set(usart_config_t* config, USART_TypeDef* usart)
{
    usart_mode_t mode = usart_mode_get(usart);

    usart->CR1 &= ~USART_CR1_OVER8;
    if(mode == USART_MODE_IrDA || mode == USART_MODE_LIN)   {
        return 0;
    }

    usart->CR1 |= USART_CR1_OVER8;
    return 1;
}

static uint8_t usart_parity_set(usart_config_t* config, USART_TypeDef* usart)
{
    uint32_t parity = config->frame_format.parity;
    usart->CR1 &= ~USART_CR1_PS;

    if(parity == PARITY_NONE)  {
        usart->CR1 &= ~USART_CR1_PCE;
        return 1;
    }

    usart->CR1 |= USART_CR1_PCE;
    usart->CR1 |= (parity << USART_CR1_PS_Pos);

    return 1;
}

static uint8_t usart_rx_operate_mode_set(usart_config_t* config, USART_TypeDef* usart)
{

}

usart_info_t* usart_init(usart_config_t* config)
{
#if (USED_MCU == STM32L475VGT6)
    USART_TypeDef* bases[USART_NUM_MAX] =  {USART1, USART2, USART3, UART4, UART5, LPUART1};
#endif

    usart_info_t* info = (usart_info_t*)alloc_memory(sizeof(usart_info_t*));

    if(!usart_clock_enable(config->usart_num, USART_CLOCK_SOURCE_PCLK)) return 0;

    info->usart_num = config->usart_num;
    info->base = bases[config->usart_num];

    gpio_speed_set(GPIO_SPEED_VERY_HIGH, config->tx_pin.name, config->tx_pin.pin);
    gpio_speed_set(GPIO_SPEED_VERY_HIGH, config->rx_pin.name, config->rx_pin.pin);

    port_init(&config->tx_pin);
    port_init(&config->rx_pin);

    usart_clock_enable(config->usart_num, config->clock_source);

    // mode set 

    usart_baudrate_set(config, info->base);
    usart_data_bit_set(config, info->base);
    usart_stop_bit_set(config, info->base);
    usart_over_sampling_mode_set(config, info->base);
    usart_parity_set(config, info->base);
    
    memset(&info->tx_info, 0, sizeof(usart_tx_t));
    memset(&info->rx_info, 0, sizeof(usart_rx_t));
    //memset(usart_tx_info[config->usart_num]->buffer, 0, sizeof(uint8_t) * USART_TX_BUFFER_SIZE);

    info->tx_info.callback = config->tx_callback;

    u_ptr[info->usart_num] = info;

    return info;
}

uint8_t usart_stop(usart_info_t* info)
{
    USART_TypeDef* usart = info->base;

    if(usart->CR1 & USART_CR1_UE){
        usart->CR1 &= ~USART_CR1_UE;
        return 1;
    }

    return 0;
}

uint8_t usart_start(usart_info_t* info)
{
    USART_TypeDef* base = info->base;

    base->CR1 |= USART_CR1_UE;

    NVIC_EnableIRQ(USART1_IRQn);

    return 1;
}

void usart_send_string_polling(usart_info_t* usart, uint8_t* str, uint16_t length, uint32_t timeout)
{
    USART_TypeDef* base = usart->base;
    uint16_t i = 0;

    for(i = 0; i < length; i++) {
        base->TDR = str[i];
        while(!(base->ISR & USART_ISR_TC));
        base->ICR |= USART_ICR_TCCF;
    }
}

void usart_send_string_interrupt(usart_info_t* usart, uint8_t* str, uint16_t length, uint32_t timeout)
{
    USART_TypeDef* base = usart->base;
    uint16_t usart_num = (uint16_t)usart->usart_num;
    usart_tx_t* ptr = &usart->tx_info;

    if(!(base->CR1 & USART_CR1_TXEIE))   {
        ptr->count = 0;
        ptr->length = length;
        memcpy(ptr->buffer, str, length);
        
        base->CR1 |= USART_CR1_TE;
        base->CR1 |= USART_CR1_TXEIE;
    }
}

void usart_received_data_get(usart_info_t* usart, uint8_t* buffer)
{
    USART_TypeDef* base = usart->base;
    usart_rx_t* ptr = &usart->rx_info;

    memcpy(buffer, ptr->buffer, ptr->count);

    ptr->count = 0;
    ptr->length = 0;
    memset(ptr->buffer, 0, USART1_RX_BUFFER_SIZE);
}

void usart_received_interrupt(usart_info_t* usart, uint16_t length, uint32_t timeout)
{
    USART_TypeDef* base = usart->base;
    usart_rx_t* ptr = &usart->rx_info;

    if(!(base->CR1 & USART_CR1_RXNEIE)) {
        ptr->count = 0;
        ptr->length = length;
        memset(ptr->buffer, 0, USART1_RX_BUFFER_SIZE);

        base->CR1 |= USART_CR1_RE;
        base->CR1 |= USART_CR1_RXNEIE;
    }
}

static void usart_rx_interrupt_handler(USART_TypeDef* handler, usart_num_t num)
{
    USART_TypeDef* base = handler;
    usart_rx_t* rx_ptr = &u_ptr[num]->rx_info;
    uint8_t* rx_buffer = u_ptr[num]->rx_info.buffer;

    if(base->RDR > 0)    {
        // RDR bit 8 : 0, parity odd
        // RDR bit 8 : 1, parity even
        rx_buffer[rx_ptr->count] = (uint8_t)(base->RDR & 0xff);
        base->RQR |= USART_RQR_RXFRQ;
        if(rx_ptr->count >= rx_ptr->length) {
            base->CR1 &= ~USART_CR1_RE;
            base->CR1 &= ~USART_CR1_RXNEIE;
            memcpy(rx_ptr->user_buffer, rx_buffer, rx_ptr->length);

            rx_ptr->callback(u_ptr[num]);
        }
    }
}

static void usart_tx_interrupt_handler(USART_TypeDef* handler, usart_num_t num)
{
    USART_TypeDef* base = handler;
    usart_tx_t* tx_ptr = &u_ptr[num]->tx_info;
    uint8_t* tx_buffer = u_ptr[num]->tx_info.buffer;

    if(tx_ptr->length != tx_ptr->count)    {
        base->TDR = tx_buffer[tx_ptr->count++];
    }
    else {
        if(!(base->CR1 & USART_CR1_TCIE))    {
            base->CR1 &= ~USART_CR1_TXEIE;
            base->CR1 |= USART_CR1_TCIE;
        }
        else /*if(base->CR1 & USART_CR1_TCIE)*/    {
            if(base->ISR & USART_ISR_TC)  {
                base->CR1 &= ~USART_CR1_TCIE;
                base->CR1 &= ~USART_CR1_TE;
                
                tx_ptr->callback(u_ptr[num]);
            }
        }
    }
}

void USART1_IRQHandler(void) 
{
    if(USART1->CR1 & USART_CR1_RE)   {
        usart_rx_interrupt_handler(USART1, USART_NUM_1);
    }

    if(USART1->CR1 & USART_CR1_TE)  {
        usart_tx_interrupt_handler(USART1, USART_NUM_1);
    }
}
