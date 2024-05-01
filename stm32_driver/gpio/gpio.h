#ifndef __GPIO_H__
#define __GPIO_H__

#include "main.h"
#include "port.h"

typedef struct gpio_info gpio_info_t;

typedef enum {
    GPIO_LOW_SET,
    GPIO_HIGH_SET,
}   gpio_set_value_t;

typedef enum {
    /*  – Open drain mode: A “0” in the Output register activates the N-MOS whereas a “1”
        in the Output register leaves the port in Hi-Z (the P-MOS is never activated)
        – Push-pull mode: A “0” in the Output register activates the N-MOS whereas a “1” in
        the Output register activates the P-MOS   */
    GPIO_OUTPUT_PUSH_FULL,
    GPIO_OUTPUT_OPER_DRAIN,
}   gpio_output_type_t;

typedef enum {
    GPIO_SPEED_LOW,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH,
    GPIO_SPEED_VERY_HIGH
}   gpio_output_speed_t;

typedef enum {
    GPIO_PULL_UP_DOWN_NO,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN,
}   gpio_push_pull_down_t;

typedef struct {
    port_config_t port_config;

    gpio_output_type_t output_type;
    gpio_push_pull_down_t pupd;
    gpio_output_speed_t speed;
    gpio_set_value_t init_value;
}   gpio_config_t;

void gpio_toggle(gpio_info_t* gpio);
void gpio_output_set(gpio_info_t* gpio, gpio_set_value_t value);
void gpio_speed_set(gpio_output_speed_t speed, port_name_t port, port_pin_num_t pin);
gpio_info_t* gpio_init(gpio_config_t* config);

#endif