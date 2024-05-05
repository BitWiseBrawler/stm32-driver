#include "main.h"

#include "dma.h"
#include "memory_management.h"

struct dma_info  {
    DMA_TypeDef* base;
    DMA_Channel_TypeDef* ch_base;
    DMA_Request_TypeDef* req_base;
};

static uint8_t dma_clock_enable(dma_num_t num)
{
    if(num >= DMA_MAX)  {
        return 0;
    }

    switch(num) {
        case DMA_1 :
            RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
            break;
        case DMA_2 :
            RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
            break;

        default : break;
    }

    return 1;
}

static uint8_t dma_ch_enable(DMA_Channel_TypeDef* dma_ch)
{
    if(dma_ch->CCR & DMA_CCR_EN)    return 0;

    dma_ch->CCR |= DMA_CCR_EN;

    return 1;
}

static uint8_t dma_channel_select(DMA_Request_TypeDef* dma_csel, uint8_t ch, uint8_t request_peripheral)
{
    uint32_t shift = 4 * ch;
    uint32_t value = request_peripheral << shift;
   
    dma_csel->CSELR &= ~(0xf << shift);
    dma_csel->CSELR |= value;

    return 1;
}

static uint8_t dma_usart_configration(dma_config_t* config, DMA_Channel_TypeDef* dma_ch)
{
    uint16_t irq_num[DMA_MAX][DMA_CHANNEL_MAX] = {
        {DMA1_Channel1_IRQn, DMA1_Channel2_IRQn, DMA1_Channel3_IRQn, DMA1_Channel4_IRQn, DMA1_Channel5_IRQn, DMA1_Channel6_IRQn, DMA1_Channel7_IRQn},
        {DMA2_Channel1_IRQn, DMA2_Channel2_IRQn, DMA2_Channel3_IRQn, DMA2_Channel4_IRQn, DMA2_Channel5_IRQn, DMA2_Channel6_IRQn, DMA2_Channel7_IRQn}
    };

    dma_ch->CCR = ( config->mode << DMA_CCR_MEM2MEM_Pos
                    | config->priority << DMA_CCR_PL_Pos
                    | config->msize << DMA_CCR_MSIZE_Pos
                    | config->psize << DMA_CCR_PSIZE_Pos
                    | DMA_CCR_MINC
                    | config->circular << DMA_CCR_CIRC_Pos
                    | config->dir << DMA_CCR_DIR_Pos
                    | DMA_CCR_TEIE
                    | config->half_interrupt << DMA_CCR_HTIE_Pos
                    | DMA_CCR_TCIE
    );

    NVIC_EnableIRQ(irq_num[config->dma_num][config->ch]);

    return 1;
}

dma_info_t* dma_init(dma_config_t* config)
{
    dma_info_t* info = (dma_info_t*)alloc_memory(sizeof(dma_info_t));
    
    uint8_t num;
    uint8_t ch;
    DMA_Channel_TypeDef* ch_base;

#if (USED_MCU == STM32L475VGT6)
    DMA_TypeDef* bases[DMA_MAX] = {DMA1, DMA2};
    DMA_Channel_TypeDef* dma1_ch_bases[DMA_CHANNEL_MAX] = {DMA1_Channel1, DMA1_Channel2, DMA1_Channel3, DMA1_Channel4, DMA1_Channel5, DMA1_Channel6, DMA1_Channel7};
    DMA_Channel_TypeDef* dma2_ch_bases[DMA_CHANNEL_MAX] = {DMA2_Channel1, DMA2_Channel2, DMA2_Channel3, DMA2_Channel4, DMA2_Channel5, DMA2_Channel6, DMA2_Channel7};
    DMA_Request_TypeDef* req_bases[DMA_MAX] = {DMA1_CSELR, DMA2_CSELR};
#else

#endif
    num = (uint8_t)config->dma_num;
    ch = (uint8_t)config->ch;

    info->base = bases[num];
    switch(num) {
        case DMA_1 : info->ch_base = dma1_ch_bases[ch]; break;
        case DMA_2 : info->ch_base = dma2_ch_bases[ch]; break;
        default : break;
    }
    info->req_base = req_bases[num];

    ch_base = info->ch_base;

    if(!dma_clock_enable(num)) return 0;

    dma_channel_select(info->req_base, ch, config->request_peripheral);

    dma_usart_configration(config, info->ch_base);

    ch_base->CPAR = (uint32_t)config->peripheral_address;
    ch_base->CMAR = (uint32_t)config->memory_address;

    return info;
}

/**
 * uart rx의 경우 
 * DIR 0 로 설정, Memory to peripheral,
 * RDR(Source)에서 데이터를 읽어와 변수(메모리, Destination)에 저장 
 * Memory increment 모드를 활성화 
 * 페리페럴 주소는 고정 
 */

void dma_data_transfer(dma_info_t* dma, uint16_t length)
{
    DMA_Channel_TypeDef* dma_ch = dma->ch_base;
    dma_ch->CNDTR = length;

    dma_ch_enable(dma->ch_base);
}

void DMA1_Channel1_IRQHandler(void)
{

}
void DMA1_Channel2_IRQHandler(void)
{
    
}
void DMA1_Channel3_IRQHandler(void)
{
    
}


void DMA1_Channel4_IRQHandler(void)
{
    if(DMA1_TCIF_INTERRUPT_FLAG_GET(4)) {
        DMA1_TCIF_INTERRUPT_FLAG_CLEAR(4);
    }

    if(DMA1_HTIF_INTERRUPT_FLAG_GET(4)) {
        DMA1_HTIF_INTERRUPT_FLAG_CLEAR(4);
    }

    if(DMA1_TEIF_INTERRUPT_FLAG_GET(4)) {
        DMA1_TEIF_INTERRUPT_FLAG_CLEAR(4);
    }
}
void DMA1_Channel5_IRQHandler(void)
{
    
}
void DMA1_Channel6_IRQHandler(void)
{
    
}
void DMA1_Channel7_IRQHandler(void)
{
    
}
