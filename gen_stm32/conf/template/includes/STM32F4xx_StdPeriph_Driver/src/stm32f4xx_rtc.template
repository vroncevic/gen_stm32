/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * stm32f4xx_rtc.c
 * 
 * This file provides firmware functions to manage following
 * functionalities of Real-Time Clock (RTC) peripheral:
 *     - Initialization
 *     - Calendar (Time and Date) configuration
 *     - Alarms (Alarm A and Alarm B) configuration
 *     - WakeUp Timer configuration
 *     - Daylight Saving configuration
 *     - Output pin Configuration
 *     - Coarse digital Calibration configuration
 *     - Smooth digital Calibration configuration
 *     - TimeStamp configuration
 *     - Tampers configuration
 *     - Backup Data Registers configuration
 *     - Shift control synchronisation
 *     - RTC Tamper and TimeStamp Pins Selection and Output
 *       Type Config configuration
 *     - Interrupts and flags management
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_rtc is free software: you can redistribute it and/or modify
 * it under terms of GNU General Public License as published by the
 * Free Software Foundation, either version 3 of License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_rtc is distributed in hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See GNU General Public License for more details.
 * See ARM License for more details.
 *
 * You should have received a copy of GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_rtc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"

/* Masks Definition */
#define RTC_TR_RESERVED_MASK ((uint32_t) 0x007F7F7F)
#define RTC_DR_RESERVED_MASK ((uint32_t) 0x00FFFF3F)
#define RTC_INIT_MASK ((uint32_t) 0xFFFFFFFF)
#define RTC_RSF_MASK ((uint32_t) 0xFFFFFF5F)

#define RTC_FLAGS_MASK ((uint32_t) \
    (RTC_FLAG_TSOVF | RTC_FLAG_TSF | RTC_FLAG_WUTF | \
    RTC_FLAG_ALRBF | RTC_FLAG_ALRAF | RTC_FLAG_INITF | \
    RTC_FLAG_RSF | RTC_FLAG_INITS | RTC_FLAG_WUTWF | \
    RTC_FLAG_ALRBWF | RTC_FLAG_ALRAWF | RTC_FLAG_TAMP1F ) \
)

#define INITMODE_TIMEOUT ((uint32_t) 0x00010000)
#define SYNCHRO_TIMEOUT ((uint32_t) 0x00020000)
#define RECALPF_TIMEOUT ((uint32_t) 0x00020000)
#define SHPF_TIMEOUT ((uint32_t) 0x00001000)

static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/**
 * Deinitializes RTC registers to their default reset values.
 * This function doesn't reset RTC Clock source and RTC Backup Data
 * registers.
 * param None
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC registers are deinitialized
 *     - ERROR: RTC registers are not deinitialized
 */
ErrorStatus RTC_DeInit(void) {
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus = 0x00;
    ErrorStatus status = ERROR;

    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* Reset TR, DR and CR registers */
        RTC->TR = (uint32_t) 0x00000000;
        RTC->DR = (uint32_t) 0x00002101;
        /* Reset All CR bits except CR[2:0] */
        RTC->CR &= (uint32_t) 0x00000007;
        /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
        do {
            wutwfstatus = RTC->ISR & RTC_ISR_WUTWF;
            wutcounter++;
        } while((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));
        if ((RTC->ISR & RTC_ISR_WUTWF) == RESET) {
            status = ERROR;
        } else {
            /* Reset all RTC CR register bits */
            RTC->CR &= (uint32_t) 0x00000000;
            RTC->WUTR = (uint32_t) 0x0000FFFF;
            RTC->PRER = (uint32_t) 0x007F00FF;
            RTC->CALIBR = (uint32_t) 0x00000000;
            RTC->ALRMAR = (uint32_t) 0x00000000;
            RTC->ALRMBR = (uint32_t) 0x00000000;
            /* Reset ISR register and exit initialization mode */
            RTC->ISR = (uint32_t) 0x00000000;
            /* Reset Tamper and alternate functions configuration register */
            RTC->TAFCR = 0x00000000;
            if(RTC_WaitForSynchro() == ERROR) {
                status = ERROR;
            } else {
                status = SUCCESS;
            }
        }
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Initializes RTC registers according to specified parameters 
 * in RTC_InitStruct.
 * param RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains
 *       configuration information for RTC peripheral.
 * The RTC Prescaler register is write protected and can be written in 
 * initialization mode only.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC registers are initialized
 *     - ERROR: RTC registers are not initialized 
 */
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct) {
    ErrorStatus status = ERROR;

    assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
    assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));
    assert_param(IS_RTC_SYNCH_PREDIV(RTC_InitStruct->RTC_SynchPrediv));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        RTC->CR &= ((uint32_t) ~(RTC_CR_FMT)); /* Clear RTC CR FMT Bit */
        /* Set RTC_CR register */
        RTC->CR |=  ((uint32_t) (RTC_InitStruct->RTC_HourFormat));
        /* Configure RTC PRER */
        RTC->PRER = (uint32_t) (RTC_InitStruct->RTC_SynchPrediv);
        RTC->PRER |= (uint32_t) (RTC_InitStruct->RTC_AsynchPrediv << 16);
        RTC_ExitInitMode(); /* Exit Initialization mode */
        status = SUCCESS;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Fills each RTC_InitStruct member with its default value.
 * param RTC_InitStruct: pointer to a RTC_InitTypeDef structure
 *       which will be initialized.
 * retval None
 */
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct) {
    /* Initialize RTC_HourFormat member */
    RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24;
    /* Initialize RTC_AsynchPrediv member */
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t) 0x7F;
    /* Initialize RTC_SynchPrediv member */
    RTC_InitStruct->RTC_SynchPrediv = (uint32_t) 0xFF;
}

/**
 * Enables or disables RTC registers write protection.
 * All RTC registers are write protected except for RTC_ISR[13:8],
 * RTC_TAFCR and RTC_BKPxR.
 * Writing a wrong key reactivates write protection.
 * The protection mechanism is not affected by system reset.
 * param NewState: new state of write protection.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_WriteProtectionCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    } else {
        /* Disable write protection for RTC registers */
        RTC->WPR = 0xCA;
        RTC->WPR = 0x53;
    }
}

/**
 * Enters RTC Initialization mode.
 * The RTC Initialization mode is write protected, use 
 * RTC_WriteProtectionCmd(DISABLE) before calling this function.
 * param None
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC is in Init mode
 *     - ERROR: RTC is not in Init mode 
 */
ErrorStatus RTC_EnterInitMode(void) {
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status = ERROR;
    uint32_t initstatus = 0x00;

    /* Check if Initialization mode is set */
    if ((RTC->ISR & RTC_ISR_INITF) == (uint32_t) RESET) {
        /* Set Initialization mode */
        RTC->ISR = (uint32_t) RTC_INIT_MASK;
        /* Wait till RTC is in INIT state and if Time out is reached exit */
        do {
            initstatus = RTC->ISR & RTC_ISR_INITF;
            initcounter++;
        } while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));
        if ((RTC->ISR & RTC_ISR_INITF) != RESET) {
            status = SUCCESS;
        } else {
            status = ERROR;
        }
    } else {
        status = SUCCESS;
    }
    return (status);
}

/**
 * Exits RTC Initialization mode.
 * When initialization sequence is complete, calendar restarts
 * counting after 4 RTCCLK cycles.  
 * The RTC Initialization mode is write protected, use 
 * RTC_WriteProtectionCmd(DISABLE) before calling this function.
 * param None
 * retval None
 */
void RTC_ExitInitMode(void) {
    RTC->ISR &= (uint32_t)~RTC_ISR_INIT; /* Exit Initialization mode */
}

/**
 * Waits until RTC Time and Date registers (RTC_TR and RTC_DR) are 
 * synchronized with RTC APB clock.
 * The RTC Resynchronization mode is write protected, use 
 * RTC_WriteProtectionCmd(DISABLE) before calling this function. 
 * To read calendar through shadow registers after Calendar 
 * initialization, calendar update or after wakeup from low power modes 
 * software must first clear RSF flag. 
 * The software must then wait until it is set again before reading 
 * calendar, which means that calendar registers have been 
 * correctly copied into RTC_TR and RTC_DR shadow registers.
 * param None
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC registers are synchronised
 *     - ERROR: RTC registers are not synchronised
 */
ErrorStatus RTC_WaitForSynchro(void) {
    __IO uint32_t synchrocounter = 0;
    ErrorStatus status = ERROR;
    uint32_t synchrostatus = 0x00;

    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    RTC->ISR &= (uint32_t)RTC_RSF_MASK; /* Clear RSF flag */
    /* Wait registers to be synchronised */
    do {
        synchrostatus = RTC->ISR & RTC_ISR_RSF;
        synchrocounter++;  
    } while((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));
    if ((RTC->ISR & RTC_ISR_RSF) != RESET) {
        status = SUCCESS;
    } else {
        status = ERROR;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
  return (status); 
}

/**
 * Enables or disables RTC reference clock detection.
 * param NewState: new state of RTC reference clock.
 *   This parameter can be: ENABLE or DISABLE.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC reference clock detection is enabled
 *     - ERROR: RTC reference clock detection is disabled 
 */
ErrorStatus RTC_RefClockCmd(FunctionalState NewState) { 
    ErrorStatus status = ERROR;

    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        if (NewState != DISABLE) {
            /* Enable RTC reference clock detection */
            RTC->CR |= RTC_CR_REFCKON;
        } else {
            /* Disable RTC reference clock detection */
            RTC->CR &= ~RTC_CR_REFCKON;
        }
        RTC_ExitInitMode(); /* Exit Initialization mode */
        status = SUCCESS;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status; 
}

/**
 * Enables or Disables Bypass Shadow feature.
 * When Bypass Shadow is enabled calendar value are taken
 * directly from Calendar counter.
 * param NewState: new state of Bypass Shadow feature.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
*/
void RTC_BypassShadowCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    if (NewState != DISABLE) {
        /* Set BYPSHAD bit */
        RTC->CR |= (uint8_t) RTC_CR_BYPSHAD;
    } else {
        /* Reset BYPSHAD bit */
        RTC->CR &= (uint8_t) ~RTC_CR_BYPSHAD;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Set RTC current time.
 * param RTC_Format: specifies format of entered parameters.
 *   This parameter can be  one of following values:
 *       arg RTC_Format_BIN:  Binary data format 
 *       arg RTC_Format_BCD:  BCD data format
 * param RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that
 *       contains time configuration information for RTC.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Time register is configured
 *     - ERROR: RTC Time register is not configured
 */
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct) {
    uint32_t tmpreg = 0;
    ErrorStatus status = ERROR;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    if (RTC_Format == RTC_Format_BIN) {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t) RESET) {
            assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        } else {
            RTC_TimeStruct->RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
        }
        assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
        assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
    } else {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t) RESET) {
            tmpreg = RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        } else {
            RTC_TimeStruct->RTC_H12 = 0x00;
            assert_param(
                IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours))
            );
        }
        assert_param(
            IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes))
        );
        assert_param(
            IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds))
        );
    }
    /* Check input parameters format */
    if (RTC_Format != RTC_Format_BIN) {
        tmpreg = (
            ((uint32_t) (RTC_TimeStruct->RTC_Hours) << 16) |
            ((uint32_t) (RTC_TimeStruct->RTC_Minutes) << 8) |
            ((uint32_t) RTC_TimeStruct->RTC_Seconds) |
            ((uint32_t) (RTC_TimeStruct->RTC_H12) << 16)
        );
    } else {
        tmpreg = (uint32_t) (
            ((uint32_t) RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16) |
            ((uint32_t) RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) |
            ((uint32_t) RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)) |
            (((uint32_t) RTC_TimeStruct->RTC_H12) << 16)
        );
    }
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
    status = ERROR;
    } else {
        /* Set RTC_TR register */
        RTC->TR = (uint32_t) (tmpreg & RTC_TR_RESERVED_MASK);
        RTC_ExitInitMode(); /* Exit Initialization mode */
        if (RTC_WaitForSynchro() == ERROR) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Fills each RTC_TimeStruct member with its default value
 * (Time = 00h:00min:00sec).
 * param RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure
 *       which will be initialized.
 * retval None
 */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct) {
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
    RTC_TimeStruct->RTC_Hours = 0;
    RTC_TimeStruct->RTC_Minutes = 0;
    RTC_TimeStruct->RTC_Seconds = 0; 
}

/**
 * Get RTC current Time.
 * param RTC_Format: specifies format of returned parameters.
 *   This parameter can be  one of following values:
 *       arg RTC_Format_BIN: Binary data format 
 *       arg RTC_Format_BCD: BCD data format
 * param RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will 
 *       contain returned current time configuration.
 * retval None
 */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    /* Get RTC_TR register */
    tmpreg = (uint32_t) (RTC->TR & RTC_TR_RESERVED_MASK);
    /* Fill structure fields with read parameters */
    RTC_TimeStruct->RTC_Hours = (uint8_t) (
        (tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> 16
    );
    RTC_TimeStruct->RTC_Minutes = (uint8_t) (
        (tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >>8
    );
    RTC_TimeStruct->RTC_Seconds = (uint8_t) (tmpreg & (RTC_TR_ST | RTC_TR_SU));
    RTC_TimeStruct->RTC_H12 = (uint8_t) ((tmpreg & (RTC_TR_PM)) >> 16);
    /* Check input parameters format */
    if (RTC_Format == RTC_Format_BIN) {
        /* Convert structure parameters to Binary format */
        RTC_TimeStruct->RTC_Hours = (uint8_t) RTC_Bcd2ToByte(
            RTC_TimeStruct->RTC_Hours
        );
        RTC_TimeStruct->RTC_Minutes = (uint8_t) RTC_Bcd2ToByte(
            RTC_TimeStruct->RTC_Minutes
        );
        RTC_TimeStruct->RTC_Seconds = (uint8_t) RTC_Bcd2ToByte(
            RTC_TimeStruct->RTC_Seconds
        );
    }
}

/**
 * Gets RTC current Calendar Subseconds value.
 * This function freeze Time and Date registers after reading
 * SSR register.
 * param None
 * retval RTC current Calendar Subseconds value.
 */
uint32_t RTC_GetSubSecond(void) {
    uint32_t tmpreg = 0;

    /* Get subseconds values from correspondent registers*/
    tmpreg = (uint32_t) (RTC->SSR);
    /* Read DR register to unfroze calendar registers */
    (void) (RTC->DR);
    return (tmpreg);
}

/**
 * Set RTC current date.
 * param RTC_Format: specifies format of entered parameters.
 *   This parameter can be  one of following values:
 *       arg RTC_Format_BIN:  Binary data format 
 *       arg RTC_Format_BCD:  BCD data format
 * param RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains
 *       date configuration information for RTC.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Date register is configured
 *     - ERROR: RTC Date register is not configured
 */
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct) {
    uint32_t tmpreg = 0;
    ErrorStatus status = ERROR;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    if (
        (RTC_Format == RTC_Format_BIN) &&
        ((RTC_DateStruct->RTC_Month & 0x10) == 0x10)
    ) {
        RTC_DateStruct->RTC_Month = (
            (RTC_DateStruct->RTC_Month & (uint32_t) ~(0x10)) + 0x0A
        );
    }
    if (RTC_Format == RTC_Format_BIN) {
        assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
        assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
        assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
    } else {
        assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));
        tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
        assert_param(IS_RTC_MONTH(tmpreg));
        tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
        assert_param(IS_RTC_DATE(tmpreg));
    }
    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));
    /* Check input parameters format */
    if (RTC_Format != RTC_Format_BIN) {
        tmpreg = (
            (((uint32_t) RTC_DateStruct->RTC_Year) << 16) |
            (((uint32_t) RTC_DateStruct->RTC_Month) << 8) |
            ((uint32_t) RTC_DateStruct->RTC_Date) |
            (((uint32_t) RTC_DateStruct->RTC_WeekDay) << 13)
        );
    } else {
        tmpreg = (
            ((uint32_t) RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) |
            ((uint32_t) RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) |
            ((uint32_t) RTC_ByteToBcd2(RTC_DateStruct->RTC_Date)) |
            ((uint32_t) RTC_DateStruct->RTC_WeekDay << 13)
        );
    }
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* Set RTC_DR register */
        RTC->DR = (uint32_t) (tmpreg & RTC_DR_RESERVED_MASK);
        RTC_ExitInitMode(); /* Exit Initialization mode */
        if (RTC_WaitForSynchro() == ERROR) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Fills each RTC_DateStruct member with its default value
 * (Monday, January 01 xx00).
 * param RTC_DateStruct: pointer to a RTC_DateTypeDef structure which
 *       will be initialized.
 * retval None
 */
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct) {
    /* Monday, January 01 xx00 */
    RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
    RTC_DateStruct->RTC_Date = 1;
    RTC_DateStruct->RTC_Month = RTC_Month_January;
    RTC_DateStruct->RTC_Year = 0;
}

/**
 * Get RTC current date. 
 * param RTC_Format: specifies format of returned parameters.
 *   This parameter can be one of following values:
 *       arg RTC_Format_BIN: Binary data format 
 *       arg RTC_Format_BCD: BCD data format
 * param RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will 
 *       contain returned current date configuration.
 * retval None
 */
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    /* Get RTC_TR register */
    tmpreg = (uint32_t) (RTC->DR & RTC_DR_RESERVED_MASK);
    /* Fill structure fields with read parameters */
    RTC_DateStruct->RTC_Year = (uint8_t) (
        (tmpreg & (RTC_DR_YT | RTC_DR_YU)) >> 16
    );
    RTC_DateStruct->RTC_Month = (uint8_t) (
        (tmpreg & (RTC_DR_MT | RTC_DR_MU)) >> 8
    );
    RTC_DateStruct->RTC_Date = (uint8_t) (tmpreg & (RTC_DR_DT | RTC_DR_DU));
    RTC_DateStruct->RTC_WeekDay = (uint8_t) ((tmpreg & (RTC_DR_WDU)) >> 13);
    /* Check input parameters format */
    if (RTC_Format == RTC_Format_BIN) {
        /* Convert structure parameters to Binary format */
        RTC_DateStruct->RTC_Year = (uint8_t) RTC_Bcd2ToByte(
            RTC_DateStruct->RTC_Year
        );
        RTC_DateStruct->RTC_Month = (uint8_t) RTC_Bcd2ToByte(
            RTC_DateStruct->RTC_Month
        );
        RTC_DateStruct->RTC_Date = (uint8_t) RTC_Bcd2ToByte(
            RTC_DateStruct->RTC_Date
        );
    }
}

/**
 * Set specified RTC Alarm.
 * The Alarm register can only be written when corresponding Alarm
 * is disabled (Use RTC_AlarmCmd(DISABLE)).
 * param RTC_Format: specifies format of returned parameters.
 *   This parameter can be one of following values:
 *       arg RTC_Format_BIN: Binary data format 
 *       arg RTC_Format_BCD: BCD data format
 * param RTC_Alarm: specifies alarm to be configured.
 *   This parameter can be one of following values:
 *       arg RTC_Alarm_A: to select Alarm A
 *       arg RTC_Alarm_B: to select Alarm B 
 * param RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that
 *       contains alarm configuration parameters.
 * retval None
 */
void RTC_SetAlarm(
    uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct
) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    assert_param(IS_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));
    assert_param(
        IS_RTC_ALARM_DATE_WEEKDAY_SEL(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel)
    );
    if (RTC_Format == RTC_Format_BIN) {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t) RESET) {
            assert_param(
                IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)
            );
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        } else {
            RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
            assert_param(
                IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)
            );
        }
        assert_param(
            IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)
        );
        assert_param(
            IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)
        );
        if (
            RTC_AlarmStruct->RTC_AlarmDateWeekDaySel ==
            RTC_AlarmDateWeekDaySel_Date
        ) {
            assert_param(
                IS_RTC_ALARM_DATE_WEEKDAY_DATE(
                    RTC_AlarmStruct->RTC_AlarmDateWeekDay
                )
            );
        } else {
            assert_param(
                IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(
                    RTC_AlarmStruct->RTC_AlarmDateWeekDay
                )
            );
        }
    } else {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t) RESET) {
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        } else {
            RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
            assert_param(
                IS_RTC_HOUR24(
                    RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)
                )
            );
        }
        assert_param(
            IS_RTC_MINUTES(
                RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)
            )
        );
        assert_param(
            IS_RTC_SECONDS(
                RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)
            )
        );
        if (
            RTC_AlarmStruct->RTC_AlarmDateWeekDaySel ==
            RTC_AlarmDateWeekDaySel_Date
        ) {
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));
        } else {
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));
        }
    }
    /* Check input parameters format */
    if (RTC_Format != RTC_Format_BIN) {
        tmpreg = (
            ((uint32_t) (RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) |
            ((uint32_t) (RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) |
            ((uint32_t) RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) |
            ((uint32_t) (RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) |
            ((uint32_t) (RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) |
            ((uint32_t) RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) |
            ((uint32_t) RTC_AlarmStruct->RTC_AlarmMask)
        );
    } else {
        tmpreg = (
            (
                (uint32_t) RTC_ByteToBcd2(
                    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours
                ) << 16
            ) |
            (
                (uint32_t) RTC_ByteToBcd2(
                    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes
                ) << 8
            ) |
            (
                (uint32_t) RTC_ByteToBcd2(
                    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds
                )
            ) |
            (
                (uint32_t) (RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16
            ) |
            (
                (uint32_t) RTC_ByteToBcd2(
                    RTC_AlarmStruct->RTC_AlarmDateWeekDay
                 ) << 24
            ) |
            ((uint32_t) RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) |
            ((uint32_t) RTC_AlarmStruct->RTC_AlarmMask)
        );
    }
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Configure Alarm register */
    if (RTC_Alarm == RTC_Alarm_A) {
        RTC->ALRMAR = (uint32_t) tmpreg;
    } else {
       RTC->ALRMBR = (uint32_t) tmpreg;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Fills each RTC_AlarmStruct member with its default value
 * (Time = 00h:00mn:00sec / Date = 1st day of month/Mask =
 * all fields are masked).
 * param RTC_AlarmStruct: pointer to a @ref RTC_AlarmTypeDef structure which
 *       will be initialized.
 * retval None
 */
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct) {
    /* Alarm Time Settings : Time = 00h:00mn:00sec */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;
    /* Alarm Date Settings : Date = 1st day of month */
    RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = 1;
    /* Alarm Masks Settings : Mask =  all fields are not masked */
    RTC_AlarmStruct->RTC_AlarmMask = RTC_AlarmMask_None;
}

/**
 * Get RTC Alarm value and masks.
 * param RTC_Format: specifies format of output parameters.
 *   This parameter can be one of following values:
 *       arg RTC_Format_BIN: Binary data format
 *       arg RTC_Format_BCD: BCD data format
 * param RTC_Alarm: specifies alarm to be read.
 *   This parameter can be one of following values:
 *       arg RTC_Alarm_A: to select Alarm A
 *       arg RTC_Alarm_B: to select Alarm B  
 * param RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will
 *       contains output alarm configuration values.
 * retval None
 */
void RTC_GetAlarm(
    uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct
) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    /* Get RTC_ALRMxR register */
    if (RTC_Alarm == RTC_Alarm_A) {
        tmpreg = (uint32_t) (RTC->ALRMAR);
    } else {
        tmpreg = (uint32_t) (RTC->ALRMBR);
    }
    /* Fill structure with read parameters */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t) (
        (tmpreg & (RTC_ALRMAR_HT | RTC_ALRMAR_HU)) >> 16
    );
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t) (
        (tmpreg & (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU)) >> 8
    );
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t) (
        tmpreg & (RTC_ALRMAR_ST | RTC_ALRMAR_SU)
    );
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (uint32_t) (
        (tmpreg & RTC_ALRMAR_PM) >> 16
    );
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = (uint32_t) (
        (tmpreg & (RTC_ALRMAR_DT | RTC_ALRMAR_DU)) >> 24
    );
    RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = (uint32_t) (
        tmpreg & RTC_ALRMAR_WDSEL
    );
    RTC_AlarmStruct->RTC_AlarmMask = (uint32_t) (
        tmpreg & RTC_AlarmMask_All
    );
    if (RTC_Format == RTC_Format_BIN) {
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = RTC_Bcd2ToByte(
            RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours
        );
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(
            RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes
        );
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(
            RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds
        );
        RTC_AlarmStruct->RTC_AlarmDateWeekDay = RTC_Bcd2ToByte(
            RTC_AlarmStruct->RTC_AlarmDateWeekDay
        );
    }
}

/**
 * Enables or disables specified RTC Alarm.
 * param RTC_Alarm: specifies alarm to be configured.
 *   This parameter can be any combination of following values:
 *       arg RTC_Alarm_A: to select Alarm A
 *       arg RTC_Alarm_B: to select Alarm B
 * param NewState: new state of specified alarm.
 *    This parameter can be: ENABLE or DISABLE.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Alarm is enabled/disabled
 *     - ERROR: RTC Alarm is not enabled/disabled
 */
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState) {
    __IO uint32_t alarmcounter = 0x00;
    uint32_t alarmstatus = 0x00;
    ErrorStatus status = ERROR;

    assert_param(IS_RTC_CMD_ALARM(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Configure Alarm state */
    if (NewState != DISABLE) {
        RTC->CR |= (uint32_t) RTC_Alarm;
        status = SUCCESS;
    } else {
        /* Disable Alarm in RTC_CR register */
        RTC->CR &= (uint32_t) ~RTC_Alarm;
        /**
         * Wait till RTC ALRxWF flag is set and
         * if Time out is reached exit
         */
        do {
            alarmstatus = RTC->ISR & (RTC_Alarm >> 8);
            alarmcounter++;
        } while((alarmcounter != INITMODE_TIMEOUT) && (alarmstatus == 0x00));
        if ((RTC->ISR & (RTC_Alarm >> 8)) == RESET) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Configure RTC AlarmA/B Subseconds value and mask.
 * This function is performed only when Alarm is disabled.
 * param RTC_Alarm: specifies alarm to be configured.
 *   This parameter can be one of following values:
 *       arg RTC_Alarm_A: to select Alarm A
 *       arg RTC_Alarm_B: to select Alarm B
 * param RTC_AlarmSubSecondValue: specifies Subseconds value.
 *   This parameter can be a value from 0 to 0x00007FFF.
 * param RTC_AlarmSubSecondMask: specifies Subseconds Mask.
 *   This parameter can be any combination of following values:
 *       arg RTC_AlarmSubSecondMask_All : All Alarm SS fields are masked.
 *           There is no comparison on sub seconds for Alarm.
 *       arg RTC_AlarmSubSecondMask_SS14_1 : SS[14:1] are don't care
 *           in Alarm comparison. Only SS[0] is compared
 *       arg RTC_AlarmSubSecondMask_SS14_2 : SS[14:2] are don't care
 *           in Alarm comparison. Only SS[1:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_3 : SS[14:3] are don't care
 *           in Alarm comparison. Only SS[2:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_4 : SS[14:4] are don't care
 *           in Alarm comparison. Only SS[3:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_5 : SS[14:5] are don't care
 *           in Alarm comparison. Only SS[4:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_6 : SS[14:6] are don't care
 *           in Alarm comparison. Only SS[5:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_7 : SS[14:7] are don't care
 *           in Alarm comparison. Only SS[6:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_8 : SS[14:8] are don't care
 *           in Alarm comparison. Only SS[7:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_9 : SS[14:9] are don't care
 *           in Alarm comparison. Only SS[8:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_10: SS[14:10] are don't care
 *           in Alarm comparison. Only SS[9:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_11: SS[14:11] are don't care
 *           in Alarm comparison. Only SS[10:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_12: SS[14:12] are don't care
 *           in Alarm comparison. Only SS[11:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14_13: SS[14:13] are don't care
 *           in Alarm comparison. Only SS[12:0] are compared
 *       arg RTC_AlarmSubSecondMask_SS14 : SS[14] is don't care
 *           in Alarm comparison. Only SS[13:0] are compared
 *       arg RTC_AlarmSubSecondMask_None : SS[14:0] are compared
 *           and must match to activate alarm
 * retval None
 */
void RTC_AlarmSubSecondConfig(
    uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue,
    uint32_t RTC_AlarmSubSecondMask
) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_ALARM(RTC_Alarm));
    assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(RTC_AlarmSubSecondValue));
    assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(RTC_AlarmSubSecondMask));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Configure Alarm A or Alarm B SubSecond registers */
    tmpreg = (uint32_t) (
        (uint32_t) (RTC_AlarmSubSecondValue) |
        (uint32_t) (RTC_AlarmSubSecondMask)
    );
    if (RTC_Alarm == RTC_Alarm_A) {
        RTC->ALRMASSR = tmpreg; /* Configure AlarmA SubSecond register */
    } else {
        RTC->ALRMBSSR = tmpreg; /* Configure Alarm B SubSecond register */
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Gets RTC Alarm Subseconds value.
 * param RTC_Alarm: specifies alarm to be read.
 *   This parameter can be one of following values:
 *       arg RTC_Alarm_A: to select Alarm A
 *       arg RTC_Alarm_B: to select Alarm B
 * param None
 * retval RTC Alarm Subseconds value.
 */
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm) {
    uint32_t tmpreg = 0;

    /* Get RTC_ALRMxR register */
    if (RTC_Alarm == RTC_Alarm_A) {
        tmpreg = (uint32_t) ((RTC->ALRMASSR) & RTC_ALRMASSR_SS);
    } else {
        tmpreg = (uint32_t) ((RTC->ALRMBSSR) & RTC_ALRMBSSR_SS);
    }
    return (tmpreg);
}

/**
 * Configures RTC Wakeup clock source.
 * The WakeUp Clock source can only be changed when RTC WakeUp
 * is disabled (Use RTC_WakeUpCmd(DISABLE)).
 * param RTC_WakeUpClock: Wakeup Clock source.
 *   This parameter can be one of following values:
 *       arg RTC_WakeUpClock_RTCCLK_Div16: RTC Wakeup Counter Clock = RTCCLK/16
 *       arg RTC_WakeUpClock_RTCCLK_Div8: RTC Wakeup Counter Clock = RTCCLK/8
 *       arg RTC_WakeUpClock_RTCCLK_Div4: RTC Wakeup Counter Clock = RTCCLK/4
 *       arg RTC_WakeUpClock_RTCCLK_Div2: RTC Wakeup Counter Clock = RTCCLK/2
 *       arg RTC_WakeUpClock_CK_SPRE_16bits: RTC Wakeup Counter Clock = CK_SPRE
 *       arg RTC_WakeUpClock_CK_SPRE_17bits: RTC Wakeup Counter Clock = CK_SPRE
 * retval None
 */
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock) {
    assert_param(IS_RTC_WAKEUP_CLOCK(RTC_WakeUpClock));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Clear Wakeup Timer clock source bits in CR register */
    RTC->CR &= (uint32_t) ~RTC_CR_WUCKSEL;
    RTC->CR |= (uint32_t) RTC_WakeUpClock; /* Configure clock source */
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Configures RTC Wakeup counter.
 * The RTC WakeUp counter can only be written when RTC WakeUp
 * is disabled (Use RTC_WakeUpCmd(DISABLE)).
 * param RTC_WakeUpCounter: specifies WakeUp counter.
 *   This parameter can be a value from 0x0000 to 0xFFFF.
 * retval None
 */
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter) {
    assert_param(IS_RTC_WAKEUP_COUNTER(RTC_WakeUpCounter));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    RTC->WUTR = (uint32_t)RTC_WakeUpCounter; /* Configure Wakeup counter */
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Returns RTC WakeUp timer counter value.
 * param None
 * retval The RTC WakeUp Counter value.
 */
uint32_t RTC_GetWakeUpCounter(void) {
    return ((uint32_t) (RTC->WUTR & RTC_WUTR_WUT)); /* Get counter value */
}

/**
 * Enables or Disables RTC WakeUp timer.
 * param NewState: new state of WakeUp timer.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState) {
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus = 0x00;
    ErrorStatus status = ERROR;

    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    if (NewState != DISABLE) {
        RTC->CR |= (uint32_t) RTC_CR_WUTE; /* Enable Wakeup Timer */
        status = SUCCESS;
    } else {
        RTC->CR &= (uint32_t) ~RTC_CR_WUTE; /* Disable Wakeup Timer */
        /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
        do {
            wutwfstatus = RTC->ISR & RTC_ISR_WUTWF;
            wutcounter++;
        } while((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));
        if ((RTC->ISR & RTC_ISR_WUTWF) == RESET) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Adds or substract one hour from current time.
 * param RTC_DayLightSaveOperation: value of hour adjustment.
 *   This parameter can be one of following values:
 *       arg RTC_DayLightSaving_SUB1H: Substract one hour (winter time)
 *       arg RTC_DayLightSaving_ADD1H: Add one hour (summer time)
 * param RTC_StoreOperation: Specifies value to be written in BCK bit
 *       in CR register to store operation.
 *   This parameter can be one of following values:
 *       arg RTC_StoreOperation_Reset: BCK Bit Reset
 *       arg RTC_StoreOperation_Set: BCK Bit Set
 * retval None
 */
void RTC_DayLightSavingConfig(
    uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation
) {
    assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
    assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    RTC->CR &= (uint32_t) ~(RTC_CR_BCK); /* Clear bits to be configured */
    /* Configure RTC_CR register */
    RTC->CR |= (uint32_t) (RTC_DayLightSaving | RTC_StoreOperation);
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Returns RTC Day Light Saving stored operation.
 * param None
 * retval RTC Day Light Saving stored operation.
 *     - RTC_StoreOperation_Reset
 *     - RTC_StoreOperation_Set
 */
uint32_t RTC_GetStoreOperation(void) {
    return (RTC->CR & RTC_CR_BCK);
}

/**
 * Configures RTC output source (AFO_ALARM).
 * param RTC_Output: Specifies which signal will be routed to RTC output.
 *   This parameter can be one of following values:
 *       arg RTC_Output_Disable: No output selected
 *       arg RTC_Output_AlarmA: signal of AlarmA mapped to output
 *       arg RTC_Output_AlarmB: signal of AlarmB mapped to output
 *       arg RTC_Output_WakeUp: signal of WakeUp mapped to output
 * param RTC_OutputPolarity: Specifies polarity of output signal.
 *    This parameter can be one of following:
 *       arg RTC_OutputPolarity_High: The output pin is high when
 *           ALRAF/ALRBF/WUTF is high (depending on OSEL)
 *       arg RTC_OutputPolarity_Low: The output pin is low when
 *           ALRAF/ALRBF/WUTF is high (depending on OSEL)
 * retval None
 */
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity) {
    assert_param(IS_RTC_OUTPUT(RTC_Output));
    assert_param(IS_RTC_OUTPUT_POL(RTC_OutputPolarity));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Clear bits to be configured */
    RTC->CR &= (uint32_t) ~(RTC_CR_OSEL | RTC_CR_POL);
    /* Configure output selection and polarity */
    RTC->CR |= (uint32_t) (RTC_Output | RTC_OutputPolarity);
    /* Enable write protection for RTC registers */
    RTC->WPR = 0xFF;
}

/**
 * Configures Coarse calibration parameters.
 * param RTC_CalibSign: specifies sign of coarse calibration value.
 *    This parameter can be  one of following values:
 *       arg RTC_CalibSign_Positive: The value sign is positive
 *       arg RTC_CalibSign_Negative: The value sign is negative
 * param Value: value of coarse calibration expressed in ppm (coded on 5 bits).
 *   This Calibration value should be between 0 and 63 when using negative
 *   sign with a 2-ppm step.
 * This Calibration value should be between 0 and 126 when using positive
 * sign with a 4-ppm step.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Coarse calibration are initialized
 *     - ERROR: RTC Coarse calibration are not initialized
 */
ErrorStatus RTC_CoarseCalibConfig(uint32_t RTC_CalibSign, uint32_t Value) {
    ErrorStatus status = ERROR;

    assert_param(IS_RTC_CALIB_SIGN(RTC_CalibSign));
    assert_param(IS_RTC_CALIB_VALUE(Value));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* Set coarse calibration value */
        RTC->CALIBR = (uint32_t) (RTC_CalibSign | Value);
        RTC_ExitInitMode(); /* Exit Initialization mode */
        status = SUCCESS;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Enables or disables Coarse calibration process.
 * param NewState: new state of Coarse calibration.
 *    This parameter can be: ENABLE or DISABLE.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Coarse calibration are enabled/disabled
 *     - ERROR: RTC Coarse calibration are not enabled/disabled
 */
ErrorStatus RTC_CoarseCalibCmd(FunctionalState NewState) {
    ErrorStatus status = ERROR;

    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR) {
        status =  ERROR;
    } else {
        if (NewState != DISABLE) {
            RTC->CR |= (uint32_t) RTC_CR_DCE; /* Enable Coarse Calibration */
        } else {
            RTC->CR &= (uint32_t) ~RTC_CR_DCE; /* Disable Coarse Calibration */
        }
        RTC_ExitInitMode(); /* Exit Initialization mode */
        status = SUCCESS;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return status;
}

/**
 * Enables or disables RTC clock to be output through relative pin.
 * param NewState: new state of digital calibration Output.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_CalibOutputCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    if (NewState != DISABLE) {
        RTC->CR |= (uint32_t) RTC_CR_COE; /* Enable RTC clock output */
    } else {
        RTC->CR &= (uint32_t) ~RTC_CR_COE; /* Disable RTC clock output */
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Configure Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
 * param RTC_CalibOutput : Select Calibration output Selection .
 *   This parameter can be one of following values:
 *       arg RTC_CalibOutput_512Hz: A signal has a regular waveform at 512Hz.
 *       arg RTC_CalibOutput_1Hz: A signal has a regular waveform at 1Hz.
 * retval None
*/
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput) {
    assert_param(IS_RTC_CALIB_OUTPUT(RTC_CalibOutput));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    RTC->CR &= (uint32_t) ~(RTC_CR_COSEL); /*clear flags before config*/
    RTC->CR |= (uint32_t) RTC_CalibOutput; /* Configure RTC_CR register */
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Configures Smooth Calibration Settings.
 * param RTC_SmoothCalibPeriod : Select Smooth Calibration Period.
 *   This parameter can be can be one of following values:
 *       arg RTC_SmoothCalibPeriod_32sec: Smooth calibration periode is 32s.
 *       arg RTC_SmoothCalibPeriod_16sec: Smooth calibration periode is 16s.
 *       arg RTC_SmoothCalibPeriod_8sec: Smooth calibartion periode is 8s.
 * param RTC_SmoothCalibPlusPulses : Select to Set or reset CALP bit.
 *   This parameter can be one of following values:
 *       arg RTC_SmoothCalibPlusPulses_Set: Add one RTCCLK puls
 *           every 2**11 pulses.
 *       arg RTC_SmoothCalibPlusPulses_Reset: No RTCCLK pulses are added.
 * param RTC_SmouthCalibMinusPulsesValue: Select value of CALM[8:0] bits.
 *   This parameter can be one any value from 0 to 0x000001FF.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Calib registers are configured
 *     - ERROR: RTC Calib registers are not configured
*/
ErrorStatus RTC_SmoothCalibConfig(
    uint32_t RTC_SmoothCalibPeriod,
    uint32_t RTC_SmoothCalibPlusPulses,
    uint32_t RTC_SmouthCalibMinusPulsesValue
) {
    ErrorStatus status = ERROR;
    uint32_t recalpfcount = 0;

    assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(RTC_SmoothCalibPeriod));
    assert_param(IS_RTC_SMOOTH_CALIB_PLUS(RTC_SmoothCalibPlusPulses));
    assert_param(IS_RTC_SMOOTH_CALIB_MINUS(RTC_SmouthCalibMinusPulsesValue));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* check if a calibration is pending*/
    if ((RTC->ISR & RTC_ISR_RECALPF) != RESET) {
        /* wait until Calibration is completed*/
        while (
            ((RTC->ISR & RTC_ISR_RECALPF) != RESET) &&
            (recalpfcount != RECALPF_TIMEOUT)
        ) {
            recalpfcount++;
        }
    }
    /**
     * check if calibration pending is completed or
     * if there is no calibration operation at all
     */
    if ((RTC->ISR & RTC_ISR_RECALPF) == RESET) {
        /* Configure Smooth calibration settings */
        RTC->CALR = (uint32_t) (
            (uint32_t) RTC_SmoothCalibPeriod |
            (uint32_t) RTC_SmoothCalibPlusPulses |
            (uint32_t) RTC_SmouthCalibMinusPulsesValue
        );
        status = SUCCESS;
    } else {
        status = ERROR;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return (ErrorStatus) (status);
}

/**
 * Enables or Disables RTC TimeStamp functionality with
 * specified time stamp pin stimulating edge.
 * param RTC_TimeStampEdge: Specifies pin edge on which TimeStamp is
 *       activated.
 *   This parameter can be one of following:
 *       arg RTC_TimeStampEdge_Rising: Time stamp event occurs on rising
 *           edge of related pin.
 *       arg RTC_TimeStampEdge_Falling: Time stamp event occurs on
 *           falling edge of related pin.
 * param NewState: new state of TimeStamp.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_TIMESTAMP_EDGE(RTC_TimeStampEdge));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    /* Get RTC_CR register and clear bits to be configured */
    tmpreg = (uint32_t) (RTC->CR & (uint32_t) ~(RTC_CR_TSEDGE | RTC_CR_TSE));
    /* Get new configuration */
    if (NewState != DISABLE) {
        tmpreg |= (uint32_t) (RTC_TimeStampEdge | RTC_CR_TSE);
    } else {
        tmpreg |= (uint32_t) (RTC_TimeStampEdge);
    }
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Configure Time Stamp TSEDGE and Enable bits */
    RTC->CR = (uint32_t) tmpreg;
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Get RTC TimeStamp value and masks.
 * param RTC_Format: specifies format of output parameters.
 *   This parameter can be one of following values:
 *       arg RTC_Format_BIN: Binary data format
 *       arg RTC_Format_BCD: BCD data format
 * param RTC_StampTimeStruct: pointer to a RTC_TimeTypeDef structure that will
 *       contains TimeStamp time values.
 * param RTC_StampDateStruct: pointer to a RTC_DateTypeDef structure that will
 *       contains TimeStamp date values.
 * retval None
 */
void RTC_GetTimeStamp(
    uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct,
    RTC_DateTypeDef* RTC_StampDateStruct
) {
    uint32_t tmptime = 0, tmpdate = 0;

    assert_param(IS_RTC_FORMAT(RTC_Format));
    /* Get TimeStamp time and date registers values */
    tmptime = (uint32_t) (RTC->TSTR & RTC_TR_RESERVED_MASK);
    tmpdate = (uint32_t) (RTC->TSDR & RTC_DR_RESERVED_MASK);
    /* Fill Time structure fields with read parameters */
    RTC_StampTimeStruct->RTC_Hours = (uint8_t) (
        (tmptime & (RTC_TR_HT | RTC_TR_HU)) >> 16
    );
    RTC_StampTimeStruct->RTC_Minutes = (uint8_t) (
        (tmptime & (RTC_TR_MNT | RTC_TR_MNU)) >> 8
    );
    RTC_StampTimeStruct->RTC_Seconds = (uint8_t) (
        tmptime & (RTC_TR_ST | RTC_TR_SU)
    );
    RTC_StampTimeStruct->RTC_H12 = (uint8_t) (
        (tmptime & (RTC_TR_PM)) >> 16
    );
    /* Fill Date structure fields with read parameters */
    RTC_StampDateStruct->RTC_Year = 0;
    RTC_StampDateStruct->RTC_Month = (uint8_t) (
        (tmpdate & (RTC_DR_MT | RTC_DR_MU)) >> 8
    );
    RTC_StampDateStruct->RTC_Date = (uint8_t) (
        tmpdate & (RTC_DR_DT | RTC_DR_DU)
    );
    RTC_StampDateStruct->RTC_WeekDay = (uint8_t) (
        (tmpdate & (RTC_DR_WDU)) >> 13
    );
    /* Check input parameters format */
    if (RTC_Format == RTC_Format_BIN) {
        /* Convert Time structure parameters to Binary format */
        RTC_StampTimeStruct->RTC_Hours = (uint8_t) (
            RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Hours)
        );
        RTC_StampTimeStruct->RTC_Minutes = (uint8_t) (
            RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Minutes)
        );
        RTC_StampTimeStruct->RTC_Seconds = (uint8_t) (
            RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Seconds)
        );
        /* Convert Date structure parameters to Binary format */
        RTC_StampDateStruct->RTC_Month = (uint8_t) (
            RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Month)
        );
        RTC_StampDateStruct->RTC_Date = (uint8_t) (
            RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Date)
        );
        RTC_StampDateStruct->RTC_WeekDay = (uint8_t) (
            RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_WeekDay)
        );
    }
}

/**
 * Get RTC timestamp Subseconds value.
 * param None
 * retval RTC current timestamp Subseconds value.
 */
uint32_t RTC_GetTimeStampSubSecond(void) {
    /* Get timestamp subseconds values from correspondent registers */
    return (uint32_t) (RTC->TSSSR);
}

/**
 * Configures select Tamper pin edge.
 * param RTC_Tamper: Selected tamper pin.
 *    This parameter can be RTC_Tamper_1.
 * param RTC_TamperTrigger: Specifies trigger on tamper pin that 
 *       stimulates tamper event.
 *   This parameter can be one of following values:
 *        arg RTC_TamperTrigger_RisingEdge: Rising Edge of tamper pin
 *            causes tamper event.
 *        arg RTC_TamperTrigger_FallingEdge: Falling Edge of tamper pin
 *            causes tamper event.
 *        arg RTC_TamperTrigger_LowLevel: Low Level of tamper pin
 *            causes tamper event.
 *        arg RTC_TamperTrigger_HighLevel: High Level of tamper pin
 *            causes tamper event.
 * retval None
 */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger) {
    assert_param(IS_RTC_TAMPER(RTC_Tamper)); 
    assert_param(IS_RTC_TAMPER_TRIGGER(RTC_TamperTrigger));
    if (RTC_TamperTrigger == RTC_TamperTrigger_RisingEdge) {
        /* Configure RTC_TAFCR register */
        RTC->TAFCR &= (uint32_t) ((uint32_t) ~(RTC_Tamper << 1));
    } else {
        /* Configure RTC_TAFCR register */
        RTC->TAFCR |= (uint32_t) (RTC_Tamper << 1);
    }
}

/**
 * Enables or Disables Tamper detection.
 * param RTC_Tamper: Selected tamper pin.
 *    This parameter can be RTC_Tamper_1.
 * param NewState: new state of tamper pin.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState) {
    assert_param(IS_RTC_TAMPER(RTC_Tamper));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        RTC->TAFCR |= (uint32_t) RTC_Tamper; /* Enable selected Tamper pin */
    } else {
        RTC->TAFCR &= (uint32_t) ~RTC_Tamper; /* Disable selected Tamper pin */
    }
}

/**
 * Configures Tampers Filter.
 * param RTC_TamperFilter: Specifies tampers filter.
 *   This parameter can be one of following values:
 *        arg RTC_TamperFilter_Disable: Tamper filter is disabled.
 *        arg RTC_TamperFilter_2Sample: Tamper is activated after 2
 *            consecutive samples at active level
 *        arg RTC_TamperFilter_4Sample: Tamper is activated after 4
 *            consecutive samples at active level
 *        arg RTC_TamperFilter_8Sample: Tamper is activated after 8
 *            consecutive samples at active level
 * retval None
 */
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter) {
    assert_param(IS_RTC_TAMPER_FILTER(RTC_TamperFilter));
    /* Clear TAMPFLT[1:0] bits in RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t) ~(RTC_TAFCR_TAMPFLT);
    /* Configure RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t) RTC_TamperFilter;
}

/**
 * Configures Tampers Sampling Frequency.
 * param RTC_TamperSamplingFreq: Specifies tampers Sampling Frequency.
 *   This parameter can be one of following values:
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div32768: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 32768
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div16384: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 16384
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div8192: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 8192
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div4096: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 4096
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div2048: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 2048
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div1024: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 1024
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div512: Each of
 *           tamper inputs are sampled with a frequency =  RTCCLK / 512
 *       arg RTC_TamperSamplingFreq_RTCCLK_Div256: Each of tamper
 *           inputs are sampled with a frequency =  RTCCLK / 256
 * retval None
 */
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq) {
    assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(RTC_TamperSamplingFreq));
    /* Clear TAMPFREQ[2:0] bits in RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t) ~(RTC_TAFCR_TAMPFREQ);
    /* Configure RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t) RTC_TamperSamplingFreq;
}

/**
 * Configures Tampers Pins input Precharge Duration.
 * param RTC_TamperPrechargeDuration: Specifies Tampers Pins input
 *       Precharge Duration.
 *   This parameter can be one of following values:
 *        arg RTC_TamperPrechargeDuration_1RTCCLK: Tamper pins are
 *            pre-charged before sampling during 1 RTCCLK cycle
 *        arg RTC_TamperPrechargeDuration_2RTCCLK: Tamper pins are
 *            pre-charged before sampling during 2 RTCCLK cycle
 *        arg RTC_TamperPrechargeDuration_4RTCCLK: Tamper pins are
 *            pre-charged before sampling during 4 RTCCLK cycle
 *        arg RTC_TamperPrechargeDuration_8RTCCLK: Tamper pins are
 *            pre-charged before sampling during 8 RTCCLK cycle
 * retval None
 */
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration) {
    assert_param(
        IS_RTC_TAMPER_PRECHARGE_DURATION(RTC_TamperPrechargeDuration)
    );
    /* Clear TAMPPRCH[1:0] bits in RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t) ~(RTC_TAFCR_TAMPPRCH);
    /* Configure RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t) RTC_TamperPrechargeDuration;
}

/**
 * Enables or Disables TimeStamp on Tamper Detection Event.
 * The timestamp is valid even TSE bit in tamper control register
 * is reset.
 * param NewState: new state of timestamp on tamper event.
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Save timestamp on tamper detection event */
        RTC->TAFCR |= (uint32_t) RTC_TAFCR_TAMPTS;
    } else {
        /* Tamper detection does not cause a timestamp to be saved */
        RTC->TAFCR &= (uint32_t) ~RTC_TAFCR_TAMPTS;
    }
}

/**
 * Enables or Disables Precharge of Tamper pin
 * param NewState: new state of tamper pull up
 *   This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_TamperPullUpCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* Enable precharge of selected Tamper pin */
        RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPPUDIS;
    } else {
        /* Disable precharge of selected Tamper pin */
        RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPPUDIS;
    }
}

/**
 * Writes a data in a specified RTC Backup data register.
 * param RTC_BKP_DR: RTC Backup data Register number.
 *    This parameter can be: RTC_BKP_DRx where x can be from 0 to 19 to
 *    specify register.
 * param Data: Data to be written in specified RTC Backup data register.
 * retval None
 */
void RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data) {
    __IO uint32_t tmp = 0;

    assert_param(IS_RTC_BKP(RTC_BKP_DR));
    tmp = RTC_BASE + 0x50;
    tmp += (RTC_BKP_DR * 4);
    *(__IO uint32_t *) tmp = (uint32_t) Data; /* Write specified register */
}

/**
 * Reads data from specified RTC Backup data Register.
 * param RTC_BKP_DR: RTC Backup data Register number.
 *   This parameter can be: RTC_BKP_DRx where x can be from 0 to 19 to
 *   specify register.
 * retval None
 */
uint32_t RTC_ReadBackupRegister(uint32_t RTC_BKP_DR) {
    __IO uint32_t tmp = 0;

    assert_param(IS_RTC_BKP(RTC_BKP_DR));
    tmp = RTC_BASE + 0x50;
    tmp += (RTC_BKP_DR * 4);
    return (*(__IO uint32_t *) tmp); /* Read specified register */
}

/**
 * Selects RTC Tamper Pin.
 * param RTC_TamperPin: specifies RTC Tamper Pin.
 *    This parameter can be one of following values:
 *       arg RTC_TamperPin_PC13: PC13 is selected as RTC Tamper Pin.
 *       arg RTC_TamperPin_PI8: PI8 is selected as RTC Tamper Pin.
 * retval None
 */
void RTC_TamperPinSelection(uint32_t RTC_TamperPin) {
    assert_param(IS_RTC_TAMPER_PIN(RTC_TamperPin));
    RTC->TAFCR &= (uint32_t) ~(RTC_TAFCR_TAMPINSEL);
    RTC->TAFCR |= (uint32_t) (RTC_TamperPin);
}

/**
 * Selects RTC TimeStamp Pin.
 * param RTC_TimeStampPin: specifies RTC TimeStamp Pin.
 *    This parameter can be one of following values:
 *       arg RTC_TimeStampPin_PC13: PC13 is selected as RTC TimeStamp Pin.
 *       arg RTC_TimeStampPin_PI8: PI8 is selected as RTC TimeStamp Pin.
 * retval None
 */
void RTC_TimeStampPinSelection(uint32_t RTC_TimeStampPin) {
    assert_param(IS_RTC_TIMESTAMP_PIN(RTC_TimeStampPin));
    RTC->TAFCR &= (uint32_t) ~(RTC_TAFCR_TSINSEL);
    RTC->TAFCR |= (uint32_t) (RTC_TimeStampPin);
}

/**
 * Configures RTC Output Pin mode.
 * param RTC_OutputType: specifies RTC Output (PC13) pin mode.
 *   This parameter can be one of following values:
 *       arg RTC_OutputType_OpenDrain: RTC Output (PC13) is configured in
 *           Open Drain mode.
 *       arg RTC_OutputType_PushPull: RTC Output (PC13) is configured in
 *           Push Pull mode.
 * retval None
 */
void RTC_OutputTypeConfig(uint32_t RTC_OutputType) {
    assert_param(IS_RTC_OUTPUT_TYPE(RTC_OutputType));
    RTC->TAFCR &= (uint32_t) ~(RTC_TAFCR_ALARMOUTTYPE);
    RTC->TAFCR |= (uint32_t) (RTC_OutputType);
}

/**
 * Configures Synchronization Shift Control Settings.
 * When REFCKON is set, firmware must not write to Shift control register
 * param RTC_ShiftAdd1S : Select to add or not 1 second to time Calendar
 *   This parameter can be one of following values:
 *        arg RTC_ShiftAdd1S_Set: Add one second to clock calendar.
 *        arg RTC_ShiftAdd1S_Reset: No effect.
 * param RTC_ShiftSubFS: Select number of Second Fractions to Substitute.
 *   This parameter can be one any value from 0 to 0x7FFF.
 * retval An ErrorStatus enumeration value:
 *     - SUCCESS: RTC Shift registers are configured
 *     - ERROR: RTC Shift registers are not configured
*/
ErrorStatus RTC_SynchroShiftConfig(
    uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS
) {
    ErrorStatus status = ERROR;
    uint32_t shpfcount = 0;

    assert_param(IS_RTC_SHIFT_ADD1S(RTC_ShiftAdd1S));
    assert_param(IS_RTC_SHIFT_SUBFS(RTC_ShiftSubFS));
    /* Disable write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    /* Check if a Shift is pending*/
    if ((RTC->ISR & RTC_ISR_SHPF) != RESET) {
        /* Wait until shift is completed*/
        while (
            ((RTC->ISR & RTC_ISR_SHPF) != RESET) && (shpfcount != SHPF_TIMEOUT)
        ) {
            shpfcount++;
        }
    }
    /**
     * Check if Shift pending is completed or if there
     * is no Shift operation at all
     */
    if ((RTC->ISR & RTC_ISR_SHPF) == RESET) {
        /* check if reference clock detection is disabled */
        if ((RTC->CR & RTC_CR_REFCKON) == RESET) {
            /* Configure Shift settings */
            RTC->SHIFTR = (uint32_t) (
                (uint32_t) (RTC_ShiftSubFS) | (uint32_t) (RTC_ShiftAdd1S)
            );
            if (RTC_WaitForSynchro() == ERROR) {
                status = ERROR;
            } else {
                status = SUCCESS;
            }
        } else {
            status = ERROR;
        }
    } else {
        status = ERROR;
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
    return (ErrorStatus) (status);
}

/**
 * Enables or disables specified RTC interrupts.
 * param RTC_IT: specifies RTC interrupt sources to be enabled or disabled.
 *    This parameter can be any combination of following values:
 *       arg RTC_IT_TS:  Time Stamp interrupt mask
 *       arg RTC_IT_WUT:  WakeUp Timer interrupt mask
 *       arg RTC_IT_ALRB:  Alarm B interrupt mask
 *       arg RTC_IT_ALRA:  Alarm A interrupt mask
 *       arg RTC_IT_TAMP: Tamper event interrupt mask
 * param NewState: new state of specified RTC interrupts.
 *    This parameter can be: ENABLE or DISABLE.
 * retval None
 */
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState) {
    assert_param(IS_RTC_CONFIG_IT(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    if (NewState != DISABLE) {
        /* Configure Interrupts in RTC_CR register */
        RTC->CR |= (uint32_t) (RTC_IT & ~RTC_TAFCR_TAMPIE);
        /* Configure Tamper Interrupt in RTC_TAFCR */
        RTC->TAFCR |= (uint32_t) (RTC_IT & RTC_TAFCR_TAMPIE);
    } else {
        /* Configure Interrupts in RTC_CR register */
        RTC->CR &= (uint32_t) ~(RTC_IT & (uint32_t) ~RTC_TAFCR_TAMPIE);
        /* Configure Tamper Interrupt in RTC_TAFCR */
        RTC->TAFCR &= (uint32_t) ~(RTC_IT & RTC_TAFCR_TAMPIE);
    }
    RTC->WPR = 0xFF; /* Enable write protection for RTC registers */
}

/**
 * Checks whether specified RTC flag is set or not.
 * param RTC_FLAG: specifies flag to check.
 *    This parameter can be one of following values:
 *       arg RTC_FLAG_TAMP1F: Tamper 1 event flag
 *       arg RTC_FLAG_TSOVF: Time Stamp OverFlow flag
 *       arg RTC_FLAG_TSF: Time Stamp event flag
 *       arg RTC_FLAG_WUTF: WakeUp Timer flag
 *       arg RTC_FLAG_ALRBF: Alarm B flag
 *       arg RTC_FLAG_ALRAF: Alarm A flag
 *       arg RTC_FLAG_INITF: Initialization mode flag
 *       arg RTC_FLAG_RSF: Registers Synchronized flag
 *       arg RTC_FLAG_INITS: Registers Configured flag
 *       arg RTC_FLAG_WUTWF: WakeUp Timer Write flag
 *       arg RTC_FLAG_ALRBWF: Alarm B Write flag
 *       arg RTC_FLAG_ALRAWF: Alarm A write flag
 * retval The new state of RTC_FLAG (SET or RESET).
 */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_GET_FLAG(RTC_FLAG));
    tmpreg = (uint32_t) (RTC->ISR & RTC_FLAGS_MASK); /* Get all flags */
    /* Return status of flag */
    if ((tmpreg & RTC_FLAG) != (uint32_t) RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears RTC's pending flags.
 * param RTC_FLAG: specifies RTC flag to clear.
 *    This parameter can be any combination of following values:
 *       arg RTC_FLAG_TAMP1F: Tamper 1 event flag
 *       arg RTC_FLAG_TSOVF: Time Stamp Overflow flag
 *       arg RTC_FLAG_TSF: Time Stamp event flag
 *       arg RTC_FLAG_WUTF: WakeUp Timer flag
 *       arg RTC_FLAG_ALRBF: Alarm B flag
 *       arg RTC_FLAG_ALRAF: Alarm A flag
 *       arg RTC_FLAG_RSF: Registers Synchronized flag
 * retval None
 */
void RTC_ClearFlag(uint32_t RTC_FLAG) {
    assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));
    /* Clear Flags in RTC_ISR register */
    RTC->ISR = (uint32_t) (
        (uint32_t) (~((RTC_FLAG | RTC_ISR_INIT)& 0x0000FFFF) |
        (uint32_t) (RTC->ISR & RTC_ISR_INIT))
    );
}

/**
 * Checks whether specified RTC interrupt has occurred or not.
 * param RTC_IT: specifies RTC interrupt source to check.
 *    This parameter can be one of following values:
 *       arg RTC_IT_TS: Time Stamp interrupt
 *       arg RTC_IT_WUT: WakeUp Timer interrupt
 *       arg RTC_IT_ALRB: Alarm B interrupt
 *       arg RTC_IT_ALRA: Alarm A interrupt
 *       arg RTC_IT_TAMP1: Tamper 1 event interrupt
 * retval The new state of RTC_IT (SET or RESET).
 */
ITStatus RTC_GetITStatus(uint32_t RTC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0, enablestatus = 0;

    assert_param(IS_RTC_GET_IT(RTC_IT));
    /* Get TAMPER Interrupt enable bit and pending bit */
    tmpreg = (uint32_t) (RTC->TAFCR & (RTC_TAFCR_TAMPIE));
    /* Get Interrupt enable Status */
    enablestatus = (uint32_t) ((RTC->CR & RTC_IT) | (tmpreg & (RTC_IT >> 15)));
    /* Get Interrupt pending bit */
    tmpreg = (uint32_t) ((RTC->ISR & (uint32_t) (RTC_IT >> 4)));
    /* Get status of Interrupt */
    if (
        (enablestatus != (uint32_t) RESET) &&
        ((tmpreg & 0x0000FFFF) != (uint32_t) RESET)
    ) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * Clears RTC's interrupt pending bits.
 * param RTC_IT: specifies RTC interrupt pending bit to clear.
 *    This parameter can be any combination of following values:
 *       arg RTC_IT_TS: Time Stamp interrupt
 *       arg RTC_IT_WUT: WakeUp Timer interrupt
 *       arg RTC_IT_ALRB: Alarm B interrupt
 *       arg RTC_IT_ALRA: Alarm A interrupt
 *       arg RTC_IT_TAMP1: Tamper 1 event interrupt
 * retval None
 */
void RTC_ClearITPendingBit(uint32_t RTC_IT) {
    uint32_t tmpreg = 0;

    assert_param(IS_RTC_CLEAR_IT(RTC_IT));
    /* Get RTC_ISR Interrupt pending bits mask */
    tmpreg = (uint32_t) (RTC_IT >> 4);
    /* Clear interrupt pending bits in RTC_ISR register */
    RTC->ISR = (uint32_t) (
        (uint32_t) (~((tmpreg | RTC_ISR_INIT) & 0x0000FFFF) |
        (uint32_t) (RTC->ISR & RTC_ISR_INIT))
    );
}

/**
 * Converts a 2 digit decimal to BCD format.
 * param Value: Byte to be converted.
 * retval Converted byte
 */
static uint8_t RTC_ByteToBcd2(uint8_t Value) {
    uint8_t bcdhigh = 0;

    while (Value >= 10) {
        bcdhigh++;
        Value -= 10;
    }
    return ((uint8_t) (bcdhigh << 4) | Value);
}

/**
 * Convert from 2 digit BCD to Binary.
 * param Value: BCD value to be converted.
 * retval Converted word
 */
static uint8_t RTC_Bcd2ToByte(uint8_t Value) {
    uint8_t tmp = 0;
    tmp = ((uint8_t) (Value & (uint8_t) 0xF0) >> (uint8_t) 0x4) * 10;
    return (tmp + (Value & (uint8_t) 0x0F));
}

