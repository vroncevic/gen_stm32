/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_pwr.c
 * 
 * This file provides firmware functions to manage following 
 * functionalities of Power Controller (PWR) peripheral:
 *      - Backup Domain Access
 *      - PVD configuration
 *      - WakeUp pin configuration
 *      - Main and Backup Regulators configuration
 *      - FLASH Power Down configuration
 *      - Low Power modes configuration
 *      - Flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_pwr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_pwr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

#define PWR_OFFSET (PWR_BASE - PERIPH_BASE)

/* Alias word address of DBP bit */
#define CR_OFFSET (PWR_OFFSET + 0x00)
#define DBP_BitNumber 0x08
#define CR_DBP_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber 0x04
#define CR_PVDE_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* Alias word address of FPDS bit */
#define FPDS_BitNumber 0x09
#define CR_FPDS_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (FPDS_BitNumber * 4))

/* Alias word address of PMODE bit */
#define PMODE_BitNumber 0x0E
#define CR_PMODE_BB (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PMODE_BitNumber * 4))

/* Alias word address of EWUP bit */
#define CSR_OFFSET (PWR_OFFSET + 0x04)
#define EWUP_BitNumber 0x08
#define CSR_EWUP_BB (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* Alias word address of BRE bit */
#define BRE_BitNumber 0x09
#define CSR_BRE_BB (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (BRE_BitNumber * 4))

/* CR register bit mask */
#define CR_DS_MASK ((uint32_t) 0xFFFFFFFC)
#define CR_PLS_MASK ((uint32_t) 0xFFFFFF1F)

/**
 * Deinitializes PWR peripheral registers to their default reset values.
 * param None
 * retval None
 */
void PWR_DeInit(void) {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
 * Enables or disables access to backup domain (RTC registers, RTC
 * backup data registers and backup SRAM).
 * If HSE divided by 2, 3, .. 31 is used as RTC clock,
 * Backup Domain Access should be kept enabled.
 * param NewState: new state of access to backup domain.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void PWR_BackupAccessCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_DBP_BB = (uint32_t) NewState;
}

/**
 * Configures voltage threshold detected by Power Voltage Detector(PVD).
 * param PWR_PVDLevel: specifies PVD detection level
 *   This parameter can be one of following values:
 *       arg PWR_PVDLevel_0: PVD detection level set to 2.0V
 *       arg PWR_PVDLevel_1: PVD detection level set to 2.2V
 *       arg PWR_PVDLevel_2: PVD detection level set to 2.3V
 *       arg PWR_PVDLevel_3: PVD detection level set to 2.5V
 *       arg PWR_PVDLevel_4: PVD detection level set to 2.7V
 *       arg PWR_PVDLevel_5: PVD detection level set to 2.8V
 *       arg PWR_PVDLevel_6: PVD detection level set to 2.9V
 *       arg PWR_PVDLevel_7: PVD detection level set to 3.0V
 * Refer to elect characteristics of you device datasheet for more details.
 * retval None
 */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel) {
    uint32_t tmpreg = 0;

    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
    tmpreg = PWR->CR;
    tmpreg &= CR_PLS_MASK; /* Clear PLS[7:5] bits */
    tmpreg |= PWR_PVDLevel; /* Set PLS[7:5] bits to PWR_PVDLevel value */
    PWR->CR = tmpreg; /* Store new value */
}

/**
 * Enables or disables Power Voltage Detector(PVD).
 * param NewState: new state of PVD.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void PWR_PVDCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_PVDE_BB = (uint32_t) NewState;
}

/**
 * Enables or disables WakeUp Pin functionality.
 * param NewState: new state of WakeUp Pin functionality.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void PWR_WakeUpPinCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t) NewState;
}

/**
 * Enables or disables Backup Regulator.
 * param NewState: new state of Backup Regulator.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void PWR_BackupRegulatorCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CSR_BRE_BB = (uint32_t) NewState;
}

/**
 * Configures main internal regulator output voltage.
 * param PWR_Regulator_Voltage: specifies regulator output voltage to achieve
 *       a tradeoff between performance and power consumption when device does
 *       not operate at maximum frequency (refer to datasheets for more).
 *   This parameter can be one of following values:
 *       arg PWR_Regulator_Voltage_Scale1: Regulator voltage output
 *           Scale 1 mode, System frequency up to 168 MHz.
 *       arg PWR_Regulator_Voltage_Scale2: Regulator voltage output
 *           Scale 2 mode, System frequency up to 144 MHz.
 * retval None
 */
void PWR_MainRegulatorModeConfig(uint32_t PWR_Regulator_Voltage) {
    assert_param(IS_PWR_REGULATOR_VOLTAGE(PWR_Regulator_Voltage));
    if (PWR_Regulator_Voltage == PWR_Regulator_Voltage_Scale2) {
        PWR->CR &= ~PWR_Regulator_Voltage_Scale1;
    } else {
        PWR->CR |= PWR_Regulator_Voltage_Scale1;
    }
}

/**
 * Enables or disables Flash Power Down in STOP mode.
 * param NewState: new state of Flash power mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void PWR_FlashPowerDownCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    *(__IO uint32_t *) CR_FPDS_BB = (uint32_t) NewState;
}

/**
 * Enters STOP mode.
 * 
 * In Stop mode, all I/O pins keep same state as in Run mode.
 * When exiting Stop mode by issuing an interrupt or a wakeup event,
 * HSI RC oscillator is selected as system clock.
 * When voltage regulator operates in low power mode, an additional
 * startup delay is incurred when waking up from Stop mode.
 * By keeping internal regulator ON during Stop mode, consumption
 * is higher although startup time is reduced.
 *
 * param PWR_Regulator: specifies regulator state in STOP mode.
 *   This parameter can be one of following values:
 *       arg PWR_Regulator_ON: STOP mode with regulator ON
 *       arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
 * param PWR_STOPEntry: specifies if STOP mode in entered with WFI or
 *       WFE instruction.
 *   This parameter can be one of following values:
 *       arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
 *       arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
 * retval None
 */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry) {
    uint32_t tmpreg = 0;

    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
    tmpreg = PWR->CR; /* Select regulator state in STOP mode */
    tmpreg &= CR_DS_MASK; /* Clear PDDS and LPDSR bits */
    /* Set LPDSR bit according to PWR_Regulator value */
    tmpreg |= PWR_Regulator;
    PWR->CR = tmpreg; /* Store new value */
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    /* Select STOP mode entry */
    if(PWR_STOPEntry == PWR_STOPEntry_WFI) {
        __WFI(); /* Request Wait For Interrupt */
    } else {
        __WFE(); /* Request Wait For Event */
    }
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t) SCB_SCR_SLEEPDEEP_Msk);
}

/**
 * Enters STANDBY mode.
 * In Standby mode, all I/O pins are high impedance except for:
 *     - Reset pad (still available)
 *     - RTC_AF1 pin (PC13) if configured for tamper, time-stamp, RTC
 *       Alarm out, or RTC clock calibration out.
 *     - RTC_AF2 pin (PI8) if configured for tamper or time-stamp.
 *     - WKUP pin 1 (PA0) if enabled.
 * param None
 * retval None
 */
void PWR_EnterSTANDBYMode(void) {
    PWR->CR |= PWR_CR_CWUF; /* Clear Wakeup flag */
    PWR->CR |= PWR_CR_PDDS; /* Select STANDBY mode */
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    /* This option is used to ensure that store operations are completed */
#if defined(__CC_ARM)
    __force_stores();
#endif
    __WFI(); /* Request Wait For Interrupt */
}

/**
 * Checks whether specified PWR flag is set or not.
 * param PWR_FLAG: specifies flag to check.
 *   This parameter can be one of following values:
 *       arg PWR_FLAG_WU: Wake Up flag. This flag indicates that wakeup event
 *           was received from WKUP pin or from RTC alarm (Alarm A 
 *           or Alarm B), RTC Tamper event, RTC TimeStamp event or RTC Wakeup
 *           An additional wakeup event is detected if WKUP pin is enabled
 *           (by setting EWUP bit) when WKUP pin level is already high.
 *       arg PWR_FLAG_SB: StandBy flag. This flag indicates that system was
 *           resumed from StandBy mode.    
 *       arg PWR_FLAG_PVDO: PVD Output. Flag is valid only if PVD is enabled
 *           by PWR_PVDCmd() function. The PVD is stopped by Standby mode
 *           For this reason, this bit is equal to 0 after Standby or reset
 *           until PVDE bit is set.
 *       arg PWR_FLAG_BRR: Backup regulator ready flag. This bit is not reset
 *           when device wakes up from Standby mode or by a system reset
 *           or power reset.  
 *       arg PWR_FLAG_VOSRDY: This flag indicates that Regulator voltage
 *           scaling output selection is ready.
 * retval The new state of PWR_FLAG (SET or RESET).
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));
    if ((PWR->CSR & PWR_FLAG) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus; /* Return flag status */
}

/**
 * Clears PWR's pending flags
 * param PWR_FLAG: specifies flag to clear
 *   This parameter can be one of following values:
 *       arg PWR_FLAG_WU: Wake Up flag
 *       arg PWR_FLAG_SB: StandBy flag
 * retval None
 */
void PWR_ClearFlag(uint32_t PWR_FLAG) {
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
    PWR->CR |= PWR_FLAG << 2;
}

