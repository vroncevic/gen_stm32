/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_syscfg.c
 * 
 * This file provides firmware functions to manage the SYSCFG peripheral.
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

#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* RCC registers bit address in the alias region */
#define SYSCFG_OFFSET (SYSCFG_BASE - PERIPH_BASE)

/* Alias word address of MII_RMII_SEL bit */
#define PMC_OFFSET (SYSCFG_OFFSET + 0x04)
#define MII_RMII_SEL_BitNumber ((uint8_t) 0x17)

#define PMC_MII_RMII_SEL_BB ( \
    PERIPH_BB_BASE + (PMC_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4) \
)

/* CMPCR Register */
/* Alias word address of CMP_PD bit */
#define CMPCR_OFFSET (SYSCFG_OFFSET + 0x20)
#define CMP_PD_BitNumber ((uint8_t) 0x00)

#define CMPCR_CMP_PD_BB ( \
    PERIPH_BB_BASE + (CMPCR_OFFSET * 32) + (CMP_PD_BitNumber * 4) \
)

/**
 * Deinitializes the Alternate Functions (remap and EXTI configuration)
 * registers to their default reset values.
 * param None
 * retval None
 */
void SYSCFG_DeInit(void) {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, DISABLE);
}

/**
 * Changes the mapping of the specified pin.
 * paramSYSCFG_Memory: selects the memory remapping.
 *   This parameter can be one of the following values:
 *     arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000
 *     arg SYSCFG_MemoryRemap_SystemFlash: System Flash memory mapped at
           0x00000000
 *     arg SYSCFG_MemoryRemap_FSMC: FSMC (Bank1 (NOR/PSRAM 1 and 2) mapped at
           0x00000000
 *     arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM (112kB) mapped at 0x00000000
 * retval None
 */
void SYSCFG_MemoryRemapConfig(uint8_t SYSCFG_MemoryRemap) {
    /* Check the parameters */
    assert_param(IS_SYSCFG_MEMORY_REMAP_CONFING(SYSCFG_MemoryRemap));
    SYSCFG->MEMRMP = SYSCFG_MemoryRemap;
}

/**
 * Selects the GPIO pin used as EXTI Line.
 * paramEXTI_PortSourceGPIOx : selects the GPIO port to be used as source for
 *          EXTI lines where x can be (A..I).
 * paramEXTI_PinSourcex: specifies the EXTI line to be configured.
 *           Parameter can be EXTI_PinSourcex where x can be (0..15, except
 *           for EXTI_PortSourceGPIOI x can be (0..11).
 * retval None
 */
void SYSCFG_EXTILineConfig(
    uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex
) {
    uint32_t tmp = 0x00;

    /* Check the parameters */
    assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
    assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));
    tmp = ((uint32_t) 0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t) 0x03));
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (
        ((uint32_t) EXTI_PortSourceGPIOx) <<
        (0x04 * (EXTI_PinSourcex & (uint8_t) 0x03))
    );
}

/**
 * Selects the ETHERNET media interface
 * paramSYSCFG_ETH_MediaInterface: specifies the Media Interface mode.
 *          This parameter can be one of the following values: 
 *            arg SYSCFG_ETH_MediaInterface_MII: MII mode selected
 *            arg SYSCFG_ETH_MediaInterface_RMII: RMII mode selected 
 * retval None
 */
void SYSCFG_ETH_MediaInterfaceConfig(uint32_t SYSCFG_ETH_MediaInterface) {
    assert_param(IS_SYSCFG_ETH_MEDIA_INTERFACE(SYSCFG_ETH_MediaInterface));
    /* Configure MII_RMII selection bit */ 
    *(__IO uint32_t *) PMC_MII_RMII_SEL_BB = SYSCFG_ETH_MediaInterface;
}

/**
 * Enables or disables the I/O Compensation Cell.
 * The I/O compensation cell can be used only when the device supply
 *         voltage ranges from 2.4 to 3.6 V.
 * paramNewState: new state of the I/O Compensation Cell.
 *          This parameter can be one of the following values:
 *            arg ENABLE: I/O compensation cell enabled
 *            arg DISABLE: I/O compensation cell power-down mode
 * retval None
 */
void SYSCFG_CompensationCellCmd(FunctionalState NewState) {
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
   *(__IO uint32_t *) CMPCR_CMP_PD_BB = (uint32_t) NewState;
}

/**
 * Checks whether the I/O Compensation Cell ready flag is set or not.
 * param None
 * retval The new state of the I/O Compensation Cell ready flag (SET or RESET)
 */
FlagStatus SYSCFG_GetCompensationCellStatus(void) {
    FlagStatus bitstatus = RESET;

    if ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY ) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

