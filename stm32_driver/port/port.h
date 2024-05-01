#ifndef __PORT_H__
#define __PORT_H__

#include "main.h"

typedef enum {
#if (USED_MCU == STM32L475VGT6)
    PORT_NAME_A,
    PORT_NAME_B,
    PORT_NAME_C,
    PORT_NAME_D,
    PORT_NAME_E,
    PORT_NAME_F,
    PORT_NAME_G,
    PORT_NAME_H,
#endif
    PORT_NUM_MAX,
}   port_name_t;

typedef enum {
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15,
}   port_pin_num_t;

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT,
    ALTERNATIVE,
    ANALOG,
}   port_mode_t;

typedef enum {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15,
}   port_alternative_select_t;

typedef enum {
    PORT_UNLOCK,
    PORT_LOCK,
}   port_lock_t;

typedef struct {
    port_name_t name;
    port_pin_num_t pin;
    port_mode_t mode;
    port_alternative_select_t alt;
    port_lock_t lock;
}   port_config_t;

void port_pin_lock(GPIO_TypeDef* base, uint16_t pins);
uint8_t port_init(port_config_t* config);

#endif