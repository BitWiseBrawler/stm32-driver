#include "main.h"
#include "pwr.h"

void flash_latency_for_clock_adjust(uint32_t sysclk) 
{
    uint8_t v_core_range = pwr_v_core_range_get();
    uint8_t i, latency;
    /**
     * RM0351(STM32L475 Reference manual, page 100)
     */
    const uint32_t range_1_clock[5] = {16000000, 32000000, 48000000, 64000000, 80000000};
    const uint32_t range_2_clock[5] = {6000000, 12000000, 18000000, 26000000, 26000000};

    for(i = 0; i < 5; i++)  {
        switch(v_core_range)    {
            case PWR_V_CORE_RANGE_1 :
                if(sysclk >= range_1_clock[i])  latency = i;
                break;
            case PWR_V_CORE_RANGE_2 :
                if(sysclk >= range_2_clock[i])  latency = i;
                break;
            default : break;
        }
    }

    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= latency;

    while ((FLASH->ACR & FLASH_ACR_LATENCY) != latency);
}