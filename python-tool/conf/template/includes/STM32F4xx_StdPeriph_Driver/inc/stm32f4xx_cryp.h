/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_cryp.h
 * 
 * This file contains all the functions prototypes for the Cryptographic
 * processor(CRYP) firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_cryp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_cryp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_CRYP_H
#define __STM32F4xx_CRYP_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    uint16_t CRYP_AlgoDir; /* Encrypt or Decrypt. This parameter can be a
                              value of @ref CRYP_Algorithm_Direction */
    uint16_t CRYP_AlgoMode; /* TDES-ECB, TDES-CBC, DES-ECB, DES-CBC, AES-ECB,
                               AES-CBC, AES-CTR, AES-Key. This parameter can
                               be a value of @ref CRYP_Algorithm_Mode */
    uint16_t CRYP_DataType; /* 32-bit/16-bit/1-bit data, bit-string.
                               Parameter can be a value of CRYP_Data_Type */
    uint16_t CRYP_KeySize; /* Used only in AES mode only : 128, 192 or 256
                              bit key length. Parameter can be a value of
                              CRYP_Key_Size_for_AES_only */
} CRYP_InitTypeDef;

typedef struct {
    uint32_t CRYP_Key0Left; /* Key 0 Left  */
    uint32_t CRYP_Key0Right; /* Key 0 Right */
    uint32_t CRYP_Key1Left; /* Key 1 left  */
    uint32_t CRYP_Key1Right; /* Key 1 Right */
    uint32_t CRYP_Key2Left; /* Key 2 left  */
    uint32_t CRYP_Key2Right; /* Key 2 Right */
    uint32_t CRYP_Key3Left; /* Key 3 left  */
    uint32_t CRYP_Key3Right; /* Key 3 Right */
} CRYP_KeyInitTypeDef;

typedef struct {
    uint32_t CRYP_IV0Left; /* Init Vector 0 Left */
    uint32_t CRYP_IV0Right; /* Init Vector 0 Right */
    uint32_t CRYP_IV1Left; /* Init Vector 1 left */
    uint32_t CRYP_IV1Right; /* Init Vector 1 Right */
} CRYP_IVInitTypeDef;

typedef struct {
    /* Configuration */
    uint32_t CR_bits9to2;
    /* KEY */
    uint32_t CRYP_IV0LR;
    uint32_t CRYP_IV0RR;
    uint32_t CRYP_IV1LR;
    uint32_t CRYP_IV1RR;
    /* IV */
    uint32_t CRYP_K0LR;
    uint32_t CRYP_K0RR;
    uint32_t CRYP_K1LR;
    uint32_t CRYP_K1RR;
    uint32_t CRYP_K2LR;
    uint32_t CRYP_K2RR;
    uint32_t CRYP_K3LR;
    uint32_t CRYP_K3RR;
} CRYP_Context;

#define CRYP_AlgoDir_Encrypt ((uint16_t) 0x0000)
#define CRYP_AlgoDir_Decrypt ((uint16_t) 0x0004)
#define CRYP_AlgoMode_TDES_ECB ((uint16_t) 0x0000)
#define CRYP_AlgoMode_TDES_CBC ((uint16_t) 0x0008)
#define CRYP_AlgoMode_DES_ECB ((uint16_t) 0x0010)
#define CRYP_AlgoMode_DES_CBC ((uint16_t) 0x0018)
#define CRYP_AlgoMode_AES_ECB ((uint16_t) 0x0020)
#define CRYP_AlgoMode_AES_CBC ((uint16_t) 0x0028)
#define CRYP_AlgoMode_AES_CTR ((uint16_t) 0x0030)
#define CRYP_AlgoMode_AES_Key ((uint16_t) 0x0038)
#define CRYP_DataType_32b ((uint16_t) 0x0000)
#define CRYP_DataType_16b ((uint16_t) 0x0040)
#define CRYP_DataType_8b ((uint16_t) 0x0080)
#define CRYP_DataType_1b ((uint16_t) 0x00C0)
#define CRYP_KeySize_128b ((uint16_t) 0x0000)
#define CRYP_KeySize_192b ((uint16_t) 0x0100)
#define CRYP_KeySize_256b ((uint16_t) 0x0200)
#define CRYP_FLAG_BUSY ((uint8_t) 0x10)
#define CRYP_FLAG_IFEM ((uint8_t) 0x01)
#define CRYP_FLAG_IFNF ((uint8_t) 0x02)
#define CRYP_FLAG_INRIS ((uint8_t) 0x22)
#define CRYP_FLAG_OFNE ((uint8_t) 0x04)
#define CRYP_FLAG_OFFU ((uint8_t) 0x08)
#define CRYP_FLAG_OUTRIS ((uint8_t) 0x21)
#define CRYP_IT_INI ((uint8_t) 0x01)
#define CRYP_IT_OUTI ((uint8_t) 0x02)
#define MODE_ENCRYPT ((uint8_t) 0x01)
#define MODE_DECRYPT ((uint8_t) 0x00)
#define CRYP_DMAReq_DataIN ((uint8_t) 0x01)
#define CRYP_DMAReq_DataOUT ((uint8_t) 0x02)

#define IS_CRYP_ALGODIR(ALGODIR) ( \
    ((ALGODIR) == CRYP_AlgoDir_Encrypt) || \
    ((ALGODIR) == CRYP_AlgoDir_Decrypt) \
)

#define IS_CRYP_ALGOMODE(ALGOMODE) ( \
    ((ALGOMODE) == CRYP_AlgoMode_TDES_ECB) || \
    ((ALGOMODE) == CRYP_AlgoMode_TDES_CBC)|| \
    ((ALGOMODE) == CRYP_AlgoMode_DES_ECB)|| \
    ((ALGOMODE) == CRYP_AlgoMode_DES_CBC) || \
    ((ALGOMODE) == CRYP_AlgoMode_AES_ECB) || \
    ((ALGOMODE) == CRYP_AlgoMode_AES_CBC) || \
    ((ALGOMODE) == CRYP_AlgoMode_AES_CTR) || \
    ((ALGOMODE) == CRYP_AlgoMode_AES_Key) \
)

#define IS_CRYP_DATATYPE(DATATYPE) ( \
    ((DATATYPE) == CRYP_DataType_32b) || \
    ((DATATYPE) == CRYP_DataType_16b)|| \
    ((DATATYPE) == CRYP_DataType_8b)|| \
    ((DATATYPE) == CRYP_DataType_1b) \
)

#define IS_CRYP_KEYSIZE(KEYSIZE) ( \
    ((KEYSIZE) == CRYP_KeySize_128b)|| \
    ((KEYSIZE) == CRYP_KeySize_192b)|| \
    ((KEYSIZE) == CRYP_KeySize_256b) \
)

#define IS_CRYP_GET_FLAG(FLAG) ( \
    ((FLAG) == CRYP_FLAG_IFEM) || \
    ((FLAG) == CRYP_FLAG_IFNF) || \
    ((FLAG) == CRYP_FLAG_OFNE) || \
    ((FLAG) == CRYP_FLAG_OFFU) || \
    ((FLAG) == CRYP_FLAG_BUSY) || \
    ((FLAG) == CRYP_FLAG_OUTRIS)|| \
    ((FLAG) == CRYP_FLAG_INRIS) \
)

#define IS_CRYP_CONFIG_IT(IT) ( \
    (((IT) & (uint8_t)0xFC) == 0x00) && ((IT) != 0x00) \
)

#define IS_CRYP_GET_IT(IT) (((IT) == CRYP_IT_INI) || ((IT) == CRYP_IT_OUTI))

#define IS_CRYP_DMAREQ(DMAREQ) ( \
    (((DMAREQ) & (uint8_t)0xFC) == 0x00) && ((DMAREQ) != 0x00) \
)

void CRYP_DeInit(void);
void CRYP_Init(CRYP_InitTypeDef* CRYP_InitStruct);
void CRYP_StructInit(CRYP_InitTypeDef* CRYP_InitStruct);
void CRYP_KeyInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct);
void CRYP_KeyStructInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct);
void CRYP_IVInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct);
void CRYP_IVStructInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct);
void CRYP_Cmd(FunctionalState NewState);
void CRYP_DataIn(uint32_t Data);
uint32_t CRYP_DataOut(void);
void CRYP_FIFOFlush(void);

ErrorStatus CRYP_SaveContext(
    CRYP_Context* CRYP_ContextSave, CRYP_KeyInitTypeDef* CRYP_KeyInitStruct
);

void CRYP_RestoreContext(CRYP_Context* CRYP_ContextRestore);
void CRYP_DMACmd(uint8_t CRYP_DMAReq, FunctionalState NewState);
void CRYP_ITConfig(uint8_t CRYP_IT, FunctionalState NewState);
ITStatus CRYP_GetITStatus(uint8_t CRYP_IT);
FlagStatus CRYP_GetFlagStatus(uint8_t CRYP_FLAG);

ErrorStatus CRYP_AES_ECB(
    uint8_t Mode, uint8_t* Key, uint16_t Keysize,
    uint8_t* Input, uint32_t Ilength, uint8_t* Output
);

ErrorStatus CRYP_AES_CBC(
    uint8_t Mode, uint8_t InitVectors[16], uint8_t* Key, uint16_t Keysize,
    uint8_t* Input, uint32_t Ilength, uint8_t* Output
);

ErrorStatus CRYP_AES_CTR(
    uint8_t Mode, uint8_t InitVectors[16], uint8_t* Key, uint16_t Keysize,
    uint8_t* Input, uint32_t Ilength, uint8_t* Output
);

ErrorStatus CRYP_TDES_ECB(
    uint8_t Mode, uint8_t Key[24], uint8_t* Input,
    uint32_t Ilength, uint8_t* Output
);

ErrorStatus CRYP_TDES_CBC(
    uint8_t Mode, uint8_t Key[24], uint8_t InitVectors[8],
    uint8_t* Input, uint32_t Ilength, uint8_t* Output
);

ErrorStatus CRYP_DES_ECB(
    uint8_t Mode, uint8_t Key[8], uint8_t* Input,
    uint32_t Ilength, uint8_t* Output
);

ErrorStatus CRYP_DES_CBC(
    uint8_t Mode, uint8_t Key[8], uint8_t InitVectors[8],
    uint8_t* Input,uint32_t Ilength, uint8_t* Output
);

#ifdef __cplusplus
    }
#endif

#endif

