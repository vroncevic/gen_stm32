/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_dma.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Direct Memory Access controller (DMA):
 *     - Initialization and Configuration
 *     - Data Counter
 *     - Double Buffer mode configuration and command
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_dma is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_dma is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* Masks Definition */
#define TRANSFER_IT_ENABLE_MASK (uint32_t) ( \
    DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE \
)

#define DMA_Stream0_IT_MASK (uint32_t) ( \
    DMA_LISR_FEIF0 | DMA_LISR_DMEIF0 | DMA_LISR_TEIF0 | DMA_LISR_HTIF0 | \
    DMA_LISR_TCIF0 \
)

#define DMA_Stream1_IT_MASK (uint32_t) (DMA_Stream0_IT_MASK << 6)
#define DMA_Stream2_IT_MASK (uint32_t) (DMA_Stream0_IT_MASK << 16)
#define DMA_Stream3_IT_MASK (uint32_t) (DMA_Stream0_IT_MASK << 22)

#define DMA_Stream4_IT_MASK (uint32_t) ( \
    DMA_Stream0_IT_MASK | (uint32_t) 0x20000000 \
)

#define DMA_Stream5_IT_MASK (uint32_t) ( \
    DMA_Stream1_IT_MASK | (uint32_t) 0x20000000 \
)

#define DMA_Stream6_IT_MASK (uint32_t) ( \
    DMA_Stream2_IT_MASK | (uint32_t) 0x20000000 \
)

#define DMA_Stream7_IT_MASK (uint32_t) ( \
    DMA_Stream3_IT_MASK | (uint32_t) 0x20000000 \
)

#define TRANSFER_IT_MASK (uint32_t) 0x0F3C0F3C
#define HIGH_ISR_MASK (uint32_t) 0x20000000
#define RESERVED_MASK (uint32_t) 0x0F7D0F7D

/**
 * Deinitialize DMAy Streamx registers to their default reset values.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * retval None
 */
void DMA_DeInit(DMA_Stream_TypeDef* DMAy_Streamx) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    /* Disable selected DMAy Streamx */
    DMAy_Streamx->CR &= ~((uint32_t) DMA_SxCR_EN);
    /* Reset DMAy Streamx control register */
    DMAy_Streamx->CR  = 0;
    /* Reset DMAy Streamx Number of Data to Transfer register */
    DMAy_Streamx->NDTR = 0;
    /* Reset DMAy Streamx peripheral address register */
    DMAy_Streamx->PAR  = 0;
    /* Reset DMAy Streamx memory 0 address register */
    DMAy_Streamx->M0AR = 0;
    /* Reset DMAy Streamx memory 1 address register */
    DMAy_Streamx->M1AR = 0;
    /* Reset DMAy Streamx FIFO control register */
    DMAy_Streamx->FCR = (uint32_t) 0x00000021;
    /* Reset interrupt pending bits for selected stream */
    if (DMAy_Streamx == DMA1_Stream0) {
        /* Reset interrupt pending bits for DMA1 Stream0 */
        DMA1->LIFCR = DMA_Stream0_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream1) {
        /* Reset interrupt pending bits for DMA1 Stream1 */
        DMA1->LIFCR = DMA_Stream1_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream2) {
        /* Reset interrupt pending bits for DMA1 Stream2 */
        DMA1->LIFCR = DMA_Stream2_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream3) {
        /* Reset interrupt pending bits for DMA1 Stream3 */
        DMA1->LIFCR = DMA_Stream3_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream4) {
        /* Reset interrupt pending bits for DMA1 Stream4 */
        DMA1->HIFCR = DMA_Stream4_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream5) {
        /* Reset interrupt pending bits for DMA1 Stream5 */
        DMA1->HIFCR = DMA_Stream5_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream6) {
        /* Reset interrupt pending bits for DMA1 Stream6 */
        DMA1->HIFCR = (uint32_t) DMA_Stream6_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream7) {
        /* Reset interrupt pending bits for DMA1 Stream7 */
        DMA1->HIFCR = DMA_Stream7_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream0) {
        /* Reset interrupt pending bits for DMA2 Stream0 */
        DMA2->LIFCR = DMA_Stream0_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream1) {
        /* Reset interrupt pending bits for DMA2 Stream1 */
        DMA2->LIFCR = DMA_Stream1_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream2) {
        /* Reset interrupt pending bits for DMA2 Stream2 */
        DMA2->LIFCR = DMA_Stream2_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream3) {
        /* Reset interrupt pending bits for DMA2 Stream3 */
        DMA2->LIFCR = DMA_Stream3_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream4) {
        /* Reset interrupt pending bits for DMA2 Stream4 */
        DMA2->HIFCR = DMA_Stream4_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream5) {
        /* Reset interrupt pending bits for DMA2 Stream5 */
        DMA2->HIFCR = DMA_Stream5_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream6) {
        /* Reset interrupt pending bits for DMA2 Stream6 */
        DMA2->HIFCR = DMA_Stream6_IT_MASK;
    } else {
        if (DMAy_Streamx == DMA2_Stream7) {
            /* Reset interrupt pending bits for DMA2 Stream7 */
            DMA2->HIFCR = DMA_Stream7_IT_MASK;
        }
    }
}

/**
 * Initializes DMAy Streamx according to specified parameters in
 * DMA_InitStruct structure.
 * Before calling this function, it is recommended to check that Stream 
 * is actually disabled using function DMA_GetCmdStatus().
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param DMA_InitStruct: pointer to a DMA_InitTypeDef structure that contains
 *       configuration information for specified DMA Stream.
 * retval None
 */
void DMA_Init(
    DMA_Stream_TypeDef* DMAy_Streamx, DMA_InitTypeDef* DMA_InitStruct
) {
    uint32_t tmpreg = 0;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CHANNEL(DMA_InitStruct->DMA_Channel));
    assert_param(IS_DMA_DIRECTION(DMA_InitStruct->DMA_DIR));
    assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
    assert_param(
        IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc)
    );
    assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
    assert_param(
        IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize)
    );
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
    assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
    assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
    assert_param(IS_DMA_FIFO_MODE_STATE(DMA_InitStruct->DMA_FIFOMode));
    assert_param(IS_DMA_FIFO_THRESHOLD(DMA_InitStruct->DMA_FIFOThreshold));
    assert_param(IS_DMA_MEMORY_BURST(DMA_InitStruct->DMA_MemoryBurst));
    assert_param(IS_DMA_PERIPHERAL_BURST(DMA_InitStruct->DMA_PeripheralBurst));
    /* DMAy Streamx CR Configuration */
    tmpreg = DMAy_Streamx->CR; /* Get DMAy_Streamx CR value */
    /**
     * Clear:
     * CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits
     */
    tmpreg &= (
        (uint32_t) ~(
            DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST |
            DMA_SxCR_PL | DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | DMA_SxCR_MINC |
            DMA_SxCR_PINC | DMA_SxCR_CIRC | DMA_SxCR_DIR
        )
    );
    /* Configure DMAy Streamx: */
    /* Set CHSEL bits according to DMA_CHSEL value */
    /* Set DIR bits according to DMA_DIR value */
    /* Set PINC bit according to DMA_PeripheralInc value */
    /* Set MINC bit according to DMA_MemoryInc value */
    /* Set PSIZE bits according to DMA_PeripheralDataSize value */
    /* Set MSIZE bits according to DMA_MemoryDataSize value */
    /* Set CIRC bit according to DMA_Mode value */
    /* Set PL bits according to DMA_Priority value */
    /* Set MBURST bits according to DMA_MemoryBurst value */
    /* Set PBURST bits according to DMA_PeripheralBurst value */
    tmpreg |= (
        DMA_InitStruct->DMA_Channel | DMA_InitStruct->DMA_DIR |
        DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
        DMA_InitStruct->DMA_PeripheralDataSize |
        DMA_InitStruct->DMA_MemoryDataSize | DMA_InitStruct->DMA_Mode |
        DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_MemoryBurst |
        DMA_InitStruct->DMA_PeripheralBurst
    );
    DMAy_Streamx->CR = tmpreg; /* Write to DMAy Streamx CR register */
    /* DMAy Streamx FCR Configuration */
    tmpreg = DMAy_Streamx->FCR; /* Get DMAy_Streamx FCR value */
    /* Clear DMDIS and FTH bits */
    tmpreg &= (uint32_t) ~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);
    /**
     * Configure DMAy Streamx FIFO: 
     * Set DMDIS bits according to DMA_FIFOMode value
     * Set FTH bits according to DMA_FIFOThreshold value 
     */
    tmpreg |= DMA_InitStruct->DMA_FIFOMode | DMA_InitStruct->DMA_FIFOThreshold;
    DMAy_Streamx->FCR = tmpreg; /* Write to DMAy Streamx CR */
    /* DMAy Streamx NDTR Configuration */
    /* Write to DMAy Streamx NDTR register */
    DMAy_Streamx->NDTR = DMA_InitStruct->DMA_BufferSize;
    /* DMAy Streamx PAR Configuration */
    /* Write to DMAy Streamx PAR */
    DMAy_Streamx->PAR = DMA_InitStruct->DMA_PeripheralBaseAddr;
    /* DMAy Streamx M0AR Configuration */
    /* Write to DMAy Streamx M0AR */
    DMAy_Streamx->M0AR = DMA_InitStruct->DMA_Memory0BaseAddr;
}

/**
 * Fills each DMA_InitStruct member with its default value.
 * param DMA_InitStruct : pointer to a DMA_InitTypeDef structure which will
 *       be initialized.
 * retval None
 */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct) {
    /* Reset DMA init structure parameters values */
    /* Initialize DMA_Channel member */
    DMA_InitStruct->DMA_Channel = 0;
    /* Initialize DMA_PeripheralBaseAddr member */
    DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
    /* Initialize DMA_Memory0BaseAddr member */
    DMA_InitStruct->DMA_Memory0BaseAddr = 0;
    /* Initialize DMA_DIR member */
    DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralToMemory;
    /* Initialize DMA_BufferSize member */
    DMA_InitStruct->DMA_BufferSize = 0;
    /* Initialize DMA_PeripheralInc member */
    DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /* Initialize DMA_MemoryInc member */
    DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
    /* Initialize DMA_PeripheralDataSize member */
    DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /* Initialize DMA_MemoryDataSize member */
    DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /* Initialize DMA_Mode member */
    DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
    /* Initialize DMA_Priority member */
    DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
    /* Initialize DMA_FIFOMode member */
    DMA_InitStruct->DMA_FIFOMode = DMA_FIFOMode_Disable;
    /* Initialize DMA_FIFOThreshold member */
    DMA_InitStruct->DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    /* Initialize DMA_MemoryBurst member */
    DMA_InitStruct->DMA_MemoryBurst = DMA_MemoryBurst_Single;
    /* Initialize DMA_PeripheralBurst member */
    DMA_InitStruct->DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
}

/**
 * Enables or disables specified DMAy Streamx.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param NewState: new state of DMAy Streamx. 
 *   This parameter can be: ENABLE or DISABLE.
 *
 * This function may be used to perform Pause-Resume operation. When a
 * transfer is ongoing, calling this function to disable Stream will
 * cause transfer to be paused. All configuration registers and the
 * number of remaining data will be preserved. When calling again this
 * function to re-enable Stream, transfer will be resumed from
 * point where it was paused.
 * After configuring DMA Stream (DMA_Init() function) and enabling the
 * stream, it is recommended to check (or wait until) DMA Stream is
 * effectively enabled. A Stream may remain disabled if a configuration 
 * parameter is wrong.
 * After disabling a DMA Stream, it is also recommended to check (or wait
 * until) DMA Stream is effectively disabled. If a Stream is disabled 
 * while a data transfer is ongoing, current data will be transferred
 * and Stream will be effectively disabled only after transfer of
 * this single data is finished.
 * retval None
 */
void DMA_Cmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected DMAy Streamx by setting EN bit */
        DMAy_Streamx->CR |= (uint32_t) DMA_SxCR_EN;
    } else {
        /* Disable selected DMAy Streamx by clearing EN bit */
        DMAy_Streamx->CR &= ~(uint32_t) DMA_SxCR_EN;
    }
}

/**
 * Configures, when PINC (Peripheral Increment address mode) bit is
 * set, if peripheral address should be incremented with data 
 * size (configured with PSIZE bits) or by a fixed offset equal to 4
 * (32-bit aligned addresses).
 * This function has no effect if Peripheral Increment mode is disabled.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param DMA_Pincos: specifies Peripheral increment offset size.
 *   This parameter can be one of following values:
 *       arg DMA_PINCOS_Psize: Peripheral address increment is done
 *           accordingly to PSIZE parameter.
 *       arg DMA_PINCOS_WordAligned: Peripheral address increment offset is
 *           fixed to 4 (32-bit aligned addresses).
 * retval None
 */
void DMA_PeriphIncOffsetSizeConfig(
    DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Pincos
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_PINCOS_SIZE(DMA_Pincos));
    /* Check needed Peripheral increment offset */
    if (DMA_Pincos != DMA_PINCOS_Psize) {
        /* Configure DMA_SxCR_PINCOS bit with input parameter */
        DMAy_Streamx->CR |= (uint32_t) DMA_SxCR_PINCOS;
    } else {
        /**
         * Clear PINCOS bit, Peripheral address
         * incremented according to PSIZE 
         */
        DMAy_Streamx->CR &= ~(uint32_t) DMA_SxCR_PINCOS;
    }
}

/**
 * Configures, when DMAy Streamx is disabled, flow controller for
 * next transactions (Peripheral or Memory).
 * Before enabling this feature, check if used peripheral supports
 * Flow Controller mode or not.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param DMA_FlowCtrl: specifies DMA flow controller.
 *   This parameter can be one of following values:
 *       arg DMA_FlowCtrl_Memory: DMAy_Streamx transactions flow controller
 *           is DMA controller.
 *       arg DMA_FlowCtrl_Peripheral: DMAy_Streamx transactions flow
 *           controller is peripheral.
 * retval None
 */
void DMA_FlowControllerConfig(
    DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FlowCtrl
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_FLOW_CTRL(DMA_FlowCtrl));
    /* Check needed flow controller */
    if(DMA_FlowCtrl != DMA_FlowCtrl_Memory) {
        /* Configure DMA_SxCR_PFCTRL bit with input parameter */
        DMAy_Streamx->CR |= (uint32_t) DMA_SxCR_PFCTRL;
    } else {
        /* Clear PFCTRL bit: Memory is flow controller */
        DMAy_Streamx->CR &= ~(uint32_t) DMA_SxCR_PFCTRL;
    }
}

/**
 * Writes number of data units to be transferred on DMAy Streamx.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param Counter: Number of data units to be transferred (from 0 to 65535)
 *       Number of data items depends only on Peripheral data format.
 * If Peripheral data format is Bytes: number of data units is equal
 * to total number of bytes to be transferred.
 * If Peripheral data format is Half-Word: number of data units is
 * equal to total number of bytes to be transferred / 2.
 * If Peripheral data format is Word: number of data units is equal
 * to total number of bytes to be transferred / 4.
 * In Memory-to-Memory transfer mode, memory buffer pointed by
 * DMAy_SxPAR register is considered as Peripheral.
 * retval The number of remaining data units in current DMAy Streamx transfer.
 */
void DMA_SetCurrDataCounter(
    DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    /* Write number of data units to be transferred */
    DMAy_Streamx->NDTR = (uint16_t) Counter;
}

/**
 * Returns number of remaining data units in current DMAy Streamx transfer.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * retval The number of remaining data units in current DMAy Streamx transfer.
 */
uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    /* Return number of remaining data units for DMAy Streamx */
    return ((uint16_t) (DMAy_Streamx->NDTR));
}

/**
 * Configures, when DMAy Streamx is disabled, double buffer mode
 * and current memory target.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param Memory1BaseAddr: base address of second buffer (Memory 1)  
 * param DMA_CurrentMemory: specifies which memory will be first buffer for
 *       transactions when Stream will be enabled.
 *   This parameter can be one of following values:
 *       arg DMA_Memory_0: Memory 0 is current buffer.
 *       arg DMA_Memory_1: Memory 1 is current buffer.
 *       
 * Memory0BaseAddr is set by DMA structure configuration in DMA_Init().
 * retval None
 */
void DMA_DoubleBufferModeConfig(
    DMA_Stream_TypeDef* DMAy_Streamx, uint32_t Memory1BaseAddr,
    uint32_t DMA_CurrentMemory
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CURRENT_MEM(DMA_CurrentMemory));
    if (DMA_CurrentMemory != DMA_Memory_0) {
        /* Set Memory 1 as current memory address */
        DMAy_Streamx->CR |= (uint32_t) (DMA_SxCR_CT);
    } else {
        /* Set Memory 0 as current memory address */
        DMAy_Streamx->CR &= ~(uint32_t) (DMA_SxCR_CT);
    }
    /* Write to DMAy Streamx M1AR */
    DMAy_Streamx->M1AR = Memory1BaseAddr;
}

/**
 * Enables or disables double buffer mode for selected DMA stream.
 * This function can be called only when DMA Stream is disabled.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param NewState: new state of DMAy Streamx double buffer mode. 
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DMA_DoubleBufferModeCmd(
    DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Configure Double Buffer mode */
    if (NewState != DISABLE) {
        /* Enable Double buffer mode */
        DMAy_Streamx->CR |= (uint32_t) DMA_SxCR_DBM;
    } else {
        /* Disable Double buffer mode */
        DMAy_Streamx->CR &= ~(uint32_t) DMA_SxCR_DBM;
    }
}

/**
 * Configures Memory address for next buffer transfer in double
 * buffer mode (for dynamic use). This function can be called when the
 * DMA Stream is enabled and when transfer is ongoing.  
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param MemoryBaseAddr: The base address of target memory buffer
 * param DMA_MemoryTarget: Next memory target to be used. 
 *   This parameter can be one of following values:
 *       arg DMA_Memory_0: To use memory address 0
 *       arg DMA_Memory_1: To use memory address 1
 * 
 * It is not allowed to modify Base Address of a target Memory when
 * this target is involved in current transfer. ie. If DMA Stream
 * is currently transferring to/from Memory 1, then it not possible to
 * modify Base address of Memory 1, but it is possible to modify Base
 * address of Memory 0.
 * To know which Memory is currently used, you can use function
 * DMA_GetCurrentMemoryTarget().
 * retval None
 */
void DMA_MemoryTargetConfig(
    DMA_Stream_TypeDef* DMAy_Streamx, uint32_t MemoryBaseAddr,
    uint32_t DMA_MemoryTarget
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CURRENT_MEM(DMA_MemoryTarget));
    /* Check Memory target to be configured */
    if (DMA_MemoryTarget != DMA_Memory_0) {
        /* Write to DMAy Streamx M1AR */
        DMAy_Streamx->M1AR = MemoryBaseAddr;
    } else {
        /* Write to DMAy Streamx M0AR */
        DMAy_Streamx->M0AR = MemoryBaseAddr;
    }
}

/**
 * Returns current memory target used by double buffer transfer.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * retval The memory target number: 0 for Memory0 or 1 for Memory1.
 */
uint32_t DMA_GetCurrentMemoryTarget(DMA_Stream_TypeDef* DMAy_Streamx) {
    uint32_t tmp = 0;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    /* Get current memory target */
    if ((DMAy_Streamx->CR & DMA_SxCR_CT) != 0) {
        tmp = 1; /* Current memory buffer used is Memory 1 */
    } else {
        tmp = 0; /* Current memory buffer used is Memory 0 */
    }
    return tmp;
}

/**
 * Returns status of EN bit for specified DMAy Streamx.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * After configuring DMA Stream (DMA_Init() function) and enabling
 * stream, it is recommended to check (or wait until) DMA Stream
 * is effectively enabled. A Stream may remain disabled if a configuration
 * parameter is wrong.
 * After disabling a DMA Stream, it is also recommended to check (or wait 
 * until) DMA Stream is effectively disabled. If a Stream is disabled
 * while a data transfer is ongoing, current data will be transferred
 * and Stream will be effectively disabled only after transfer
 * of this single data is finished.
 * retval Current state of DMAy Streamx (ENABLE or DISABLE).
 */
FunctionalState DMA_GetCmdStatus(DMA_Stream_TypeDef* DMAy_Streamx) {
    FunctionalState state = DISABLE;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    if ((DMAy_Streamx->CR & (uint32_t) DMA_SxCR_EN) != 0) {
        /* Selected DMAy Streamx EN bit is set (DMA is still transferring) */
        state = ENABLE;
    } else {
        /**
         * Selected DMAy Streamx EN bit is cleared (DMA is disabled and
         * all transfers are complete) 
         */
        state = DISABLE;
    }
    return state;
}

/**
 * Returns current DMAy Streamx FIFO filled level.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0 
 *       to 7 to select DMA Stream.
 * retval The FIFO filling state.
 *     - DMA_FIFOStatus_Less1QuarterFull: when FIFO is less than 1
 *       quarter-full and not empty.
 *     - DMA_FIFOStatus_1QuarterFull: if more than 1 quarter-full.
 *     - DMA_FIFOStatus_HalfFull: if more than 1 half-full.
 *     - DMA_FIFOStatus_3QuartersFull: if more than 3 quarters-full.
 *     - DMA_FIFOStatus_Empty: when FIFO is empty
 *     - DMA_FIFOStatus_Full: when FIFO is full
 */
uint32_t DMA_GetFIFOStatus(DMA_Stream_TypeDef* DMAy_Streamx) {
    uint32_t tmpreg = 0;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    /* Get FIFO level bits */
    tmpreg = (uint32_t) ((DMAy_Streamx->FCR & DMA_SxFCR_FS));
    return tmpreg;
}

/**
 * Checks whether specified DMAy Streamx flag is set or not.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param DMA_FLAG: specifies flag to check.
 *   This parameter can be one of following values:
 *       arg DMA_FLAG_TCIFx:  Streamx transfer complete flag
 *       arg DMA_FLAG_HTIFx:  Streamx half transfer complete flag
 *       arg DMA_FLAG_TEIFx:  Streamx transfer error flag
 *       arg DMA_FLAG_DMEIFx: Streamx direct mode error flag
 *       arg DMA_FLAG_FEIFx:  Streamx FIFO error flag
 *         Where x can be 0 to 7 to select DMA Stream.
 * retval The new state of DMA_FLAG (SET or RESET).
 */
FlagStatus DMA_GetFlagStatus(
    DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG
) {
    FlagStatus bitstatus = RESET;
    DMA_TypeDef* DMAy;
    uint32_t tmpreg = 0;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_GET_FLAG(DMA_FLAG));
    /* Determine DMA to which belongs stream */
    if (DMAy_Streamx < DMA2_Stream0) {
        DMAy = DMA1; /* DMAy_Streamx belongs to DMA1 */
    } else {
        DMAy = DMA2; /* DMAy_Streamx belongs to DMA2 */
    }
    /* Check if flag is in HISR or LISR */
    if ((DMA_FLAG & HIGH_ISR_MASK) != (uint32_t) RESET) {
        tmpreg = DMAy->HISR; /* Get DMAy HISR register value */
    } else {
        tmpreg = DMAy->LISR; /* Get DMAy LISR register value */
    }
    tmpreg &= (uint32_t) RESERVED_MASK; /* Mask reserved bits */
    /* Check status of specified DMA flag */
    if ((tmpreg & DMA_FLAG) != (uint32_t) RESET) {
        bitstatus = SET; /* DMA_FLAG is set */
    } else {
        bitstatus = RESET; /* DMA_FLAG is reset */
    }
    return bitstatus; /* Return DMA_FLAG status */
}

/**
 * Clears DMAy Streamx's pending flags.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param DMA_FLAG: specifies flag to clear.
 *   This parameter can be any combination of following values:
 *       arg DMA_FLAG_TCIFx:  Streamx transfer complete flag
 *       arg DMA_FLAG_HTIFx:  Streamx half transfer complete flag
 *       arg DMA_FLAG_TEIFx:  Streamx transfer error flag
 *       arg DMA_FLAG_DMEIFx: Streamx direct mode error flag
 *       arg DMA_FLAG_FEIFx:  Streamx FIFO error flag
 *         Where x can be 0 to 7 to select DMA Stream.
 * retval None
 */
void DMA_ClearFlag(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG) {
    DMA_TypeDef* DMAy;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));
    /* Determine DMA to which belongs stream */
    if (DMAy_Streamx < DMA2_Stream0) {
        DMAy = DMA1; /* DMAy_Streamx belongs to DMA1 */
    } else {
        DMAy = DMA2; /* DMAy_Streamx belongs to DMA2 */
    }
    /* Check if LIFCR or HIFCR register is targeted */
    if ((DMA_FLAG & HIGH_ISR_MASK) != (uint32_t) RESET) {
        /* Set DMAy HIFCR register clear flag bits */
        DMAy->HIFCR = (uint32_t) (DMA_FLAG & RESERVED_MASK);
    } else {
        /* Set DMAy LIFCR register clear flag bits */
        DMAy->LIFCR = (uint32_t) (DMA_FLAG & RESERVED_MASK);
    }
}

/**
 * Enables or disables specified DMAy Streamx interrupts.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *          to 7 to select DMA Stream.
 * param DMA_IT: specifies DMA interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of following values:
 *       arg DMA_IT_TC:  Transfer complete interrupt mask
 *       arg DMA_IT_HT:  Half transfer complete interrupt mask
 *       arg DMA_IT_TE:  Transfer error interrupt mask
 *       arg DMA_IT_FE:  FIFO error interrupt mask
 * param NewState: new state of specified DMA interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void DMA_ITConfig(
    DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState
) {
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CONFIG_IT(DMA_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Check if DMA_IT parameter contains a FIFO interrupt */
    if ((DMA_IT & DMA_IT_FE) != 0) {
        if (NewState != DISABLE) {
            /* Enable selected DMA FIFO interrupts */
            DMAy_Streamx->FCR |= (uint32_t) DMA_IT_FE;
        } else {
            /* Disable selected DMA FIFO interrupts */
            DMAy_Streamx->FCR &= ~(uint32_t) DMA_IT_FE;
        }
    }
    /* Check if DMA_IT parameter contains a Transfer interrupt */
    if (DMA_IT != DMA_IT_FE) {
        if (NewState != DISABLE) {
            /* Enable selected DMA transfer interrupts */
            DMAy_Streamx->CR |= (uint32_t) (DMA_IT  & TRANSFER_IT_ENABLE_MASK);
        } else {
            /* Disable selected DMA transfer interrupts */
            DMAy_Streamx->CR &= ~(uint32_t) (DMA_IT & TRANSFER_IT_ENABLE_MASK);
        }
    }
}

/**
 * Checks whether specified DMAy Streamx interrupt has occurred or not.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *       to 7 to select DMA Stream.
 * param DMA_IT: specifies DMA interrupt source to check.
 *   This parameter can be one of following values:
 *       arg DMA_IT_TCIFx: Streamx transfer complete interrupt
 *       arg DMA_IT_HTIFx: Streamx half transfer complete interrupt
 *       arg DMA_IT_TEIFx: Streamx transfer error interrupt
 *       arg DMA_IT_DMEIFx: Streamx direct mode error interrupt
 *       arg DMA_IT_FEIFx: Streamx FIFO error interrupt
 *         Where x can be 0 to 7 to select DMA Stream.
 * retval The new state of DMA_IT (SET or RESET).
 */
ITStatus DMA_GetITStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT) {
    ITStatus bitstatus = RESET;
    DMA_TypeDef* DMAy;
    uint32_t tmpreg = 0, enablestatus = 0;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_GET_IT(DMA_IT));
    /* Determine DMA to which belongs stream */
    if (DMAy_Streamx < DMA2_Stream0) {
        DMAy = DMA1; /* DMAy_Streamx belongs to DMA1 */
    } else {
        DMAy = DMA2; /* DMAy_Streamx belongs to DMA2 */
    }
    /* Check if interrupt enable bit is in CR or FCR register */
    if ((DMA_IT & TRANSFER_IT_MASK) != (uint32_t) RESET) {
        /* Get interrupt enable position mask in CR register */
        tmpreg = (uint32_t) ((DMA_IT >> 11) & TRANSFER_IT_ENABLE_MASK);
        /* Check enable bit in CR register */
        enablestatus = (uint32_t) (DMAy_Streamx->CR & tmpreg);
    } else {
        /* Check enable bit in FCR register */
        enablestatus = (uint32_t) (DMAy_Streamx->FCR & DMA_IT_FE);
    }
    /* Check if interrupt pending flag is in LISR or HISR */
    if ((DMA_IT & HIGH_ISR_MASK) != (uint32_t) RESET) {
        tmpreg = DMAy->HISR; /* Get DMAy HISR register value */
    } else {
        tmpreg = DMAy->LISR; /* Get DMAy LISR register value */
    }
    tmpreg &= (uint32_t) RESERVED_MASK; /* mask all reserved bits */
    /* Check status of specified DMA interrupt */
    if (
        ((tmpreg & DMA_IT) != (uint32_t) RESET) &&
        (enablestatus != (uint32_t) RESET)
    ) {
        bitstatus = SET; /* DMA_IT is set */
    } else {
        bitstatus = RESET; /* DMA_IT is reset */
    }
    return bitstatus; /* Return DMA_IT status */
}

/**
 * Clears DMAy Streamx's interrupt pending bits.
 * param DMAy_Streamx: where y can be 1 or 2 to select DMA and x can be 0
 *          to 7 to select DMA Stream.
 * param DMA_IT: specifies DMA interrupt pending bit to clear.
 *   This parameter can be any combination of following values:
 *       arg DMA_IT_TCIFx: Streamx transfer complete interrupt
 *       arg DMA_IT_HTIFx: Streamx half transfer complete interrupt
 *       arg DMA_IT_TEIFx: Streamx transfer error interrupt
 *       arg DMA_IT_DMEIFx: Streamx direct mode error interrupt
 *       arg DMA_IT_FEIFx: Streamx FIFO error interrupt
 *         Where x can be 0 to 7 to select DMA Stream.
 * retval None
 */
void DMA_ClearITPendingBit(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT) {
    DMA_TypeDef* DMAy;

    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CLEAR_IT(DMA_IT));
    /* Determine DMA to which belongs stream */
    if (DMAy_Streamx < DMA2_Stream0) {
        DMAy = DMA1; /* DMAy_Streamx belongs to DMA1 */
    }  else {
        DMAy = DMA2; /* DMAy_Streamx belongs to DMA2 */
    }
    /* Check if LIFCR or HIFCR register is targeted */
    if ((DMA_IT & HIGH_ISR_MASK) != (uint32_t) RESET) {
        /* Set DMAy HIFCR register clear interrupt bits */
        DMAy->HIFCR = (uint32_t) (DMA_IT & RESERVED_MASK);
    } else {
        /* Set DMAy LIFCR register clear interrupt bits */
        DMAy->LIFCR = (uint32_t) (DMA_IT & RESERVED_MASK);
    }
}

