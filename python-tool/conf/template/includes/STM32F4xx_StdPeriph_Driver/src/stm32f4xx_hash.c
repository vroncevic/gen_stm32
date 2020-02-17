/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_hash.c
 * 
 * This file provides firmware functions to manage the following 
 * functionalities of the HASH / HMAC Processor (HASH) peripheral:
 *   - Initialization and Configuration functions
 *   - Message Digest generation functions
 *   - context swapping functions
 *   - DMA interface function
 *   - Interrupts and flags management
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

#include "stm32f4xx_hash.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/**
 * Deinitializes the HASH peripheral registers to their default reset values
 * param None
 * retval None
 */
void HASH_DeInit(void) {
    /* Enable HASH reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_HASH, ENABLE);
    /* Release HASH from reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_HASH, DISABLE);
}

/**
 * Initializes the HASH peripheral according to the specified parameters
 * in the HASH_InitStruct structure.
 * The hash processor is reset when calling this function so that the
 * HASH will be ready to compute the message digest of a new message.
 * There is no need to call HASH_Reset() function.
 * param HASH_InitStruct: pointer to a HASH_InitTypeDef structure that contains
 *       configuration information for the HASH peripheral.
 * The field HASH_HMACKeyType in HASH_InitTypeDef must be filled only 
 * if the algorithm mode is HMAC.
 * retval None
 */
void HASH_Init(HASH_InitTypeDef* HASH_InitStruct) {
    assert_param(IS_HASH_ALGOSELECTION(HASH_InitStruct->HASH_AlgoSelection));
    assert_param(IS_HASH_DATATYPE(HASH_InitStruct->HASH_DataType));
    assert_param(IS_HASH_ALGOMODE(HASH_InitStruct->HASH_AlgoMode));
    /* Configure the Algorithm used, algorithm mode and the datatype */
    HASH->CR &= ~ (HASH_CR_ALGO | HASH_CR_DATATYPE | HASH_CR_MODE);
    HASH->CR |= (
        HASH_InitStruct->HASH_AlgoSelection | \
        HASH_InitStruct->HASH_DataType | \
        HASH_InitStruct->HASH_AlgoMode
    );
    /* if algorithm mode is HMAC, set the Key */  
    if (HASH_InitStruct->HASH_AlgoMode == HASH_AlgoMode_HMAC) {
        assert_param(IS_HASH_HMAC_KEYTYPE(HASH_InitStruct->HASH_HMACKeyType));
        HASH->CR &= ~HASH_CR_LKEY;
        HASH->CR |= HASH_InitStruct->HASH_HMACKeyType;
    }
    /**
     * Reset the HASH processor core, so that the HASH will
     * be ready to computethe message digest of a new message.
     */
    HASH->CR |= HASH_CR_INIT;
}

/**
 * Fills each HASH_InitStruct member with its default value.
 * param HASH_InitStruct : pointer to a HASH_InitTypeDef structure which will
 * be initialized.
 * The default values set are : Processor mode is HASH, Algorithm selected is
 * SHA1, Data type selected is 32b and HMAC Key Type is short key.
 * retval None
 */
void HASH_StructInit(HASH_InitTypeDef* HASH_InitStruct) {
    /* Initialize the HASH_AlgoSelection member */
    HASH_InitStruct->HASH_AlgoSelection = HASH_AlgoSelection_SHA1;
    /* Initialize the HASH_AlgoMode member */
    HASH_InitStruct->HASH_AlgoMode = HASH_AlgoMode_HASH;
    /* Initialize the HASH_DataType member */
    HASH_InitStruct->HASH_DataType = HASH_DataType_32b;
    /* Initialize the HASH_HMACKeyType member */
    HASH_InitStruct->HASH_HMACKeyType = HASH_HMACKeyType_ShortKey;
}

/**
 * Resets the HASH processor core, so that the HASH will be ready
 * to compute the message digest of a new message.
 * Calling this function will clear the HASH_SR_DCIS (Digest calculation 
 * completion interrupt status) bit corresponding to HASH_IT_DCI 
 * interrupt and HASH_FLAG_DCIS flag.
 * param None
 * retval None
 */
void HASH_Reset(void) {
    HASH->CR |= HASH_CR_INIT; /* Reset the HASH processor core */
}

/**
 * Configure the Number of valid bits in last word of the message
 * param ValidNumber: Number of valid bits in last word of the message.
 *   This parameter must be a number between 0 and 0x1F.
 *       - 0x00: All 32 bits of the last data written are valid
 *       - 0x01: Only bit [0] of the last data written is valid
 *       - 0x02: Only bits[1:0] of the last data written are valid
 *       - 0x03: Only bits[2:0] of the last data written are valid
 *       - ...
 *       - 0x1F: Only bits[30:0] of the last data written are valid
 * The Number of valid bits must be set before to start the message
 * digest competition (in Hash and HMAC) and key treatment(in HMAC).
 * retval None
 */
void HASH_SetLastWordValidBitsNbr(uint16_t ValidNumber) {
    assert_param(IS_HASH_VALIDBITSNUMBER(ValidNumber));
    /* Configure the Number of valid bits in last word of the message */
    HASH->STR &= ~(HASH_STR_NBW);
    HASH->STR |= ValidNumber;
}

/**
 * Writes data in the Data Input FIFO
 * param Data: new data of the message to be processed.
 * retval None
 */
void HASH_DataIn(uint32_t Data) {
    HASH->DIN = Data; /* Write in the DIN register a new data */
}

/**
 * Returns the number of words already pushed into the IN FIFO.
 * param None
 * retval The value of words already pushed into the IN FIFO.
 */
uint8_t HASH_GetInFIFOWordsNbr(void) {
    return ((HASH->CR & HASH_CR_NBW) >> 8); /* Return the value of NBW bits */
}

/**
 * Provides the message digest result.
 * In MD5 mode, Data[4] filed of HASH_MsgDigest structure is not used
 * and is read as zero.
 * param HASH_MessageDigest: pointer to a HASH_MsgDigest structure which will 
 *       hold the message digest result 
 * retval None
 */
void HASH_GetDigest(HASH_MsgDigest* HASH_MessageDigest) {
    /* Get the data field */
    HASH_MessageDigest->Data[0] = HASH->HR[0];
    HASH_MessageDigest->Data[1] = HASH->HR[1];
    HASH_MessageDigest->Data[2] = HASH->HR[2];
    HASH_MessageDigest->Data[3] = HASH->HR[3];
    HASH_MessageDigest->Data[4] = HASH->HR[4];
}

/**
 * Starts the message padding and calculation of the final message
 * param None
 * retval None
 */
void HASH_StartDigest(void) {
    HASH->STR |= HASH_STR_DCAL; /* Start the Digest calculation */
}

/**
 * Save the Hash peripheral Context.
 * The context can be saved only when no block is currently being 
 * processed. So user must wait for DINIS = 1 (the last block has been 
 * processed and the input FIFO is empty) or NBW != 0 (the FIFO is not 
 * full and no processing is ongoing).   
 * param HASH_ContextSave: pointer to a HASH_Context structure that contains
 *       the repository for current context.
 * retval None
 */
void HASH_SaveContext(HASH_Context* HASH_ContextSave) {
    uint8_t i = 0;

    /* save context registers */
    HASH_ContextSave->HASH_IMR = HASH->IMR;
    HASH_ContextSave->HASH_STR = HASH->STR;
    HASH_ContextSave->HASH_CR  = HASH->CR;
    for(i = 0; i <= 50;i++) {
        HASH_ContextSave->HASH_CSR[i] = HASH->CSR[i];
    }
}

/**
 * Restore the Hash peripheral Context.
 * After calling this function, user can restart the processing from the
 * point where it has been interrupted.
 * param HASH_ContextRestore: pointer to a HASH_Context structure that contains
 *       the repository for saved context.
 * retval None
 */
void HASH_RestoreContext(HASH_Context* HASH_ContextRestore) {
    uint8_t i = 0;

    /* restore context registers */
    HASH->IMR = HASH_ContextRestore->HASH_IMR;
    HASH->STR = HASH_ContextRestore->HASH_STR;
    HASH->CR = HASH_ContextRestore->HASH_CR;
    HASH->CR |= HASH_CR_INIT; /* Initialize the hash processor */
    /* continue restoring context registers */
    for(i = 0; i <= 50;i++) {
        HASH->CSR[i] = HASH_ContextRestore->HASH_CSR[i];
    }
}

/**
 * Enables or disables the HASH DMA interface.
 * @note   The DMA is disabled by hardware after the end of transfer.
 * param NewState: new state of the selected HASH DMA transfer request.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void HASH_DMACmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        HASH->CR |= HASH_CR_DMAE; /* Enable the HASH DMA request */
    } else {
        HASH->CR &= ~HASH_CR_DMAE; /* Disable the HASH DMA request */
    }
}

/**
 * Enables or disables the specified HASH interrupts.
 * param HASH_IT: specifies HASH interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *       arg HASH_IT_DINI: Data Input interrupt
 *       arg HASH_IT_DCI: Digest Calculation Completion Interrupt
 * param NewState: new state of the specified HASH interrupt.
 *       This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void HASH_ITConfig(uint8_t HASH_IT, FunctionalState NewState) {
    assert_param(IS_HASH_IT(HASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        HASH->IMR |= HASH_IT; /* Enable the selected HASH interrupt */
    } else {
        HASH->IMR &= (uint8_t) ~HASH_IT; /* Disable selected HASH interrupt */
    }
}

/**
 * Checks whether the specified HASH flag is set or not.
 * param HASH_FLAG: specifies the HASH flag to check.
 *   This parameter can be one of the following values:
 *       arg HASH_FLAG_DINIS: Data input interrupt status flag
 *       arg HASH_FLAG_DCIS: Digest calculation completion interr status flag
 *       arg HASH_FLAG_BUSY: Busy flag
 *       arg HASH_FLAG_DMAS: DMAS Status flag
 *       arg HASH_FLAG_DINNE: Data Input register (DIN) not empty status flag
 * retval The new state of HASH_FLAG (SET or RESET)
 */
FlagStatus HASH_GetFlagStatus(uint16_t HASH_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tempreg = 0;

    assert_param(IS_HASH_GET_FLAG(HASH_FLAG));
    /* check if the FLAG is in CR register */
    if ((HASH_FLAG & HASH_FLAG_DINNE) != (uint16_t) RESET)  {
        tempreg = HASH->CR;
    } else {
        tempreg = HASH->SR;
    }
    /* Check the status of the specified HASH flag */
    if ((tempreg & HASH_FLAG) != (uint16_t) RESET) {
        bitstatus = SET; /* HASH is set */
    } else {
        bitstatus = RESET; /* HASH_FLAG is reset */
    }
    return bitstatus; /* Return the HASH_FLAG status */
}
/**
 * Clears the HASH flags.
 * param HASH_FLAG: specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *       arg HASH_FLAG_DINIS: Data Input Flag
 *       arg HASH_FLAG_DCIS: Digest Calculation Completion Flag
 * retval None
 */
void HASH_ClearFlag(uint16_t HASH_FLAG) {
    assert_param(IS_HASH_CLEAR_FLAG(HASH_FLAG));
    HASH->SR = ~(uint32_t) HASH_FLAG; /* Clear the selected HASH flags */
}

/**
 * Checks whether the specified HASH interrupt has occurred or not.
 * param HASH_IT: specifies the HASH interrupt source to check.
 *   This parameter can be one of the following values:
 *       arg HASH_IT_DINI: Data Input interrupt
 *       arg HASH_IT_DCI: Digest Calculation Completion Interrupt
 * retval The new state of HASH_IT (SET or RESET).
 */
ITStatus HASH_GetITStatus(uint8_t HASH_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    assert_param(IS_HASH_GET_IT(HASH_IT));
    /* Check the status of the specified HASH interrupt */
    tmpreg =  HASH->SR;
    if (((HASH->IMR & tmpreg) & HASH_IT) != RESET) {
        bitstatus = SET; /* HASH_IT is set */
    } else {
        bitstatus = RESET; /* HASH_IT is reset */
    }
    return bitstatus; /* Return the HASH_IT status */
}

/**
 * Clears the HASH interrupt pending bit(s).
 * param HASH_IT: specifies the HASH interrupt pending bit(s) to clear.
 *   This parameter can be any combination of the following values:
 *       arg HASH_IT_DINI: Data Input interrupt
 *       arg HASH_IT_DCI: Digest Calculation Completion Interrupt
 * retval None
 */
void HASH_ClearITPendingBit(uint8_t HASH_IT) {
    assert_param(IS_HASH_IT(HASH_IT));
    /* Clear the selected HASH interrupt pending bit */
    HASH->SR = (uint8_t) ~HASH_IT;
}

