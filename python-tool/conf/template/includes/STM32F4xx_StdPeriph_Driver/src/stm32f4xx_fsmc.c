/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_fsmc.c
 * 
 * This file provides firmware functions to managefollowing 
 * functionalities ofFSMC peripheral:
 *     - Interface with SRAM, PSRAM, NOR and OneNAND memories
 *     - Interface with NAND memories
 *     - Interface with 16-bit PC Card compatible memories
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_fsmc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_fsmc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* FSMC BCRx Mask */
#define BCR_MBKEN_SET ((uint32_t) 0x00000001)
#define BCR_MBKEN_RESET ((uint32_t) 0x000FFFFE)
#define BCR_FACCEN_SET ((uint32_t) 0x00000040)

/* FSMC PCRx Mask */
#define PCR_PBKEN_SET ((uint32_t) 0x00000004)
#define PCR_PBKEN_RESET ((uint32_t) 0x000FFFFB)
#define PCR_ECCEN_SET ((uint32_t) 0x00000040)
#define PCR_ECCEN_RESET ((uint32_t) 0x000FFFBF)
#define PCR_MEMORYTYPE_NAND ((uint32_t) 0x00000008)

/**
 * DeinitializesFSMC NOR/SRAM Banks registers to their default reset values.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank1_NORSRAM1: FSMC Bank1 NOR/SRAM1
 *       arg FSMC_Bank1_NORSRAM2: FSMC Bank1 NOR/SRAM2
 *       arg FSMC_Bank1_NORSRAM3: FSMC Bank1 NOR/SRAM3
 *       arg FSMC_Bank1_NORSRAM4: FSMC Bank1 NOR/SRAM4
 * retval None
 */
void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank) {
    assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));
    /* FSMC_Bank1_NORSRAM1 */
    if (FSMC_Bank == FSMC_Bank1_NORSRAM1) {
        FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030DB;
    } else {
        FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030D2;
    }
    FSMC_Bank1->BTCR[FSMC_Bank + 1] = 0x0FFFFFFF;
    FSMC_Bank1E->BWTR[FSMC_Bank] = 0x0FFFFFFF;
}

/**
 * InitializesFSMC NOR/SRAM Banks according tospecified parameters
 * inFSMC_NORSRAMInitStruct.
 * param FSMC_NORSRAMInitStruct : pointer to FSMC_NORSRAMInitTypeDef structure
 *       that containsconfiguration info for FSMC NOR/SRAM specified Banks.
 * retval None
 */
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct) {
    assert_param(IS_FSMC_NORSRAM_BANK(FSMC_NORSRAMInitStruct->FSMC_Bank));
    assert_param(IS_FSMC_MUX(FSMC_NORSRAMInitStruct->FSMC_DataAddressMux));
    assert_param(IS_FSMC_MEMORY(FSMC_NORSRAMInitStruct->FSMC_MemoryType));
    assert_param(
        IS_FSMC_MEMORY_WIDTH(FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth)
    );
    assert_param(
        IS_FSMC_BURSTMODE(FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode)
    );
    assert_param(
        IS_FSMC_ASYNWAIT(FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait)
    );
    assert_param(
        IS_FSMC_WAIT_POLARITY(FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity)
    );
    assert_param(IS_FSMC_WRAP_MODE(FSMC_NORSRAMInitStruct->FSMC_WrapMode));
    assert_param(
        IS_FSMC_WAIT_SIGNAL_ACTIVE(
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive
        )
    );
    assert_param(
        IS_FSMC_WRITE_OPERATION(FSMC_NORSRAMInitStruct->FSMC_WriteOperation)
    );
    assert_param(
        IS_FSMC_WAITE_SIGNAL(FSMC_NORSRAMInitStruct->FSMC_WaitSignal)
    );
    assert_param(
        IS_FSMC_EXTENDED_MODE(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode)
    );
    assert_param(IS_FSMC_WRITE_BURST(FSMC_NORSRAMInitStruct->FSMC_WriteBurst));
    assert_param(
        IS_FSMC_ADDRESS_SETUP_TIME(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime
        )
    );
    assert_param(
        IS_FSMC_ADDRESS_HOLD_TIME(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime
        )
    );
    assert_param(
        IS_FSMC_DATASETUP_TIME(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime
        )
    );
    assert_param(
        IS_FSMC_TURNAROUND_TIME(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration
        )
    );
    assert_param(
        IS_FSMC_CLK_DIV(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision
        )
    );
    assert_param(
        IS_FSMC_DATA_LATENCY(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency
        )
    );
    assert_param(
        IS_FSMC_ACCESS_MODE(
            FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode
        )
    );
    /* Bank1 NOR/SRAM control register configuration */
    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] = (uint32_t) (
        FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
        FSMC_NORSRAMInitStruct->FSMC_MemoryType |
        FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
        FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
        FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait |
        FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
        FSMC_NORSRAMInitStruct->FSMC_WrapMode |
        FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
        FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
        FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
        FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
        FSMC_NORSRAMInitStruct->FSMC_WriteBurst
    );
    if (FSMC_NORSRAMInitStruct->FSMC_MemoryType == FSMC_MemoryType_NOR) {
        FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |=
            (uint32_t) BCR_FACCEN_SET;
    }
    /* Bank1 NOR/SRAM timing register configuration */
    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank+1] = (uint32_t) (
        FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
        (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
        (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
        (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
        (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
        (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
        FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode
    );
    /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if (FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == FSMC_ExtendedMode_Enable) {
        assert_param(
            IS_FSMC_ADDRESS_SETUP_TIME(
                FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime
            )
        );
        assert_param(
            IS_FSMC_ADDRESS_HOLD_TIME(
                FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime
            )
        );
        assert_param(
            IS_FSMC_DATASETUP_TIME(
                FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime
            )
        );
        assert_param(
            IS_FSMC_CLK_DIV(
                FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision
            )
        );
        assert_param(
            IS_FSMC_DATA_LATENCY(
                FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency
            )
        );
        assert_param(
            IS_FSMC_ACCESS_MODE(
                FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode
            )
        );
        FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = (uint32_t) (
            FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
            (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4 )|
            (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
            (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision << 20) |
            (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency << 24) |
            FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode
        );
    } else {
        FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
    }
}

/**
 * Fills each FSMC_NORSRAMInitStruct member with its default value.
 * param FSMC_NORSRAMInitStruct: pointer to a FSMC_NORSRAMInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct) {
    /* Reset NOR/SRAM Init structure parameters values */
    FSMC_NORSRAMInitStruct->FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStruct->FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
    FSMC_NORSRAMInitStruct->FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStruct->FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStruct->FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStruct->FSMC_WaitSignal = FSMC_WaitSignal_Enable;
    FSMC_NORSRAMInitStruct->FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStruct->FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime = 0xFF;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode = FSMC_AccessMode_A; 
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime = 0xFF;
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency = 0xF;
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode = FSMC_AccessMode_A;
}

/**
 * Enables or disablesspecified NOR/SRAM Memory Bank.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank1_NORSRAM1: FSMC Bank1 NOR/SRAM1  
 *       arg FSMC_Bank1_NORSRAM2: FSMC Bank1 NOR/SRAM2 
 *       arg FSMC_Bank1_NORSRAM3: FSMC Bank1 NOR/SRAM3 
 *       arg FSMC_Bank1_NORSRAM4: FSMC Bank1 NOR/SRAM4 
 * param NewState: new state ofFSMC_Bank. Parameter can be: ENABLE/DISABLE.
 * retval None
 */
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState) {
    assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enableselected NOR/SRAM Bank by settingPBKEN bit inBCRx register */
        FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_SET;
    } else {
        /* Disableselected NOR/SRAM Bank by clearingPBKEN bit inBCRx reg */
        FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_RESET;
    }
}

/**
 * DeinitializesFSMC NAND Banks registers to their default reset values.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND 
 * retval None
 */
void FSMC_NANDDeInit(uint32_t FSMC_Bank) {
    assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
    if (FSMC_Bank == FSMC_Bank2_NAND) {
        /* SetFSMC_Bank2 registers to their reset values */
        FSMC_Bank2->PCR2 = 0x00000018;
        FSMC_Bank2->SR2 = 0x00000040;
        FSMC_Bank2->PMEM2 = 0xFCFCFCFC;
        FSMC_Bank2->PATT2 = 0xFCFCFCFC;  
    } else {
        /* SetFSMC_Bank3 registers to their reset values */
        FSMC_Bank3->PCR3 = 0x00000018;
        FSMC_Bank3->SR3 = 0x00000040;
        FSMC_Bank3->PMEM3 = 0xFCFCFCFC;
        FSMC_Bank3->PATT3 = 0xFCFCFCFC; 
    }
}

/**
 * InitializesFSMC NAND Banks according tospecified parameters
 * inFSMC_NANDInitStruct.
 * param FSMC_NANDInitStruct : pointer to a FSMC_NANDInitTypeDef structure that
 *       containsconfiguration information forFSMC NAND specified Banks.
 * retval None
 */
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct) {
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    assert_param(IS_FSMC_NAND_BANK(FSMC_NANDInitStruct->FSMC_Bank));
    assert_param(IS_FSMC_WAIT_FEATURE(FSMC_NANDInitStruct->FSMC_Waitfeature));
    assert_param(
        IS_FSMC_MEMORY_WIDTH(FSMC_NANDInitStruct->FSMC_MemoryDataWidth)
    );
    assert_param(IS_FSMC_ECC_STATE(FSMC_NANDInitStruct->FSMC_ECC));
    assert_param(IS_FSMC_ECCPAGE_SIZE(FSMC_NANDInitStruct->FSMC_ECCPageSize));
    assert_param(IS_FSMC_TCLR_TIME(FSMC_NANDInitStruct->FSMC_TCLRSetupTime));
    assert_param(IS_FSMC_TAR_TIME(FSMC_NANDInitStruct->FSMC_TARSetupTime));
    assert_param(
        IS_FSMC_SETUP_TIME(
            FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime
        )
    );
    assert_param(
        IS_FSMC_WAIT_TIME(
            FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime
        )
    );
    assert_param(
        IS_FSMC_HOLD_TIME(
            FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime
        )
    );
    assert_param(
        IS_FSMC_HIZ_TIME(
            FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime
        )
    );
    assert_param(
        IS_FSMC_SETUP_TIME(
            FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime
        )
    );
    assert_param(
        IS_FSMC_WAIT_TIME(
            FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime
        )
    );
    assert_param(
        IS_FSMC_HOLD_TIME(
            FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime
        )
    );
    assert_param(
        IS_FSMC_HIZ_TIME(
            FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime
        )
    );
    /* Settmppcr value according to FSMC_NANDInitStruct parameters */
    tmppcr = (uint32_t) (
        FSMC_NANDInitStruct->FSMC_Waitfeature |
        PCR_MEMORYTYPE_NAND |
        FSMC_NANDInitStruct->FSMC_MemoryDataWidth |
        FSMC_NANDInitStruct->FSMC_ECC |
        FSMC_NANDInitStruct->FSMC_ECCPageSize |
        (FSMC_NANDInitStruct->FSMC_TCLRSetupTime << 9 ) |
        (FSMC_NANDInitStruct->FSMC_TARSetupTime << 13)
    );
    /* Set tmppmem value according to FSMC_CommonSpaceTimingStructure parameters */
    tmppmem = (uint32_t) (
        FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
        (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
        (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
        (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24)
    );
    /* Set tmppatt value according to FSMC_AttributeSpaceTimingStructure parameters */
    tmppatt = (uint32_t) (
        FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
        (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
        (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
        (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24)
    );
    if (FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND) {
        /* FSMC_Bank2_NAND registers configuration */
        FSMC_Bank2->PCR2 = tmppcr;
        FSMC_Bank2->PMEM2 = tmppmem;
        FSMC_Bank2->PATT2 = tmppatt;
    } else {
        /* FSMC_Bank3_NAND registers configuration */
        FSMC_Bank3->PCR3 = tmppcr;
        FSMC_Bank3->PMEM3 = tmppmem;
        FSMC_Bank3->PATT3 = tmppatt;
    }
}


/**
 * Fills each FSMC_NANDInitStruct member with its default value.
 * param FSMC_NANDInitStruct: pointer to a FSMC_NANDInitTypeDef structure which
 *       will be initialized.
 * retval None
 */
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct) {
    /* Reset NAND Init structure parameters values */
    FSMC_NANDInitStruct->FSMC_Bank = FSMC_Bank2_NAND;
    FSMC_NANDInitStruct->FSMC_Waitfeature = FSMC_Waitfeature_Disable;
    FSMC_NANDInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NANDInitStruct->FSMC_ECC = FSMC_ECC_Disable;
    FSMC_NANDInitStruct->FSMC_ECCPageSize = FSMC_ECCPageSize_256Bytes;
    FSMC_NANDInitStruct->FSMC_TCLRSetupTime = 0x0;
    FSMC_NANDInitStruct->FSMC_TARSetupTime = 0x0;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}

/**
 * Enables or disablesspecified NAND Memory Bank.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 * param NewState: new state ofFSMC_Bank. Parameter can be: ENABLE or DISABLE.
 * retval None
 */
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState) {
    assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enableselected NAND Bank by settingPBKEN bit inPCRx register */
        if (FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 |= PCR_PBKEN_SET;
        } else {
            FSMC_Bank3->PCR3 |= PCR_PBKEN_SET;
        }
    } else {
        /* Disableselected NAND Bank by clearingPBKEN bit inPCRx register */
        if (FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 &= PCR_PBKEN_RESET;
        } else {
            FSMC_Bank3->PCR3 &= PCR_PBKEN_RESET;
        }
    }
}
/**
 * Enables or disablesFSMC NAND ECC feature.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 * param NewState: new state ofFSMC NAND ECC feature.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState) {
    assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /**
         * Enableselected NAND Bank ECC function by
         * settingECCEN bit inPCRx register.
         */
        if (FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 |= PCR_ECCEN_SET;
        } else {
            FSMC_Bank3->PCR3 |= PCR_ECCEN_SET;
        }
    } else {
        /**
         * Disableselected NAND Bank ECC function by
         * clearingECCEN bit inPCRx register.
         */
        if (FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 &= PCR_ECCEN_RESET;
        } else {
            FSMC_Bank3->PCR3 &= PCR_ECCEN_RESET;
        }
    }
}

/**
 * Returnserror correction code register value.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 * retval The Error Correction Code (ECC) value.
 */
uint32_t FSMC_GetECC(uint32_t FSMC_Bank) {
    uint32_t eccval = 0x00000000;

    if (FSMC_Bank == FSMC_Bank2_NAND) {
        eccval = FSMC_Bank2->ECCR2; /* GetECCR2 register value */
    } else {
        eccval = FSMC_Bank3->ECCR3; /* GetECCR3 register value */
    }
    return(eccval); /* Returnerror correction code value */
}

/**
 * DeinitializesFSMC PCCARD Bank registers to their default reset values.
 * param None
 * retval None
 */
void FSMC_PCCARDDeInit(void) {
    /* SetFSMC_Bank4 registers to their reset values */
    FSMC_Bank4->PCR4 = 0x00000018;
    FSMC_Bank4->SR4 = 0x00000000;
    FSMC_Bank4->PMEM4 = 0xFCFCFCFC;
    FSMC_Bank4->PATT4 = 0xFCFCFCFC;
    FSMC_Bank4->PIO4 = 0xFCFCFCFC;
}

/**
 * InitializesFSMC PCCARD Bank according tospecified parameters
 * inFSMC_PCCARDInitStruct.
 * param FSMC_PCCARDInitStruct : pointer to a FSMC_PCCARDInitTypeDef structure
 *       that containsconfiguration information forFSMC PCCARD Bank.
 * retval None
 */
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct) {
    assert_param(
        IS_FSMC_WAIT_FEATURE(FSMC_PCCARDInitStruct->FSMC_Waitfeature)
    );
    assert_param(IS_FSMC_TCLR_TIME(FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime));
    assert_param(IS_FSMC_TAR_TIME(FSMC_PCCARDInitStruct->FSMC_TARSetupTime));
    assert_param(
        IS_FSMC_SETUP_TIME(
            FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime
        )
    );
    assert_param(
        IS_FSMC_WAIT_TIME(
            FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime
        )
    );
    assert_param(
        IS_FSMC_HOLD_TIME(
            FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime
        )
    );
    assert_param(
        IS_FSMC_HIZ_TIME(
            FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime
        )
    );
    assert_param(
        IS_FSMC_SETUP_TIME(
            FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime
        )
    );
    assert_param(
        IS_FSMC_WAIT_TIME(
            FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime
        )
    );
    assert_param(
        IS_FSMC_HOLD_TIME(
            FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime
        )
    );
    assert_param(
        IS_FSMC_HIZ_TIME(
            FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime
        )
    );
    assert_param(
        IS_FSMC_SETUP_TIME(
            FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime
        )
    );
    assert_param(
        IS_FSMC_WAIT_TIME(
            FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime
        )
    );
    assert_param(
        IS_FSMC_HOLD_TIME(
            FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime
        )
    );
    assert_param(
        IS_FSMC_HIZ_TIME(
            FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime
        )
    );
    /* SetPCR4 register value according to FSMC_PCCARDInitStruct parameters */
    FSMC_Bank4->PCR4 = (uint32_t) (
        FSMC_PCCARDInitStruct->FSMC_Waitfeature |
        FSMC_MemoryDataWidth_16b |
        (FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime << 9) |
        (FSMC_PCCARDInitStruct->FSMC_TARSetupTime << 13)
    );
    /* Set PMEM4 register value according to FSMC_CommonSpaceTimingStructure parameters */
    FSMC_Bank4->PMEM4 = (uint32_t) (
        FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
        (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
        (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
        (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24)
    );
    /* Set PATT4 register value according to FSMC_AttributeSpaceTimingStructure parameters */
    FSMC_Bank4->PATT4 = (uint32_t) (
        FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
        (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
        (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
        (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24)
    );
    /* Set PIO4 register value according to FSMC_IOSpaceTimingStructure parameters */
    FSMC_Bank4->PIO4 = (uint32_t) (
        FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime |
        (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
        (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
        (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime << 24)
    );
}

/**
 * Fills each FSMC_PCCARDInitStruct member with its default value.
 * param FSMC_PCCARDInitStruct: pointer to a FSMC_PCCARDInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct) {
    /* Reset PCCARD Init structure parameters values */
    FSMC_PCCARDInitStruct->FSMC_Waitfeature = FSMC_Waitfeature_Disable;
    FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime = 0x0;
    FSMC_PCCARDInitStruct->FSMC_TARSetupTime = 0x0;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}

/**
 * Enables or disablesPCCARD Memory Bank.
 * param NewState: new state ofPCCARD Memory Bank.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void FSMC_PCCARDCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* EnablePCCARD Bank by settingPBKEN bit inPCR4 register */
        FSMC_Bank4->PCR4 |= PCR_PBKEN_SET;
    } else {
        /* DisablePCCARD Bank by clearingPBKEN bit inPCR4 register */
        FSMC_Bank4->PCR4 &= PCR_PBKEN_RESET;
    }
}

/**
 * Enables or disablesspecified FSMC interrupts.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 *       arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
 * param FSMC_IT: specifiesFSMC interrupt sources to be enabled/disabled.
 *   This parameter can be any combination offollowing values:
 *       arg FSMC_IT_RisingEdge: Rising edge detection interrupt.
 *       arg FSMC_IT_Level: Level edge detection interrupt.
 *       arg FSMC_IT_FallingEdge: Falling edge detection interrupt.
 * param NewState: new state ofspecified FSMC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void FSMC_ITConfig(
    uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState
) {
    assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
    assert_param(IS_FSMC_IT(FSMC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enableselected FSMC_Bank2 interrupts */
        if (FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->SR2 |= FSMC_IT;
        } else if (FSMC_Bank == FSMC_Bank3_NAND) {
            FSMC_Bank3->SR3 |= FSMC_IT;
        } else {
            FSMC_Bank4->SR4 |= FSMC_IT;
        }
    } else {
        /* Disableselected FSMC_Bank2 interrupts */
        if (FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->SR2 &= (uint32_t) ~FSMC_IT;
        } else if (FSMC_Bank == FSMC_Bank3_NAND) {
            FSMC_Bank3->SR3 &= (uint32_t) ~FSMC_IT;
        } else {
            FSMC_Bank4->SR4 &= (uint32_t) ~FSMC_IT;
        }
    }
}

/**
 * Checks whetherspecified FSMC flag is set or not.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 *       arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
 * param FSMC_FLAG: specifiesflag to check.
 *   This parameter can be one offollowing values:
 *       arg FSMC_FLAG_RisingEdge: Rising edge detection Flag.
 *       arg FSMC_FLAG_Level: Level detection Flag.
 *       arg FSMC_FLAG_FallingEdge: Falling edge detection Flag.
 *       arg FSMC_FLAG_FEMPT: Fifo empty Flag. 
 * retval The new state of FSMC_FLAG (SET or RESET).
 */
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tmpsr = 0x00000000;

    assert_param(IS_FSMC_GETFLAG_BANK(FSMC_Bank));
    assert_param(IS_FSMC_GET_FLAG(FSMC_FLAG));
    if (FSMC_Bank == FSMC_Bank2_NAND) {
        tmpsr = FSMC_Bank2->SR2;
    } else if(FSMC_Bank == FSMC_Bank3_NAND) {
        tmpsr = FSMC_Bank3->SR3;
    } else {
        tmpsr = FSMC_Bank4->SR4;
    }
    /* Getflag status */
    if ((tmpsr & FSMC_FLAG) != (uint16_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus; /* Returnflag status */
}

/**
 * ClearsFSMC's pending flags.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 *       arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
 * param FSMC_FLAG: specifiesflag to clear.
 *   This parameter can be any combination offollowing values:
 *       arg FSMC_FLAG_RisingEdge: Rising edge detection Flag.
 *       arg FSMC_FLAG_Level: Level detection Flag.
 *       arg FSMC_FLAG_FallingEdge: Falling edge detection Flag.
 * retval None
 */
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG) {
    assert_param(IS_FSMC_GETFLAG_BANK(FSMC_Bank));
    assert_param(IS_FSMC_CLEAR_FLAG(FSMC_FLAG));
    if (FSMC_Bank == FSMC_Bank2_NAND) {
        FSMC_Bank2->SR2 &= ~FSMC_FLAG;
    } else if(FSMC_Bank == FSMC_Bank3_NAND) {
        FSMC_Bank3->SR3 &= ~FSMC_FLAG;
    } else {
        FSMC_Bank4->SR4 &= ~FSMC_FLAG;
    }
}

/**
 * Checks whetherspecified FSMC interrupt has occurred or not.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 *       arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
 * param FSMC_IT: specifiesFSMC interrupt source to check.
 *   This parameter can be one offollowing values:
 *       arg FSMC_IT_RisingEdge: Rising edge detection interrupt.
 *       arg FSMC_IT_Level: Level edge detection interrupt.
 *       arg FSMC_IT_FallingEdge: Falling edge detection interrupt.
 * retval The new state of FSMC_IT (SET or RESET).
 */
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0;

    assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
    assert_param(IS_FSMC_GET_IT(FSMC_IT));
    if (FSMC_Bank == FSMC_Bank2_NAND) {
    tmpsr = FSMC_Bank2->SR2;
    } else if (FSMC_Bank == FSMC_Bank3_NAND) {
        tmpsr = FSMC_Bank3->SR3;
    } else {
        tmpsr = FSMC_Bank4->SR4;
    }
    itstatus = tmpsr & FSMC_IT;
    itenable = tmpsr & (FSMC_IT >> 3);
    if ((itstatus != (uint32_t) RESET)  && (itenable != (uint32_t) RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * ClearsFSMC's interrupt pending bits.
 * param FSMC_Bank: specifiesFSMC Bank to be used
 *   This parameter can be one offollowing values:
 *       arg FSMC_Bank2_NAND: FSMC Bank2 NAND 
 *       arg FSMC_Bank3_NAND: FSMC Bank3 NAND
 *       arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
 * param FSMC_IT: specifiesinterrupt pending bit to clear.
 *   This parameter can be any combination offollowing values:
 *       arg FSMC_IT_RisingEdge: Rising edge detection interrupt.
 *       arg FSMC_IT_Level: Level edge detection interrupt.
 *       arg FSMC_IT_FallingEdge: Falling edge detection interrupt.
 * retval None
 */
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT) {
    assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
    assert_param(IS_FSMC_IT(FSMC_IT));
    if (FSMC_Bank == FSMC_Bank2_NAND) {
        FSMC_Bank2->SR2 &= ~(FSMC_IT >> 3);
    } else if (FSMC_Bank == FSMC_Bank3_NAND) {
        FSMC_Bank3->SR3 &= ~(FSMC_IT >> 3);
    } else {
        FSMC_Bank4->SR4 &= ~(FSMC_IT >> 3);
    }
}

