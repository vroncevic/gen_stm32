/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_cryp.c
 * 
 * This file provides firmware functions to manage following 
 * functionalities of  Cryptographic processor (CRYP) peripheral:
 *     - Initialization and Configuration functions
 *     - Data treatment functions
 *     - Context swapping functions
 *     - DMA interface function
 *     - Interrupts and flags management
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

#include "stm32f4xx_cryp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

#define FLAG_MASK ((uint8_t) 0x20)
#define MAX_TIMEOUT ((uint16_t) 0xFFFF)

/**
 * Deinitializes CRYP peripheral registers to their default reset values
 * param None
 * retval None
 */
void CRYP_DeInit(void) {
    /* Enable CRYP reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, ENABLE);
    /* Release CRYP from reset state */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, DISABLE);
}

/**
 * Initializes CRYP peripheral according to specified parameters
 * in CRYP_InitStruct.
 * param CRYP_InitStruct: pointer to a CRYP_InitTypeDef structure that contains
 *       configuration information for CRYP peripheral.
 * retval None
 */
void CRYP_Init(CRYP_InitTypeDef* CRYP_InitStruct) {
    assert_param(IS_CRYP_ALGOMODE(CRYP_InitStruct->CRYP_AlgoMode));
    assert_param(IS_CRYP_DATATYPE(CRYP_InitStruct->CRYP_DataType));
    assert_param(IS_CRYP_ALGODIR(CRYP_InitStruct->CRYP_AlgoDir));
    CRYP->CR &= ~CRYP_CR_ALGOMODE; /* Select Algorithm mode*/
    CRYP->CR |= CRYP_InitStruct->CRYP_AlgoMode;
    CRYP->CR &= ~CRYP_CR_DATATYPE; /* Select dataType */
    CRYP->CR |= CRYP_InitStruct->CRYP_DataType;
    /* select Key size (used only with AES algorithm) */
    if (
        (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_ECB) ||
        (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_CBC) ||
        (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_CTR) ||
        (CRYP_InitStruct->CRYP_AlgoMode == CRYP_AlgoMode_AES_Key)
    ) {
        assert_param(IS_CRYP_KEYSIZE(CRYP_InitStruct->CRYP_KeySize));
        CRYP->CR &= ~CRYP_CR_KEYSIZE;
        /* Key size and value must be configured once key has been prepared */
        CRYP->CR |= CRYP_InitStruct->CRYP_KeySize;
    }
    CRYP->CR &= ~CRYP_CR_ALGODIR; /* Select data Direction */
    CRYP->CR |= CRYP_InitStruct->CRYP_AlgoDir;
}

/**
 * Fills each CRYP_InitStruct member with its default value.
 * param CRYP_InitStruct: pointer to a CRYP_InitTypeDef structure which will
 *       be initialized.
 * retval None
 */
void CRYP_StructInit(CRYP_InitTypeDef* CRYP_InitStruct) {
    /* Initialize CRYP_AlgoDir member */
    CRYP_InitStruct->CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    /* initialize CRYP_AlgoMode member */
    CRYP_InitStruct->CRYP_AlgoMode = CRYP_AlgoMode_TDES_ECB;
    /* initialize CRYP_DataType member */
    CRYP_InitStruct->CRYP_DataType = CRYP_DataType_32b;
    /* Initialize CRYP_KeySize member */
    CRYP_InitStruct->CRYP_KeySize = CRYP_KeySize_128b;
}

/**
 * Initializes CRYP Keys according to specified parameters in
 * CRYP_KeyInitStruct.
 * param CRYP_KeyInitStruct: pointer to a CRYP_KeyInitTypeDef structure that
 *       contains configuration information for CRYP Keys.
 * retval None
 */
void CRYP_KeyInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct) {
    /* Key Initialisation */
    CRYP->K0LR = CRYP_KeyInitStruct->CRYP_Key0Left;
    CRYP->K0RR = CRYP_KeyInitStruct->CRYP_Key0Right;
    CRYP->K1LR = CRYP_KeyInitStruct->CRYP_Key1Left;
    CRYP->K1RR = CRYP_KeyInitStruct->CRYP_Key1Right;
    CRYP->K2LR = CRYP_KeyInitStruct->CRYP_Key2Left;
    CRYP->K2RR = CRYP_KeyInitStruct->CRYP_Key2Right;
    CRYP->K3LR = CRYP_KeyInitStruct->CRYP_Key3Left;
    CRYP->K3RR = CRYP_KeyInitStruct->CRYP_Key3Right;
}

/**
 * Fills each CRYP_KeyInitStruct member with its default value.
 * param CRYP_KeyInitStruct: pointer to a CRYP_KeyInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void CRYP_KeyStructInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct) {
    CRYP_KeyInitStruct->CRYP_Key0Left = 0;
    CRYP_KeyInitStruct->CRYP_Key0Right = 0;
    CRYP_KeyInitStruct->CRYP_Key1Left = 0;
    CRYP_KeyInitStruct->CRYP_Key1Right = 0;
    CRYP_KeyInitStruct->CRYP_Key2Left = 0;
    CRYP_KeyInitStruct->CRYP_Key2Right = 0;
    CRYP_KeyInitStruct->CRYP_Key3Left = 0;
    CRYP_KeyInitStruct->CRYP_Key3Right = 0;
}

/**
 * Initializes CRYP Initialization Vectors(IV) according to the
 * specified parameters in CRYP_IVInitStruct.
 * param CRYP_IVInitStruct: pointer to a CRYP_IVInitTypeDef structure that
 *       contains configuration information for CRYP Initialization Vectors.
 * retval None
 */
void CRYP_IVInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct) {
    CRYP->IV0LR = CRYP_IVInitStruct->CRYP_IV0Left;
    CRYP->IV0RR = CRYP_IVInitStruct->CRYP_IV0Right;
    CRYP->IV1LR = CRYP_IVInitStruct->CRYP_IV1Left;
    CRYP->IV1RR = CRYP_IVInitStruct->CRYP_IV1Right;
}

/**
 * Fills each CRYP_IVInitStruct member with its default value.
 * param CRYP_IVInitStruct: pointer to a CRYP_IVInitTypeDef Initialization.
 * Vectors(IV) structure which will be initialized.
 * retval None
 */
void CRYP_IVStructInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct) {
    CRYP_IVInitStruct->CRYP_IV0Left  = 0;
    CRYP_IVInitStruct->CRYP_IV0Right = 0;
    CRYP_IVInitStruct->CRYP_IV1Left  = 0;
    CRYP_IVInitStruct->CRYP_IV1Right = 0;
}

/**
 * Flushes IN and OUT FIFOs (that is read/write pointers of FIFOs are reset)
 * The FIFOs must be flushed only when BUSY flag is reset.
 * param None
 * retval None
 */
void CRYP_FIFOFlush(void) {
    CRYP->CR |= CRYP_CR_FFLUSH; /* Reset read and write pointers of FIFOs */
}

/**
 * Enables or disables CRYP peripheral.
 * param NewState: new state of CRYP peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void CRYP_Cmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        CRYP->CR |= CRYP_CR_CRYPEN; /* Enable Cryptographic processor */
    } else {
        CRYP->CR &= ~CRYP_CR_CRYPEN; /* Disable Cryptographic processor */
    }
}

/**
 * Writes data in Data Input register (DIN).
 * After DIN register has been read once or several times,
 * FIFO must be flushed (using CRYP_FIFOFlush() function).
 * param Data: data to write in Data Input register
 * retval None
 */
void CRYP_DataIn(uint32_t Data) {
    CRYP->DR = Data;
}

/**
 * Returns last data entered into output FIFO.
 * param None
 * retval Last data entered into output FIFO.
 */
uint32_t CRYP_DataOut(void) {
    return CRYP->DOUT;
}

/**
 * Saves CRYP peripheral Context.
 * This function stops DMA transfer before to save context.
 * After restoring context, you have to enable DMA again (if DMA was
 * previously used).
 * param CRYP_ContextSave: pointer to a CRYP_Context structure that contains
 *       repository for current context.
 * param CRYP_KeyInitStruct: pointer to a CRYP_KeyInitTypeDef structure that
 *       contains configuration information for CRYP Keys.
 * retval None
 */
ErrorStatus CRYP_SaveContext(
    CRYP_Context* CRYP_ContextSave, CRYP_KeyInitTypeDef* CRYP_KeyInitStruct
) {
    __IO uint32_t timeout = 0;
    uint32_t ckeckmask = 0, bitstatus;
    ErrorStatus status = ERROR;

    /* Stop DMA transfers on IN FIFO by clearing DIEN bit in CRYP_DMACR */
    CRYP->DMACR &= ~(uint32_t) CRYP_DMACR_DIEN;
    /**
     * Wait until both IN and OUT FIFOs are empty
     * (IFEM=1 and OFNE=0 in CRYP_SR register) and
     * BUSY bit is cleared.
     */
    if (
        (
            CRYP->CR & (uint32_t) (
                CRYP_CR_ALGOMODE_TDES_ECB | CRYP_CR_ALGOMODE_TDES_CBC
            )
        ) != (uint32_t) 0
    ) {
        ckeckmask =  CRYP_SR_IFEM | CRYP_SR_BUSY;
    } else {
        ckeckmask =  CRYP_SR_IFEM | CRYP_SR_BUSY | CRYP_SR_OFNE;
    }
    do {
        bitstatus = CRYP->SR & ckeckmask;
        timeout++;
    } while ((timeout != MAX_TIMEOUT) && (bitstatus != CRYP_SR_IFEM));
    if ((CRYP->SR & ckeckmask) != CRYP_SR_IFEM) {
        status = ERROR;
    } else {
        /* Stop DMA transfers on OUT FIFO by 
           - writing DOEN bit to 0 in CRYP_DMACR register 
           - and clear CRYPEN bit. */
        CRYP->DMACR &= ~(uint32_t) CRYP_DMACR_DOEN;
        CRYP->CR &= ~(uint32_t) CRYP_CR_CRYPEN;
        /* Save current configuration (bits [9:2] in CRYP_CR register) */
        CRYP_ContextSave->CR_bits9to2 = CRYP->CR & (
            CRYP_CR_KEYSIZE | CRYP_CR_DATATYPE |
            CRYP_CR_ALGOMODE | CRYP_CR_ALGODIR
        );
        /* and, if not in ECB mode, initialization vectors. */
        CRYP_ContextSave->CRYP_IV0LR = CRYP->IV0LR;
        CRYP_ContextSave->CRYP_IV0RR = CRYP->IV0RR;
        CRYP_ContextSave->CRYP_IV1LR = CRYP->IV1LR;
        CRYP_ContextSave->CRYP_IV1RR = CRYP->IV1RR;
        /* save The key value */
        CRYP_ContextSave->CRYP_K0LR = CRYP_KeyInitStruct->CRYP_Key0Left;
        CRYP_ContextSave->CRYP_K0RR = CRYP_KeyInitStruct->CRYP_Key0Right;
        CRYP_ContextSave->CRYP_K1LR = CRYP_KeyInitStruct->CRYP_Key1Left;
        CRYP_ContextSave->CRYP_K1RR = CRYP_KeyInitStruct->CRYP_Key1Right;
        CRYP_ContextSave->CRYP_K2LR = CRYP_KeyInitStruct->CRYP_Key2Left;
        CRYP_ContextSave->CRYP_K2RR = CRYP_KeyInitStruct->CRYP_Key2Right;
        CRYP_ContextSave->CRYP_K3LR = CRYP_KeyInitStruct->CRYP_Key3Left;
        CRYP_ContextSave->CRYP_K3RR = CRYP_KeyInitStruct->CRYP_Key3Right;
        /**
         * When needed, save DMA status (pointers for IN and OUT messages,
         * number of remaining bytes, etc.) 
         */
        status = SUCCESS;
    }
    return status;
}

/**
 * Restores CRYP peripheral Context.
 * Since teh DMA transfer is stopped in CRYP_SaveContext() function,
 * after restoring context, you have to enable DMA again (if the
 * DMA was previously used).
 * param CRYP_ContextRestore: pointer to a CRYP_Context structure that contains
 * repository for saved context.
 * The data that were saved during context saving must be rewrited into
 * IN FIFO.
 * retval None
 */
void CRYP_RestoreContext(CRYP_Context* CRYP_ContextRestore) {
    /* Configure processor with saved configuration */
    CRYP->CR = CRYP_ContextRestore->CR_bits9to2;
    /* restore The key value */
    CRYP->K0LR = CRYP_ContextRestore->CRYP_K0LR;
    CRYP->K0RR = CRYP_ContextRestore->CRYP_K0RR;
    CRYP->K1LR = CRYP_ContextRestore->CRYP_K1LR;
    CRYP->K1RR = CRYP_ContextRestore->CRYP_K1RR;
    CRYP->K2LR = CRYP_ContextRestore->CRYP_K2LR;
    CRYP->K2RR = CRYP_ContextRestore->CRYP_K2RR;
    CRYP->K3LR = CRYP_ContextRestore->CRYP_K3LR;
    CRYP->K3RR = CRYP_ContextRestore->CRYP_K3RR;
    /* and initialization vectors. */
    CRYP->IV0LR = CRYP_ContextRestore->CRYP_IV0LR;
    CRYP->IV0RR = CRYP_ContextRestore->CRYP_IV0RR;
    CRYP->IV1LR = CRYP_ContextRestore->CRYP_IV1LR;
    CRYP->IV1RR = CRYP_ContextRestore->CRYP_IV1RR;
    /* Enable cryptographic processor */
    CRYP->CR |= CRYP_CR_CRYPEN;
}

/**
 * Enables or disables CRYP DMA interface.
 * param CRYP_DMAReq: specifies CRYP DMA transfer request to be enabled
 * or disabled.
 *   This parameter can be any combination of following values:
 *       arg CRYP_DMAReq_DataOUT: DMA for outgoing(Tx) data transfer
 *       arg CRYP_DMAReq_DataIN: DMA for incoming(Rx) data transfer
 * param NewState: new state of selected CRYP DMA transfer request.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void CRYP_DMACmd(uint8_t CRYP_DMAReq, FunctionalState NewState) {
    assert_param(IS_CRYP_DMAREQ(CRYP_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        CRYP->DMACR |= CRYP_DMAReq; /* Enable selected CRYP DMA request */
    } else {
        /* Disable selected CRYP DMA request */
        CRYP->DMACR &= (uint8_t) ~CRYP_DMAReq;
    }
}

/**
 * Enables or disables specified CRYP interrupts.
 * param CRYP_IT: specifies CRYP interrupt source to be enabled or disabled.
 *   This parameter can be any combination of following values:
 *       arg CRYP_IT_INI: Input FIFO interrupt
 *       arg CRYP_IT_OUTI: Output FIFO interrupt
 * param NewState: new state of specified CRYP interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void CRYP_ITConfig(uint8_t CRYP_IT, FunctionalState NewState) {
    assert_param(IS_CRYP_CONFIG_IT(CRYP_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        CRYP->IMSCR |= CRYP_IT; /* Enable selected CRYP interrupt */
    } else {
        CRYP->IMSCR &= (uint8_t) ~CRYP_IT; /* Disable selected CRYP interr */
    }
}

/**
 * Checks whether specified CRYP interrupt has occurred or not.
 * This function checks status of masked interrupt (i.e 
 * interrupt should be previously enabled).
 * param CRYP_IT: specifies CRYP (masked) interrupt source to check.
 *   This parameter can be one of following values:
 *       arg CRYP_IT_INI: Input FIFO interrupt
 *       arg CRYP_IT_OUTI: Output FIFO interrupt
 * retval The new state of CRYP_IT (SET or RESET).
 */
ITStatus CRYP_GetITStatus(uint8_t CRYP_IT) {
    ITStatus bitstatus = RESET;

    assert_param(IS_CRYP_GET_IT(CRYP_IT));
    /* Check status of specified CRYP interrupt */
    if ((CRYP->MISR &  CRYP_IT) != (uint8_t) RESET) {
        bitstatus = SET; /* CRYP_IT is set */
    } else {
        bitstatus = RESET; /* CRYP_IT is reset */
    }
    return bitstatus; /* Return CRYP_IT status */
}

/**
 * Checks whether specified CRYP flag is set or not.
 * param CRYP_FLAG: specifies CRYP flag to check.
 *   This parameter can be one of following values:
 *       arg CRYP_FLAG_IFEM: Input FIFO Empty flag.
 *       arg CRYP_FLAG_IFNF: Input FIFO Not Full flag.
 *       arg CRYP_FLAG_OFNE: Output FIFO Not Empty flag.
 *       arg CRYP_FLAG_OFFU: Output FIFO Full flag.
 *       arg CRYP_FLAG_BUSY: Busy flag.
 *       arg CRYP_FLAG_OUTRIS: Output FIFO raw interrupt flag.
 *       arg CRYP_FLAG_INRIS: Input FIFO raw interrupt flag.
 * retval The new state of CRYP_FLAG (SET or RESET).
 */
FlagStatus CRYP_GetFlagStatus(uint8_t CRYP_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tempreg = 0;

    assert_param(IS_CRYP_GET_FLAG(CRYP_FLAG));
    /* check if FLAG is in RISR register */
    if ((CRYP_FLAG & FLAG_MASK) != 0x00) {
        tempreg = CRYP->RISR;
    } else {
        tempreg = CRYP->SR;
    }
    /* Check status of specified CRYP flag */
    if ((tempreg & CRYP_FLAG ) != (uint8_t) RESET) {
        bitstatus = SET; /* CRYP_FLAG is set */
    } else {
        bitstatus = RESET; /* CRYP_FLAG is reset */
    }
    return bitstatus; /* Return CRYP_FLAG status */
}

