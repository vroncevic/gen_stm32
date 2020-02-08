/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_iwdg.h
 * 
 * This file contains all the functions prototypes for the IWDG 
 * firmware library.
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

#ifndef __STM32F4xx_IWDG_H
#define __STM32F4xx_IWDG_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define IWDG_WriteAccess_Enable ((uint16_t) 0x5555)
#define IWDG_WriteAccess_Disable ((uint16_t) 0x0000)
#define IWDG_Prescaler_4 ((uint8_t) 0x00)
#define IWDG_Prescaler_8 ((uint8_t) 0x01)
#define IWDG_Prescaler_16 ((uint8_t) 0x02)
#define IWDG_Prescaler_32 ((uint8_t) 0x03)
#define IWDG_Prescaler_64 ((uint8_t) 0x04)
#define IWDG_Prescaler_128 ((uint8_t) 0x05)
#define IWDG_Prescaler_256 ((uint8_t) 0x06)
#define IWDG_FLAG_PVU ((uint16_t) 0x0001)
#define IWDG_FLAG_RVU ((uint16_t) 0x0002)

#define IS_IWDG_WRITE_ACCESS(ACCESS) ( \
    ((ACCESS) == IWDG_WriteAccess_Enable) || \
    ((ACCESS) == IWDG_WriteAccess_Disable) \
)

#define IS_IWDG_PRESCALER(PRESCALER) ( \
    ((PRESCALER) == IWDG_Prescaler_4)  || \
    ((PRESCALER) == IWDG_Prescaler_8)  || \
    ((PRESCALER) == IWDG_Prescaler_16) || \
    ((PRESCALER) == IWDG_Prescaler_32) || \
    ((PRESCALER) == IWDG_Prescaler_64) || \
    ((PRESCALER) == IWDG_Prescaler_128)|| \
    ((PRESCALER) == IWDG_Prescaler_256) \
)

#define IS_IWDG_FLAG(FLAG) ( \
    ((FLAG) == IWDG_FLAG_PVU) || ((FLAG) == IWDG_FLAG_RVU) \
)

#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
    }
#endif

#endif

