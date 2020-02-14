/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_exti.c
 * 
 * This file provides firmware functions to manage the following
 * functionalities of the EXTI peripheral:
 *   - Initialization and Configuration
 *   - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_exti is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_exti is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_exti.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_conf.h"

#define EXTI_LINENONE ((uint32_t)0x00000)

/**
 * Deinitializes the EXTI peripheral registers to their default reset values.
 * param None
 * retval None
 */
void EXTI_DeInit(void) {
    EXTI->IMR = 0x00000000;
    EXTI->EMR = 0x00000000;
    EXTI->RTSR = 0x00000000;
    EXTI->FTSR = 0x00000000;
    EXTI->PR = 0x007FFFFF;
}

/**
 * Initializes the EXTI peripheral according to the specified
 * parameters in the EXTI_InitStruct.
 * param EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
 * that contains the configuration information for the EXTI peripheral.
 * retval None
 */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct) {
    uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
    assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
    assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));  
    assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));
    tmp = (uint32_t) EXTI_BASE;
    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE) {
        /* Clear EXTI line configuration */
        EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;
        tmp += EXTI_InitStruct->EXTI_Mode;
        *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
        /* Clear Rising Falling edge configuration */
        EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;
        /* Select the trigger for the selected external interrupts */
        if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling) {
            /* Rising Falling edge */
            EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
            EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
        } else {
            tmp = (uint32_t) EXTI_BASE;
            tmp += EXTI_InitStruct->EXTI_Trigger;
            *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
        }
    } else {
        tmp += EXTI_InitStruct->EXTI_Mode;
        /* Disable the selected external lines */
        *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
    }
}

/**
 * Fills each EXTI_InitStruct member with its reset value.
 * param EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
 * be initialized.
 * retval None
 */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct) {
    EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
 * Generates a Software interrupt on selected EXTI line.
 * param EXTI_Line: specifies the EXTI line on which the software interrupt
 * will be generated.
 * This parameter can be any combination of EXTI_Linex where x can be (0..22)
 * retval None
 */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line) {
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
    EXTI->SWIER |= EXTI_Line;
}

/**
 * Checks whether the specified EXTI line flag is set or not.
 * param EXTI_Line: specifies the EXTI line flag to check.
 *          This parameter can be EXTI_Linex where x can be(0..22)
 * retval The new state of EXTI_Line (SET or RESET).
 */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line) {
    FlagStatus bitstatus = RESET;
    /* Check the parameters */

    assert_param(IS_GET_EXTI_LINE(EXTI_Line));
    if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears the EXTI's line pending flags.
 * param EXTI_Line: specifies the EXTI lines flags to clear.
 * This parameter can be any combination of EXTI_Linex where x can be (0..22)
 * retval None
 */
void EXTI_ClearFlag(uint32_t EXTI_Line) {
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
    EXTI->PR = EXTI_Line;
}

/**
 * Checks whether the specified EXTI line is asserted or not.
 * param EXTI_Line: specifies the EXTI line to check.
 * This parameter can be EXTI_Linex where x can be(0..22)
 * retval The new state of EXTI_Line (SET or RESET).
 */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));
    enablestatus =  EXTI->IMR & EXTI_Line;
    if (
        ((EXTI->PR & EXTI_Line) != (uint32_t) RESET) &&
        (enablestatus != (uint32_t) RESET)
    ) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears the EXTI's line pending bits.
 * param EXTI_Line: specifies the EXTI lines to clear.
 * This parameter can be any combination of EXTI_Linex where x can be (0..22)
 * retval None
 */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line) {
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(EXTI_Line));
    EXTI->PR = EXTI_Line;
}

