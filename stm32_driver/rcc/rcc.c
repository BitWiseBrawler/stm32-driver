#include "main.h"
#include "stm32l475xx.h"
#include "common_define.h"
#include "rcc.h"
#include "port.h"
#include "pwr.h"
#include "flash.h"

#define STM32L475VGT_MSI_MAX_CLOCK  48*M_Hz
#define RCC_CR_MISRANGE_CLEAR   (RCC->CR &= ~RCC_CR_MSIRANGE)

typedef enum {
    CLOCK_100_KHZ = 100000,
    CLOCK_200_KHZ = 200000,
    CLOCK_400_KHZ = 400000,
    CLOCK_800_KHZ = 800000,
    CLOCK_1_MHZ = 1000000,
    CLOCK_2_MHZ = 2000000,
    CLOCK_4_MHZ = 4000000,
    CLOCK_8_MHZ = 8000000,
    CLOCK_16_MHZ = 16000000,
    CLOCK_24_MHZ = 24000000,
    CLOCK_32_MHZ = 32000000,
    CLOCK_48_MHZ = 48000000,
}   clock_value_t;

struct mcu_clock_info  {
    uint32_t lse;
    uint32_t hse;
    uint32_t hsi;
    uint32_t msi;
    uint32_t system_clock;
    uint32_t hclk;
    uint32_t apb1_peripheral;
    uint32_t apb1_timer;
    uint32_t apb2_peripheral;
    uint32_t apb2_timer;
};

static mcu_clock_info_t mcu_clock;

static uint32_t find_msi_clock(uint32_t set_clock) 
{
    int msi_clock_table[MSI_CLOCK_NUM] = {CLOCK_100_KHZ, CLOCK_200_KHZ, CLOCK_400_KHZ, CLOCK_800_KHZ, 
                                            CLOCK_1_MHZ, CLOCK_2_MHZ, CLOCK_4_MHZ, CLOCK_8_MHZ, 
                                            CLOCK_16_MHZ, CLOCK_24_MHZ, CLOCK_32_MHZ, CLOCK_48_MHZ};

    uint32_t diff = abs(set_clock - msi_clock_table[0]);
    uint8_t shift;

    for (int i = 1; i < MSI_CLOCK_NUM; ++i) {
        uint32_t current_diff = abs(set_clock - msi_clock_table[i]);
        if (current_diff < diff) {
            diff = current_diff;
            shift = i;
        }
    }
    
    return (shift << RCC_CR_MSIRANGE_Pos);
}

static int8_t rcc_hsi_clock_init(rcc_config_t* config)
{
    RCC->CR |= (1 << RCC_CR_HSION_Pos);

    while(!(RCC->CR & RCC_CR_HSIRDY));

    /**
     * Set and cleared by software to force HSI16 ON even in Stop modes. The HSI16 can only
     * feed USARTs and I2Cs peripherals configured with HSI16 as kernel clock. Keeping the
     * HSI16 ON in Stop mode allows to avoid slowing down the communication speed because of
     * the HSI16 startup time. This bit has no effect on HSION value.
     * 0: No effect on HSI16 oscillator.
     * 1: HSI16 oscillator is forced ON even in Stop mode.
     */
    //RCC->CR |= (1 << RCC_CR_HSIKERON_Pos);
    
    /**
     * Set and cleared by software. When the system wakeup clock is MSI, this bit is used to
     * wakeup the HSI16 is parallel of the system wakeup.
     * 0: HSI16 oscillator is not enabled by hardware when exiting Stop mode with MSI as wakeup
     * clock.
     * 1: HSI16 oscillator is enabled by hardware when exiting Stop mode with MSI as wakeup
     * clock.
     */

    //RCC->CR |= (1 << RCC_CR_HSIASFS_Pos);

    if((RCC->CFGR & RCC_CFGR_SW) != RCC_CFGR_SW_HSI)   {
        RCC->CFGR &= ~RCC_CFGR_SW;
        RCC->CFGR |= (RCC_CFGR_SW_HSI << RCC_CFGR_SW_Pos);
    }

    RCC->CR &= ~RCC_CR_MSION;

    while(RCC->CR & RCC_CR_MSIRDY);

    mcu_clock.system_clock = HSI_CLOCK_VALUE_HZ;

    return 1;
}

static int8_t rcc_msi_clock_init(rcc_config_t* config)
{
    uint32_t sysclk = config->sysclk;
    uint32_t msi_range;

    RCC->CR |= RCC_CR_MSION;

    while(!(RCC->CR & RCC_CR_MSIRDY));

    /**
     * 1 : MSI Range is provided by MSIRANGE[3:0] in the RCC_CR register
     * 0 : MSI Range is provided by MSISRANGE[3:0] in RCC_CSR register
     */
    RCC->CR |= (1 << RCC_CR_MSIRGSEL_Pos);

    if(config->sysclk > STM32L475VGT_MSI_MAX_CLOCK)  {
        sysclk = STM32L475VGT_MSI_MAX_CLOCK;
        msi_range = RCC_CR_MSIRANGE_11;
    }
    else {
         msi_range = find_msi_clock(config->sysclk);
    }

    RCC_CR_MISRANGE_CLEAR;
    RCC->CR |= msi_range;
    
    if((RCC->CFGR & RCC_CFGR_SW) != RCC_CFGR_SW_MSI)   {
        RCC->CFGR &= ~RCC_CFGR_SW;
        RCC->CFGR |= (RCC_CFGR_SW_MSI << RCC_CFGR_SW_Pos);
    }
   
    mcu_clock.system_clock = sysclk;

    return 1;
}

static int8_t rcc_hse_clock_init(rcc_config_t* config)
{
    return 1;
}

static uint8_t rcc_apb_init(apb_name_t apb_num, hclk_div_t div)
{
    uint32_t div_table[APB_DIV_NUM] = {RCC_CFGR_PPRE1_DIV1, RCC_CFGR_PPRE1_DIV2, RCC_CFGR_PPRE1_DIV4, RCC_CFGR_PPRE1_DIV8, RCC_CFGR_PPRE1_DIV16};
    uint16_t div_value[APB_DIV_NUM] = {1, 2, 4, 8, 16};

    switch(apb_num) {
        case APB1 :
            RCC->CFGR &= ~RCC_CFGR_PPRE1;
            RCC->CFGR |= div_table[div];
            mcu_clock.apb1_peripheral = mcu_clock.hclk / div_value[div];
            mcu_clock.apb1_timer = mcu_clock.apb1_peripheral;
            break;

        case APB2 :
            RCC->CFGR &= ~RCC_CFGR_PPRE2;
            RCC->CFGR |= (div_table[div] << (RCC_CFGR_PPRE2_Pos - RCC_CFGR_PPRE1_Pos));
            mcu_clock.apb2_peripheral = mcu_clock.hclk / div_value[div];
            mcu_clock.apb2_timer = mcu_clock.apb2_peripheral;
            break;
        default : break;
    }

    return 1;
}

static uint8_t rcc_hclk_init(hclk_div_t div)
{
    uint32_t div_table[HCLK_DIV_NUM] = {RCC_CFGR_HPRE_DIV1, RCC_CFGR_HPRE_DIV2, RCC_CFGR_HPRE_DIV4, RCC_CFGR_HPRE_DIV8, RCC_CFGR_HPRE_DIV16, RCC_CFGR_HPRE_DIV64, RCC_CFGR_HPRE_DIV128, RCC_CFGR_HPRE_DIV256, RCC_CFGR_HPRE_DIV512};
    uint16_t div_value[HCLK_DIV_NUM] = {1, 2, 4, 8, 16, 64, 128, 256, 512};

    RCC->CFGR &= ~RCC_CFGR_HPRE;
    RCC->CFGR |= div_table[div];

    mcu_clock.hclk = mcu_clock.system_clock / div_value[div];

    return 1;
}

uint8_t rcc_init(rcc_config_t* config)
{
    memset(&mcu_clock, 0, sizeof(mcu_clock_info_t));
    
    flash_latency_for_clock_adjust(config->sysclk);

    /**
     * bit 0 : MSION
     * bit 8 : HSION
     * bit 16 : HSEON
     */

    switch(config->sysclk_source)  {
        case HSI_CLOCK :
            rcc_hsi_clock_init(config);
            break;

        case MSI_CLOCK :
            rcc_msi_clock_init(config);
            break;

        case HSE_CLOCK :
            rcc_hse_clock_init(config);
            break;
        default : break;
    }
  
    rcc_hclk_init(HCLK_DIV_1);
    rcc_apb_init(APB1, APB_DIV_1);
    rcc_apb_init(APB2, APB_DIV_1);

    return 1;
}

uint32_t rcc_apb1_peripheral_clock_get(void)
{
    return mcu_clock.apb1_peripheral;
}

uint32_t rcc_apb2_peripheral_clock_get(void)
{
    return mcu_clock.apb2_peripheral;
}

uint32_t rcc_system_clock_get(void)
{
    return mcu_clock.system_clock;
}

/**
 * @brief 
 * 
 * @details 2024 02 15. MSI, HSI 확인 완료, PLL 설정 확인해야함.
 * @details peripheral 클럭 설정하는 부분 보강 필요함. 사용자가 설정 하도록 
 * @details 48MHz 설정에서 왜 안되는지 확인하기 
 */