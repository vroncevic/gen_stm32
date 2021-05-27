/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_iwdg.c
 * 
 * This file provides firmware functions to manage the following
 * functionalities of the Independent watchdog (IWDG) peripheral:
 *     - Prescaler and Counter configuration
 *     - IWDG activation
 *     - Flag management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_iwdg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_iwdg is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_conf.h"

#define KR_KEY_RELOAD ((uint16_t) 0xAAAA)
#define KR_KEY_ENABLE ((uint16_t) 0xCCCC)

/**
 * Enables or disables write access to IWDG_PR and IWDG_RLR registers.
 * param IWDG_WriteAccess: new state of write access to IWDG_PR and
 * IWDG_RLR registers.
 *   This parameter can be one of the following values:
 *       arg IWDG_WriteAccess_Enable: Enable write access to IWDG_PR and
 *           IWDG_RLR registers
 *       arg IWDG_WriteAccess_Disable: Disable write access to IWDG_PR and
 *           IWDG_RLR registers
 * retval None
 */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess) {
    assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
    IWDG->KR = IWDG_WriteAccess;
}

/**
 * Sets IWDG Prescaler value.
 * param IWDG_Prescaler: specifies the IWDG Prescaler value.
 *   This parameter can be one of the following values:
 *       arg IWDG_Prescaler_4: IWDG prescaler set to 4
 *       arg IWDG_Prescaler_8: IWDG prescaler set to 8
 *       arg IWDG_Prescaler_16: IWDG prescaler set to 16
 *       arg IWDG_Prescaler_32: IWDG prescaler set to 32
 *       arg IWDG_Prescaler_64: IWDG prescaler set to 64
 *       arg IWDG_Prescaler_128: IWDG prescaler set to 128
 *       arg IWDG_Prescaler_256: IWDG prescaler set to 256
 * retval None
 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler) {
    assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
    IWDG->PR = IWDG_Prescaler;
}

/**
 * Sets IWDG Reload value.
 * param Reload: specifies the IWDG Reload value.
 * This parameter must be a number between 0 and 0x0FFF.
 * retval None
 */
void IWDG_SetReload(uint16_t Reload) {
    assert_param(IS_IWDG_RELOAD(Reload));
    IWDG->RLR = Reload;
}

/**
 * Reloads IWDG counter with value defined in the reload register
 * (write access to IWDG_PR and IWDG_RLR registers disabled).
 * param None
 * retval None
 */
void IWDG_ReloadCounter(void) {
    IWDG->KR = KR_KEY_RELOAD;
}

/**
 * Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
 * param None
 * retval None
 */
void IWDG_Enable(void) {
    IWDG->KR = KR_KEY_ENABLE;
}

/**
 * Checks whether the specified IWDG flag is set or not.
 * param IWDG_FLAG: specifies the flag to check.
 *   This parameter can be one of the following values:
 *       arg IWDG_FLAG_PVU: Prescaler Value Update on going
 *       arg IWDG_FLAG_RVU: Reload Value Update on going
 * retval The new state of IWDG_FLAG (SET or RESET).
 */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG) {
    FlagStatus bitstatus = RESET;
    assert_param(IS_IWDG_FLAG(IWDG_FLAG));
    if ((IWDG->SR & IWDG_FLAG) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

