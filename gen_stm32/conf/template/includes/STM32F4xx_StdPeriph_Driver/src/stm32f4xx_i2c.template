/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_i2c.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Inter-integrated circuit (I2C)
 *     - Initialization and Configuration
 *     - Data transfers
 *     - PEC management
 *     - DMA transfers management
 *     - Interrupts, events and flags management
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

#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

#define CR1_CLEAR_MASK ((uint16_t) 0xFBF5) /* I2C registers Masks */
#define FLAG_MASK ((uint32_t) 0x00FFFFFF) /* I2C FLAG mask */
#define ITEN_MASK ((uint32_t) 0x07000000) /* I2C Interrupt Enable mask */

/**
 * Deinitialize I2Cx peripheral registers to their default reset values.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * retval None
 */
void I2C_DeInit(I2C_TypeDef* I2Cx) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    if (I2Cx == I2C1) {
        /* Enable I2C1 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
        /* Release I2C1 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    } else if (I2Cx == I2C2) {
        /* Enable I2C2 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
        /* Release I2C2 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
    } else {
        if (I2Cx == I2C3) {
            /* Enable I2C3 reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, ENABLE);
            /* Release I2C3 from reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, DISABLE);
        }
    }
}

/**
 * Initializes I2Cx peripheral according to specified parameters in
 * I2C_InitStruct.
 * To use I2C at 400 KHz (in fast mode), PCLK1 frequency 
 * (I2C peripheral input clock) must be a multiple of 10 MHz.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_InitStruct: pointer to a I2C_InitTypeDef structure that contains
 *       configuration information for specified I2C peripheral.
 * retval None
 */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct) {
    uint16_t tmpreg = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk1 = 8000000;
    RCC_ClocksTypeDef  rcc_clocks;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
    assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
    assert_param(IS_I2C_DUTY_CYCLE(I2C_InitStruct->I2C_DutyCycle));
    assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
    assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
    assert_param(
        IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress)
    );
    /* I2Cx CR2 Configuration */
    tmpreg = I2Cx->CR2; /* Get I2Cx CR2 value */
    /* Clear frequency FREQ[5:0] bits */
    tmpreg &= (uint16_t) ~((uint16_t) I2C_CR2_FREQ);
    /* Get pclk1 frequency value */
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.PCLK1_Frequency;
    /* Set frequency bits depending on pclk1 value */
    freqrange = (uint16_t) (pclk1 / 1000000);
    tmpreg |= freqrange;
    /* Write to I2Cx CR2 */
    I2Cx->CR2 = tmpreg;
    /* I2Cx CCR Configuration */
    /* Disable selected I2C peripheral to configure TRISE */
    I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_PE);
    /* Reset tmpreg value */
    tmpreg = 0; /* Clear F/S, DUTY and CCR[11:0] bits */
    /* Configure speed in standard mode */
    if (I2C_InitStruct->I2C_ClockSpeed <= 100000) {
        /* Standard mode speed calculate */
        result = (uint16_t) (pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));
        /* Test if CCR value is under 0x4*/
        if (result < 0x04) {
            result = 0x04; /* Set minimum allowed value */
        }
        tmpreg |= result; /* Set speed value for standard mode */
        /* Set Maximum Rise Time for standard mode */
        I2Cx->TRISE = freqrange + 1; 
    } else {
        if (I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2) {
            /* Fast mode speed calculate: Tlow/Thigh = 2 */
            result = (uint16_t) (pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
        } else {
            /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
            result = (uint16_t) (
                pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25)
            );
            result |= I2C_DutyCycle_16_9; /* Set DUTY bit */
        }
        /* Test if CCR value is under 0x1*/
        if ((result & I2C_CCR_CCR) == 0) {
            result |= (uint16_t) 0x0001; /* Set minimum allowed value */
        }
        /* Set speed value and set F/S bit for fast mode */
        tmpreg |= (uint16_t) (result | I2C_CCR_FS);
        /* Set Maximum Rise Time for fast mode */
        I2Cx->TRISE = (uint16_t) (
            ((freqrange * (uint16_t) 300) / (uint16_t) 1000) + (uint16_t) 1
        );
    }
    I2Cx->CCR = tmpreg; /* Write to I2Cx CCR */
    I2Cx->CR1 |= I2C_CR1_PE; /* Enable selected I2C peripheral */
    /* I2Cx CR1 Configuration */
    tmpreg = I2Cx->CR1; /* Get I2Cx CR1 value */
    tmpreg &= CR1_CLEAR_MASK; /* Clear ACK, SMBTYPE and  SMBUS bits */
    /* Configure I2Cx: mode and acknowledgement */
    /* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
    /* Set ACK bit according to I2C_Ack value */
    tmpreg |= (uint16_t) (
        (uint32_t) I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack
    );
    I2Cx->CR1 = tmpreg; /* Write to I2Cx CR1 */
    /* I2Cx OAR1 Configuration */
    /* Set I2Cx Own Address1 and acknowledged address */
    I2Cx->OAR1 = (
        I2C_InitStruct->I2C_AcknowledgedAddress |
        I2C_InitStruct->I2C_OwnAddress1
    );
}

/**
 * Fills each I2C_InitStruct member with its default value.
 * param I2C_InitStruct: pointer to an I2C_InitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct) {
    /* Reset I2C init structure parameters values */
    /* initialize I2C_ClockSpeed member */
    I2C_InitStruct->I2C_ClockSpeed = 5000;
    /* Initialize I2C_Mode member */
    I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
    /* Initialize I2C_DutyCycle member */
    I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;
    /* Initialize I2C_OwnAddress1 member */
    I2C_InitStruct->I2C_OwnAddress1 = 0;
    /* Initialize I2C_Ack member */
    I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
    /* Initialize I2C_AcknowledgedAddress member */
    I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/**
 * Enables or disables specified I2C peripheral.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2Cx peripheral.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_PE; /* Enable selected I2C peripheral */
    } else {
        /* Disable selected I2C peripheral */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_PE);
    }
}

/**
 * Generates I2Cx communication START condition.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C START condition generation.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None.
 */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_START; /* Generate a START condition */
    } else {
        /* Disable START condition generation */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_START);
    }
}

/**
 * Generates I2Cx communication STOP condition.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C STOP condition generation.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None.
 */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_STOP; /* Generate a STOP condition */
    } else {
        /* Disable STOP condition generation */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_STOP);
    }
}

/**
 * Transmits address byte to select slave device.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param Address: specifies slave address which will be transmitted
 * param I2C_Direction: specifies whether I2C device will be a Transmitter
 *       or a Receiver.
 *  This parameter can be one of following values
 *      arg I2C_Direction_Transmitter: Transmitter mode
 *      arg I2C_Direction_Receiver: Receiver mode
 * retval None.
 */
void I2C_Send7bitAddress(
    I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction
) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DIRECTION(I2C_Direction));
    /* Test on direction to set/reset read/write bit */
    if (I2C_Direction != I2C_Direction_Transmitter) {
        Address |= I2C_OAR1_ADD0; /* Set address bit0 for read */
    } else {
        /* Reset address bit0 for write */
        Address &= (uint8_t) ~((uint8_t) I2C_OAR1_ADD0);
    }
    I2Cx->DR = Address; /* Send address */
}

/**
 * Enables or disables specified I2C acknowledge feature.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C Acknowledgement.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None.
 */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_ACK; /* Enable acknowledgement */
    } else {
        /* Disable acknowledgement */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_ACK);
    }
}

/**
 * Configures specified I2C own address2.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param Address: specifies 7bit I2C own address2.
 * retval None.
 */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address) {
    uint16_t tmpreg = 0;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    tmpreg = I2Cx->OAR2; /* Get old register value */
    /* Reset I2Cx Own address2 bit [7:1] */
    tmpreg &= (uint16_t) ~((uint16_t) I2C_OAR2_ADD2);
    /* Set I2Cx Own address2 */
    tmpreg |= (uint16_t) ((uint16_t) Address & (uint16_t) 0x00FE);
    I2Cx->OAR2 = tmpreg; /* Store new register value */
}

/**
 * Enables or disables specified I2C dual addressing mode.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C dual addressing mode.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->OAR2 |= I2C_OAR2_ENDUAL; /* Enable dual addressing mode */
    } else {
        /* Disable dual addressing mode */
        I2Cx->OAR2 &= (uint16_t) ~((uint16_t) I2C_OAR2_ENDUAL);
    }
}

/**
 * Enables or disables specified I2C general call feature.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C General call.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_ENGC; /* Enable generall call */
    } else {
        /* Disable generall call */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_ENGC);
    }
}

/**
 * Enables or disables specified I2C software reset.
 * When software reset is enabled, I2C IOs are released (this can
 * be useful to recover from bus errors).  
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C software reset.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_SWRST; /* Peripheral under reset */
    } else {
        /* Peripheral not under reset */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_SWRST);
    }
}

/**
 * Enables or disables specified I2C Clock stretching.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2Cx Clock stretching.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState == DISABLE) {
        /* Enable selected I2C Clock stretching */
        I2Cx->CR1 |= I2C_CR1_NOSTRETCH;
    } else {
        /* Disable selected I2C Clock stretching */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_NOSTRETCH);
    }
}

/**
 * Selects specified I2C fast mode duty cycle.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_DutyCycle: specifies fast mode duty cycle.
 *  This parameter can be one of following values:
 *      arg I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
 *      arg I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
 * retval None
 */
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));
    if (I2C_DutyCycle != I2C_DutyCycle_16_9) {
        I2Cx->CCR &= I2C_DutyCycle_2; /* I2C fast mode Tlow/Thigh=2 */
    } else {
        /* I2C fast mode Tlow/Thigh=16/9 */
        I2Cx->CCR |= I2C_DutyCycle_16_9;
    }
}

/**
 * Selects specified I2C NACK position in master receiver mode.
 * This function is useful in I2C Master Receiver mode when number
 * of data to be received is equal to 2. In this case, this function 
 * should be called (with parameter I2C_NACKPosition_Next) before data 
 * reception starts,as described in 2-byte reception procedure 
 * recommended in Reference Manual in Section: Master receiver.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_NACKPosition: specifies NACK position.
 *  This parameter can be one of following values:
 *      arg I2C_NACKPosition_Next: indicates that next byte will be last
 *          received byte.
 *      arg I2C_NACKPosition_Current: indicates that current byte is last 
 *          received byte.
 *  This function configures same bit (POS) as I2C_PECPositionConfig() 
 *  but is intended to be used in I2C mode while I2C_PECPositionConfig() 
 *  is intended to used in SMBUS mode.
 * retval None
 */
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));
    /* Check input parameter */
    if (I2C_NACKPosition == I2C_NACKPosition_Next) {
        /* Next byte in shift register is last received byte */
        I2Cx->CR1 |= I2C_NACKPosition_Next;
    } else {
        /* Current byte in shift register is last received byte */
        I2Cx->CR1 &= I2C_NACKPosition_Current;
    }
}

/**
 * Drives SMBusAlert pin high or low for specified I2C.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_SMBusAlert: specifies SMBAlert pin level. 
 *  This parameter can be one of following values:
 *      arg I2C_SMBusAlert_Low: SMBAlert pin driven low
 *      arg I2C_SMBusAlert_High: SMBAlert pin driven high
 * retval None
 */
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_SMBUS_ALERT(I2C_SMBusAlert));
    if (I2C_SMBusAlert == I2C_SMBusAlert_Low) {
        I2Cx->CR1 |= I2C_SMBusAlert_Low; /* Drive SMBusAlert pin Low */
    } else {
        I2Cx->CR1 &= I2C_SMBusAlert_High; /* Drive SMBusAlert pin High */
    }
}

/**
 * Enables or disables specified I2C ARP.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2Cx ARP. 
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_ENARP; /* Enable selected I2C ARP */
    } else {
        /* Disable selected I2C ARP */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_ENARP);
    }
}

/**
 * Sends a data byte through I2Cx peripheral.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param Data: Byte to be transmitted..
 * retval None
 */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    I2Cx->DR = Data; /* Write in DR register data to be sent */
}

/**
 * Returns most recent received data by I2Cx peripheral.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * retval The value of received data.
 */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    return (uint8_t) I2Cx->DR; /* Return data in DR register */
}

/**
 * Enables or disables specified I2C PEC transfer.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C PEC transmission.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected I2C PEC transmission */
        I2Cx->CR1 |= I2C_CR1_PEC;
    } else {
        /* Disable selected I2C PEC transmission */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_PEC);
    }
}

/**
 * Selects specified I2C PEC position.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_PECPosition: specifies PEC position. 
 *  This parameter can be one of following values:
 *      arg I2C_PECPosition_Next: indicates that next byte is PEC
 *      arg I2C_PECPosition_Current: indicates that current byte is PEC
 *  This function configures same bit (POS) as I2C_NACKPositionConfig()
 *  but is intended to be used in SMBUS mode while I2C_NACKPositionConfig() 
 *  is intended to used in I2C mode.
 * retval None
 */
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_PEC_POSITION(I2C_PECPosition));
    if (I2C_PECPosition == I2C_PECPosition_Next) {
        /* Next byte in shift register is PEC */
        I2Cx->CR1 |= I2C_PECPosition_Next;
    } else {
        /* Current byte in shift register is PEC */
        I2Cx->CR1 &= I2C_PECPosition_Current;
    }
}

/**
 * Enables or disables PEC value calculation of transferred bytes.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2Cx PEC value calculation.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR1 |= I2C_CR1_ENPEC; /* Enable selected I2C PEC calculation */
    } else {
        /* Disable selected I2C PEC calculation */
        I2Cx->CR1 &= (uint16_t) ~((uint16_t) I2C_CR1_ENPEC);
    }
}

/**
 * Returns PEC value for specified I2C.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * retval The PEC value.
 */
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    return ((I2Cx->SR2) >> 8); /* Return selected I2C PEC value */
}

/**
 * Enables or disables specified I2C DMA requests.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C DMA transfer.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR2 |= I2C_CR2_DMAEN; /* Enable selected I2C DMA requests */
    } else {
        /* Disable selected I2C DMA requests */
        I2Cx->CR2 &= (uint16_t) ~((uint16_t) I2C_CR2_DMAEN);
    }
}

/**
 * Specifies that next DMA transfer is last one.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param NewState: new state of I2C DMA last transfer.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        I2Cx->CR2 |= I2C_CR2_LAST; /* Next DMA transfer is last transfer */
    } else {
        /* Next DMA transfer is not last transfer */
        I2Cx->CR2 &= (uint16_t) ~((uint16_t) I2C_CR2_LAST);
    }
}

/**
 * Reads specified I2C register and returns its value.
 * param I2C_Register: specifies register to read.
 *  This parameter can be one of following values:
 *      arg I2C_Register_CR1: CR1 register.
 *      arg I2C_Register_CR2: CR2 register.
 *      arg I2C_Register_OAR1: OAR1 register.
 *      arg I2C_Register_OAR2: OAR2 register.
 *      arg I2C_Register_DR: DR register.
 *      arg I2C_Register_SR1: SR1 register.
 *      arg I2C_Register_SR2: SR2 register.
 *      arg I2C_Register_CCR: CCR register.
 *      arg I2C_Register_TRISE: TRISE register.
 * retval The value of read register.
 */
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register) {
    __IO uint32_t tmp = 0;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_REGISTER(I2C_Register));
    tmp = (uint32_t) I2Cx;
    tmp += I2C_Register;
    return (*(__IO uint16_t *) tmp); /* Return selected register value */
}

/**
 * Enables or disables specified I2C interrupts.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_IT: specifies I2C interrupts sources to be enabled/disabled.
 *  This parameter can be any combination of following values:
 *      arg I2C_IT_BUF: Buffer interrupt mask
 *      arg I2C_IT_EVT: Event interrupt mask
 *      arg I2C_IT_ERR: Error interrupt mask
 * param NewState: new state of specified I2C interrupts.
 *  This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2C_ITConfig(
    I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState
) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2C_CONFIG_IT(I2C_IT));
    if (NewState != DISABLE) {
        I2Cx->CR2 |= I2C_IT; /* Enable selected I2C interrupts */
    } else {
        I2Cx->CR2 &= (uint16_t) ~I2C_IT; /* Disable selected I2C interrupts */
    }
}

/**
 * Checks whether last I2Cx Event is equal to one passed
 * as parameter.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_EVENT: specifies event to be checked. 
 *  This parameter can be one of following values:
 *      arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED: EV1
 *      arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED: EV1
 *      arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED: EV1
 *      arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED: EV1
 *      arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED: EV1
 *      arg I2C_EVENT_SLAVE_BYTE_RECEIVED: EV2
 *      arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF): EV2
 *      arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL): EV2
 *      arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED: EV3
 *      arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF): EV3
 *      arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL): EV3
 *      arg I2C_EVENT_SLAVE_ACK_FAILURE: EV3_2
 *      arg I2C_EVENT_SLAVE_STOP_DETECTED: EV4
 *      arg I2C_EVENT_MASTER_MODE_SELECT: EV5
 *      arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED: EV6     
 *      arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED: EV6
 *      arg I2C_EVENT_MASTER_BYTE_RECEIVED: EV7
 *      arg I2C_EVENT_MASTER_BYTE_TRANSMITTING: EV8
 *      arg I2C_EVENT_MASTER_BYTE_TRANSMITTED: EV8_2
 *      arg I2C_EVENT_MASTER_MODE_ADDRESS10: EV9
 * For detailed description of Events, please refer to section I2C_Events
 * in stm32f4xx_i2c.h file.
 * retval An ErrorStatus enumeration value:
 *    - SUCCESS: Last event is equal to I2C_EVENT
 *    - ERROR: Last event is different from I2C_EVENT
 */
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;
    ErrorStatus status = ERROR;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_EVENT(I2C_EVENT));
    /* Read I2Cx status register */
    flag1 = I2Cx->SR1;
    flag2 = I2Cx->SR2;
    flag2 = flag2 << 16;
    /* Get last event value from I2C status register */
    lastevent = (flag1 | flag2) & FLAG_MASK;
    /* Check whether last event contains I2C_EVENT */
    if ((lastevent & I2C_EVENT) == I2C_EVENT) {
        status = SUCCESS; /* SUCCESS: last event is equal to I2C_EVENT */
    } else {
        status = ERROR; /* ERROR: last event is different from I2C_EVENT */
    }
    return status; /* Return status */
}

/**
 * Returns last I2Cx Event.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * For detailed description of Events, please refer to section I2C_Events
 * in stm32f4xx_i2c.h file.
 * retval The last event
 */
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx) {
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Read I2Cx status register */
    flag1 = I2Cx->SR1;
    flag2 = I2Cx->SR2;
    flag2 = flag2 << 16;
    /* Get last event value from I2C status register */
    lastevent = (flag1 | flag2) & FLAG_MASK;
    return lastevent; /* Return status */
}

/**
 * Checks whether specified I2C flag is set or not.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_FLAG: specifies flag to check. 
 *  This parameter can be one of following values:
 *      arg I2C_FLAG_DUALF: Dual flag (Slave mode)
 *      arg I2C_FLAG_SMBHOST: SMBus host header (Slave mode)
 *      arg I2C_FLAG_SMBDEFAULT: SMBus default header (Slave mode)
 *      arg I2C_FLAG_GENCALL: General call header flag (Slave mode)
 *      arg I2C_FLAG_TRA: Transmitter/Receiver flag
 *      arg I2C_FLAG_BUSY: Bus busy flag
 *      arg I2C_FLAG_MSL: Master/Slave flag
 *      arg I2C_FLAG_SMBALERT: SMBus Alert flag
 *      arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
 *      arg I2C_FLAG_PECERR: PEC error in reception flag
 *      arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
 *      arg I2C_FLAG_AF: Acknowledge failure flag
 *      arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
 *      arg I2C_FLAG_BERR: Bus error flag
 *      arg I2C_FLAG_TXE: Data register empty flag (Transmitter)
 *      arg I2C_FLAG_RXNE: Data register not empty (Receiver) flag
 *      arg I2C_FLAG_STOPF: Stop detection flag (Slave mode)
 *      arg I2C_FLAG_ADD10: 10-bit header sent flag (Master mode)
 *      arg I2C_FLAG_BTF: Byte transfer finished flag
 *      arg I2C_FLAG_ADDR: Address sent flag (Master mode) "ADSL"
 *        Address matched flag (Slave mode)"ENDAD"
 *      arg I2C_FLAG_SB: Start bit flag (Master mode)
 * retval The new state of I2C_FLAG (SET or RESET).
 */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG) {
    FlagStatus bitstatus = RESET;
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_FLAG(I2C_FLAG));
    i2cxbase = (uint32_t) I2Cx; /* Get I2Cx peripheral base address */
    i2creg = I2C_FLAG >> 28; /* Read flag register index */
    I2C_FLAG &= FLAG_MASK; /* Get bit[23:0] of flag */
    if (i2creg != 0) {
        i2cxbase += 0x14; /* Get I2Cx SR1 register address */
    } else  {
        /* Flag in I2Cx SR2 Register */
        I2C_FLAG = (uint32_t) (I2C_FLAG >> 16);
        i2cxbase += 0x18; /* Get I2Cx SR2 register address */
    }
    if(((*(__IO uint32_t *) i2cxbase) & I2C_FLAG) != (uint32_t) RESET) {
        bitstatus = SET; /* I2C_FLAG is set */
    } else {
        bitstatus = RESET; /* I2C_FLAG is reset */
    }
    return bitstatus; /* Return I2C_FLAG status */
}

/**
 * Clears I2Cx's pending flags.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_FLAG: specifies flag to clear. 
 *  This parameter can be any combination of following values:
 *      arg I2C_FLAG_SMBALERT: SMBus Alert flag
 *      arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
 *      arg I2C_FLAG_PECERR: PEC error in reception flag
 *      arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
 *      arg I2C_FLAG_AF: Acknowledge failure flag
 *      arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
 *      arg I2C_FLAG_BERR: Bus error flag
 * STOPF (STOP detection) is cleared by software sequence: a read operation 
 * to I2C_SR1 register (I2C_GetFlagStatus()) followed by a write operation 
 * to I2C_CR1 register (I2C_Cmd() to re-enable I2C peripheral).
 * ADD10 (10-bit header sent) is cleared by software sequence: a read 
 * operation to I2C_SR1 (I2C_GetFlagStatus()) followed by writing 
 * second byte of address in DR register.
 * BTF (Byte Transfer Finished) is cleared by software sequence: a read 
 * operation to I2C_SR1 register (I2C_GetFlagStatus()) followed by a 
 * read/write to I2C_DR register (I2C_SendData()).
 * ADDR (Address sent) is cleared by software sequence: a read operation to 
 * I2C_SR1 register (I2C_GetFlagStatus()) followed by a read operation to 
 * I2C_SR2 register ((void)(I2Cx->SR2)).
 * SB (Start Bit) is cleared software sequence: a read operation to I2C_SR1
 * register (I2C_GetFlagStatus()) followed by a write operation to I2C_DR
 * register (I2C_SendData()).
 * retval None
 */
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG) {
    uint32_t flagpos = 0;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));
    flagpos = I2C_FLAG & FLAG_MASK; /* Get I2C flag position */
    I2Cx->SR1 = (uint16_t) ~flagpos; /* Clear selected I2C flag */
}

/**
 * Checks whether specified I2C interrupt has occurred or not.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_IT: specifies interrupt source to check. 
 *  This parameter can be one of following values:
 *      arg I2C_IT_SMBALERT: SMBus Alert flag
 *      arg I2C_IT_TIMEOUT: Timeout or Tlow error flag
 *      arg I2C_IT_PECERR: PEC error in reception flag
 *      arg I2C_IT_OVR: Overrun/Underrun flag (Slave mode)
 *      arg I2C_IT_AF: Acknowledge failure flag
 *      arg I2C_IT_ARLO: Arbitration lost flag (Master mode)
 *      arg I2C_IT_BERR: Bus error flag
 *      arg I2C_IT_TXE: Data register empty flag (Transmitter)
 *      arg I2C_IT_RXNE: Data register not empty (Receiver) flag
 *      arg I2C_IT_STOPF: Stop detection flag (Slave mode)
 *      arg I2C_IT_ADD10: 10-bit header sent flag (Master mode)
 *      arg I2C_IT_BTF: Byte transfer finished flag
 *      arg I2C_IT_ADDR: Address sent flag (Master mode) "ADSL"
 *      Address matched flag (Slave mode)"ENDAD"
 *      arg I2C_IT_SB: Start bit flag (Master mode)
 * retval The new state of I2C_IT (SET or RESET).
 */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_IT(I2C_IT));
    /* Check if interrupt source is enabled or not */
    enablestatus = (uint32_t) (((I2C_IT & ITEN_MASK) >> 16) & (I2Cx->CR2));
    I2C_IT &= FLAG_MASK; /* Get bit[23:0] of flag */
    /* Check status of specified I2C flag */
    if (((I2Cx->SR1 & I2C_IT) != (uint32_t)RESET) && enablestatus) {
        bitstatus = SET; /* I2C_IT is set */
    } else {
        bitstatus = RESET; /* I2C_IT is reset */
    }
    return bitstatus; /* Return I2C_IT status */
}

/**
 * Clears I2Cx's interrupt pending bits.
 * param I2Cx: where x can be 1, 2 or 3 to select I2C peripheral.
 * param I2C_IT: specifies interrupt pending bit to clear. 
 *  This parameter can be any combination of following values:
 *      arg I2C_IT_SMBALERT: SMBus Alert interrupt
 *      arg I2C_IT_TIMEOUT: Timeout or Tlow error interrupt
 *      arg I2C_IT_PECERR: PEC error in reception  interrupt
 *      arg I2C_IT_OVR: Overrun/Underrun interrupt (Slave mode)
 *      arg I2C_IT_AF: Acknowledge failure interrupt
 *      arg I2C_IT_ARLO: Arbitration lost interrupt (Master mode)
 *      arg I2C_IT_BERR: Bus error interrupt
 * STOPF (STOP detection) is cleared by software sequence: a read operation
 * to I2C_SR1 register (I2C_GetITStatus()) followed by a write operation to
 * I2C_CR1 register (I2C_Cmd() to re-enable I2C peripheral).
 * ADD10 (10-bit header sent) is cleared by software sequence: a read
 * operation to I2C_SR1 (I2C_GetITStatus()) followed by writing second
 * byte of address in I2C_DR register.
 * BTF (Byte Transfer Finished) is cleared by software sequence: a read
 * operation to I2C_SR1 register (I2C_GetITStatus()) followed by a
 * read/write to I2C_DR register (I2C_SendData()).
 * ADDR (Address sent) is cleared by software sequence: a read operation to
 * I2C_SR1 register (I2C_GetITStatus()) followed by a read operation to
 * I2C_SR2 register ((void)(I2Cx->SR2)).
 * SB (Start Bit) is cleared by software sequence: a read operation to
 * I2C_SR1 register (I2C_GetITStatus()) followed by a write operation to
 * I2C_DR register (I2C_SendData()).
 * retval None
 */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT) {
    uint32_t flagpos = 0;
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_IT(I2C_IT));
    flagpos = I2C_IT & FLAG_MASK; /* Get I2C flag position */
    I2Cx->SR1 = (uint16_t) ~flagpos; /* Clear selected I2C flag */
}

