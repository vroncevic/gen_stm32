/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_usart.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Universal synchronous asynchronous receiver
 * transmitter (USART):
 *     - Initialization and Configuration
 *     - Data transfers
 *     - Multi-Processor Communication
 *     - LIN mode
 *     - Half-duplex mode
 *     - Smartcard mode
 *     - IrDA mode
 *     - DMA transfers management
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_usart is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_usart is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* USART CR1 register clear Mask ((~(uint16_t) 0xE9F3)) */
#define CR1_CLEAR_MASK ( \
    (uint16_t) ( \
        USART_CR1_M | USART_CR1_PCE | \
        USART_CR1_PS | USART_CR1_TE | \
        USART_CR1_RE \
    ) \
)

/* USART CR2 register clock bits clear Mask ((~(uint16_t) 0xF0FF)) */
#define CR2_CLOCK_CLEAR_MASK ( \
    (uint16_t) ( \
        USART_CR2_CLKEN | USART_CR2_CPOL | \
        USART_CR2_CPHA | USART_CR2_LBCL \
    ) \
)

/* USART CR3 register clear Mask ((~(uint16_t)0xFCFF)) */
#define CR3_CLEAR_MASK ((uint16_t)(USART_CR3_RTSE | USART_CR3_CTSE))

/* USART Interrupts mask */
#define IT_MASK ((uint16_t)0x001F)

/**
 * Deinitializes USARTx peripheral registers to their default reset values.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * retval None
 */
void USART_DeInit(USART_TypeDef* USARTx) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    if (USARTx == USART1) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
    } else if (USARTx == USART2) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
    } else if (USARTx == USART3) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
    } else if (USARTx == UART4) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
    } else if (USARTx == UART5) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    } else {
        if (USARTx == USART6) {
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, ENABLE);
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, DISABLE);
        }
    }
}

/**
 * Initializes USARTx peripheral according to specified
 * parameters in USART_InitStruct .
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or 
 * UART peripheral.
 * param USART_InitStruct: pointer to a USART_InitTypeDef structure
 *       that contains configuration information for USART peripheral.
 * retval None
 */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct) {
    uint32_t tmpreg = 0x00, apbclock = 0x00;
    uint32_t integerdivider = 0x00;
    uint32_t fractionaldivider = 0x00;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
    assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
    assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
    assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
    assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
    assert_param(
        IS_USART_HARDWARE_FLOW_CONTROL(
            USART_InitStruct->USART_HardwareFlowControl
        )
    );
    /**
     * The hardware flow control is available only for USART1,
     * USART2, USART3 and USART6 
     */
    if (
        USART_InitStruct->USART_HardwareFlowControl !=
        USART_HardwareFlowControl_None
    ) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }
    tmpreg = USARTx->CR2; /* USART CR2 Configuration */
    /* Clear STOP[13:12] bits */
    tmpreg &= (uint32_t) ~((uint32_t) USART_CR2_STOP);
    /**
     * Configure USART Stop Bits, Clock, CPOL, CPHA and LastBit:
     * Set STOP[13:12] bits according to USART_StopBits value 
     */
    tmpreg |= (uint32_t) USART_InitStruct->USART_StopBits;
    USARTx->CR2 = (uint16_t) tmpreg; /* Write to USART CR2 */
    tmpreg = USARTx->CR1; /* USART CR1 Configuration */
    /* Clear M, PCE, PS, TE and RE bits */
    tmpreg &= (uint32_t) ~((uint32_t) CR1_CLEAR_MASK);

    /**
     * Configure USART Word Length, Parity and mode:
     * Set M bits according to USART_WordLength value
     * Set PCE and PS bits according to USART_Parity value
     * Set TE and RE bits according to USART_Mode value 
     */
    tmpreg |= (uint32_t) (
        USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
        USART_InitStruct->USART_Mode
    );
    USARTx->CR1 = (uint16_t) tmpreg; /* Write to USART CR1 */
    tmpreg = USARTx->CR3; /* USART CR3 Configuration */
    /* Clear CTSE and RTSE bits */
    tmpreg &= (uint32_t) ~((uint32_t) CR3_CLEAR_MASK);
    /**
     * Configure USART HFC:
     * Set CTSE and RTSE bits according to USART_HardwareFlowControl value 
     */
    tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
    USARTx->CR3 = (uint16_t) tmpreg; /* Write to USART CR3 */
    /* USART BRR Configuration */
    /* Configure USART Baud Rate */
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    if ((USARTx == USART1) || (USARTx == USART6)) {
        apbclock = RCC_ClocksStatus.PCLK2_Frequency;
    } else {
        apbclock = RCC_ClocksStatus.PCLK1_Frequency;
    }
    /* Determine integer part */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        /* Integer part computing in case Oversampling mode is 8 Samples */
        integerdivider = (
            (25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate))
        );
    } else {
        /* Integer part computing in case Oversampling mode is 16 Samples */
        integerdivider = (
            (25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate))
        );
    }
    tmpreg = (integerdivider / 100) << 4;
    /* Determine fractional part */
    fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
    /* Implement fractional part in register */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t) 0x07);
    } else {
        tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t) 0x0F);
    }
    USARTx->BRR = (uint16_t) tmpreg; /* Write to USART BRR register */
}

/**
 * Fills each USART_InitStruct member with its default value.
 * param USART_InitStruct: pointer to a USART_InitTypeDef structure which will
 *       be initialized.
 * retval None
 */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct) {
    /* USART_InitStruct members default value */
    USART_InitStruct->USART_BaudRate = 9600;
    USART_InitStruct->USART_WordLength = USART_WordLength_8b;
    USART_InitStruct->USART_StopBits = USART_StopBits_1;
    USART_InitStruct->USART_Parity = USART_Parity_No ;
    USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct->USART_HardwareFlowControl =
    USART_HardwareFlowControl_None;
}

/**
 * Initializes USARTx peripheral Clock according to specified
 * parameters in USART_ClockInitStruct.
 * param USARTx: where x can be 1, 2, 3 or 6 to select USART peripheral.
 * param USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef structure
 *       that contains configuration information for  USART peripheral.
 * The Smart Card and Synchronous modes are not available for UART4 and UART5.
 * retval None
 */
void USART_ClockInit(
    USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct
) {
    uint32_t tmpreg = 0x00;

    assert_param(IS_USART_1236_PERIPH(USARTx));
    assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
    assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
    assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
    assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
    tmpreg = USARTx->CR2; /* USART CR2 Configuration */
    /* Clear CLKEN, CPOL, CPHA and LBCL bits */
    tmpreg &= (uint32_t) ~((uint32_t) CR2_CLOCK_CLEAR_MASK);
    /* Configure USART Clock, CPOL, CPHA and LastBit */
    /* Set CLKEN bit according to USART_Clock value */
    /* Set CPOL bit according to USART_CPOL value */
    /* Set CPHA bit according to USART_CPHA value */
    /* Set LBCL bit according to USART_LastBit value */
    tmpreg |= (uint32_t) (
        USART_ClockInitStruct->USART_Clock |
        USART_ClockInitStruct->USART_CPOL |
        USART_ClockInitStruct->USART_CPHA |
        USART_ClockInitStruct->USART_LastBit
    );
    USARTx->CR2 = (uint16_t) tmpreg; /* Write to USART CR2 */
}

/**
 * Fills each USART_ClockInitStruct member with its default value.
 * param USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct) {
    /* USART_ClockInitStruct members default value */
    USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
    USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
    USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
 * Enables or disables specified USART peripheral.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of USARTx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected USART by setting UE bit in CR1 register */
        USARTx->CR1 |= USART_CR1_UE;
    } else {
        /* Disable selected USART by clearing UE bit in CR1 register */
        USARTx->CR1 &= (uint16_t) ~((uint16_t) USART_CR1_UE);
    }
}

/**
 * Sets system clock prescaler.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_Prescaler: specifies prescaler clock.
 * The function is used for IrDA mode with UART4 and UART5.
 * retval None
 */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    USARTx->GTPR &= USART_GTPR_GT; /* Clear USART prescaler */
    USARTx->GTPR |= USART_Prescaler; /* Set USART prescaler */
}

/**
 * Enables or disables USART's 8x oversampling mode.
 * This function has to be called before calling USART_Init() function
 * in order to have correct baudrate Divider value.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of USART 8x oversampling mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable 8x Oversampling mode by setting OVER8 bit in CR1 register */
        USARTx->CR1 |= USART_CR1_OVER8;
    } else {
        /* Disable 8x Oversampling mode by clearing OVER8 bit in CR1 reg */
        USARTx->CR1 &= (uint16_t) ~((uint16_t) USART_CR1_OVER8);
    }
}

/**
 * Enables or disables USART's one bit sampling method.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of USART one bit sampling method.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable one bit method by setting ONEBITE bit in CR3 register */
        USARTx->CR3 |= USART_CR3_ONEBIT;
    } else {
        /* Disable one bit method by clearing ONEBITE bit in CR3 register */
        USARTx->CR3 &= (uint16_t) ~((uint16_t) USART_CR3_ONEBIT);
    }
}

/**
 * Transmits single data through USARTx peripheral.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param Data: data to transmit.
 * retval None
 */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DATA(Data));
    USARTx->DR = (Data & (uint16_t) 0x01FF); /* Transmit Data */
}

/**
 * Returns most recent received data by USARTx peripheral.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * retval The received data.
 */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    return (uint16_t) (USARTx->DR & (uint16_t) 0x01FF); /* Receive Data */
}

/**
 * Sets address of USART node.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_Address: Indicates address of USART node.
 * retval None
 */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_ADDRESS(USART_Address));
    /* Clear USART address */
    USARTx->CR2 &= (uint16_t) ~((uint16_t) USART_CR2_ADD);
    USARTx->CR2 |= USART_Address; /* Set USART address node */
}

/**
 * Determines if USART is in mute mode or not.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of USART mute mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable USART mute mode  by setting RWU bit in CR1 register */
        USARTx->CR1 |= USART_CR1_RWU;
    } else {
        /* Disable USART mute mode by clearing RWU bit in CR1 register */
        USARTx->CR1 &= (uint16_t) ~((uint16_t) USART_CR1_RWU);
    }
}
/**
 * Selects USART WakeUp method.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or 
 *       UART peripheral.
 * param USART_WakeUp: specifies USART wakeup method.
 *   This parameter can be one of following values:
 *       arg USART_WakeUp_IdleLine: WakeUp by an idle line detection
 *       arg USART_WakeUp_AddressMark: WakeUp by an address mark
 * retval None
 */
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_WAKEUP(USART_WakeUp));
    USARTx->CR1 &= (uint16_t) ~((uint16_t) USART_CR1_WAKE);
    USARTx->CR1 |= USART_WakeUp;
}

/**
 * Sets USART LIN Break detection length.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_LINBreakDetectLength: specifies LIN break detection length.
 *   This parameter can be one of following values:
 *       arg USART_LINBreakDetectLength_10b: 10-bit break detection
 *       arg USART_LINBreakDetectLength_11b: 11-bit break detection
 * retval None
 */
void USART_LINBreakDetectLengthConfig(
    USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength
) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));
    USARTx->CR2 &= (uint16_t) ~((uint16_t) USART_CR2_LBDL);
    USARTx->CR2 |= USART_LINBreakDetectLength;
}

/**
 * Enables or disables USART's LIN mode.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of USART LIN mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable LIN mode by setting LINEN bit in CR2 register */
        USARTx->CR2 |= USART_CR2_LINEN;
    } else {
        /* Disable LIN mode by clearing LINEN bit in CR2 register */
        USARTx->CR2 &= (uint16_t) ~((uint16_t) USART_CR2_LINEN);
    }
}

/**
 * Transmits break characters.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * retval None
 */
void USART_SendBreak(USART_TypeDef* USARTx) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    USARTx->CR1 |= USART_CR1_SBK; /* Send break characters */
}

/**
 * Enables or disables USART's Half Duplex communication.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of USART Communication.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable Half-Duplex mode by setting HDSEL bit in CR3 register */
        USARTx->CR3 |= USART_CR3_HDSEL;
    } else {
        /* Disable Half-Duplex mode by clearing HDSEL bit in CR3 register */
        USARTx->CR3 &= (uint16_t) ~((uint16_t) USART_CR3_HDSEL);
    }
}

/**
 * Sets specified USART guard time.
 * param USARTx: where x can be 1, 2, 3 or 6 to select USART or
 *       UART peripheral.
 * param USART_GuardTime: specifies guard time.
 * retval None
 */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime) {
    assert_param(IS_USART_1236_PERIPH(USARTx));
    USARTx->GTPR &= USART_GTPR_PSC; /* Clear USART Guard time */
    /* Set USART guard time */
    USARTx->GTPR |= (uint16_t) ((uint16_t) USART_GuardTime << 0x08);
}

/**
 * Enables or disables USART's Smart Card mode.
 * param USARTx: where x can be 1, 2, 3 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of Smart Card mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_1236_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable SC mode by setting SCEN bit in CR3 register */
        USARTx->CR3 |= USART_CR3_SCEN;
    } else {
        /* Disable SC mode by clearing SCEN bit in CR3 register */
        USARTx->CR3 &= (uint16_t) ~((uint16_t) USART_CR3_SCEN);
    }
}

/**
 * Enables or disables NACK transmission.
 * param USARTx: where x can be 1, 2, 3 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of NACK transmission.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_1236_PERIPH(USARTx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable NACK transmission by setting NACK bit in CR3 register */
        USARTx->CR3 |= USART_CR3_NACK;
    } else {
        /* Disable NACK transmission by clearing NACK bit in CR3 register */
        USARTx->CR3 &= (uint16_t) ~((uint16_t) USART_CR3_NACK);
    }
}

/**
 * Configures USART's IrDA interface.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or 
 *       UART peripheral.
 * param USART_IrDAMode: specifies IrDA mode.
 *   This parameter can be one of following values:
 *       arg USART_IrDAMode_LowPower
 *       arg USART_IrDAMode_Normal
 * retval None
 */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));
    USARTx->CR3 &= (uint16_t) ~((uint16_t) USART_CR3_IRLP);
    USARTx->CR3 |= USART_IrDAMode;
}

/**
 * Enables or disables USART's IrDA interface.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param NewState: new state of IrDA mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable IrDA mode by setting IREN bit in CR3 register */
        USARTx->CR3 |= USART_CR3_IREN;
    } else {
        /* Disable IrDA mode by clearing IREN bit in CR3 register */
        USARTx->CR3 &= (uint16_t) ~((uint16_t) USART_CR3_IREN);
    }
}

/**
 * Enables or disables USART's DMA interface.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_DMAReq: specifies DMA request.
 *   This parameter can be any combination of following values:
 *       arg USART_DMAReq_Tx: USART DMA transmit request
 *       arg USART_DMAReq_Rx: USART DMA receive request
 * param NewState: new state of DMA Request sources.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_DMACmd(
    USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState
) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DMAREQ(USART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /**
         * Enable DMA transfer for selected requests by setting DMAT and/or
         * DMAR bits in USART CR3 register 
         */
        USARTx->CR3 |= USART_DMAReq;
    } else {
        /**
         * Disable DMA transfer for selected requests
         * by clearing DMAT and/or DMAR bits in USART CR3 register 
         */
        USARTx->CR3 &= (uint16_t) ~USART_DMAReq;
    }
}

/**
 * Enables or disables specified USART interrupts.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_IT: specifies USART interrupt sources to be enabled or disabled.
 *   This parameter can be one of following values:
 *       arg USART_IT_CTS: CTS change interrupt
 *       arg USART_IT_LBD: LIN Break detection interrupt
 *       arg USART_IT_TXE: Transmit Data Register empty interrupt
 *       arg USART_IT_TC: Transmission complete interrupt
 *       arg USART_IT_RXNE: Receive Data register not empty interrupt
 *       arg USART_IT_IDLE: Idle line detection interrupt
 *       arg USART_IT_PE: Parity Error interrupt
 *       arg USART_IT_ERR: Error interrupt(Frame error, noise error,
 *           overrun error)
 * param NewState: new state of specified USARTx interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void USART_ITConfig(
    USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState
) {
    uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
    uint32_t usartxbase = 0x00;

    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CONFIG_IT(USART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* The CTS interrupt is not available for UART4 and UART5 */
    if (USART_IT == USART_IT_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }
    usartxbase = (uint32_t) USARTx;
    usartreg = (((uint8_t) USART_IT) >> 0x05); /* Get USART register index */
    itpos = USART_IT & IT_MASK; /* Get interrupt position */
    itmask = (((uint32_t) 0x01) << itpos);
    if (usartreg == 0x01) {
        usartxbase += 0x0C;
    } else if (usartreg == 0x02) {
        usartxbase += 0x10;
    } else {
        usartxbase += 0x14;
    }
    if (NewState != DISABLE) {
        *(__IO uint32_t*) usartxbase |= itmask;
    } else {
        *(__IO uint32_t*) usartxbase &= ~itmask;
    }
}

/**
 * Checks whether specified USART flag is set or not.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_FLAG: specifies flag to check.
 *   This parameter can be one of following values:
 *       arg USART_FLAG_CTS: CTS Change flag (not available
 *           for UART4 and UART5)
 *       arg USART_FLAG_LBD: LIN Break detection flag
 *       arg USART_FLAG_TXE: Transmit data register empty flag
 *       arg USART_FLAG_TC: Transmission Complete flag
 *       arg USART_FLAG_RXNE: Receive data register not empty flag
 *       arg USART_FLAG_IDLE: Idle Line detection flag
 *       arg USART_FLAG_ORE: OverRun Error flag
 *       arg USART_FLAG_NE: Noise Error flag
 *       arg USART_FLAG_FE: Framing Error flag
 *       arg USART_FLAG_PE: Parity Error flag
 * retval The new state of USART_FLAG (SET or RESET).
 */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG) {
    FlagStatus bitstatus = RESET;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_FLAG(USART_FLAG));
    /* The CTS flag is not available for UART4 and UART5 */
    if (USART_FLAG == USART_FLAG_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }
    if ((USARTx->SR & USART_FLAG) != (uint16_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears USARTx's pending flags.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_FLAG: specifies flag to clear.
 *   This parameter can be any combination of following values:
 *       arg USART_FLAG_CTS: CTS Change flag (not available
 *           for UART4 and UART5).
 *       arg USART_FLAG_LBD: LIN Break detection flag.
 *       arg USART_FLAG_TC: Transmission Complete flag.
 *       arg USART_FLAG_RXNE: Receive data register not empty flag.
 * PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun 
 * error) and IDLE (Idle line detected) flags are cleared by software 
 * sequence: a read operation to USART_SR register (USART_GetFlagStatus())
 * followed by a read operation to USART_DR register (USART_ReceiveData())
 * RXNE flag can be also cleared by a read to USART_DR register 
 * (USART_ReceiveData()).
 * TC flag can be also cleared by software sequence: a read operation to 
 * USART_SR register (USART_GetFlagStatus()) followed by a write operation
 * to USART_DR register (USART_SendData()).
 * TXE flag is cleared only by a write to USART_DR register 
 * (USART_SendData()).
 * retval None
 */
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG) {
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
    /* The CTS flag is not available for UART4 and UART5 */
    if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }
    USARTx->SR = (uint16_t) ~USART_FLAG;
}

/**
 * Checks whether specified USART interrupt has occurred or not.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_IT: specifies USART interrupt source to check.
 *   This parameter can be one of following values:
 *       arg USART_IT_CTS: CTS change interrupt (not available
 *           for UART4 and UART5)
 *       arg USART_IT_LBD: LIN Break detection interrupt
 *       arg USART_IT_TXE: Transmit Data Register empty interrupt
 *       arg USART_IT_TC: Transmission complete interrupt
 *       arg USART_IT_RXNE: Receive Data register not empty interrupt
 *       arg USART_IT_IDLE: Idle line detection interrupt
 *       arg USART_IT_ORE_RX : OverRun Error interrupt if RXNEIE bit is set
 *       arg USART_IT_ORE_ER : OverRun Error interrupt if EIE bit is set
 *       arg USART_IT_NE: Noise Error interrupt
 *       arg USART_IT_FE: Framing Error interrupt
 *       arg USART_IT_PE: Parity Error interrupt
 * retval The new state of USART_IT (SET or RESET).
 */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT) {
    uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
    ITStatus bitstatus = RESET;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_GET_IT(USART_IT));
    /* The CTS interrupt is not available for UART4 and UART5 */
    if (USART_IT == USART_IT_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }
    /* Get USART register index */
    usartreg = (((uint8_t) USART_IT) >> 0x05);
    itmask = USART_IT & IT_MASK; /* Get interrupt position */
    itmask = (uint32_t) 0x01 << itmask;
    if (usartreg == 0x01) {
        itmask &= USARTx->CR1;
    } else if (usartreg == 0x02) {
        itmask &= USARTx->CR2;
    } else {
        itmask &= USARTx->CR3;
    }
    bitpos = USART_IT >> 0x08;
    bitpos = (uint32_t) 0x01 << bitpos;
    bitpos &= USARTx->SR;
    if ((itmask != (uint16_t) RESET)&&(bitpos != (uint16_t) RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears USARTx's interrupt pending bits.
 * param USARTx: where x can be 1, 2, 3, 4, 5 or 6 to select USART or
 *       UART peripheral.
 * param USART_IT: specifies interrupt pending bit to clear
 *   This parameter can be one of following values:
 *       arg USART_IT_CTS: CTS change interrupt (not available for UART
 *           and UART5)
 *       arg USART_IT_LBD: LIN Break detection interrupt
 *       arg USART_IT_TC: Transmission complete interrupt.
 *       arg USART_IT_RXNE: Receive Data register not empty interrupt.
 *
 * PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
 * error) and IDLE (Idle line detected) pending bits are cleared by
 * software sequence: a read operation to USART_SR register
 * (USART_GetITStatus()) followed by a read operation to USART_DR register
 * (USART_ReceiveData()).
 * RXNE pending bit can be also cleared by a read to USART_DR register
 * (USART_ReceiveData()).
 * TC pending bit can be also cleared by software sequence: a read
 * operation to USART_SR register (USART_GetITStatus()) followed by a write
 * operation to USART_DR register (USART_SendData()).
 * TXE pending bit is cleared only by a write to USART_DR register
 * (USART_SendData()).
 * retval None
 */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT) {
    uint16_t bitpos = 0x00, itmask = 0x00;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_IT(USART_IT));
    /* The CTS interrupt is not available for UART4 and UART5 */
    if (USART_IT == USART_IT_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }
    bitpos = USART_IT >> 0x08;
    itmask = ((uint16_t) 0x01 << (uint16_t) bitpos);
    USARTx->SR = (uint16_t) ~itmask;
}

