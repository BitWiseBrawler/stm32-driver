#ifndef __COMMON_DEFINE_H__
#define __COMMON_DEFINE_H__


#define ITM_PRINTF_LOG_ON       0

/************************************************************************************/
/*              USART 1 configration                                                */
#define USART1_TX_BUFFER_SIZE       1024
#define USART1_RX_BUFFER_SIZE       1024
/***********************************************************************************/

typedef void* ptr_t;

enum {
    STM32L475VGT6,
};

#define USED_MCU  STM32L475VGT6



#if (USED_MCU == STM32L475VGT6) 
#define USART_FIFO_SUPPORTED        0
#else

#endif



#endif