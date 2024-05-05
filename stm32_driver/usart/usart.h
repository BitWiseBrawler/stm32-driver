#ifndef __usart_H__
#define __usart_H__

#include "main.h"
#include "port.h"
#include "dma.h"

typedef struct usart_info usart_info_t;

#define USART_TX_BUFFER_SIZE  1024

typedef enum {
#if (USED_MCU == STM32L475VGT6)
    USART_NUM_1,
    USART_NUM_2,
    USART_NUM_3,
    UART_NUM_4,
    UART_NUM_5,
    LPUART_NUM_1,
#endif
    USART_NUM_MAX,
}   usart_num_t;


typedef enum {
    USART_AUTO_BAUDRATE_DISABLE,
    USART_AUTO_BAUDRATE_ENABLE,
}   usart_auto_baudrate_t;

typedef enum {
    USART_MODE_NORMAL,
    USART_MODE_SMART_CARD,
    USART_MODE_IrDA,
    USART_MODE_LIN,
}   usart_mode_t;

typedef enum {
    PARITY_EVEN,
    PARITY_ODD,
    PARITY_NONE,
}   usart_parity_t;

typedef enum {
    DATA_BIT__7,
    DATA_BIT__8,
    DATA_BIT__9,
    DATA_BIT__NUM,
}   usart_data_bit_t;

typedef enum {
    MSB_FIRST,
    LSB_FIRST,
}   usart_data_order_t;

typedef enum {
    STOP_BIT_1,
    STOP_BIT_0_5,
    STOP_BIT_2,
    STOP_BIT_1_5,
    STOP_BIT_NUM,
}   usart_stop_bit_t;

typedef enum {
    SERIAL_NOT_USED,
    SERIAL_RS_485,
    SERIAL_RS_232,
}   usart_serial_mode_t;

typedef enum {
    USART_OVER_8,
    USART_OVER_16,
}   usart_over_sampling_t;

typedef enum {
    USART_CLOCK_SOURCE_PCLK,
    USART_CLOCK_SOURCE_SYSCLK,
    USART_CLOCK_SOURCE_HSI16,
    USART_CLOCK_SOURCE_LSE,
}   usart_clock_source_t;

typedef struct {
    usart_data_bit_t data_bit;
    usart_parity_t parity;
    usart_data_order_t data_order;
    usart_stop_bit_t stop_bit;
}   usart_data_frame_format_t;

typedef struct {
    usart_num_t usart_num;
    usart_mode_t mode;
    usart_auto_baudrate_t auto_baudrate;
    uint32_t baudrate;

    usart_data_frame_format_t frame_format;
    
    usart_over_sampling_t over_sampling;
    usart_clock_source_t clock_source;
  
    uint16_t tx_interrupt_priority;
    void (*tx_callback)(usart_info_t*);

    uint16_t rx_interrupt_priority;
    void (*rx_callback)(usart_info_t*);

    uint8_t dma_used;

    port_config_t tx_pin;
    port_config_t rx_pin;

    usart_serial_mode_t serial_mode;

}   usart_config_t;

uint8_t usart_tx_enable(usart_info_t* info);
uint8_t usart_start(usart_info_t* info);
uint8_t usart_stop(usart_info_t* info);
uint8_t usart_data_transmit(usart_info_t* info);
usart_info_t* usart_init(usart_config_t* config);
void USART_SendString(const char *str);

void usart_send_string_dma(usart_info_t* usart, uint8_t* str, uint16_t length, uint32_t timeout);
void usart_received_dma(usart_info_t* usart, uint16_t length, uint32_t timeout);

#endif