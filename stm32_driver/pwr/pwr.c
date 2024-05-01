#include "main.h"

#include "pwr.h"

pwr_v_core_range_t pwr_v_core_range_get(void)
{
    return (PWR->CR1 & PWR_CR1_VOS) >> PWR_CR1_VOS_Pos;
}