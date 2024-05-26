#include "stm32l475xx.h"
#include "timer.h"

#include "memory_management.h"

struct timer_info {
    TIM_TypeDef* base;

};

static uint8_t tim_ch_check_feature_support(timer_config_t* config)
{
    switch(config->timer_num)   {
        case TIM_CH_1 :
        case TIM_CH_8 :
            if(config->ch > TIM_CH_6)   {
                return 0;
            }
            break;

        case TIM_CH_2 :
        case TIM_CH_3 :
        case TIM_CH_4 : 
        case TIM_CH_5 :
            if(config->ch > TIM_CH_4)   {
                return 0;
            }
            break;
        
        case TIM_CH_6 :
        case TIM_CH_7 :
            if(config->ch > TIM_CH_NONE)    {
                return 0;
            }
            break;

        case TIM_CH_15 :
            if(config->ch > TIM_CH_2)   {
                return 0;
            }
            break;

        case TIM_CH_16 :
        case TIM_CH_17 :
            if(config->ch > TIM_CH_1)   {
                return 0;
            }
            break;

        default : break;
    }

    return 1;
}

static uint8_t tim_check_feature_support(timer_config_t* config)    
{
    if((config->timer_num == TIM_CH_6 || config->timer_num == TIM_CH_7))  {
        if(config->mode != TIMER_COUNT) {
           return 0;
        }
    }

    return 1;
}


static uint8_t tim_counter_config(timer_config_t* config)
{
    return 1;
}



timer_info_t* timer_init(timer_config_t* config)
{
#if (USED_MCU == STM32L475VGT6)
    TIM_TypeDef* bases[TIM_CH_MAX] =  {TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, TIM8, 
                                    TIM15, TIM16, TIM17};
    TIM_TypeDef* base;
#else 

#endif
    timer_info_t* info = (timer_info_t*)alloc_memory(sizeof(timer_info_t));

    if(config->ch >= TIM_CH_MAX)    return NULL;

    base = bases[config->ch];
    
    if(!tim_check_feature_support(config))  return NULL;

    if(!tim_ch_check_feature_support(config))   return NULL;

    tim_counter_config(config);

    return info;
}