#include "main.h"

#include "rcc.h"
#include "systick.h"
#include "port.h"
#include "gpio.h"
#include "itm.h"
#include "memory_management.h"
#include "usart.h"

static gpio_info_t* gpio_led;
static usart_info_t* uart_stlink;

static void init_clock(void)
{
    rcc_config_t rcc_config = {
        .sysclk = 48*M_Hz,
        .sysclk_source = MSI_CLOCK,
        .sysclk_pll_used = PLL_NOT_USED,
    };

    rcc_init(&rcc_config);
}

void usart_tx_callback(usart_info_t* usart)
{
    char* str = "Hello world\r\n";
    //usart_send_string_interrupt(uart_stlink, (uint8_t*)str, strlen(str), 1000);
}

static void init_peripheral(void)
{
    init_clock();

    systick_init(rcc_system_clock_get());

    gpio_config_t gpio_config = {
        .port_config = {
            .name = PORT_NAME_B,
            .pin = PIN_14,
            .mode = GPIO_OUTPUT,
            .lock = PORT_LOCK,
        },
        .output_type = GPIO_OUTPUT_PUSH_FULL,
        .pupd = GPIO_PULL_UP_DOWN_NO,
        .speed = GPIO_SPEED_VERY_HIGH,
        .init_value = GPIO_LOW_SET,
    };
    
    gpio_led = gpio_init(&gpio_config);
    gpio_output_set(gpio_led, GPIO_HIGH_SET); 

    usart_config_t uart_config = {
        .usart_num = USART_NUM_1,
        .mode = USART_MODE_NORMAL,
        .auto_baudrate = USART_AUTO_BAUDRATE_DISABLE,
        .baudrate = 115200,

        .frame_format = {
            .data_bit = DATA_BIT__9,
            .parity = PARITY_NONE,
            .data_order = MSB_FIRST,
            .stop_bit = STOP_BIT_1
        },
        .over_sampling = USART_OVER_8,
        .clock_source = USART_CLOCK_SOURCE_SYSCLK,

        .tx_callback = usart_tx_callback,

        .tx_pin = {
            .name = PORT_NAME_B,
            .pin = PIN_6,
            .mode = ALTERNATIVE,
            .alt = AF7,
            .lock = PORT_LOCK,
        },
        .rx_pin = {
            .name = PORT_NAME_B,
            .pin = PIN_7,
            .mode = ALTERNATIVE,
            .alt = AF7,
            .lock = PORT_LOCK,
        },

        .serial_mode = SERIAL_NOT_USED,
    };

    uart_stlink = usart_init(&uart_config);

    usart_start(uart_stlink);
}

static uint32_t pre_time=0;
void systick_led(void)
{
    if(systick_freerun_get() - pre_time >= SYSTICK_1_MSEC)   {
        gpio_toggle(gpio_led);
        pre_time = systick_freerun_get();
    }
}

int main(void)
{
    ITM_Init();
    init_peripheral();

#if (ITM_PRINTF_LOG_ON == 1)
    printf("B-L475E-IOT01A1(stm32l475) congP Driver\n");
    calculate_memory_usage();
#endif

    usart_send_string_interrupt(uart_stlink, (uint8_t*)"Hello stm32\r\n", 14, 1000);
    
    while(1)    {
        systick_led();
    }
}
