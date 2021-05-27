/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * misc.h
 * 
 * This file has extern declaration for common tables like Bitreverse,
 * reciprocal etc which are used across different functions.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * misc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * misc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MISC_H
#define __MISC_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    /**
     * Specifies the IRQ channel to be enabled or disabled.
     * This parameter can be an enumerator of IRQn_Type 
     * enumeration (For the complete STM32 Devices IRQ Channels
     * list, please refer to stm32f4xx.h file).
     */
    uint8_t NVIC_IRQChannel;
    /**
     * Specifies the pre-emption priority for the IRQ channel
     * specified in NVIC_IRQChannel. This parameter can be a value
     * between 0 and 15 as described in the table MISC_NVIC_Priority_Table
     * A lower priority value indicates a higher priority.
     */
    uint8_t NVIC_IRQChannelPreemptionPriority;
    /**
     * Specifies the subpriority level for the IRQ channel specified
     * in NVIC_IRQChannel. This parameter can be a value
     * between 0 and 15 as described in the table MISC_NVIC_Priority_Table
     * A lower priority value indicates a higher priority.
     */
    uint8_t NVIC_IRQChannelSubPriority;
    /**
     * Specifies whether the IRQ channel defined in NVIC_IRQChannel
     * will be enabled or disabled.
     * This parameter can be set either to ENABLE or DISABLE.
     */
    FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;

#define NVIC_VectTab_RAM ((uint32_t) 0x20000000)
#define NVIC_VectTab_FLASH ((uint32_t) 0x08000000)

#define IS_NVIC_VECTTAB(VECTTAB) ( \
    ((VECTTAB) == NVIC_VectTab_RAM) || \
    ((VECTTAB) == NVIC_VectTab_FLASH) \
)

#define NVIC_LP_SEVONPEND ((uint8_t) 0x10)
#define NVIC_LP_SLEEPDEEP ((uint8_t) 0x04)
#define NVIC_LP_SLEEPONEXIT ((uint8_t) 0x02)

#define IS_NVIC_LP(LP) ( \
    ((LP) == NVIC_LP_SEVONPEND) || \
    ((LP) == NVIC_LP_SLEEPDEEP) || \
    ((LP) == NVIC_LP_SLEEPONEXIT) \
)

#define NVIC_PriorityGroup_0 ((uint32_t) 0x700)
#define NVIC_PriorityGroup_1 ((uint32_t) 0x600)
#define NVIC_PriorityGroup_2 ((uint32_t) 0x500)
#define NVIC_PriorityGroup_3 ((uint32_t) 0x400)
#define NVIC_PriorityGroup_4 ((uint32_t) 0x300)

#define IS_NVIC_PRIORITY_GROUP(GROUP) ( \
    ((GROUP) == NVIC_PriorityGroup_0) || \
    ((GROUP) == NVIC_PriorityGroup_1) || \
    ((GROUP) == NVIC_PriorityGroup_2) || \
    ((GROUP) == NVIC_PriorityGroup_3) || \
    ((GROUP) == NVIC_PriorityGroup_4) \
)

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY) ((PRIORITY) < 0x10)
#define IS_NVIC_SUB_PRIORITY(PRIORITY) ((PRIORITY) < 0x10)
#define IS_NVIC_OFFSET(OFFSET) ((OFFSET) < 0x000FFFFF)
#define SysTick_CLKSource_HCLK_Div8 ((uint32_t) 0xFFFFFFFB)
#define SysTick_CLKSource_HCLK ((uint32_t) 0x00000004)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) ( \
    ((SOURCE) == SysTick_CLKSource_HCLK) || \
    ((SOURCE) == SysTick_CLKSource_HCLK_Div8) \
)

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
    }
#endif

#endif

