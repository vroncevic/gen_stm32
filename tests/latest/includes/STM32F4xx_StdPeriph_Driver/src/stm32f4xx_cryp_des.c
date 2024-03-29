/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_cryp_des.c
 * 
 * This file provides high level functions to encrypt and decrypt an
 * input message using DES in ECB/CBC modes. It uses the stm32f4xx_cryp
 * drivers to access the STM32F4xx CRYP peripheral.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_cryp_des is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_cryp_des is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_cryp.h"

#define DESBUSY_TIMEOUT ((uint32_t) 0x00010000)

/**
 * Encrypt and decrypt using DES in ECB Mode
 * param Mode: encryption or decryption Mode.
 *   This parameter can be one of the following values:
 *       arg MODE_ENCRYPT: Encryption
 *       arg MODE_DECRYPT: Decryption
 * param Key: Key used for DES algorithm.
 * param Ilength: length of the Input buffer, must be a multiple of 8.
 * param Input: pointer to the Input buffer.
 * param Output: pointer to the returned buffer.
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: Operation done
 *          - ERROR: Operation failed
 */
ErrorStatus CRYP_DES_ECB(
    uint8_t Mode, uint8_t Key[8], uint8_t* Input,
    uint32_t Ilength, uint8_t* Output
) {
    CRYP_InitTypeDef DES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef DES_CRYP_KeyInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr = (uint32_t) Key;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;
    uint32_t i = 0;

    /* Crypto structures initialisation*/
    CRYP_KeyStructInit(&DES_CRYP_KeyInitStructure);
    /* Crypto Init for Encryption process */
    if( Mode == MODE_ENCRYPT ) {
        DES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    } else {
        DES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
    }
    DES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_DES_ECB;
    DES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&DES_CRYP_InitStructure);
    /* Key Initialisation */
    DES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*) (keyaddr));
    keyaddr+=4;
    DES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(*(uint32_t*) (keyaddr));
    CRYP_KeyInit(& DES_CRYP_KeyInitStructure);
    CRYP_FIFOFlush(); /* Flush IN/OUT FIFO */
    /* Enable Crypto processor */
    CRYP_Cmd(ENABLE);
    for(i=0; ((i<Ilength) && (status != ERROR)); i+=8) {
        /* Write the Input block in the Input FIFO */
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr+=4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr+=4;
        /* Wait until the complete message has been processed */
        counter = 0;
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while((counter != DESBUSY_TIMEOUT) && (busystatus != RESET));
        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* Read the Output block from the Output FIFO */
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr+=4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr+=4;
        }
    }
    CRYP_Cmd(DISABLE); /* Disable Crypto */
    return status;
}

/**
 * Encrypt and decrypt using DES in CBC Mode
 * param Mode: encryption or decryption Mode.
 *   This parameter can be one of the following values:
 *       arg MODE_ENCRYPT: Encryption
 *       arg MODE_DECRYPT: Decryption
 * param Key: Key used for DES algorithm.
 * param InitVectors: Initialisation Vectors used for DES algorithm.
 * param Ilength: length of the Input buffer, must be a multiple of 8.
 * param Input: pointer to the Input buffer.
 * param Output: pointer to the returned buffer.
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: Operation done
 *          - ERROR: Operation failed
 */
ErrorStatus CRYP_DES_CBC(
    uint8_t Mode, uint8_t Key[8], uint8_t InitVectors[8],
    uint8_t* Input, uint32_t Ilength, uint8_t* Output
) {
    CRYP_InitTypeDef DES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef DES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef DES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr = (uint32_t) Key;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;
    uint32_t ivaddr = (uint32_t) InitVectors;
    uint32_t i = 0;

    /* Crypto structures initialisation*/
    CRYP_KeyStructInit(&DES_CRYP_KeyInitStructure);
    /* Crypto Init for Encryption process */
    if(Mode == MODE_ENCRYPT) {
        DES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    } else {
        DES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
    }
    DES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_DES_CBC;
    DES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&DES_CRYP_InitStructure);
    /* Key Initialisation */
    DES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*) (keyaddr));
    keyaddr+=4;
    DES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(*(uint32_t*) (keyaddr));
    CRYP_KeyInit(& DES_CRYP_KeyInitStructure);
    /* Initialization Vectors */
    DES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*) (ivaddr));
    ivaddr+=4;
    DES_CRYP_IVInitStructure.CRYP_IV0Right= __REV(*(uint32_t*) (ivaddr));
    CRYP_IVInit(&DES_CRYP_IVInitStructure);
    CRYP_FIFOFlush(); /* Flush IN/OUT FIFO */
    CRYP_Cmd(ENABLE); /* Enable Crypto processor */
    for(i=0; ((i<Ilength) && (status != ERROR)); i+=8) {
        /* Write the Input block in the Input FIFO */
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr+=4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr+=4;
        /* Wait until the complete message has been processed */
        counter = 0;
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while((counter != DESBUSY_TIMEOUT) && (busystatus != RESET));
        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* Read the Output block from the Output FIFO */
           *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr+=4;
           *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr+=4;
        }
    }
    CRYP_Cmd(DISABLE); /* Disable Crypto */
    return status;
}

