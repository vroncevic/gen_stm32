/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_spi.h
 * 
 * This file contains all functions prototypes for SPI firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_spi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_spi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_SPI_H
#define __STM32F4xx_SPI_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define SPI_CPOL_Low ((uint16_t) 0x0000)
#define SPI_CPOL_High ((uint16_t) 0x0002)
#define SPI_Direction_2Lines_FullDuplex ((uint16_t) 0x0000)
#define SPI_Direction_2Lines_RxOnly ((uint16_t) 0x0400)
#define SPI_Direction_1Line_Rx ((uint16_t) 0x8000)
#define SPI_Direction_1Line_Tx ((uint16_t) 0xC000)
#define SPI_Mode_Master ((uint16_t) 0x0104)
#define SPI_Mode_Slave ((uint16_t) 0x0000)
#define SPI_DataSize_16b ((uint16_t) 0x0800)
#define SPI_DataSize_8b ((uint16_t) 0x0000)
#define SPI_CPHA_1Edge ((uint16_t) 0x0000)
#define SPI_CPHA_2Edge ((uint16_t) 0x0001)
#define SPI_NSS_Soft ((uint16_t) 0x0200)
#define SPI_NSS_Hard ((uint16_t) 0x0000)
#define SPI_BaudRatePrescaler_2 ((uint16_t) 0x0000)
#define SPI_BaudRatePrescaler_4 ((uint16_t) 0x0008)
#define SPI_BaudRatePrescaler_8 ((uint16_t) 0x0010)
#define SPI_BaudRatePrescaler_16 ((uint16_t) 0x0018)
#define SPI_BaudRatePrescaler_32 ((uint16_t) 0x0020)
#define SPI_BaudRatePrescaler_64 ((uint16_t) 0x0028)
#define SPI_BaudRatePrescaler_128 ((uint16_t) 0x0030)
#define SPI_BaudRatePrescaler_256 ((uint16_t) 0x0038)
#define SPI_FirstBit_MSB ((uint16_t) 0x0000)
#define SPI_FirstBit_LSB ((uint16_t) 0x0080)
#define I2S_Mode_SlaveTx ((uint16_t) 0x0000)
#define I2S_Mode_SlaveRx ((uint16_t) 0x0100)
#define I2S_Mode_MasterTx ((uint16_t) 0x0200)
#define I2S_Mode_MasterRx ((uint16_t) 0x0300)
#define I2S_Standard_Phillips ((uint16_t) 0x0000)
#define I2S_Standard_MSB ((uint16_t) 0x0010)
#define I2S_Standard_LSB ((uint16_t) 0x0020)
#define I2S_Standard_PCMShort ((uint16_t) 0x0030)
#define I2S_Standard_PCMLong ((uint16_t) 0x00B0)
#define I2S_DataFormat_16b ((uint16_t) 0x0000)
#define I2S_DataFormat_16bextended ((uint16_t) 0x0001)
#define I2S_DataFormat_24b ((uint16_t) 0x0003)
#define I2S_DataFormat_32b ((uint16_t) 0x0005)
#define I2S_MCLKOutput_Enable ((uint16_t) 0x0200)
#define I2S_MCLKOutput_Disable ((uint16_t) 0x0000)
#define I2S_AudioFreq_192k ((uint32_t) 192000)
#define I2S_AudioFreq_96k ((uint32_t) 96000)
#define I2S_AudioFreq_48k ((uint32_t) 48000)
#define I2S_AudioFreq_44k ((uint32_t) 44100)
#define I2S_AudioFreq_32k ((uint32_t) 32000)
#define I2S_AudioFreq_22k ((uint32_t) 22050)
#define I2S_AudioFreq_16k ((uint32_t) 16000)
#define I2S_AudioFreq_11k ((uint32_t) 11025)
#define I2S_AudioFreq_8k ((uint32_t) 8000)
#define I2S_AudioFreq_Default ((uint32_t) 2)
#define I2S_CPOL_Low ((uint16_t) 0x0000)
#define I2S_CPOL_High ((uint16_t) 0x0008)
#define SPI_I2S_DMAReq_Tx ((uint16_t) 0x0002)
#define SPI_I2S_DMAReq_Rx ((uint16_t) 0x0001)
#define SPI_NSSInternalSoft_Set ((uint16_t) 0x0100)
#define SPI_NSSInternalSoft_Reset ((uint16_t) 0xFEFF)
#define SPI_CRC_Tx ((uint8_t) 0x00)
#define SPI_CRC_Rx ((uint8_t) 0x01)
#define SPI_Direction_Rx ((uint16_t) 0xBFFF)
#define SPI_Direction_Tx ((uint16_t) 0x4000)
#define SPI_I2S_IT_TXE ((uint8_t) 0x71)
#define SPI_I2S_IT_RXNE ((uint8_t) 0x60)
#define SPI_I2S_IT_ERR ((uint8_t) 0x50)
#define I2S_IT_UDR ((uint8_t) 0x53)
#define SPI_I2S_IT_TIFRFE ((uint8_t) 0x58)
#define SPI_I2S_IT_OVR ((uint8_t) 0x56)
#define SPI_IT_MODF ((uint8_t) 0x55)
#define SPI_IT_CRCERR ((uint8_t) 0x54)
#define SPI_I2S_FLAG_RXNE ((uint16_t) 0x0001)
#define SPI_I2S_FLAG_TXE ((uint16_t) 0x0002)
#define I2S_FLAG_CHSIDE ((uint16_t) 0x0004)
#define I2S_FLAG_UDR ((uint16_t) 0x0008)
#define SPI_FLAG_CRCERR ((uint16_t) 0x0010)
#define SPI_FLAG_MODF ((uint16_t) 0x0020)
#define SPI_I2S_FLAG_OVR ((uint16_t) 0x0040)
#define SPI_I2S_FLAG_BSY ((uint16_t) 0x0080)
#define SPI_I2S_FLAG_TIFRFE ((uint16_t) 0x0100)
#define SPI_DMAReq_Tx SPI_I2S_DMAReq_Tx
#define SPI_DMAReq_Rx SPI_I2S_DMAReq_Rx
#define SPI_IT_TXE SPI_I2S_IT_TXE
#define SPI_IT_RXNE SPI_I2S_IT_RXNE
#define SPI_IT_ERR SPI_I2S_IT_ERR
#define SPI_IT_OVR SPI_I2S_IT_OVR
#define SPI_FLAG_RXNE SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE SPI_I2S_FLAG_TXE
#define SPI_FLAG_OVR SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY SPI_I2S_FLAG_BSY
#define SPI_DeInit SPI_I2S_DeInit
#define SPI_ITConfig SPI_I2S_ITConfig
#define SPI_DMACmd SPI_I2S_DMACmd
#define SPI_SendData SPI_I2S_SendData
#define SPI_ReceiveData SPI_I2S_ReceiveData
#define SPI_GetFlagStatus SPI_I2S_GetFlagStatus
#define SPI_ClearFlag SPI_I2S_ClearFlag
#define SPI_GetITStatus SPI_I2S_GetITStatus
#define SPI_ClearITPendingBit SPI_I2S_ClearITPendingBit

typedef struct {
    uint16_t SPI_Direction; /* Specifies SPI unidirectional or bidirectional
                               data mode. Parameter can be a value of
                               SPI_data_direction */
    uint16_t SPI_Mode; /* Specifies SPI operating mode.
                          Parameter can be a value of SPI_mode */
    uint16_t SPI_DataSize; /* Specifies SPI data size.
                              Parameter can be a value of SPI_data_size */
    uint16_t SPI_CPOL; /* Specifies serial clock steady state.
                          Parameter can be a value of SPI_Clock_Polarity */
    uint16_t SPI_CPHA; /* Specifies clock active edge for bit capture.
                          Parameter can be a value of SPI_Clock_Phase */
    uint16_t SPI_NSS; /* Specifies whether NSS signal is managed by
                         hardware (NSS pin) or by software using SSI bit.
                         Parameter can be a value of
                         SPI_Slave_Select_management */
    uint16_t SPI_BaudRatePrescaler; /* Specifies Baud Rate prescaler value
                                       which will be used to configure
                                       transmit and receive SCK clock.
                                       Parameter can be a value of
                                       SPI_BaudRate_Prescaler
                                       The communication clock is derived from
                                       master clock. The slave clock does not
                                       need to be set. */
    uint16_t SPI_FirstBit; /* Specifies whether data transfers start from MSB
                              or LSB bit. Parameter can be a value of
                              SPI_MSB_LSB_transmission */
    /* Specifies polynomial used for CRC calculation. */
    uint16_t SPI_CRCPolynomial;
} SPI_InitTypeDef;

typedef struct {
    uint16_t I2S_Mode; /* Specifies I2S operating mode. Parameter can be a
                          value of I2S_Mode */
    uint16_t I2S_Standard; /* Specifies standard used for I2S communication.
                              Parameter can be a value of I2S_Standard */
    uint16_t I2S_DataFormat; /* Specifies data format for I2S communication.
                                Parameter can be a value of I2S_Data_Format */
    uint16_t I2S_MCLKOutput; /* Specifies whether I2S MCLK output is enabled
                                or not. Parameter can be a value of
                                I2S_MCLK_Output */
    uint32_t I2S_AudioFreq; /* Specifies frequency selected for I2S
                               communication. Parameter can be a value of
                               I2S_Audio_Frequency */
    uint16_t I2S_CPOL; /* Specifies idle state of I2S clock. Parameter can be
                          a value of I2S_Clock_Polarity */
} I2S_InitTypeDef;

#define IS_SPI_ALL_PERIPH(PERIPH) ( \
    ((PERIPH) == SPI1) || ((PERIPH) == SPI2) || ((PERIPH) == SPI3) \
)

#define IS_SPI_ALL_PERIPH_EXT(PERIPH) ( \
    ((PERIPH) == SPI1) || ((PERIPH) == SPI2) || \
    ((PERIPH) == SPI3) || ((PERIPH) == I2S2ext) || \
    ((PERIPH) == I2S3ext) \
)

#define IS_SPI_23_PERIPH(PERIPH) (((PERIPH) == SPI2) || ((PERIPH) == SPI3))

#define IS_SPI_23_PERIPH_EXT(PERIPH) ( \
    ((PERIPH) == SPI2) || ((PERIPH) == SPI3) || \
    ((PERIPH) == I2S2ext) || ((PERIPH) == I2S3ext) \
)

#define IS_I2S_EXT_PERIPH(PERIPH) ( \
    ((PERIPH) == I2S2ext) || ((PERIPH) == I2S3ext) \
)

#define IS_SPI_DIRECTION_MODE(MODE) ( \
    ((MODE) == SPI_Direction_2Lines_FullDuplex) || \
    ((MODE) == SPI_Direction_2Lines_RxOnly) || \
    ((MODE) == SPI_Direction_1Line_Rx) || \
    ((MODE) == SPI_Direction_1Line_Tx) \
)

#define IS_SPI_MODE(MODE) ( \
    ((MODE) == SPI_Mode_Master) || ((MODE) == SPI_Mode_Slave) \
)

#define IS_SPI_DATASIZE(DATASIZE) ( \
    ((DATASIZE) == SPI_DataSize_16b) || ((DATASIZE) == SPI_DataSize_8b) \
)

#define IS_SPI_CPOL(CPOL) ( \
    ((CPOL) == SPI_CPOL_Low) || ((CPOL) == SPI_CPOL_High) \
)

#define IS_SPI_CPHA(CPHA) ( \
    ((CPHA) == SPI_CPHA_1Edge) || ((CPHA) == SPI_CPHA_2Edge) \
)

#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || ((NSS) == SPI_NSS_Hard))

#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) ( \
    ((PRESCALER) == SPI_BaudRatePrescaler_2) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
    ((PRESCALER) == SPI_BaudRatePrescaler_256) \
)

#define IS_SPI_FIRST_BIT(BIT) ( \
    ((BIT) == SPI_FirstBit_MSB) || ((BIT) == SPI_FirstBit_LSB) \
)

#define IS_I2S_MODE(MODE) ( \
    ((MODE) == I2S_Mode_SlaveTx) || ((MODE) == I2S_Mode_SlaveRx) || \
    ((MODE) == I2S_Mode_MasterTx) || ((MODE) == I2S_Mode_MasterRx) \
)

#define IS_I2S_STANDARD(STANDARD) ( \
    ((STANDARD) == I2S_Standard_Phillips) || \
    ((STANDARD) == I2S_Standard_MSB) || \
    ((STANDARD) == I2S_Standard_LSB) || \
    ((STANDARD) == I2S_Standard_PCMShort) || \
    ((STANDARD) == I2S_Standard_PCMLong) \
)

#define IS_I2S_DATA_FORMAT(FORMAT) ( \
    ((FORMAT) == I2S_DataFormat_16b) || \
    ((FORMAT) == I2S_DataFormat_16bextended) || \
    ((FORMAT) == I2S_DataFormat_24b) || \
    ((FORMAT) == I2S_DataFormat_32b) \
)

#define IS_I2S_MCLK_OUTPUT(OUTPUT) ( \
    ((OUTPUT) == I2S_MCLKOutput_Enable) || \
    ((OUTPUT) == I2S_MCLKOutput_Disable) \
)

#define IS_I2S_AUDIO_FREQ(FREQ) ( \
    (((FREQ) >= I2S_AudioFreq_8k) && ((FREQ) <= I2S_AudioFreq_192k)) || \
    ((FREQ) == I2S_AudioFreq_Default) \
)

#define IS_I2S_CPOL(CPOL) ( \
    ((CPOL) == I2S_CPOL_Low) || ((CPOL) == I2S_CPOL_High) \
)

#define IS_SPI_I2S_DMAREQ(DMAREQ) ( \
    (((DMAREQ) & (uint16_t)0xFFFC) == 0x00) && ((DMAREQ) != 0x00) \
)

#define IS_SPI_NSS_INTERNAL(INTERNAL) ( \
    ((INTERNAL) == SPI_NSSInternalSoft_Set) || \
    ((INTERNAL) == SPI_NSSInternalSoft_Reset) \
)

#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))

#define IS_SPI_DIRECTION(DIRECTION) ( \
    ((DIRECTION) == SPI_Direction_Rx) || ((DIRECTION) == SPI_Direction_Tx) \
)

#define IS_SPI_I2S_CONFIG_IT(IT) ( \
    ((IT) == SPI_I2S_IT_TXE) || ((IT) == SPI_I2S_IT_RXNE) || \
    ((IT) == SPI_I2S_IT_ERR) \
)

#define IS_SPI_I2S_CLEAR_IT(IT) (((IT) == SPI_IT_CRCERR))

#define IS_SPI_I2S_GET_IT(IT) ( \
    ((IT) == SPI_I2S_IT_RXNE)|| ((IT) == SPI_I2S_IT_TXE) || \
    ((IT) == SPI_IT_CRCERR)  || ((IT) == SPI_IT_MODF) || \
    ((IT) == SPI_I2S_IT_OVR) || ((IT) == I2S_IT_UDR) || \
    ((IT) == SPI_I2S_IT_TIFRFE) \
)

#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))

#define IS_SPI_I2S_GET_FLAG(FLAG) ( \
    ((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
    ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
    ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
    ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE)|| \
    ((FLAG) == SPI_I2S_FLAG_TIFRFE) \
)

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)

void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);

void SPI_NSSInternalSoftwareConfig(
    SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft
);

void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);

void I2S_FullDuplexConfig(
    SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct
);

void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);

void SPI_I2S_DMACmd(
    SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState
);

void SPI_I2S_ITConfig(
    SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState
);

FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
    }
#endif

#endif

