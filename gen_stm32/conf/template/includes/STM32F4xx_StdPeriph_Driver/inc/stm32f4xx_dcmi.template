/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_dcmi.h
 * 
 * This file contains all functions prototypes for DCMI firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_dcmi is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_dcmi is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_DCMI_H
#define __STM32F4xx_DCMI_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    uint16_t DCMI_CaptureMode; /* Specifies Capture Mode: Continuous or
                                  Snapshot. Parameter can be a value of
                                  DCMI_Capture_Mode */
    uint16_t DCMI_SynchroMode; /* Specifies Synchronization Mode: Hardware
                                  or Embedded. Parameter can be a value of
                                  DCMI_Synchronization_Mode */
    uint16_t DCMI_PCKPolarity; /* Specifies Pixel clock polarity: Falling
                                  or Rising. Parameter can be a value of
                                  DCMI_PIXCK_Polarity */
    uint16_t DCMI_VSPolarity; /* Specifies Vertical synchronization polarity:
                                 High or Low. Parameter can be a value of
                                 DCMI_VSYNC_Polarity */
    uint16_t DCMI_HSPolarity; /* Specifies Horizontal synchronization polarity:
                                 High or Low. Parameter can be a value of
                                 DCMI_HSYNC_Polarity */
    uint16_t DCMI_CaptureRate; /* Specifies frequency of frame capture:
                                  All, 1/2 or 1/4. Parameter can be a value
                                  of DCMI_Capture_Rate */
    uint16_t DCMI_ExtendedDataMode; /* Specifies data width: 8-bit, 10-bit,
                                       12-bit or 14-bit. Parameter can be a
                                       value of DCMI_Extended_Data_Mode */
} DCMI_InitTypeDef;

typedef struct {
    uint16_t DCMI_VerticalStartLine; /* Specifies Vertical start line count
                                        from which image capture will start.
                                        Parameter can be a value between
                                        0x00 and 0x1FFF */
    uint16_t DCMI_HorizontalOffsetCount; /* Specifies number of pixel clocks
                                            to count before starting a capture.
                                            Parameter can be a value between
                                            0x00 and 0x3FFF */
    uint16_t DCMI_VerticalLineCount; /* Specifies number of lines to be
                                        captured from starting point.
                                        Parameter can be a value between
                                        0x00 and 0x3FFF */
    uint16_t DCMI_CaptureCount; /* Specifies number of pixel clocks to be
                                   captured from starting point on same line.
                                   Parameter can be a value between 0x00
                                   and 0x3FFF */
} DCMI_CROPInitTypeDef;

typedef struct {
    uint8_t DCMI_FrameStartCode; /* Specifies code of frame start delimiter */
    uint8_t DCMI_LineStartCode; /* Specifies code of line start delimiter.*/
    uint8_t DCMI_LineEndCode; /* Specifies code of line end delimiter.*/
    uint8_t DCMI_FrameEndCode; /* Specifies code of frame end delimiter.*/
} DCMI_CodesInitTypeDef;

/**
 * The received data are transferred continuously into the
 * destination memory through DMA.
 */
#define DCMI_CaptureMode_Continuous ((uint16_t) 0x0000)

/**
 * Once activated, interface waits for start of
 * frame and then transfers a single frame through DMA.
 */
#define DCMI_CaptureMode_SnapShot ((uint16_t) 0x0002)

/**
 * Hardware synchronization data capture (frame/line start/stop)
 * is synchronized with HSYNC/VSYNC signals.
 */
#define DCMI_SynchroMode_Hardware ((uint16_t) 0x0000)

/**
 * Embedded synchronization data capture is synchronized with
 * synchronization codes embedded in data flow.
 */
#define DCMI_SynchroMode_Embedded ((uint16_t) 0x0010)

/* Pixel clock active on Falling edge */
#define DCMI_PCKPolarity_Falling ((uint16_t) 0x0000)

/* Pixel clock active on Rising edge */
#define DCMI_PCKPolarity_Rising ((uint16_t) 0x0020)

/* Vertical synchronization active Low */
#define DCMI_VSPolarity_Low ((uint16_t) 0x0000)

/* Vertical synchronization active High */
#define DCMI_VSPolarity_High ((uint16_t) 0x0080)

/* Horizontal synchronization active Low */
#define DCMI_HSPolarity_Low ((uint16_t) 0x0000)

/* Horizontal synchronization active High */
#define DCMI_HSPolarity_High ((uint16_t) 0x0040)

/* All frames are captured */
#define DCMI_CaptureRate_All_Frame ((uint16_t) 0x0000)

/* Every alternate frame captured */
#define DCMI_CaptureRate_1of2_Frame ((uint16_t) 0x0100)

/* One frame in 4 frames captured */
#define DCMI_CaptureRate_1of4_Frame ((uint16_t) 0x0200)

/* Interface captures 8-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_8b ((uint16_t) 0x0000)

/* Interface captures 10-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_10b ((uint16_t) 0x0400)

/* Interface captures 12-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_12b ((uint16_t) 0x0800)

/* Interface captures 14-bit data on every pixel clock */
#define DCMI_ExtendedDataMode_14b ((uint16_t) 0x0C00)

#define DCMI_IT_FRAME ((uint16_t) 0x0001)
#define DCMI_IT_OVF ((uint16_t) 0x0002)
#define DCMI_IT_ERR ((uint16_t) 0x0004)
#define DCMI_IT_VSYNC ((uint16_t) 0x0008)
#define DCMI_IT_LINE ((uint16_t) 0x0010)
#define DCMI_FLAG_HSYNC ((uint16_t) 0x2001)
#define DCMI_FLAG_VSYNC ((uint16_t) 0x2002)
#define DCMI_FLAG_FNE ((uint16_t) 0x2004)
#define DCMI_FLAG_FRAMERI ((uint16_t) 0x0001)
#define DCMI_FLAG_OVFRI ((uint16_t) 0x0002)
#define DCMI_FLAG_ERRRI ((uint16_t) 0x0004)
#define DCMI_FLAG_VSYNCRI ((uint16_t) 0x0008)
#define DCMI_FLAG_LINERI ((uint16_t) 0x0010)
#define DCMI_FLAG_FRAMEMI ((uint16_t) 0x1001)
#define DCMI_FLAG_OVFMI ((uint16_t) 0x1002)
#define DCMI_FLAG_ERRMI ((uint16_t) 0x1004)
#define DCMI_FLAG_VSYNCMI ((uint16_t) 0x1008)
#define DCMI_FLAG_LINEMI ((uint16_t) 0x1010)

#define IS_DCMI_CAPTURE_MODE(MODE) ( \
    ((MODE) == DCMI_CaptureMode_Continuous) || \
    ((MODE) == DCMI_CaptureMode_SnapShot) \
)

#define IS_DCMI_SYNCHRO(MODE) ( \
    ((MODE) == DCMI_SynchroMode_Hardware) || \
    ((MODE) == DCMI_SynchroMode_Embedded) \
)

#define IS_DCMI_PCKPOLARITY(POLARITY) ( \
    ((POLARITY) == DCMI_PCKPolarity_Falling) || \
    ((POLARITY) == DCMI_PCKPolarity_Rising) \
)

#define IS_DCMI_VSPOLARITY(POLARITY) ( \
    ((POLARITY) == DCMI_VSPolarity_Low) || \
    ((POLARITY) == DCMI_VSPolarity_High) \
)

#define IS_DCMI_HSPOLARITY(POLARITY) ( \
    ((POLARITY) == DCMI_HSPolarity_Low) || \
    ((POLARITY) == DCMI_HSPolarity_High) \
)

#define IS_DCMI_CAPTURE_RATE(RATE) ( \
    ((RATE) == DCMI_CaptureRate_All_Frame) || \
    ((RATE) == DCMI_CaptureRate_1of2_Frame) ||\
    ((RATE) == DCMI_CaptureRate_1of4_Frame) \
)

#define IS_DCMI_EXTENDED_DATA(DATA) ( \
    ((DATA) == DCMI_ExtendedDataMode_8b) || \
    ((DATA) == DCMI_ExtendedDataMode_10b) ||\
    ((DATA) == DCMI_ExtendedDataMode_12b) ||\
    ((DATA) == DCMI_ExtendedDataMode_14b) \
)

#define IS_DCMI_CONFIG_IT(IT) ( \
    (((IT) & (uint16_t)0xFFE0) == 0x0000) && ((IT) != 0x0000) \
)

#define IS_DCMI_GET_IT(IT) ( \
    ((IT) == DCMI_IT_FRAME) || \
    ((IT) == DCMI_IT_OVF) || \
    ((IT) == DCMI_IT_ERR) || \
    ((IT) == DCMI_IT_VSYNC) || \
    ((IT) == DCMI_IT_LINE) \
)

#define IS_DCMI_GET_FLAG(FLAG) ( \
    ((FLAG) == DCMI_FLAG_HSYNC) || \
    ((FLAG) == DCMI_FLAG_VSYNC) || \
    ((FLAG) == DCMI_FLAG_FNE) || \
    ((FLAG) == DCMI_FLAG_FRAMERI) || \
    ((FLAG) == DCMI_FLAG_OVFRI) || \
    ((FLAG) == DCMI_FLAG_ERRRI) || \
    ((FLAG) == DCMI_FLAG_VSYNCRI) || \
    ((FLAG) == DCMI_FLAG_LINERI) || \
    ((FLAG) == DCMI_FLAG_FRAMEMI) || \
    ((FLAG) == DCMI_FLAG_OVFMI) || \
    ((FLAG) == DCMI_FLAG_ERRMI) || \
    ((FLAG) == DCMI_FLAG_VSYNCMI) || \
    ((FLAG) == DCMI_FLAG_LINEMI) \
)

#define IS_DCMI_CLEAR_FLAG(FLAG) ( \
    (((FLAG) & (uint16_t)0xFFE0) == 0x0000) && ((FLAG) != 0x0000) \
)

void DCMI_DeInit(void);
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct);
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct);
void DCMI_CROPConfig(DCMI_CROPInitTypeDef* DCMI_CROPInitStruct);
void DCMI_CROPCmd(FunctionalState NewState);
void DCMI_SetEmbeddedSynchroCodes(DCMI_CodesInitTypeDef* DCMI_CodesInitStruct);
void DCMI_JPEGCmd(FunctionalState NewState);
void DCMI_Cmd(FunctionalState NewState);
void DCMI_CaptureCmd(FunctionalState NewState);
uint32_t DCMI_ReadData(void);
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState);
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG);
void DCMI_ClearFlag(uint16_t DCMI_FLAG);
ITStatus DCMI_GetITStatus(uint16_t DCMI_IT);
void DCMI_ClearITPendingBit(uint16_t DCMI_IT);

#ifdef __cplusplus
    }
#endif

#endif

