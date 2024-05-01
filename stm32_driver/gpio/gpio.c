#include "main.h"
#include "gpio.h"
#include "port.h"
#include "memory_management.h"

struct gpio_info  {
    GPIO_TypeDef* base;
    uint16_t pin;
    gpio_set_value_t status;
};

static void gpio_output_init(gpio_config_t* config, GPIO_TypeDef* base)
{
    uint16_t pin = config->port_config.pin;
    int32_t value;

    value = (config->output_type << pin);
    base->OTYPER &= ~(value);
    base->OTYPER |= value;

    value = (config->pupd << (pin * 2));
    base->PUPDR &= ~(value);
    base->PUPDR |= value;

    value = (config->speed << (pin * 2));
    base->OSPEEDR &= ~(value);
    base->OSPEEDR |= value;
}

void gpio_toggle(gpio_info_t* gpio)
{
    GPIO_TypeDef* base = gpio->base;

    base->ODR ^= (1 << gpio->pin);
    gpio->status = base->ODR & (1 << gpio->pin);
}

void gpio_output_set(gpio_info_t* gpio, gpio_set_value_t value)
{
    GPIO_TypeDef* base = gpio->base;
    gpio->status = value;

    if(value == GPIO_HIGH_SET)  {
        base->ODR |= (1 << gpio->pin);
    }
    else {
        base->ODR &= ~(1 << gpio->pin);
    }
}

void gpio_speed_set(gpio_output_speed_t speed, port_name_t port, port_pin_num_t pin)
{
#if (USED_MCU == STM32L475VGT6)    
    GPIO_TypeDef* bases[PORT_NUM_MAX] =  {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
#endif
    uint16_t shift = 2 * pin;

    bases[port]->OSPEEDR &= ~(3 << shift);
    bases[port]->OSPEEDR |= (3 << shift);
}
gpio_info_t* gpio_init(gpio_config_t* config)
{
#if (USED_MCU == STM32L475VGT6)
    GPIO_TypeDef* bases[PORT_NUM_MAX] =  {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
#endif

    gpio_info_t* info = (gpio_info_t*)alloc_memory(sizeof(gpio_info_t));
    port_config_t *port = &config->port_config;

    info->base = bases[(uint8_t)port->name];
    info->pin = port->pin;

    if(port_init(port))     {
        switch(port->mode)  {
            case GPIO_OUTPUT :
                gpio_output_init(config, info->base);
                break;

            case GPIO_INPUT :
            break;

            default : break;
        }
    }

    return info;
}