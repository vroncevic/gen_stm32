/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_dbgmcu.c
 * 
 * This file provides all the DBGMCU firmware functions.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_dbgmcu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_dbgmcu is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_dbgmcu.h"
#include "stm32f4xx_conf.h"

#define IDCODE_DEVID_MASK ((uint32_t) 0x00000FFF)

/**
 * Returns the device revision identifier.
 * None
 * retval Device revision identifier
 */
uint32_t DBGMCU_GetREVID(void) {
    return(DBGMCU->IDCODE >> 16);
}

/**
 * Returns the device identifier.
 * None
 * retval Device identifier
 */
uint32_t DBGMCU_GetDEVID(void) {
    return(DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
 * Configures low power mode behavior when the MCU is in Debug mode.
 * DBGMCU_Periph: specifies the low power mode.
 *   This parameter can be any combination of the following values:
 *     arg DBGMCU_SLEEP: Keep debugger connection during SLEEP mode
 *     arg DBGMCU_STOP: Keep debugger connection during STOP mode
 *     arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
 * NewState: new state of the specified low power mode in Debug mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState) {
    /* Check the parameters */
    assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DBGMCU->CR |= DBGMCU_Periph;
    } else {
        DBGMCU->CR &= ~DBGMCU_Periph;
    }
}

/**
 * Configures APB1 peripheral behavior when the MCU is in Debug mode.
 * DBGMCU_Periph: specifies the APB1 peripheral.
 *   This parameter can be any combination of the following values:
 *     arg DBGMCU_TIM2_STOP: TIM2 counter stopped when Core is halted
 *     arg DBGMCU_TIM3_STOP: TIM3 counter stopped when Core is halted
 *     arg DBGMCU_TIM4_STOP: TIM4 counter stopped when Core is halted
 *     arg DBGMCU_TIM5_STOP: TIM5 counter stopped when Core is halted
 *     arg DBGMCU_TIM6_STOP: TIM6 counter stopped when Core is halted
 *     arg DBGMCU_TIM7_STOP: TIM7 counter stopped when Core is halted
 *     arg DBGMCU_TIM12_STOP: TIM12 counter stopped when Core is halted
 *     arg DBGMCU_TIM13_STOP: TIM13 counter stopped when Core is halted
 *     arg DBGMCU_TIM14_STOP: TIM14 counter stopped when Core is halted
 *     arg DBGMCU_RTC_STOP: RTC Calendar and Wakeup counter stopped
 *         when Core is halted
 *     arg DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted
 *     arg DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted
 *     arg DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped
 *         when Core is halted
 *     arg DBGMCU_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS timeout mode stopped
 *         when Core is halted
 *     arg DBGMCU_I2C3_SMBUS_TIMEOUT: I2C3 SMBUS timeout mode stopped
 *         when Core is halted
 *     arg DBGMCU_CAN2_STOP: Debug CAN1 stopped when Core is halted
 *     arg DBGMCU_CAN1_STOP: Debug CAN2 stopped when Core is halted
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DBGMCU_APB1PeriphConfig(
    uint32_t DBGMCU_Periph, FunctionalState NewState
) {
    /* Check the parameters */
    assert_param(IS_DBGMCU_APB1PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DBGMCU->APB1FZ |= DBGMCU_Periph;
    } else {
        DBGMCU->APB1FZ &= ~DBGMCU_Periph;
    }
}

/**
 * Configures APB2 peripheral behavior when the MCU is in Debug mode.
 * DBGMCU_Periph: specifies the APB2 peripheral.
 *   This parameter can be any combination of the following values:
 *     arg DBGMCU_TIM1_STOP: TIM1 counter stopped when Core is halted
 *     arg DBGMCU_TIM8_STOP: TIM8 counter stopped when Core is halted
 *     arg DBGMCU_TIM9_STOP: TIM9 counter stopped when Core is halted
 *     arg DBGMCU_TIM10_STOP: TIM10 counter stopped when Core is halted
 *     arg DBGMCU_TIM11_STOP: TIM11 counter stopped when Core is halted
 * NewState: new state of the specified peripheral in Debug mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DBGMCU_APB2PeriphConfig(
    uint32_t DBGMCU_Periph, FunctionalState NewState
) {
    /* Check the parameters */
    assert_param(IS_DBGMCU_APB2PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DBGMCU->APB2FZ |= DBGMCU_Periph;
    } else {
        DBGMCU->APB2FZ &= ~DBGMCU_Periph;
    }
}

