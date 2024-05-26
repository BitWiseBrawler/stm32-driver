#ifndef __TIMER_H__
#define __TIMER_H__

#include "main.h"
#include "port.h"

typedef struct timer_info timer_info_t;

/************************************************************************************/
/*              configuration parameters                                            */

typedef enum {
    TIM_CH_NONE,
    TIM_CH_1,
    TIM_CH_2,
    TIM_CH_3,
    TIM_CH_4,
    TIM_CH_5,
    TIM_CH_6,
    TIM_CH_7,
    TIM_CH_8,
    TIM_CH_15,
    TIM_CH_16,
    TIM_CH_17,    
    TIM_CH_MAX,
}   timer_channel_t;

typedef enum {
    TIMER_COUNT,
    TIMER_PWM,
    TIMER_INPUT_CAPTURE,
    TIMER_OUTPUT_COMPARE,
    TIMER_TRIGGER_EVENT,
    TIMER_ONE_PULSE_MODE_OUTPUT,
}   timer_mode_t;

typedef enum {
    TIM_UP_COUNT,
    TIM_DOWN_COUNT,
}   timer_counter_mode_t;

typedef enum {
    TIM_DIVISION_DISABLE,
    TIM_DIVISION_2,
    TIM_DIVISION_4,
}   timer_inter_clock_division_t;

typedef enum {
    TIM_AUTO_RELOAD_DISABLE,
    TIM_AUTO_RELOAD_ENABLE,
}   timer_counter_auto_reload_t;
/************************************************************************************/
/************************************************************************************/
/*              configuration                                                       */
typedef struct {
    timer_counter_mode_t mode;
    uint32_t prescaler;
    uint32_t period;
    timer_counter_auto_reload_t auto_reload;
    timer_inter_clock_division_t clock_div;
}   timer_counter_config_t;

typedef struct {

}   timer_trigger_output_config_t; 

typedef struct {

}   timer_output_compare_config_t;

typedef struct {

}   timer_input_capture_config_t;

typedef struct {
    timer_channel_t timer_num;
    timer_channel_t ch;
    timer_mode_t mode;
    port_config_t output_pin[2];

    timer_counter_config_t counter_config;
#if 0
    timer_trigger_output_config_t trigger_output_config;
    timer_output_compare_config_t output_compare_config;
    timer_input_capture_config_t input_capture_config;
#endif 
}   timer_config_t;
/************************************************************************************/
#endif