/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_cryp_aes.c
 * 
 * This file provides high level functions to encrypt and decrypt an
 * input message using AES in ECB/CBC/CTR modes.
 * It uses the stm32f4xx_cryp.c/.h drivers to access the STM32F4xx CRYP
 * peripheral.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_cryp_aes is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_cryp_aes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_cryp.h"

#define AESBUSY_TIMEOUT ((uint32_t) 0x00010000)

/**
 * Encrypt and decrypt using AES in ECB Mode
 * param Mode: encryption or decryption Mode.
 *   This parameter can be one of the following values:
 *       arg MODE_ENCRYPT: Encryption
 *       arg MODE_DECRYPT: Decryption
 * param Key: Key used for AES algorithm.
 * param Keysize: length of the Key, must be a 128, 192 or 256.
 * param Input: pointer to the Input buffer.
 * param Ilength: length of the Input buffer, must be a multiple of 16.
 * param Output: pointer to the returned buffer.
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: Operation done
 *          - ERROR: Operation failed
 */
ErrorStatus CRYP_AES_ECB(
    uint8_t Mode, uint8_t* Key, uint16_t Keysize,
    uint8_t* Input, uint32_t Ilength, uint8_t* Output
) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr = (uint32_t) Key;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;
    uint32_t i = 0;

    /* Crypto structures initialisation*/
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);
    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        default:
            break;
    }
    if (Mode == MODE_DECRYPT) {
        CRYP_FIFOFlush(); /* Flush IN/OUT FIFOs */
        /* Crypto Init for Key preparation for decryption process */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_Key;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_32b;
        CRYP_Init(&AES_CRYP_InitStructure);
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure); /* Key Initialisation */
        CRYP_Cmd(ENABLE); /* Enable Crypto processor */
        /* wait until the Busy flag is RESET */
        do {
          busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
          counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));
        if (busystatus != RESET) {
           status = ERROR;
        } else {
          /* Crypto Init for decryption process */  
          AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        }
    } else {
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);
        /* Crypto Init for Encryption process */
        AES_CRYP_InitStructure.CRYP_AlgoDir  = CRYP_AlgoDir_Encrypt;
    }
    AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_ECB;
    AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&AES_CRYP_InitStructure);
    CRYP_FIFOFlush(); /* Flush IN/OUT FIFOs */
    CRYP_Cmd(ENABLE); /* Enable Crypto processor */
    for(i=0; ((i<Ilength) && (status != ERROR)); i+=16) {
        /* Write the Input block in the IN FIFO */
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        counter = 0; /* Wait until the complete message has been processed */
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));
       if (busystatus != RESET) {
           status = ERROR;
       } else {
           /* Read the Output block from the Output FIFO */
           *(uint32_t*) (outputaddr) = CRYP_DataOut();
           outputaddr += 4;
           *(uint32_t*) (outputaddr) = CRYP_DataOut();
           outputaddr += 4;
           *(uint32_t*) (outputaddr) = CRYP_DataOut();
           outputaddr += 4;
           *(uint32_t*) (outputaddr) = CRYP_DataOut(); 
           outputaddr += 4;
        }
    }
    CRYP_Cmd(DISABLE); /* Disable Crypto */
    return status;
}

/**
 * Encrypt and decrypt using AES in CBC Mode
 * param Mode: encryption or decryption Mode.
 *   This parameter can be one of the following values:
 *       arg MODE_ENCRYPT: Encryption
 *       arg MODE_DECRYPT: Decryption
 * param InitVectors: Initialisation Vectors used for AES algorithm.
 * param Key: Key used for AES algorithm.
 * param Keysize: length of the Key, must be a 128, 192 or 256.
 * param Input: pointer to the Input buffer.
 * param Ilength: length of the Input buffer, must be a multiple of 16.
 * param Output: pointer to the returned buffer.
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: Operation done
 *          - ERROR: Operation failed
 */
ErrorStatus CRYP_AES_CBC(
    uint8_t Mode, uint8_t InitVectors[16], uint8_t* Key,
    uint16_t Keysize, uint8_t* Input, uint32_t Ilength,
    uint8_t* Output
) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef AES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr = (uint32_t) Key;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;
    uint32_t ivaddr = (uint32_t) InitVectors;
    uint32_t i = 0;

    /* Crypto structures initialisation*/
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);
    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        default:
            break;
    }
    /* CRYP Initialization Vectors */
    AES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*) (ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV0Right= __REV(*(uint32_t*) (ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Left = __REV(*(uint32_t*) (ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Right= __REV(*(uint32_t*) (ivaddr));
    if (Mode == MODE_DECRYPT) {
        CRYP_FIFOFlush(); /* Flush IN/OUT FIFOs */
        /* Crypto Init for Key preparation for decryption process */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_Key;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_32b;
        CRYP_Init(&AES_CRYP_InitStructure);
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure); /* Key Initialisation */
        CRYP_Cmd(ENABLE); /* Enable Crypto processor */
        /* wait until the Busy flag is RESET */
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
       } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));
       if (busystatus != RESET) {
           status = ERROR;
       } else {
           /* Crypto Init for decryption process */
           AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
       }
    } else {
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);
        /* Crypto Init for Encryption process */
        AES_CRYP_InitStructure.CRYP_AlgoDir  = CRYP_AlgoDir_Encrypt;
    }
    AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_CBC;
    AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&AES_CRYP_InitStructure);
    CRYP_IVInit(&AES_CRYP_IVInitStructure); /* CRYP Initialization Vectors */
    CRYP_FIFOFlush(); /* Flush IN/OUT FIFOs */
    CRYP_Cmd(ENABLE); /* Enable Crypto processor */
    for (i=0; ((i<Ilength) && (status != ERROR)); i+=16) {
        /* Write the Input block in the IN FIFO */
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        counter = 0; /* Wait until the complete message has been processed */
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));
        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* Read the Output block from the Output FIFO */
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
        }
    }
    CRYP_Cmd(DISABLE); /* Disable Crypto */
    return status;
}

/**
 * Encrypt and decrypt using AES in CTR Mode
 * param Mode: encryption or decryption Mode.
 *   This parameter can be one of the following values:
 *       arg MODE_ENCRYPT: Encryption
 *       arg MODE_DECRYPT: Decryption
 * param InitVectors: Initialisation Vectors used for AES algorithm.
 * param Key: Key used for AES algorithm.
 * param Keysize: length of the Key, must be a 128, 192 or 256.
 * param Input: pointer to the Input buffer.
 * param Ilength: length of the Input buffer, must be a multiple of 16.
 * param Output: pointer to the returned buffer.
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: Operation done
 *          - ERROR: Operation failed
 */
ErrorStatus CRYP_AES_CTR(
    uint8_t Mode, uint8_t InitVectors[16], uint8_t* Key,
    uint16_t Keysize, uint8_t* Input, uint32_t Ilength,
    uint8_t* Output
) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef AES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr = (uint32_t) Key;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;
    uint32_t ivaddr = (uint32_t) InitVectors;
    uint32_t i = 0;

    /* Crypto structures initialisation*/
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);
    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(
                *(uint32_t*) (keyaddr)
            );
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right= __REV(
                *(uint32_t*) (keyaddr)
            );
            break;
        default:
            break;
    }
    /* CRYP Initialization Vectors */
    AES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*) (ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV0Right= __REV(*(uint32_t*) (ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Left = __REV(*(uint32_t*) (ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Right= __REV(*(uint32_t*) (ivaddr));
    CRYP_KeyInit(&AES_CRYP_KeyInitStructure); /* Key Initialisation */
    if (Mode == MODE_DECRYPT) {
        /* Crypto Init for decryption process */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
    } else {
        /* Crypto Init for Encryption process */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    }
    AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_CTR;
    AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&AES_CRYP_InitStructure);
    CRYP_IVInit(&AES_CRYP_IVInitStructure); /* CRYP Initialization Vectors */
    CRYP_FIFOFlush(); /* Flush IN/OUT FIFOs */
    CRYP_Cmd(ENABLE); /* Enable Crypto processor */
    for (i=0; ((i<Ilength) && (status != ERROR)); i+=16) {
        /* Write the Input block in the IN FIFO */
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*) (inputaddr));
        inputaddr += 4;
        counter = 0; /* Wait until the complete message has been processed */
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));
        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* Read the Output block from the Output FIFO */
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*) (outputaddr) = CRYP_DataOut();
            outputaddr += 4;
        }
    }
    CRYP_Cmd(DISABLE); /* Disable Crypto */
    return status;
}

