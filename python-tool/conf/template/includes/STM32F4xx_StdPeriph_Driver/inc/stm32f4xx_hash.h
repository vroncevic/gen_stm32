/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_hash.h
 * 
 * This file contains all the functions prototypes for the HASH
 * firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_hash is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_hash is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_HASH_H
#define __STM32F4xx_HASH_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    uint32_t HASH_AlgoSelection; /* SHA-1 or MD5. Parameter can be a value
                                    of HASH_Algo_Selection */
    uint32_t HASH_AlgoMode; /* HASH or HMAC. Parameter can be a value
                               of HASH_processor_Algorithm_Mode */
    uint32_t HASH_DataType; /* 32-bit data, 16-bit data, 8-bit data or
                               bit-string. Parameter can be a value of
                               HASH_Data_Type */
    uint32_t HASH_HMACKeyType; /* HMAC Short key or HMAC Long Key.
                                  Parameter can be a value of.*/
} HASH_InitTypeDef;

typedef struct {
    uint32_t Data[5]; /* Message digest result:
                         5x 32bit words for SHA1 or
                         4x 32bit words for MD5.*/
} HASH_MsgDigest;

typedef struct {
    uint32_t HASH_IMR;
    uint32_t HASH_STR;
    uint32_t HASH_CR;
    uint32_t HASH_CSR[51];
} HASH_Context;

#define HASH_AlgoSelection_SHA1 ((uint16_t) 0x0000) /* HASH function is SHA1 */
#define HASH_AlgoSelection_MD5 ((uint16_t) 0x0080) /* HASH function is MD5 */
#define HASH_AlgoMode_HASH ((uint16_t) 0x0000) /* Algorithm is HASH */ 
#define HASH_AlgoMode_HMAC ((uint16_t) 0x0040) /* Algorithm is HMAC */
#define HASH_DataType_32b ((uint16_t) 0x0000)
#define HASH_DataType_16b ((uint16_t) 0x0010)
#define HASH_DataType_8b ((uint16_t) 0x0020)
#define HASH_DataType_1b ((uint16_t) 0x0030)

/* HMAC Key is <= 64 bytes */
#define HASH_HMACKeyType_ShortKey ((uint32_t) 0x00000000)

/* HMAC Key is > 64 bytes */
#define HASH_HMACKeyType_LongKey ((uint32_t) 0x00010000)

/* A new block can be entered into the input buffer (DIN)*/
#define HASH_IT_DINI ((uint8_t) 0x01)
#define HASH_IT_DCI ((uint8_t) 0x02) /* Digest calculation complete */

/* 16 locations are free in DIN: new block can be entered into the in buffer.*/
#define HASH_FLAG_DINIS ((uint16_t) 0x0001)
#define HASH_FLAG_DCIS ((uint16_t) 0x0002) /* Digest calculation complete */

/* DMA interface is enabled (DMAE=1) or a transfer is ongoing */
#define HASH_FLAG_DMAS ((uint16_t) 0x0004)

/* The hash core is Busy: processing a block of data */
#define HASH_FLAG_BUSY ((uint16_t) 0x0008)

/* DIN not empty: The input buffer contains at least one word of data */
#define HASH_FLAG_DINNE ((uint16_t) 0x1000)

#define IS_HASH_ALGOSELECTION(ALGOSELECTION) ( \
    ((ALGOSELECTION) == HASH_AlgoSelection_SHA1) || \
    ((ALGOSELECTION) == HASH_AlgoSelection_MD5) \
)

#define IS_HASH_ALGOMODE(ALGOMODE) ( \
    ((ALGOMODE) == HASH_AlgoMode_HASH) || \
    ((ALGOMODE) == HASH_AlgoMode_HMAC) \
)

#define IS_HASH_DATATYPE(DATATYPE) ( \
    ((DATATYPE) == HASH_DataType_32b)|| \
    ((DATATYPE) == HASH_DataType_16b)|| \
    ((DATATYPE) == HASH_DataType_8b)|| \
    ((DATATYPE) == HASH_DataType_1b) \
)

#define IS_HASH_HMAC_KEYTYPE(KEYTYPE) ( \
    ((KEYTYPE) == HASH_HMACKeyType_ShortKey) || \
    ((KEYTYPE) == HASH_HMACKeyType_LongKey) \
)

#define IS_HASH_VALIDBITSNUMBER(VALIDBITS) ((VALIDBITS) <= 0x1F)
#define IS_HASH_IT(IT) ((((IT) & (uint8_t)0xFC) == 0x00) && ((IT) != 0x00))
#define IS_HASH_GET_IT(IT) (((IT) == HASH_IT_DINI) || ((IT) == HASH_IT_DCI))

#define IS_HASH_GET_FLAG(FLAG) ( \
    ((FLAG) == HASH_FLAG_DINIS) || \
    ((FLAG) == HASH_FLAG_DCIS) || \
    ((FLAG) == HASH_FLAG_DMAS) || \
    ((FLAG) == HASH_FLAG_BUSY) || \
    ((FLAG) == HASH_FLAG_DINNE) \
)

#define IS_HASH_CLEAR_FLAG(FLAG) ( \
    ((FLAG) == HASH_FLAG_DINIS) || \
    ((FLAG) == HASH_FLAG_DCIS) \
)

void HASH_DeInit(void);
void HASH_Init(HASH_InitTypeDef* HASH_InitStruct);
void HASH_StructInit(HASH_InitTypeDef* HASH_InitStruct);
void HASH_Reset(void);
void HASH_DataIn(uint32_t Data);
uint8_t HASH_GetInFIFOWordsNbr(void);
void HASH_SetLastWordValidBitsNbr(uint16_t ValidNumber);
void HASH_StartDigest(void);
void HASH_GetDigest(HASH_MsgDigest* HASH_MessageDigest);
void HASH_SaveContext(HASH_Context* HASH_ContextSave);
void HASH_RestoreContext(HASH_Context* HASH_ContextRestore);
void HASH_DMACmd(FunctionalState NewState);
void HASH_ITConfig(uint8_t HASH_IT, FunctionalState NewState);
FlagStatus HASH_GetFlagStatus(uint16_t HASH_FLAG);
void HASH_ClearFlag(uint16_t HASH_FLAG);
ITStatus HASH_GetITStatus(uint8_t HASH_IT);
void HASH_ClearITPendingBit(uint8_t HASH_IT);
ErrorStatus HASH_SHA1(uint8_t* Input, uint32_t Ilen, uint8_t Output[20]);

ErrorStatus HMAC_SHA1(
    uint8_t* Key, uint32_t Keylen, uint8_t* Input, uint32_t Ilen,
    uint8_t Output[20]
);

ErrorStatus HASH_MD5(uint8_t* Input, uint32_t Ilen, uint8_t Output[16]);

ErrorStatus HMAC_MD5(
    uint8_t* Key, uint32_t Keylen, uint8_t* Input, uint32_t Ilen,
    uint8_t Output[16]
);

#ifdef __cplusplus
    }
#endif

#endif

