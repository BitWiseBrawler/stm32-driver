#ifndef __RCC_H__
#define __RCC_H__

#include "main.h"
#include "common_define.h"
#include "port.h"

typedef struct mcu_clock_info mcu_clock_info_t;

#define M_Hz        1000000
#define K_Hz        1000

#if (USED_MCU == STM32L475VGT6)
#define HSI_CLOCK_VALUE_HZ      16*M_Hz

#define HCLK_MAX_CLK           80*M_Hz            
#define APB1_MAX_CLK           80*M_Hz
#define APB2_MAX_CLK           80*M_Hz
#else

#endif
typedef enum {
    HCLK_DIV_1,
    HCLK_DIV_2,
    HCLK_DIV_4,
    HCLK_DIV_8,
    HCLK_DIV_16,
    HCLK_DIV_64,
    HCLK_DIV_128,
    HCLK_DIV_256,
    HCLK_DIV_512,
    HCLK_DIV_NUM,
}   hclk_div_t;

typedef enum    {
    APB1,
    APB2,
}   apb_name_t;

typedef enum {
    APB_DIV_1,
    APB_DIV_2,
    APB_DIV_4,
    APB_DIV_8,
    APB_DIV_16,
    APB_DIV_NUM,
}   apb_div_t;

typedef enum {
    MSI_100_KHZ = 0,
    MSI_200_KHZ,
    MSI_400_KHZ,
    MSI_800_KHZ,
    MSI_1_MHZ,
    MSI_2_MHZ,
    MSI_4_MHZ,
    MSI_8_MHZ,
    MSI_16_MHZ,
    MSI_24_MHZ,
    MSI_32_MHZ,
    MSI_48_MHZ,
    MSI_CLOCK_NUM,
}   msi_clock_range_t;

typedef enum {
    MSI_CLOCK,
    HSI_CLOCK,
    HSE_CLOCK
}   sysclk_select_t;

typedef enum {
    PLL_NOT_USED,
    PLL_USED
}   sysclk_pll_select_t;

typedef struct {
    uint32_t sysclk;
    sysclk_select_t sysclk_source;
    sysclk_pll_select_t sysclk_pll_used;
}   rcc_config_t;

uint8_t rcc_init(rcc_config_t* config);

uint32_t rcc_apb1_peripheral_clock_get(void);
uint32_t rcc_apb2_peripheral_clock_get(void);
uint32_t rcc_system_clock_get(void);

#endif