/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_hash_md5.c
 * 
 * This file provides high level functions to compute the HASH MD5 and
 * HMAC MD5 Digest of an input message. It uses the stm32f4xx_hash drivers
 * to access the STM32F4xx HASH peripheral.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_hash_md5 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_hash_md5 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_hash.h"
#include "stm32f4xx_conf.h"

#define MD5BUSY_TIMEOUT ((uint32_t) 0x00010000)

/**
 * Compute the HASH MD5 digest.
 * param Input: pointer to the Input buffer to be treated.
 * param Ilen: length of the Input buffer.
 * param Output: the returned digest
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: digest computation done
 *          - ERROR: digest computation failed
 */
ErrorStatus HASH_MD5(uint8_t* Input, uint32_t Ilen, uint8_t Output[16]) {
    HASH_InitTypeDef MD5_HASH_InitStructure;
    HASH_MsgDigest MD5_MessageDigest;
    __IO uint16_t nbvalidbitsdata = 0;
    uint32_t i = 0;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;

    /* Number of valid bits in last word of the Input data */
    nbvalidbitsdata = 8 * (Ilen % 4);
    HASH_DeInit(); /* HASH peripheral initialization */
    /* HASH Configuration */
    MD5_HASH_InitStructure.HASH_AlgoSelection = HASH_AlgoSelection_MD5;
    MD5_HASH_InitStructure.HASH_AlgoMode = HASH_AlgoMode_HASH;
    MD5_HASH_InitStructure.HASH_DataType = HASH_DataType_8b;
    HASH_Init(&MD5_HASH_InitStructure);
    /* Configure the number of valid bits in last word of the data */
    HASH_SetLastWordValidBitsNbr(nbvalidbitsdata);
    /* Write the Input block in the IN FIFO */
    for(i = 0; i < Ilen; i += 4) {
        HASH_DataIn(*(uint32_t*) inputaddr);
        inputaddr += 4;
    }
    HASH_StartDigest(); /* Start the HASH processor */
    /* wait until the Busy flag is RESET */
    do {
        busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
        counter++;
    } while((counter != MD5BUSY_TIMEOUT) && (busystatus != RESET));
    if (busystatus != RESET) {
       status = ERROR;
    } else {
        HASH_GetDigest(&MD5_MessageDigest); /* Read the message digest */
        *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[0]);
        outputaddr += 4;
        *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[1]);
        outputaddr += 4;
        *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[2]);
        outputaddr += 4;
        *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[3]);
    }
    return status;
}

/**
 * Compute the HMAC MD5 digest.
 * param Key: pointer to the Key used for HMAC.
 * param Keylen: length of the Key used for HMAC.
 * param Input: pointer to the Input buffer to be treated.
 * param Ilen: length of the Input buffer.
 * param Output: the returned digest
 * retval An ErrorStatus enumeration value:
 *          - SUCCESS: digest computation done
 *          - ERROR: digest computation failed
 */
ErrorStatus HMAC_MD5(
    uint8_t* Key, uint32_t Keylen, uint8_t* Input,
    uint32_t Ilen, uint8_t Output[16]
) {
    HASH_InitTypeDef MD5_HASH_InitStructure;
    HASH_MsgDigest MD5_MessageDigest;
    __IO uint16_t nbvalidbitsdata = 0;
    __IO uint16_t nbvalidbitskey = 0;
    uint32_t i = 0;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr = (uint32_t) Key;
    uint32_t inputaddr = (uint32_t) Input;
    uint32_t outputaddr = (uint32_t) Output;

    /* Number of valid bits in last word of the Input data */
    nbvalidbitsdata = 8 * (Ilen % 4);
    /* Number of valid bits in last word of the Key */
    nbvalidbitskey = 8 * (Keylen % 4);
    HASH_DeInit(); /* HASH peripheral initialization */
    /* HASH Configuration */
    MD5_HASH_InitStructure.HASH_AlgoSelection = HASH_AlgoSelection_MD5;
    MD5_HASH_InitStructure.HASH_AlgoMode = HASH_AlgoMode_HMAC;
    MD5_HASH_InitStructure.HASH_DataType = HASH_DataType_8b;
    if (Keylen > 64) {
        /* HMAC long Key */
        MD5_HASH_InitStructure.HASH_HMACKeyType = HASH_HMACKeyType_LongKey;
    } else {
        /* HMAC short Key */
        MD5_HASH_InitStructure.HASH_HMACKeyType = HASH_HMACKeyType_ShortKey;
    }
    HASH_Init(&MD5_HASH_InitStructure);
    /* Configure the number of valid bits in last word of the Key */
    HASH_SetLastWordValidBitsNbr(nbvalidbitskey);
    /* Write the Key */
    for(i = 0; i < Keylen; i += 4) {
        HASH_DataIn(*(uint32_t*) keyaddr);
        keyaddr += 4;
    }
    HASH_StartDigest(); /* Start the HASH processor */
    /* wait until the Busy flag is RESET */
    do {
        busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
        counter++;
    } while((counter != MD5BUSY_TIMEOUT) && (busystatus != RESET));
    if (busystatus != RESET) {
        status = ERROR;
    } else {
        /* Configure the number of valid bits in last word of Input data */
        HASH_SetLastWordValidBitsNbr(nbvalidbitsdata);
        /* Write the Input block in the IN FIFO */
        for(i = 0; i < Ilen; i += 4) {
            HASH_DataIn(*(uint32_t*) inputaddr);
            inputaddr += 4;
        }
        HASH_StartDigest(); /* Start the HASH processor */
        counter = 0; /* wait until the Busy flag is RESET */
        do {
            busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
            counter++;
        } while ((counter != MD5BUSY_TIMEOUT) && (busystatus != RESET));
        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* Configure the number of valid bits in last word of the Key */
            HASH_SetLastWordValidBitsNbr(nbvalidbitskey);
            keyaddr = (uint32_t) Key; /* Write the Key */
            for(i = 0; i < Keylen; i += 4) {
                HASH_DataIn(*(uint32_t*) keyaddr);
                keyaddr += 4;
            }
            HASH_StartDigest(); /* Start the HASH processor */
            counter = 0; /* wait until the Busy flag is RESET */
            do {
                busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
                counter++;
            } while((counter != MD5BUSY_TIMEOUT) && (busystatus != RESET));
            if (busystatus != RESET) {
                status = ERROR;
            } else {
                /* Read the message digest */
                HASH_GetDigest(&MD5_MessageDigest);
                *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[0]);
                outputaddr += 4;
                *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[1]);
                outputaddr += 4;
                *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[2]);
                outputaddr += 4;
                *(uint32_t*) (outputaddr) = __REV(MD5_MessageDigest.Data[3]);
            }
        }
    }
    return status;
}

