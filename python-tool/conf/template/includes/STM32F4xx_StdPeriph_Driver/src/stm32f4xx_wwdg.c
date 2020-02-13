/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_wwdg.c
 * 
 * This file provides firmware functions to manage the following
 * functionalities of the Window watchdog (WWDG) peripheral:
 *   - Prescaler, Refresh window and Counter configuration
 *   - WWDG activation
 *   - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * CMSIS DSP Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * CMSIS DSP Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_wwdg.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

#define WWDG_OFFSET (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFR_OFFSET (WWDG_OFFSET + 0x04)
#define EWI_BitNumber 0x09
#define CFR_EWI_BB (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* CFR register bit mask */
#define CFR_WDGTB_MASK ((uint32_t) 0xFFFFFE7F)
#define CFR_W_MASK ((uint32_t) 0xFFFFFF80)
#define BIT_MASK ((uint8_t) 0x7F)

/**
 * Deinitializes WWDG peripheral registers to their default reset values.
 * param None
 * retval None
 */
void WWDG_DeInit(void) {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
 * Sets the WWDG Prescaler.
 * param  WWDG_Prescaler: specifies the WWDG Prescaler. This parameter can
 * be one of the following values:
 *     arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
 *     arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
 *     arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
 *     arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
 * retval None
 */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler) {
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
    /* Clear WDGTB[1:0] bits */
    tmpreg = WWDG->CFR & CFR_WDGTB_MASK;
    /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
    tmpreg |= WWDG_Prescaler;
    /* Store the new value */
    WWDG->CFR = tmpreg;
}

/**
 * Sets the WWDG window value.
 * param  WindowValue: specifies window value to be compared to downcounter.
 * This parameter value must be lower than 0x80.
 * retval None
 */
void WWDG_SetWindowValue(uint8_t WindowValue) {
    __IO uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
    /* Clear W[6:0] bits */
    tmpreg = WWDG->CFR & CFR_W_MASK;
    /* Set W[6:0] bits according to WindowValue value */
    tmpreg |= WindowValue & (uint32_t) BIT_MASK;
    /* Store the new value */
    WWDG->CFR = tmpreg;
}

/**
 * Enables the WWDG Early Wakeup interrupt(EWI).
 * Once enabled this interrupt cannot be disabled except by a system reset.
 * param  None
 * retval None
 */
void WWDG_EnableIT(void) {
    *(__IO uint32_t *) CFR_EWI_BB = (uint32_t) ENABLE;
}

/**
 * Sets the WWDG counter value.
 * param  Counter: specifies the watchdog counter value. This parameter must
 * be a number between 0x40 and 0x7F (to prevent generating an immediate
 * reset) 
 * retval None
 */
void WWDG_SetCounter(uint8_t Counter) {
    /* Check the parameters */
    assert_param(IS_WWDG_COUNTER(Counter));
    /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
    WWDG->CR = Counter & BIT_MASK;
}

/**
 * Enables WWDG and load the counter value.
 * param  Counter: specifies the watchdog counter value. This parameter
 * must be a number between 0x40 and 0x7F (to prevent generating an
 * immediate reset)
 * retval None
 */
void WWDG_Enable(uint8_t Counter) {
    /* Check the parameters */
    assert_param(IS_WWDG_COUNTER(Counter));
    WWDG->CR = WWDG_CR_WDGA | Counter;
}

/**
 * Checks whether the Early Wakeup interrupt flag is set or not.
 * param  None
 * retval The new state of the Early Wakeup interrupt flag (SET or RESET)
 */
FlagStatus WWDG_GetFlagStatus(void) {
    FlagStatus bitstatus = RESET;

    if ((WWDG->SR) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears Early Wakeup interrupt flag.
 * param  None
 * retval None
 */
void WWDG_ClearFlag(void) {
    WWDG->SR = (uint32_t) RESET;
}

