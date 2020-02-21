/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_adc.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Analog to Digital Convertor (ADC) peripheral:
 *     - Initialization and Configuration (in addition to ADC multi mode
 *       selection)
 *     - Analog Watchdog configuration
 *     - Temperature Sensor & Vrefint (Voltage Reference internal) & VBAT
 *       management
 *     - Regular Channels Configuration
 *     - Regular Channels DMA Configuration
 *     - Injected channels Configuration
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_adc is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_adc is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* ADC DISCNUM mask */
#define CR1_DISCNUM_RESET ((uint32_t) 0xFFFF1FFF)

/* ADC AWDCH mask */
#define CR1_AWDCH_RESET ((uint32_t) 0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CR1_AWDMode_RESET ((uint32_t) 0xFF3FFDFF)

/* CR1 register Mask */
#define CR1_CLEAR_MASK ((uint32_t) 0xFCFFFEFF)

/* ADC EXTEN mask */
#define CR2_EXTEN_RESET ((uint32_t) 0xCFFFFFFF)

/* ADC JEXTEN mask */
#define CR2_JEXTEN_RESET ((uint32_t) 0xFFCFFFFF)

/* ADC JEXTSEL mask */
#define CR2_JEXTSEL_RESET ((uint32_t) 0xFFF0FFFF)

/* CR2 register Mask */
#define CR2_CLEAR_MASK ((uint32_t) 0xC0FFF7FD)

/* ADC SQx mask */
#define SQR3_SQ_SET ((uint32_t) 0x0000001F)
#define SQR2_SQ_SET ((uint32_t) 0x0000001F)
#define SQR1_SQ_SET ((uint32_t) 0x0000001F)

/* ADC L Mask */
#define SQR1_L_RESET ((uint32_t) 0xFF0FFFFF)

/* ADC JSQx mask */
#define JSQR_JSQ_SET ((uint32_t) 0x0000001F)

/* ADC JL mask */
#define JSQR_JL_SET ((uint32_t) 0x00300000)
#define JSQR_JL_RESET ((uint32_t) 0xFFCFFFFF)

/* ADC SMPx mask */
#define SMPR1_SMP_SET ((uint32_t) 0x00000007)
#define SMPR2_SMP_SET ((uint32_t) 0x00000007)

/* ADC JDRx registers offset */
#define JDR_OFFSET ((uint8_t) 0x28)

/* ADC CDR register base address */
#define CDR_ADDRESS ((uint32_t) 0x40012308)

/* ADC CCR register Mask */
#define CR_CLEAR_MASK ((uint32_t) 0xFFFC30E0)

/**
 * Deinitializes all ADCs peripherals registers to their default reset values.
 * param None
 * retval None
 */
void ADC_DeInit(void) {
    /* Enable all ADCs reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, ENABLE);
    /* Release all ADCs from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, DISABLE);
}

/**
 * Initializes ADCx peripheral according to specified parameters
 * in ADC_InitStruct.
 * This function is used to configure global features of ADC
 * (Resolution and Data Alignment), however, rest of configuration
 * parameters are specific to regular channels group (scan mode
 * activation, continuous mode activation, External trigger source and
 * edge, number of conversion in regular channels group sequencer).
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_InitStruct: pointer to an ADC_InitTypeDef structure that
 *       contains configuration information for specified ADC peripheral.
 * retval None
 */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct) {
    uint32_t tmpreg1 = 0;
    uint8_t tmpreg2 = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
    assert_param(
        IS_ADC_EXT_TRIG_EDGE(ADC_InitStruct->ADC_ExternalTrigConvEdge)
    );
    assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
    assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfConversion));
    tmpreg1 = ADCx->CR1; /* Get ADCx CR1 value */
    tmpreg1 &= CR1_CLEAR_MASK; /* Clear RES and SCAN bits */
    /* Configure ADCx: scan conversion mode and resolution */
    /* Set SCAN bit according to ADC_ScanConvMode value */
    /* Set RES bit according to ADC_Resolution value */ 
    tmpreg1 |= (uint32_t) (
        ((uint32_t) ADC_InitStruct->ADC_ScanConvMode << 8) |
        ADC_InitStruct->ADC_Resolution
    );
    ADCx->CR1 = tmpreg1; /* Write to ADCx CR1 */
    tmpreg1 = ADCx->CR2; /* Get ADCx CR2 value */
    tmpreg1 &= CR2_CLEAR_MASK; /* Clear CONT, ALIGN, EXTEN and EXTSEL bits */
    /**
     * Configure ADCx: external trigger event and edge, data alignment
     * and continuous conversion mode
     */
    /* Set ALIGN bit according to ADC_DataAlign value */
    /* Set EXTEN bits according to ADC_ExternalTrigConvEdge value */ 
    /* Set EXTSEL bits according to ADC_ExternalTrigConv value */
    /* Set CONT bit according to ADC_ContinuousConvMode value */
    tmpreg1 |= (uint32_t) (
        ADC_InitStruct->ADC_DataAlign |
        ADC_InitStruct->ADC_ExternalTrigConv |
        ADC_InitStruct->ADC_ExternalTrigConvEdge |
        ((uint32_t) ADC_InitStruct->ADC_ContinuousConvMode << 1)
    );
    ADCx->CR2 = tmpreg1; /* Write to ADCx CR2 */
    tmpreg1 = ADCx->SQR1; /* Get ADCx SQR1 value */
    tmpreg1 &= SQR1_L_RESET; /* Clear L bits */
    /* Configure ADCx: regular channel sequence length */
    /* Set L bits according to ADC_NbrOfConversion value */
    tmpreg2 |= (uint8_t) (ADC_InitStruct->ADC_NbrOfConversion - (uint8_t) 1);
    tmpreg1 |= ((uint32_t) tmpreg2 << 20);
    ADCx->SQR1 = tmpreg1; /* Write to ADCx SQR1 */
}

/**
 * Fills each ADC_InitStruct member with its default value.
 * This function is used to initialize global features of ADC
 * (Resolution and Data Alignment), however, rest of configuration
 * parameters are specific to regular channels group (scan mode
 * activation, continuous mode activation, External trigger source and
 * edge, number of conversion in regular channels group sequencer).
 * param ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will
 *       be initialized.
 * retval None
 */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct) {
    /* Initialize ADC_Mode member */
    ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;
    /* initialize ADC_ScanConvMode member */
    ADC_InitStruct->ADC_ScanConvMode = DISABLE;
    /* Initialize ADC_ContinuousConvMode member */
    ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;
    /* Initialize ADC_ExternalTrigConvEdge member */
    ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    /* Initialize ADC_ExternalTrigConv member */
    ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    /* Initialize ADC_DataAlign member */
    ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
    /* Initialize ADC_NbrOfConversion member */
    ADC_InitStruct->ADC_NbrOfConversion = 1;
}

/**
 * Initializes ADCs peripherals according to specified parameters 
 * in ADC_CommonInitStruct.
 * param ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure 
 *       that contains configuration information for  All ADCs peripherals.
 * retval None
 */
void ADC_CommonInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct) {
    uint32_t tmpreg1 = 0;

    assert_param(IS_ADC_MODE(ADC_CommonInitStruct->ADC_Mode));
    assert_param(IS_ADC_PRESCALER(ADC_CommonInitStruct->ADC_Prescaler));
    assert_param(
        IS_ADC_DMA_ACCESS_MODE(ADC_CommonInitStruct->ADC_DMAAccessMode)
    );
    assert_param(
        IS_ADC_SAMPLING_DELAY(ADC_CommonInitStruct->ADC_TwoSamplingDelay)
    );
    tmpreg1 = ADC->CCR; /* Get ADC CCR value */
    tmpreg1 &= CR_CLEAR_MASK; /* Clear MULTI, DELAY, DMA and ADCPRE bits */
    /**
     * Configure ADCx: Multi mode, Delay between two sampling time,
     * ADC prescaler, and DMA access mode for multimode */
    /* Set MULTI bits according to ADC_Mode value */
    /* Set ADCPRE bits according to ADC_Prescaler value */
    /* Set DMA bits according to ADC_DMAAccessMode value */
    /* Set DELAY bits according to ADC_TwoSamplingDelay value */
    tmpreg1 |= (uint32_t) (
        ADC_CommonInitStruct->ADC_Mode |
        ADC_CommonInitStruct->ADC_Prescaler |
        ADC_CommonInitStruct->ADC_DMAAccessMode |
        ADC_CommonInitStruct->ADC_TwoSamplingDelay
    );
    ADC->CCR = tmpreg1; /* Write to ADC CCR */
}

/**
 * Fills each ADC_CommonInitStruct member with its default value.
 * param ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct) {
    /* Initialize ADC_Mode member */
    ADC_CommonInitStruct->ADC_Mode = ADC_Mode_Independent;
    /* initialize ADC_Prescaler member */
    ADC_CommonInitStruct->ADC_Prescaler = ADC_Prescaler_Div2;
    /* Initialize ADC_DMAAccessMode member */
    ADC_CommonInitStruct->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    /* Initialize ADC_TwoSamplingDelay member */
    ADC_CommonInitStruct->ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
}

/**
 * Enables or disables specified ADC peripheral.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of ADCx peripheral. 
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Set ADON bit to wake up ADC from power down mode */
        ADCx->CR2 |= (uint32_t) ADC_CR2_ADON;
    } else {
        /* Disable selected ADC peripheral */
        ADCx->CR2 &= (uint32_t) (~ADC_CR2_ADON);
    }
}

/**
 * Enables or disables analog watchdog on single/all
 * regular or injected channels
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_AnalogWatchdog: ADC analog watchdog configuration.
 *   This parameter can be one of following values:
 *        arg ADC_AnalogWatchdog_SingleRegEnable: Analog watchdog on a
 *            single regular channel
 *        arg ADC_AnalogWatchdog_SingleInjecEnable: Analog watchdog on
 *            a single injected channel
 *        arg ADC_AnalogWatchdog_SingleRegOrInjecEnable: Analog
 *            watchdog on a single regular or injected channel
 *        arg ADC_AnalogWatchdog_AllRegEnable: Analog watchdog
 *            on all regular channel
 *        arg ADC_AnalogWatchdog_AllInjecEnable: Analog watchdog
 *            on all injected channel
 *        arg ADC_AnalogWatchdog_AllRegAllInjecEnable: Analog watchdog
 *            on all regular and injected channels
 *        arg ADC_AnalogWatchdog_None: No channel guarded by analog watchdog
 * retval None
 */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog) {
    uint32_t tmpreg = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));
    tmpreg = ADCx->CR1; /* Get old register value */
    tmpreg &= CR1_AWDMode_RESET; /* Clear AWDEN, JAWDEN and AWDSGL bits */
    tmpreg |= ADC_AnalogWatchdog; /* Set analog watchdog enable mode */
    ADCx->CR1 = tmpreg; /* Store new register value */
}

/**
 * Configures high and low thresholds of analog watchdog.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param HighThreshold: ADC analog watchdog High threshold value.
 *    This parameter must be a 12-bit value.
 * param LowThreshold:  ADC analog watchdog Low threshold value.
 *    This parameter must be a 12-bit value.
 * retval None
 */
void ADC_AnalogWatchdogThresholdsConfig(
    ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold
) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_THRESHOLD(HighThreshold));
    assert_param(IS_ADC_THRESHOLD(LowThreshold));
    ADCx->HTR = HighThreshold; /* Set ADCx high threshold */
    ADCx->LTR = LowThreshold; /* Set ADCx low threshold */
}

/**
 * Configures analog watchdog guarded single channel
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_Channel: ADC channel to configure for analog watchdog.
 *    This parameter can be one of following values:
 *        arg ADC_Channel_0: ADC Channel0 selected
 *        arg ADC_Channel_1: ADC Channel1 selected
 *        arg ADC_Channel_2: ADC Channel2 selected
 *        arg ADC_Channel_3: ADC Channel3 selected
 *        arg ADC_Channel_4: ADC Channel4 selected
 *        arg ADC_Channel_5: ADC Channel5 selected
 *        arg ADC_Channel_6: ADC Channel6 selected
 *        arg ADC_Channel_7: ADC Channel7 selected
 *        arg ADC_Channel_8: ADC Channel8 selected
 *        arg ADC_Channel_9: ADC Channel9 selected
 *        arg ADC_Channel_10: ADC Channel10 selected
 *        arg ADC_Channel_11: ADC Channel11 selected
 *        arg ADC_Channel_12: ADC Channel12 selected
 *        arg ADC_Channel_13: ADC Channel13 selected
 *        arg ADC_Channel_14: ADC Channel14 selected
 *        arg ADC_Channel_15: ADC Channel15 selected
 *        arg ADC_Channel_16: ADC Channel16 selected
 *        arg ADC_Channel_17: ADC Channel17 selected
 *        arg ADC_Channel_18: ADC Channel18 selected
 * retval None
 */
void ADC_AnalogWatchdogSingleChannelConfig(
    ADC_TypeDef* ADCx, uint8_t ADC_Channel
) {
    uint32_t tmpreg = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    tmpreg = ADCx->CR1; /* Get old register value */
    /* Clear Analog watchdog channel select bits */
    tmpreg &= CR1_AWDCH_RESET;
    tmpreg |= ADC_Channel; /* Set Analog watchdog channel */
    ADCx->CR1 = tmpreg; /* Store new register value */
}

/**
 * Enables or disables temperature sensor and Vrefint channels.
 * param NewState: new state of temperature sensor and Vrefint channels.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_TempSensorVrefintCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable temperature sensor and Vrefint channel*/
        ADC->CCR |= (uint32_t) ADC_CCR_TSVREFE;
    } else {
        /* Disable temperature sensor and Vrefint channel*/
        ADC->CCR &= (uint32_t) (~ADC_CCR_TSVREFE);
    }
}

/**
 * Enables or disables VBAT (Voltage Battery) channel.
 * param NewState: new state of VBAT channel.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_VBATCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        ADC->CCR |= (uint32_t) ADC_CCR_VBATE; /* Enable VBAT channel*/
    } else {
        ADC->CCR &= (uint32_t) (~ADC_CCR_VBATE); /* Disable VBAT channel*/
    }
}

/**
 * Configures for selected ADC regular channel its corresponding
 *         rank in sequencer and its sample time.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_Channel: ADC channel to configure. 
 *    This parameter can be one of following values:
 *        arg ADC_Channel_0: ADC Channel0 selected
 *        arg ADC_Channel_1: ADC Channel1 selected
 *        arg ADC_Channel_2: ADC Channel2 selected
 *        arg ADC_Channel_3: ADC Channel3 selected
 *        arg ADC_Channel_4: ADC Channel4 selected
 *        arg ADC_Channel_5: ADC Channel5 selected
 *        arg ADC_Channel_6: ADC Channel6 selected
 *        arg ADC_Channel_7: ADC Channel7 selected
 *        arg ADC_Channel_8: ADC Channel8 selected
 *        arg ADC_Channel_9: ADC Channel9 selected
 *        arg ADC_Channel_10: ADC Channel10 selected
 *        arg ADC_Channel_11: ADC Channel11 selected
 *        arg ADC_Channel_12: ADC Channel12 selected
 *        arg ADC_Channel_13: ADC Channel13 selected
 *        arg ADC_Channel_14: ADC Channel14 selected
 *        arg ADC_Channel_15: ADC Channel15 selected
 *        arg ADC_Channel_16: ADC Channel16 selected
 *        arg ADC_Channel_17: ADC Channel17 selected
 *        arg ADC_Channel_18: ADC Channel18 selected
 * param Rank: The rank in regular group sequencer.
 *    This parameter must be between 1 to 16.
 * param ADC_SampleTime: The sample time value to be set for selected channel.
 *    This parameter can be one of following values:
 *        arg ADC_SampleTime_3Cycles: Sample time equal to 3 cycles
 *        arg ADC_SampleTime_15Cycles: Sample time equal to 15 cycles
 *        arg ADC_SampleTime_28Cycles: Sample time equal to 28 cycles
 *        arg ADC_SampleTime_56Cycles: Sample time equal to 56 cycles
 *        arg ADC_SampleTime_84Cycles: Sample time equal to 84 cycles
 *        arg ADC_SampleTime_112Cycles: Sample time equal to 112 cycles	
 *        arg ADC_SampleTime_144Cycles: Sample time equal to 144 cycles	
 *        arg ADC_SampleTime_480Cycles: Sample time equal to 480 cycles	
 * retval None
 */
void ADC_RegularChannelConfig(
    ADC_TypeDef* ADCx, uint8_t ADC_Channel,
    uint8_t Rank, uint8_t ADC_SampleTime
) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    assert_param(IS_ADC_REGULAR_RANK(Rank));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
    /* if ADC_Channel_10 ... ADC_Channel_18 is selected */
    if (ADC_Channel > ADC_Channel_9) {
        tmpreg1 = ADCx->SMPR1; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SMPR1_SMP_SET << (3 * (ADC_Channel - 10));
        tmpreg1 &= ~tmpreg2; /* Clear old sample time */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_SampleTime << (3 * (ADC_Channel - 10));
        tmpreg1 |= tmpreg2; /* Set new sample time */
        ADCx->SMPR1 = tmpreg1; /* Store new register value */
    } else {
        tmpreg1 = ADCx->SMPR2; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SMPR2_SMP_SET << (3 * ADC_Channel);
        tmpreg1 &= ~tmpreg2; /* Clear old sample time */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_SampleTime << (3 * ADC_Channel);
        tmpreg1 |= tmpreg2; /* Set new sample time */
        ADCx->SMPR2 = tmpreg1; /* Store new register value */
    }
    /* For Rank 1 to 6 */
    if (Rank < 7) {
        tmpreg1 = ADCx->SQR3; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SQR3_SQ_SET << (5 * (Rank - 1));
        tmpreg1 &= ~tmpreg2; /* Clear old SQx bits for selected rank */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_Channel << (5 * (Rank - 1));
        tmpreg1 |= tmpreg2; /* Set SQx bits for selected rank */
        ADCx->SQR3 = tmpreg1; /* Store new register value */
    } else if (Rank < 13) {
        tmpreg1 = ADCx->SQR2; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SQR2_SQ_SET << (5 * (Rank - 7));
        tmpreg1 &= ~tmpreg2; /* Clear old SQx bits for selected rank */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_Channel << (5 * (Rank - 7));
        tmpreg1 |= tmpreg2; /* Set SQx bits for selected rank */
        ADCx->SQR2 = tmpreg1; /* Store new register value */
    } else {
        tmpreg1 = ADCx->SQR1; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SQR1_SQ_SET << (5 * (Rank - 13));
        tmpreg1 &= ~tmpreg2; /* Clear old SQx bits for selected rank */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_Channel << (5 * (Rank - 13));
        tmpreg1 |= tmpreg2; /* Set SQx bits for selected rank */
        ADCx->SQR1 = tmpreg1; /* Store new register value */
    }
}

/**
 * Enables selected ADC software start conversion of regular channels.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * retval None
 */
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    /* Enable selected ADC conversion for regular group */
    ADCx->CR2 |= (uint32_t) ADC_CR2_SWSTART;
}

/**
 * Gets selected ADC Software start regular conversion Status.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * retval The new state of ADC software start conversion (SET or RESET).
 */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    /* Check status of SWSTART bit */
    if ((ADCx->CR2 & ADC_CR2_JSWSTART) != (uint32_t) RESET) {
        bitstatus = SET; /* SWSTART bit is set */
    } else {
        bitstatus = RESET; /* SWSTART bit is reset */
    }
    return bitstatus; /* Return SWSTART bit status */
}


/**
 * Enables or disables EOC on each regular channel conversion
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC EOC flag rising
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_EOCOnEachRegularChannelCmd(
    ADC_TypeDef* ADCx, FunctionalState NewState
) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC EOC rising on each regular channel conversion */
        ADCx->CR2 |= (uint32_t) ADC_CR2_EOCS;
    } else {
        /**
         * Disable selected ADC EOC rising on each regular
         * channel conversion
         */
        ADCx->CR2 &= (uint32_t) (~ADC_CR2_EOCS);
    }
}

/**
 * Enables or disables ADC continuous conversion mode 
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC continuous conversion mode
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC continuous conversion mode */
        ADCx->CR2 |= (uint32_t) ADC_CR2_CONT;
    } else {
        /* Disable selected ADC continuous conversion mode */
        ADCx->CR2 &= (uint32_t) (~ADC_CR2_CONT);
    }
}

/**
 * Configures discontinuous mode for selected ADC regular group channel.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param Number: specifies discontinuous mode regular channel count value.
 *    This number must be between 1 and 8.
 * retval None
 */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));
    tmpreg1 = ADCx->CR1; /* Get old register value */
    /* Clear old discontinuous mode channel count */
    tmpreg1 &= CR1_DISCNUM_RESET;
    tmpreg2 = Number - 1; /* Set discontinuous mode channel count */
    tmpreg1 |= tmpreg2 << 13;
    ADCx->CR1 = tmpreg1; /* Store new register value */
}

/**
 * Enables or disables discontinuous mode on regular group channel
 * for specified ADC
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC discontinuous mode on
 *       regular group channel.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC regular discontinuous mode */
        ADCx->CR1 |= (uint32_t) ADC_CR1_DISCEN;
    } else {
        /* Disable selected ADC regular discontinuous mode */
        ADCx->CR1 &= (uint32_t) (~ADC_CR1_DISCEN);
    }
}

/**
 * Returns last ADCx conversion result data for regular channel.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * retval The Data conversion value.
 */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    return (uint16_t) ADCx->DR; /* Return selected ADC conversion value */
}

/**
 * Returns last ADC1, ADC2 and ADC3 regular conversions results
 * data in selected multi mode.
 * param None
 * retval The Data conversion value.
 * In dual mode, value returned by this function is as following
 * Data[15:0]: these bits contain regular data of ADC1.
 * Data[31:16]: these bits contain regular data of ADC2.
 * In triple mode, value returned by this function is as following
 * Data[15:0]: these bits contain alternatively regular data
 * of ADC1, ADC3 and ADC2.
 * Data[31:16]: these bits contain alternatively regular data
 * of ADC2, ADC1 and ADC3.
 */
uint32_t ADC_GetMultiModeConversionValue(void) {
    /* Return multi mode conversion value */
    return (*(__IO uint32_t *) CDR_ADDRESS);
}

 /**
 * Enables or disables specified ADC DMA request.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC DMA transfer.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC DMA request */
        ADCx->CR2 |= (uint32_t) ADC_CR2_DMA;
    } else {
        /* Disable selected ADC DMA request */
        ADCx->CR2 &= (uint32_t) (~ADC_CR2_DMA);
    }
}

/**
 * Enables or disables ADC DMA request after last transfer (Single-ADC mode)
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC DMA request after last transfer.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_DMARequestAfterLastTransferCmd(
    ADC_TypeDef* ADCx, FunctionalState NewState
) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC DMA request after last transfer */
        ADCx->CR2 |= (uint32_t) ADC_CR2_DDS;
    } else {
        /* Disable selected ADC DMA request after last transfer */
        ADCx->CR2 &= (uint32_t) (~ADC_CR2_DDS);
    }
}

/**
 * Enables or disables ADC DMA request after last transfer in multi ADC mode
 * param NewState: new state of selected ADC DMA request after last transfer.
 *    This parameter can be: ENABLE or DISABLE.
 * if Enabled, DMA requests are issued as long as data are converted and
 * DMA mode for multi ADC mode (selected using ADC_CommonInit() function
 * by ADC_CommonInitStruct.ADC_DMAAccessMode structure member) is 
 * ADC_DMAAccessMode_1, ADC_DMAAccessMode_2 or ADC_DMAAccessMode_3.
 * retval None
 */
void ADC_MultiModeDMARequestAfterLastTransferCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC DMA request after last transfer */
        ADC->CCR |= (uint32_t) ADC_CCR_DDS;
    } else {
        /* Disable selected ADC DMA request after last transfer */
        ADC->CCR &= (uint32_t) (~ADC_CCR_DDS);
    }
}

/**
 * Configures for selected ADC injected channel its corresponding
 * rank in sequencer and its sample time.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_Channel: ADC channel to configure. 
 *    This parameter can be one of following values:
 *        arg ADC_Channel_0: ADC Channel0 selected
 *        arg ADC_Channel_1: ADC Channel1 selected
 *        arg ADC_Channel_2: ADC Channel2 selected
 *        arg ADC_Channel_3: ADC Channel3 selected
 *        arg ADC_Channel_4: ADC Channel4 selected
 *        arg ADC_Channel_5: ADC Channel5 selected
 *        arg ADC_Channel_6: ADC Channel6 selected
 *        arg ADC_Channel_7: ADC Channel7 selected
 *        arg ADC_Channel_8: ADC Channel8 selected
 *        arg ADC_Channel_9: ADC Channel9 selected
 *        arg ADC_Channel_10: ADC Channel10 selected
 *        arg ADC_Channel_11: ADC Channel11 selected
 *        arg ADC_Channel_12: ADC Channel12 selected
 *        arg ADC_Channel_13: ADC Channel13 selected
 *        arg ADC_Channel_14: ADC Channel14 selected
 *        arg ADC_Channel_15: ADC Channel15 selected
 *        arg ADC_Channel_16: ADC Channel16 selected
 *        arg ADC_Channel_17: ADC Channel17 selected
 *        arg ADC_Channel_18: ADC Channel18 selected
 * param Rank: The rank in injected group sequencer.
 *    This parameter must be between 1 to 4.
 * param ADC_SampleTime: The sample time value to be set for selected channel.
 *    This parameter can be one of following values:
 *        arg ADC_SampleTime_3Cycles: Sample time equal to 3 cycles
 *        arg ADC_SampleTime_15Cycles: Sample time equal to 15 cycles
 *        arg ADC_SampleTime_28Cycles: Sample time equal to 28 cycles
 *        arg ADC_SampleTime_56Cycles: Sample time equal to 56 cycles
 *        arg ADC_SampleTime_84Cycles: Sample time equal to 84 cycles
 *        arg ADC_SampleTime_112Cycles: Sample time equal to 112 cycles
 *        arg ADC_SampleTime_144Cycles: Sample time equal to 144 cycles
 *        arg ADC_SampleTime_480Cycles: Sample time equal to 480 cycles
 * retval None
 */
void ADC_InjectedChannelConfig(
    ADC_TypeDef* ADCx, uint8_t ADC_Channel,
    uint8_t Rank, uint8_t ADC_SampleTime
) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    assert_param(IS_ADC_INJECTED_RANK(Rank));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
    /* if ADC_Channel_10 ... ADC_Channel_18 is selected */
    if (ADC_Channel > ADC_Channel_9) {
        tmpreg1 = ADCx->SMPR1; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SMPR1_SMP_SET << (3*(ADC_Channel - 10));
        tmpreg1 &= ~tmpreg2; /* Clear old sample time */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_SampleTime << (3*(ADC_Channel - 10));
        tmpreg1 |= tmpreg2; /* Set new sample time */
        ADCx->SMPR1 = tmpreg1; /* Store new register value */
    } else {
        tmpreg1 = ADCx->SMPR2; /* Get old register value */
        /* Calculate mask to clear */
        tmpreg2 = SMPR2_SMP_SET << (3 * ADC_Channel);
        tmpreg1 &= ~tmpreg2; /* Clear old sample time */
        /* Calculate mask to set */
        tmpreg2 = (uint32_t) ADC_SampleTime << (3 * ADC_Channel);
        tmpreg1 |= tmpreg2; /* Set new sample time */
        ADCx->SMPR2 = tmpreg1; /* Store new register value */
    }
    /* Rank configuration */
    tmpreg1 = ADCx->JSQR; /* Get old register value */
    /* Get JL value: Number = JL+1 */
    tmpreg3 = (tmpreg1 & JSQR_JL_SET) >> 20;
    /* Calculate mask to clear: ((Rank-1)+(4-JL-1)) */
    tmpreg2 = JSQR_JSQ_SET << (5 * (uint8_t) ((Rank + 3) - (tmpreg3 + 1)));
    tmpreg1 &= ~tmpreg2; /* Clear old JSQx bits for selected rank */
    /* Calculate mask to set: ((Rank-1)+(4-JL-1)) */
    tmpreg2 = (
        (uint32_t) ADC_Channel << (5 * (uint8_t) ((Rank + 3) - (tmpreg3 + 1)))
    );
    tmpreg1 |= tmpreg2; /* Set JSQx bits for selected rank */
    ADCx->JSQR = tmpreg1; /* Store new register value */
}

/**
 * Configures sequencer length for injected channels
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param Length: The sequencer length. 
 *    This parameter must be a number between 1 to 4.
 * retval None
 */
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_LENGTH(Length));
    tmpreg1 = ADCx->JSQR; /* Get old register value */
    /* Clear old injected sequence length JL bits */
    tmpreg1 &= JSQR_JL_RESET;
    tmpreg2 = Length - 1; /* Set injected sequence length JL bits */
    tmpreg1 |= tmpreg2 << 20;
    ADCx->JSQR = tmpreg1; /* Store new register value */
}

/**
 * Set injected channels conversion value offset
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_InjectedChannel: ADC injected channel to set its offset.
 *    This parameter can be one of following values:
 *        arg ADC_InjectedChannel_1: Injected Channel1 selected
 *        arg ADC_InjectedChannel_2: Injected Channel2 selected
 *        arg ADC_InjectedChannel_3: Injected Channel3 selected
 *        arg ADC_InjectedChannel_4: Injected Channel4 selected
 * param Offset: offset value for selected ADC injected channel
 *    This parameter must be a 12bit value.
 * retval None
 */
void ADC_SetInjectedOffset(
    ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset
) {
    __IO uint32_t tmp = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
    assert_param(IS_ADC_OFFSET(Offset));
    tmp = (uint32_t) ADCx;
    tmp += ADC_InjectedChannel;
    /* Set selected injected channel data offset */
    *(__IO uint32_t *) tmp = (uint32_t) Offset;
}

 /**
 * Configures ADCx external trigger for injected channels conversion.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_ExternalTrigInjecConv: specifies ADC trigger to
 *       start injected conversion.
 *    This parameter can be one of following values:
 *      arg ADC_ExternalTrigInjecConv_T1_CC4: Timer1 capture compare4 selected
 *      arg ADC_ExternalTrigInjecConv_T1_TRGO: Timer1 TRGO event selected
 *      arg ADC_ExternalTrigInjecConv_T2_CC1: Timer2 capture compare1 selected
 *      arg ADC_ExternalTrigInjecConv_T2_TRGO: Timer2 TRGO event selected
 *      arg ADC_ExternalTrigInjecConv_T3_CC2: Timer3 capture compare2 selected
 *      arg ADC_ExternalTrigInjecConv_T3_CC4: Timer3 capture compare4 selected
 *      arg ADC_ExternalTrigInjecConv_T4_CC1: Timer4 capture compare1 selected
 *      arg ADC_ExternalTrigInjecConv_T4_CC2: Timer4 capture compare2 selected
 *      arg ADC_ExternalTrigInjecConv_T4_CC3: Timer4 capture compare3 selected
 *      arg ADC_ExternalTrigInjecConv_T4_TRGO: Timer4 TRGO event selected
 *      arg ADC_ExternalTrigInjecConv_T5_CC4: Timer5 capture compare4 selected
 *      arg ADC_ExternalTrigInjecConv_T5_TRGO: Timer5 TRGO event selected
 *      arg ADC_ExternalTrigInjecConv_T8_CC2: Timer8 capture compare2 selected
 *      arg ADC_ExternalTrigInjecConv_T8_CC3: Timer8 capture compare3 selected
 *      arg ADC_ExternalTrigInjecConv_T8_CC4: Timer8 capture compare4 selected
 *      arg ADC_ExternalTrigInjecConv_Ext_IT15: External interrupt line 15
 *            event selected
 * retval None
 */
void ADC_ExternalTrigInjectedConvConfig(
    ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv
) {
    uint32_t tmpreg = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));
    tmpreg = ADCx->CR2; /* Get old register value */
    /* Clear old external event selection for injected group */
    tmpreg &= CR2_JEXTSEL_RESET;
    /* Set external event selection for injected group */
    tmpreg |= ADC_ExternalTrigInjecConv;
    ADCx->CR2 = tmpreg; /* Store new register value */
}

/**
 * Configures ADCx external trigger edge for injected channels conversion.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_ExternalTrigInjecConvEdge: specifies ADC external trigger edge
 *       to start injected conversion. 
 *    This parameter can be one of following values:
 *        arg ADC_ExternalTrigInjecConvEdge_None: external trigger
 *            disabled for injected conversion
 *        arg ADC_ExternalTrigInjecConvEdge_Rising: detection on rising edge
 *        arg ADC_ExternalTrigInjecConvEdge_Falling: detection on falling edge
 *        arg ADC_ExternalTrigInjecConvEdge_RisingFalling: detection
 *            on both rising and falling edge
 * retval None
 */
void ADC_ExternalTrigInjectedConvEdgeConfig(
    ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConvEdge
) {
    uint32_t tmpreg = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_EXT_INJEC_TRIG_EDGE(ADC_ExternalTrigInjecConvEdge));
    tmpreg = ADCx->CR2; /* Get old register value */
    /* Clear old external trigger edge for injected group */
    tmpreg &= CR2_JEXTEN_RESET;
    /* Set new external trigger edge for injected group */
    tmpreg |= ADC_ExternalTrigInjecConvEdge;
    ADCx->CR2 = tmpreg; /* Store new register value */
}

/**
 * Enables selected ADC software start conversion of injected channels.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * retval None
 */
void ADC_SoftwareStartInjectedConv(ADC_TypeDef* ADCx) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx)); /* Check parameters */
    /* Enable selected ADC conversion for injected group */
    ADCx->CR2 |= (uint32_t) ADC_CR2_JSWSTART;
}

/**
 * Gets selected ADC Software start injected conversion Status.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * retval The new state of ADC software start injected conversion (SET/RESET).
 */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    /* Check status of JSWSTART bit */
    if ((ADCx->CR2 & ADC_CR2_JSWSTART) != (uint32_t) RESET) {
        bitstatus = SET; /* JSWSTART bit is set */
    } else {
        bitstatus = RESET; /* JSWSTART bit is reset */
    }
    return bitstatus; /* Return JSWSTART bit status */
}

/**
 * Enables or disables selected ADC automatic injected group 
 * conversion after regular one.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC auto injected conversion
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC automatic injected group conversion */
        ADCx->CR1 |= (uint32_t) ADC_CR1_JAUTO;
    } else {
        /* Disable selected ADC automatic injected group conversion */
        ADCx->CR1 &= (uint32_t) (~ADC_CR1_JAUTO);
    }
}

/**
 * Enables or disables discontinuous mode for injected group 
 * channel for specified ADC
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param NewState: new state of selected ADC discontinuous
 *       mode on injected group channel.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable selected ADC injected discontinuous mode */
        ADCx->CR1 |= (uint32_t) ADC_CR1_JDISCEN;
    } else {
        /* Disable selected ADC injected discontinuous mode */
        ADCx->CR1 &= (uint32_t) (~ADC_CR1_JDISCEN);
    }
}

/**
 * Returns ADC injected channel conversion result
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_InjectedChannel: converted ADC injected channel.
 *    This parameter can be one of following values:
 *        arg ADC_InjectedChannel_1: Injected Channel1 selected
 *        arg ADC_InjectedChannel_2: Injected Channel2 selected
 *        arg ADC_InjectedChannel_3: Injected Channel3 selected
 *        arg ADC_InjectedChannel_4: Injected Channel4 selected
 * retval The Data conversion value.
 */
uint16_t ADC_GetInjectedConversionValue(
    ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel
) {
    __IO uint32_t tmp = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
    tmp = (uint32_t) ADCx;
    tmp += ADC_InjectedChannel + JDR_OFFSET;
    /* Returns selected injected channel conversion data value */
    return (uint16_t) (*(__IO uint32_t*) tmp);
}

/**
 * Enables or disables specified ADC interrupts.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_IT: specifies ADC interrupt sources to be enabled or disabled.
 *    This parameter can be one of following values:
 *        arg ADC_IT_EOC: End of conversion interrupt mask
 *        arg ADC_IT_AWD: Analog watchdog interrupt mask
 *        arg ADC_IT_JEOC: End of injected conversion interrupt mask
 *        arg ADC_IT_OVR: Overrun interrupt enable
 * param NewState: new state of specified ADC interrupts.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void ADC_ITConfig(
    ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState
) {
    uint32_t itmask = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT(ADC_IT));
    itmask = (uint8_t) ADC_IT; /* Get ADC IT index */
    itmask = (uint32_t) 0x01 << itmask;
    if (NewState != DISABLE) {
        ADCx->CR1 |= itmask; /* Enable selected ADC interrupts */
    } else {
        /* Disable selected ADC interrupts */
        ADCx->CR1 &= (~(uint32_t) itmask);
    }
}

/**
 * Checks whether specified ADC flag is set or not.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_FLAG: specifies flag to check.
 *    This parameter can be one of following values:
 *        arg ADC_FLAG_AWD: Analog watchdog flag
 *        arg ADC_FLAG_EOC: End of conversion flag
 *        arg ADC_FLAG_JEOC: End of injected group conversion flag
 *        arg ADC_FLAG_JSTRT: Start of injected group conversion flag
 *        arg ADC_FLAG_STRT: Start of regular group conversion flag
 *        arg ADC_FLAG_OVR: Overrun flag
 * retval The new state of ADC_FLAG (SET or RESET).
 */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_FLAG(ADC_FLAG));
    /* Check status of specified ADC flag */
    if ((ADCx->SR & ADC_FLAG) != (uint8_t) RESET) {
        bitstatus = SET; /* ADC_FLAG is set */
    } else {
        bitstatus = RESET; /* ADC_FLAG is reset */
    }
    return bitstatus; /* Return ADC_FLAG status */
}

/**
 * Clears ADCx's pending flags.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_FLAG: specifies flag to clear.
 *    This parameter can be any combination of following values:
 *        arg ADC_FLAG_AWD: Analog watchdog flag
 *        arg ADC_FLAG_EOC: End of conversion flag
 *        arg ADC_FLAG_JEOC: End of injected group conversion flag
 *        arg ADC_FLAG_JSTRT: Start of injected group conversion flag
 *        arg ADC_FLAG_STRT: Start of regular group conversion flag
 *        arg ADC_FLAG_OVR: Overrun flag
 * retval None
 */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG) {
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
    ADCx->SR = ~(uint32_t) ADC_FLAG; /* Clear selected ADC flags */
}

/**
 * Checks whether specified ADC interrupt has occurred or not.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_IT: specifies ADC interrupt source to check.
 *    This parameter can be one of following values:
 *        arg ADC_IT_EOC: End of conversion interrupt mask
 *        arg ADC_IT_AWD: Analog watchdog interrupt mask
 *        arg ADC_IT_JEOC: End of injected conversion interrupt mask
 *        arg ADC_IT_OVR: Overrun interrupt mask
 * retval The new state of ADC_IT (SET or RESET).
 */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t itmask = 0, enablestatus = 0;

    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT(ADC_IT));
    itmask = ADC_IT >> 8; /* Get ADC IT index */
    /* Get ADC_IT enable bit status */
    enablestatus = (ADCx->CR1 & ((uint32_t) 0x01 << (uint8_t) ADC_IT));
    /* Check status of specified ADC interrupt */
    if (((ADCx->SR & itmask) != (uint32_t) RESET) && enablestatus) {
        bitstatus = SET; /* ADC_IT is set */
    } else {
        bitstatus = RESET; /* ADC_IT is reset */
    }
    return bitstatus; /* Return ADC_IT status */
}

/**
 * Clears ADCx's interrupt pending bits.
 * param ADCx: where x can be 1, 2 or 3 to select ADC peripheral.
 * param ADC_IT: specifies ADC interrupt pending bit to clear.
 *    This parameter can be one of following values:
 *        arg ADC_IT_EOC: End of conversion interrupt mask
 *        arg ADC_IT_AWD: Analog watchdog interrupt mask
 *        arg ADC_IT_JEOC: End of injected conversion interrupt mask
 *        arg ADC_IT_OVR: Overrun interrupt mask
 * retval None
 */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT) {
    uint8_t itmask = 0;
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT(ADC_IT));
    itmask = (uint8_t) (ADC_IT >> 8); /* Get ADC IT index */
    /* Clear selected ADC interrupt pending bits */
    ADCx->SR = ~(uint32_t) itmask;
}

