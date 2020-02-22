/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_tim.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of TIM peripheral:
 *     - TimeBase management
 *     - Output Compare management
 *     - Input Capture management
 *     - Advanced-control timers (TIM1 and TIM8) specific features
 *     - Interrupts, DMA and flags management
 *     - Clocks management
 *     - Synchronization management
 *     - Specific interface management
 *     - Specific remapping management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_tim is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_tim is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* TIM registers bit mask */
#define SMCR_ETR_MASK ((uint16_t) 0x00FF)
#define CCMR_OFFSET ((uint16_t) 0x0018)
#define CCER_CCE_SET ((uint16_t) 0x0001)
#define CCER_CCNE_SET ((uint16_t) 0x0004)
#define CCMR_OC13M_MASK ((uint16_t) 0xFF8F)
#define CCMR_OC24M_MASK ((uint16_t) 0x8FFF)

static void TI1_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
);

static void TI2_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
);

static void TI3_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
);

static void TI4_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
);

/**
 * Deinitializes TIMx peripheral registers to their default reset values.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * retval None
 */
void TIM_DeInit(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    if (TIMx == TIM1) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);
    } else if (TIMx == TIM2) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
    } else if (TIMx == TIM3) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
    } else if (TIMx == TIM4) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
    } else if (TIMx == TIM5) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
    } else if (TIMx == TIM6) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
    } else if (TIMx == TIM7) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
    } else if (TIMx == TIM8) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
    } else if (TIMx == TIM9) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, DISABLE);
    } else if (TIMx == TIM10) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, DISABLE);
    } else if (TIMx == TIM11) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, DISABLE);
    } else if (TIMx == TIM12) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);
    } else if (TIMx == TIM13) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, DISABLE);
    } else {
        if (TIMx == TIM14) {
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);
        }
    }
}

/**
 * Initializes TIMx Time Base Unit peripheral according to 
 * specified parameters in TIM_TimeBaseInitStruct.
 * param TIMx: where x can be  1 to 14 to select TIM peripheral.
 * param TIM_TimeBaseInitStruct: pointer to TIM_TimeBaseInitTypeDef structure
 *       that contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_TimeBaseInit(
    TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct
) {
    uint16_t tmpcr1 = 0;

    assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
    assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
    assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));
    tmpcr1 = TIMx->CR1;
    if (
        (TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) ||
        (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5)
    ) {
        /* Select Counter Mode */
        tmpcr1 &= (uint16_t) (~(TIM_CR1_DIR | TIM_CR1_CMS));
        tmpcr1 |= (uint32_t) TIM_TimeBaseInitStruct->TIM_CounterMode;
    }
    if ((TIMx != TIM6) && (TIMx != TIM7)) {
        /* Set clock division */
        tmpcr1 &= (uint16_t) (~TIM_CR1_CKD);
        tmpcr1 |= (uint32_t) TIM_TimeBaseInitStruct->TIM_ClockDivision;
    }
    TIMx->CR1 = tmpcr1;
    TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period; /* Set Autoreload value */
    TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler; /* Set Prescaler */
    if ((TIMx == TIM1) || (TIMx == TIM8)) {
        /* Set Repetition Counter value */
        TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
    }
    /**
     * Generate an update event to reload Prescaler 
     * and repetition counter(only for TIM1 and TIM8) value immediatly
     */
    TIMx->EGR = TIM_PSCReloadMode_Immediate;
}

/**
 * Fills each TIM_TimeBaseInitStruct member with its default value.
 * param TIM_TimeBaseInitStruct : pointer to a TIM_TimeBaseInitTypeDef
 *       structure which will be initialized.
 * retval None
 */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct) {
    /* Set default configuration */
    TIM_TimeBaseInitStruct->TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
    TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
 * Configures TIMx Prescaler.
 * param TIMx: where x can be  1 to 14 to select TIM peripheral.
 * param Prescaler: specifies Prescaler Register value
 * param TIM_PSCReloadMode: specifies TIM Prescaler Reload mode
 *   This parameter can be one of following values:
 *       arg TIM_PSCReloadMode_Update: The Prescaler is loaded at update event.
 *       arg TIM_PSCReloadMode_Immediate: The Prescaler is loaded immediatly.
 * retval None
 */
void TIM_PrescalerConfig(
    TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode
) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));
    TIMx->PSC = Prescaler; /* Set Prescaler value */
    TIMx->EGR = TIM_PSCReloadMode; /* Set or reset UG Bit */
}

/**
 * Specifies TIMx Counter Mode to be used.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_CounterMode: specifies Counter Mode to be used
 *   This parameter can be one of following values:
 *       arg TIM_CounterMode_Up: TIM Up Counting Mode
 *       arg TIM_CounterMode_Down: TIM Down Counting Mode
 *       arg TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
 *       arg TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
 *       arg TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
 * retval None
 */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode) {
    uint16_t tmpcr1 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));
    tmpcr1 = TIMx->CR1;
    /* Reset CMS and DIR Bits */
    tmpcr1 &= (uint16_t) ~(TIM_CR1_DIR | TIM_CR1_CMS);
    tmpcr1 |= TIM_CounterMode; /* Set Counter Mode */
    TIMx->CR1 = tmpcr1; /* Write to TIMx CR1 register */
}

/**
 * Sets TIMx Counter Register value
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param Counter: specifies Counter register new value.
 * retval None
 */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    TIMx->CNT = Counter; /* Set Counter Register value */
}

/**
 * Sets TIMx Autoreload Register value
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param Autoreload: specifies Autoreload register new value.
 * retval None
 */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    TIMx->ARR = Autoreload; /* Set Autoreload Register value */
}

/**
 * Gets TIMx Counter value.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * retval Counter Register value
 */
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    return TIMx->CNT; /* Get Counter Register value */
}

/**
 * Gets TIMx Prescaler value.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * retval Prescaler Register value.
 */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    return TIMx->PSC; /* Get Prescaler Register value */
}

/**
 * Enables or Disables TIMx Update event.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param NewState: new state of TIMx UDIS bit
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR1 |= TIM_CR1_UDIS; /* Set Update Disable Bit */
    } else {
        TIMx->CR1 &= (uint16_t) ~TIM_CR1_UDIS; /* Reset Update Disable Bit */
    }
}

/**
 * Configures TIMx Update Request Interrupt source.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_UpdateSource: specifies Update source.
 *   This parameter can be one of following values:
 *       arg TIM_UpdateSource_Global: Source of update is counter
 *           overflow/underflow or setting of UG bit, or an update
 *           generation through slave mode controller.
 *       arg TIM_UpdateSource_Regular: Source of update is counter
 *           overflow/underflow.
 * retval None
 */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));
    if (TIM_UpdateSource != TIM_UpdateSource_Global) {
        TIMx->CR1 |= TIM_CR1_URS; /* Set URS Bit */
    } else {
        TIMx->CR1 &= (uint16_t) ~TIM_CR1_URS; /* Reset URS Bit */
    }
}

/**
 * Enables or disables TIMx peripheral Preload register on ARR.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param NewState: new state of TIMx peripheral Preload register
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR1 |= TIM_CR1_ARPE; /* Set ARR Preload Bit */
    } else {
        TIMx->CR1 &= (uint16_t) ~TIM_CR1_ARPE; /* Reset ARR Preload Bit */
    }
}

/**
 * Selects TIMx's One Pulse Mode.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_OPMode: specifies OPM Mode to be used.
 *   This parameter can be one of following values:
 *       arg TIM_OPMode_Single
 *       arg TIM_OPMode_Repetitive
 * retval None
 */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_OPM_MODE(TIM_OPMode));
    TIMx->CR1 &= (uint16_t) ~TIM_CR1_OPM; /* Reset OPM Bit */
    TIMx->CR1 |= TIM_OPMode; /* Configure OPM Mode */
}

/**
 * Sets TIMx Clock Division value.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_CKD: specifies clock division value.
 *   This parameter can be one of following value:
 *       arg TIM_CKD_DIV1: TDTS = Tck_tim
 *       arg TIM_CKD_DIV2: TDTS = 2*Tck_tim
 *       arg TIM_CKD_DIV4: TDTS = 4*Tck_tim
 * retval None
 */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD) {
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_CKD_DIV(TIM_CKD));
    TIMx->CR1 &= (uint16_t) (~TIM_CR1_CKD); /* Reset CKD Bits */
    TIMx->CR1 |= TIM_CKD; /* Set CKD value */
}

/**
 * Enables or disables specified TIM peripheral.
 * param TIMx: where x can be 1 to 14 to select TIMx peripheral.
 * param NewState: new state of TIMx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR1 |= TIM_CR1_CEN; /* Enable TIM Counter */
    } else {
        TIMx->CR1 &= (uint16_t) ~TIM_CR1_CEN; /* Disable TIM Counter */
    }
}

/**
 * Initializes TIMx Channel1 according to specified parameters in
 * TIM_OCInitStruct.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that
 *       contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx)); 
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
    /* Disable Channel 1: Reset CC1E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC1E;
    tmpccer = TIMx->CCER; /* Get TIMx CCER register value */
    tmpcr2 =  TIMx->CR2; /* Get TIMx CR2 register value */
    tmpccmrx = TIMx->CCMR1; /* Get TIMx CCMR1 register value */
    /* Reset Output Compare Mode Bits */
    tmpccmrx &= (uint16_t) ~TIM_CCMR1_OC1M;
    tmpccmrx &= (uint16_t) ~TIM_CCMR1_CC1S;
    /* Select Output Compare Mode */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
    tmpccer &= (uint16_t) ~TIM_CCER_CC1P; /* Reset Output Polarity level */
    /* Set Output Compare Polarity */
    tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
    tmpccer |= TIM_OCInitStruct->TIM_OutputState; /* Set Output State */
    if ((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
        /* Reset Output N Polarity level */
        tmpccer &= (uint16_t) ~TIM_CCER_CC1NP;
        /* Set Output N Polarity */
        tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;
        tmpccer &= (uint16_t) ~TIM_CCER_CC1NE; /* Reset Output N State */
        /* Set Output N State */
        tmpccer |= TIM_OCInitStruct->TIM_OutputNState;
        /* Reset Output Compare and Output Compare N IDLE State */
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS1;
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS1N;
        /* Set Output Idle state */
        tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
        /* Set Output N Idle state */
        tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
    }
    TIMx->CR2 = tmpcr2; /* Write to TIMx CR2 */
    TIMx->CCMR1 = tmpccmrx; /* Write to TIMx CCMR1 */
    /* Set Capture Compare Register value */
    TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer; /* Write to TIMx CCER */
}

/**
 * Initializes TIMx Channel2 according to specified parameters 
 * in TIM_OCInitStruct.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that
 *       contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx)); 
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
    /* Disable Channel 2: Reset CC2E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC2E;
    tmpccer = TIMx->CCER; /* Get TIMx CCER register value */
    tmpcr2 =  TIMx->CR2; /* Get TIMx CR2 register value */
    tmpccmrx = TIMx->CCMR1; /* Get TIMx CCMR1 register value */
    /* Reset Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint16_t) ~TIM_CCMR1_OC2M;
    tmpccmrx &= (uint16_t) ~TIM_CCMR1_CC2S;
    /* Select Output Compare Mode */
    tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
    /* Reset Output Polarity level */
    tmpccer &= (uint16_t)~TIM_CCER_CC2P;
    /* Set Output Compare Polarity */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);
    /* Set Output State */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);
    if ((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
        /* Reset Output N Polarity level */
        tmpccer &= (uint16_t) ~TIM_CCER_CC2NP;
        /* Set Output N Polarity */
        tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OCNPolarity << 4);
        /* Reset Output N State */
        tmpccer &= (uint16_t) ~TIM_CCER_CC2NE;
        /* Set Output N State */
        tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OutputNState << 4);
        /* Reset Output Compare and Output Compare N IDLE State */
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS2;
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS2N;
        /* Set Output Idle state */
        tmpcr2 |= (uint16_t) (TIM_OCInitStruct->TIM_OCIdleState << 2);
        /* Set Output N Idle state */
        tmpcr2 |= (uint16_t) (TIM_OCInitStruct->TIM_OCNIdleState << 2);
    }
    TIMx->CR2 = tmpcr2; /* Write to TIMx CR2 */
    TIMx->CCMR1 = tmpccmrx; /* Write to TIMx CCMR1 */
    /* Set Capture Compare Register value */
    TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer; /* Write to TIMx CCER */
}

/**
 * Initializes TIMx Channel3 according to specified parameters
 * in TIM_OCInitStruct.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that
 *       contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
    assert_param(IS_TIM_LIST3_PERIPH(TIMx)); 
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
    /* Disable Channel 3: Reset CC2E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC3E;
    tmpccer = TIMx->CCER; /* Get TIMx CCER register value */
    tmpcr2 =  TIMx->CR2; /* Get TIMx CR2 register value */
    tmpccmrx = TIMx->CCMR2; /* Get TIMx CCMR2 register value */
    /* Reset Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint16_t) ~TIM_CCMR2_OC3M;
    tmpccmrx &= (uint16_t) ~TIM_CCMR2_CC3S;
    /* Select Output Compare Mode */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
    /* Reset Output Polarity level */
    tmpccer &= (uint16_t) ~TIM_CCER_CC3P;
    /* Set Output Compare Polarity */
    tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OCPolarity << 8);
    /* Set Output State */
    tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OutputState << 8);
    if((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
        /* Reset Output N Polarity level */
        tmpccer &= (uint16_t) ~TIM_CCER_CC3NP;
        /* Set Output N Polarity */
        tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OCNPolarity << 8);
        /* Reset Output N State */
        tmpccer &= (uint16_t) ~TIM_CCER_CC3NE;
        /* Set Output N State */
        tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OutputNState << 8);
        /* Reset Output Compare and Output Compare N IDLE State */
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS3;
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS3N;
        /* Set Output Idle state */
        tmpcr2 |= (uint16_t) (TIM_OCInitStruct->TIM_OCIdleState << 4);
        /* Set Output N Idle state */
        tmpcr2 |= (uint16_t) (TIM_OCInitStruct->TIM_OCNIdleState << 4);
    }
    TIMx->CR2 = tmpcr2; /* Write to TIMx CR2 */
    TIMx->CCMR2 = tmpccmrx; /* Write to TIMx CCMR2 */
    /* Set Capture Compare Register value */
    TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer; /* Write to TIMx CCER */
}

/**
 * Initializes TIMx Channel4 according to specified
 * parameters in TIM_OCInitStruct.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure that
 *       contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx)); 
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));
    /* Disable Channel 4: Reset CC4E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC4E;
    tmpccer = TIMx->CCER; /* Get TIMx CCER register value */
    tmpcr2 =  TIMx->CR2; /* Get TIMx CR2 register value */
    tmpccmrx = TIMx->CCMR2; /* Get TIMx CCMR2 register value */
    /* Reset Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint16_t) ~TIM_CCMR2_OC4M;
    tmpccmrx &= (uint16_t) ~TIM_CCMR2_CC4S;
    /* Select Output Compare Mode */
    tmpccmrx |= (uint16_t) (TIM_OCInitStruct->TIM_OCMode << 8);
    /* Reset Output Polarity level */
    tmpccer &= (uint16_t) ~TIM_CCER_CC4P;
    /* Set Output Compare Polarity */
    tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OCPolarity << 12);
    /* Set Output State */
    tmpccer |= (uint16_t) (TIM_OCInitStruct->TIM_OutputState << 12);
    if((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
        /* Reset Output Compare IDLE State */
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS4;
        /* Set Output Idle state */
        tmpcr2 |= (uint16_t) (TIM_OCInitStruct->TIM_OCIdleState << 6);
    }
    TIMx->CR2 = tmpcr2; /* Write to TIMx CR2 */
    TIMx->CCMR2 = tmpccmrx; /* Write to TIMx CCMR2 */
    /* Set Capture Compare Register value */
    TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer; /* Write to TIMx CCER */
}

/**
 * Fills each TIM_OCInitStruct member with its default value.
 * param TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct) {
    /* Set default configuration */
    TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct->TIM_Pulse = 0x00000000;
    TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
 * Selects TIM Output Compare Mode.
 * This function disables selected channel before changing Output
 * Compare Mode. If needed, user has to enable this channel using
 * TIM_CCxCmd() and TIM_CCxNCmd() functions.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_Channel: specifies TIM Channel
 *   This parameter can be one of following values:
 *       arg TIM_Channel_1: TIM Channel 1
 *       arg TIM_Channel_2: TIM Channel 2
 *       arg TIM_Channel_3: TIM Channel 3
 *       arg TIM_Channel_4: TIM Channel 4
 * param TIM_OCMode: specifies TIM Output Compare Mode.
 *    This parameter can be one of following values:
 *       arg TIM_OCMode_Timing
 *       arg TIM_OCMode_Active
 *       arg TIM_OCMode_Toggle
 *       arg TIM_OCMode_PWM1
 *       arg TIM_OCMode_PWM2
 *       arg TIM_ForcedAction_Active
 *       arg TIM_ForcedAction_InActive
 * retval None
 */
void TIM_SelectOCxM(
    TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode
) {
    uint32_t tmp = 0;
    uint16_t tmp1 = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_OCM(TIM_OCMode));
    tmp = (uint32_t) TIMx;
    tmp += CCMR_OFFSET;
    tmp1 = CCER_CCE_SET << (uint16_t) TIM_Channel;
    /* Disable Channel: Reset CCxE Bit */
    TIMx->CCER &= (uint16_t) ~tmp1;
    if ((TIM_Channel == TIM_Channel_1) || (TIM_Channel == TIM_Channel_3)) {
        tmp += (TIM_Channel >> 1);
        /* Reset OCxM bits in CCMRx register */
        *(__IO uint32_t *) tmp &= CCMR_OC13M_MASK;
        /* Configure OCxM bits in CCMRx register */
        *(__IO uint32_t *) tmp |= TIM_OCMode;
    } else {
        tmp += (uint16_t) (TIM_Channel - (uint16_t) 4) >> (uint16_t) 1;
        /* Reset OCxM bits in CCMRx register */
        *(__IO uint32_t *) tmp &= CCMR_OC24M_MASK;
        /* Configure OCxM bits in CCMRx register */
        *(__IO uint32_t *) tmp |= (uint16_t) (TIM_OCMode << 8);
    }
}

/**
 * Sets TIMx Capture Compare1 Register value
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param Compare1: specifies Capture Compare1 register new value.
 * retval None
 */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1) {
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    TIMx->CCR1 = Compare1; /* Set Capture Compare1 Register value */
}

/**
 * Sets TIMx Capture Compare2 Register value
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param Compare2: specifies Capture Compare2 register new value.
 * retval None
 */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    TIMx->CCR2 = Compare2; /* Set Capture Compare2 Register value */
}

/**
 * Sets TIMx Capture Compare3 Register value
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param Compare3: specifies Capture Compare3 register new value.
 * retval None
 */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    TIMx->CCR3 = Compare3; /* Set Capture Compare3 Register value */
}

/**
 * Sets TIMx Capture Compare4 Register value
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param Compare4: specifies Capture Compare4 register new value.
 * retval None
 */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    TIMx->CCR4 = Compare4; /* Set Capture Compare4 Register value */
}

/**
 * Forces TIMx output 1 waveform to active or inactive level.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_ForcedAction: specifies forced Action to be
 *       set to output waveform.
 *   This parameter can be one of following values:
 *       arg TIM_ForcedAction_Active: Force active level on OC1REF
 *       arg TIM_ForcedAction_InActive: Force inactive level on OC1REF.
 * retval None
 */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) ~TIM_CCMR1_OC1M;
    tmpccmr1 |= TIM_ForcedAction;
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 register */
}

/**
 * Forces TIMx output 2 waveform to active or inactive level.
 * param TIMx: where x can be  1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_ForcedAction: specifies forced Action to be
 *       set to output waveform.
 *   This parameter can be one of following values:
 *       arg TIM_ForcedAction_Active: Force active level on OC2REF
 *       arg TIM_ForcedAction_InActive: Force inactive level on OC2REF.
 * retval None
 */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) ~TIM_CCMR1_OC2M;
    tmpccmr1 |= (uint16_t) (TIM_ForcedAction << 8);
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 register */
}

/**
 * Forces TIMx output 3 waveform to active or inactive level.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ForcedAction: specifies forced Action to be set to output waveform.
 *   This parameter can be one of following values:
 *       arg TIM_ForcedAction_Active: Force active level on OC3REF
 *       arg TIM_ForcedAction_InActive: Force inactive level on OC3REF.
 * retval None
 */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) ~TIM_CCMR2_OC3M;
    tmpccmr2 |= TIM_ForcedAction;
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 register */
}

/**
 * Forces TIMx output 4 waveform to active or inactive level.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ForcedAction: specifies forced Action to be
 *       set to output waveform.
 *   This parameter can be one of following values:
 *       arg TIM_ForcedAction_Active: Force active level on OC4REF
 *       arg TIM_ForcedAction_InActive: Force inactive level on OC4REF.
 * retval None
 */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) ~TIM_CCMR2_OC4M;
    tmpccmr2 |= (uint16_t) (TIM_ForcedAction << 8);
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 register */
}

/**
 * Enables or disables TIMx peripheral Preload register on CCR1.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_OCPreload: new state of TIMx peripheral Preload register
 *   This parameter can be one of following values:
 *       arg TIM_OCPreload_Enable
 *       arg TIM_OCPreload_Disable
 * retval None
 */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) (~TIM_CCMR1_OC1PE);
    tmpccmr1 |= TIM_OCPreload;
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 register */
}

/**
 * Enables or disables TIMx peripheral Preload register on CCR2.
 * param TIMx: where x can be  1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_OCPreload: new state of TIMx peripheral Preload register
 *   This parameter can be one of following values:
 *       arg TIM_OCPreload_Enable
 *       arg TIM_OCPreload_Disable
 * retval None
 */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) (~TIM_CCMR1_OC2PE);
    tmpccmr1 |= (uint16_t) (TIM_OCPreload << 8);
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 register */
}

/**
 * Enables or disables TIMx peripheral Preload register on CCR3.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCPreload: new state of TIMx peripheral Preload register
 *   This parameter can be one of following values:
 *       arg TIM_OCPreload_Enable
 *       arg TIM_OCPreload_Disable
 * retval None
 */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) (~TIM_CCMR2_OC3PE);
    tmpccmr2 |= TIM_OCPreload;
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 register */
}

/**
 * Enables or disables TIMx peripheral Preload register on CCR4.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCPreload: new state of TIMx peripheral Preload register
 *   This parameter can be one of following values:
 *       arg TIM_OCPreload_Enable
 *       arg TIM_OCPreload_Disable
 * retval None
 */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) (~TIM_CCMR2_OC4PE);
    tmpccmr2 |= (uint16_t) (TIM_OCPreload << 8);
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 register */
}

/**
 * Configures TIMx Output Compare 1 Fast feature.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_OCFast: new state of Output Compare Fast Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCFast_Enable: TIM output compare fast enable
 *       arg TIM_OCFast_Disable: TIM output compare fast disable
 * retval None
 */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) ~TIM_CCMR1_OC1FE;
    tmpccmr1 |= TIM_OCFast;
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 */
}

/**
 * Configures TIMx Output Compare 2 Fast feature.
 * param TIMx: where x can be  1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_OCFast: new state of Output Compare Fast Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCFast_Enable: TIM output compare fast enable
 *       arg TIM_OCFast_Disable: TIM output compare fast disable
 * retval None
 */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) (~TIM_CCMR1_OC2FE);
    tmpccmr1 |= (uint16_t) (TIM_OCFast << 8);
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 */
}

/**
 * Configures TIMx Output Compare 3 Fast feature.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCFast: new state of Output Compare Fast Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCFast_Enable: TIM output compare fast enable
 *       arg TIM_OCFast_Disable: TIM output compare fast disable
 * retval None
 */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) ~TIM_CCMR2_OC3FE;
    tmpccmr2 |= TIM_OCFast;
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 */
}

/**
 * Configures TIMx Output Compare 4 Fast feature.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCFast: new state of Output Compare Fast Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCFast_Enable: TIM output compare fast enable
 *       arg TIM_OCFast_Disable: TIM output compare fast disable
 * retval None
 */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) (~TIM_CCMR2_OC4FE); /* Reset OC4FE Bit */
    /* Enable or Disable Output Compare Fast Bit */
    tmpccmr2 |= (uint16_t) (TIM_OCFast << 8);
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 */
}

/**
 * Clears or safeguards OCREF1 signal on an external event
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_OCClear: new state of Output Compare Clear Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCClear_Enable: TIM Output clear enable
 *       arg TIM_OCClear_Disable: TIM Output clear disable
 * retval None
 */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) ~TIM_CCMR1_OC1CE;
    /* Enable or Disable Output Compare Clear Bit */
    tmpccmr1 |= TIM_OCClear;
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 register */
}

/**
 * Clears or safeguards OCREF2 signal on an external event
 * param TIMx: where x can be  1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_OCClear: new state of Output Compare Clear Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCClear_Enable: TIM Output clear enable
 *       arg TIM_OCClear_Disable: TIM Output clear disable
 * retval None
 */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr1 = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
    tmpccmr1 = TIMx->CCMR1;
    tmpccmr1 &= (uint16_t) ~TIM_CCMR1_OC2CE;
    /* Enable or Disable Output Compare Clear Bit */
    tmpccmr1 |= (uint16_t) (TIM_OCClear << 8);
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 register */
}

/**
 * Clears or safeguards OCREF3 signal on an external event
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCClear: new state of Output Compare Clear Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCClear_Enable: TIM Output clear enable
 *       arg TIM_OCClear_Disable: TIM Output clear disable
 * retval None
 */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) ~TIM_CCMR2_OC3CE;
    /* Enable or Disable Output Compare Clear Bit */
    tmpccmr2 |= TIM_OCClear;
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 register */
}

/**
 * Clears or safeguards OCREF4 signal on an external event
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCClear: new state of Output Compare Clear Enable Bit.
 *   This parameter can be one of following values:
 *       arg TIM_OCClear_Enable: TIM Output clear enable
 *       arg TIM_OCClear_Disable: TIM Output clear disable
 * retval None
 */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr2 = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
    tmpccmr2 = TIMx->CCMR2;
    tmpccmr2 &= (uint16_t) ~TIM_CCMR2_OC4CE;
    /* Enable or Disable Output Compare Clear Bit */
    tmpccmr2 |= (uint16_t) (TIM_OCClear << 8);
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 register */
}

/**
 * Configures TIMx channel 1 polarity.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_OCPolarity: specifies OC1 Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCPolarity_High: Output Compare active high
 *       arg TIM_OCPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) (~TIM_CCER_CC1P);
    tmpccer |= TIM_OCPolarity;
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Configures TIMx Channel 1N polarity.
 * param TIMx: where x can be 1 or 8 to select TIM peripheral.
 * param TIM_OCNPolarity: specifies OC1N Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCNPolarity_High: Output Compare active high
 *       arg TIM_OCNPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity) {
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~TIM_CCER_CC1NP;
    tmpccer |= TIM_OCNPolarity;
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Configures TIMx channel 2 polarity.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_OCPolarity: specifies OC2 Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCPolarity_High: Output Compare active high
 *       arg TIM_OCPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
    tmpccer = TIMx->CCER; 
    tmpccer &= (uint16_t) (~TIM_CCER_CC2P);
    tmpccer |= (uint16_t) (TIM_OCPolarity << 4);
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Configures TIMx Channel 2N polarity.
 * param TIMx: where x can be 1 or 8 to select TIM peripheral.
 * param TIM_OCNPolarity: specifies OC2N Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCNPolarity_High: Output Compare active high
 *       arg TIM_OCNPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity) {
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~TIM_CCER_CC2NP;
    tmpccer |= (uint16_t) (TIM_OCNPolarity << 4);
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Configures TIMx channel 3 polarity.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCPolarity: specifies OC3 Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCPolarity_High: Output Compare active high
 *       arg TIM_OCPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~TIM_CCER_CC3P; /* Set or Reset CC3P Bit */
    tmpccer |= (uint16_t) (TIM_OCPolarity << 8);
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Configures TIMx Channel 3N polarity.
 * param TIMx: where x can be 1 or 8 to select TIM peripheral.
 * param TIM_OCNPolarity: specifies OC3N Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCNPolarity_High: Output Compare active high
 *       arg TIM_OCNPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity) {
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~TIM_CCER_CC3NP; /* Set or Reset CC3NP Bit */
    tmpccer |= (uint16_t) (TIM_OCNPolarity << 8);
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Configures TIMx channel 4 polarity.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_OCPolarity: specifies OC4 Polarity
 *   This parameter can be one of following values:
 *       arg TIM_OCPolarity_High: Output Compare active high
 *       arg TIM_OCPolarity_Low: Output Compare active low
 * retval None
 */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
      uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~TIM_CCER_CC4P; /* Set or Reset CC4P Bit */
    tmpccer |= (uint16_t) (TIM_OCPolarity << 12);
    TIMx->CCER = tmpccer; /* Write to TIMx CCER register */
}

/**
 * Enables or disables TIM Capture Compare Channel x.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_Channel: specifies TIM Channel
 *   This parameter can be one of following values:
 *       arg TIM_Channel_1: TIM Channel 1
 *       arg TIM_Channel_2: TIM Channel 2
 *       arg TIM_Channel_3: TIM Channel 3
 *       arg TIM_Channel_4: TIM Channel 4
 * param TIM_CCx: specifies TIM Channel CCxE bit new state.
 *   This parameter can be: TIM_CCx_Enable or TIM_CCx_Disable. 
 * retval None
 */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx) {
      uint16_t tmp = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx)); 
    assert_param(IS_TIM_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_CCX(TIM_CCx));
    tmp = CCER_CCE_SET << TIM_Channel;
    TIMx->CCER &= (uint16_t) ~tmp; /* Reset CCxE Bit */
    TIMx->CCER |= (uint16_t) (TIM_CCx << TIM_Channel); /* Set/reset CCxE Bit */
}

/**
 * Enables or disables TIM Capture Compare Channel xN.
 * param TIMx: where x can be 1 or 8 to select TIM peripheral.
 * param TIM_Channel: specifies TIM Channel
 *   This parameter can be one of following values:
 *       arg TIM_Channel_1: TIM Channel 1
 *       arg TIM_Channel_2: TIM Channel 2
 *       arg TIM_Channel_3: TIM Channel 3
 * param TIM_CCxN: specifies TIM Channel CCxNE bit new state.
 *   This parameter can be: TIM_CCxN_Enable or TIM_CCxN_Disable.
 * retval None
 */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN) {
    uint16_t tmp = 0;

    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_CCXN(TIM_CCxN));
    tmp = CCER_CCNE_SET << TIM_Channel;
    TIMx->CCER &= (uint16_t) ~tmp; /* Reset CCxNE Bit */
    /* Set or reset CCxNE Bit */
    TIMx->CCER |=  (uint16_t) (TIM_CCxN << TIM_Channel);
}

/**
 * Initializes TIM peripheral according to specified parameters
 * in TIM_ICInitStruct.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure that
 *       contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct) {
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
    assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
    assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
    if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1) {
        /* TI1 Configuration */
        TI1_Config(
            TIMx, TIM_ICInitStruct->TIM_ICPolarity,
            TIM_ICInitStruct->TIM_ICSelection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2) {
        /* TI2 Configuration */
        assert_param(IS_TIM_LIST2_PERIPH(TIMx));
        TI2_Config(
            TIMx, TIM_ICInitStruct->TIM_ICPolarity,
            TIM_ICInitStruct->TIM_ICSelection,
            TIM_ICInitStruct->TIM_ICFilter
         );
        /* Set Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3) {
        /* TI3 Configuration */
        assert_param(IS_TIM_LIST3_PERIPH(TIMx));
        TI3_Config(
            TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
            TIM_ICInitStruct->TIM_ICSelection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else {
        /* TI4 Configuration */
        assert_param(IS_TIM_LIST3_PERIPH(TIMx));
        TI4_Config(
            TIMx, TIM_ICInitStruct->TIM_ICPolarity,
            TIM_ICInitStruct->TIM_ICSelection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

/**
 * Fills each TIM_ICInitStruct member with its default value.
 * param TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct) {
    /* Set default configuration */
    TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/**
 * Configures TIM peripheral according to specified parameters
 * in TIM_ICInitStruct to measure an external PWM signal.
 * param TIMx: where x can be  1, 2, 3, 4, 5,8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
 *       that contains configuration information for specified TIM peripheral.
 * retval None
 */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct) {
    uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
    uint16_t icoppositeselection = TIM_ICSelection_DirectTI;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    /* Select Opposite Input Polarity */
    if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising) {
        icoppositepolarity = TIM_ICPolarity_Falling;
    } else {
        icoppositepolarity = TIM_ICPolarity_Rising;
    }
    /* Select Opposite Input */
    if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI) {
        icoppositeselection = TIM_ICSelection_IndirectTI;
    } else {
        icoppositeselection = TIM_ICSelection_DirectTI;
    }
    if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1) {
        /* TI1 Configuration */
        TI1_Config(
            TIMx, TIM_ICInitStruct->TIM_ICPolarity,
            TIM_ICInitStruct->TIM_ICSelection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        /* TI2 Configuration */
        TI2_Config(
            TIMx, icoppositepolarity, icoppositeselection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else {
        /* TI2 Configuration */
        TI2_Config(
            TIMx, TIM_ICInitStruct->TIM_ICPolarity,
            TIM_ICInitStruct->TIM_ICSelection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        /* TI1 Configuration */
        TI1_Config(
            TIMx, icoppositepolarity, icoppositeselection,
            TIM_ICInitStruct->TIM_ICFilter
        );
        /* Set Input Capture Prescaler value */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

/**
 * Gets TIMx Input Capture 1 value.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * retval Capture Compare 1 Register value.
 */
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    return TIMx->CCR1; /* Get Capture 1 Register value */
}

/**
 * Gets TIMx Input Capture 2 value.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * retval Capture Compare 2 Register value.
 */
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    return TIMx->CCR2; /* Get Capture 2 Register value */
}

/**
 * Gets TIMx Input Capture 3 value.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * retval Capture Compare 3 Register value.
 */
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    return TIMx->CCR3; /* Get Capture 3 Register value */
}

/**
 * Gets TIMx Input Capture 4 value.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * retval Capture Compare 4 Register value.
 */
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    return TIMx->CCR4; /* Get Capture 4 Register value */
}

/**
 * Sets TIMx Input Capture 1 prescaler.
 * param TIMx: where x can be 1 to 14 except 6 and 7, to select TIM peripheral.
 * param TIM_ICPSC: specifies Input Capture1 prescaler new value.
 *   This parameter can be one of following values:
 *       arg TIM_ICPSC_DIV1: no prescaler
 *       arg TIM_ICPSC_DIV2: capture is done once every 2 events
 *       arg TIM_ICPSC_DIV4: capture is done once every 4 events
 *       arg TIM_ICPSC_DIV8: capture is done once every 8 events
 * retval None
 */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
    TIMx->CCMR1 &= (uint16_t) ~TIM_CCMR1_IC1PSC; /* Reset IC1PSC Bits */
    TIMx->CCMR1 |= TIM_ICPSC; /* Set IC1PSC value */
}

/**
 * Sets TIMx Input Capture 2 prescaler.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_ICPSC: specifies Input Capture2 prescaler new value.
 *   This parameter can be one of following values:
 *       arg TIM_ICPSC_DIV1: no prescaler
 *       arg TIM_ICPSC_DIV2: capture is done once every 2 events
 *       arg TIM_ICPSC_DIV4: capture is done once every 4 events
 *       arg TIM_ICPSC_DIV8: capture is done once every 8 events
 * retval None
 */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
    TIMx->CCMR1 &= (uint16_t) ~TIM_CCMR1_IC2PSC; /* Reset IC2PSC Bits */
    TIMx->CCMR1 |= (uint16_t) (TIM_ICPSC << 8); /* Set IC2PSC value */
}

/**
 * Sets TIMx Input Capture 3 prescaler.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ICPSC: specifies Input Capture3 prescaler new value.
 *   This parameter can be one of following values:
 *       arg TIM_ICPSC_DIV1: no prescaler
 *       arg TIM_ICPSC_DIV2: capture is done once every 2 events
 *       arg TIM_ICPSC_DIV4: capture is done once every 4 events
 *       arg TIM_ICPSC_DIV8: capture is done once every 8 events
 * retval None
 */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
    TIMx->CCMR2 &= (uint16_t) ~TIM_CCMR2_IC3PSC; /* Reset IC3PSC Bits */
    TIMx->CCMR2 |= TIM_ICPSC; /* Set IC3PSC value */
}

/**
 * Sets TIMx Input Capture 4 prescaler.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ICPSC: specifies Input Capture4 prescaler new value.
 *   This parameter can be one of following values:
 *       arg TIM_ICPSC_DIV1: no prescaler
 *       arg TIM_ICPSC_DIV2: capture is done once every 2 events
 *       arg TIM_ICPSC_DIV4: capture is done once every 4 events
 *       arg TIM_ICPSC_DIV8: capture is done once every 8 events
 * retval None
 */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
    TIMx->CCMR2 &= (uint16_t) ~TIM_CCMR2_IC4PSC; /* Reset IC4PSC Bits */
    TIMx->CCMR2 |= (uint16_t) (TIM_ICPSC << 8); /* Set IC4PSC value */
}

/**
 * Configures Break feature, dead time, Lock level, OSSI/OSSR State
 * and AOE(automatic output enable).
 * param TIMx: where x can be  1 or 8 to select TIM 
 * param TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure that
 *       contains BDTR Register configuration  information for TIM peripheral.
 * retval None
 */
void TIM_BDTRConfig(
    TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct
) {
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
    assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
    assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
    assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
    assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
    assert_param(
        IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput)
    );
    /**
     * Set Lock level, Break enable Bit and Polarity, OSSR State,
     * OSSI State, dead time value and Automatic Output Enable Bit
     */
    TIMx->BDTR = (uint32_t) (
        TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
        TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
        TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
        TIM_BDTRInitStruct->TIM_AutomaticOutput
    );
}

/**
 * Fills each TIM_BDTRInitStruct member with its default value.
 * param TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef
 *       structure which will be initialized.
 * retval None
 */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct) {
    /* Set default configuration */
    TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
    TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
    TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
 * Enables or disables TIM peripheral Main Outputs.
 * param TIMx: where x can be 1 or 8 to select TIMx peripheral.
 * param NewState: new state of TIM peripheral Main Outputs.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->BDTR |= TIM_BDTR_MOE; /* Enable TIM Main Output */
    } else {
        TIMx->BDTR &= (uint16_t) ~TIM_BDTR_MOE; /* Disable TIM Main Output */
    }
}

/**
 * Selects TIM peripheral Commutation event.
 * param TIMx: where x can be  1 or 8 to select TIMx peripheral
 * param NewState: new state of Commutation event.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR2 |= TIM_CR2_CCUS; /* Set COM Bit */
    } else {
        TIMx->CR2 &= (uint16_t) ~TIM_CR2_CCUS; /* Reset COM Bit */
    }
}

/**
 * Sets or Resets TIM peripheral Capture Compare Preload Control bit.
 * param TIMx: where x can be  1 or 8 to select TIMx peripheral
 * param NewState: new state of Capture Compare Preload Control bit
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR2 |= TIM_CR2_CCPC; /* Set CCPC Bit */
    } else {
        TIMx->CR2 &= (uint16_t) ~TIM_CR2_CCPC; /* Reset CCPC Bit */
    }
}

/**
 * Enables or disables specified TIM interrupts.
 * param TIMx: where x can be 1 to 14 to select TIMx peripheral.
 * param TIM_IT: specifies TIM interrupts sources to be enabled or disabled.
 *   This parameter can be any combination of following values:
 *       arg TIM_IT_Update: TIM update Interrupt source
 *       arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 *       arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 *       arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 *       arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 *       arg TIM_IT_COM: TIM Commutation Interrupt source
 *       arg TIM_IT_Trigger: TIM Trigger Interrupt source
 *       arg TIM_IT_Break: TIM Break Interrupt source
 * For TIM6 and TIM7 only parameter TIM_IT_Update can be used
 * For TIM9 and TIM12 only one of following parameters can be used:
 * TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 or TIM_IT_Trigger.
 * For TIM10, TIM11, TIM13 and TIM14 only one of following parameters can
 * be used: TIM_IT_Update or TIM_IT_CC1
 * TIM_IT_COM and TIM_IT_Break can be used only with TIM1 and TIM8
 * param NewState: new state of TIM interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_ITConfig(
    TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState
) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_IT(TIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->DIER |= TIM_IT; /* Enable Interrupt sources */
    } else {
        TIMx->DIER &= (uint16_t) ~TIM_IT; /* Disable Interrupt sources */
    }
}

/**
 * Configures TIMx event to be generate by software.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_EventSource: specifies event source.
 *   This parameter can be one or more of following values:
 *       arg TIM_EventSource_Update: Timer update Event source
 *       arg TIM_EventSource_CC1: Timer Capture Compare 1 Event source
 *       arg TIM_EventSource_CC2: Timer Capture Compare 2 Event source
 *       arg TIM_EventSource_CC3: Timer Capture Compare 3 Event source
 *       arg TIM_EventSource_CC4: Timer Capture Compare 4 Event source
 *       arg TIM_EventSource_COM: Timer COM event source  
 *       arg TIM_EventSource_Trigger: Timer Trigger Event source
 *       arg TIM_EventSource_Break: Timer Break event source
 * TIM6 and TIM7 can only generate an update event.
 * TIM_EventSource_COM and TIM_EventSource_Break are used
 * only with TIM1 and TIM8.
 * retval None
 */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));
    TIMx->EGR = TIM_EventSource; /* Set event sources */
}

/**
 * Checks whether specified TIM flag is set or not.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_FLAG: specifies flag to check.
 *   This parameter can be one of following values:
 *       arg TIM_FLAG_Update: TIM update Flag
 *       arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
 *       arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
 *       arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
 *       arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
 *       arg TIM_FLAG_COM: TIM Commutation Flag
 *       arg TIM_FLAG_Trigger: TIM Trigger Flag
 *       arg TIM_FLAG_Break: TIM Break Flag
 *       arg TIM_FLAG_CC1OF: TIM Capture Compare 1 over capture Flag
 *       arg TIM_FLAG_CC2OF: TIM Capture Compare 2 over capture Flag
 *       arg TIM_FLAG_CC3OF: TIM Capture Compare 3 over capture Flag
 *       arg TIM_FLAG_CC4OF: TIM Capture Compare 4 over capture Flag
 * TIM6 and TIM7 can have only one update flag. 
 * TIM_FLAG_COM and TIM_FLAG_Break are used only with TIM1 and TIM8.
 * retval The new state of TIM_FLAG (SET or RESET).
 */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG) { 
    ITStatus bitstatus = RESET;

    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_GET_FLAG(TIM_FLAG));
    if ((TIMx->SR & TIM_FLAG) != (uint16_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
   return bitstatus;
}

/**
 * Clears TIMx's pending flags.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_FLAG: specifies flag bit to clear.
 *   This parameter can be any combination of following values:
 *       arg TIM_FLAG_Update: TIM update Flag
 *       arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
 *       arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
 *       arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
 *       arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
 *       arg TIM_FLAG_COM: TIM Commutation Flag
 *       arg TIM_FLAG_Trigger: TIM Trigger Flag
 *       arg TIM_FLAG_Break: TIM Break Flag
 *       arg TIM_FLAG_CC1OF: TIM Capture Compare 1 over capture Flag
 *       arg TIM_FLAG_CC2OF: TIM Capture Compare 2 over capture Flag
 *       arg TIM_FLAG_CC3OF: TIM Capture Compare 3 over capture Flag
 *       arg TIM_FLAG_CC4OF: TIM Capture Compare 4 over capture Flag
 * TIM6 and TIM7 can have only one update flag. 
 * TIM_FLAG_COM and TIM_FLAG_Break are used only with TIM1 and TIM8.
 * retval None
 */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    TIMx->SR = (uint16_t) ~TIM_FLAG; /* Clear flags */
}

/**
 * Checks whether TIM interrupt has occurred or not.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_IT: specifies TIM interrupt source to check.
 *   This parameter can be one of following values:
 *       arg TIM_IT_Update: TIM update Interrupt source
 *       arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 *       arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 *       arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 *       arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 *       arg TIM_IT_COM: TIM Commutation Interrupt source
 *       arg TIM_IT_Trigger: TIM Trigger Interrupt source
 *       arg TIM_IT_Break: TIM Break Interrupt source
 * TIM6 and TIM7 can generate only an update interrupt.
 * TIM_IT_COM and TIM_IT_Break are used only with TIM1 and TIM8.
 * retval The new state of TIM_IT(SET or RESET).
 */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT) {
    ITStatus bitstatus = RESET;
    uint16_t itstatus = 0x0, itenable = 0x0;

    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_GET_IT(TIM_IT));
    itstatus = TIMx->SR & TIM_IT;
    itenable = TIMx->DIER & TIM_IT;
    if ((itstatus != (uint16_t) RESET) && (itenable != (uint16_t) RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears TIMx's interrupt pending bits.
 * param TIMx: where x can be 1 to 14 to select TIM peripheral.
 * param TIM_IT: specifies pending bit to clear.
 *   This parameter can be any combination of following values:
 *       arg TIM_IT_Update: TIM1 update Interrupt source
 *       arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
 *       arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
 *       arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
 *       arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
 *       arg TIM_IT_COM: TIM Commutation Interrupt source
 *       arg TIM_IT_Trigger: TIM Trigger Interrupt source
 *       arg TIM_IT_Break: TIM Break Interrupt source
 * TIM6 and TIM7 can generate only an update interrupt.
 * TIM_IT_COM and TIM_IT_Break are used only with TIM1 and TIM8.
 * retval None
 */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT) {
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    TIMx->SR = (uint16_t) ~TIM_IT; /* Clear IT pending Bit */
}

/**
 * Configures TIMx's DMA interface.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_DMABase: DMA Base address.
 *   This parameter can be one of following values:
 *       arg TIM_DMABase_CR1
 *       arg TIM_DMABase_CR2
 *       arg TIM_DMABase_SMCR
 *       arg TIM_DMABase_DIER
 *       arg TIM1_DMABase_SR
 *       arg TIM_DMABase_EGR
 *       arg TIM_DMABase_CCMR1
 *       arg TIM_DMABase_CCMR2
 *       arg TIM_DMABase_CCER
 *       arg TIM_DMABase_CNT
 *       arg TIM_DMABase_PSC
 *       arg TIM_DMABase_ARR
 *       arg TIM_DMABase_RCR
 *       arg TIM_DMABase_CCR1
 *       arg TIM_DMABase_CCR2
 *       arg TIM_DMABase_CCR3
 *       arg TIM_DMABase_CCR4
 *       arg TIM_DMABase_BDTR
 *       arg TIM_DMABase_DCR
 * param TIM_DMABurstLength: DMA Burst length. This parameter can be one value
 *       between: TIM_DMABurstLength_1Transfer and
 *       TIM_DMABurstLength_18Transfers.
 * retval None
 */
void TIM_DMAConfig(
    TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength
) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_DMA_BASE(TIM_DMABase)); 
    assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));
    /* Set DMA Base and DMA Burst Length */
    TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
 * Enables or disables TIMx's DMA Requests.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 6, 7 or 8
 *       to select TIM peripheral
 * param TIM_DMASource: specifies DMA Request sources.
 *   This parameter can be any combination of following values:
 *       arg TIM_DMA_Update: TIM update Interrupt source
 *       arg TIM_DMA_CC1: TIM Capture Compare 1 DMA source
 *       arg TIM_DMA_CC2: TIM Capture Compare 2 DMA source
 *       arg TIM_DMA_CC3: TIM Capture Compare 3 DMA source
 *       arg TIM_DMA_CC4: TIM Capture Compare 4 DMA source
 *       arg TIM_DMA_COM: TIM Commutation DMA source
 *       arg TIM_DMA_Trigger: TIM Trigger DMA source
 * param NewState: new state of DMA Request sources.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_DMACmd(
    TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState
) {
    assert_param(IS_TIM_LIST5_PERIPH(TIMx)); 
    assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->DIER |= TIM_DMASource; /* Enable DMA sources */
    } else {
        TIMx->DIER &= (uint16_t) ~TIM_DMASource; /* Disable DMA sources */
    }
}

/**
 * Selects TIMx peripheral Capture Compare DMA source.
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param NewState: new state of Capture Compare DMA source
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR2 |= TIM_CR2_CCDS; /* Set CCDS Bit */
    } else {
        TIMx->CR2 &= (uint16_t) ~TIM_CR2_CCDS; /* Reset CCDS Bit */
    }
}

/**
 * Configures TIMx internal Clock
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * retval None
 */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    /* Disable slave mode to clock prescaler directly with internal clock */
    TIMx->SMCR &=  (uint16_t) ~TIM_SMCR_SMS;
}

/**
 * Configures TIMx Internal Trigger as External Clock
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_InputTriggerSource: Trigger source.
 *   This parameter can be one of following values:
 *       arg TIM_TS_ITR0: Internal Trigger 0
 *       arg TIM_TS_ITR1: Internal Trigger 1
 *       arg TIM_TS_ITR2: Internal Trigger 2
 *       arg TIM_TS_ITR3: Internal Trigger 3
 * retval None
 */
void TIM_ITRxExternalClockConfig(
    TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource
) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));
    /* Select Internal Trigger */
    TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
    /* Select External clock mode1 */
    TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
 * Configures TIMx Trigger as External Clock
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
 *       to select TIM peripheral.
 * param TIM_TIxExternalCLKSource: Trigger source.
 *   This parameter can be one of following values:
 *       arg TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
 *       arg TIM_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
 *       arg TIM_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
 * param TIM_ICPolarity: specifies TIx Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Rising
 *       arg TIM_ICPolarity_Falling
 * param ICFilter: specifies filter value.
 *   This parameter must be a value between 0x0 and 0xF.
 * retval None
 */
void TIM_TIxExternalClockConfig(
    TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
    uint16_t TIM_ICPolarity, uint16_t ICFilter
) {
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
    assert_param(IS_TIM_IC_FILTER(ICFilter));
    /* Configure Timer Input Clock Source */
    if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2) {
        TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    } else {
        TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    }
    /* Select Trigger source */
    TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
    TIMx->SMCR |= TIM_SlaveMode_External1; /* Select External clock mode1 */
}

/**
 * Configures External clock Mode1
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ExtTRGPrescaler: The external Trigger Prescaler.
 *   This parameter can be one of following values:
 *       arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
 *       arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
 *       arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
 *       arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
 * param TIM_ExtTRGPolarity: The external Trigger Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
 *       arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
 * param ExtTRGFilter: External Trigger Filter.
 *   This parameter must be a value between 0x00 and 0x0F
 * retval None
 */
void TIM_ETRClockMode1Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
    uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter
) {
    uint16_t tmpsmcr = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
    /* Configure ETR Clock source */
    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
    tmpsmcr = TIMx->SMCR; /* Get TIMx SMCR register value */
    tmpsmcr &= (uint16_t) ~TIM_SMCR_SMS; /* Reset SMS Bits */
    tmpsmcr |= TIM_SlaveMode_External1; /* Select External clock mode1 */
    tmpsmcr &= (uint16_t) ~TIM_SMCR_TS; /* Select Trigger selection : ETRF */
    tmpsmcr |= TIM_TS_ETRF;
    TIMx->SMCR = tmpsmcr; /* Write to TIMx SMCR */
}

/**
 * Configures External clock Mode2
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ExtTRGPrescaler: The external Trigger Prescaler.
 *   This parameter can be one of following values:
 *       arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
 *       arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
 *       arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
 *       arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
 * param TIM_ExtTRGPolarity: The external Trigger Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
 *       arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
 * param ExtTRGFilter: External Trigger Filter.
 *   This parameter must be a value between 0x00 and 0x0F
 * retval None
 */
void TIM_ETRClockMode2Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
    uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter
) {
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
    /* Configure ETR Clock source */
    TIM_ETRConfig(
        TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter
    );
    TIMx->SMCR |= TIM_SMCR_ECE; /* Enable External clock mode2 */
}

/**
 * Selects Input Trigger source
 * param TIMx: where x can be  1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
 *       to select TIM peripheral.
 * param TIM_InputTriggerSource: The Input Trigger source.
 *   This parameter can be one of following values:
 *       arg TIM_TS_ITR0: Internal Trigger 0
 *       arg TIM_TS_ITR1: Internal Trigger 1
 *       arg TIM_TS_ITR2: Internal Trigger 2
 *       arg TIM_TS_ITR3: Internal Trigger 3
 *       arg TIM_TS_TI1F_ED: TI1 Edge Detector
 *       arg TIM_TS_TI1FP1: Filtered Timer Input 1
 *       arg TIM_TS_TI2FP2: Filtered Timer Input 2
 *       arg TIM_TS_ETRF: External Trigger input
 * retval None
 */
void TIM_SelectInputTrigger(
    TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource
) {
    uint16_t tmpsmcr = 0;

    assert_param(IS_TIM_LIST1_PERIPH(TIMx)); 
    assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));
    tmpsmcr = TIMx->SMCR; /* Get TIMx SMCR register value */
    tmpsmcr &= (uint16_t) ~TIM_SMCR_TS; /* Reset TS Bits */
    tmpsmcr |= TIM_InputTriggerSource; /* Set Input Trigger source */
    TIMx->SMCR = tmpsmcr; /* Write to TIMx SMCR */
}

/**
 * Selects TIMx Trigger Output Mode.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 6, 7 or 8
 *       to select TIM peripheral.
 * param TIM_TRGOSource: specifies Trigger Output source.
 *   This parameter can be one of following values:
 *  - For all TIMx
 *     arg TIM_TRGOSource_Reset: The UG bit in TIM_EGR register
 *         is used as trigger output(TRGO)
 *     arg TIM_TRGOSource_Enable: The Counter Enable CEN is used
 *         as trigger output(TRGO)
 *     arg TIM_TRGOSource_Update: The update event is selected
 *         as trigger output(TRGO)
 *  - For all TIMx except TIM6 and TIM7
 *     arg TIM_TRGOSource_OC1: The trigger output sends a positive
 *         pulse when CC1IF flag is to be set, as soon as a capture or
 *         compare match occurs(TRGO)
 *     arg TIM_TRGOSource_OC1Ref: OC1REF signal is used as trigger output(TRGO)
 *     arg TIM_TRGOSource_OC2Ref: OC2REF signal is used as trigger output(TRGO)
 *     arg TIM_TRGOSource_OC3Ref: OC3REF signal is used as trigger output(TRGO)
 *     arg TIM_TRGOSource_OC4Ref: OC4REF signal is used as trigger output(TRGO)
 * retval None
 */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource) {
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));
    TIMx->CR2 &= (uint16_t) ~TIM_CR2_MMS; /* Reset MMS Bits */
    TIMx->CR2 |= TIM_TRGOSource; /* Select TRGO source */
}

/**
 * Selects TIMx Slave Mode.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_SlaveMode: specifies Timer Slave Mode.
 *   This parameter can be one of following values:
 *       arg TIM_SlaveMode_Reset: Rising edge of selected trigger
 *           signal(TRGI) reinitialize counter and triggers an update
 *           of registers
 *       arg TIM_SlaveMode_Gated: The counter clock is enabled when
 *           trigger signal (TRGI) is high
 *       arg TIM_SlaveMode_Trigger: The counter starts at a rising
 *           edge of trigger TRGI
 *       arg TIM_SlaveMode_External1: Rising edges of selected
 *           trigger (TRGI) clock counter
 * retval None
 */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));
    TIMx->SMCR &= (uint16_t) ~TIM_SMCR_SMS; /* Reset SMS Bits */
    TIMx->SMCR |= TIM_SlaveMode; /* Select Slave Mode */
}

/**
 * Sets or Resets TIMx Master/Slave Mode.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_MasterSlaveMode: specifies Timer Master Slave Mode.
 *   This parameter can be one of following values:
 *       arg TIM_MasterSlaveMode_Enable: synchronization between current timer
 *           and its slaves (through TRGO)
 *       arg TIM_MasterSlaveMode_Disable: No action
 * retval None
 */
void TIM_SelectMasterSlaveMode(
    TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode
) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));
    TIMx->SMCR &= (uint16_t) ~TIM_SMCR_MSM; /* Reset MSM Bit */
    TIMx->SMCR |= TIM_MasterSlaveMode; /* Set or Reset MSM Bit */
}

/**
 * Configures TIMx External Trigger (ETR).
 * param TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ExtTRGPrescaler: The external Trigger Prescaler.
 *   This parameter can be one of following values:
 *       arg TIM_ExtTRGPSC_OFF: ETRP Prescaler OFF.
 *       arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
 *       arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
 *       arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
 * param TIM_ExtTRGPolarity: The external Trigger Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
 *       arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
 * param ExtTRGFilter: External Trigger Filter.
 *   This parameter must be a value between 0x00 and 0x0F
 * retval None
 */
void TIM_ETRConfig(
    TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
    uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter
){
    uint16_t tmpsmcr = 0;

    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
    tmpsmcr = TIMx->SMCR;
    tmpsmcr &= SMCR_ETR_MASK; /* Reset ETR Bits */
    /* Set Prescaler, Filter value and Polarity */
    tmpsmcr |= (uint16_t) (
        TIM_ExtTRGPrescaler | (uint16_t) (
            TIM_ExtTRGPolarity | (uint16_t) (ExtTRGFilter << (uint16_t) 8)
        )
    );
    TIMx->SMCR = tmpsmcr; /* Write to TIMx SMCR */
}

/**
 * Configures TIMx Encoder Interface.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_EncoderMode: specifies TIMx Encoder Mode.
 *   This parameter can be one of following values:
 *       arg TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge
 *           depending on TI2FP2 level.
 *       arg TIM_EncoderMode_TI2: Counter counts on TI2FP2 edge
 *           depending on TI1FP1 level.
 *       arg TIM_EncoderMode_TI12: Counter counts on both
 *           TI1FP1 and TI2FP2 edges depending on level
 *           of other input.
 * param TIM_IC1Polarity: specifies IC1 Polarity
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Falling: IC Falling edge.
 *       arg TIM_ICPolarity_Rising: IC Rising edge.
 * param TIM_IC2Polarity: specifies IC2 Polarity
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Falling: IC Falling edge.
 *       arg TIM_ICPolarity_Rising: IC Rising edge.
 * retval None
 */
void TIM_EncoderInterfaceConfig(
    TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
    uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity
) {
    uint16_t tmpsmcr = 0;
    uint16_t tmpccmr1 = 0;
    uint16_t tmpccer = 0;

    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
    assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
    assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));
    tmpsmcr = TIMx->SMCR; /* Get TIMx SMCR register value */
    tmpccmr1 = TIMx->CCMR1; /* Get TIMx CCMR1 register value */
    tmpccer = TIMx->CCER; /* Get TIMx CCER register value */
    tmpsmcr &= (uint16_t) ~TIM_SMCR_SMS; /* Set encoder Mode */
    tmpsmcr |= TIM_EncoderMode;
    /* Select Capture Compare 1 and Capture Compare 2 as input */
    tmpccmr1 &= ((uint16_t) ~TIM_CCMR1_CC1S) & ((uint16_t) ~TIM_CCMR1_CC2S);
    tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
    /* Set TI1 and TI2 Polarities */
    tmpccer &= ((uint16_t) ~TIM_CCER_CC1P) & ((uint16_t) ~TIM_CCER_CC2P);
    tmpccer |= (uint16_t) (
        TIM_IC1Polarity | (uint16_t) (TIM_IC2Polarity << (uint16_t) 4)
    );
    TIMx->SMCR = tmpsmcr; /* Write to TIMx SMCR */
    TIMx->CCMR1 = tmpccmr1; /* Write to TIMx CCMR1 */
    TIMx->CCER = tmpccer; /* Write to TIMx CCER */
}

/**
 * Enables or disables TIMx's Hall sensor interface.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to
 *       select TIM peripheral.
 * param NewState: new state of TIMx Hall sensor interface.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState) {
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        TIMx->CR2 |= TIM_CR2_TI1S; /* Set TI1S Bit */
    } else {
        TIMx->CR2 &= (uint16_t) ~TIM_CR2_TI1S; /* Reset TI1S Bit */
    }
}

/**
 * Configures TIM2, TIM5 and TIM11 Remapping input capabilities.
 * param TIMx: where x can be 2, 5 or 11 to select TIM peripheral.
 * param TIM_Remap: specifies TIM input remapping source.
 *   This parameter can be one of following values:
 *       arg TIM2_TIM8_TRGO: TIM2 ITR1 input is connected
 *           to TIM8 Trigger output(default)
 *       arg TIM2_ETH_PTP: TIM2 ITR1 input is connected to
 *           ETH PTP trogger output.
 *       arg TIM2_USBFS_SOF: TIM2 ITR1 input is connected to USB FS SOF.
 *       arg TIM2_USBHS_SOF: TIM2 ITR1 input is connected to USB HS SOF.
 *       arg TIM5_GPIO: TIM5 CH4 input is connected to
 *           dedicated Timer pin(default)
 *       arg TIM5_LSI: TIM5 CH4 input is connected to LSI clock.
 *       arg TIM5_LSE: TIM5 CH4 input is connected to LSE clock.
 *       arg TIM5_RTC: TIM5 CH4 input is connected to RTC Output event.
 *       arg TIM11_GPIO: TIM11 CH4 input is connected to dedicated
 *           Timer pin(default)
 *       arg TIM11_HSE: TIM11 CH4 input is connected to HSE_RTC clock
 *           (HSE divided by a programmable prescaler)
 * retval None
 */
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint16_t TIM_Remap) {
    assert_param(IS_TIM_LIST6_PERIPH(TIMx));
    assert_param(IS_TIM_REMAP(TIM_Remap));
    TIMx->OR =  TIM_Remap; /* Set Timer remapping configuration */
}

/**
 * Configure TI1 as Input.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
 *       to select TIM peripheral.
 * param TIM_ICPolarity : The Input Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Rising
 *       arg TIM_ICPolarity_Falling
 *       arg TIM_ICPolarity_BothEdge  
 * param TIM_ICSelection: specifies input to be used.
 *   This parameter can be one of following values:
 *       arg TIM_ICSelection_DirectTI: TIM Input 1 is selected
 *           to be connected to IC1.
 *       arg TIM_ICSelection_IndirectTI: TIM Input 1 is selected
 *           to be connected to IC2.
 *       arg TIM_ICSelection_TRC: TIM Input 1 is selected
 *           to be connected to TRC.
 * param TIM_ICFilter: Specifies Input Capture Filter.
 *   This parameter must be a value between 0x00 and 0x0F.
 * retval None
 */
static void TI1_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
) {
    uint16_t tmpccmr1 = 0, tmpccer = 0;

    /* Disable Channel 1: Reset CC1E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC1E;
    tmpccmr1 = TIMx->CCMR1;
    tmpccer = TIMx->CCER;
    /* Select Input and set filter */
    tmpccmr1 &= ((uint16_t) ~TIM_CCMR1_CC1S) & ((uint16_t) ~TIM_CCMR1_IC1F);
    tmpccmr1 |= (uint16_t) (
        TIM_ICSelection | (uint16_t) (TIM_ICFilter << (uint16_t) 4)
    );
    /* Select Polarity and set CC1E Bit */
    tmpccer &= (uint16_t) ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
    tmpccer |= (uint16_t) (TIM_ICPolarity | (uint16_t) TIM_CCER_CC1E);
    /* Write to TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

/**
 * Configure TI2 as Input.
 * param TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12
 *       to select TIM peripheral.
 * param TIM_ICPolarity : The Input Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Rising
 *       arg TIM_ICPolarity_Falling
 *       arg TIM_ICPolarity_BothEdge   
 * param TIM_ICSelection: specifies input to be used.
 *   This parameter can be one of following values:
 *       arg TIM_ICSelection_DirectTI: TIM Input 2 is selected
 *           to be connected to IC2.
 *       arg TIM_ICSelection_IndirectTI: TIM Input 2 is selected
 *           to be connected to IC1.
 *       arg TIM_ICSelection_TRC: TIM Input 2 is selected
 *           to be connected to TRC.
 * param TIM_ICFilter: Specifies Input Capture Filter.
 *   This parameter must be a value between 0x00 and 0x0F.
 * retval None
 */
static void TI2_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
) {
    uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

    /* Disable Channel 2: Reset CC2E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC2E;
    tmpccmr1 = TIMx->CCMR1;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t) (TIM_ICPolarity << 4);
    /* Select Input and set filter */
    tmpccmr1 &= ((uint16_t) ~TIM_CCMR1_CC2S) & ((uint16_t) ~TIM_CCMR1_IC2F);
    tmpccmr1 |= (uint16_t) (TIM_ICFilter << 12);
    tmpccmr1 |= (uint16_t) (TIM_ICSelection << 8);
    /* Select Polarity and set CC2E Bit */
    tmpccer &= (uint16_t) ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
    tmpccer |=  (uint16_t) (tmp | (uint16_t) TIM_CCER_CC2E);
    /* Write to TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1 ;
    TIMx->CCER = tmpccer;
}

/**
 * Configure TI3 as Input.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ICPolarity : The Input Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Rising
 *       arg TIM_ICPolarity_Falling
 *       arg TIM_ICPolarity_BothEdge
 * param TIM_ICSelection: specifies input to be used.
 *   This parameter can be one of following values:
 *       arg TIM_ICSelection_DirectTI: TIM Input 3 is selected
 *           to be connected to IC3.
 *       arg TIM_ICSelection_IndirectTI: TIM Input 3 is selected
 *           to be connected to IC4.
 *       arg TIM_ICSelection_TRC: TIM Input 3 is selected
 *           to be connected to TRC.
 * param TIM_ICFilter: Specifies Input Capture Filter.
 *   This parameter must be a value between 0x00 and 0x0F.
 * retval None
 */
static void TI3_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
) {
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* Disable Channel 3: Reset CC3E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC3E;
    tmpccmr2 = TIMx->CCMR2;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t) (TIM_ICPolarity << 8);
    /* Select Input and set filter */
    tmpccmr2 &= ((uint16_t) ~TIM_CCMR1_CC1S) & ((uint16_t) ~TIM_CCMR2_IC3F);
    tmpccmr2 |= (uint16_t) (
        TIM_ICSelection | (uint16_t) (TIM_ICFilter << (uint16_t) 4)
    );
    /* Select Polarity and set CC3E Bit */
    tmpccer &= (uint16_t) ~(TIM_CCER_CC3P | TIM_CCER_CC3NP);
    tmpccer |= (uint16_t) (tmp | (uint16_t) TIM_CCER_CC3E);
    /* Write to TIMx CCMR2 and CCER registers */
    TIMx->CCMR2 = tmpccmr2;
    TIMx->CCER = tmpccer;
}

/**
 * Configure TI4 as Input.
 * param TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select TIM peripheral.
 * param TIM_ICPolarity : The Input Polarity.
 *   This parameter can be one of following values:
 *       arg TIM_ICPolarity_Rising
 *       arg TIM_ICPolarity_Falling
 *       arg TIM_ICPolarity_BothEdge
 * param TIM_ICSelection: specifies input to be used.
 *   This parameter can be one of following values:
 *       arg TIM_ICSelection_DirectTI: TIM Input 4 is selected
 *           to be connected to IC4.
 *       arg TIM_ICSelection_IndirectTI: TIM Input 4 is selected
 *           to be connected to IC3.
 *       arg TIM_ICSelection_TRC: TIM Input 4 is selected
 *           to be connected to TRC.
 * param TIM_ICFilter: Specifies Input Capture Filter.
 *   This parameter must be a value between 0x00 and 0x0F.
 * retval None
 */
static void TI4_Config(
    TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
    uint16_t TIM_ICFilter
) {
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* Disable Channel 4: Reset CC4E Bit */
    TIMx->CCER &= (uint16_t) ~TIM_CCER_CC4E;
    tmpccmr2 = TIMx->CCMR2;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t) (TIM_ICPolarity << 12);
    /* Select Input and set filter */
    tmpccmr2 &= ((uint16_t) ~TIM_CCMR1_CC2S) & ((uint16_t) ~TIM_CCMR1_IC2F);
    tmpccmr2 |= (uint16_t) (TIM_ICSelection << 8);
    tmpccmr2 |= (uint16_t) (TIM_ICFilter << 12);
    /* Select Polarity and set CC4E Bit */
    tmpccer &= (uint16_t) ~(TIM_CCER_CC4P | TIM_CCER_CC4NP);
    tmpccer |= (uint16_t) (tmp | (uint16_t) TIM_CCER_CC4E);
    TIMx->CCMR2 = tmpccmr2; /* Write to TIMx CCMR2 and CCER registers */
    TIMx->CCER = tmpccer ;
}

