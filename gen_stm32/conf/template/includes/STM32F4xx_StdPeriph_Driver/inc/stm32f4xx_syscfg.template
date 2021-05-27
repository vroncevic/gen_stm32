/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_syscfg.h
 * 
 * This file contains all functions prototypes for SYSCFG firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_syscfg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_syscfg is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_SYSCFG_H
#define __STM32F4xx_SYSCFG_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define EXTI_PortSourceGPIOA ((uint8_t) 0x00)
#define EXTI_PortSourceGPIOB ((uint8_t) 0x01)
#define EXTI_PortSourceGPIOC ((uint8_t) 0x02)
#define EXTI_PortSourceGPIOD ((uint8_t) 0x03)
#define EXTI_PortSourceGPIOE ((uint8_t) 0x04)
#define EXTI_PortSourceGPIOF ((uint8_t) 0x05)
#define EXTI_PortSourceGPIOG ((uint8_t) 0x06)
#define EXTI_PortSourceGPIOH ((uint8_t) 0x07)
#define EXTI_PortSourceGPIOI ((uint8_t) 0x08)
#define EXTI_PinSource0 ((uint8_t) 0x00)
#define EXTI_PinSource1 ((uint8_t) 0x01)
#define EXTI_PinSource2 ((uint8_t) 0x02)
#define EXTI_PinSource3 ((uint8_t) 0x03)
#define EXTI_PinSource4 ((uint8_t) 0x04)
#define EXTI_PinSource5 ((uint8_t) 0x05)
#define EXTI_PinSource6 ((uint8_t) 0x06)
#define EXTI_PinSource7 ((uint8_t) 0x07)
#define EXTI_PinSource8 ((uint8_t) 0x08)
#define EXTI_PinSource9 ((uint8_t) 0x09)
#define EXTI_PinSource10 ((uint8_t) 0x0A)
#define EXTI_PinSource11 ((uint8_t) 0x0B)
#define EXTI_PinSource12 ((uint8_t) 0x0C)
#define EXTI_PinSource13 ((uint8_t) 0x0D)
#define EXTI_PinSource14 ((uint8_t) 0x0E)
#define EXTI_PinSource15 ((uint8_t) 0x0F)
#define SYSCFG_MemoryRemap_Flash ((uint8_t) 0x00)
#define SYSCFG_MemoryRemap_SystemFlash ((uint8_t) 0x01)
#define SYSCFG_MemoryRemap_FSMC ((uint8_t) 0x02)
#define SYSCFG_MemoryRemap_SRAM ((uint8_t) 0x03)
#define SYSCFG_ETH_MediaInterface_MII ((uint32_t) 0x00000000)
#define SYSCFG_ETH_MediaInterface_RMII ((uint32_t) 0x00000001)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) ( \
    ((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOF) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOG) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOH) || \
    ((PORTSOURCE) == EXTI_PortSourceGPIOI) \
)

#define IS_EXTI_PIN_SOURCE(PINSOURCE) ( \
    ((PINSOURCE) == EXTI_PinSource0) || \
    ((PINSOURCE) == EXTI_PinSource1) || \
    ((PINSOURCE) == EXTI_PinSource2) || \
    ((PINSOURCE) == EXTI_PinSource3) || \
    ((PINSOURCE) == EXTI_PinSource4) || \
    ((PINSOURCE) == EXTI_PinSource5) || \
    ((PINSOURCE) == EXTI_PinSource6) || \
    ((PINSOURCE) == EXTI_PinSource7) || \
    ((PINSOURCE) == EXTI_PinSource8) || \
    ((PINSOURCE) == EXTI_PinSource9) || \
    ((PINSOURCE) == EXTI_PinSource10) || \
    ((PINSOURCE) == EXTI_PinSource11) || \
    ((PINSOURCE) == EXTI_PinSource12) || \
    ((PINSOURCE) == EXTI_PinSource13) || \
    ((PINSOURCE) == EXTI_PinSource14) || \
    ((PINSOURCE) == EXTI_PinSource15) \
)

#define IS_SYSCFG_MEMORY_REMAP_CONFING(REMAP) ( \
    ((REMAP) == SYSCFG_MemoryRemap_Flash) || \
    ((REMAP) == SYSCFG_MemoryRemap_SystemFlash) || \
    ((REMAP) == SYSCFG_MemoryRemap_SRAM) || \
    ((REMAP) == SYSCFG_MemoryRemap_FSMC) \
)

#define IS_SYSCFG_ETH_MEDIA_INTERFACE(INTERFACE) ( \
    ((INTERFACE) == SYSCFG_ETH_MediaInterface_MII) || \
    ((INTERFACE) == SYSCFG_ETH_MediaInterface_RMII) \
)

void SYSCFG_DeInit(void);
void SYSCFG_MemoryRemapConfig(uint8_t SYSCFG_MemoryRemap);

void SYSCFG_EXTILineConfig(
    uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex
);

void SYSCFG_ETH_MediaInterfaceConfig(uint32_t SYSCFG_ETH_MediaInterface);
void SYSCFG_CompensationCellCmd(FunctionalState NewState);
FlagStatus SYSCFG_GetCompensationCellStatus(void);

#ifdef __cplusplus
    }
#endif

#endif

