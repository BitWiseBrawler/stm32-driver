#include "main.h"

#include "systick.h"
#include "itm.h"

static uint32_t systick_msec_freerun;

uint32_t systick_freerun_get(void)
{
    return systick_msec_freerun;
}

void systick_freerun_set(uint32_t value)
{
    systick_msec_freerun = value;
}

void SysTick_Handler(void) 
{
    systick_msec_freerun++;
}

void systick_init(uint32_t tick)
{
    SysTick_Config(tick / 1000); // msec
}