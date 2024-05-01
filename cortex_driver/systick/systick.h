#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#define SYSTICK_1_MSEC      1000

uint32_t systick_freerun_get(void);
void systick_freerun_set(uint32_t value);
void systick_init(uint32_t tick);

#endif