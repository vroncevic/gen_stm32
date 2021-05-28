/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_dac.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Digital-to-Analog Converter (DAC) peripheral:
 *     - DAC channels configuration: trigger, output buffer, data format
 *     - DMA management
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_dac is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_dac is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_dac.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* CR register Mask */
#define CR_CLEAR_MASK ((uint32_t) 0x00000FFE)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_SET ((uint32_t) 0x00000003)
#define DUAL_SWTRIG_RESET ((uint32_t) 0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_OFFSET ((uint32_t) 0x00000008)
#define DHR12R2_OFFSET ((uint32_t) 0x00000014)
#define DHR12RD_OFFSET ((uint32_t) 0x00000020)

/* DOR register offset */
#define DOR_OFFSET ((uint32_t) 0x0000002C)

/**
 * Deinitializes DAC peripheral registers to their default reset values.
 * param None
 * retval None
 */
void DAC_DeInit(void) {
    /* Enable DAC reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
    /* Release DAC from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/**
 * Initializes DAC peripheral according to specified parameters
 * in DAC_InitStruct.
 * param DAC_Channel: selected DAC channel. 
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_InitStruct: pointer to a DAC_InitTypeDef structure that contains
 *       configuration information for  specified DAC channel.
 * retval None
 */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0;

    assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
    assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
    assert_param(
        IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(
            DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude
        )
    );
    assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));

    tmpreg1 = DAC->CR; /* Get DAC CR value */
    /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
    tmpreg1 &= ~(CR_CLEAR_MASK << DAC_Channel);
    /**
     * Configure for selected DAC channel: buffer output, trigger,
     * wave generation, mask/amplitude for wave generation 
     */
    /* Set TSELx and TENx bits according to DAC_Trigger value */
    /* Set WAVEx bits according to DAC_WaveGeneration value */
    /* Set MAMPx bits according to DAC_LFSRUnmask_TriangleAmplitude value */
    /* Set BOFFx bit according to DAC_OutputBuffer value */
    tmpreg2 = (
        DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
        DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude |
        DAC_InitStruct->DAC_OutputBuffer
    );
    /* Calculate CR register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2 << DAC_Channel;
    DAC->CR = tmpreg1; /* Write to DAC CR */
}

/**
 * Fills each DAC_InitStruct member with its default value.
 * param DAC_InitStruct: pointer to a DAC_InitTypeDef structure which will
 *       be initialized.
 * retval None
 */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct) {
    /* Initialize DAC_Trigger member */
    DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
    /* Initialize DAC_WaveGeneration member */
    DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
    /* Initialize DAC_LFSRUnmask_TriangleAmplitude member */
    DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    /* Initialize DAC_OutputBuffer member */
    DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
 * Enables or disables specified DAC channel.
 * param DAC_Channel: The selected DAC channel. 
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param NewState: new state of DAC channel. 
 *   This parameter can be: ENABLE or DISABLE.
 * When DAC channel is enabled trigger source can no more be modified.
 * retval None
 */
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected DAC channel */
        DAC->CR |= (DAC_CR_EN1 << DAC_Channel);
    } else {
        /* Disable selected DAC channel */
        DAC->CR &= (~(DAC_CR_EN1 << DAC_Channel));
    }
}

/**
 * Enables or disables selected DAC channel software trigger.
 * param DAC_Channel: The selected DAC channel. 
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param NewState: new state of selected DAC channel software trigger.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable software trigger for selected DAC channel */
        DAC->SWTRIGR |= (uint32_t) DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4);
    } else {
        /* Disable software trigger for selected DAC channel */
        DAC->SWTRIGR &= ~(
            (uint32_t) DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4)
        );
    }
}

/**
 * Enables or disables simultaneously two DAC channels software triggers.
 * param NewState: new state of DAC channels software triggers.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable software trigger for both DAC channels */
        DAC->SWTRIGR |= DUAL_SWTRIG_SET;
    } else {
        /* Disable software trigger for both DAC channels */
        DAC->SWTRIGR &= DUAL_SWTRIG_RESET;
    }
}

/**
 * Enables or disables selected DAC channel wave generation.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_Wave: specifies wave type to enable or disable.
 *   This parameter can be one of following values:
 *       arg DAC_Wave_Noise: noise wave generation
 *       arg DAC_Wave_Triangle: triangle wave generation
 * param NewState: new state of selected DAC channel wave generation.
 *   This parameter can be: ENABLE or DISABLE.  
 * retval None
 */
void DAC_WaveGenerationCmd(
    uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState
) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_WAVE(DAC_Wave)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected wave generation for selected DAC channel */
        DAC->CR |= DAC_Wave << DAC_Channel;
    } else {
        /* Disable selected wave generation for selected DAC channel */
        DAC->CR &= ~(DAC_Wave << DAC_Channel);
    }
}

/**
 * Set specified data holding register value for DAC channel1.
 * param DAC_Align: Specifies data alignment for DAC channel1.
 *   This parameter can be one of following values:
 *       arg DAC_Align_8b_R: 8bit right data alignment selected
 *       arg DAC_Align_12b_L: 12bit left data alignment selected
 *       arg DAC_Align_12b_R: 12bit right data alignment selected
 * param Data: Data to be loaded in selected data holding register.
 * retval None
 */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data) {
    __IO uint32_t tmp = 0;

    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));
    tmp = (uint32_t) DAC_BASE;
    tmp += DHR12R1_OFFSET + DAC_Align;
    /* Set DAC channel1 selected data holding register */
    *(__IO uint32_t *) tmp = Data;
}

/**
 * Set specified data holding register value for DAC channel2.
 * param DAC_Align: Specifies data alignment for DAC channel2.
 *   This parameter can be one of following values:
 *       arg DAC_Align_8b_R: 8bit right data alignment selected
 *       arg DAC_Align_12b_L: 12bit left data alignment selected
 *       arg DAC_Align_12b_R: 12bit right data alignment selected
 * param Data: Data to be loaded in selected data holding register.
 * retval None
 */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data) {
    __IO uint32_t tmp = 0;

    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));
    tmp = (uint32_t) DAC_BASE;
    tmp += DHR12R2_OFFSET + DAC_Align;
    /* Set DAC channel2 selected data holding register */
    *(__IO uint32_t *) tmp = Data;
}

/**
 * Set specified data holding register value for dual channel DAC.
 * param DAC_Align: Specifies data alignment for dual channel DAC.
 *   This parameter can be one of following values:
 *       arg DAC_Align_8b_R: 8bit right data alignment selected
 *       arg DAC_Align_12b_L: 12bit left data alignment selected
 *       arg DAC_Align_12b_R: 12bit right data alignment selected
 * param Data2: Data for DAC Channel2 to be loaded in selected data
 *       holding register.
 * param Data1: Data for DAC Channel1 to be loaded in selected data
 *       holding register.
 * In dual mode, a unique register access is required to write in both
 * DAC channels at same time.
 * retval None
 */
void DAC_SetDualChannelData(
    uint32_t DAC_Align, uint16_t Data2, uint16_t Data1
) {
    uint32_t data = 0, tmp = 0;

    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data1));
    assert_param(IS_DAC_DATA(Data2));
    /* Calculate and set dual DAC data holding register value */
    if (DAC_Align == DAC_Align_8b_R) {
        data = ((uint32_t) Data2 << 8) | Data1;
    } else {
        data = ((uint32_t) Data2 << 16) | Data1;
    }
    tmp = (uint32_t) DAC_BASE;
    tmp += DHR12RD_OFFSET + DAC_Align;
    /* Set dual DAC selected data holding register */
    *(__IO uint32_t *) tmp = data;
}

/**
 * Returns last data output value of selected DAC channel.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * retval The selected DAC channel data output value.
 */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel) {
    __IO uint32_t tmp = 0;

    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    tmp = (uint32_t) DAC_BASE ;
    tmp += DOR_OFFSET + ((uint32_t) DAC_Channel >> 2);
    /* Returns DAC channel data output register value */
    return (uint16_t) (*(__IO uint32_t*) tmp);
}

/**
 * Enables or disables specified DAC channel DMA request.
 * When enabled DMA1 is generated when an external trigger (EXTI Line9,
 * TIM2, TIM4, TIM5, TIM6, TIM7 or TIM8  but not a software trigger) occurs.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param NewState: new state of selected DAC channel DMA request.
 *   This parameter can be: ENABLE or DISABLE.
 * The DAC channel1 is mapped on DMA1 Stream 5 channel7 which must be
 * already configured.
 * The DAC channel2 is mapped on DMA1 Stream 6 channel7 which must be
 * already configured.
 * retval None
 */
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected DAC channel DMA request */
        DAC->CR |= (DAC_CR_DMAEN1 << DAC_Channel);
    } else {
        /* Disable selected DAC channel DMA request */
        DAC->CR &= (~(DAC_CR_DMAEN1 << DAC_Channel));
    }
}

/**
 * Enables or disables specified DAC interrupts.
 * param DAC_Channel: The selected DAC channel. 
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_IT: specifies DAC interrupt sources to be enabled or disabled.
 *   This parameter can be following values:
 *       arg DAC_IT_DMAUDR: DMA underrun interrupt mask
 * The DMA underrun occurs when a second external trigger arrives before
 * acknowledgement for first external trigger is received (first request).
 * param NewState: new state of specified DAC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DAC_ITConfig(
    uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState
) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_DAC_IT(DAC_IT));
    if (NewState != DISABLE) {
        DAC->CR |=  (DAC_IT << DAC_Channel); /* Enable selected DAC interr */
    } else {
        /* Disable selected DAC interrupts */
        DAC->CR &= (~(uint32_t) (DAC_IT << DAC_Channel));
    }
}

/**
 * Checks whether specified DAC flag is set or not.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_FLAG: specifies flag to check. 
 *   This parameter can be only of following value:
 *       arg DAC_FLAG_DMAUDR: DMA underrun flag
 * The DMA underrun occurs when a second external trigger arrives before
 * acknowledgement for first external trigger is received (first request).
 * retval The new state of DAC_FLAG (SET or RESET).
 */
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_FLAG(DAC_FLAG));
    /* Check status of specified DAC flag */
    if ((DAC->SR & (DAC_FLAG << DAC_Channel)) != (uint8_t) RESET) {
        bitstatus = SET; /* DAC_FLAG is set */
    } else {
        bitstatus = RESET; /* DAC_FLAG is reset */
    }
    return  bitstatus; /* Return DAC_FLAG status */
}

/**
 * Clears DAC channel's pending flags.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_FLAG: specifies flag to clear.
 *   This parameter can be of following value:
 *       arg DAC_FLAG_DMAUDR: DMA underrun flag
 * The DMA underrun occurs when a second external trigger arrives before
 * acknowledgement for first external trigger is received (first request).
 * retval None
 */
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_FLAG(DAC_FLAG));
    DAC->SR = (DAC_FLAG << DAC_Channel); /* Clear selected DAC flags */
}

/**
 * Checks whether specified DAC interrupt has occurred or not.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_IT: specifies DAC interrupt source to check. 
 *   This parameter can be following values:
 *       arg DAC_IT_DMAUDR: DMA underrun interrupt mask
 * The DMA underrun occurs when a second external trigger arrives before
 * acknowledgement for first external trigger is received (first request).
 * retval The new state of DAC_IT (SET or RESET).
 */
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_IT(DAC_IT));
    /* Get DAC_IT enable bit status */
    enablestatus = (DAC->CR & (DAC_IT << DAC_Channel)) ;
    /* Check status of specified DAC interrupt */
    if (
        ((DAC->SR & (DAC_IT << DAC_Channel)) != (uint32_t) RESET) &&
        enablestatus
    ) {
        bitstatus = SET; /* DAC_IT is set */
    } else {
        bitstatus = RESET; /* DAC_IT is reset */
    }
    return bitstatus; /* Return DAC_IT status */
}

/**
 * Clears DAC channel's interrupt pending bits.
 * param DAC_Channel: The selected DAC channel.
 *   This parameter can be one of following values:
 *       arg DAC_Channel_1: DAC Channel1 selected
 *       arg DAC_Channel_2: DAC Channel2 selected
 * param DAC_IT: specifies DAC interrupt pending bit to clear.
 *   This parameter can be following values:
 *       arg DAC_IT_DMAUDR: DMA underrun interrupt mask
 * The DMA underrun occurs when a second external trigger arrives before
 * acknowledgement for first external trigger is received (first request).
 * retval None
 */
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT) {
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_IT(DAC_IT)); 
    /* Clear selected DAC interrupt pending bits */
    DAC->SR = (DAC_IT << DAC_Channel);
}

