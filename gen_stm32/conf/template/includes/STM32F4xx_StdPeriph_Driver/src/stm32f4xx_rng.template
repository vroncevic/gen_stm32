/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_rng.c
 * 
 * This file provides firmware functions to manage the following
 * functionalities of the Random Number Generator (RNG) peripheral:
 *     - Initialization and Configuration 
 *     - Get 32 bit Random number
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_rng is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_rng is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_rng.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/**
 * Deinitializes the RNG peripheral registers to their default reset values.
 * param None
 * retval None
 */
void RNG_DeInit(void) {
    /* Enable RNG reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_RNG, ENABLE);
    /* Release RNG from reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_RNG, DISABLE);
}

/**
 * Enables or disables the RNG peripheral.
 * param NewState: new state of the RNG peripheral.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RNG_Cmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RNG->CR |= RNG_CR_RNGEN; /* Enable the RNG */
    } else {
        RNG->CR &= ~RNG_CR_RNGEN; /* Disable the RNG */
    }
}

/**
 * Returns a 32-bit random number.
 * 
 * Before to call this function you have to wait till DRDY (data ready)
 * flag is set, using RNG_GetFlagStatus(RNG_FLAG_DRDY) function.
 * Each time the the Random number data is read (using RNG_GetRandomNumber()
 * function), the RNG_FLAG_DRDY flag is automatically cleared.
 * In the case of a seed error, the generation of random numbers is 
 * interrupted for as long as the SECS bit is '1'. If a number is 
 * available in the RNG_DR register, it must not be used because it may 
 * not have enough entropy. In this case, it is recommended to clear the 
 * SEIS bit(using RNG_ClearFlag(RNG_FLAG_SECS) function), then disable 
 * and enable the RNG peripheral (using RNG_Cmd() function) to 
 * reinitialize and restart the RNG.
 * In the case of a clock error, the RNG is no more able to generate 
 * random numbers because the PLL48CLK clock is not correct. User have 
 * to check that the clock controller is correctly configured to provide
 * the RNG clock and clear the CEIS bit (using RNG_ClearFlag(RNG_FLAG_CECS) 
 * function) . The clock error has no impact on the previously generated 
 * random numbers, and the RNG_DR register contents can be used.
 * param None
 * retval 32-bit random number.
 */
uint32_t RNG_GetRandomNumber(void) {
    return RNG->DR; /* Return the 32 bit random number from the DR register */
}

/**
 * Enables or disables the RNG interrupt.
 * The RNG provides 3 interrupt sources:
 *     - Computed data is ready event (DRDY),
 *     - Seed error Interrupt (SEI) and
 *     - Clock error Interrupt (CEI),
 * All these interrupts sources are enabled by setting the IE bit in 
 * CR register. However, each interrupt have its specific status bit
 * (see RNG_GetITStatus() function) and clear bit except the DRDY event
 * (see RNG_ClearITPendingBit() function).
 * param NewState: new state of the RNG interrupt.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RNG_ITConfig(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RNG->CR |= RNG_CR_IE; /* Enable the RNG interrupt */
    } else {
        RNG->CR &= ~RNG_CR_IE; /* Disable the RNG interrupt */
    }
}

/**
 * Checks whether the specified RNG flag is set or not.
 * param RNG_FLAG: specifies the RNG flag to check.
 *   This parameter can be one of the following values:
 *       arg RNG_FLAG_DRDY: Data Ready flag.
 *       arg RNG_FLAG_CECS: Clock Error Current flag.
 *       arg RNG_FLAG_SECS: Seed Error Current flag.
 * retval The new state of RNG_FLAG (SET or RESET).
 */
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_RNG_GET_FLAG(RNG_FLAG));
    /* Check the status of the specified RNG flag */
    if ((RNG->SR & RNG_FLAG) != (uint8_t) RESET) {
        bitstatus = SET; /* RNG_FLAG is set */
    } else {
        bitstatus = RESET; /* RNG_FLAG is reset */
    }
    return  bitstatus; /* Return the RNG_FLAG status */
}

/**
 * Clears the RNG flags.
 * param RNG_FLAG: specifies the flag to clear. 
 *   This parameter can be any combination of the following values:
 *       arg RNG_FLAG_CECS: Clock Error Current flag.
 *       arg RNG_FLAG_SECS: Seed Error Current flag.
 * RNG_FLAG_DRDY can not be cleared by RNG_ClearFlag() function.
 * This flag is cleared only by reading the Random number data
 * (using RNG_GetRandomNumber() function).
 * retval None
 */
void RNG_ClearFlag(uint8_t RNG_FLAG) {
    assert_param(IS_RNG_CLEAR_FLAG(RNG_FLAG));
    /* Clear the selected RNG flags */
    RNG->SR = ~(uint32_t) (((uint32_t) RNG_FLAG) << 4);
}

/**
 * Checks whether the specified RNG interrupt has occurred or not.
 * param RNG_IT: specifies the RNG interrupt source to check.
 *   This parameter can be one of the following values:
 *       arg RNG_IT_CEI: Clock Error Interrupt.
 *       arg RNG_IT_SEI: Seed Error Interrupt.
 * retval The new state of RNG_IT (SET or RESET).
 */
ITStatus RNG_GetITStatus(uint8_t RNG_IT) {
    ITStatus bitstatus = RESET;

    assert_param(IS_RNG_GET_IT(RNG_IT));
    /* Check the status of the specified RNG interrupt */
    if ((RNG->SR & RNG_IT) != (uint8_t) RESET) {
        bitstatus = SET; /* RNG_IT is set */
    } else {
        bitstatus = RESET; /* RNG_IT is reset */
    }
    return bitstatus; /* Return the RNG_IT status */
}

/**
 * Clears the RNG interrupt pending bit(s).
 * param RNG_IT: specifies the RNG interrupt pending bit(s) to clear.
 *   This parameter can be any combination of the following values:
 *       arg RNG_IT_CEI: Clock Error Interrupt.
 *       arg RNG_IT_SEI: Seed Error Interrupt.
 * retval None
 */
void RNG_ClearITPendingBit(uint8_t RNG_IT) {
    assert_param(IS_RNG_IT(RNG_IT));
    RNG->SR = (uint8_t)~RNG_IT; /* Clear selected RNG interrupt pending bit */
}

