/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_wwdg.h
 * 
 * This file contains all the functions prototypes for the WWDG firmware
 * library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_wwdg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_wwdg is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_WWDG_H
#define __STM32F4xx_WWDG_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define WWDG_Prescaler_1 ((uint32_t) 0x00000000)
#define WWDG_Prescaler_2 ((uint32_t) 0x00000080)
#define WWDG_Prescaler_4 ((uint32_t) 0x00000100)
#define WWDG_Prescaler_8 ((uint32_t) 0x00000180)

#define IS_WWDG_PRESCALER(PRESCALER) ( \
    ((PRESCALER) == WWDG_Prescaler_1) || \
    ((PRESCALER) == WWDG_Prescaler_2) || \
    ((PRESCALER) == WWDG_Prescaler_4) || \
    ((PRESCALER) == WWDG_Prescaler_8) \
)

#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

#ifdef __cplusplus
    }
#endif

#endif

