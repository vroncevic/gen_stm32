/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_can.h
 * 
 * This file contains all the functions prototypes for CAN firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_can is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_can is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_CAN_H
#define __STM32F4xx_CAN_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define IS_CAN_ALL_PERIPH(PERIPH) ( \
    ((PERIPH) == CAN1) || ((PERIPH) == CAN2) \
)

typedef struct {
    uint16_t CAN_Prescaler; /* Specifies length of a time quantum.
                               It ranges from 1 to 1024. */
    uint8_t CAN_Mode; /* Specifies CAN operating mode. Parameter can be a
                         value of CAN_operating_mode */
    uint8_t CAN_SJW; /* Specifies maximum number of time quanta CAN
                        hardware is allowed to lengthen or shorten a
                        bit to perform resynchronization.
                        Parameter can be a value of
                        CAN_synchronisation_jump_width */
    uint8_t CAN_BS1; /* Specifies number of time quanta in Bit Segment 1.
                        Parameter can be a value of
                        CAN_time_quantum_in_bit_segment_1 */
    uint8_t CAN_BS2; /* Specifies number of time quanta in Bit Segment 2.
                        Parameter can be a value of
                        CAN_time_quantum_in_bit_segment_2 */
    FunctionalState CAN_TTCM; /* Enable or disable time triggered
                                 communication mode. Parameter can be set
                                 either to ENABLE or DISABLE. */
    FunctionalState CAN_ABOM; /* Enable or disable automatic bus-off
                                 management. Parameter can be set either to
                                 ENABLE or DISABLE. */
    FunctionalState CAN_AWUM; /* Enable or disable automatic wake-up mode.
                                 Parameter can be set either to ENABLE or
                                 DISABLE. */
    FunctionalState CAN_NART; /* Enable or disable non-automatic
                                 retransmission mode. Parameter can be set
                                 either to ENABLE or DISABLE. */
    FunctionalState CAN_RFLM; /* Enable or disable Receive FIFO Locked mode.
                                 Parameter can be set either to ENABLE or
                                 DISABLE. */
    FunctionalState CAN_TXFP; /* Enable or disable transmit FIFO priority.
                                 Parameter can be set either to ENABLE or
                                 DISABLE. */
} CAN_InitTypeDef;

typedef struct {
    uint16_t CAN_FilterIdHigh; /* Specifies filter identification number
                                  (MSBs for a 32-bit configuration, first one
                                  for a 16-bit configuration). Parameter can
                                  be a value between 0x0000 and 0xFFFF */
    uint16_t CAN_FilterIdLow; /* Specifies filter identification number
                                 (LSBs for a 32-bit configuration, second one
                                 for a 16-bit configuration). Parameter can be
                                 a value between 0x0000 and 0xFFFF */
    uint16_t CAN_FilterMaskIdHigh; /* Specifies filter mask number or
                                      identification number, according to mode
                                      (MSBs for a 32-bit configuration,
                                      first one for a 16-bit configuration).
                                      Parameter can be a value between 0x0000
                                      and 0xFFFF */
    uint16_t CAN_FilterMaskIdLow; /* Specifies filter mask number or
                                     identification number, according to mode
                                     (LSBs for a 32-bit configuration,
                                     second one for a 16-bit configuration).
                                     Parameter can be a value between 0x0000
                                     and 0xFFFF */
    uint16_t CAN_FilterFIFOAssignment; /* Specifies FIFO (0 or 1) which will
                                          be assigned to filter. Parameter can
                                          be a value of CAN_filter_FIFO */
    uint8_t CAN_FilterNumber; /* Specifies filter which will be initialized.
                                 It ranges from 0 to 13. */
    uint8_t CAN_FilterMode; /* Specifies filter mode to be initialized.
                               Parameter can be a value of CAN_filter_mode */
    uint8_t CAN_FilterScale; /* Specifies filter scale. Parameter can be a
                                value of CAN_filter_scale */
    FunctionalState CAN_FilterActivation; /* Enable or disable filter.
                                             Parameter can be set either to
                                             ENABLE or DISABLE. */
} CAN_FilterInitTypeDef;

typedef struct {
    uint32_t StdId;  /* Specifies standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */
    uint32_t ExtId;  /* Specifies extended identifier.
                        Parameter can be a value between 0 to 0x1FFFFFFF. */
    uint8_t IDE;     /* Specifies type of identifier for message that 
                        will be transmitted. This parameter can be a value 
                        of CAN_identifier_type */
    uint8_t RTR;     /* Specifies type of frame for message that will 
                        be transmitted. This parameter can be a value of 
                        CAN_remote_transmission_request */
    uint8_t DLC;     /* Specifies length of frame that will be 
                        transmitted. This parameter can be a value between 
                        0 to 8 */
    uint8_t Data[8]; /* Contains data to be transmitted. It ranges from 0 
                        to 0xFF. */
} CanTxMsg;

typedef struct {
    uint32_t StdId; /* Specifies standard identifier.
                       Parameter can be a value between 0 to 0x7FF. */
    uint32_t ExtId; /* Specifies extended identifier.
                       Parameter can be a value between 0 to 0x1FFFFFFF. */
    uint8_t IDE; /* Specifies type of identifier for message that
                    will be received. This parameter can be a value of
                    CAN_identifier_type */
    uint8_t RTR; /* Specifies type of frame for received message.
                    Parameter can be a value of 
                    CAN_remote_transmission_request */
    uint8_t DLC; /* Specifies length of frame that will be received.
                    Parameter can be a value between 0 to 8 */
    uint8_t Data[8]; /* Contains data to be received. It is ranges from 0 to
                        0xFF. */
    uint8_t FMI; /* Specifies index of filter message stored in
                    mailbox passes through. This parameter can be a
                    value between 0 to 0xFF */
} CanRxMsg;

#define CAN_InitStatus_Failed ((uint8_t) 0x00) /* CAN initialization failed */
#define CAN_InitStatus_Success ((uint8_t) 0x01) /* CAN initialization OK */
#define CANINITFAILED CAN_InitStatus_Failed
#define CANINITOK CAN_InitStatus_Success
#define CAN_Mode_Normal ((uint8_t) 0x00) /* normal mode */
#define CAN_Mode_LoopBack ((uint8_t) 0x01) /* loopback mode */
#define CAN_Mode_Silent ((uint8_t) 0x02) /* silent mode */
#define CAN_OperatingMode_Initialization ((uint8_t) 0x00) /* Init mode */
#define CAN_OperatingMode_Normal ((uint8_t) 0x01) /* Normal mode */
#define CAN_OperatingMode_Sleep ((uint8_t) 0x02) /* sleep mode */

/* loopback combined with silent mode */
#define CAN_Mode_Silent_LoopBack ((uint8_t) 0x03)

/* CAN entering specific mode failed */
#define CAN_ModeStatus_Failed ((uint8_t) 0x00)

/* CAN entering specific mode Succeed */
#define CAN_ModeStatus_Success ((uint8_t) !CAN_ModeStatus_Failed)

#define CAN_SJW_1tq ((uint8_t) 0x00) /* 1 time quantum */
#define CAN_SJW_2tq ((uint8_t) 0x01) /* 2 time quantum */
#define CAN_SJW_3tq ((uint8_t) 0x02) /* 3 time quantum */
#define CAN_SJW_4tq ((uint8_t) 0x03) /* 4 time quantum */
#define CAN_BS1_1tq ((uint8_t) 0x00) /* 1 time quantum */
#define CAN_BS1_2tq ((uint8_t) 0x01) /* 2 time quantum */
#define CAN_BS1_3tq ((uint8_t) 0x02) /* 3 time quantum */
#define CAN_BS1_4tq ((uint8_t) 0x03) /* 4 time quantum */
#define CAN_BS1_5tq ((uint8_t) 0x04) /* 5 time quantum */
#define CAN_BS1_6tq ((uint8_t) 0x05) /* 6 time quantum */
#define CAN_BS1_7tq ((uint8_t) 0x06) /* 7 time quantum */
#define CAN_BS1_8tq ((uint8_t) 0x07) /* 8 time quantum */
#define CAN_BS1_9tq ((uint8_t) 0x08) /* 9 time quantum */
#define CAN_BS1_10tq ((uint8_t) 0x09) /* 10 time quantum */
#define CAN_BS1_11tq ((uint8_t) 0x0A) /* 11 time quantum */
#define CAN_BS1_12tq ((uint8_t) 0x0B) /* 12 time quantum */
#define CAN_BS1_13tq ((uint8_t) 0x0C) /* 13 time quantum */
#define CAN_BS1_14tq ((uint8_t) 0x0D) /* 14 time quantum */
#define CAN_BS1_15tq ((uint8_t) 0x0E) /* 15 time quantum */
#define CAN_BS1_16tq ((uint8_t) 0x0F) /* 16 time quantum */
#define CAN_BS2_1tq ((uint8_t) 0x00) /* 1 time quantum */
#define CAN_BS2_2tq ((uint8_t) 0x01) /* 2 time quantum */
#define CAN_BS2_3tq ((uint8_t) 0x02) /* 3 time quantum */
#define CAN_BS2_4tq ((uint8_t) 0x03) /* 4 time quantum */
#define CAN_BS2_5tq ((uint8_t) 0x04) /* 5 time quantum */
#define CAN_BS2_6tq ((uint8_t) 0x05) /* 6 time quantum */
#define CAN_BS2_7tq ((uint8_t) 0x06) /* 7 time quantum */
#define CAN_BS2_8tq ((uint8_t) 0x07) /* 8 time quantum */
#define CAN_FilterMode_IdMask ((uint8_t) 0x00) /* identifier/mask mode */
#define CAN_FilterMode_IdList ((uint8_t) 0x01) /* identifier list mode */
#define CAN_FilterScale_16bit ((uint8_t) 0x00) /* Two 16-bit filters */
#define CAN_FilterScale_32bit ((uint8_t) 0x01) /* One 32-bit filter */

/* Filter FIFO 0 assignment for filter x */
#define CAN_Filter_FIFO0 ((uint8_t) 0x00)

/* Filter FIFO 1 assignment for filter x */
#define CAN_Filter_FIFO1 ((uint8_t) 0x01)

#define CAN_FilterFIFO0 CAN_Filter_FIFO0
#define CAN_FilterFIFO1 CAN_Filter_FIFO1
#define CAN_Id_Standard ((uint32_t) 0x00000000) /* Standard Id */
#define CAN_Id_Extended ((uint32_t) 0x00000004) /* Extended Id */
#define CAN_ID_STD CAN_Id_Standard
#define CAN_ID_EXT CAN_Id_Extended
#define CAN_RTR_Data ((uint32_t) 0x00000000) /* Data frame */
#define CAN_RTR_Remote ((uint32_t) 0x00000002) /* Remote frame */
#define CAN_RTR_DATA CAN_RTR_Data
#define CAN_RTR_REMOTE CAN_RTR_Remote
#define CAN_TxStatus_Failed ((uint8_t) 0x00)/* CAN transmission failed */
#define CAN_TxStatus_Ok ((uint8_t) 0x01) /* CAN transmission succeeded */
#define CAN_TxStatus_Pending ((uint8_t) 0x02) /* CAN transmission pending */

/* CAN cell did not provide an empty mailbox */
#define CAN_TxStatus_NoMailBox ((uint8_t) 0x04)

#define CANTXFAILED CAN_TxStatus_Failed
#define CANTXOK CAN_TxStatus_Ok
#define CANTXPENDING CAN_TxStatus_Pending
#define CAN_NO_MB CAN_TxStatus_NoMailBox
#define CAN_FIFO0 ((uint8_t) 0x00) /* CAN FIFO 0 used to receive */
#define CAN_FIFO1 ((uint8_t) 0x01) /* CAN FIFO 1 used to receive */
#define CAN_Sleep_Failed ((uint8_t) 0x00) /* CAN did not enter sleep mode */
#define CAN_Sleep_Ok ((uint8_t) 0x01) /* CAN entered sleep mode */
#define CANSLEEPFAILED CAN_Sleep_Failed
#define CANSLEEPOK CAN_Sleep_Ok
#define CAN_WakeUp_Failed ((uint8_t) 0x00) /* CAN did not leave sleep mode */
#define CAN_WakeUp_Ok ((uint8_t) 0x01) /* CAN leaved sleep mode */
#define CANWAKEUPFAILED CAN_WakeUp_Failed
#define CANWAKEUPOK CAN_WakeUp_Ok
#define CAN_ErrorCode_NoErr ((uint8_t) 0x00) /* No Error */
#define	CAN_ErrorCode_StuffErr ((uint8_t) 0x10) /* Stuff Error */
#define	CAN_ErrorCode_FormErr ((uint8_t) 0x20) /* Form Error */
#define	CAN_ErrorCode_ACKErr ((uint8_t) 0x30) /* Acknowledgment Error */
#define	CAN_ErrorCode_BitRecessiveErr ((uint8_t) 0x40) /* Bit Rec Error */
#define	CAN_ErrorCode_BitDominantErr ((uint8_t) 0x50) /* Bit Dom Error */
#define	CAN_ErrorCode_CRCErr ((uint8_t) 0x60) /* CRC Error  */
#define	CAN_ErrorCode_SoftwareSetErr ((uint8_t) 0x70) /* Software Set Error */
#define CAN_FLAG_RQCP0 ((uint32_t) 0x38000001) /* Request MailBox0 Flag */
#define CAN_FLAG_RQCP1 ((uint32_t) 0x38000100) /* Request MailBox1 Flag */
#define CAN_FLAG_RQCP2 ((uint32_t) 0x38010000) /* Request MailBox2 Flag */
#define CAN_FLAG_FMP0 ((uint32_t) 0x12000003) /* FIFO 0 Message Pending Flag */
#define CAN_FLAG_FF0 ((uint32_t) 0x32000008) /* FIFO 0 Full Flag */
#define CAN_FLAG_FOV0 ((uint32_t) 0x32000010) /* FIFO 0 Overrun Flag */
#define CAN_FLAG_FMP1 ((uint32_t) 0x14000003) /* FIFO 1 Message Pending Flag */
#define CAN_FLAG_FF1 ((uint32_t) 0x34000008) /* FIFO 1 Full Flag */
#define CAN_FLAG_FOV1 ((uint32_t) 0x34000010) /* FIFO 1 Overrun Flag */
#define CAN_FLAG_WKU ((uint32_t) 0x31000008) /* Wake up Flag */

/**
 * When SLAK interrupt is disabled (SLKIE=0), no polling on SLAKI is possible.
 * In this case SLAK bit can be polled.
 */
#define CAN_FLAG_SLAK ((uint32_t) 0x31000012) /* Sleep acknowledge Flag */
#define CAN_FLAG_EWG ((uint32_t) 0x10F00001) /* Error Warning Flag */
#define CAN_FLAG_EPV ((uint32_t) 0x10F00002) /* Error Passive Flag */
#define CAN_FLAG_BOF ((uint32_t) 0x10F00004) /* Bus-Off Flag */
#define CAN_FLAG_LEC ((uint32_t) 0x30F00070) /* Last error code Flag */
#define CAN_IT_TME ((uint32_t) 0x00000001) /* Transmit mailbox empty interr */

/* Receive interrs */
#define CAN_IT_FMP0 ((uint32_t) 0x00000002) /* FIFO 0 message pending interr */
#define CAN_IT_FF0 ((uint32_t) 0x00000004) /* FIFO 0 full interr */
#define CAN_IT_FOV0 ((uint32_t) 0x00000008) /* FIFO 0 overrun interr */
#define CAN_IT_FMP1 ((uint32_t) 0x00000010) /* FIFO 1 message pending interr */
#define CAN_IT_FF1 ((uint32_t) 0x00000020) /* FIFO 1 full interr */
#define CAN_IT_FOV1 ((uint32_t) 0x00000040) /* FIFO 1 overrun interr */

/* Operating Mode interrs */
#define CAN_IT_WKU ((uint32_t) 0x00010000) /* Wake-up interr */
#define CAN_IT_SLK ((uint32_t) 0x00020000) /* Sleep acknowledge interr */

/* Error interrs */
#define CAN_IT_EWG ((uint32_t) 0x00000100) /* Error warning interr */
#define CAN_IT_EPV ((uint32_t) 0x00000200) /* Error passive interr */
#define CAN_IT_BOF ((uint32_t) 0x00000400) /* Bus-off interr */
#define CAN_IT_LEC ((uint32_t) 0x00000800) /* Last error code interr */
#define CAN_IT_ERR ((uint32_t) 0x00008000) /* Error interr */

/* Flags named as interrs: kept only for FW compatibility */
#define CAN_IT_RQCP0 CAN_IT_TME
#define CAN_IT_RQCP1 CAN_IT_TME
#define CAN_IT_RQCP2 CAN_IT_TME

#define IS_CAN_MODE(MODE) ( \
    ((MODE) == CAN_Mode_Normal) || \
    ((MODE) == CAN_Mode_LoopBack)|| \
    ((MODE) == CAN_Mode_Silent) || \
    ((MODE) == CAN_Mode_Silent_LoopBack) \
)

#define IS_CAN_OPERATING_MODE(MODE) ( \
    ((MODE) == CAN_OperatingMode_Initialization) ||\
    ((MODE) == CAN_OperatingMode_Normal) || \
    ((MODE) == CAN_OperatingMode_Sleep) \
)

#define IS_CAN_SJW(SJW) ( \
    ((SJW) == CAN_SJW_1tq) || ((SJW) == CAN_SJW_2tq) || \
    ((SJW) == CAN_SJW_3tq) || ((SJW) == CAN_SJW_4tq) \
)

#define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16tq)
#define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8tq)

#define IS_CAN_PRESCALER(PRESCALER) ( \
    ((PRESCALER) >= 1) && ((PRESCALER) <= 1024) \
)

#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 27)

#define IS_CAN_FILTER_MODE(MODE) ( \
    ((MODE) == CAN_FilterMode_IdMask) || ((MODE) == CAN_FilterMode_IdList) \
)

#define IS_CAN_FILTER_SCALE(SCALE) ( \
    ((SCALE) == CAN_FilterScale_16bit) || ((SCALE) == CAN_FilterScale_32bit) \
)

#define IS_CAN_FILTER_FIFO(FIFO) ( \
    ((FIFO) == CAN_FilterFIFO0) || ((FIFO) == CAN_FilterFIFO1) \
)

#define IS_CAN_BANKNUMBER(BANKNUMBER) ( \
    ((BANKNUMBER) >= 1) && ((BANKNUMBER) <= 27) \
)

#define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ( \
    (TRANSMITMAILBOX) <= ((uint8_t)0x02) \
)

#define IS_CAN_STDID(STDID) ((STDID) <= ((uint32_t)0x7FF))
#define IS_CAN_EXTID(EXTID) ((EXTID) <= ((uint32_t)0x1FFFFFFF))
#define IS_CAN_DLC(DLC) ((DLC) <= ((uint8_t)0x08))

#define IS_CAN_IDTYPE(IDTYPE) ( \
    ((IDTYPE) == CAN_Id_Standard) || ((IDTYPE) == CAN_Id_Extended) \
)

#define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_Data) || ((RTR) == CAN_RTR_Remote))
#define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))

#define IS_CAN_GET_FLAG(FLAG) ( \
    ((FLAG) == CAN_FLAG_LEC) || ((FLAG) == CAN_FLAG_BOF) || \
    ((FLAG) == CAN_FLAG_EPV) || ((FLAG) == CAN_FLAG_EWG) || \
    ((FLAG) == CAN_FLAG_WKU) || ((FLAG) == CAN_FLAG_FOV0) || \
    ((FLAG) == CAN_FLAG_FF0) || ((FLAG) == CAN_FLAG_FMP0) || \
    ((FLAG) == CAN_FLAG_FOV1) || ((FLAG) == CAN_FLAG_FF1) || \
    ((FLAG) == CAN_FLAG_FMP1) || ((FLAG) == CAN_FLAG_RQCP2) || \
    ((FLAG) == CAN_FLAG_RQCP1)|| ((FLAG) == CAN_FLAG_RQCP0) || \
    ((FLAG) == CAN_FLAG_SLAK ) \
)

#define IS_CAN_CLEAR_FLAG(FLAG) ( \
    ((FLAG) == CAN_FLAG_LEC) || ((FLAG) == CAN_FLAG_RQCP2) || \
    ((FLAG) == CAN_FLAG_RQCP1) || ((FLAG) == CAN_FLAG_RQCP0) || \
    ((FLAG) == CAN_FLAG_FF0) || ((FLAG) == CAN_FLAG_FOV0) ||\
    ((FLAG) == CAN_FLAG_FF1) || ((FLAG) == CAN_FLAG_FOV1) || \
    ((FLAG) == CAN_FLAG_WKU) || ((FLAG) == CAN_FLAG_SLAK) \
)

#define IS_CAN_IT(IT) ( \
    ((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FMP0) || \
    ((IT) == CAN_IT_FF0) || ((IT) == CAN_IT_FOV0) || \
    ((IT) == CAN_IT_FMP1) || ((IT) == CAN_IT_FF1) || \
    ((IT) == CAN_IT_FOV1) || ((IT) == CAN_IT_EWG) || \
    ((IT) == CAN_IT_EPV) || ((IT) == CAN_IT_BOF) || \
    ((IT) == CAN_IT_LEC) || ((IT) == CAN_IT_ERR) || \
    ((IT) == CAN_IT_WKU) || ((IT) == CAN_IT_SLK) \
)

#define IS_CAN_CLEAR_IT(IT) ( \
    ((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FF0) || \
    ((IT) == CAN_IT_FOV0) || ((IT) == CAN_IT_FF1) || \
    ((IT) == CAN_IT_FOV1) || ((IT) == CAN_IT_EWG) || \
    ((IT) == CAN_IT_EPV) || ((IT) == CAN_IT_BOF) || \
    ((IT) == CAN_IT_LEC) || ((IT) == CAN_IT_ERR) || \
    ((IT) == CAN_IT_WKU) || ((IT) == CAN_IT_SLK) \
)

void CAN_DeInit(CAN_TypeDef* CANx);
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_SlaveStartBank(uint8_t CAN_BankNumber); 
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState);
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState);
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage);
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode);
uint8_t CAN_Sleep(CAN_TypeDef* CANx);
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx);
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx);
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx);

void CAN_ITConfig(
    CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState
);

FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT);

#ifdef __cplusplus
    }
#endif

#endif

