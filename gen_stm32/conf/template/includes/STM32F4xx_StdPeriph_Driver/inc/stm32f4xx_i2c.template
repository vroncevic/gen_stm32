/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_i2c.h
 * 
 * This file contains all functions prototypes for I2C firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_i2c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_i2c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_I2C_H
#define __STM32F4xx_I2C_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

typedef struct {
    uint32_t I2C_ClockSpeed; /* Specifies clock frequency.
                                Parameter must be set to a value
                                lower than 400kHz */
    uint16_t I2C_Mode; /* Specifies I2C mode. Parameter can
                          be a value of I2C_mode */
    uint16_t I2C_DutyCycle; /* Specifies I2C fast mode duty cycle.
                               Parameter can be a value of
                               I2C_duty_cycle_in_fast_mode */
    uint16_t I2C_OwnAddress1; /* Specifies first device own address.
                                 Parameter can be a 7-bit or 10-bit
                                 address. */
    uint16_t I2C_Ack; /* Enables or disables acknowledgement.
                         Parameter can be a value of I2C_acknowledgement */
    uint16_t I2C_AcknowledgedAddress; /* Specifies if 7-bit or 10-bit address
                                         is acknowledged. Parameter can be a
                                         value of I2C_acknowledged_address */
} I2C_InitTypeDef;

#define IS_I2C_ALL_PERIPH(PERIPH) ( \
    ((PERIPH) == I2C1) || ((PERIPH) == I2C2) || ((PERIPH) == I2C3) \
)

#define I2C_Mode_I2C ((uint16_t) 0x0000)
#define I2C_Mode_SMBusDevice ((uint16_t) 0x0002)
#define I2C_Mode_SMBusHost ((uint16_t) 0x000A)
/* I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DutyCycle_16_9 ((uint16_t) 0x4000)
#define I2C_DutyCycle_2 ((uint16_t) 0xBFFF) /* I2C fast mode Tlow/Thigh = 2 */
#define I2C_Ack_Enable ((uint16_t) 0x0400)
#define I2C_Ack_Disable ((uint16_t) 0x0000)
#define I2C_Direction_Transmitter ((uint8_t) 0x00)
#define I2C_Direction_Receiver ((uint8_t) 0x01)
#define I2C_AcknowledgedAddress_7bit ((uint16_t) 0x4000)
#define I2C_AcknowledgedAddress_10bit ((uint16_t) 0xC000)
#define I2C_Register_CR1 ((uint8_t) 0x00)
#define I2C_Register_CR2 ((uint8_t) 0x04)
#define I2C_Register_OAR1 ((uint8_t) 0x08)
#define I2C_Register_OAR2 ((uint8_t) 0x0C)
#define I2C_Register_DR ((uint8_t) 0x10)
#define I2C_Register_SR1 ((uint8_t) 0x14)
#define I2C_Register_SR2 ((uint8_t) 0x18)
#define I2C_Register_CCR ((uint8_t) 0x1C)
#define I2C_Register_TRISE ((uint8_t) 0x20)
#define I2C_NACKPosition_Next ((uint16_t) 0x0800)
#define I2C_NACKPosition_Current ((uint16_t) 0xF7FF)
#define I2C_SMBusAlert_Low ((uint16_t) 0x2000)
#define I2C_SMBusAlert_High ((uint16_t) 0xDFFF)
#define I2C_PECPosition_Next ((uint16_t) 0x0800)
#define I2C_PECPosition_Current ((uint16_t) 0xF7FF)
#define I2C_IT_BUF ((uint16_t) 0x0400)
#define I2C_IT_EVT ((uint16_t) 0x0200)
#define I2C_IT_ERR ((uint16_t) 0x0100)
#define I2C_IT_SMBALERT ((uint32_t) 0x01008000)
#define I2C_IT_TIMEOUT ((uint32_t) 0x01004000)
#define I2C_IT_PECERR ((uint32_t) 0x01001000)
#define I2C_IT_OVR ((uint32_t) 0x01000800)
#define I2C_IT_AF ((uint32_t) 0x01000400)
#define I2C_IT_ARLO ((uint32_t) 0x01000200)
#define I2C_IT_BERR ((uint32_t) 0x01000100)
#define I2C_IT_TXE ((uint32_t) 0x06000080)
#define I2C_IT_RXNE ((uint32_t) 0x06000040)
#define I2C_IT_STOPF ((uint32_t) 0x02000010)
#define I2C_IT_ADD10 ((uint32_t) 0x02000008)
#define I2C_IT_BTF ((uint32_t) 0x02000004)
#define I2C_IT_ADDR ((uint32_t) 0x02000002)
#define I2C_IT_SB ((uint32_t) 0x02000001)
#define I2C_FLAG_DUALF ((uint32_t) 0x00800000)
#define I2C_FLAG_SMBHOST ((uint32_t) 0x00400000)
#define I2C_FLAG_SMBDEFAULT ((uint32_t) 0x00200000)
#define I2C_FLAG_GENCALL ((uint32_t) 0x00100000)
#define I2C_FLAG_TRA ((uint32_t) 0x00040000)
#define I2C_FLAG_BUSY ((uint32_t) 0x00020000)
#define I2C_FLAG_MSL ((uint32_t) 0x00010000)
#define I2C_FLAG_SMBALERT ((uint32_t) 0x10008000)
#define I2C_FLAG_TIMEOUT ((uint32_t) 0x10004000)
#define I2C_FLAG_PECERR ((uint32_t) 0x10001000)
#define I2C_FLAG_OVR ((uint32_t) 0x10000800)
#define I2C_FLAG_AF ((uint32_t) 0x10000400)
#define I2C_FLAG_ARLO ((uint32_t) 0x10000200)
#define I2C_FLAG_BERR ((uint32_t) 0x10000100)
#define I2C_FLAG_TXE ((uint32_t) 0x10000080)
#define I2C_FLAG_RXNE ((uint32_t) 0x10000040)
#define I2C_FLAG_STOPF ((uint32_t) 0x10000010)
#define I2C_FLAG_ADD10 ((uint32_t) 0x10000008)
#define I2C_FLAG_BTF ((uint32_t) 0x10000004)
#define I2C_FLAG_ADDR ((uint32_t) 0x10000002)
#define I2C_FLAG_SB ((uint32_t) 0x10000001)

/* BUSY, MSL and SB flag */
#define I2C_EVENT_MASTER_MODE_SELECT ((uint32_t) 0x00030001)

/* BUSY, MSL, ADDR, TXE and TRA flags */
#define I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ((uint32_t) 0x00070082)

/* BUSY, MSL and ADDR flags */
#define I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ((uint32_t) 0x00030002)

/* BUSY, MSL and ADD10 flags */
#define I2C_EVENT_MASTER_MODE_ADDRESS10 ((uint32_t) 0x00030008)

#define IS_I2C_MODE(MODE) ( \
    ((MODE) == I2C_Mode_I2C) || ((MODE) == I2C_Mode_SMBusDevice) || \
    ((MODE) == I2C_Mode_SMBusHost) \
)

#define IS_I2C_DUTY_CYCLE(CYCLE) ( \
    ((CYCLE) == I2C_DutyCycle_16_9) || ((CYCLE) == I2C_DutyCycle_2) \
)

#define IS_I2C_ACK_STATE(STATE) ( \
    ((STATE) == I2C_Ack_Enable) || ((STATE) == I2C_Ack_Disable) \
)

#define IS_I2C_DIRECTION(DIRECTION) ( \
    ((DIRECTION) == I2C_Direction_Transmitter) || \
    ((DIRECTION) == I2C_Direction_Receiver) \
)

#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) ( \
    ((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
    ((ADDRESS) == I2C_AcknowledgedAddress_10bit) \
)

#define IS_I2C_REGISTER(REGISTER) ( \
    ((REGISTER) == I2C_Register_CR1) || ((REGISTER) == I2C_Register_CR2) || \
    ((REGISTER) == I2C_Register_OAR1) || ((REGISTER) == I2C_Register_OAR2) || \
    ((REGISTER) == I2C_Register_DR) || ((REGISTER) == I2C_Register_SR1) || \
    ((REGISTER) == I2C_Register_SR2) || ((REGISTER) == I2C_Register_CCR) || \
    ((REGISTER) == I2C_Register_TRISE) \
)

#define IS_I2C_NACK_POSITION(POSITION) ( \
    ((POSITION) == I2C_NACKPosition_Next) || \
    ((POSITION) == I2C_NACKPosition_Current) \
)

#define IS_I2C_SMBUS_ALERT(ALERT) ( \
    ((ALERT) == I2C_SMBusAlert_Low) || ((ALERT) == I2C_SMBusAlert_High) \
)

#define IS_I2C_PEC_POSITION(POSITION) ( \
    ((POSITION) == I2C_PECPosition_Next) || \
    ((POSITION) == I2C_PECPosition_Current) \
)

#define IS_I2C_CONFIG_IT(IT) ( \
    (((IT) & (uint16_t) 0xF8FF) == 0x00) && ((IT) != 0x00) \
)

#define IS_I2C_CLEAR_IT(IT) ( \
    (((IT) & (uint16_t) 0x20FF) == 0x00) && ((IT) != (uint16_t) 0x00) \
)

#define IS_I2C_GET_IT(IT) ( \
    ((IT) == I2C_IT_SMBALERT) || ((IT) == I2C_IT_TIMEOUT) || \
    ((IT) == I2C_IT_PECERR) || ((IT) == I2C_IT_OVR) || \
    ((IT) == I2C_IT_AF) || ((IT) == I2C_IT_ARLO) || \
    ((IT) == I2C_IT_BERR) || ((IT) == I2C_IT_TXE) || \
    ((IT) == I2C_IT_RXNE) || ((IT) == I2C_IT_STOPF) || \
    ((IT) == I2C_IT_ADD10) || ((IT) == I2C_IT_BTF) || \
    ((IT) == I2C_IT_ADDR) || ((IT) == I2C_IT_SB) \
)

#define IS_I2C_CLEAR_FLAG(FLAG) ( \
    (((FLAG) & (uint16_t) 0x20FF) == 0x00) && ((FLAG) != (uint16_t) 0x00) \
)

#define IS_I2C_GET_FLAG(FLAG) ( \
    ((FLAG) == I2C_FLAG_DUALF) || ((FLAG) == I2C_FLAG_SMBHOST) || \
    ((FLAG) == I2C_FLAG_SMBDEFAULT) || ((FLAG) == I2C_FLAG_GENCALL) || \
    ((FLAG) == I2C_FLAG_TRA) || ((FLAG) == I2C_FLAG_BUSY) || \
    ((FLAG) == I2C_FLAG_MSL) || ((FLAG) == I2C_FLAG_SMBALERT) || \
    ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_PECERR) || \
    ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_AF) || \
    ((FLAG) == I2C_FLAG_ARLO) || ((FLAG) == I2C_FLAG_BERR) || \
    ((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_RXNE) || \
    ((FLAG) == I2C_FLAG_STOPF) || ((FLAG) == I2C_FLAG_ADD10) || \
    ((FLAG) == I2C_FLAG_BTF) || ((FLAG) == I2C_FLAG_ADDR) || \
    ((FLAG) == I2C_FLAG_SB) \
)

/**
 * Address Acknowledge
 * 
 * After checking on EV5 (start condition correctly released on bus),
 * master sends address of slave(s) with which it will communicate 
 * (I2C_Send7bitAddress() function, it also determines direction of
 * communication: Master transmitter or Receiver). Then master has to wait
 * that a slave acknowledges his address. If an acknowledge is sent on bus,
 * one of following events will be set:
 * 
 *  1) In case of Master Receiver (7-bit addressing):
 *     I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED event is set.
 * 
 *  2) In case of Master Transmitter (7-bit addressing):
 *     I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED is set.
 * 
 *  3) In case of 10-Bit addressing mode, master (just after generating START
 *     and checking on EV5) has to send header of 10-bit addressing mode
 *     (I2C_SendData() function). Then master should wait on EV9. It means
 *     that 10-bit addressing header has been correctly sent on bus.
 *     Then master should send second part of 10-bit address (LSB) using
 *     function I2C_Send7bitAddress(). Then master should wait for event EV6.
 */

/**
 * Communication events
 * 
 * If a communication is established (START condition generated and slave
 * address acknowledged) then master has to check on one of following events
 * for communication procedures:
 * 
 * 1) Master Receiver mode: The master has to wait on event EV7 then to read
 *    data received from slave (I2C_ReceiveData() function).
 * 
 * 2) Master Transmitter mode: The master has to send data (I2C_SendData()
 *    function) then to wait on event EV8 or EV8_2.
 *    These two events are similar:
 *     - EV8 means that data has been written in data register and is 
 *       being shifted out.
 *     - EV8_2 means that data has been physically shifted out and output 
 *       on bus.
 *     In most cases, using EV8 is sufficient for application.
 *     Using EV8_2 leads to a slower communication but ensure more reliable
 *     test. EV8_2 is also more suitable than EV8 for testing on last data
 *     transmission (before Stop condition generation).
 * 
 * In case  user software does not guarantee that this event EV7 is 
 * managed before current byte end of transfer, then user may check on EV7 
 * and BTF flag at same time (I2C_EVENT_MASTER_BYTE_RECEIVED | I2C_FLAG_BTF).
 * In this case communication may be slower.
 */

/* BUSY, MSL and RXNE flags */
#define I2C_EVENT_MASTER_BYTE_RECEIVED ((uint32_t) 0x00030040)

/* TRA, BUSY, MSL, TXE flags */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING ((uint32_t) 0x00070080)

/* TRA, BUSY, MSL, TXE and BTF flags */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTED ((uint32_t) 0x00070084)

/** 
 * Communication start events
 * 
 * Wait on one of these events at start of communication. It means that
 * I2C peripheral detected a Start condition on bus (generated by master
 * device) followed by peripheral address. The peripheral generates an ACK
 * condition on bus (if acknowledge feature is enabled through function
 * I2C_AcknowledgeConfig()) and events listed above are set:
 * 
 * 1) In normal case (only one address managed by slave), when address
 *    sent by master matches own address of peripheral (configured by
 *    I2C_OwnAddress1 field) I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set
 *    (where XXX could be TRANSMITTER or RECEIVER).
 * 
 * 2) In case address sent by master matches second address of peripheral
 *    (configured by function I2C_OwnAddress2Config() and enabled 
 *    by function I2C_DualAddressCmd()) events
 *    I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED (where XXX could be
 *    TRANSMITTER or RECEIVER) are set.
 * 
 * 3) In case address sent by master is General Call (address 0x00) and
 *    if Call is enabled for peripheral (function I2C_GeneralCallCmd())
 *    following event is set I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED.
 */

/* EV1 (all events below are variants of EV1) */
/* 1) Case of One Single Address managed by slave */
/* BUSY and ADDR flags */
#define I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED ((uint32_t) 0x00020002)

/* TRA, BUSY, TXE and ADDR flags */
#define I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED ((uint32_t) 0x00060082)

/* 2) Case of Dual address managed by slave */
/* DUALF and BUSY flags */
#define I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED ((uint32_t) 0x00820000)

/* DUALF, TRA, BUSY and TXE flags */
#define I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ( \
    (uint32_t) 0x00860080 \
)

/* 3) Case of General Call enabled for slave */
/* GENCALL and BUSY flags */
#define I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED ((uint32_t) 0x00120000)

/**
 * Wait on one of these events when EV1 has already been checked and:
 * 
 * - Slave RECEIVER mode:
 *     - EV2: When application is expecting a data byte to be received.
 *     - EV4: When application is expecting end of communication: master
 *       sends a stop condition and data transmission is stopped.
 * 
 * - Slave Transmitter mode:
 *    - EV3: When a byte has been transmitted by slave and application is
 *      expecting end of byte transmission. The two events
 *      I2C_EVENT_SLAVE_BYTE_TRANSMITTED and I2C_EVENT_SLAVE_BYTE_TRANSMITTING
 *      are similar. The second one can optionally be used when user
 *      software doesn't guarantee EV3 is managed before current byte
 *      end of transfer.
 *    - EV3_2: When master sends a NACK in order to tell slave that data
 *      transmission shall end (before sending STOP condition). In this case
 *      slave has to stop sending data bytes and expect Stop condition on bus.
 * 
 * In case  user software does not guarantee that event EV2 is
 * managed before current byte end of transfer, then user may check on EV2
 * and BTF flag at same time (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_BTF).
 * In this case communication may be slower.
 */

/* Slave RECEIVER mode, BUSY, RXNE, STOP flags*/
#define I2C_EVENT_SLAVE_BYTE_RECEIVED ((uint32_t) 0x00020040)
#define I2C_EVENT_SLAVE_STOP_DETECTED ((uint32_t) 0x00000010)

/* Slave TRANSMITTER mode */
/* TRA, BUSY, TXE and BTF flags */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTED ((uint32_t) 0x00060084)

/* TRA, BUSY and TXE flags */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTING ((uint32_t) 0x00060080)

/* AF flag */
#define I2C_EVENT_SLAVE_ACK_FAILURE ((uint32_t) 0x00000400)

#define IS_I2C_EVENT(EVENT) ( \
    ((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) || \
    ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) || \
    ((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED) || \
    ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED) || \
    ((EVENT) == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED) || \
    ((EVENT) == I2C_EVENT_SLAVE_BYTE_RECEIVED) || \
    ((EVENT) == (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)) || \
    ((EVENT) == (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)) || \
    ((EVENT) == I2C_EVENT_SLAVE_BYTE_TRANSMITTED) || \
    ((EVENT) == (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)) || \
    ((EVENT) == (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL)) || \
    ((EVENT) == I2C_EVENT_SLAVE_STOP_DETECTED) || \
    ((EVENT) == I2C_EVENT_MASTER_MODE_SELECT) || \
    ((EVENT) == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) || \
    ((EVENT) == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) || \
    ((EVENT) == I2C_EVENT_MASTER_BYTE_RECEIVED) || \
    ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTED) || \
    ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTING) || \
    ((EVENT) == I2C_EVENT_MASTER_MODE_ADDRESS10) || \
    ((EVENT) == I2C_EVENT_SLAVE_ACK_FAILURE) \
)

#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x3FF)
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 400000))

void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);

void I2C_Send7bitAddress(
    I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction
);

void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle);
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);

void I2C_ITConfig(
    I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState
);

/**
  This I2C driver provides three different ways for I2C state monitoring
  depending on application requirements and constraints:
     1. Basic state monitoring (Using I2C_CheckEvent() function)
     -----------------------------------------------------------
        It compares status registers (SR1 and SR2) content to a given
        event (can be combination of one or more flags).
        It returns SUCCESS if current status includes given flags
        and returns ERROR if one or more flags are missing in current status.
      - When to use
      --------------
      - This function is suitable for most applications as well as for startup
        activity since events are fully described in product reference
        manual (RM0090).
      - It is also suitable for users who need to define their own events.
      - Limitations
      --------------
      - If an error occurs (ie. error flags are set besides to monitored
        flags), I2C_CheckEvent() function may return SUCCESS despite
        communication hold or corrupted real state. 
        In this case, it is advised to use error interrupts to monitor
        error events and handle them in interrupt IRQ handler.
      Note
      ----
        For error management, it is advised to use following functions:
        - I2C_ITConfig() to configure and enable error interrupts (I2C_IT_ERR).
        - I2Cx_ER_IRQHandler() which is called when error interrupt occurs.
          Where x is peripheral instance (I2C1, I2C2, ...)
        - I2C_GetFlagStatus() or I2C_GetITStatus()  to be called into 
          I2Cx_ER_IRQHandler() function in order to determine which error
          occurred.
        - I2C_ClearFlag() or I2C_ClearITPendingBit() and/or
          I2C_SoftwareResetCmd() and/or I2C_GenerateStop() in order to clear
          error flag and source and return to correct  communication status.
     2. Advanced state monitoring (Using function I2C_GetLastEvent())
     --------------------------------------------------------------------
        Using function I2C_GetLastEvent() which returns image of both status
        registers in a single word (uint32_t) (Status Register 2 value is
        shifted left by 16 bits and concatenated to Status Register 1).
      - When to use
      --------------
        - This function is suitable for same applications above but it
          allows to overcome mentioned limitation of I2C_GetFlagStatus()
          function.
        - The returned value could be compared to events already defined in
          this file or to custom values defined by user.
          This function is suitable when multiple flags are monitored at
          same time.
        - At opposite of I2C_CheckEvent() function, this function allows
          user to choose when an event is accepted (when all events flags are
          set and no other flags are set or just when needed flags are set
          like I2C_CheckEvent() function.
      - Limitations
      --------------
        - User may need to define his own events.
        - Same remark concerning error management is applicable for this
          function if user decides to check only regular communication flags
          (and ignores error flags).
     3. Flag-based state monitoring (Using function I2C_GetFlagStatus())
     -----------------------------------------------------------------------
          Using function I2C_GetFlagStatus() which simply returns status of
          one single flag (ie. I2C_FLAG_RXNE ...)
       - When to use
       - This function could be used for specific applications or in debug
         phase.
       - It is suitable when only one flag checking is needed (most I2C
         events are monitored through multiple flags).
       - Limitations: 
         - When calling this function, Status register is accessed.
           Some flags are cleared when status register is accessed.
           So checking status of one Flag, may clear other ones.
         - Function may need to be called twice or more in order to monitor
           one single event.
 */

ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);

#ifdef __cplusplus
    }
#endif

#endif

