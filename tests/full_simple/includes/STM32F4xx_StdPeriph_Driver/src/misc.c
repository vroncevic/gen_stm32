/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * misc.c
 * 
 * This file provides all miscellaneous firmware functions.
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

#include "misc.h"
#include "stm32f4xx_conf.h"

#define AIRCR_VECTKEY_MASK ((uint32_t) 0x05FA0000)

/**
 * Configures priority grouping: pre-emption priority and subpriority.
 * NVIC_PriorityGroup: specifies priority grouping bits length.
 *   This parameter can be one of following values:
 * arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
 *                                4 bits for subpriority
 * arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
 *                                3 bits for subpriority
 * arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
 *                                2 bits for subpriority
 * arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
 *                                1 bits for subpriority
 * arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
 *                                0 bits for subpriority
 * When NVIC_PriorityGroup_0 is selected, IRQ pre-emption is no more possible.
 * The pending IRQ priority will be managed only by subpriority.
 * return None
 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup) {
    /* Check parameters */
    assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));
    /* Set PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
 * Initializes NVIC peripheral according to specified parameters in
 * NVIC_InitStruct.
 * To configure interrupts priority correctly, NVIC_PriorityGroupConfig()
 * function should be called before.
 * NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
 * configuration information for specified NVIC peripheral.
 * return None
 */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct) {
    uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

    /* Check parameters */
    assert_param(
        IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd)
    );
    assert_param(
        IS_NVIC_PREEMPTION_PRIORITY(
            NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority
        )
    );
    assert_param(
        IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority)
    );
    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE) {
        /* Compute Corresponding IRQ Priority */
        tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700)) >> 0x08;
        tmppre = (0x4 - tmppriority);
        tmpsub = tmpsub >> tmppriority;
        tmppriority = (
            NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre
        );
        tmppriority |= (uint8_t) (
            NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub
        );
        tmppriority = tmppriority << 0x04;
        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
        /* Enable Selected IRQ Channels */
        NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
        (uint32_t) 0x01 << (
            NVIC_InitStruct->NVIC_IRQChannel & (uint8_t) 0x1F
        );
    } else {
        /* Disable Selected IRQ Channels */
        NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
        (uint32_t) 0x01 << (
            NVIC_InitStruct->NVIC_IRQChannel & (uint8_t) 0x1F
        );
    }
}

/**
 * Sets vector table location and Offset.
 * NVIC_VectTab: specifies if vector table is in RAM or FLASH memory.
 * This parameter can be one of following values:
 * arg NVIC_VectTab_RAM: Vector Table in internal SRAM.
 * arg NVIC_VectTab_FLASH: Vector Table in internal FLASH.
 * Offset: Vector Table base offset field. Value must be multiple of 0x200.
 * return None
 */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset) {
    /* Check parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset));
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t) 0x1FFFFF80);
}

/**
 * Selects condition for system to enter low power mode.
 * LowPowerMode: Specifies new mode for system to enter low power mode.
 * This parameter can be one of following values:
 * arg NVIC_LP_SEVONPEND: Low Power SEV on Pend.
 * arg NVIC_LP_SLEEPDEEP: Low Power DEEPSLEEP request.
 * arg NVIC_LP_SLEEPONEXIT: Low Power Sleep on Exit.
 * NewState: new state of LP condition. Parameter can be: ENABLE or DISABLE.
 * return None
 */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState) {
    /* Check parameters */
    assert_param(IS_NVIC_LP(LowPowerMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        SCB->SCR |= LowPowerMode;
    } else {
        SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
    }
}

/**
 * Configures SysTick clock source.
 * SysTick_CLKSource: specifies SysTick clock source.
 * This parameter can be one of following values:
 * arg SysTick_CLKSource_HCLK_Div8: AHB clock divided by 8 selected as
 * SysTick clock source.
 * arg SysTick_CLKSource_HCLK: AHB clock selected as SysTick clock source.
 * return None
 */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource) {
    /* Check parameters */
    assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
    if (SysTick_CLKSource == SysTick_CLKSource_HCLK) {
        SysTick->CTRL |= SysTick_CLKSource_HCLK;
    } else {
        SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
    }
}

