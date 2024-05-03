#ifndef __MCU_PRODUCT_LIST_H__
#define __MCU_PRODUCT_LIST_H__

typedef enum {
    STM32L412C8T6,
    STM32L412C8U6,
    STM32L412C8U6TR,
    STM32L412CBT3,
    STM32L412CBT3TR,
    STM32L412CBT6,
    STM32L412CBT6P,
    STM32L412CBT6TR,
    STM32L412CBU6,
    STM32L412CBU6P,
    STM32L412CBU6TR,
    STM32L412K8T6,
    STM32L412K8T6TR,
    STM32L412K8U6,
    STM32L412K8U6TR,
    STM32L412KBT3,
    STM32L412KBT3TR,
    STM32L412KBT6,
    STM32L412KBU3,
    STM32L412KBU6,
    STM32L412KBU6TR,
    STM32L412R8I6,
    STM32L412R8T6,
    STM32L412R8T6TR,
    STM32L412RBI6,
    STM32L412RBI6P,
    STM32L412RBT6,
    STM32L412RBT6P,
    STM32L412RBT6TR,
    STM32L412T8Y6TR,
    STM32L412TBY3TR,
    STM32L412TBY6PTR,
    STM32L412TBY6TR,
    STM32L422CBT6,
    STM32L422CBU6,
    STM32L422KBT6,
    STM32L422KBU6,
    STM32L422RBI6,
    STM32L422RBT6,
    STM32L422TBY6TR,
    STM32L431CBT3,
    STM32L431CBT3TR,
    STM32L431CBT6,
    STM32L431CBT6TR,
    STM32L431CBU6,
    STM32L431CBU6TR,
    STM32L431CBY6TR,
    STM32L431CBY7TR,
    STM32L431CCT6,
    STM32L431CCT6TR,
    STM32L431CCU6,
    STM32L431CCU6TR,
    STM32L431CCU7,
    STM32L431CCU7TR,
    STM32L431CCY6TR,
    STM32L431KBU3,
    STM32L431KBU3TR,
    STM32L431KBU6,
    STM32L431KBU6TR,
    STM32L431KCU6,
    STM32L431KCU6TR,
    STM32L431RBI3,
    STM32L431RBI6,
    STM32L431RBI6TR,
    STM32L431RBT6,
    STM32L431RBT6TR,
    STM32L431RBY6TR,
    STM32L431RCI6,
    STM32L431RCI6TR,
    STM32L431RCT6,
    STM32L431RCT6TR,
    STM32L431RCY6TR,
    STM32L431VCI3,
    STM32L431VCI3TR,
    STM32L431VCI6,
    STM32L431VCI7,
    STM32L431VCI7TR,
    STM32L431VCT6,
    STM32L431VCT6TR,
    STM32L432KBU6,
    STM32L432KBU6TR,
    STM32L432KCU3,
    STM32L432KCU3TR,
    STM32L432KCU6,
    STM32L433CBT6,
    STM32L433CBT7,
    STM32L433CBU6,
    STM32L433CBY6TR,
    STM32L433CCT3,
    STM32L433CCT3TR,
    STM32L433CCT6,
    STM32L433CCT6TR,
    STM32L433CCU3,
    STM32L433CCU3TR,
    STM32L433CCU6,
    STM32L433CCU6TR,
    STM32L433CCY3TR,
    STM32L433CCY6TR,
    STM32L433RBI6,
    STM32L433RBT6,
    STM32L433RBY6TR,
    STM32L433RCI3,
    STM32L433RCI6,
    STM32L433RCI6TR,
    STM32L433RCT3,
    STM32L433RCT3TR,
    STM32L433RCT6,
    STM32L433RCT6P,
    STM32L433RCT6TR,
    STM32L433RCY3TR,
    STM32L433RCY6TR,
    STM32L433VCI3,
    STM32L433VCI6,
    STM32L433VCI6TR,
    STM32L433VCT3,
    STM32L433VCT6,
    STM32L433VCT6TR,
    STM32L442KCU6,
    STM32L442KCU6TR,
    STM32L443CCF6TR,
    STM32L443CCT6,
    STM32L443CCT6TR,
    STM32L443CCU6,
    STM32L443CCY6TR,
    STM32L443RCI3,
    STM32L443RCI3TR,
    STM32L443RCI6,
    STM32L443RCI6TR,
    STM32L443RCT6,
    STM32L443RCT6TR,
    STM32L443RCY6TR,
    STM32L443VCI6,
    STM32L443VCT6,
    STM32L443VCT6TR,
    STM32L451CCU3,
    STM32L451CCU3TR,
    STM32L451CCU6,
    STM32L451CCU6TR,
    STM32L451CET6,
    STM32L451CEU6,
    STM32L451CEU6TR,
    STM32L451RCI6,
    STM32L451RCI6TR,
    STM32L451RCT3,
    STM32L451RCT3TR,
    STM32L451RCT6,
    STM32L451REI6,
    STM32L451REI6TR,
    STM32L451RET6,
    STM32L451RET6TR,
    STM32L451REY6TR,
    STM32L451VCI6,
    STM32L451VCT6,
    STM32L451VEI6,
    STM32L451VET6,
    STM32L451VET6TR,
    STM32L452CCU6,
    STM32L452CET6,
    STM32L452CET6P,
    STM32L452CEU3,
    STM32L452CEU6,
    STM32L452RCI6,
    STM32L452RCT6,
    STM32L452RCT6TR,
    STM32L452REI3,
    STM32L452REI6,
    STM32L452RET3,
    STM32L452RET6,
    STM32L452RET6P,
    STM32L452RET6TR,
    STM32L452REY3TR,
    STM32L452REY6PTR,
    STM32L452REY6TR,
    STM32L452VCI6,
    STM32L452VCT6,
    STM32L452VEI3,
    STM32L452VEI3TR,
    STM32L452VEI6,
    STM32L452VEI6TR,
    STM32L452VET3,
    STM32L452VET6,
    STM32L462CET6,
    STM32L462CEU3,
    STM32L462CEU6,
    STM32L462CEU6F,
    STM32L462CEU6TR,
    STM32L462REI6,
    STM32L462RET6,
    STM32L462RET6TR,
    STM32L462REY6TR,
    STM32L462VEI6,
    STM32L462VEI6TR,
    STM32L462VET6,
    STM32L462VET6TR,
    STM32L471QEI3TR,
    STM32L471QEI6,
    STM32L471QEI6TR,
    STM32L471QEI7,
    STM32L471QEI7TR,
    STM32L471QGI6,
    STM32L471QGI6TR,
    STM32L471RET3,
    STM32L471RET3TR,
    STM32L471RET6,
    STM32L471RET6TR,
    STM32L471RGT6,
    STM32L471RGT6TR,
    STM32L471VET6,
    STM32L471VET6TR,
    STM32L471VGT3,
    STM32L471VGT6,
    STM32L471VGT6TR,
    STM32L471ZEJ3,
    STM32L471ZEJ3TR,
    STM32L471ZEJ6,
    STM32L471ZEJ6TR,
    STM32L471ZET6,
    STM32L471ZET6TR,
    STM32L471ZGJ6,
    STM32L471ZGT6,
    STM32L475RCT3,
    STM32L475RCT6,
    STM32L475RCT7,
    STM32L475RCT7TR,
    STM32L475RET6,
    STM32L475RET6TR,
    STM32L475RGT6,
    STM32L475RGT6TR,
    STM32L475RGT7,
    STM32L475RGT7TR,
    STM32L475VCT6,
    STM32L475VET6,
    STM32L475VET6TR,
    STM32L475VGT6,
    STM32L476JEY6TR,
    STM32L476JGY3TR,
    STM32L476JGY6PTR,
    STM32L476JGY6TR,
    STM32L476JGY7TR,
    STM32L476MEY6TR,
    STM32L476MGY3TR,
    STM32L476MGY6MTR,
    STM32L476MGY6TR,
    STM32L476QEI6,
    STM32L476QEI6TR,
    STM32L476QGI3,
    STM32L476QGI3TR,
    STM32L476QGI6,
    STM32L476QGI6P,
    STM32L476QGI6TR,
    STM32L476RCT6,
    STM32L476RCT6TR,
    STM32L476RET6,
    STM32L476RET6TR,
    STM32L476RGT3,
    STM32L476RGT6,
    STM32L476RGT6TR,
    STM32L476VCT6,
    STM32L476VCT6TR,
    STM32L476VET6,
    STM32L476VET6TR,
    STM32L476VGT3,
    STM32L476VGT6,
    STM32L476VGT6TR,
    STM32L476VGT7,
    STM32L476VGT7TR,
    STM32L476VGY6PTR,
    STM32L476ZET6,
    STM32L476ZET6TR,
    STM32L476ZGJ6,
    STM32L476ZGT3,
    STM32L476ZGT6,
    STM32L476ZGT6TR,
    STM32L486JGY6TR,
    STM32L486QGI6,
    STM32L486QGI6TR,
    STM32L486RGT6,
    STM32L486RGT6TR,
    STM32L486RGT7,
    STM32L486RGT7TR,
    STM32L486VGT3,
    STM32L486VGT3TR,
    STM32L486VGT6,
    STM32L486VGT6TR,
    STM32L486ZGT3,
    STM32L486ZGT6,
    STM32L496AEI6,
    STM32L496AGI3,
    STM32L496AGI6,
    STM32L496AGI6P,
    STM32L496QEI6,
    STM32L496QEI6TR,
    STM32L496QGI3,
    STM32L496QGI6,
    STM32L496QGI6P,
    STM32L496QGI6S,
    STM32L496QGI6STR,
    STM32L496RET6,
    STM32L496RET6TR,
    STM32L496RGT3,
    STM32L496RGT3TR,
    STM32L496RGT6,
    STM32L496RGT6P,
    STM32L496RGT6TR,
    STM32L496VET3,
    STM32L496VET6,
    STM32L496VET6TR,
    STM32L496VGT3,
    STM32L496VGT6,
    STM32L496VGT6P,
    STM32L496VGT6TR,
    STM32L496VGY6PTR,
    STM32L496VGY6TR,
    STM32L496WGY6PTR,
    STM32L496ZET6,
    STM32L496ZET6TR,
    STM32L496ZGT3,
    STM32L496ZGT6,
    STM32L496ZGT6P,
    STM32L496ZGT6TR,
    STM32L4A6AGI6,
    STM32L4A6AGI6P,
    STM32L4A6QGI6,
    STM32L4A6QGI6P,
    STM32L4A6RGT6,
    STM32L4A6RGT6P,
    STM32L4A6RGT6TR,
    STM32L4A6RGT7,
    STM32L4A6RGT7TR,
    STM32L4A6VGT6,
    STM32L4A6VGT6P,
    STM32L4A6VGT6PTR,
    STM32L4A6VGT6TR,
    STM32L4A6VGY6PTR,
    STM32L4A6VGY6TR,
    STM32L4A6ZGT6,
    STM32L4A6ZGT6P,
    STM32L4P5AEI6,
    STM32L4P5AGI6,
    STM32L4P5AGI6P,
    STM32L4P5CET6,
    STM32L4P5CEU6,
    STM32L4P5CGT6,
    STM32L4P5CGT6P,
    STM32L4P5CGU6,
    STM32L4P5CGU6P,
    STM32L4P5QEI6,
    STM32L4P5QGI6,
    STM32L4P5QGI6P,
    STM32L4P5QGI6S,
    STM32L4P5QGI6STR,
    STM32L4P5QGI6TR,
    STM32L4P5RET6,
    STM32L4P5RGT6,
    STM32L4P5RGT6P,
    STM32L4P5VET6,
    STM32L4P5VET6TR,
    STM32L4P5VEY6TR,
    STM32L4P5VGT6,
    STM32L4P5VGT6P,
    STM32L4P5VGY6PTR,
    STM32L4P5VGY6TR,
    STM32L4P5ZET6,
    STM32L4P5ZGT6,
    STM32L4P5ZGT6P,
    STM32L4P5ZGT6TR,
    STM32L4Q5AGI6,
    STM32L4Q5AGI6P,
    STM32L4Q5CGT6,
    STM32L4Q5CGT6P,
    STM32L4Q5CGU6,
    STM32L4Q5CGU6P,
    STM32L4Q5QGI6,
    STM32L4Q5QGI6P,
    STM32L4Q5RGT3,
    STM32L4Q5RGT6,
    STM32L4Q5RGT6P,
    STM32L4Q5VGT6,
    STM32L4Q5VGT6P,
    STM32L4Q5VGY6PTR,
    STM32L4Q5VGY6TR,
    STM32L4Q5ZGT6,
    STM32L4Q5ZGT6P,
    STM32L4R5AGI6,
    STM32L4R5AII6,
    STM32L4R5AII6P,
    STM32L4R5QGI6,
    STM32L4R5QGI6S,
    STM32L4R5QGI6STR,
    STM32L4R5QGI6TR,
    STM32L4R5QII6,
    STM32L4R5QII6P,
    STM32L4R5QII6TR,
    STM32L4R5VGT6,
    STM32L4R5VIT6,
    STM32L4R5VIT6TR,
    STM32L4R5ZGT6,
    STM32L4R5ZGT6TR,
    STM32L4R5ZGY6TR,
    STM32L4R5ZIT6,
    STM32L4R5ZIT6P,
    STM32L4R5ZIY6TR,
    STM32L4R7AII6,
    STM32L4R7VIT6,
    STM32L4R7ZIT6,
    STM32L4R9AGI6,
    STM32L4R9AII6,
    STM32L4R9VGT6,
    STM32L4R9VIT6,
    STM32L4R9ZGJ6,
    STM32L4R9ZGT6,
    STM32L4R9ZGY6TR,
    STM32L4R9ZIJ6,
    STM32L4R9ZIT6,
    STM32L4R9ZIY6PTR,
    STM32L4R9ZIY6TR,
    STM32L4S5AII3,
    STM32L4S5AII3TR,
    STM32L4S5AII6,
    STM32L4S5QII6,
    STM32L4S5VIT3,
    STM32L4S5VIT6,
    STM32L4S5VIT6TR,
    STM32L4S5ZIT6,
    STM32L4S5ZIY6TR,
    STM32L4S7AII6,
    STM32L4S7VIT6,
    STM32L4S7ZIT6,
    STM32L4S9AII6,
    STM32L4S9VIT6,
    STM32L4S9ZIJ6,
    STM32L4S9ZIJ6TR,
    STM32L4S9ZIT6,
    STM32L4S9ZIY6TR,
}   stm32_l4_serise_t;

#endif