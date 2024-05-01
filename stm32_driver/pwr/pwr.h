#ifndef __PWR_H__
#define __PWR_H__

typedef enum {
    PWR_V_CORE_RANGE_1 = 1,
    PWR_V_CORE_RANGE_2 = 2,
} pwr_v_core_range_t;

pwr_v_core_range_t pwr_v_core_range_get(void);

#endif