#include "main.h"
#include "port.h"
#include "rcc.h"

uint8_t rcc_port_clock_enable(port_name_t en)
{
    if(PORT_NUM_MAX <= en)  {
        //printf("out of range : PORT(GPIO) %c\n", en+65);
        return 0;
    }
    RCC->AHB2ENR |= (1 << en);
    return 1;
}

void port_pin_lock(GPIO_TypeDef* base, uint16_t pins)
{
    base->LCKR = GPIO_LCKR_LCKK | (1 << pins);
    base->LCKR = (1 << pins);
    base->LCKR = GPIO_LCKR_LCKK | (1 << pins);    
    (void)base->LCKR;
}

uint8_t port_lock_status_get(GPIO_TypeDef* base, uint16_t pins)
{
    return (base->LCKR & GPIO_LCKR_LCKK) >> GPIO_LCKR_LCKK_Pos;
}

uint8_t port_init(port_config_t* config)
{
    GPIO_TypeDef* bases[PORT_NUM_MAX] =  {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
    GPIO_TypeDef* base = bases[(uint8_t)config->name];
    uint8_t afr_index;
    uint8_t name = (uint8_t)config->name;
    uint16_t shift;

    if(!rcc_port_clock_enable(name)) return 0;
    
    shift = config->pin * 2;
    base->MODER &= ~(3 << shift);
    base->MODER |= (config->mode << shift);

    if(config->mode == ALTERNATIVE) {
        shift = config->pin * 4;
        afr_index = (config->pin > PIN_7) ? 1 : 0;

        base->AFR[afr_index] &= ~(0x0f << shift);
        base->AFR[afr_index] |= (config->alt << shift);
    }
    
    return 1;
}