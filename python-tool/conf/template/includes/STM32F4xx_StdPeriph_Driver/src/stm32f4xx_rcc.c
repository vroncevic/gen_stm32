/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_rcc.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Reset and clock control (RCC) peripheral:
 *     - Internal/external clocks, PLL, CSS and MCO configuration
 *     - System, AHB and APB busses clocks configuration
 *     - Peripheral clocks configuration
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_rcc is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_rcc is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* RCC registers bit address in alias region */
#define RCC_OFFSET (RCC_BASE - PERIPH_BASE)

/* CR Register */
/* Alias word address of HSION bit */
#define CR_OFFSET (RCC_OFFSET + 0x00)
#define HSION_BitNumber 0x00
#define CR_HSION_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of CSSON bit */
#define CSSON_BitNumber 0x13
#define CR_CSSON_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (CSSON_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber 0x18
#define CR_PLLON_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

/* Alias word address of PLLI2SON bit */
#define PLLI2SON_BitNumber 0x1A
#define CR_PLLI2SON_BB ( \
    PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLI2SON_BitNumber * 4) \
)

/* CFGR Register */
/* Alias word address of I2SSRC bit */
#define CFGR_OFFSET (RCC_OFFSET + 0x08)
#define I2SSRC_BitNumber 0x17
#define CFGR_I2SSRC_BB ( \
    PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (I2SSRC_BitNumber * 4) \
)

/* BDCR Register */
/* Alias word address of RTCEN bit */
#define BDCR_OFFSET (RCC_OFFSET + 0x70)
#define RTCEN_BitNumber 0x0F
#define BDCR_RTCEN_BB ( \
    PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4) \
)

/* Alias word address of BDRST bit */
#define BDRST_BitNumber 0x10
#define BDCR_BDRST_BB ( \
    PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4) \
)

/* CSR Register */
/* Alias word address of LSION bit */
#define CSR_OFFSET (RCC_OFFSET + 0x74)
#define LSION_BitNumber 0x00
#define CSR_LSION_BB ( \
    PERIPH_BB_BASE + (CSR_OFFSET * 32) + (LSION_BitNumber * 4) \
)

/* RCC registers bit mask */
/* CFGR register bit mask */
#define CFGR_MCO2_RESET_MASK ((uint32_t) 0x07FFFFFF)
#define CFGR_MCO1_RESET_MASK ((uint32_t) 0xF89FFFFF)

/* RCC Flag Mask */
#define FLAG_MASK ((uint8_t) 0x1F)

/* CR register byte 3 (Bits[23:16]) base address */
#define CR_BYTE3_ADDRESS ((uint32_t) 0x40023802)

/* CIR register byte 2 (Bits[15:8]) base address */
#define CIR_BYTE2_ADDRESS ((uint32_t) (RCC_BASE + 0x0C + 0x01))

/* CIR register byte 3 (Bits[23:16]) base address */
#define CIR_BYTE3_ADDRESS ((uint32_t) (RCC_BASE + 0x0C + 0x02))

/* BDCR register base address */
#define BDCR_ADDRESS (PERIPH_BASE + BDCR_OFFSET)

static __I uint8_t APBAHBPrescTable[16] = {
    0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9
};

/**
 * Resets RCC clock configuration to default reset state.
 * The default reset state of clock configuration is given below:
 *     - HSI ON and used as system clock source
 *     - HSE, PLL and PLLI2S OFF
 *     - AHB, APB1 and APB2 prescaler set to 1.
 *     - CSS, MCO1 and MCO2 OFF
 *     - All interrupts disabled
 * This function doesn't modify configuration of the
 *     - Peripheral clocks
 *     - LSI, LSE and RTC clocks 
 * param None
 * retval None
 */
void RCC_DeInit(void) {
    RCC->CR |= (uint32_t) 0x00000001; /* Set HSION bit */
    RCC->CFGR = 0x00000000; /* Reset CFGR register */
    RCC->CR &= (uint32_t) 0xFEF6FFFF; /* Reset HSEON, CSSON and PLLON bits */
    RCC->PLLCFGR = 0x24003010; /* Reset PLLCFGR register */
    RCC->CR &= (uint32_t) 0xFFFBFFFF; /* Reset HSEBYP bit */
    RCC->CIR = 0x00000000; /* Disable all interrupts */
}

/**
 * Configures External High Speed oscillator (HSE).
 * After enabling HSE (RCC_HSE_ON or RCC_HSE_Bypass), application
 * software should wait on HSERDY flag to be set indicating that HSE clock
 * is stable and can be used to clock PLL and/or system clock.
 * HSE state can not be changed if it is used directly or through the
 * PLL as system clock. In this case, you have to select another source
 * of system clock then change HSE state (ex. disable it).
 * The HSE is stopped by hardware when entering STOP and STANDBY modes.
 * This function reset CSSON bit, so if Clock security system(CSS)
 * was previously enabled you have to enable it again after calling this
 * function.
 * param RCC_HSE: specifies new state of HSE.
 *   This parameter can be one of following values:
 *       arg RCC_HSE_OFF: turn OFF HSE oscillator, HSERDY flag goes low after
 *           6 HSE oscillator clock cycles.
 *       arg RCC_HSE_ON: turn ON HSE oscillator
 *       arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
 * retval None
 */
void RCC_HSEConfig(uint8_t RCC_HSE) {
    assert_param(IS_RCC_HSE(RCC_HSE));
    /* Reset HSEON and HSEBYP bits before configuring HSE */
    *(__IO uint8_t *) CR_BYTE3_ADDRESS = RCC_HSE_OFF;
    /* Set new HSE configuration */
    *(__IO uint8_t *) CR_BYTE3_ADDRESS = RCC_HSE;
}

/**
 * Waits for HSE start-up.
 * This functions waits on HSERDY flag to be set and return SUCCESS if 
 * this flag is set, otherwise returns ERROR if timeout is reached 
 * and this flag is not set. The timeout value is defined by constant
 * HSE_STARTUP_TIMEOUT in stm32f4xx.h file. You can tailor it depending
 * on HSE crystal used in your application.
 * param None
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: HSE oscillator is stable and ready to use
 *     - ERROR: HSE oscillator not yet ready
 */
ErrorStatus RCC_WaitForHSEStartUp(void) {
    __IO uint32_t startupcounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus hsestatus = RESET;

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        hsestatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
        startupcounter++;
    } while ((startupcounter != HSE_STARTUP_TIMEOUT) && (hsestatus == RESET));
    if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET) {
        status = SUCCESS;
    } else {
        status = ERROR;
    }
    return (status);
}

/**
 * Adjusts Internal High Speed oscillator (HSI) calibration value.
 * The calibration is used to compensate for variations in voltage
 * and temperature that influence frequency of internal HSI RC.
 * param HSICalibrationValue: specifies calibration trimming value.
 *   This parameter must be a number between 0 and 0x1F.
 * retval None
 */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_CALIBRATION_VALUE(HSICalibrationValue));
    tmpreg = RCC->CR;
    tmpreg &= ~RCC_CR_HSITRIM; /* Clear HSITRIM[4:0] bits */
    /* Set HSITRIM[4:0] bits according to HSICalibrationValue value */
    tmpreg |= (uint32_t) HSICalibrationValue << 3;
    RCC->CR = tmpreg; /* Store new value */
}

/**
 * Enables or disables Internal High Speed oscillator (HSI).
 * The HSI is stopped by hardware when entering STOP and STANDBY modes.
 * It is used (enabled by hardware) as system clock source after startup
 * from Reset, wakeup from STOP and STANDBY mode, or in case of failure
 * of HSE used directly or indirectly as system clock (if Clock
 * Security System CSS is enabled).
 * HSI can not be stopped if it is used as system clock source. In this case,
 * you have to select another source of system clock then stop HSI.
 * After enabling HSI, application software should wait on HSIRDY
 * flag to be set indicating that HSI clock is stable and can be used as
 * system clock source.
 * param NewState: new state of HSI.
 *   This parameter can be: ENABLE or DISABLE.
 * When HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
 * clock cycles.
 * retval None
 */
void RCC_HSICmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_HSION_BB = (uint32_t) NewState;
}

/**
 * Configures External Low Speed oscillator (LSE).
 * As LSE is in Backup domain and write access is denied to
 * this domain after reset, you have to enable write access using 
 * PWR_BackupAccessCmd(ENABLE) function before to configure LSE
 * (to be done once after reset).  
 * After enabling LSE (RCC_LSE_ON or RCC_LSE_Bypass), application
 * software should wait on LSERDY flag to be set indicating that LSE clock
 * is stable and can be used to clock RTC.
 * param RCC_LSE: specifies new state of LSE.
 *   This parameter can be one of following values:
 *       arg RCC_LSE_OFF: turn OFF LSE oscillator, LSERDY flag goes low after
 *           6 LSE oscillator clock cycles.
 *       arg RCC_LSE_ON: turn ON LSE oscillator
 *       arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
 * retval None
 */
void RCC_LSEConfig(uint8_t RCC_LSE) {
    assert_param(IS_RCC_LSE(RCC_LSE));
    /* Reset LSEON and LSEBYP bits before configuring LSE */
    /* Reset LSEON bit */
    *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_OFF;
    /* Reset LSEBYP bit */
    *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_OFF;
    /* Configure LSE (RCC_LSE_OFF is already covered by code section above) */
    switch (RCC_LSE) {
        case RCC_LSE_ON:
            /* Set LSEON bit */
            *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_ON;
            break;
        case RCC_LSE_Bypass:
            /* Set LSEBYP and LSEON bits */
            *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
            break;
        default:
            break;
    }
}

/**
 * Enables or disables Internal Low Speed oscillator (LSI).
 * After enabling LSI, application software should wait on 
 * LSIRDY flag to be set indicating that LSI clock is stable and can
 * be used to clock IWDG and/or RTC.
 * LSI can not be disabled if IWDG is running.
 * param NewState: new state of LSI.
 *   This parameter can be: ENABLE or DISABLE.
 * When LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
 * clock cycles.
 * retval None
 */
void RCC_LSICmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CSR_LSION_BB = (uint32_t) NewState;
}

/**
 * Configures main PLL clock source, multiplication and division factors.
 * This function must be used only when main PLL is disabled.
 * param RCC_PLLSource: specifies PLL entry clock source.
 *   This parameter can be one of following values:
 *       arg RCC_PLLSource_HSI: HSI oscillator clk selected as PLL clock entry
 *       arg RCC_PLLSource_HSE: HSE oscillator clk selected as PLL clock entry
 * This clock source (RCC_PLLSource) is common for main PLL and PLLI2S.
 * param PLLM: specifies division factor for PLL VCO input clock
 *   This parameter must be a number between 0 and 63.
 * You have to set PLLM parameter correctly to ensure that VCO input
 * frequency ranges from 1 to 2 MHz. It is recommended to select a frequency
 * of 2 MHz to limit PLL jitter.
 * param PLLN: specifies multiplication factor for PLL VCO output clock
 *   This parameter must be a number between 192 and 432.
 * You have to set PLLN parameter correctly to ensure that VCO
 * output frequency is between 192 and 432 MHz.
 * param PLLP: specifies division factor for main system clock (SYSCLK)
 *   This parameter must be a number in range {2, 4, 6, or 8}.
 * You have to set PLLP parameter correctly to not exceed 168 MHz on
 * System clock frequency.
 * param PLLQ: specifies division factor for OTG FS, SDIO and RNG clocks
 *   This parameter must be a number between 4 and 15.
 * If USB OTG FS is used in your application, you have to set the
 * PLLQ parameter correctly to have 48 MHz clock for USB. However,
 * SDIO and RNG need a frequency lower than or equal to 48 MHz to work
 * correctly.
 * retval None
 */
void RCC_PLLConfig(
    uint32_t RCC_PLLSource, uint32_t PLLM, uint32_t PLLN,
    uint32_t PLLP, uint32_t PLLQ
) {
    assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
    assert_param(IS_RCC_PLLM_VALUE(PLLM));
    assert_param(IS_RCC_PLLN_VALUE(PLLN));
    assert_param(IS_RCC_PLLP_VALUE(PLLP));
    assert_param(IS_RCC_PLLQ_VALUE(PLLQ));
    RCC->PLLCFGR = (
        PLLM | (PLLN << 6) | (((PLLP >> 1) -1) << 16) |
        (RCC_PLLSource) | (PLLQ << 24)
    );
}

/**
 * Enables or disables main PLL.
 * After enabling main PLL, application software should wait on
 * PLLRDY flag to be set indicating that PLL clock is stable and can
 * be used as system clock source.
 * The main PLL can not be disabled if it is used as system clock source
 * The main PLL is disabled by hardware when entering STOP and STANDBY modes.
 * param NewState: new state of main PLL. Parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_PLLCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_PLLON_BB = (uint32_t) NewState;
}

/**
 * Configures PLLI2S clock multiplication and division factors.
 * This function must be used only when PLLI2S is disabled.
 * PLLI2S clock source is common with main PLL (configured in 
 * RCC_PLLConfig function)
 * param PLLI2SN: specifies multiplication factor for PLLI2S VCO output clock
 *   This parameter must be a number between 192 and 432.
 * You have to set PLLI2SN parameter correctly to ensure that VCO
 * output frequency is between 192 and 432 MHz.
 * param PLLI2SR: specifies division factor for I2S clock
 *   This parameter must be a number between 2 and 7.
 * You have to set PLLI2SR parameter correctly to not exceed 192 MHz
 * on I2S clock frequency.
 * retval None
 */
void RCC_PLLI2SConfig(uint32_t PLLI2SN, uint32_t PLLI2SR) {
    assert_param(IS_RCC_PLLI2SN_VALUE(PLLI2SN));
    assert_param(IS_RCC_PLLI2SR_VALUE(PLLI2SR));
    RCC->PLLI2SCFGR = (PLLI2SN << 6) | (PLLI2SR << 28);
}

/**
 * Enables or disables PLLI2S.
 * The PLLI2S is disabled by hardware when entering STOP and STANDBY modes.
 * param NewState: new state of PLLI2S. Parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_PLLI2SCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_PLLI2SON_BB = (uint32_t) NewState;
}

/**
 * Enables or disables Clock Security System.
 * If a failure is detected on HSE oscillator clock, this oscillator
 * is automatically disabled and an interrupt is generated to inform the
 * software about failure (Clock Security System Interrupt, CSSI),
 * allowing MCU to perform rescue operations. The CSSI is linked to 
 * Cortex-M4 NMI (Non-Maskable Interrupt) exception vector.
 * param NewState: new state of Clock Security System.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_CSSON_BB = (uint32_t) NewState;
}

/**
 * Selects clock source to output on MCO1 pin(PA8).
 * PA8 should be configured in alternate function mode.
 * param RCC_MCO1Source: specifies clock source to output.
 *   This parameter can be one of following values:
 *       arg RCC_MCO1Source_HSI: HSI clock selected as MCO1 source
 *       arg RCC_MCO1Source_LSE: LSE clock selected as MCO1 source
 *       arg RCC_MCO1Source_HSE: HSE clock selected as MCO1 source
 *       arg RCC_MCO1Source_PLLCLK: main PLL clock selected as MCO1 source
 * param RCC_MCO1Div: specifies MCO1 prescaler.
 *   This parameter can be one of following values:
 *       arg RCC_MCO1Div_1: no division applied to MCO1 clock
 *       arg RCC_MCO1Div_2: division by 2 applied to MCO1 clock
 *       arg RCC_MCO1Div_3: division by 3 applied to MCO1 clock
 *       arg RCC_MCO1Div_4: division by 4 applied to MCO1 clock
 *       arg RCC_MCO1Div_5: division by 5 applied to MCO1 clock
 * retval None
 */
void RCC_MCO1Config(uint32_t RCC_MCO1Source, uint32_t RCC_MCO1Div) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_MCO1SOURCE(RCC_MCO1Source));
    assert_param(IS_RCC_MCO1DIV(RCC_MCO1Div));
    tmpreg = RCC->CFGR;
    tmpreg &= CFGR_MCO1_RESET_MASK; /* Clear MCO1[1:0] and MCO1PRE[2:0] bits */
    /* Select MCO1 clock source and prescaler */
    tmpreg |= RCC_MCO1Source | RCC_MCO1Div;
    RCC->CFGR = tmpreg; /* Store new value */
}

/**
 * Selects clock source to output on MCO2 pin(PC9).
 * PC9 should be configured in alternate function mode.
 * param RCC_MCO2Source: specifies clock source to output.
 *   This parameter can be one of following values:
 *       arg RCC_MCO2Source_SYSCLK: System clock (SYSCLK)
 *           selected as MCO2 source
 *       arg RCC_MCO2Source_PLLI2SCLK: PLLI2S clock selected as MCO2 source
 *       arg RCC_MCO2Source_HSE: HSE clock selected as MCO2 source
 *       arg RCC_MCO2Source_PLLCLK: main PLL clock selected as MCO2 source
 * param RCC_MCO2Div: specifies MCO2 prescaler.
 *   This parameter can be one of following values:
 *       arg RCC_MCO2Div_1: no division applied to MCO2 clock
 *       arg RCC_MCO2Div_2: division by 2 applied to MCO2 clock
 *       arg RCC_MCO2Div_3: division by 3 applied to MCO2 clock
 *       arg RCC_MCO2Div_4: division by 4 applied to MCO2 clock
 *       arg RCC_MCO2Div_5: division by 5 applied to MCO2 clock
 * retval None
 */
void RCC_MCO2Config(uint32_t RCC_MCO2Source, uint32_t RCC_MCO2Div) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_MCO2SOURCE(RCC_MCO2Source));
    assert_param(IS_RCC_MCO2DIV(RCC_MCO2Div));
    tmpreg = RCC->CFGR;
    tmpreg &= CFGR_MCO2_RESET_MASK; /* Clear MCO2 and MCO2PRE[2:0] bits */
    /* Select MCO2 clock source and prescaler */
    tmpreg |= RCC_MCO2Source | RCC_MCO2Div;
    RCC->CFGR = tmpreg; /* Store new value */
}

/**
 * Configures system clock (SYSCLK).
 * The HSI is used (enabled by hardware) as system clock source after
 * startup from Reset, wake-up from STOP and STANDBY mode, or in case
 * of failure of HSE used directly or indirectly as system clock
 * (if Clock Security System CSS is enabled).
 * A switch from one clock source to another occurs only if target
 * clock source is ready (clock stable after startup delay or PLL locked).
 * If a clock source which is not yet ready is selected, switch will
 * occur when clock source will be ready. 
 * You can use RCC_GetSYSCLKSource() function to know which clock is
 * currently used as system clock source. 
 * param RCC_SYSCLKSource: specifies clock source used as system clock.
 *   This parameter can be one of following values:
 *       arg RCC_SYSCLKSource_HSI: HSI selected as system clock source
 *       arg RCC_SYSCLKSource_HSE: HSE selected as system clock source
 *       arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
 * retval None
 */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
    tmpreg = RCC->CFGR;
    tmpreg &= ~RCC_CFGR_SW; /* Clear SW[1:0] bits */
    /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
    tmpreg |= RCC_SYSCLKSource;
    RCC->CFGR = tmpreg; /* Store new value */
}

/**
 * Returns clock source used as system clock.
 * param None
 * retval The clock source used as system clock.
 * The returned value can be one of following:
 *     - 0x00: HSI used as system clock
 *     - 0x04: HSE used as system clock
 *     - 0x08: PLL used as system clock
 */
uint8_t RCC_GetSYSCLKSource(void) {
    return ((uint8_t) (RCC->CFGR & RCC_CFGR_SWS));
}

/**
 * Configures AHB clock (HCLK).
 * Depending on device voltage range, software has to set correctly
 * these bits to ensure that HCLK not exceed maximum allowed frequency
 * (for more details refer to section above "CPU, AHB and APB busses
 * clocks configuration functions")
 * param RCC_SYSCLK: defines AHB clock divider. This clock is derived from
 *       system clock (SYSCLK).
 *   This parameter can be one of following values:
 *       arg RCC_SYSCLK_Div1: AHB clock = SYSCLK
 *       arg RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
 *       arg RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
 *       arg RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
 *       arg RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
 *       arg RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
 *       arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
 *       arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
 *       arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
 * retval None
 */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_HCLK(RCC_SYSCLK));
    tmpreg = RCC->CFGR;
    tmpreg &= ~RCC_CFGR_HPRE; /* Clear HPRE[3:0] bits */
    /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
    tmpreg |= RCC_SYSCLK;
    RCC->CFGR = tmpreg; /* Store new value */
}


/**
 * Configures Low Speed APB clock (PCLK1).
 * param RCC_HCLK: defines APB1 clock divider. This clock is derived from
 *       AHB clock (HCLK).
 *   This parameter can be one of following values:
 *       arg RCC_HCLK_Div1: APB1 clock = HCLK
 *       arg RCC_HCLK_Div2: APB1 clock = HCLK/2
 *       arg RCC_HCLK_Div4: APB1 clock = HCLK/4
 *       arg RCC_HCLK_Div8: APB1 clock = HCLK/8
 *       arg RCC_HCLK_Div16: APB1 clock = HCLK/16
 * retval None
 */
void RCC_PCLK1Config(uint32_t RCC_HCLK) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_PCLK(RCC_HCLK));
    tmpreg = RCC->CFGR;
    tmpreg &= ~RCC_CFGR_PPRE1; /* Clear PPRE1[2:0] bits */
    /* Set PPRE1[2:0] bits according to RCC_HCLK value */
    tmpreg |= RCC_HCLK;
    RCC->CFGR = tmpreg; /* Store new value */
}

/**
 * Configures High Speed APB clock (PCLK2).
 * param RCC_HCLK: defines APB2 clock divider. This clock is derived from
 *       AHB clock (HCLK).
 *   This parameter can be one of following values:
 *       arg RCC_HCLK_Div1: APB2 clock = HCLK
 *       arg RCC_HCLK_Div2: APB2 clock = HCLK/2
 *       arg RCC_HCLK_Div4: APB2 clock = HCLK/4
 *       arg RCC_HCLK_Div8: APB2 clock = HCLK/8
 *       arg RCC_HCLK_Div16: APB2 clock = HCLK/16
 * retval None
 */
void RCC_PCLK2Config(uint32_t RCC_HCLK) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_PCLK(RCC_HCLK));
    tmpreg = RCC->CFGR;
    tmpreg &= ~RCC_CFGR_PPRE2; /* Clear PPRE2[2:0] bits */
    /* Set PPRE2[2:0] bits according to RCC_HCLK value */
    tmpreg |= RCC_HCLK << 3;
    RCC->CFGR = tmpreg; /* Store new value */
}

/**
 * Returns frequencies of different on chip clocks; SYSCLK, HCLK,
 * PCLK1 and PCLK2.
 * The system frequency computed by this function is not real
 * frequency in chip. It is calculated based on predefined
 * constant and selected clock source:
 *     If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
 *     If SYSCLK source is HSE, function returns values based on HSE_VALUE(**)
 *     If SYSCLK source is PLL, function returns values based on HSE_VALUE(**)
 *     or HSI_VALUE(*) multiplied/divided by PLL factors.
 *   (*) HSI_VALUE is a constant defined in stm32f4xx.h file (default value
 *        16 MHz) but real value may vary depending on variations
 *        in voltage and temperature.
 *   (**) HSE_VALUE is a constant defined in stm32f4xx.h file (default value
 *        25 MHz), user has to ensure that HSE_VALUE is same as real
 *        frequency of crystal used. Otherwise, this function may
 *        have wrong result.
 * The result of this function could be not correct when using fractional
 * value for HSE crystal.
 * 
 * param RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
 * clocks frequencies.
 * 
 * This function can be used by user application to compute 
 * baudrate for communication peripherals or configure other parameters.
 * Each time SYSCLK, HCLK, PCLK1 and/or PCLK2 clock changes, this function
 * must be called to update structure's field. Otherwise, any
 * configuration based on this function will be incorrect.
 * retval None
 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks) {
    uint32_t tmp = 0, presc = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
    tmp = RCC->CFGR & RCC_CFGR_SWS; /* Get SYSCLK source */

    switch (tmp) {
        case 0x00:
            /* HSI used as system clock source */
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
        case 0x04:
            /* HSE used as system clock  source */
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
            break;
        case 0x08:  /* PLL used as system clock  source */
            /**
             * PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
             * SYSCLK = PLL_VCO / PLLP
             */
            pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
            pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
            if (pllsource != 0) {
                /* HSE used as PLL clock source */
                pllvco = (HSE_VALUE / pllm) * (
                    (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6
                );
            } else {
                /* HSI used as PLL clock source */
                pllvco = (HSI_VALUE / pllm) * (
                    (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6
                );
            }
            pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16) + 1 ) * 2;
            RCC_Clocks->SYSCLK_Frequency = pllvco / pllp;
            break;
        default:
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
    }
    /* Compute HCLK, PCLK1 and PCLK2 clocks frequencies */
    tmp = RCC->CFGR & RCC_CFGR_HPRE; /* Get HCLK prescaler */
    tmp = tmp >> 4;
    presc = APBAHBPrescTable[tmp];
    /* HCLK clock frequency */
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
    tmp = RCC->CFGR & RCC_CFGR_PPRE1; /* Get PCLK1 prescaler */
    tmp = tmp >> 10;
    presc = APBAHBPrescTable[tmp];
    /* PCLK1 clock frequency */
    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    tmp = RCC->CFGR & RCC_CFGR_PPRE2; /* Get PCLK2 prescaler */
    tmp = tmp >> 13;
    presc = APBAHBPrescTable[tmp];
    /* PCLK2 clock frequency */
    RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
}

/**
 * Configures RTC clock (RTCCLK).
 * As RTC clock configuration bits are in Backup domain and write
 * access is denied to this domain after reset, you have to enable write
 * access using PWR_BackupAccessCmd(ENABLE) function before to configure
 * RTC clock source (to be done once after reset).
 * Once RTC clock is configured it can't be changed unless
 * Backup domain is reset using RCC_BackupResetCmd() function, or by
 * a Power On Reset (POR).
 * param RCC_RTCCLKSource: specifies RTC clock source.
 *   This parameter can be one of following values:
 *       arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
 *       arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
 *       arg RCC_RTCCLKSource_HSE_Divx: HSE clock divided by x selected
 *           as RTC clock, where x:[2,31]
 * If LSE or LSI is used as RTC clock source, RTC continues to
 * work in STOP and STANDBY modes, and can be used as wakeup source.
 * However, when HSE clock is used as RTC clock source, RTC
 * cannot be used in STOP and STANDBY modes.    
 * The maximum input clock frequency for RTC is 1MHz (when using HSE as
 * RTC clock source).
 * retval None
 */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource) {
    uint32_t tmpreg = 0;

    assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
    if ((RCC_RTCCLKSource & 0x00000300) == 0x00000300) {
        /**
         * If HSE is selected as RTC clock source, configure HSE
         * division factor for RTC clock
         */
        tmpreg = RCC->CFGR;
        tmpreg &= ~RCC_CFGR_RTCPRE; /* Clear RTCPRE[4:0] bits */
        /* Configure HSE division factor for RTC clock */
        tmpreg |= (RCC_RTCCLKSource & 0xFFFFCFF);
        RCC->CFGR = tmpreg; /* Store new value */
    }
    RCC->BDCR |= (RCC_RTCCLKSource & 0x00000FFF); /* Select RTC clock source */
}

/**
 * Enables or disables RTC clock.
 * This function must be used only after RTC clock source was selected
 * using RCC_RTCCLKConfig function.
 * param NewState: new state of RTC clock. Parameter can be: ENABLE/DISABLE.
 * retval None
 */
void RCC_RTCCLKCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) BDCR_RTCEN_BB = (uint32_t) NewState;
}

/**
 * Forces or releases Backup domain reset.
 * This function resets RTC peripheral (including backup registers)
 * and RTC clock source selection in RCC_CSR register.
 * The BKPSRAM is not affected by this reset.
 * param NewState: new state of Backup domain reset.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_BackupResetCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) BDCR_BDRST_BB = (uint32_t) NewState;
}

/**
 * Configures I2S clock source (I2SCLK).
 * This function must be called before enabling I2S APB clock.
 * param RCC_I2SCLKSource: specifies I2S clock source.
 *   This parameter can be one of following values:
 *       arg RCC_I2S2CLKSource_PLLI2S: PLLI2S clock used as I2S clock source
 *       arg RCC_I2S2CLKSource_Ext: External clock mapped on I2S_CKIN pin
 *           used as I2S clock source
 * retval None
 */
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLKSource) {
    assert_param(IS_RCC_I2SCLK_SOURCE(RCC_I2SCLKSource));
    *(__IO uint32_t *) CFGR_I2SSRC_BB = RCC_I2SCLKSource;
}

/**
 * Enables or disables AHB1 peripheral clock.
 * After reset, peripheral clock (used for registers read/write access)
 * is disabled and application software has to enable this clock before 
 * using it.
 * param RCC_AHBPeriph: specifies AHB1 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_AHB1Periph_GPIOA: GPIOA clock
 *       arg RCC_AHB1Periph_GPIOB: GPIOB clock
 *       arg RCC_AHB1Periph_GPIOC: GPIOC clock
 *       arg RCC_AHB1Periph_GPIOD: GPIOD clock
 *       arg RCC_AHB1Periph_GPIOE: GPIOE clock
 *       arg RCC_AHB1Periph_GPIOF: GPIOF clock
 *       arg RCC_AHB1Periph_GPIOG: GPIOG clock
 *       arg RCC_AHB1Periph_GPIOG: GPIOG clock
 *       arg RCC_AHB1Periph_GPIOI: GPIOI clock
 *       arg RCC_AHB1Periph_CRC: CRC clock
 *       arg RCC_AHB1Periph_BKPSRAM: BKPSRAM interface clock
 *       arg RCC_AHB1Periph_CCMDATARAMEN CCM data RAM interface clock
 *       arg RCC_AHB1Periph_DMA1: DMA1 clock
 *       arg RCC_AHB1Periph_DMA2: DMA2 clock
 *       arg RCC_AHB1Periph_ETH_MAC: Ethernet MAC clock
 *       arg RCC_AHB1Periph_ETH_MAC_Tx: Ethernet Transmission clock
 *       arg RCC_AHB1Periph_ETH_MAC_Rx: Ethernet Reception clock
 *       arg RCC_AHB1Periph_ETH_MAC_PTP: Ethernet PTP clock
 *       arg RCC_AHB1Periph_OTG_HS: USB OTG HS clock
 *       arg RCC_AHB1Periph_OTG_HS_ULPI: USB OTG HS ULPI clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB1PeriphClockCmd(
    uint32_t RCC_AHB1Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB1_CLOCK_PERIPH(RCC_AHB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB1ENR |= RCC_AHB1Periph;
    } else {
        RCC->AHB1ENR &= ~RCC_AHB1Periph;
    }
}

/**
 * Enables or disables AHB2 peripheral clock.
 * After reset, peripheral clock (used for registers read/write access)
 * is disabled and application software has to enable this clock before 
 * using it.
 * param RCC_AHBPeriph: specifies AHB2 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_AHB2Periph_DCMI: DCMI clock
 *       arg RCC_AHB2Periph_CRYP: CRYP clock
 *       arg RCC_AHB2Periph_HASH: HASH clock
 *       arg RCC_AHB2Periph_RNG: RNG clock
 *       arg RCC_AHB2Periph_OTG_FS: USB OTG FS clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB2PeriphClockCmd(
    uint32_t RCC_AHB2Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB2_PERIPH(RCC_AHB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB2ENR |= RCC_AHB2Periph;
    } else {
        RCC->AHB2ENR &= ~RCC_AHB2Periph;
    }
}

/**
 * Enables or disables AHB3 peripheral clock.
 * After reset, peripheral clock (used for registers read/write access)
 * is disabled and application software has to enable this clock before
 * using it.
 * param RCC_AHBPeriph: specifies AHB3 peripheral to gates its clock.
 *   This parameter must be: RCC_AHB3Periph_FSMC
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB3PeriphClockCmd(
    uint32_t RCC_AHB3Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB3_PERIPH(RCC_AHB3Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB3ENR |= RCC_AHB3Periph;
    } else {
        RCC->AHB3ENR &= ~RCC_AHB3Periph;
    }
}

/**
 * Enables or disables Low Speed APB (APB1) peripheral clock.
 * After reset, peripheral clock (used for registers read/write access)
 * is disabled and application software has to enable this clock before 
 * using it.
 * param RCC_APB1Periph: specifies APB1 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_APB1Periph_TIM2: TIM2 clock
 *       arg RCC_APB1Periph_TIM3: TIM3 clock
 *       arg RCC_APB1Periph_TIM4: TIM4 clock
 *       arg RCC_APB1Periph_TIM5: TIM5 clock
 *       arg RCC_APB1Periph_TIM6: TIM6 clock
 *       arg RCC_APB1Periph_TIM7: TIM7 clock
 *       arg RCC_APB1Periph_TIM12: TIM12 clock
 *       arg RCC_APB1Periph_TIM13: TIM13 clock
 *       arg RCC_APB1Periph_TIM14: TIM14 clock
 *       arg RCC_APB1Periph_WWDG: WWDG clock
 *       arg RCC_APB1Periph_SPI2: SPI2 clock
 *       arg RCC_APB1Periph_SPI3: SPI3 clock
 *       arg RCC_APB1Periph_USART2: USART2 clock
 *       arg RCC_APB1Periph_USART3: USART3 clock
 *       arg RCC_APB1Periph_UART4: UART4 clock
 *       arg RCC_APB1Periph_UART5: UART5 clock
 *       arg RCC_APB1Periph_I2C1: I2C1 clock
 *       arg RCC_APB1Periph_I2C2: I2C2 clock
 *       arg RCC_APB1Periph_I2C3: I2C3 clock
 *       arg RCC_APB1Periph_CAN1: CAN1 clock
 *       arg RCC_APB1Periph_CAN2: CAN2 clock
 *       arg RCC_APB1Periph_PWR: PWR clock
 *       arg RCC_APB1Periph_DAC: DAC clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_APB1PeriphClockCmd(
    uint32_t RCC_APB1Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->APB1ENR |= RCC_APB1Periph;
    } else {
        RCC->APB1ENR &= ~RCC_APB1Periph;
    }
}

/**
 * Enables or disables High Speed APB (APB2) peripheral clock.
 * After reset, peripheral clock (used for registers read/write access)
 * is disabled and application software has to enable this clock before
 * using it.
 * param RCC_APB2Periph: specifies APB2 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_APB2Periph_TIM1: TIM1 clock
 *       arg RCC_APB2Periph_TIM8: TIM8 clock
 *       arg RCC_APB2Periph_USART1: USART1 clock
 *       arg RCC_APB2Periph_USART6: USART6 clock
 *       arg RCC_APB2Periph_ADC1: ADC1 clock
 *       arg RCC_APB2Periph_ADC2: ADC2 clock
 *       arg RCC_APB2Periph_ADC3: ADC3 clock
 *       arg RCC_APB2Periph_SDIO: SDIO clock
 *       arg RCC_APB2Periph_SPI1: SPI1 clock
 *       arg RCC_APB2Periph_SYSCFG: SYSCFG clock
 *       arg RCC_APB2Periph_TIM9: TIM9 clock
 *       arg RCC_APB2Periph_TIM10: TIM10 clock
 *       arg RCC_APB2Periph_TIM11: TIM11 clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_APB2PeriphClockCmd(
    uint32_t RCC_APB2Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->APB2ENR |= RCC_APB2Periph;
    } else {
        RCC->APB2ENR &= ~RCC_APB2Periph;
   }
}

/**
 * Forces or releases AHB1 peripheral reset.
 * param RCC_AHB1Periph: specifies AHB1 peripheral to reset.
 *   This parameter can be any combination of following values:
 *       arg RCC_AHB1Periph_GPIOA: GPIOA clock
 *       arg RCC_AHB1Periph_GPIOB: GPIOB clock
 *       arg RCC_AHB1Periph_GPIOC: GPIOC clock
 *       arg RCC_AHB1Periph_GPIOD: GPIOD clock
 *       arg RCC_AHB1Periph_GPIOE: GPIOE clock
 *       arg RCC_AHB1Periph_GPIOF: GPIOF clock
 *       arg RCC_AHB1Periph_GPIOG: GPIOG clock
 *       arg RCC_AHB1Periph_GPIOG: GPIOG clock
 *       arg RCC_AHB1Periph_GPIOI: GPIOI clock
 *       arg RCC_AHB1Periph_CRC: CRC clock
 *       arg RCC_AHB1Periph_DMA1: DMA1 clock
 *       arg RCC_AHB1Periph_DMA2: DMA2 clock
 *       arg RCC_AHB1Periph_ETH_MAC: Ethernet MAC clock
 *       arg RCC_AHB1Periph_OTG_HS: USB OTG HS clock
 * param NewState: new state of specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB1PeriphResetCmd(
    uint32_t RCC_AHB1Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB1_RESET_PERIPH(RCC_AHB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB1RSTR |= RCC_AHB1Periph;
    } else {
        RCC->AHB1RSTR &= ~RCC_AHB1Periph;
    }
}

/**
 * Forces or releases AHB2 peripheral reset.
 * param RCC_AHB2Periph: specifies AHB2 peripheral to reset.
 *   This parameter can be any combination of following values:
 *       arg RCC_AHB2Periph_DCMI: DCMI clock
 *       arg RCC_AHB2Periph_CRYP: CRYP clock
 *       arg RCC_AHB2Periph_HASH: HASH clock
 *       arg RCC_AHB2Periph_RNG: RNG clock
 *       arg RCC_AHB2Periph_OTG_FS: USB OTG FS clock
 * param NewState: new state of specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB2PeriphResetCmd(
    uint32_t RCC_AHB2Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB2_PERIPH(RCC_AHB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB2RSTR |= RCC_AHB2Periph;
    } else {
        RCC->AHB2RSTR &= ~RCC_AHB2Periph;
    }
}

/**
 * Forces or releases AHB3 peripheral reset.
 * param RCC_AHB3Periph: specifies AHB3 peripheral to reset.
 *   This parameter must be: RCC_AHB3Periph_FSMC
 * param NewState: new state of specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB3PeriphResetCmd(
    uint32_t RCC_AHB3Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB3_PERIPH(RCC_AHB3Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB3RSTR |= RCC_AHB3Periph;
    } else {
        RCC->AHB3RSTR &= ~RCC_AHB3Periph;
    }
}

/**
 * Forces or releases Low Speed APB (APB1) peripheral reset.
 * param RCC_APB1Periph: specifies APB1 peripheral to reset.
 *   This parameter can be any combination of following values:
 *       arg RCC_APB1Periph_TIM2: TIM2 clock
 *       arg RCC_APB1Periph_TIM3: TIM3 clock
 *       arg RCC_APB1Periph_TIM4: TIM4 clock
 *       arg RCC_APB1Periph_TIM5: TIM5 clock
 *       arg RCC_APB1Periph_TIM6: TIM6 clock
 *       arg RCC_APB1Periph_TIM7: TIM7 clock
 *       arg RCC_APB1Periph_TIM12: TIM12 clock
 *       arg RCC_APB1Periph_TIM13: TIM13 clock
 *       arg RCC_APB1Periph_TIM14: TIM14 clock
 *       arg RCC_APB1Periph_WWDG: WWDG clock
 *       arg RCC_APB1Periph_SPI2: SPI2 clock
 *       arg RCC_APB1Periph_SPI3: SPI3 clock
 *       arg RCC_APB1Periph_USART2: USART2 clock
 *       arg RCC_APB1Periph_USART3: USART3 clock
 *       arg RCC_APB1Periph_UART4: UART4 clock
 *       arg RCC_APB1Periph_UART5: UART5 clock
 *       arg RCC_APB1Periph_I2C1: I2C1 clock
 *       arg RCC_APB1Periph_I2C2: I2C2 clock
 *       arg RCC_APB1Periph_I2C3: I2C3 clock
 *       arg RCC_APB1Periph_CAN1: CAN1 clock
 *       arg RCC_APB1Periph_CAN2: CAN2 clock
 *       arg RCC_APB1Periph_PWR: PWR clock
 *       arg RCC_APB1Periph_DAC: DAC clock
 * param NewState: new state of specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_APB1PeriphResetCmd(
    uint32_t RCC_APB1Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->APB1RSTR |= RCC_APB1Periph;
    } else {
        RCC->APB1RSTR &= ~RCC_APB1Periph;
    }
}

/**
 * Forces or releases High Speed APB (APB2) peripheral reset.
 * param RCC_APB2Periph: specifies APB2 peripheral to reset.
 *   This parameter can be any combination of following values:
 *       arg RCC_APB2Periph_TIM1: TIM1 clock
 *       arg RCC_APB2Periph_TIM8: TIM8 clock
 *       arg RCC_APB2Periph_USART1: USART1 clock
 *       arg RCC_APB2Periph_USART6: USART6 clock
 *       arg RCC_APB2Periph_ADC1: ADC1 clock
 *       arg RCC_APB2Periph_ADC2: ADC2 clock
 *       arg RCC_APB2Periph_ADC3: ADC3 clock
 *       arg RCC_APB2Periph_SDIO: SDIO clock
 *       arg RCC_APB2Periph_SPI1: SPI1 clock
 *       arg RCC_APB2Periph_SYSCFG: SYSCFG clock
 *       arg RCC_APB2Periph_TIM9: TIM9 clock
 *       arg RCC_APB2Periph_TIM10: TIM10 clock
 *       arg RCC_APB2Periph_TIM11: TIM11 clock
 * param NewState: new state of specified peripheral reset.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_APB2PeriphResetCmd(
    uint32_t RCC_APB2Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_APB2_RESET_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->APB2RSTR |= RCC_APB2Periph;
    } else {
        RCC->APB2RSTR &= ~RCC_APB2Periph;
    }
}

/**
 * Enables or disables AHB1 peripheral clock during Low Power (Sleep) mode.
 * Peripheral clock gating in SLEEP mode can be used to further reduce
 * power consumption.
 * After wakeup from SLEEP mode, peripheral clock is enabled again.
 * By default, all peripheral clocks are enabled during SLEEP mode.
 * param RCC_AHBPeriph: specifies AHB1 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_AHB1Periph_GPIOA: GPIOA clock
 *       arg RCC_AHB1Periph_GPIOB: GPIOB clock 
 *       arg RCC_AHB1Periph_GPIOC: GPIOC clock
 *       arg RCC_AHB1Periph_GPIOD: GPIOD clock
 *       arg RCC_AHB1Periph_GPIOE: GPIOE clock
 *       arg RCC_AHB1Periph_GPIOF: GPIOF clock
 *       arg RCC_AHB1Periph_GPIOG: GPIOG clock
 *       arg RCC_AHB1Periph_GPIOG: GPIOG clock
 *       arg RCC_AHB1Periph_GPIOI: GPIOI clock
 *       arg RCC_AHB1Periph_CRC: CRC clock
 *       arg RCC_AHB1Periph_BKPSRAM: BKPSRAM interface clock
 *       arg RCC_AHB1Periph_DMA1: DMA1 clock
 *       arg RCC_AHB1Periph_DMA2: DMA2 clock
 *       arg RCC_AHB1Periph_ETH_MAC: Ethernet MAC clock
 *       arg RCC_AHB1Periph_ETH_MAC_Tx: Ethernet Transmission clock
 *       arg RCC_AHB1Periph_ETH_MAC_Rx: Ethernet Reception clock
 *       arg RCC_AHB1Periph_ETH_MAC_PTP: Ethernet PTP clock
 *       arg RCC_AHB1Periph_OTG_HS: USB OTG HS clock
 *       arg RCC_AHB1Periph_OTG_HS_ULPI: USB OTG HS ULPI clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB1PeriphClockLPModeCmd(
    uint32_t RCC_AHB1Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB1_LPMODE_PERIPH(RCC_AHB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB1LPENR |= RCC_AHB1Periph;
    } else {
        RCC->AHB1LPENR &= ~RCC_AHB1Periph;
    }
}

/**
 * Enables or disables AHB2 peripheral clock during Low Power (Sleep) mode.
 * Peripheral clock gating in SLEEP mode can be used to further reduce
 * power consumption.
 * After wakeup from SLEEP mode, peripheral clock is enabled again.
 * By default, all peripheral clocks are enabled during SLEEP mode.
 * param RCC_AHBPeriph: specifies AHB2 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_AHB2Periph_DCMI: DCMI clock
 *       arg RCC_AHB2Periph_CRYP: CRYP clock
 *       arg RCC_AHB2Periph_HASH: HASH clock
 *       arg RCC_AHB2Periph_RNG: RNG clock
 *       arg RCC_AHB2Periph_OTG_FS: USB OTG FS clock 
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB2PeriphClockLPModeCmd(
    uint32_t RCC_AHB2Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB2_PERIPH(RCC_AHB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB2LPENR |= RCC_AHB2Periph;
    } else {
        RCC->AHB2LPENR &= ~RCC_AHB2Periph;
    }
}

/**
 * Enables or disables AHB3 peripheral clock during Low Power (Sleep) mode.
 * Peripheral clock gating in SLEEP mode can be used to further reduce
 * power consumption.
 * After wakeup from SLEEP mode, peripheral clock is enabled again.
 * By default, all peripheral clocks are enabled during SLEEP mode.
 * param RCC_AHBPeriph: specifies AHB3 peripheral to gates its clock.
 *   This parameter must be: RCC_AHB3Periph_FSMC
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_AHB3PeriphClockLPModeCmd(
    uint32_t RCC_AHB3Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_AHB3_PERIPH(RCC_AHB3Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->AHB3LPENR |= RCC_AHB3Periph;
    } else {
        RCC->AHB3LPENR &= ~RCC_AHB3Periph;
    }
}

/**
 * Enables or disables APB1 peripheral clock during Low Power (Sleep) mode.
 * Peripheral clock gating in SLEEP mode can be used to further reduce
 * power consumption.
 * After wakeup from SLEEP mode, peripheral clock is enabled again.
 * By default, all peripheral clocks are enabled during SLEEP mode.
 * param RCC_APB1Periph: specifies APB1 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_APB1Periph_TIM2: TIM2 clock
 *       arg RCC_APB1Periph_TIM3: TIM3 clock
 *       arg RCC_APB1Periph_TIM4: TIM4 clock
 *       arg RCC_APB1Periph_TIM5: TIM5 clock
 *       arg RCC_APB1Periph_TIM6: TIM6 clock
 *       arg RCC_APB1Periph_TIM7: TIM7 clock
 *       arg RCC_APB1Periph_TIM12: TIM12 clock
 *       arg RCC_APB1Periph_TIM13: TIM13 clock
 *       arg RCC_APB1Periph_TIM14: TIM14 clock
 *       arg RCC_APB1Periph_WWDG: WWDG clock
 *       arg RCC_APB1Periph_SPI2: SPI2 clock
 *       arg RCC_APB1Periph_SPI3: SPI3 clock
 *       arg RCC_APB1Periph_USART2: USART2 clock
 *       arg RCC_APB1Periph_USART3: USART3 clock
 *       arg RCC_APB1Periph_UART4: UART4 clock
 *       arg RCC_APB1Periph_UART5: UART5 clock
 *       arg RCC_APB1Periph_I2C1: I2C1 clock
 *       arg RCC_APB1Periph_I2C2: I2C2 clock
 *       arg RCC_APB1Periph_I2C3: I2C3 clock
 *       arg RCC_APB1Periph_CAN1: CAN1 clock
 *       arg RCC_APB1Periph_CAN2: CAN2 clock
 *       arg RCC_APB1Periph_PWR: PWR clock
 *       arg RCC_APB1Periph_DAC: DAC clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_APB1PeriphClockLPModeCmd(
    uint32_t RCC_APB1Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->APB1LPENR |= RCC_APB1Periph;
    } else {
        RCC->APB1LPENR &= ~RCC_APB1Periph;
    }
}

/**
 * Enables or disables APB2 peripheral clock during Low Power (Sleep) mode.
 * Peripheral clock gating in SLEEP mode can be used to further reduce
 * power consumption.
 * After wakeup from SLEEP mode, peripheral clock is enabled again.
 * By default, all peripheral clocks are enabled during SLEEP mode.
 * param RCC_APB2Periph: specifies APB2 peripheral to gates its clock.
 *   This parameter can be any combination of following values:
 *       arg RCC_APB2Periph_TIM1: TIM1 clock
 *       arg RCC_APB2Periph_TIM8: TIM8 clock
 *       arg RCC_APB2Periph_USART1: USART1 clock
 *       arg RCC_APB2Periph_USART6: USART6 clock
 *       arg RCC_APB2Periph_ADC1: ADC1 clock
 *       arg RCC_APB2Periph_ADC2: ADC2 clock
 *       arg RCC_APB2Periph_ADC3: ADC3 clock
 *       arg RCC_APB2Periph_SDIO: SDIO clock
 *       arg RCC_APB2Periph_SPI1: SPI1 clock
 *       arg RCC_APB2Periph_SYSCFG: SYSCFG clock
 *       arg RCC_APB2Periph_TIM9: TIM9 clock
 *       arg RCC_APB2Periph_TIM10: TIM10 clock
 *       arg RCC_APB2Periph_TIM11: TIM11 clock
 * param NewState: new state of specified peripheral clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_APB2PeriphClockLPModeCmd(
    uint32_t RCC_APB2Periph, FunctionalState NewState
) {
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RCC->APB2LPENR |= RCC_APB2Periph;
    } else {
        RCC->APB2LPENR &= ~RCC_APB2Periph;
    }
}

/**
 * Enables or disables specified RCC interrupts.
 * param RCC_IT: specifies RCC interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of following values:
 *       arg RCC_IT_LSIRDY: LSI ready interrupt
 *       arg RCC_IT_LSERDY: LSE ready interrupt
 *       arg RCC_IT_HSIRDY: HSI ready interrupt
 *       arg RCC_IT_HSERDY: HSE ready interrupt
 *       arg RCC_IT_PLLRDY: main PLL ready interrupt
 *       arg RCC_IT_PLLI2SRDY: PLLI2S ready interrupt
 * param NewState: new state of specified RCC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState) {
    assert_param(IS_RCC_IT(RCC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /**
         *  Perform Byte access to RCC_CIR[14:8] bits
         * to enable selected interrupts
         */
        *(__IO uint8_t *) CIR_BYTE2_ADDRESS |= RCC_IT;
    } else {
        /**
         * Perform Byte access to RCC_CIR[14:8] bits
         * to disable selected interrupts
         */
        *(__IO uint8_t *) CIR_BYTE2_ADDRESS &= (uint8_t) ~RCC_IT;
    }
}

/**
 * Checks whether specified RCC flag is set or not.
 * param RCC_FLAG: specifies flag to check.
 *   This parameter can be one of following values:
 *       arg RCC_FLAG_HSIRDY: HSI oscillator clock ready
 *       arg RCC_FLAG_HSERDY: HSE oscillator clock ready
 *       arg RCC_FLAG_PLLRDY: main PLL clock ready
 *       arg RCC_FLAG_PLLI2SRDY: PLLI2S clock ready
 *       arg RCC_FLAG_LSERDY: LSE oscillator clock ready
 *       arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
 *       arg RCC_FLAG_BORRST: POR/PDR or BOR reset
 *       arg RCC_FLAG_PINRST: Pin reset
 *       arg RCC_FLAG_PORRST: POR/PDR reset
 *       arg RCC_FLAG_SFTRST: Software reset
 *       arg RCC_FLAG_IWDGRST: Independent Watchdog reset
 *       arg RCC_FLAG_WWDGRST: Window Watchdog reset
 *       arg RCC_FLAG_LPWRRST: Low Power reset
 * retval The new state of RCC_FLAG (SET or RESET).
 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG) {
    uint32_t tmp = 0;
    uint32_t statusreg = 0;
    FlagStatus bitstatus = RESET;

    assert_param(IS_RCC_FLAG(RCC_FLAG));
    tmp = RCC_FLAG >> 5; /* Get RCC register index */
    if (tmp == 1) {
        statusreg = RCC->CR;
    } else if (tmp == 2) {
        statusreg = RCC->BDCR;
    } else {
        statusreg = RCC->CSR;
    }
    tmp = RCC_FLAG & FLAG_MASK; /* Get flag position */
    if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus; /* Return flag status */
}

/**
 * Clears RCC reset flags.
 * The reset flags are: RCC_FLAG_PINRST, RCC_FLAG_PORRST,  RCC_FLAG_SFTRST,
 * RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
 * param None
 * retval None
 */
void RCC_ClearFlag(void) {
    RCC->CSR |= RCC_CSR_RMVF; /* Set RMVF bit to clear reset flags */
}

/**
 * Checks whether specified RCC interrupt has occurred or not.
 * param RCC_IT: specifies RCC interrupt source to check.
 *   This parameter can be one of following values:
 *       arg RCC_IT_LSIRDY: LSI ready interrupt
 *       arg RCC_IT_LSERDY: LSE ready interrupt
 *       arg RCC_IT_HSIRDY: HSI ready interrupt
 *       arg RCC_IT_HSERDY: HSE ready interrupt
 *       arg RCC_IT_PLLRDY: main PLL ready interrupt
 *       arg RCC_IT_PLLI2SRDY: PLLI2S ready interrupt
 *       arg RCC_IT_CSS: Clock Security System interrupt
 * retval The new state of RCC_IT (SET or RESET).
 */
ITStatus RCC_GetITStatus(uint8_t RCC_IT) {
    ITStatus bitstatus = RESET;

    assert_param(IS_RCC_GET_IT(RCC_IT));
    /* Check status of specified RCC interrupt */
    if ((RCC->CIR & RCC_IT) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus; /* Return RCC_IT status */
}

/**
 * Clears RCC's interrupt pending bits.
 * param RCC_IT: specifies interrupt pending bit to clear.
 *   This parameter can be any combination of following values:
 *       arg RCC_IT_LSIRDY: LSI ready interrupt
 *       arg RCC_IT_LSERDY: LSE ready interrupt
 *       arg RCC_IT_HSIRDY: HSI ready interrupt
 *       arg RCC_IT_HSERDY: HSE ready interrupt
 *       arg RCC_IT_PLLRDY: main PLL ready interrupt
 *       arg RCC_IT_PLLI2SRDY: PLLI2S ready interrupt
 *       arg RCC_IT_CSS: Clock Security System interrupt
 * retval None
 */
void RCC_ClearITPendingBit(uint8_t RCC_IT) {
    assert_param(IS_RCC_CLEAR_IT(RCC_IT));
    /**
     * Perform Byte access to RCC_CIR[23:16] bits
     * to clear selected interrupt pending bits
     */
    *(__IO uint8_t *) CIR_BYTE3_ADDRESS = RCC_IT;
}

