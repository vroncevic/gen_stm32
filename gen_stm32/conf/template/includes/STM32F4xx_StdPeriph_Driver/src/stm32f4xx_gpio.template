/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_gpio.c
 * 
 * This file provides firmware functions to managefollowing functionalities
 * of GPIO peripheral:
 *   - Initialization and Configuration
 *   - GPIO Read and Write
 *   - GPIO Alternate functions configuration
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_gpio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_gpio is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/**
 * Deinitializes GPIOx peripheral registers to their default reset values.
 * By default, GPIO pins are configured in input floating mode
 * (except JTAG pins).
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * retval None
 */
void GPIO_DeInit(GPIO_TypeDef* GPIOx) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    if (GPIOx == GPIOA) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, DISABLE);
    } else if (GPIOx == GPIOB) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, DISABLE);
    } else if (GPIOx == GPIOC) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, DISABLE);
    } else if (GPIOx == GPIOD) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, DISABLE);
    } else if (GPIOx == GPIOE) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, DISABLE);
    } else if (GPIOx == GPIOF) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOF, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOF, DISABLE);
    } else if (GPIOx == GPIOG) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOG, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOG, DISABLE);
    } else if (GPIOx == GPIOH) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, DISABLE);
    } else {
        if (GPIOx == GPIOI) {
            RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOI, ENABLE);
            RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOI, DISABLE);
        }
    }
}

/**
 * Initializes GPIOx peripheral according tospecified parameters in
 * GPIO_InitStruct.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
 *       configuration information forspecified GPIO peripheral.
 * retval None
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) {
    uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));
    for (pinpos = 0x00; pinpos < 0x10; pinpos++) {
        pos = ((uint32_t) 0x01) << pinpos;
        /* Getport pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
        if (currentpin == pos) {
            GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
            GPIOx->MODER |= (
                ((uint32_t) GPIO_InitStruct->GPIO_Mode) << (pinpos * 2)
            );
            if (
                (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) ||
               (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)
            ) {
                /* Check Speed mode parameters */
                assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
                /* Speed mode configuration */
                GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
                GPIOx->OSPEEDR |= (
                    (uint32_t) (GPIO_InitStruct->GPIO_Speed) << (pinpos * 2)
                );
                /* Check Output mode parameters */
                assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));
                /* Output mode configuration*/
                GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t) pinpos));
                GPIOx->OTYPER |= (uint16_t) (
                    ((uint16_t) GPIO_InitStruct->GPIO_OType) <<
                    ((uint16_t) pinpos)
                );
            }
            /* Pull-up Pull down resistor configuration*/
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t) pinpos * 2));
            GPIOx->PUPDR |= (
                ((uint32_t) GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2)
            );
        }
    }
}

/**
 * Fills each GPIO_InitStruct member with its default value.
 * param GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which
 *       will be initialized.
 * retval None
 */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct) {
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
 * Locks GPIO Pins configuration registers.
 * The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
 * GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
 * The configuration oflocked GPIO pins can no longer be modified
 * untilnext reset.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: specifiesport bit to be locked.
 *   Parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 * retval None
 */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    __IO uint32_t tmp = 0x00010000;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    tmp |= GPIO_Pin;
    GPIOx->LCKR = tmp; /* Set LCKK bit */
    GPIOx->LCKR =  GPIO_Pin; /* Reset LCKK bit */
    GPIOx->LCKR = tmp; /* Set LCKK bit */
    tmp = GPIOx->LCKR; /* Read LCKK bit*/
    tmp = GPIOx->LCKR; /* Read LCKK bit*/
}

/**
 * Readsspecified input port pin.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: specifiesport bit to read.
 *   This parameter can be GPIO_Pin_x where x can be (0..15).
 * retval The input port pin value.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    uint8_t bitstatus = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t) Bit_RESET) {
        bitstatus = (uint8_t) Bit_SET;
    } else {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 * Readsspecified GPIO input data port.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * retval GPIO input data port value.
 */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    return ((uint16_t) GPIOx->IDR);
}

/**
 * Readsspecified output data port bit.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: specifiesport bit to read.
 *   This parameter can be GPIO_Pin_x where x can be (0..15).
 * retval The output port pin value.
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    uint8_t bitstatus = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    if ((GPIOx->ODR & GPIO_Pin) != (uint32_t) Bit_RESET) {
        bitstatus = (uint8_t)Bit_SET;
    } else {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 * Readsspecified GPIO output data port.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * retval GPIO output data port value.
 */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    return ((uint16_t) GPIOx->ODR);
}

/**
 * Setsselected data port bits.
 * This functions uses GPIOx_BSRR register to allow atomic read/modify 
 * accesses. In this way, there is no risk of an IRQ occurring between
 * read andmodify access.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: specifiesport bits to be written.
 *   Parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 * retval None
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    GPIOx->BSRRL = GPIO_Pin;
}

/**
 * Clearsselected data port bits.
 * This functions uses GPIOx_BSRR register to allow atomic read/modify 
 * accesses. In this way, there is no risk of an IRQ occurring between
 * read andmodify access.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: specifiesport bits to be written.
 *   Parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 * retval None
 */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    GPIOx->BSRRH = GPIO_Pin;
}

/**
 * Sets or clearsselected data port bit.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: specifiesport bit to be written.
 *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
 * param BitVal: specifiesvalue to be written toselected bit.
 *   This parameter can be one ofBitAction enum values:
 *       arg Bit_RESET: to clearport pin
 *       arg Bit_SET: to setport pin
 * retval None
 */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));
    if (BitVal != Bit_RESET) {
        GPIOx->BSRRL = GPIO_Pin;
    } else {
        GPIOx->BSRRH = GPIO_Pin ;
    }
}

/**
 * Writes data tospecified GPIO data port.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param PortVal: specifiesvalue to be written toport output data register.
 * retval None
 */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    GPIOx->ODR = PortVal;
}

/**
 * Togglesspecified GPIO pins.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_Pin: Specifiespins to be toggled.
 * retval None
 */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    GPIOx->ODR ^= GPIO_Pin;
}

/**
 * Changesmapping ofspecified pin.
 * param GPIOx: where x can be (A..I) to selectGPIO peripheral.
 * param GPIO_PinSource: specifiespin forAlternate function.
 *   This parameter can be GPIO_PinSourcex where x can be (0..15).
 * param GPIO_AFSelection: selectspin to used as Alternate function.
 *   This parameter can be one offollowing values:
 *       arg GPIO_AF_RTC_50Hz: Connect RTC_50Hz pin to AF0
 *           (default after reset)
 *       arg GPIO_AF_MCO: Connect MCO pin (MCO1 and MCO2) to AF0
 *           (default after reset)
 *       arg GPIO_AF_TAMPER: Connect TAMPER pins (TAMPER_1 and TAMPER_2) to
 *           AF0 (default after reset)
 *       arg GPIO_AF_SWJ: Connect SWJ pins (SWD and JTAG)to AF0
 *           (default after reset)
 *       arg GPIO_AF_TRACE: Connect TRACE pins to AF0 (default after reset)
 *       arg GPIO_AF_TIM1: Connect TIM1 pins to AF1
 *       arg GPIO_AF_TIM2: Connect TIM2 pins to AF1
 *       arg GPIO_AF_TIM3: Connect TIM3 pins to AF2
 *       arg GPIO_AF_TIM4: Connect TIM4 pins to AF2
 *       arg GPIO_AF_TIM5: Connect TIM5 pins to AF2
 *       arg GPIO_AF_TIM8: Connect TIM8 pins to AF3
 *       arg GPIO_AF_TIM9: Connect TIM9 pins to AF3
 *       arg GPIO_AF_TIM10: Connect TIM10 pins to AF3
 *       arg GPIO_AF_TIM11: Connect TIM11 pins to AF3
 *       arg GPIO_AF_I2C1: Connect I2C1 pins to AF4
 *       arg GPIO_AF_I2C2: Connect I2C2 pins to AF4
 *       arg GPIO_AF_I2C3: Connect I2C3 pins to AF4
 *       arg GPIO_AF_SPI1: Connect SPI1 pins to AF5
 *       arg GPIO_AF_SPI2: Connect SPI2/I2S2 pins to AF5
 *       arg GPIO_AF_SPI3: Connect SPI3/I2S3 pins to AF6
 *       arg GPIO_AF_I2S3ext: Connect I2S3ext pins to AF7
 *       arg GPIO_AF_USART1: Connect USART1 pins to AF7
 *       arg GPIO_AF_USART2: Connect USART2 pins to AF7
 *       arg GPIO_AF_USART3: Connect USART3 pins to AF7
 *       arg GPIO_AF_UART4: Connect UART4 pins to AF8
 *       arg GPIO_AF_UART5: Connect UART5 pins to AF8
 *       arg GPIO_AF_USART6: Connect USART6 pins to AF8
 *       arg GPIO_AF_CAN1: Connect CAN1 pins to AF9
 *       arg GPIO_AF_CAN2: Connect CAN2 pins to AF9
 *       arg GPIO_AF_TIM12: Connect TIM12 pins to AF9
 *       arg GPIO_AF_TIM13: Connect TIM13 pins to AF9
 *       arg GPIO_AF_TIM14: Connect TIM14 pins to AF9
 *       arg GPIO_AF_OTG_FS: Connect OTG_FS pins to AF10
 *       arg GPIO_AF_OTG_HS: Connect OTG_HS pins to AF10
 *       arg GPIO_AF_ETH: Connect ETHERNET pins to AF11
 *       arg GPIO_AF_FSMC: Connect FSMC pins to AF12
 *       arg GPIO_AF_OTG_HS_FS: Connect OTG HS (configured in FS) pins to AF12
 *       arg GPIO_AF_SDIO: Connect SDIO pins to AF12
 *       arg GPIO_AF_DCMI: Connect DCMI pins to AF13
 *       arg GPIO_AF_EVENTOUT: Connect EVENTOUT pins to AF15
 * retval None
 */
void GPIO_PinAFConfig(
    GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF
) {
    uint32_t temp = 0x00;
    uint32_t temp_2 = 0x00;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    assert_param(IS_GPIO_AF(GPIO_AF));
    temp = (
        (uint32_t) (GPIO_AF) << (
            (uint32_t) ((uint32_t) GPIO_PinSource & (uint32_t) 0x07) * 4
        )
    );
    GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~(
        (uint32_t) 0xF << (
            (uint32_t) ((uint32_t) GPIO_PinSource & (uint32_t) 0x07) * 4
        )
    );
    temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
    GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

