#include "main.h"

#include "stm32l475xx.h"
#include "rcc.h"
#include "systick.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    ITM_SendChar(ch);
    return ch;
}

uint8_t ITM_Init(void) 
{
    uint32_t time_out;    
    uint32_t last_time;
    
    ITM->LAR = 0xC5ACCE55; // ITM Lock Access Register
    ITM->TCR = 0x0001000D; // ITM Trace Control Register

    time_out = systick_freerun_get();

    while(!(ITM->TCR& ITM_TCR_BUSY_Msk)){
        last_time = systick_freerun_get();
        if(last_time - time_out > 1000) {
            return 0;
        }
    }

    printf("I have completed the TIM initialization. Now you can use SWV with printf.\n");
    
    return 1;
}