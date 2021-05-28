/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_can.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Controller area network (CAN) peripheral:
 *     - Initialization and Configuration
 *     - CAN Frames Transmission
 *     - CAN Frames Reception
 *     - Operation modes switch
 *     - Error management
 *     - Interrupts and flags
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_can is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_can is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_can.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* CAN Master Control Register bits */
#define MCR_DBF ((uint32_t) 0x00010000) /* software master reset */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ ((uint32_t) 0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FMR_FINIT ((uint32_t) 0x00000001) /* Filter init mode */

/* Time out for INAK bit */
#define INAK_TIMEOUT ((uint32_t) 0x0000FFFF)

/* Time out for SLAK bit */
#define SLAK_TIMEOUT ((uint32_t) 0x0000FFFF)

/* Flags in TSR register */
#define CAN_FLAGS_TSR ((uint32_t) 0x08000000)

/* Flags in RF1R register */
#define CAN_FLAGS_RF1R ((uint32_t) 0x04000000)

/* Flags in RF0R register */
#define CAN_FLAGS_RF0R ((uint32_t) 0x02000000)

/* Flags in MSR register */
#define CAN_FLAGS_MSR ((uint32_t) 0x01000000)

/* Flags in ESR register */
#define CAN_FLAGS_ESR ((uint32_t) 0x00F00000)

/* Mailboxes definition */
#define CAN_TXMAILBOX_0 ((uint8_t) 0x00)
#define CAN_TXMAILBOX_1 ((uint8_t) 0x01)
#define CAN_TXMAILBOX_2 ((uint8_t) 0x02)

#define CAN_MODE_MASK ((uint32_t) 0x00000003)

static ITStatus CheckITStatus(uint32_t CAN_Reg, uint32_t It_Bit);

/**
 * Deinitializes CAN peripheral registers to their default reset values
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * retval None.
 */
void CAN_DeInit(CAN_TypeDef* CANx) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    if (CANx == CAN1) {
        /* Enable CAN1 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, ENABLE);
        /* Release CAN1 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, DISABLE);
    } else {
        /* Enable CAN2 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, ENABLE);
        /* Release CAN2 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, DISABLE);
    }
}

/**
 * Initializes CAN peripheral according to specified parameters in
 * CAN_InitStruct.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * param CAN_InitStruct: pointer to a CAN_InitTypeDef structure that contains
 *       configuration information for CAN peripheral.
 * retval Constant indicates initialization succeed which will be
 *        CAN_InitStatus_Failed or CAN_InitStatus_Success.
 */
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct) {
    uint8_t InitStatus = CAN_InitStatus_Failed;
    uint32_t wait_ack = 0x00000000;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TTCM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_ABOM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_AWUM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_NART));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_RFLM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TXFP));
    assert_param(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
    assert_param(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
    assert_param(IS_CAN_BS1(CAN_InitStruct->CAN_BS1));
    assert_param(IS_CAN_BS2(CAN_InitStruct->CAN_BS2));
    assert_param(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));
    CANx->MCR &= (~(uint32_t) CAN_MCR_SLEEP); /* Exit from sleep mode */
    CANx->MCR |= CAN_MCR_INRQ; /* Request initialisation */
    /* Wait acknowledge */
    while (
        ((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) &&
        (wait_ack != INAK_TIMEOUT)
    ) {
        wait_ack++;
    }
    /* Check acknowledge */
    if ((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) {
        InitStatus = CAN_InitStatus_Failed;
    } else {
        /* Set time triggered communication mode */
        if (CAN_InitStruct->CAN_TTCM == ENABLE) {
            CANx->MCR |= CAN_MCR_TTCM;
        } else {
            CANx->MCR &= ~(uint32_t) CAN_MCR_TTCM;
        }
        /* Set automatic bus-off management */
        if (CAN_InitStruct->CAN_ABOM == ENABLE) {
            CANx->MCR |= CAN_MCR_ABOM;
        } else {
            CANx->MCR &= ~(uint32_t) CAN_MCR_ABOM;
        }
        /* Set automatic wake-up mode */
        if (CAN_InitStruct->CAN_AWUM == ENABLE) {
            CANx->MCR |= CAN_MCR_AWUM;
        } else {
            CANx->MCR &= ~(uint32_t) CAN_MCR_AWUM;
        }
        /* Set no automatic retransmission */
        if (CAN_InitStruct->CAN_NART == ENABLE) {
            CANx->MCR |= CAN_MCR_NART;
        } else {
           CANx->MCR &= ~(uint32_t) CAN_MCR_NART;
        }
        /* Set receive FIFO locked mode */
        if (CAN_InitStruct->CAN_RFLM == ENABLE) {
            CANx->MCR |= CAN_MCR_RFLM;
        } else {
            CANx->MCR &= ~(uint32_t) CAN_MCR_RFLM;
        }
        /* Set transmit FIFO priority */
        if (CAN_InitStruct->CAN_TXFP == ENABLE) {
            CANx->MCR |= CAN_MCR_TXFP;
        } else {
            CANx->MCR &= ~(uint32_t) CAN_MCR_TXFP;
        }
        /* Set bit timing register */
        CANx->BTR = (uint32_t) (
            ((uint32_t) CAN_InitStruct->CAN_Mode << 30) |
            ((uint32_t) CAN_InitStruct->CAN_SJW << 24) |
            ((uint32_t) CAN_InitStruct->CAN_BS1 << 16) |
            ((uint32_t) CAN_InitStruct->CAN_BS2 << 20) |
            ((uint32_t) CAN_InitStruct->CAN_Prescaler - 1)
        );
        /* Request leave initialisation */
        CANx->MCR &= ~(uint32_t) CAN_MCR_INRQ;
        wait_ack = 0; /* Wait acknowledge */
        while (
            ((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) &&
            (wait_ack != INAK_TIMEOUT)
        ) {
            wait_ack++;
        }
        /* and check acknowledged */
        if ((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) {
            InitStatus = CAN_InitStatus_Failed;
        } else {
            InitStatus = CAN_InitStatus_Success ;
        }
    }
    return InitStatus; /* At this step, return status of initialization */
}

/**
 * Configures CAN reception filter according to specified parameters
 * in CAN_FilterInitStruct.
 * param CAN_FilterInitStruct: pointer to a CAN_FilterInitTypeDef structure
 *       that contains configuration information.
 * retval None
 */
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct) {
    uint32_t filter_number_bit_pos = 0;

    assert_param(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
    assert_param(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
    assert_param(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
    assert_param(
        IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment)
    );
    assert_param(
        IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation)
    );
    filter_number_bit_pos = (
        ((uint32_t) 1) << CAN_FilterInitStruct->CAN_FilterNumber
    );
    CAN1->FMR |= FMR_FINIT; /* Initialisation mode for filter */
    /* Filter Deactivation */
    CAN1->FA1R &= ~(uint32_t) filter_number_bit_pos;
    /* Filter Scale */
    if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit) {
        /* 16-bit scale for filter */
        CAN1->FS1R &= ~(uint32_t) filter_number_bit_pos;
        /* First 16-bit identifier and First 16-bit mask */
        /* Or First 16-bit identifier and Second 16-bit identifier */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = (
            (
                (
                    0x0000FFFF &
                    (uint32_t) CAN_FilterInitStruct->CAN_FilterMaskIdLow
                ) << 16
            ) |
            (0x0000FFFF & (uint32_t) CAN_FilterInitStruct->CAN_FilterIdLow)
        );
        /* Second 16-bit identifier and Second 16-bit mask */
        /* Or Third 16-bit identifier and Fourth 16-bit identifier */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = (
            (
                (
                    0x0000FFFF &
                    (uint32_t) CAN_FilterInitStruct->CAN_FilterMaskIdHigh
                ) << 16
            ) |
            (0x0000FFFF & (uint32_t) CAN_FilterInitStruct->CAN_FilterIdHigh)
        );
    }
    if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit) {
        CAN1->FS1R |= filter_number_bit_pos; /* 32-bit scale for filter */
        /* 32-bit identifier or First 32-bit identifier */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 = (
            (
                (
                    0x0000FFFF &
                    (uint32_t) CAN_FilterInitStruct->CAN_FilterIdHigh
                ) << 16
            ) |
            (0x0000FFFF & (uint32_t) CAN_FilterInitStruct->CAN_FilterIdLow)
        );
        /* 32-bit mask or Second 32-bit identifier */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = (
            (
                (
                    0x0000FFFF &
                    (uint32_t) CAN_FilterInitStruct->CAN_FilterMaskIdHigh
                ) << 16
            ) |
            (0x0000FFFF & (uint32_t) CAN_FilterInitStruct->CAN_FilterMaskIdLow)
        );
    }
    /* Filter Mode */
    if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask) {
        /* Id/Mask mode for filter */
        CAN1->FM1R &= ~(uint32_t) filter_number_bit_pos;
    } else {
        /* Identifier list mode for filter */
        CAN1->FM1R |= (uint32_t) filter_number_bit_pos;
    }
    /* Filter FIFO assignment */
    if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO0) {
        /* FIFO 0 assignation for filter */
        CAN1->FFA1R &= ~(uint32_t) filter_number_bit_pos;
    }
    if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO1) {
        /* FIFO 1 assignation for filter */
        CAN1->FFA1R |= (uint32_t) filter_number_bit_pos;
    }
    /* Filter activation */
    if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE) {
        CAN1->FA1R |= filter_number_bit_pos;
    }
    CAN1->FMR &= ~FMR_FINIT; /* Leave initialisation mode for filter */
}

/**
 * Fills each CAN_InitStruct member with its default value.
 * param CAN_InitStruct: pointer to a CAN_InitTypeDef structure
 *       which ill be initialized.
 * retval None
 */
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct) {
    /* Reset CAN init structure parameters values */
    /* Initialize time triggered communication mode */
    CAN_InitStruct->CAN_TTCM = DISABLE;
    /* Initialize automatic bus-off management */
    CAN_InitStruct->CAN_ABOM = DISABLE;
    /* Initialize automatic wake-up mode */
    CAN_InitStruct->CAN_AWUM = DISABLE;
    /* Initialize no automatic retransmission */
    CAN_InitStruct->CAN_NART = DISABLE;
    /* Initialize receive FIFO locked mode */
    CAN_InitStruct->CAN_RFLM = DISABLE;
    /* Initialize transmit FIFO priority */
    CAN_InitStruct->CAN_TXFP = DISABLE;
    /* Initialize CAN_Mode member */
    CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;
    /* Initialize CAN_SJW member */
    CAN_InitStruct->CAN_SJW = CAN_SJW_1tq;
    /* Initialize CAN_BS1 member */
    CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;
    /* Initialize CAN_BS2 member */
    CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;
    /* Initialize CAN_Prescaler member */
    CAN_InitStruct->CAN_Prescaler = 1;
}

/**
 * Select start bank filter for slave CAN.
 * param CAN_BankNumber: Select start slave bank filter from 1..27.
 * retval None
 */
void CAN_SlaveStartBank(uint8_t CAN_BankNumber) {
    assert_param(IS_CAN_BANKNUMBER(CAN_BankNumber));
    CAN1->FMR |= FMR_FINIT; /* Enter Initialisation mode for filter */
    CAN1->FMR &= (uint32_t) 0xFFFFC0F1; /* Select start slave bank */
    CAN1->FMR |= (uint32_t) (CAN_BankNumber) << 8;
    /* Leave Initialisation mode for filter */
    CAN1->FMR &= ~FMR_FINIT;
}

/**
 * Enables or disables DBG Freeze for CAN.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param NewState: new state of CAN peripheral. 
 *    This parameter can be: ENABLE (CAN reception/transmission is frozen
 *          during debug. Reception FIFOs can still be accessed/controlled
 *          normally) or DISABLE (CAN is working during debug).
 * retval None
 */
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        CANx->MCR |= MCR_DBF; /* Enable Debug Freeze */
    } else {
        CANx->MCR &= ~MCR_DBF; /* Disable Debug Freeze */
    }
}

/**
 * Enables or disables CAN Time TriggerOperation communication mode.
 * DLC must be programmed as 8 in order Time Stamp (2 bytes) to be 
 * sent over CAN bus.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param NewState: Mode new state. This parameter can be: ENABLE or DISABLE.
 *       When enabled, Time stamp (TIME[15:0]) value is  sent in last two
 *       data bytes of 8-byte message: TIME[7:0] in data byte 6 and TIME[15:8]
 *       in data byte 7.
 * retval None
 */
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        CANx->MCR |= CAN_MCR_TTCM; /* Enable TTCM mode */
        /* Set TGT bits */
        CANx->sTxMailBox[0].TDTR |= ((uint32_t) CAN_TDT0R_TGT);
        CANx->sTxMailBox[1].TDTR |= ((uint32_t) CAN_TDT1R_TGT);
        CANx->sTxMailBox[2].TDTR |= ((uint32_t) CAN_TDT2R_TGT);
    } else {
        /* Disable TTCM mode */
        CANx->MCR &= (uint32_t) (~(uint32_t) CAN_MCR_TTCM);
        /* Reset TGT bits */
        CANx->sTxMailBox[0].TDTR &= ((uint32_t) ~CAN_TDT0R_TGT);
        CANx->sTxMailBox[1].TDTR &= ((uint32_t) ~CAN_TDT1R_TGT);
        CANx->sTxMailBox[2].TDTR &= ((uint32_t) ~CAN_TDT2R_TGT);
    }
}

/**
 * Initiates and transmits a CAN frame message.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param TxMessage: pointer to a structure which contains CAN Id,
 * CAN DLC and CAN data.
 * retval The number of mailbox that is used for transmission or
 *     CAN_TxStatus_NoMailBox if there is no empty mailbox.
 */
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage) {
    uint8_t transmit_mailbox = 0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IDTYPE(TxMessage->IDE));
    assert_param(IS_CAN_RTR(TxMessage->RTR));
    assert_param(IS_CAN_DLC(TxMessage->DLC));
    /* Select one empty transmit mailbox */
    if ((CANx->TSR&CAN_TSR_TME0) == CAN_TSR_TME0) {
        transmit_mailbox = 0;
    } else if ((CANx->TSR&CAN_TSR_TME1) == CAN_TSR_TME1) {
        transmit_mailbox = 1;
    } else if ((CANx->TSR&CAN_TSR_TME2) == CAN_TSR_TME2) {
        transmit_mailbox = 2;
    } else {
        transmit_mailbox = CAN_TxStatus_NoMailBox;
    }
    if (transmit_mailbox != CAN_TxStatus_NoMailBox) {
        CANx->sTxMailBox[transmit_mailbox].TIR &= TMIDxR_TXRQ; /* Set up Id */
        if (TxMessage->IDE == CAN_Id_Standard) {
            assert_param(IS_CAN_STDID(TxMessage->StdId));
            CANx->sTxMailBox[transmit_mailbox].TIR |= (
                (TxMessage->StdId << 21) | TxMessage->RTR
            );
        } else {
            assert_param(IS_CAN_EXTID(TxMessage->ExtId));
            CANx->sTxMailBox[transmit_mailbox].TIR |= (
                (TxMessage->ExtId << 3) | TxMessage->IDE | TxMessage->RTR
            );
        }
        TxMessage->DLC &= (uint8_t) 0x0000000F; /* Set up DLC */
        CANx->sTxMailBox[transmit_mailbox].TDTR &= (uint32_t) 0xFFFFFFF0;
        CANx->sTxMailBox[transmit_mailbox].TDTR |= TxMessage->DLC;
        /* Set up data field */
        CANx->sTxMailBox[transmit_mailbox].TDLR = (
            ((uint32_t) TxMessage->Data[3] << 24) |
            ((uint32_t) TxMessage->Data[2] << 16) |
            ((uint32_t) TxMessage->Data[1] << 8) |
            ((uint32_t) TxMessage->Data[0])
        );
        CANx->sTxMailBox[transmit_mailbox].TDHR = (
            ((uint32_t) TxMessage->Data[7] << 24) |
            ((uint32_t) TxMessage->Data[6] << 16) |
            ((uint32_t) TxMessage->Data[5] << 8) |
            ((uint32_t) TxMessage->Data[4])
        );
        /* Request transmission */
        CANx->sTxMailBox[transmit_mailbox].TIR |= TMIDxR_TXRQ;
    }
    return transmit_mailbox;
}

/**
 * Checks transmission status of a CAN Frame.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * param TransmitMailbox: number of mailbox that is used for transmission.
 * retval CAN_TxStatus_Ok if CAN driver transmits message,
 *     CAN_TxStatus_Failed in an other case.
 */
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox) {
    uint32_t state = 0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));
    switch (TransmitMailbox) {
        case (CAN_TXMAILBOX_0):
           state = CANx->TSR & (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0);
            break;
        case (CAN_TXMAILBOX_1):
            state = CANx->TSR & (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1);
            break;
        case (CAN_TXMAILBOX_2):
            state = CANx->TSR & (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2);
            break;
        default:
            state = CAN_TxStatus_Failed;
            break;
    }
    switch (state) {
        /* transmit pending */
        case (0x0): state = CAN_TxStatus_Pending;
            break;
         /* transmit failed */
        case (CAN_TSR_RQCP0 | CAN_TSR_TME0):
            state = CAN_TxStatus_Failed;
            break;
        case (CAN_TSR_RQCP1 | CAN_TSR_TME1):
            state = CAN_TxStatus_Failed;
            break;
        case (CAN_TSR_RQCP2 | CAN_TSR_TME2):
            state = CAN_TxStatus_Failed;
            break;
        /* transmit succeeded */
        case (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0):
            state = CAN_TxStatus_Ok;
            break;
        case (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1):
            state = CAN_TxStatus_Ok;
            break;
        case (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2):
            state = CAN_TxStatus_Ok;
            break;
        default: state = CAN_TxStatus_Failed;
            break;
    }
    return (uint8_t) state;
}

/**
 * Cancels a transmit request.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * param Mailbox: Mailbox number.
 * retval None
 */
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));
    /* abort transmission */
    switch (Mailbox) {
        case (CAN_TXMAILBOX_0): CANx->TSR |= CAN_TSR_ABRQ0;
            break;
        case (CAN_TXMAILBOX_1): CANx->TSR |= CAN_TSR_ABRQ1;
            break;
        case (CAN_TXMAILBOX_2): CANx->TSR |= CAN_TSR_ABRQ2;
            break;
        default:
            break;
    }
}

/**
 * Receives a correct CAN frame.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * param FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
 * param RxMessage: pointer to a structure receive frame which contains CAN Id,
 *         CAN DLC, CAN data and FMI number.
 * retval None
 */
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));
    /* Get Id */
    RxMessage->IDE = (uint8_t) (0x04 & CANx->sFIFOMailBox[FIFONumber].RIR);
    if (RxMessage->IDE == CAN_Id_Standard) {
        RxMessage->StdId = (uint32_t) (
            0x000007FF & (CANx->sFIFOMailBox[FIFONumber].RIR >> 21)
        );
    } else {
        RxMessage->ExtId = (uint32_t) (
            0x1FFFFFFF & (CANx->sFIFOMailBox[FIFONumber].RIR >> 3)
        );
    }
    RxMessage->RTR = (uint8_t) (0x02 & CANx->sFIFOMailBox[FIFONumber].RIR);
    /* Get DLC */
    RxMessage->DLC = (uint8_t) (0x0F & CANx->sFIFOMailBox[FIFONumber].RDTR);
    /* Get FMI */
    RxMessage->FMI = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDTR >> 8)
    );
    /* Get data field */
    RxMessage->Data[0] = (uint8_t) (
        0xFF & CANx->sFIFOMailBox[FIFONumber].RDLR
    );
    RxMessage->Data[1] = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 8)
    );
    RxMessage->Data[2] = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 16)
    );
    RxMessage->Data[3] = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 24)
    );
    RxMessage->Data[4] = (uint8_t) (
        0xFF & CANx->sFIFOMailBox[FIFONumber].RDHR
    );
    RxMessage->Data[5] = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 8)
    );
    RxMessage->Data[6] = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 16)
    );
    RxMessage->Data[7] = (uint8_t) (
        0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 24)
    );
    /* Release FIFO */
    /* Release FIFO0 */
    if (FIFONumber == CAN_FIFO0) {
        CANx->RF0R |= CAN_RF0R_RFOM0;
    } else {
        CANx->RF1R |= CAN_RF1R_RFOM1;
    }
}

/**
 * Releases specified receive FIFO.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * param FIFONumber: FIFO to release, CAN_FIFO0 or CAN_FIFO1.
 * retval None
 */
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));
    /* Release FIFO0 */
    if (FIFONumber == CAN_FIFO0) {
        CANx->RF0R |= CAN_RF0R_RFOM0;
    } else {
        CANx->RF1R |= CAN_RF1R_RFOM1;
    }
}

/**
 * Returns number of pending received messages.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * param FIFONumber: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
 * retval NbMessage: which is number of pending message.
 */
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber) {
    uint8_t message_pending = 0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));
    if (FIFONumber == CAN_FIFO0) {
        message_pending = (uint8_t) (CANx->RF0R & (uint32_t) 0x03);
    } else if (FIFONumber == CAN_FIFO1) {
        message_pending = (uint8_t) (CANx->RF1R & (uint32_t) 0x03);
    } else {
        message_pending = 0;
    }
    return message_pending;
}

/**
 * Selects CAN Operation mode.
 * param CAN_OperatingMode: CAN Operating Mode.
 *   This parameter can be one of @ref CAN_OperatingMode_TypeDef enumeration.
 * retval status of requested mode which can be
 *     - CAN_ModeStatus_Failed:  CAN failed entering specific mode 
 *     - CAN_ModeStatus_Success: CAN Succeed entering specific mode 
 */
uint8_t CAN_OperatingModeRequest(
    CAN_TypeDef* CANx, uint8_t CAN_OperatingMode
) {
    uint8_t status = CAN_ModeStatus_Failed;
    uint32_t timeout = INAK_TIMEOUT; /* Timeout for INAK or for SLAK bits*/

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_OPERATING_MODE(CAN_OperatingMode));
    if (CAN_OperatingMode == CAN_OperatingMode_Initialization) {
        /* Request initialisation */
        CANx->MCR = (uint32_t) (
            (CANx->MCR & (uint32_t) (~(uint32_t) CAN_MCR_SLEEP)) |
            CAN_MCR_INRQ
        );
        /* Wait acknowledge */
        while (
            ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK) && (timeout != 0)
        ) {
            timeout--;
        }
        if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK) {
            status = CAN_ModeStatus_Failed;
        } else {
            status = CAN_ModeStatus_Success;
        }
    } else  if (CAN_OperatingMode == CAN_OperatingMode_Normal) {
        /* Request leave initialisation and sleep mode and enter Normal mode */
        CANx->MCR &= (uint32_t) (~(CAN_MCR_SLEEP | CAN_MCR_INRQ));
        /* Wait acknowledge */
        while (((CANx->MSR & CAN_MODE_MASK) != 0) && (timeout != 0)) {
            timeout--;
        }
        if ((CANx->MSR & CAN_MODE_MASK) != 0) {
            status = CAN_ModeStatus_Failed;
        } else {
            status = CAN_ModeStatus_Success;
        }
    } else  if (CAN_OperatingMode == CAN_OperatingMode_Sleep) {
        /* Request Sleep mode */
        CANx->MCR = (uint32_t) (
            (CANx->MCR & (uint32_t) (~(uint32_t) CAN_MCR_INRQ)) |
            CAN_MCR_SLEEP
        );
        /* Wait acknowledge */
        while (
            ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK) && (timeout!=0)
        ) {
            timeout--;
        }
        if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK) {
            status = CAN_ModeStatus_Failed;
        } else {
            status = CAN_ModeStatus_Success;
        }
    } else {
        status = CAN_ModeStatus_Failed;
    }
    return  (uint8_t) status;
}

/**
 * Enters Sleep (low power) mode.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * retval CAN_Sleep_Ok if sleep entered, CAN_Sleep_Failed otherwise.
 */
uint8_t CAN_Sleep(CAN_TypeDef* CANx) {
    uint8_t sleepstatus = CAN_Sleep_Failed;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    /* Request Sleep mode */
    CANx->MCR = (
        ((CANx->MCR) & (uint32_t) (~(uint32_t) CAN_MCR_INRQ)) | CAN_MCR_SLEEP
    );
    /* Sleep mode status */
    if ((CANx->MSR & (CAN_MSR_SLAK|CAN_MSR_INAK)) == CAN_MSR_SLAK) {
        sleepstatus =  CAN_Sleep_Ok; /* Sleep mode not entered */
    }
    return (uint8_t) sleepstatus; /* return sleep mode status */
}

/**
 * Wakes up CAN peripheral from sleep mode.
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * retval CAN_WakeUp_Ok if sleep mode left, CAN_WakeUp_Failed otherwise.
 */
uint8_t CAN_WakeUp(CAN_TypeDef* CANx) {
    uint32_t wait_slak = SLAK_TIMEOUT;
    uint8_t wakeupstatus = CAN_WakeUp_Failed;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    CANx->MCR &= ~(uint32_t) CAN_MCR_SLEEP; /* Wake up request */
    /* Sleep mode status */
    while (
        ((CANx->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK) && (wait_slak != 0x00)
    ) {
        wait_slak--;
    }
    if ((CANx->MSR & CAN_MSR_SLAK) != CAN_MSR_SLAK) {
        /* wake up done : Sleep mode exited */
        wakeupstatus = CAN_WakeUp_Ok;
    }
    return (uint8_t) wakeupstatus; /* return wakeup status */
}

/**
 * Returns CANx's last error code (LEC).
 * param CANx: where x can be 1 or 2 to select CAN peripheral.
 * retval Error code:
 *     - CAN_ERRORCODE_NoErr: No Error  
 *     - CAN_ERRORCODE_StuffErr: Stuff Error
 *     - CAN_ERRORCODE_FormErr: Form Error
 *     - CAN_ERRORCODE_ACKErr : Acknowledgment Error
 *     - CAN_ERRORCODE_BitRecessiveErr: Bit Recessive Error
 *     - CAN_ERRORCODE_BitDominantErr: Bit Dominant Error
 *     - CAN_ERRORCODE_CRCErr: CRC Error
 *     - CAN_ERRORCODE_SoftwareSetErr: Software Set Error 
 */
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx) {
    uint8_t errorcode=0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    /* Get error code */
    errorcode = (((uint8_t) CANx->ESR) & (uint8_t) CAN_ESR_LEC);
    return errorcode; /* Return error code*/
}

/**
 * Returns CANx Receive Error Counter (REC).
 * In case of an error during reception, this counter is incremented
 * by 1 or by 8 depending on error condition as defined by CAN
 * standard. After every successful reception, counter is
 * decremented by 1 or reset to 120 if its value was higher than 128.
 * When counter value exceeds 127, CAN controller enters 
 * error passive state.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * retval CAN Receive Error Counter. 
 */
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx) {
    uint8_t counter=0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    /* Get Receive Error Counter */
    counter = (uint8_t) ((CANx->ESR & CAN_ESR_REC) >> 24);
    return counter; /* Return Receive Error Counter */
}

/**
 * Returns LSB of 9-bit CANx Transmit Error Counter(TEC).
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * retval LSB of 9-bit CAN Transmit Error Counter.
 */
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx) {
    uint8_t counter=0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    /* Get LSB of 9-bit CANx Transmit Error Counter(TEC) */
    counter = (uint8_t) ((CANx->ESR & CAN_ESR_TEC) >> 16);
    /* Return LSB of 9-bit CANx Transmit Error Counter(TEC) */
    return counter;
}

/**
 * Enables or disables specified CANx interrupts.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param CAN_IT: specifies CAN interrupt sources to be enabled or disabled.
 *    This parameter can be: 
 *        arg CAN_IT_TME: Transmit mailbox empty Interrupt 
 *        arg CAN_IT_FMP0: FIFO 0 message pending Interrupt 
 *        arg CAN_IT_FF0: FIFO 0 full Interrupt
 *        arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
 *        arg CAN_IT_FMP1: FIFO 1 message pending Interrupt 
 *        arg CAN_IT_FF1: FIFO 1 full Interrupt
 *        arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
 *        arg CAN_IT_WKU: Wake-up Interrupt
 *        arg CAN_IT_SLK: Sleep acknowledge Interrupt
 *        arg CAN_IT_EWG: Error warning Interrupt
 *        arg CAN_IT_EPV: Error passive Interrupt
 *        arg CAN_IT_BOF: Bus-off Interrupt
 *        arg CAN_IT_LEC: Last error code Interrupt
 *        arg CAN_IT_ERR: Error Interrupt
 * param NewState: new state of CAN interrupts.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void CAN_ITConfig(
    CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState
) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IT(CAN_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        CANx->IER |= CAN_IT; /* Enable selected CANx interrupt */
    } else {
        CANx->IER &= ~CAN_IT; /* Disable selected CANx interrupt */
    }
}

/**
 * Checks whether specified CAN flag is set or not.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param CAN_FLAG: specifies flag to check.
 *    This parameter can be one of following values:
 *        arg CAN_FLAG_RQCP0: Request MailBox0 Flag
 *        arg CAN_FLAG_RQCP1: Request MailBox1 Flag
 *        arg CAN_FLAG_RQCP2: Request MailBox2 Flag
 *        arg CAN_FLAG_FMP0: FIFO 0 Message Pending Flag
 *        arg CAN_FLAG_FF0: FIFO 0 Full Flag
 *        arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag 
 *        arg CAN_FLAG_FMP1: FIFO 1 Message Pending Flag
 *        arg CAN_FLAG_FF1: FIFO 1 Full Flag
 *        arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag
 *        arg CAN_FLAG_WKU: Wake up Flag
 *        arg CAN_FLAG_SLAK: Sleep acknowledge Flag
 *        arg CAN_FLAG_EWG: Error Warning Flag
 *        arg CAN_FLAG_EPV: Error Passive Flag
 *        arg CAN_FLAG_BOF: Bus-Off Flag
 *        arg CAN_FLAG_LEC: Last error code Flag
 * retval The new state of CAN_FLAG (SET or RESET).
 */
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_GET_FLAG(CAN_FLAG));
    if ((CAN_FLAG & CAN_FLAGS_ESR) != (uint32_t) RESET) {
        /* Check status of specified CAN flag */
        if ((CANx->ESR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t) RESET) {
            bitstatus = SET; /* CAN_FLAG is set */
        } else {
            bitstatus = RESET; /* CAN_FLAG is reset */
        }
    } else if ((CAN_FLAG & CAN_FLAGS_MSR) != (uint32_t) RESET) {
        /* Check status of specified CAN flag */
        if ((CANx->MSR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t) RESET) {
            bitstatus = SET; /* CAN_FLAG is set */
        } else {
            bitstatus = RESET; /* CAN_FLAG is reset */
        }
    } else if((CAN_FLAG & CAN_FLAGS_TSR) != (uint32_t) RESET) {
        /* Check status of specified CAN flag */
        if ((CANx->TSR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t) RESET) {
            bitstatus = SET; /* CAN_FLAG is set */
        } else {
            bitstatus = RESET; /* CAN_FLAG is reset */
        }
    } else if ((CAN_FLAG & CAN_FLAGS_RF0R) != (uint32_t) RESET) {
        /* Check status of specified CAN flag */
        if ((CANx->RF0R & (CAN_FLAG & 0x000FFFFF)) != (uint32_t) RESET) {
            bitstatus = SET; /* CAN_FLAG is set */
        } else {
            bitstatus = RESET; /* CAN_FLAG is reset */
        }
    } else {
        /* Check status of specified CAN flag */
        if (
            (uint32_t) (CANx->RF1R & (CAN_FLAG & 0x000FFFFF)) !=
            (uint32_t) RESET
        ) {
            bitstatus = SET; /* CAN_FLAG is set */
        } else {
            bitstatus = RESET; /* CAN_FLAG is reset */
        }
    }
    return bitstatus; /* Return CAN_FLAG status */
}

/**
 * Clears CAN's pending flags.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param CAN_FLAG: specifies flag to clear.
 *    This parameter can be one of following values:
 *        arg CAN_FLAG_RQCP0: Request MailBox0 Flag
 *        arg CAN_FLAG_RQCP1: Request MailBox1 Flag
 *        arg CAN_FLAG_RQCP2: Request MailBox2 Flag
 *        arg CAN_FLAG_FF0: FIFO 0 Full Flag
 *        arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag
 *        arg CAN_FLAG_FF1: FIFO 1 Full Flag
 *        arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag
 *        arg CAN_FLAG_WKU: Wake up Flag
 *        arg CAN_FLAG_SLAK: Sleep acknowledge Flag
 *        arg CAN_FLAG_LEC: Last error code Flag
 * retval None
 */
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG) {
    uint32_t flagtmp=0;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_CLEAR_FLAG(CAN_FLAG));
    if (CAN_FLAG == CAN_FLAG_LEC) {
        CANx->ESR = (uint32_t) RESET; /* Clear selected CAN flags */
    } else {
        flagtmp = CAN_FLAG & 0x000FFFFF;
        if ((CAN_FLAG & CAN_FLAGS_RF0R)!=(uint32_t) RESET) {
            CANx->RF0R = (uint32_t) (flagtmp); /* Receive Flags */
        } else if ((CAN_FLAG & CAN_FLAGS_RF1R)!=(uint32_t )RESET) {
            CANx->RF1R = (uint32_t) (flagtmp); /* Receive Flags */
        } else if ((CAN_FLAG & CAN_FLAGS_TSR)!=(uint32_t) RESET) {
            CANx->TSR = (uint32_t) (flagtmp); /* Transmit Flags */
        } else {
            CANx->MSR = (uint32_t) (flagtmp); /* Operating mode Flags */
        }
    }
}

/**
 * Checks whether specified CANx interrupt has occurred or not.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param CAN_IT: specifies CAN interrupt source to check.
 *    This parameter can be one of following values:
 *        arg CAN_IT_TME: Transmit mailbox empty Interrupt
 *        arg CAN_IT_FMP0: FIFO 0 message pending Interrupt
 *        arg CAN_IT_FF0: FIFO 0 full Interrupt
 *        arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
 *        arg CAN_IT_FMP1: FIFO 1 message pending Interrupt
 *        arg CAN_IT_FF1: FIFO 1 full Interrupt
 *        arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
 *        arg CAN_IT_WKU: Wake-up Interrupt
 *        arg CAN_IT_SLK: Sleep acknowledge Interrupt
 *        arg CAN_IT_EWG: Error warning Interrupt
 *        arg CAN_IT_EPV: Error passive Interrupt
 *        arg CAN_IT_BOF: Bus-off Interrupt
 *        arg CAN_IT_LEC: Last error code Interrupt
 *        arg CAN_IT_ERR: Error Interrupt
 * retval The current state of CAN_IT (SET or RESET).
 */
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT) {
    ITStatus itstatus = RESET;

    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IT(CAN_IT));
    /* check interrupt enable bit */
    if ((CANx->IER & CAN_IT) != RESET) {
        /* in case Interrupt is enabled, */
        switch (CAN_IT) {
            case CAN_IT_TME:
                /* Check CAN_TSR_RQCPx bits */
                itstatus = CheckITStatus(
                    CANx->TSR, CAN_TSR_RQCP0|CAN_TSR_RQCP1|CAN_TSR_RQCP2
                );
                break;
            case CAN_IT_FMP0:
                /* Check CAN_RF0R_FMP0 bit */
                itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FMP0);
                break;
            case CAN_IT_FF0:
                /* Check CAN_RF0R_FULL0 bit */
                itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FULL0);
                break;
            case CAN_IT_FOV0:
                /* Check CAN_RF0R_FOVR0 bit */
                itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FOVR0);
                break;
            case CAN_IT_FMP1:
                /* Check CAN_RF1R_FMP1 bit */
                itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FMP1);
                break;
            case CAN_IT_FF1:
                /* Check CAN_RF1R_FULL1 bit */
                itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FULL1);
                break;
            case CAN_IT_FOV1:
                /* Check CAN_RF1R_FOVR1 bit */
                itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FOVR1);
                break;
            case CAN_IT_WKU:
                /* Check CAN_MSR_WKUI bit */
                itstatus = CheckITStatus(CANx->MSR, CAN_MSR_WKUI);
                break;
            case CAN_IT_SLK:
                /* Check CAN_MSR_SLAKI bit */
                itstatus = CheckITStatus(CANx->MSR, CAN_MSR_SLAKI);
                break;
            case CAN_IT_EWG:
                /* Check CAN_ESR_EWGF bit */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EWGF);
                break;
            case CAN_IT_EPV:
                /* Check CAN_ESR_EPVF bit */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EPVF);
                break;
            case CAN_IT_BOF:
                /* Check CAN_ESR_BOFF bit */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_BOFF);
                break;
            case CAN_IT_LEC:
                /* Check CAN_ESR_LEC bit */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_LEC);
                break;
            case CAN_IT_ERR:
                /* Check CAN_MSR_ERRI bit */ 
                itstatus = CheckITStatus(CANx->MSR, CAN_MSR_ERRI);
                break;
            default:
                /* in case of error, return RESET */
                itstatus = RESET;
                break;
        }
    } else {
        /* in case Interrupt is not enabled, return RESET */
        itstatus  = RESET;
    }
    return itstatus; /* Return CAN_IT status */
}

/**
 * Clears CANx's interrupt pending bits.
 * param CANx: where x can be 1 or 2 to to select CAN peripheral.
 * param CAN_IT: specifies interrupt pending bit to clear.
 *    This parameter can be one of following values:
 *        arg CAN_IT_TME: Transmit mailbox empty Interrupt
 *        arg CAN_IT_FF0: FIFO 0 full Interrupt
 *        arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
 *        arg CAN_IT_FF1: FIFO 1 full Interrupt
 *        arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
 *        arg CAN_IT_WKU: Wake-up Interrupt
 *        arg CAN_IT_SLK: Sleep acknowledge Interrupt
 *        arg CAN_IT_EWG: Error warning Interrupt
 *        arg CAN_IT_EPV: Error passive Interrupt
 *        arg CAN_IT_BOF: Bus-off Interrupt
 *        arg CAN_IT_LEC: Last error code Interrupt
 *        arg CAN_IT_ERR: Error Interrupt
 * retval None
 */
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_CLEAR_IT(CAN_IT));
    switch (CAN_IT) {
        case CAN_IT_TME:
            /* Clear CAN_TSR_RQCPx (rc_w1)*/
            CANx->TSR = CAN_TSR_RQCP0 | CAN_TSR_RQCP1 | CAN_TSR_RQCP2;
            break;
        case CAN_IT_FF0:
            CANx->RF0R = CAN_RF0R_FULL0; /* Clear CAN_RF0R_FULL0 (rc_w1)*/
            break;
        case CAN_IT_FOV0:
            CANx->RF0R = CAN_RF0R_FOVR0; /* Clear CAN_RF0R_FOVR0 (rc_w1)*/
            break;
        case CAN_IT_FF1:
            CANx->RF1R = CAN_RF1R_FULL1; /* Clear CAN_RF1R_FULL1 (rc_w1)*/
            break;
        case CAN_IT_FOV1:
            CANx->RF1R = CAN_RF1R_FOVR1; /* Clear CAN_RF1R_FOVR1 (rc_w1)*/
            break;
        case CAN_IT_WKU:
            CANx->MSR = CAN_MSR_WKUI; /* Clear CAN_MSR_WKUI (rc_w1)*/
            break;
        case CAN_IT_SLK:
            CANx->MSR = CAN_MSR_SLAKI; /* Clear CAN_MSR_SLAKI (rc_w1)*/
            break;
        case CAN_IT_EWG:
            CANx->MSR = CAN_MSR_ERRI; /* Clear CAN_MSR_ERRI (rc_w1) */
            /**
             * corresponding Flag is cleared by hardware
             * depending on CAN Bus status
             */
            break;
        case CAN_IT_EPV:
            CANx->MSR = CAN_MSR_ERRI; /* Clear CAN_MSR_ERRI (rc_w1) */
            /**
             * corresponding Flag is cleared by hardware
             * depending on CAN Bus status
             */
            break;
        case CAN_IT_BOF:
             CANx->MSR = CAN_MSR_ERRI; /* Clear CAN_MSR_ERRI (rc_w1) */
             /**
              * corresponding Flag is cleared by hardware
              * depending on CAN Bus status
              */
             break;
        case CAN_IT_LEC:
            CANx->ESR = RESET; /*  Clear LEC bits */
            CANx->MSR = CAN_MSR_ERRI; /* Clear CAN_MSR_ERRI (rc_w1) */
            break;
        case CAN_IT_ERR:
             CANx->ESR = RESET; /*Clear LEC bits */
             CANx->MSR = CAN_MSR_ERRI; /* Clear CAN_MSR_ERRI (rc_w1) */
             /**
              * BOFF, EPVF and EWGF Flags are cleared by hardware
              * depending on CAN Bus status
              */
             break;
        default:
             break;
   }
}

/**
 * Checks whether CAN interrupt has occurred or not.
 * param CAN_Reg: specifies CAN interrupt register to check.
 * param It_Bit: specifies interrupt source bit to check.
 * retval The new state of CAN Interrupt (SET or RESET).
 */
static ITStatus CheckITStatus(uint32_t CAN_Reg, uint32_t It_Bit) {
    ITStatus pendingbitstatus = RESET;
    if ((CAN_Reg & It_Bit) != (uint32_t) RESET) {
        pendingbitstatus = SET;
    } else {
        pendingbitstatus = RESET;
    }
    return pendingbitstatus;
}

