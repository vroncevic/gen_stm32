/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_dcmi.c
 * 
 * This file provides firmware functions to manage following 
 * functionalities of DCMI peripheral:
 *     - Initialization and Configuration
 *     - Image capture functions
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_dcmi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_dcmi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/**
 * Deinitializes DCMI registers to their default reset values.
 * param None
 * retval None
 */
void DCMI_DeInit(void) {
    DCMI->CR = 0x0;
    DCMI->IER = 0x0;
    DCMI->ICR = 0x1F;
    DCMI->ESCR = 0x0;
    DCMI->ESUR = 0x0;
    DCMI->CWSTRTR = 0x0;
    DCMI->CWSIZER = 0x0;
}

/**
 * Initializes DCMI according to specified parameters in DCMI_InitStruct.
 * param DCMI_InitStruct: pointer to a DCMI_InitTypeDef structure that contains
 *       configuration information for DCMI.
 * retval None
 */
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct) {
    uint32_t temp = 0x0;

    assert_param(IS_DCMI_CAPTURE_MODE(DCMI_InitStruct->DCMI_CaptureMode));
    assert_param(IS_DCMI_SYNCHRO(DCMI_InitStruct->DCMI_SynchroMode));
    assert_param(IS_DCMI_PCKPOLARITY(DCMI_InitStruct->DCMI_PCKPolarity));
    assert_param(IS_DCMI_VSPOLARITY(DCMI_InitStruct->DCMI_VSPolarity));
    assert_param(IS_DCMI_HSPOLARITY(DCMI_InitStruct->DCMI_HSPolarity));
    assert_param(IS_DCMI_CAPTURE_RATE(DCMI_InitStruct->DCMI_CaptureRate));
    assert_param(
        IS_DCMI_EXTENDED_DATA(DCMI_InitStruct->DCMI_ExtendedDataMode)
    );
    /**
     * The DCMI configuration registers should be programmed correctly before
     * enabling CR_ENABLE Bit and CR_CAPTURE Bit 
     */
    DCMI->CR &= ~(DCMI_CR_ENABLE | DCMI_CR_CAPTURE);
    /* Reset old DCMI configuration */
    temp = DCMI->CR;
    temp &= ~(
        (uint32_t) DCMI_CR_CM | DCMI_CR_ESS | DCMI_CR_PCKPOL |
                   DCMI_CR_HSPOL | DCMI_CR_VSPOL | DCMI_CR_FCRC_0 |
                   DCMI_CR_FCRC_1 | DCMI_CR_EDM_0 | DCMI_CR_EDM_1
    );
    /* Sets new configuration of DCMI peripheral */
    temp |= (
        (uint32_t) DCMI_InitStruct->DCMI_CaptureMode |
                   DCMI_InitStruct->DCMI_SynchroMode |
                   DCMI_InitStruct->DCMI_PCKPolarity |
                   DCMI_InitStruct->DCMI_VSPolarity |
                   DCMI_InitStruct->DCMI_HSPolarity |
                   DCMI_InitStruct->DCMI_CaptureRate |
                   DCMI_InitStruct->DCMI_ExtendedDataMode
    );
    DCMI->CR = temp;
}

/**
 * Fills each DCMI_InitStruct member with its default value.
 * param DCMI_InitStruct : pointer to a DCMI_InitTypeDef structure which will
 *       be initialized.
 * retval None
 */
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct) {
    /* Set default configuration */
    DCMI_InitStruct->DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
    DCMI_InitStruct->DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
    DCMI_InitStruct->DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
    DCMI_InitStruct->DCMI_VSPolarity = DCMI_VSPolarity_Low;
    DCMI_InitStruct->DCMI_HSPolarity = DCMI_HSPolarity_Low;
    DCMI_InitStruct->DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
    DCMI_InitStruct->DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
}

/**
 * Initializes DCMI peripheral CROP mode according to specified
 * parameters in DCMI_CROPInitStruct.
 * This function should be called before to enable and start DCMI interface.
 * param DCMI_CROPInitStruct:  pointer to a DCMI_CROPInitTypeDef structure
 *       that contains configuration information for DCMI peripheral CROP mode.
 * retval None
 */
void DCMI_CROPConfig(DCMI_CROPInitTypeDef* DCMI_CROPInitStruct) {
    /* Sets CROP window coordinates */
    DCMI->CWSTRTR = (uint32_t) (
        (uint32_t) DCMI_CROPInitStruct->DCMI_HorizontalOffsetCount |
        ((uint32_t) DCMI_CROPInitStruct->DCMI_VerticalStartLine << 16)
    );
    /* Sets CROP window size */
    DCMI->CWSIZER = (uint32_t) (
        DCMI_CROPInitStruct->DCMI_CaptureCount |
        ((uint32_t) DCMI_CROPInitStruct->DCMI_VerticalLineCount << 16)
    );
}

/**
 * Enables or disables DCMI Crop feature.
 * This function should be called before to enable and start DCMI interface.
 * param NewState: new state of DCMI Crop feature. 
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DCMI_CROPCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DCMI->CR |= (uint32_t) DCMI_CR_CROP; /* Enable DCMI Crop feature */
    } else {
        DCMI->CR &= ~(uint32_t) DCMI_CR_CROP; /* Disable DCMI Crop feature */
    }
}

/**
 * Sets embedded synchronization codes
 * param DCMI_CodesInitTypeDef: pointer to a DCMI_CodesInitTypeDef structure
 *       that contains embedded synchronization codes for DCMI peripheral.
 * retval None
 */
void DCMI_SetEmbeddedSynchroCodes(
DCMI_CodesInitTypeDef* DCMI_CodesInitStruct
) {
    DCMI->ESCR = (uint32_t) (
        DCMI_CodesInitStruct->DCMI_FrameStartCode |
        ((uint32_t) DCMI_CodesInitStruct->DCMI_LineStartCode << 8)|
        ((uint32_t) DCMI_CodesInitStruct->DCMI_LineEndCode << 16)|
        ((uint32_t) DCMI_CodesInitStruct->DCMI_FrameEndCode << 24)
    );
}

/**
 * Enables or disables DCMI JPEG format.
 * The Crop and Embedded Synchronization features cannot be used in this mode.
 * param NewState: new state of DCMI JPEG format.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DCMI_JPEGCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DCMI->CR |= (uint32_t) DCMI_CR_JPEG; /* Enable DCMI JPEG format */
    } else {
        DCMI->CR &= ~(uint32_t) DCMI_CR_JPEG; /* Disable DCMI JPEG format */
    }
}

/**
 * Enables or disables DCMI interface.
 * param NewState: new state of DCMI interface.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DCMI_Cmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable DCMI by setting ENABLE bit */
        DCMI->CR |= (uint32_t) DCMI_CR_ENABLE;
    } else {
        /* Disable DCMI by clearing ENABLE bit */
        DCMI->CR &= ~(uint32_t) DCMI_CR_ENABLE;
    }
}

/**
 * Enables or disables DCMI Capture.
 * param NewState: new state of DCMI capture.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DCMI_CaptureCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DCMI->CR |= (uint32_t) DCMI_CR_CAPTURE; /* Enable DCMI Capture */
    } else {
        DCMI->CR &= ~(uint32_t) DCMI_CR_CAPTURE; /* Disable DCMI Capture */
    }
}

/**
 * Reads data stored in DR register.
 * param None 
 * retval Data register value
 */
uint32_t DCMI_ReadData(void) {
    return DCMI->DR;
}

/**
 * Enables or disables DCMI interface interrupts.
 * param DCMI_IT: specifies DCMI interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of following values:
 *       arg DCMI_IT_FRAME: Frame capture complete interrupt mask
 *       arg DCMI_IT_OVF: Overflow interrupt mask
 *       arg DCMI_IT_ERR: Synchronization error interrupt mask
 *       arg DCMI_IT_VSYNC: VSYNC interrupt mask
 *       arg DCMI_IT_LINE: Line interrupt mask
 * param NewState: new state of specified DCMI interrupts.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState) {
    assert_param(IS_DCMI_CONFIG_IT(DCMI_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        DCMI->IER |= DCMI_IT; /* Enable Interrupt sources */
    } else {
        DCMI->IER &= (uint16_t) (~DCMI_IT); /* Disable Interrupt sources */
    }
}

/**
 * Checks whether  DCMI interface flag is set or not.
 * param DCMI_FLAG: specifies flag to check.
 *   This parameter can be one of following values:
 *       arg DCMI_FLAG_FRAMERI: Frame capture complete Raw flag mask
 *       arg DCMI_FLAG_OVFRI: Overflow Raw flag mask
 *       arg DCMI_FLAG_ERRRI: Synchronization error Raw flag mask
 *       arg DCMI_FLAG_VSYNCRI: VSYNC Raw flag mask
 *       arg DCMI_FLAG_LINERI: Line Raw flag mask
 *       arg DCMI_FLAG_FRAMEMI: Frame capture complete Masked flag mask
 *       arg DCMI_FLAG_OVFMI: Overflow Masked flag mask
 *       arg DCMI_FLAG_ERRMI: Synchronization error Masked flag mask
 *       arg DCMI_FLAG_VSYNCMI: VSYNC Masked flag mask
 *       arg DCMI_FLAG_LINEMI: Line Masked flag mask
 *       arg DCMI_FLAG_HSYNC: HSYNC flag mask
 *       arg DCMI_FLAG_VSYNC: VSYNC flag mask
 *       arg DCMI_FLAG_FNE: Fifo not empty flag mask
 * retval The new state of DCMI_FLAG (SET or RESET).
 */
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t dcmireg, tempreg = 0;

    assert_param(IS_DCMI_GET_FLAG(DCMI_FLAG));
    dcmireg = (((uint16_t) DCMI_FLAG) >> 12); /* Get DCMI register index */
    if (dcmireg == 0x01) {
        tempreg= DCMI->RISR;
    } else if (dcmireg == 0x02) {
        tempreg = DCMI->SR;
    } else {
        tempreg = DCMI->MISR;
    }
    if ((tempreg & DCMI_FLAG) != (uint16_t) RESET ) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return  bitstatus; /* Return DCMI_FLAG status */
}

/**
 * Clears DCMI's pending flags.
 * param DCMI_FLAG: specifies flag to clear.
 *   This parameter can be any combination of following values:
 *       arg DCMI_FLAG_FRAMERI: Frame capture complete Raw flag mask
 *       arg DCMI_FLAG_OVFRI: Overflow Raw flag mask
 *       arg DCMI_FLAG_ERRRI: Synchronization error Raw flag mask
 *       arg DCMI_FLAG_VSYNCRI: VSYNC Raw flag mask
 *       arg DCMI_FLAG_LINERI: Line Raw flag mask
 * retval None
 */
void DCMI_ClearFlag(uint16_t DCMI_FLAG) {
    assert_param(IS_DCMI_CLEAR_FLAG(DCMI_FLAG));
    /**
     * Clear flag by writing in ICR register 1 in corresponding
     * Flag position
     */
    DCMI->ICR = DCMI_FLAG;
}

/**
 * Checks whether DCMI interrupt has occurred or not.
 * param DCMI_IT: specifies DCMI interrupt source to check.
 *   This parameter can be one of following values:
 *       arg DCMI_IT_FRAME: Frame capture complete interrupt mask
 *       arg DCMI_IT_OVF: Overflow interrupt mask
 *       arg DCMI_IT_ERR: Synchronization error interrupt mask
 *       arg DCMI_IT_VSYNC: VSYNC interrupt mask
 *       arg DCMI_IT_LINE: Line interrupt mask
 * retval The new state of DCMI_IT (SET or RESET).
 */
ITStatus DCMI_GetITStatus(uint16_t DCMI_IT) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0;

    assert_param(IS_DCMI_GET_IT(DCMI_IT));
    itstatus = DCMI->MISR & DCMI_IT; /* Only masked interrupts are checked */
    if ((itstatus != (uint16_t) RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears DCMI's interrupt pending bits.
 * param DCMI_IT: specifies DCMI interrupt pending bit to clear.
 *   This parameter can be any combination of following values:
 *       arg DCMI_IT_FRAME: Frame capture complete interrupt mask
 *       arg DCMI_IT_OVF: Overflow interrupt mask
 *       arg DCMI_IT_ERR: Synchronization error interrupt mask
 *       arg DCMI_IT_VSYNC: VSYNC interrupt mask
 *       arg DCMI_IT_LINE: Line interrupt mask
 * retval None
 */
void DCMI_ClearITPendingBit(uint16_t DCMI_IT) {
    /**
     * Clear interrupt pending Bit by writing in ICR register 1 in
     * corresponding pending Bit position
     */
    DCMI->ICR = DCMI_IT;
}

