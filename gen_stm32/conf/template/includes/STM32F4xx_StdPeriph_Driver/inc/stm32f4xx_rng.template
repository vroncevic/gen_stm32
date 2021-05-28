/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_rng.h
 * 
 * This file contains all the functions prototypes for the Random
 * Number Generator(RNG) firmware library.
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

#ifndef __STM32F4xx_RNG_H
#define __STM32F4xx_RNG_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define RNG_FLAG_DRDY ((uint8_t) 0x0001) /* Data ready */
#define RNG_FLAG_CECS ((uint8_t) 0x0002) /* Clock error current status */
#define RNG_FLAG_SECS ((uint8_t) 0x0004) /* Seed error current status */
#define RNG_IT_CEI ((uint8_t)0x20) /* Clock error interrupt */
#define RNG_IT_SEI ((uint8_t)0x40) /* Seed error interrupt */

#define IS_RNG_GET_FLAG(RNG_FLAG) ( \
    ((RNG_FLAG) == RNG_FLAG_DRDY) || \
    ((RNG_FLAG) == RNG_FLAG_CECS) || \
    ((RNG_FLAG) == RNG_FLAG_SECS) \
)

#define IS_RNG_CLEAR_FLAG(RNG_FLAG) ( \
    ((RNG_FLAG) == RNG_FLAG_CECS) || \
    ((RNG_FLAG) == RNG_FLAG_SECS) \
)

#define IS_RNG_IT(IT) ( \
    (((IT) & (uint8_t)0x9F) == 0x00) && ((IT) != 0x00) \
)

#define IS_RNG_GET_IT(RNG_IT) ( \
    ((RNG_IT) == RNG_IT_CEI) || ((RNG_IT) == RNG_IT_SEI) \
)

void RNG_DeInit(void);
void RNG_Cmd(FunctionalState NewState);
uint32_t RNG_GetRandomNumber(void);
void RNG_ITConfig(FunctionalState NewState);
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG);
void RNG_ClearFlag(uint8_t RNG_FLAG);
ITStatus RNG_GetITStatus(uint8_t RNG_IT);
void RNG_ClearITPendingBit(uint8_t RNG_IT);

#ifdef __cplusplus
    }
#endif

#endif

