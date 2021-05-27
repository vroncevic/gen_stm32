/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_spi.c
 * 
 * This file provides firmware functions to managefollowing
 * functionalities ofSerial peripheral interface (SPI):
 *     - Initialization and Configuration
 *     - Data transfers functions
 *     - Hardware CRC Calculation
 *     - DMA transfers management
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_spi is free software: you can redistribute it and/or modify
 * it underterms ofGNU General Public License as published by the
 * Free Software Foundation, either version 3 ofLicense, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_spi is distributed inhope that it will be useful, but
 * WITHOUT ANY WARRANTY; without evenimplied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * SeeGNU General Public License for more details.
 * SeeARM License for more details.
 *
 * You should have received a copy ofGNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* SPI registers Masks */
#define CR1_CLEAR_MASK ((uint16_t) 0x3040)
#define I2SCFGR_CLEAR_MASK ((uint16_t) 0xF040)

/* RCC PLLs masks */
#define PLLCFGR_PPLR_MASK ((uint32_t) 0x70000000)
#define PLLCFGR_PPLN_MASK ((uint32_t) 0x00007FC0)

#define SPI_CR2_FRF ((uint16_t) 0x0010)
#define SPI_SR_TIFRFE ((uint16_t) 0x0100)

/**
 * DeinitializeSPIx peripheral registers to their default reset values.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode.
 * The extended I2S blocks (ie. I2S2ext and I2S3ext blocks) are deinitialized
 * whenrelative I2S peripheral is deinitialized (extended block's clock
 * is managed byI2S peripheral clock).
 * retval None
 */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    if (SPIx == SPI1) {
        /* Enable SPI1 reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
        /* Release SPI1 from reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
    } else if (SPIx == SPI2) {
        /* Enable SPI2 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
        /* Release SPI2 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
    } else {
        if (SPIx == SPI3) {
            /* Enable SPI3 reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
            /* Release SPI3 from reset state */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
        }
    }
}

/**
 * InitializesSPIx peripheral according tospecified
 * parameters inSPI_InitStruct.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
 *       containsconfiguration information forspecified SPI peripheral.
 * retval None
 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct) {
    uint16_t tmpreg = 0;

    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
    assert_param(
        IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler)
    );
    assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
    assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));
    /* SPIx CR1 Configuration */
    tmpreg = SPIx->CR1; /* GetSPIx CR1 value */
    /**
     * Clear:
     * BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL
     * and CPHA bits 
     */
    tmpreg &= CR1_CLEAR_MASK;
    /**
     * Configure SPIx: direction, NSS management, first transmitted bit,
     * BaudRate prescaler master/salve mode, CPOL and CPHA 
     */
    /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
    /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
    /* Set LSBFirst bit according to SPI_FirstBit value */
    /* Set BR bits according to SPI_BaudRatePrescaler value */
    /* Set CPOL bit according to SPI_CPOL value */
    /* Set CPHA bit according to SPI_CPHA value */
    tmpreg |= (uint16_t) (
        (uint32_t) SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
        SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |
        SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |
        SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit
    );
    SPIx->CR1 = tmpreg; /* Write to SPIx CR1 */
    /* ActivateSPI mode (Reset I2SMOD bit in I2SCFGR register) */
    SPIx->I2SCFGR &= (uint16_t) ~((uint16_t) SPI_I2SCFGR_I2SMOD);
    /* SPIx CRCPOLY Configuration */
    /* Write to SPIx CRCPOLY */
    SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/**
 * InitializesSPIx peripheral according tospecified 
 * parameters inI2S_InitStruct.
 * param SPIx: where x can be  2 or 3 to selectSPI peripheral
 *       (configured in I2S mode).
 * param I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
 *       containsconfiguration information forspecified SPI peripheral
 *       configured in I2S mode.
 * The function calculatesoptimal prescaler needed to obtainmost 
 * accurate audio frequency (depending onI2S clock source,PLL values 
 * andproduct configuration). But in caseprescaler value is greater 
 * than 511,default value (0x02) will be configured instead.
 * 
 * If an external clock is used as source clock forI2S, thendefine
 * I2S_EXTERNAL_CLOCK_VAL in file stm32f4xx_conf.h should be enabled and set
 * tovalue ofthe source clock frequency (in Hz).
 * retval None
 */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct) {
    uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
    uint32_t tmp = 0, i2sclk = 0;
#ifndef I2S_EXTERNAL_CLOCK_VAL
    uint32_t pllm = 0, plln = 0, pllr = 0;
#endif
    assert_param(IS_SPI_23_PERIPH(SPIx));
    assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
    assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
    assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
    assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
    assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
    assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));
    /* SPIx I2SCFGR & I2SPR Configuration */
    /**
     * Clear:
     * I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits 
     */
    SPIx->I2SCFGR &= I2SCFGR_CLEAR_MASK;
    SPIx->I2SPR = 0x0002;
    tmpreg = SPIx->I2SCFGR; /* GetI2SCFGR register value */
    /* Ifdefault value has to be written, reinitialize i2sdiv and i2sodd*/
    if (I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default) {
        i2sodd = (uint16_t) 0;
        i2sdiv = (uint16_t) 2;
    } else {
        /* Checkframe length (ForPrescaler computing) */
        if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b) {
            packetlength = 1; /* Packet length is 16 bits */
        } else {
            packetlength = 2; /* Packet length is 32 bits */
        }
        /* Get I2S source Clock frequency */
        /**
         * If an external I2S clock has to be used, this define should
         * be set inproject configuration or instm32f4xx_conf.h file 
         */
#ifdef I2S_EXTERNAL_CLOCK_VAL
        /* Set external clock as I2S clock source */
        if ((RCC->CFGR & RCC_CFGR_I2SSRC) == 0) {
            RCC->CFGR |= (uint32_t) RCC_CFGR_I2SSRC;
        }
        /* SetI2S clock toexternal clock  value */
        i2sclk = I2S_EXTERNAL_CLOCK_VAL;
#else
        /* Set PLLI2S as I2S clock source */
        if ((RCC->CFGR & RCC_CFGR_I2SSRC) != 0) {
            RCC->CFGR &= ~(uint32_t) RCC_CFGR_I2SSRC;
        }
        /* GetPLLI2SN value */
        plln = (uint32_t) (
            ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6) &
            (RCC_PLLI2SCFGR_PLLI2SN >> 6)
        );
        /* GetPLLI2SR value */
        pllr = (uint32_t) (
            ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28) &
            (RCC_PLLI2SCFGR_PLLI2SR >> 28)
        );
        /* GetPLLM value */
        pllm = (uint32_t) (RCC->PLLCFGR & RCC_PLLCFGR_PLLM);
        /* GetI2S source clock value */
        i2sclk = (uint32_t) (((HSE_VALUE / pllm) * plln) / pllr);
#endif
        /**
         * ComputeReal divider depending onMCLK output state,
         * with a floating point 
         */
        if (I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable) {
            /* MCLK output is enabled */
            tmp = (uint16_t) (
                ((((i2sclk / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5
            );
        } else {
            /* MCLK output is disabled */
            tmp = (uint16_t) (
                (
                    (
                        ((i2sclk / (32 * packetlength)) *10 ) /
                        I2S_InitStruct->I2S_AudioFreq
                    )
                ) +
                5
            );
        }
        /* Removeflatting point */
        tmp = tmp / 10;
        /* Checkparity ofdivider */
        i2sodd = (uint16_t) (tmp & (uint16_t) 0x0001);
        /* Computei2sdiv prescaler */
        i2sdiv = (uint16_t) ((tmp - i2sodd) / 2);
        /* GetMask forOdd bit (SPI_I2SPR[8]) register */
        i2sodd = (uint16_t) (i2sodd << 8);
    }
    /* Test ifdivider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2) || (i2sdiv > 0xFF)) {
        /* Setdefault values */
        i2sdiv = 2;
        i2sodd = 0;
    }
    /* Write to SPIx I2SPR registercomputed value */
    SPIx->I2SPR = (uint16_t) (
        (uint16_t) i2sdiv | (uint16_t) (
            i2sodd | (uint16_t) I2S_InitStruct->I2S_MCLKOutput
        )
    );
    /* ConfigureI2S withSPI_InitStruct values */
    tmpreg |= (uint16_t) (
        (uint16_t) SPI_I2SCFGR_I2SMOD | (uint16_t) (
            I2S_InitStruct->I2S_Mode |
            (uint16_t) (
                I2S_InitStruct->I2S_Standard |
                (uint16_t) (
                    I2S_InitStruct->I2S_DataFormat |
                    (uint16_t) I2S_InitStruct->I2S_CPOL
                )
            )
        )
    );
    SPIx->I2SCFGR = tmpreg; /* Write to SPIx I2SCFGR */
}

/**
 * Fills each SPI_InitStruct member with its default value.
 * param SPI_InitStruct: pointer to a SPI_InitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct) {
    /* Reset SPI init structure parameters values */
    /* InitializeSPI_Direction member */
    SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    /* initializeSPI_Mode member */
    SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
    /* initializeSPI_DataSize member */
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    /* InitializeSPI_CPOL member */
    SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
    /* InitializeSPI_CPHA member */
    SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
    /* InitializeSPI_NSS member */
    SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
    /* InitializeSPI_BaudRatePrescaler member */
    SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    /* InitializeSPI_FirstBit member */
    SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
    /* InitializeSPI_CRCPolynomial member */
    SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
 * Fills each I2S_InitStruct member with its default value.
 * param I2S_InitStruct: pointer to a I2S_InitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct) {
    /* Reset I2S init structure parameters values */
    /* InitializeI2S_Mode member */
    I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;
    /* InitializeI2S_Standard member */
    I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;
    /* InitializeI2S_DataFormat member */
    I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;
    /* InitializeI2S_MCLKOutput member */
    I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    /* InitializeI2S_AudioFreq member */
    I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;
    /* InitializeI2S_CPOL member */
    I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
 * Enables or disablesspecified SPI peripheral.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param NewState: new state ofSPIx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        SPIx->CR1 |= SPI_CR1_SPE; /* Enableselected SPI peripheral */
    } else {
        /* Disableselected SPI peripheral */
        SPIx->CR1 &= (uint16_t) ~((uint16_t)SPI_CR1_SPE);
    }
}

/**
 * Enables or disablesspecified SPI peripheral (in I2S mode).
 * param SPIx: where x can be 2 or 3 to selectSPI peripheral
 *       (or I2Sxext for full duplex mode).
 * param NewState: new state ofSPIx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    assert_param(IS_SPI_23_PERIPH_EXT(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enableselected SPI peripheral (in I2S mode) */
        SPIx->I2SCFGR |= SPI_I2SCFGR_I2SE;
    } else {
        /* Disableselected SPI peripheral in I2S mode */
        SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SE);
    }
}

/**
 * Configuresdata size forselected SPI.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param SPI_DataSize: specifiesSPI data size.
 *   This parameter can be one offollowing values:
 *      arg SPI_DataSize_16b: Set data frame format to 16bit
 *      arg SPI_DataSize_8b: Set data frame format to 8bit
 * retval None
 */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DATASIZE(SPI_DataSize));
    SPIx->CR1 &= (uint16_t) ~SPI_DataSize_16b; /* Clear DFF bit */
    SPIx->CR1 |= SPI_DataSize; /* Set new DFF bit value */
}

/**
 * Selectsdata transfer direction in bidirectional mode forspecified SPI.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param SPI_Direction: specifiesdata transfer direction in bidirectional mode.
 *   This parameter can be one offollowing values:
 *      arg SPI_Direction_Tx: Selects Tx transmission direction
 *      arg SPI_Direction_Rx: Selects Rx receive direction
 * retval None
 */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DIRECTION(SPI_Direction));
    if (SPI_Direction == SPI_Direction_Tx) {
        SPIx->CR1 |= SPI_Direction_Tx; /* SetTx only mode */
    } else {
        SPIx->CR1 &= SPI_Direction_Rx; /* SetRx only mode */
    }
}

/**
 * Configures internally by softwareNSS pin forselected SPI.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param SPI_NSSInternalSoft: specifiesSPI NSS internal state.
 *          This parameter can be one offollowing values:
 *      arg SPI_NSSInternalSoft_Set: Set NSS pin internally
 *      arg SPI_NSSInternalSoft_Reset: Reset NSS pin internally
 * retval None
 */
void SPI_NSSInternalSoftwareConfig(
    SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft
) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));
    if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset) {
        /* Set NSS pin internally by software */
        SPIx->CR1 |= SPI_NSSInternalSoft_Set;
    } else {
        /* Reset NSS pin internally by software */
        SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
    }
}

/**
 * Enables or disablesSS output forselected SPI.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param NewState: new state ofSPIx SS output.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enableselected SPI SS output */
        SPIx->CR2 |= (uint16_t) SPI_CR2_SSOE;
    } else {
        /* Disableselected SPI SS output */
        SPIx->CR2 &= (uint16_t) ~((uint16_t) SPI_CR2_SSOE);
    }
}

/**
 * Enables or disablesSPIx/I2Sx DMA interface.
 * This function can be called only afterSPI_Init() function has
 * been called.
 * When TI mode is selected,control bits SSM, SSI, CPOL and CPHA 
 * are not taken into consideration and are configured by hardware
 * respectively toTI mode requirements.
 * param SPIx: where x can be 1, 2 or 3 
 * param NewState: new state ofselected SPI TI communication mode.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* EnableTI mode forselected SPI peripheral */
        SPIx->CR2 |= SPI_CR2_FRF;
    } else {
        /* DisableTI mode forselected SPI peripheral */
        SPIx->CR2 &= (uint16_t) ~SPI_CR2_FRF;
    }
}

/**
 * Configuresfull duplex mode forI2Sx peripheral using its
 * extension I2Sxext according tospecified parameters in
 * I2S_InitStruct.
 * param I2Sxext: x can be 2 or 3 to selectI2S peripheral extension block.
 * param I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
 *       containsconfiguration information forspecified I2S peripheral
 *        extension.
 * The structure pointed by I2S_InitStruct parameter should besame
 * used formaster I2S peripheral. In this case, ifmaster is 
 * configured as transmitter,slave will be receiver and vice versa.
 * Or you can force a different mode by modifyingfield I2S_Mode to the
 * value I2S_SlaveRx or I2S_SlaveTx indepedently ofmaster configuration.
 * The I2S full duplex extension can be configured in slave mode only.
 * retval None
 */
void I2S_FullDuplexConfig(
    SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct
) {
    uint16_t tmpreg = 0, tmp = 0;

    assert_param(IS_I2S_EXT_PERIPH(I2Sxext));
    assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
    assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
    assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
    assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));
    /* SPIx I2SCFGR & I2SPR Configuration */
    /**
     * Clear:
     * I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits 
     */
    I2Sxext->I2SCFGR &= I2SCFGR_CLEAR_MASK; 
    I2Sxext->I2SPR = 0x0002;
    tmpreg = I2Sxext->I2SCFGR; /* GetI2SCFGR register value */
    /* Getmode to be configured forextended I2S */
    if (
        (I2S_InitStruct->I2S_Mode == I2S_Mode_MasterTx) ||
        (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveTx)
    ) {
        tmp = I2S_Mode_SlaveRx;
    } else {
        if (
            (I2S_InitStruct->I2S_Mode == I2S_Mode_MasterRx) ||
            (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveRx)
        ) {
            tmp = I2S_Mode_SlaveTx;
        }
    }
    /* ConfigureI2S withSPI_InitStruct values */
    tmpreg |= (uint16_t) (
        (uint16_t) SPI_I2SCFGR_I2SMOD | (uint16_t) (
            tmp | (uint16_t) (
                I2S_InitStruct->I2S_Standard | (uint16_t) (
                    I2S_InitStruct->I2S_DataFormat |
                    (uint16_t) I2S_InitStruct->I2S_CPOL
                )
            )
        )
    );
    I2Sxext->I2SCFGR = tmpreg; /* Write to SPIx I2SCFGR */
}

/**
 * Returnsmost recent received data bySPIx/I2Sx peripheral.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * retval The value ofreceived data.
 */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx) {
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    return SPIx->DR; /* Returndata inDR register */
}

/**
 * Transmits a Data throughSPIx/I2Sx peripheral.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param Data: Data to be transmitted.
 * retval None
 */
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data) {
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    SPIx->DR = Data; /* Write inDR registerdata to be sent */
}

/**
 * Enables or disablesCRC value calculation oftransferred bytes.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param NewState: new state ofSPIx CRC value calculation.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        SPIx->CR1 |= SPI_CR1_CRCEN; /* Enableselected SPI CRC calculation */
    } else {
        /* Disableselected SPI CRC calculation */
        SPIx->CR1 &= (uint16_t) ~((uint16_t) SPI_CR1_CRCEN);
    }
}

/**
 * TransmitSPIx CRC value.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * retval None
 */
void SPI_TransmitCRC(SPI_TypeDef* SPIx) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    SPIx->CR1 |= SPI_CR1_CRCNEXT; /* Enableselected SPI CRC transmission */
}

/**
 * Returnstransmit orreceive CRC register value forspecified SPI.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * param SPI_CRC: specifiesCRC register to be read.
 *   This parameter can be one offollowing values:
 *      arg SPI_CRC_Tx: Selects Tx CRC register
 *      arg SPI_CRC_Rx: Selects Rx CRC register
 * retval The selected CRC register value
 */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC) {
    uint16_t crcreg = 0;

    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_CRC(SPI_CRC));
    if (SPI_CRC != SPI_CRC_Rx) {
        crcreg = SPIx->TXCRCR; /* GetTx CRC register */
    } else {
        crcreg = SPIx->RXCRCR; /* GetRx CRC register */
    }
    return crcreg; /* Returnselected CRC register */
}

/**
 * ReturnsCRC Polynomial register value forspecified SPI.
 * param SPIx: where x can be 1, 2 or 3 to selectSPI peripheral.
 * retval The CRC Polynomial register value.
 */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    return SPIx->CRCPR; /* ReturnCRC polynomial register */
}

/**
 * Enables or disablesSPIx/I2Sx DMA interface.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param SPI_I2S_DMAReq: specifiesSPI DMA transfer request
 *       to be enabled/disabled.
 *   This parameter can be any combination offollowing values:
 *      arg SPI_I2S_DMAReq_Tx: Tx buffer DMA transfer request
 *      arg SPI_I2S_DMAReq_Rx: Rx buffer DMA transfer request
 * param NewState: new state ofselected SPI DMA transfer request.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void SPI_I2S_DMACmd(
    SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState
) {
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));
    if (NewState != DISABLE) {
        /* Enableselected SPI DMA requests */
        SPIx->CR2 |= SPI_I2S_DMAReq;
    } else {
        /* Disableselected SPI DMA requests */
        SPIx->CR2 &= (uint16_t) ~SPI_I2S_DMAReq;
    }
}

/**
 * Enables or disablesspecified SPI/I2S interrupts.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param SPI_I2S_IT: specifiesSPI interrupt source to be enabled or disabled.
 *   This parameter can be one offollowing values:
 *      arg SPI_I2S_IT_TXE: Tx buffer empty interrupt mask
 *      arg SPI_I2S_IT_RXNE: Rx buffer not empty interrupt mask
 *      arg SPI_I2S_IT_ERR: Error interrupt mask
 * param NewState: new state ofspecified SPI interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void SPI_I2S_ITConfig(
    SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState
) {
    uint16_t itpos = 0, itmask = 0 ;

    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));
    itpos = SPI_I2S_IT >> 4; /* GetSPI IT index */
    itmask = (uint16_t)1 << (uint16_t) itpos; /* SetIT mask */
    if (NewState != DISABLE) {
        SPIx->CR2 |= itmask; /* Enableselected SPI interrupt */
    } else {
        SPIx->CR2 &= (uint16_t) ~itmask; /* Disableselected SPI interrupt */
    }
}

/**
 * Checks whetherspecified SPIx/I2Sx flag is set or not.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param SPI_I2S_FLAG: specifiesSPI flag to check.
 *   This parameter can be one offollowing values:
 *      arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
 *      arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
 *      arg SPI_I2S_FLAG_BSY: Busy flag.
 *      arg SPI_I2S_FLAG_OVR: Overrun flag.
 *      arg SPI_FLAG_MODF: Mode Fault flag.
 *      arg SPI_FLAG_CRCERR: CRC Error flag.
 *      arg SPI_I2S_FLAG_TIFRFE: Format Error.
 *      arg I2S_FLAG_UDR: Underrun Error flag.
 *      arg I2S_FLAG_CHSIDE: Channel Side flag.
 * retval The new state of SPI_I2S_FLAG (SET or RESET).
 */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));
    /* Checkstatus ofspecified SPI flag */
    if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t) RESET) {
        bitstatus = SET; /* SPI_I2S_FLAG is set */
    } else {
        bitstatus = RESET; /* SPI_I2S_FLAG is reset */
    }
    return bitstatus; /* ReturnSPI_I2S_FLAG status */
}

/**
 * ClearsSPIx CRC Error (CRCERR) flag.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param SPI_I2S_FLAG: specifiesSPI flag to clear.
 *   This function clears only CRCERR flag.
 *      arg SPI_FLAG_CRCERR: CRC Error flag.
 * OVR (OverRun error) flag is cleared by software sequence: a read 
 * operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by a read
 * operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
 * UDR (UnderRun error) flag is cleared by a read operation to
 * SPI_SR register (SPI_I2S_GetFlagStatus()).
 * MODF (Mode Fault) flag is cleared by software sequence: a read/write
 * operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by a
 * write operation to SPI_CR1 register (SPI_Cmd() to enableSPI).
 *  
 * retval None
 */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG) {
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));
    /* Clearselected SPI CRC Error (CRCERR) flag */
    SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
 * Checks whetherspecified SPIx/I2Sx interrupt has occurred or not.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param SPI_I2S_IT: specifiesSPI interrupt source to check.
 *   This parameter can be one offollowing values:
 *      arg SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
 *      arg SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
 *      arg SPI_I2S_IT_OVR: Overrun interrupt.
 *      arg SPI_IT_MODF: Mode Fault interrupt.
 *      arg SPI_IT_CRCERR: CRC Error interrupt.
 *      arg I2S_IT_UDR: Underrun interrupt.
 *      arg SPI_I2S_IT_TIFRFE: Format Error interrupt.
 * retval The new state of SPI_I2S_IT (SET or RESET).
 */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT) {
    ITStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));
    itpos = 0x01 << (SPI_I2S_IT & 0x0F); /* GetSPI_I2S_IT index */
    itmask = SPI_I2S_IT >> 4; /* GetSPI_I2S_IT IT mask */
    itmask = 0x01 << itmask; /* SetIT mask */
    /* GetSPI_I2S_IT enable bit status */
    enablestatus = (SPIx->CR2 & itmask) ;
    /* Checkstatus ofspecified SPI interrupt */
    if (((SPIx->SR & itpos) != (uint16_t) RESET) && enablestatus) {
        bitstatus = SET; /* SPI_I2S_IT is set */
    } else {
        bitstatus = RESET; /* SPI_I2S_IT is reset */
    }
    return bitstatus; /* ReturnSPI_I2S_IT status */
}

/**
 * ClearsSPIx CRC Error (CRCERR) interrupt pending bit.
 * param SPIx: To selectSPIx/I2Sx peripheral, where x can be: 1, 2 or 3 
 *       in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
 * param SPI_I2S_IT: specifiesSPI interrupt pending bit to clear.
 *   This function clears only CRCERR interrupt pending bit.
 *       arg SPI_IT_CRCERR: CRC Error interrupt.
 * OVR (OverRun Error) interrupt pending bit is cleared by software 
 * sequence: a read operation to SPI_DR register (SPI_I2S_ReceiveData()) 
 * followed by a read operation to SPI_SR register (SPI_I2S_GetITStatus()).
 * UDR (UnderRun Error) interrupt pending bit is cleared by a read 
 * operation to SPI_SR register (SPI_I2S_GetITStatus()).
 * MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
 * a read/write operation to SPI_SR register (SPI_I2S_GetITStatus()) 
 * followed by a write operation to SPI_CR1 register (SPI_Cmd() to enable 
 * SPI).
 * retval None
 */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT) {
    uint16_t itpos = 0;

    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_CLEAR_IT(SPI_I2S_IT));
    itpos = 0x01 << (SPI_I2S_IT & 0x0F); /* GetSPI_I2S IT index */
    /* Clearselected SPI CRC Error (CRCERR) interrupt pending bit */
    SPIx->SR = (uint16_t) ~itpos;
}

