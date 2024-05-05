#ifndef __DMA_H__
#define __DMA_H__

#include "main.h"

typedef struct dma_info dma_info_t;

#define ONLY_AVAILABLE_RANGE_1 ((USED_MCU >= STM32L496AEI6) && (USED_MCU <= STM32L4A6ZGT6P))
#define ONLY_AVAILABLE_RANGE_2 ((USED_MCU >= STM32L486JGY6TR) && (USED_MCU <= STM32L4A6ZGT6P))

typedef enum {
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7,
    DMA_CHANNEL_MAX,
} dma_channel_t;

/************************************************************************************/
/*              DMA 1 channel map                                                   */
typedef enum {
    DMA1_CH1__ADC1,
    DMA1_CH1__RESERVED1,
    DMA1_CH1__RESERVED2,
    DMA1_CH1__RESERVED3,
    DMA1_CH1__TIM2_CH3,
    DMA1_CH1__TIM17_CH1__UP,
    DMA1_CH1__TIM4_CH1,
    DMA1_CH1__RESERVED4,
    DMA1_CH1__MAX
}   dma1_channel1_map_t;

typedef enum {
    DMA1_CH2__ADC2,
    DMA1_CH2__SPI1_RX,
    DMA1_CH2__USART3_TX,
    DMA1_CH2__I2C3_TX,
    DMA1_CH2__TIM2_UP,
    DMA1_CH2__TIM3_CH3,
    DMA1_CH2__RESERVED,
    DMA1_CH2__TIM1_CH1,
    DMA1_CH2__MAX,
}   dma1_channel2_map_t;

typedef enum {
    DMA1_CH3__ADC3,
    DMA1_CH3__SPI1_TX,
    DMA1_CH3__USART3_RX,
    DMA1_CH3__I2C3_RX,
    DMA1_CH3__TIM16_CH1__UP,
    DMA1_CH3__TIM3_CH4__TIM3_UP,
    DMA1_CH3__TIM6_UP__DAC_CH1,
    DMA1_CH3__TIM_CH2,
    DMA1_CH3__MAX,
}   dma1_channel3_map_t;

typedef enum {
    DMA1_CH4__DFSDM1_FLT0,
    DMA1_CH4__SPI2_RX,
    DMA1_CH4__USART1_TX,
    DMA1_CH4__I2C2_TX,
    DMA1_CH4__RESERVED,
    DMA1_CH4__TIM7_UP__DAC_CH2,
    DMA1_CH4__TIM3_CH2,
    DMA1_CH4__TIM1_CH4__TRIG__COM,
    DMA1_CH4__MAX,
}   dma1_channel4_map_t;

typedef enum {
    DMA1_CH5__DFSDM1_FLT1,
    DMA1_CH5__SPI2_TX,
    DMA1_CH5__USART1_RX,
    DMA1_CH5__I2C2_RX,
    DMA1_CH5__TIM2_CH1,
    DMA1_CH5__QUADSPI,
    DMA1_CH5__TIM4_CH3,
    DMA1_CH5__TIM15_CH1__UP__TRIG__COM,
    DMA1_CH5__MAX,
}   dma1_channel5_map_t;

typedef enum {
    DMA1_CH6__DFSDM1_FTL2,
    DMA1_CH6__SAI2_A,
    DMA1_CH6__USART2_RX,
    DMA1_CH6__I2C1_TX,
    DMA1_CH6__TIM16_CH1__UP,
    DMA1_CH6__TIM3_CH1__TRIG,
    DMA1_CH6__RESERVED1,
    DMA1_CH6__TIM1_UP,
    DMA1_CH6__MAX,
}   dma1_channel6_map_t;

typedef enum {
    DMA1_CH7__DFSDM1_FLT3,
    DMA1_CH7__SAI2_B,
    DMA1_CH7__USART2_TX,
    DMA1_CH7__I2C1_RX,
    DMA1_CH7__TIM2_CH2__CH4,
    DMA1_CH7__TIM17_CH1__UP,
    DMA1_CH7__TIM4_UP,
    DMA1_CH7__TIM1_CH,
    DMA1_CH7__MAX,
}   dma1_channel7_map_t;
/************************************************************************************/

/************************************************************************************/
/*              DMA 2 channel map                                                   */
typedef enum {
#if ONLY_AVAILABLE_RANGE_1
    DMA2_CH1__I2C4_RX,
#else
    DMA2_CH1__RESERVED1,
#endif
    DMA2_CH1__SAI1_A,
    DMA2_CH1__UART5_TX,
    DMA2_CH1__SPI3_RX,
    DMA2_CH1__SWPMI1_RX,
    DMA2_CH1__TIM5_CH4__TRIG,
#if ONLY_AVAILABLE_RANGE_2
    DMA2_CH1__AES_IN,
#else 
    DMA2_CH1__RESERVED2,
#endif
    DMA2_CH1__TIM8_CH3__UP,
    DMA2_CH1__MAX,
}   dma2_channel1_map_t;

typedef enum {
#if ONLY_AVAILABLE_RANGE_1
    DMA2_CH2__I2C4_TX,
#else 
    DMA2_CH2__RESERVED1,
#endif
    DMA2_CH2__SAI1_B,
    DMA2_CH2__UART5_RX,
    DMA2_CH2__SPI3_TX,
    DMA2_CH2__SWPMI1_TX,
    DMA2_CH2__TIM5_CH3__UP,
#if ONLY_AVAILABLE_RANGE_2
    DMA2_CH2__AES_OUT,
#else
    DMA2_CH2__RESERVED2,
#endif
    DMA2_CH2__TIM8_CH4__TRIG__COM,
    DMA2_CH2__MAX,
}   dma2_channel2_map_t;


typedef enum {
    DMA2_CH3__ADC1,
    DMA2_CH3__SAI2_A,
    DMA2_CH3__UART4_TX,
    DMA2_CH3__RESERVED1,
    DMA2_CH3__SPI1_RX,
    DMA2_CH3__RESERVED2,
#if ONLY_AVAILABLE_RANGE_2
    DMA2_CH3__AES_OUT,
#else
    DMA2_CH2__RESERVED2,
#endif
    DMA2_CH3__RESERVED3,
    DMA2_CH3__MAX,
}   dma2_channel3_map_t;

typedef enum {
    DMA2_CH4__ADC2,
    DMA2_CH4__SAI2_B,
    DMA2_CH4__RESERVED1,
    DMA2_CH4__TIM6_UP__DAC_CH1,
    DMA2_CH4__SPI1_TX,
    DMA2_CH4__TIM5_CH2,
    DMA2_CH4__RESERVED2,
    DMA2_CH4__SDMMC1,
    DMA2_CH4__MAX,
}   dma2_channel4_map_t;

typedef enum {
    DMA2_CH5__ADC3,
    DMA2_CH5__RESERVED1,
    DMA2_CH5__UART4_RX,
    DMA2_CH5__TIM7_UP__DAC_CH2,
#if ONLY_AVAILABLE_RANGE_1
    DMA2_CH5__DCMI,
#else
    DMA2_RESERVED2,
#endif
    DMA2_CH5__TIM5_CH1,
#if ONLY_AVAILABLE_RANGE_2
    DMA2_CH5__AES_IN,
#else
    DMA2_RESERVED3,
#endif
    DMA2_CH5__SDMMC1,
    DMA2_CH5__MAX,
}   dma2_channel5_map_t;

typedef enum {
#if ONLY_AVAILABLE_RANGE_1
    DMA2_CH6__DCMI,
#else
    DMA2_CH6_RESERVED1,
#endif
    DMA2_CH6__SAI1_A,
    DMA2_CH6__USART1_TX,
    DMA2_CH6__RESERVED2,
    DMA2_CH6__LPUART1_TX,
    DMA2_CH6__I2C1_RX,
    DMA2_CH6__RESERVED3,
    DMA2_CH6__TIM8_CH1,
    DMA2_CH6__MAX,
}   dma2_channel6_map_t;

typedef enum {
    DMA2_CH7__RESERVED1,
    DMA2_CH7__SAI1_B,
    DMA2_CH7__USART1_RX,
    DMA2_CH7__QUADSPI,
    DMA2_CH7__LPUART1_RX,
    DMA2_CH7__I2C1_TX,
#if ONLY_AVAILABLE_RANGE_1
    DMA2_CH7__HASH_IN,
#else
    DMA2_CH7_RESERVED2,
#endif
    DMA2_CH7__TIM8_CH2,
    DMA2_CH7__MAX,
}   dma2_channel7_map_t;
/************************************************************************************/

/************************************************************************************/
/*              Define a DMA interrupt flag get and clear macro.                    */
#define DMA1_TCIF_INTERRUPT_FLAG_CLEAR(DMA_CHANNEL) \
    DMA1->IFCR = (DMA_IFCR_CTCIF1 << ((DMA_CHANNEL - 1) * 4));

#define DMA1_HTIF_INTERRUPT_FLAG_CLEAR(DMA_CHANNEL) \
    DMA1->IFCR = (DMA_IFCR_CHTIF1 << ((DMA_CHANNEL - 1) * 4));

#define DMA1_TEIF_INTERRUPT_FLAG_CLEAR(DMA_CHANNEL) \
    DMA1->IFCR = (DMA_IFCR_CTEIF1 << ((DMA_CHANNEL - 1) * 4));

#define DMA1_GIF_INTERRUPT_FLAG_CLEAR(CMA_CHANNEL) \
    DMA1->IFCR = (DMA_IFCR_CGIF1 << ((DMA_CHANNEL - 1) * 4));

#define DMA1_TCIF_INTERRUPT_FLAG_GET(DMA_CHANNEL) \
    ((DMA1->ISR & (DMA_ISR_TCIF1 << ((DMA_CHANNEL - 1) * 4))) ? 1 : 0)
        
#define DMA1_HTIF_INTERRUPT_FLAG_GET(DMA_CHANNEL) \
    (DMA1->ISR & (DMA_ISR_HTIF1 << ((DMA_CHANNEL - 1) * 4)) ? 1 : 0)

#define DMA1_TEIF_INTERRUPT_FLAG_GET(DMA_CHANNEL) \
    (DMA1->ISR & (DMA_ISR_TEIF1 << ((DMA_CHANNEL - 1) * 4)) ? 1 : 0)
    
/************************************************************************************/
typedef enum    {
    DMA_1,
    DMA_2,
    DMA_MAX,
} dma_num_t;

typedef enum    {
    PERI_TO_MEM,
    MEM_TO_PERI,
    MEM_TO_MEM,
    PERI_TO_PERI,
    DMA_DATA_TRANSFER_MODE_MAX,
}   dma_data_transfer_mode_t;

typedef enum    {
    DMA_PRIORITY_LEVEL_LOW,
    DMA_PRIORITY_LEVEL_MEDIUM,
    DMA_PRIORITY_LEVEL_HIGH,
    DMA_PRIORITY_LEVEL_VERY_HIGH,
}   dma_priority_level_t;

typedef enum    {
    MSIZE_8_BIT,
    MSIZE_16_BIT,
    MSIZE_32_BIT,
}   dma_memory_size_t;

typedef enum {
    PSIZE_8_BIT,
    PSIZE_16_BIT,
    PSIZE_32_BIT,
}   dma_peripheral_size_t;

typedef enum {
    CIRCULAR_MODE_OFF,
    CIRCULAR_MODE_ON,
}   dma_circular_mode_t;

typedef enum    {
    DMA_DIR_READ_FROM_PERIPHERAL,
    DMA_DIR_READ_FROM_MEMORY,
}   dma_data_transfer_direction_t;


typedef enum {
    DMA_HALF_INTERRUPT_ENABLE,
    DMA_HALF_INTERRUPT_DISABLE,
}   dma_half_interrupt_t;

typedef struct {

    dma_num_t dma_num;
    dma_channel_t ch;

    dma_data_transfer_mode_t mode;
    dma_priority_level_t priority;
    dma_memory_size_t msize;
    dma_peripheral_size_t psize;
    dma_circular_mode_t circular;
    dma_data_transfer_direction_t dir;
    dma_half_interrupt_t half_interrupt;
    
    uint8_t request_peripheral; /* Refer to the DMA1 and DMA2 Channel map.*/

    uint32_t* peripheral_address;
    uint32_t* memory_address;

}   dma_config_t;

dma_info_t* dma_init(dma_config_t* config);
void dma_data_transfer(dma_info_t* dma, uint16_t length);


#endif