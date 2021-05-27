/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_dbgmcu.h
 * 
 * This file contains all the functions prototypes for the DBGMCU
 * firmware library.
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

#ifndef __STM32F4xx_DBGMCU_H
#define __STM32F4xx_DBGMCU_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define DBGMCU_SLEEP ((uint32_t) 0x00000001)
#define DBGMCU_STOP ((uint32_t) 0x00000002)
#define DBGMCU_STANDBY ((uint32_t) 0x00000004)
#define DBGMCU_TIM2_STOP ((uint32_t) 0x00000001)
#define DBGMCU_TIM3_STOP ((uint32_t) 0x00000002)
#define DBGMCU_TIM4_STOP ((uint32_t) 0x00000004)
#define DBGMCU_TIM5_STOP ((uint32_t) 0x00000008)
#define DBGMCU_TIM6_STOP ((uint32_t) 0x00000010)
#define DBGMCU_TIM7_STOP ((uint32_t) 0x00000020)
#define DBGMCU_TIM12_STOP ((uint32_t) 0x00000040)
#define DBGMCU_TIM13_STOP ((uint32_t) 0x00000080)
#define DBGMCU_TIM14_STOP ((uint32_t) 0x00000100)
#define DBGMCU_RTC_STOP ((uint32_t) 0x00000400)
#define DBGMCU_WWDG_STOP ((uint32_t) 0x00000800)
#define DBGMCU_IWDG_STOP ((uint32_t) 0x00001000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT ((uint32_t) 0x00200000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT ((uint32_t) 0x00400000)
#define DBGMCU_I2C3_SMBUS_TIMEOUT ((uint32_t) 0x00800000)
#define DBGMCU_CAN1_STOP ((uint32_t) 0x02000000)
#define DBGMCU_CAN2_STOP ((uint32_t) 0x04000000)
#define DBGMCU_TIM1_STOP ((uint32_t) 0x00000001)
#define DBGMCU_TIM8_STOP ((uint32_t) 0x00000002)
#define DBGMCU_TIM9_STOP ((uint32_t) 0x00010000)
#define DBGMCU_TIM10_STOP ((uint32_t) 0x00020000)
#define DBGMCU_TIM11_STOP ((uint32_t) 0x00040000)

#define IS_DBGMCU_PERIPH(PERIPH) ( \
    (((PERIPH) & 0xFFFFFFF8) == 0x00) && ((PERIPH) != 0x00) \
)

#define IS_DBGMCU_APB1PERIPH(PERIPH) ( \
    (((PERIPH) & 0xF91FE200) == 0x00) && ((PERIPH) != 0x00) \
)

#define IS_DBGMCU_APB2PERIPH(PERIPH) ( \
    (((PERIPH) & 0xFFF8FFFC) == 0x00) && ((PERIPH) != 0x00) \
)

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
    }
#endif

#endif

