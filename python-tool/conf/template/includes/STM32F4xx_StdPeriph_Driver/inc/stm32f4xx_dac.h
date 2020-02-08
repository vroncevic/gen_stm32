/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_dac.h
 * 
 * This file contains all the functions prototypes for the DAC
 * firmware library.
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

#ifndef __STM32F4xx_DAC_H
#define __STM32F4xx_DAC_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    uint32_t DAC_Trigger; /* Specifies the external trigger for the selected
                             DAC channel. Parameter can be a value of
                             DAC_trigger_selection. */
    uint32_t DAC_WaveGeneration; /* Specifies whether DAC channel noise waves
                                    or triangle waves are generated, or
                                    whether no wave is generated. Parameter
                                    can be a value of DAC_wave_generation */
    uint32_t DAC_LFSRUnmask_TriangleAmplitude; /* Specifies the LFSR mask for
                                                  noise wave generation or
                                                  the maximum amplitude 
                                                  triangle generation for DAC
                                                  channel. Parameter can be a
                                                  value */
    uint32_t DAC_OutputBuffer; /* Specifies whether the DAC channel output
                                  buffer is enabled or disabled. Parameter
                                  can be a value of DAC_output_buffer */
} DAC_InitTypeDef;

/**
 * Conversion is automatic once the DAC1_DHRxxxx register
 * has been loaded, and not by external trigger
 */
#define DAC_Trigger_None ((uint32_t) 0x00000000)

/* TIM2 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_T2_TRGO ((uint32_t) 0x00000024)

/* TIM4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_T4_TRGO ((uint32_t) 0x0000002C)

/* TIM5 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_T5_TRGO ((uint32_t) 0x0000001C)

/* TIM6 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_T6_TRGO ((uint32_t) 0x00000004)

/* TIM7 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_T7_TRGO ((uint32_t) 0x00000014)

/* TIM8 TRGO selected as external conversion trigger for DAC channel */
#define DAC_Trigger_T8_TRGO ((uint32_t) 0x0000000C)

/* EXTI Line9 event selected as external conversion trigger for DAC channel */
#define DAC_Trigger_Ext_IT9 ((uint32_t) 0x00000034)

/* Conversion started by software trigger for DAC channel */
#define DAC_Trigger_Software ((uint32_t) 0x0000003C)
#define DAC_WaveGeneration_None ((uint32_t) 0x00000000)
#define DAC_WaveGeneration_Noise ((uint32_t) 0x00000040)
#define DAC_WaveGeneration_Triangle ((uint32_t) 0x00000080)

/* Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUnmask_Bit0 ((uint32_t) 0x00000000)

/* Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits1_0 ((uint32_t) 0x00000100)

/* Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits2_0 ((uint32_t) 0x00000200)

/* Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits3_0 ((uint32_t) 0x00000300)

/* Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits4_0 ((uint32_t) 0x00000400)

/* Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits5_0 ((uint32_t) 0x00000500)

/* Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits6_0 ((uint32_t) 0x00000600)

/* Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits7_0 ((uint32_t) 0x00000700)

/* Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits8_0 ((uint32_t) 0x00000800)

/* Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits9_0 ((uint32_t) 0x00000900)

/* Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits10_0 ((uint32_t) 0x00000A00)

/* Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits11_0 ((uint32_t) 0x00000B00)

/* Select max triangle amplitude of 1 */
#define DAC_TriangleAmplitude_1 ((uint32_t) 0x00000000)

/* Select max triangle amplitude of 3 */
#define DAC_TriangleAmplitude_3 ((uint32_t) 0x00000100)

/* Select max triangle amplitude of 7 */
#define DAC_TriangleAmplitude_7 ((uint32_t) 0x00000200)

/* Select max triangle amplitude of 15 */
#define DAC_TriangleAmplitude_15 ((uint32_t) 0x00000300)

/* Select max triangle amplitude of 31 */
#define DAC_TriangleAmplitude_31 ((uint32_t) 0x00000400)

/* Select max triangle amplitude of 63 */
#define DAC_TriangleAmplitude_63 ((uint32_t) 0x00000500)

/* Select max triangle amplitude of 127 */
#define DAC_TriangleAmplitude_127 ((uint32_t) 0x00000600)

/* Select max triangle amplitude of 255 */
#define DAC_TriangleAmplitude_255 ((uint32_t) 0x00000700)

/* Select max triangle amplitude of 511 */
#define DAC_TriangleAmplitude_511 ((uint32_t) 0x00000800)

/* Select max triangle amplitude of 1023 */
#define DAC_TriangleAmplitude_1023 ((uint32_t) 0x00000900)

/* Select max triangle amplitude of 2047 */
#define DAC_TriangleAmplitude_2047 ((uint32_t) 0x00000A00)

/* Select max triangle amplitude of 4095 */
#define DAC_TriangleAmplitude_4095 ((uint32_t) 0x00000B00)
#define DAC_OutputBuffer_Enable ((uint32_t) 0x00000000)
#define DAC_OutputBuffer_Disable ((uint32_t) 0x00000002)
#define DAC_Channel_1 ((uint32_t) 0x00000000)
#define DAC_Channel_2 ((uint32_t) 0x00000010)
#define DAC_Align_12b_R ((uint32_t) 0x00000000)
#define DAC_Align_12b_L ((uint32_t) 0x00000004)
#define DAC_Align_8b_R ((uint32_t) 0x00000008)
#define DAC_Wave_Noise ((uint32_t) 0x00000040)
#define DAC_Wave_Triangle ((uint32_t) 0x00000080)
#define DAC_IT_DMAUDR ((uint32_t) 0x00002000)
#define DAC_FLAG_DMAUDR ((uint32_t) 0x00002000)

#define IS_DAC_TRIGGER(TRIGGER) ( \
    ((TRIGGER) == DAC_Trigger_None) || \
    ((TRIGGER) == DAC_Trigger_T6_TRGO) || \
    ((TRIGGER) == DAC_Trigger_T8_TRGO) || \
    ((TRIGGER) == DAC_Trigger_T7_TRGO) || \
    ((TRIGGER) == DAC_Trigger_T5_TRGO) || \
    ((TRIGGER) == DAC_Trigger_T2_TRGO) || \
    ((TRIGGER) == DAC_Trigger_T4_TRGO) || \
    ((TRIGGER) == DAC_Trigger_Ext_IT9) || \
    ((TRIGGER) == DAC_Trigger_Software) \
)

#define IS_DAC_GENERATE_WAVE(WAVE) ( \
    ((WAVE) == DAC_WaveGeneration_None) || \
    ((WAVE) == DAC_WaveGeneration_Noise) || \
    ((WAVE) == DAC_WaveGeneration_Triangle) \
)

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) ( \
    ((VALUE) == DAC_LFSRUnmask_Bit0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits1_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits2_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits3_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits4_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits5_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits6_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits7_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits8_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits9_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits10_0) || \
    ((VALUE) == DAC_LFSRUnmask_Bits11_0) || \
    ((VALUE) == DAC_TriangleAmplitude_1) || \
    ((VALUE) == DAC_TriangleAmplitude_3) || \
    ((VALUE) == DAC_TriangleAmplitude_7) || \
    ((VALUE) == DAC_TriangleAmplitude_15) || \
    ((VALUE) == DAC_TriangleAmplitude_31) || \
    ((VALUE) == DAC_TriangleAmplitude_63) || \
    ((VALUE) == DAC_TriangleAmplitude_127) || \
    ((VALUE) == DAC_TriangleAmplitude_255) || \
    ((VALUE) == DAC_TriangleAmplitude_511) || \
    ((VALUE) == DAC_TriangleAmplitude_1023) || \
    ((VALUE) == DAC_TriangleAmplitude_2047) || \
    ((VALUE) == DAC_TriangleAmplitude_4095) \
)

#define IS_DAC_OUTPUT_BUFFER_STATE(STATE) ( \
    ((STATE) == DAC_OutputBuffer_Enable) || \
    ((STATE) == DAC_OutputBuffer_Disable) \
)

#define IS_DAC_CHANNEL(CHANNEL) ( \
    ((CHANNEL) == DAC_Channel_1) || \
    ((CHANNEL) == DAC_Channel_2) \
)

#define IS_DAC_ALIGN(ALIGN) ( \
    ((ALIGN) == DAC_Align_12b_R) || \
    ((ALIGN) == DAC_Align_12b_L) || \
    ((ALIGN) == DAC_Align_8b_R) \
)

#define IS_DAC_WAVE(WAVE) ( \
    ((WAVE) == DAC_Wave_Noise) || \
    ((WAVE) == DAC_Wave_Triangle) \
)

#define IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0)
#define IS_DAC_IT(IT) (((IT) == DAC_IT_DMAUDR))
#define IS_DAC_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))

void DAC_DeInit(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);

void DAC_WaveGenerationCmd(
    uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState
);

void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);

void DAC_SetDualChannelData(
    uint32_t DAC_Align, uint16_t Data2, uint16_t Data1
);

uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);

void DAC_ITConfig(
    uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState
);

FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG);
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG);
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT);
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT);

#ifdef __cplusplus
    }
#endif

#endif

