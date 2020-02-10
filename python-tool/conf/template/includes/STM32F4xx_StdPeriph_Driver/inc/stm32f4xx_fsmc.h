/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_fsmc.h
 * 
 * This file contains all functions prototypes for FSMC firmware library.
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

#ifndef __STM32F4xx_FSMC_H
#define __STM32F4xx_FSMC_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    uint32_t FSMC_AddressSetupTime; /* Defines number of HCLK cycles to
                                       configure duration of address setup
                                       time. Parameter can be a value between
                                       0 and 0xF. Parameter is not used with
                                       synchronous NOR Flash memories. */
    uint32_t FSMC_AddressHoldTime; /* Defines number of HCLK cycles to
                                      configure duration of address hold time.
                                      Parameter can be value between 0 and 0xF.
                                      Parameter is not used with synchronous
                                      NOR Flash memories.*/
    uint32_t FSMC_DataSetupTime; /* Defines number of HCLK cycles to configure
                                    duration of data setup time. Parameter
                                    can be a value between 0 and 0xFF.
                                    Parameter is used for SRAMs, ROMs and
                                    asynchronous multiplexed NOR Flash
                                    memories. */
    uint32_t FSMC_BusTurnAroundDuration; /* Defines number of HCLK cycles to
                                            configure duration of bus
                                            turnaround. Parameter can be a
                                            value between 0 and 0xF.
                                            This parameter is only used for
                                            multiplexed NOR Flash memories. */
    uint32_t FSMC_CLKDivision; /* Defines period of CLK clock output signal,
                                  expressed in number of HCLK cycles.
                                  Parameter can be a value between 1 and 0xF.
                                  Parameter is not used for asynchronous NOR
                                  Flash, SRAM or ROM accesses. */
    uint32_t FSMC_DataLatency; /* Defines number of memory clock cycles to
                                  issue to memory before getting first data.
                                  The parameter value depends on memory type
                                  as shown below:
                                  - It must be set to 0 in case of a CRAM
                                  - It is don't care in asynchronous NOR,
                                    SRAM or ROM accesses
                                  - It may assume a value between 0 and 0xF
                                    in NOR Flash memories
                                  with synchronous burst mode enable */
    uint32_t FSMC_AccessMode; /* Specifies asynchronous access mode.
                                 Parameter can be value of FSMC_Access_Mode */
} FSMC_NORSRAMTimingInitTypeDef;

typedef struct {
    uint32_t FSMC_Bank; /* Specifies NOR/SRAM memory bank that will be used.
                           Parameter can be a value of FSMC_NORSRAM_Bank */
    uint32_t FSMC_DataAddressMux; /* Specifies whether address and data values
                                     are multiplexed on databus or not.
                                     Parameter can be a value of
                                     FSMC_Data_Address_Bus_Multiplexing */
    uint32_t FSMC_MemoryType; /* Specifies type of external memory attached to
                                 corresponding memory bank. Parameter can be
                                 value of FSMC_Memory_Type */
    uint32_t FSMC_MemoryDataWidth; /* Specifies external memory device width.
                                      Parameter can be a value of
                                      FSMC_Data_Width */
    uint32_t FSMC_BurstAccessMode; /* Enables or disables burst access mode
                                      for Flash memory, valid only with
                                      synchronous burst Flash memories.
                                      Parameter can be a value of
                                      FSMC_Burst_Access_Mode */
    uint32_t FSMC_AsynchronousWait; /* Enables or disables wait signal during
                                       asynchronous transfers, valid only with
                                       asynchronous Flash memories.
                                       Parameter can be a value of
                                       FSMC_AsynchronousWait */
    uint32_t FSMC_WaitSignalPolarity; /* Specifies wait signal polarity, valid
                                         only when accessing Flash memory in
                                         burst mode. Parameter can be a value
                                         of FSMC_Wait_Signal_Polarity */
    uint32_t FSMC_WrapMode; /* Enables or disables Wrapped burst access mode
                               for Flash memory, valid only when accessing
                               Flash memories in burst mode. Parameter can be
                               a value of FSMC_Wrap_Mode */
    uint32_t FSMC_WaitSignalActive; /* Specifies if wait signal is asserted by
                                       memory one clock cycle before wait
                                       state or during wait state, valid only
                                       when accessing memories in burst mode.
                                       Parameter can be a value of
                                       FSMC_Wait_Timing */
    uint32_t FSMC_WriteOperation; /* Enables or disables write operation in
                                     selected bank by FSMC. Parameter can be a
                                     value of FSMC_Write_Operation */
    uint32_t FSMC_WaitSignal; /* Enables or disables wait-state insertion via
                                 wait signal, valid for Flash memory access in
                                 burst mode. Parameter can be a value of
                                 FSMC_Wait_Signal */
    uint32_t FSMC_ExtendedMode; /* Enables or disables extended mode.
                                   Parameter can be a value of
                                   FSMC_Extended_Mode */
    uint32_t FSMC_WriteBurst; /* Enables or disables write burst operation.
                                 Parameter can be value of FSMC_Write_Burst */
    /* Timing Parameters for write/read access if ExtendedMode is not used */
    FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;
    /* Timing Parameters for write access if ExtendedMode is used */
    FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;
} FSMC_NORSRAMInitTypeDef;

typedef struct {
    uint32_t FSMC_SetupTime; /* Defines number of HCLK cycles to setup address
                                before command assertion for NAND-Flash read
                                or write access to common/Attribute or I/O
                                memory space (depending on memory space
                                timing to be configured). parameter can be a
                                value between 0 and 0xFF.*/
    uint32_t FSMC_WaitSetupTime; /* Defines minimum number of HCLK cycles to
                                    assert command for NAND-Flash read or
                                    write access to common/Attribute or I/O
                                    memory space (depending on memory space
                                    timing to be configured). Parameter can
                                    be a number between 0x00 and 0xFF */
    uint32_t FSMC_HoldSetupTime; /* Defines number of HCLK clock cycles to
                                    hold address (and data for write access)
                                    after command deassertion for NAND-Flash
                                    read or write access to common/Attribute
                                    or I/O memory space (depending on memory
                                    space timing to be configured). Parameter
                                    can be a number between 0x00 and 0xFF */
    uint32_t FSMC_HiZSetupTime; /* Defines number of HCLK clock cycles during
                                   which databus is kept in HiZ after start of
                                   a NAND-Flash write access to
                                   common/Attribute or I/O memory space
                                   (depending on memory space timing to be
                                   configured). Parameter can be a number
                                   between 0x00 and 0xFF */
} FSMC_NAND_PCCARDTimingInitTypeDef;

typedef struct {
    uint32_t FSMC_Bank; /* Specifies NAND memory bank that will be used.
                           Parameter can be a value of FSMC_NAND_Bank */
    uint32_t FSMC_Waitfeature; /* Enables or disables Wait feature for NAND
                                  Memory Bank. Parameter can be any value of
                                  FSMC_Wait_feature */
    uint32_t FSMC_MemoryDataWidth; /* Specifies external memory device width.
                                      Parameter can be any value of
                                      FSMC_Data_Width */
    uint32_t FSMC_ECC; /* Enables or disables ECC computation.
                          Parameter can be any value of FSMC_ECC */
    uint32_t FSMC_ECCPageSize; /* Defines page size for extended ECC.
                                  Parameter can be any value of
                                  FSMC_ECC_Page_Size */
    uint32_t FSMC_TCLRSetupTime; /* Defines number of HCLK cycles to configure
                                    delay between CLE low and RE low.
                                    Parameter can be a value between
                                    0 and 0xFF. */
    uint32_t FSMC_TARSetupTime; /* Defines number of HCLK cycles to configure
                                   delay between ALE low and RE low.
                                   Parameter can be a number between
                                   0x0 and 0xFF */ 
    /* FSMC Common Space Timing */
    FSMC_NAND_PCCARDTimingInitTypeDef* FSMC_CommonSpaceTimingStruct;
    /* FSMC Attribute Space Timing */
    FSMC_NAND_PCCARDTimingInitTypeDef* FSMC_AttributeSpaceTimingStruct;
} FSMC_NANDInitTypeDef;

typedef struct {
    uint32_t FSMC_Waitfeature; /* Enables or disables Wait feature for Memory
                                  Bank. Parameter can be any value of
                                  FSMC_Wait_feature */
    uint32_t FSMC_TCLRSetupTime; /* Defines number of HCLK cycles to configure
                                    delay between CLE low and RE low. Parameter
                                    can be a value between 0 and 0xFF. */
    uint32_t FSMC_TARSetupTime; /* Defines number of HCLK cycles to configure
                                   delay between ALE low and RE low. Parameter
                                   can be a number between 0x0 and 0xFF */
    /* FSMC Common Space Timing */
    FSMC_NAND_PCCARDTimingInitTypeDef* FSMC_CommonSpaceTimingStruct;
    /* FSMC Attribute Space Timing */
    FSMC_NAND_PCCARDTimingInitTypeDef* FSMC_AttributeSpaceTimingStruct;
    /* FSMC IO Space Timing */
    FSMC_NAND_PCCARDTimingInitTypeDef* FSMC_IOSpaceTimingStruct;
} FSMC_PCCARDInitTypeDef;

#define FSMC_Bank1_NORSRAM1 ((uint32_t) 0x00000000)
#define FSMC_Bank1_NORSRAM2 ((uint32_t) 0x00000002)
#define FSMC_Bank1_NORSRAM3 ((uint32_t) 0x00000004)
#define FSMC_Bank1_NORSRAM4 ((uint32_t) 0x00000006)
#define FSMC_Bank2_NAND ((uint32_t) 0x00000010)
#define FSMC_Bank3_NAND ((uint32_t) 0x00000100)
#define FSMC_Bank4_PCCARD ((uint32_t) 0x00001000)
#define FSMC_DataAddressMux_Disable ((uint32_t) 0x00000000)
#define FSMC_DataAddressMux_Enable ((uint32_t) 0x00000002)
#define FSMC_MemoryType_SRAM ((uint32_t) 0x00000000)
#define FSMC_MemoryType_PSRAM ((uint32_t) 0x00000004)
#define FSMC_MemoryType_NOR ((uint32_t) 0x00000008)
#define FSMC_MemoryDataWidth_8b ((uint32_t) 0x00000000)
#define FSMC_MemoryDataWidth_16b ((uint32_t) 0x00000010)
#define FSMC_BurstAccessMode_Disable ((uint32_t) 0x00000000)
#define FSMC_BurstAccessMode_Enable ((uint32_t) 0x00000100)
#define FSMC_AsynchronousWait_Disable ((uint32_t) 0x00000000)
#define FSMC_AsynchronousWait_Enable ((uint32_t) 0x00008000)
#define FSMC_WaitSignalPolarity_Low ((uint32_t) 0x00000000)
#define FSMC_WaitSignalPolarity_High ((uint32_t) 0x00000200)
#define FSMC_WrapMode_Disable ((uint32_t) 0x00000000)
#define FSMC_WrapMode_Enable ((uint32_t) 0x00000400)
#define FSMC_WaitSignalActive_BeforeWaitState ((uint32_t) 0x00000000)
#define FSMC_WaitSignalActive_DuringWaitState ((uint32_t) 0x00000800)
#define FSMC_WriteOperation_Disable ((uint32_t) 0x00000000)
#define FSMC_WriteOperation_Enable ((uint32_t) 0x00001000)
#define FSMC_WaitSignal_Disable ((uint32_t) 0x00000000)
#define FSMC_WaitSignal_Enable ((uint32_t) 0x00002000)
#define FSMC_ExtendedMode_Disable ((uint32_t) 0x00000000)
#define FSMC_ExtendedMode_Enable ((uint32_t) 0x00004000)
#define FSMC_WriteBurst_Disable ((uint32_t) 0x00000000)
#define FSMC_WriteBurst_Enable ((uint32_t) 0x00080000)
#define FSMC_AccessMode_A ((uint32_t) 0x00000000)
#define FSMC_AccessMode_B ((uint32_t) 0x10000000)
#define FSMC_AccessMode_C ((uint32_t) 0x20000000)
#define FSMC_AccessMode_D ((uint32_t) 0x30000000)
#define FSMC_Waitfeature_Disable ((uint32_t) 0x00000000)
#define FSMC_Waitfeature_Enable ((uint32_t) 0x00000002)
#define FSMC_ECC_Disable ((uint32_t) 0x00000000)
#define FSMC_ECC_Enable ((uint32_t) 0x00000040)
#define FSMC_ECCPageSize_256Bytes ((uint32_t) 0x00000000)
#define FSMC_ECCPageSize_512Bytes ((uint32_t) 0x00020000)
#define FSMC_ECCPageSize_1024Bytes ((uint32_t) 0x00040000)
#define FSMC_ECCPageSize_2048Bytes ((uint32_t) 0x00060000)
#define FSMC_ECCPageSize_4096Bytes ((uint32_t) 0x00080000)
#define FSMC_ECCPageSize_8192Bytes ((uint32_t) 0x000A0000)
#define FSMC_IT_RisingEdge ((uint32_t) 0x00000008)
#define FSMC_IT_Level ((uint32_t) 0x00000010)
#define FSMC_IT_FallingEdge ((uint32_t) 0x00000020)
#define FSMC_FLAG_RisingEdge ((uint32_t) 0x00000001)
#define FSMC_FLAG_Level ((uint32_t) 0x00000002)
#define FSMC_FLAG_FallingEdge ((uint32_t) 0x00000004)
#define FSMC_FLAG_FEMPT ((uint32_t) 0x00000040)

#define IS_FSMC_NORSRAM_BANK(BANK) ( \
    ((BANK) == FSMC_Bank1_NORSRAM1) || ((BANK) == FSMC_Bank1_NORSRAM2) || \
    ((BANK) == FSMC_Bank1_NORSRAM3) || ((BANK) == FSMC_Bank1_NORSRAM4) \
)

#define IS_FSMC_NAND_BANK(BANK) ( \
    ((BANK) == FSMC_Bank2_NAND) || ((BANK) == FSMC_Bank3_NAND) \
)

#define IS_FSMC_GETFLAG_BANK(BANK) ( \
    ((BANK) == FSMC_Bank2_NAND) || ((BANK) == FSMC_Bank3_NAND) || \
    ((BANK) == FSMC_Bank4_PCCARD) \
)

#define IS_FSMC_IT_BANK(BANK) ( \
    ((BANK) == FSMC_Bank2_NAND) || \
    ((BANK) == FSMC_Bank3_NAND) || \
    ((BANK) == FSMC_Bank4_PCCARD) \
)

#define IS_FSMC_MUX(MUX) ( \
    ((MUX) == FSMC_DataAddressMux_Disable) || \
    ((MUX) == FSMC_DataAddressMux_Enable) \
)

#define IS_FSMC_MEMORY(MEMORY) ( \
    ((MEMORY) == FSMC_MemoryType_SRAM) || \
    ((MEMORY) == FSMC_MemoryType_PSRAM)|| \
    ((MEMORY) == FSMC_MemoryType_NOR) \
)

#define IS_FSMC_MEMORY_WIDTH(WIDTH) ( \
    ((WIDTH) == FSMC_MemoryDataWidth_8b) || \
    ((WIDTH) == FSMC_MemoryDataWidth_16b) \
)

#define IS_FSMC_BURSTMODE(STATE) ( \
    ((STATE) == FSMC_BurstAccessMode_Disable) || \
    ((STATE) == FSMC_BurstAccessMode_Enable) \
)

#define IS_FSMC_ASYNWAIT(STATE) ( \
    ((STATE) == FSMC_AsynchronousWait_Disable) || \
    ((STATE) == FSMC_AsynchronousWait_Enable) \
)

#define IS_FSMC_WAIT_POLARITY(POLARITY) ( \
    ((POLARITY) == FSMC_WaitSignalPolarity_Low) || \
    ((POLARITY) == FSMC_WaitSignalPolarity_High) \
)

#define IS_FSMC_WRAP_MODE(MODE) ( \
    ((MODE) == FSMC_WrapMode_Disable) || ((MODE) == FSMC_WrapMode_Enable) \
)

#define IS_FSMC_WAIT_SIGNAL_ACTIVE(ACTIVE) ( \
    ((ACTIVE) == FSMC_WaitSignalActive_BeforeWaitState) || \
    ((ACTIVE) == FSMC_WaitSignalActive_DuringWaitState) \
)

#define IS_FSMC_WRITE_OPERATION(OPERATION) ( \
    ((OPERATION) == FSMC_WriteOperation_Disable) || \
    ((OPERATION) == FSMC_WriteOperation_Enable) \
)

#define IS_FSMC_WAITE_SIGNAL(SIGNAL) ( \
    ((SIGNAL) == FSMC_WaitSignal_Disable) || \
    ((SIGNAL) == FSMC_WaitSignal_Enable) \
)

#define IS_FSMC_EXTENDED_MODE(MODE) ( \
    ((MODE) == FSMC_ExtendedMode_Disable) || \
    ((MODE) == FSMC_ExtendedMode_Enable) \
)

#define IS_FSMC_WRITE_BURST(BURST) ( \
    ((BURST) == FSMC_WriteBurst_Disable) || \
    ((BURST) == FSMC_WriteBurst_Enable) \
)

#define IS_FSMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 0xF)
#define IS_FSMC_ADDRESS_HOLD_TIME(TIME) ((TIME) <= 0xF)
#define IS_FSMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 0xFF))
#define IS_FSMC_TURNAROUND_TIME(TIME) ((TIME) <= 0xF)
#define IS_FSMC_CLK_DIV(DIV) ((DIV) <= 0xF)
#define IS_FSMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 0xF)

#define IS_FSMC_ACCESS_MODE(MODE) ( \
    ((MODE) == FSMC_AccessMode_A) || ((MODE) == FSMC_AccessMode_B) || \
    ((MODE) == FSMC_AccessMode_C) || ((MODE) == FSMC_AccessMode_D) \
)

#define IS_FSMC_WAIT_FEATURE(FEATURE) ( \
    ((FEATURE) == FSMC_Waitfeature_Disable) || \
    ((FEATURE) == FSMC_Waitfeature_Enable) \
)

#define IS_FSMC_ECC_STATE(STATE) ( \
    ((STATE) == FSMC_ECC_Disable) || ((STATE) == FSMC_ECC_Enable) \
)

#define IS_FSMC_ECCPAGE_SIZE(SIZE) ( \
    ((SIZE) == FSMC_ECCPageSize_256Bytes) || \
    ((SIZE) == FSMC_ECCPageSize_512Bytes) || \
    ((SIZE) == FSMC_ECCPageSize_1024Bytes) || \
    ((SIZE) == FSMC_ECCPageSize_2048Bytes) || \
    ((SIZE) == FSMC_ECCPageSize_4096Bytes) || \
    ((SIZE) == FSMC_ECCPageSize_8192Bytes) \
)

#define IS_FSMC_TCLR_TIME(TIME) ((TIME) <= 0xFF)
#define IS_FSMC_TAR_TIME(TIME) ((TIME) <= 0xFF)
#define IS_FSMC_SETUP_TIME(TIME) ((TIME) <= 0xFF)
#define IS_FSMC_WAIT_TIME(TIME) ((TIME) <= 0xFF)
#define IS_FSMC_HOLD_TIME(TIME) ((TIME) <= 0xFF)
#define IS_FSMC_HIZ_TIME(TIME) ((TIME) <= 0xFF)

#define IS_FSMC_IT(IT) ( \
    (((IT) & (uint32_t) 0xFFFFFFC7) == 0x00000000) && ((IT) != 0x00000000) \
)

#define IS_FSMC_GET_IT(IT) ( \
    ((IT) == FSMC_IT_RisingEdge) || ((IT) == FSMC_IT_Level) || \
    ((IT) == FSMC_IT_FallingEdge) \
)

#define IS_FSMC_GET_FLAG(FLAG) ( \
    ((FLAG) == FSMC_FLAG_RisingEdge) || ((FLAG) == FSMC_FLAG_Level) || \
    ((FLAG) == FSMC_FLAG_FallingEdge) || ((FLAG) == FSMC_FLAG_FEMPT) \
)

#define IS_FSMC_CLEAR_FLAG(FLAG) ( \
    (((FLAG) & (uint32_t) 0xFFFFFFF8) == 0x00000000) && \
    ((FLAG) != 0x00000000) \
)

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_NANDDeInit(uint32_t FSMC_Bank);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState);
uint32_t FSMC_GetECC(uint32_t FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_PCCARDCmd(FunctionalState NewState);

void FSMC_ITConfig(
    uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState
);

FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT);
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT);

#ifdef __cplusplus
    }
#endif

#endif

