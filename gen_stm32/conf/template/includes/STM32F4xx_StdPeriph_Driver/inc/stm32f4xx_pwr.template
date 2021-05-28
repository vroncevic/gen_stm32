/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_pwr.h
 * 
 * This file contains all the functions prototypes for PWR firmware library.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_pwr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_pwr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STM32F4xx_PWR_H
#define __STM32F4xx_PWR_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "stm32f4xx.h"

#define PWR_PVDLevel_0 PWR_CR_PLS_LEV0
#define PWR_PVDLevel_1 PWR_CR_PLS_LEV1
#define PWR_PVDLevel_2 PWR_CR_PLS_LEV2
#define PWR_PVDLevel_3 PWR_CR_PLS_LEV3
#define PWR_PVDLevel_4 PWR_CR_PLS_LEV4
#define PWR_PVDLevel_5 PWR_CR_PLS_LEV5
#define PWR_PVDLevel_6 PWR_CR_PLS_LEV6
#define PWR_PVDLevel_7 PWR_CR_PLS_LEV7
#define PWR_Regulator_ON ((uint32_t) 0x00000000)
#define PWR_Regulator_LowPower PWR_CR_LPDS
#define PWR_STOPEntry_WFI ((uint8_t) 0x01)
#define PWR_STOPEntry_WFE ((uint8_t) 0x02)
#define PWR_Regulator_Voltage_Scale1 ((uint32_t) 0x00004000)
#define PWR_Regulator_Voltage_Scale2 ((uint32_t) 0x00000000)
#define PWR_FLAG_WU PWR_CSR_WUF
#define PWR_FLAG_SB PWR_CSR_SBF
#define PWR_FLAG_PVDO PWR_CSR_PVDO
#define PWR_FLAG_BRR PWR_CSR_BRR
#define PWR_FLAG_VOSRDY PWR_CSR_VOSRDY
#define PWR_FLAG_REGRDY PWR_FLAG_VOSRDY

#define IS_PWR_PVD_LEVEL(LEVEL) ( \
    ((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
    ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
    ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
    ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7) \
)

#define IS_PWR_REGULATOR(REGULATOR) ( \
    ((REGULATOR) == PWR_Regulator_ON) || \
    ((REGULATOR) == PWR_Regulator_LowPower) \
)

#define IS_PWR_STOP_ENTRY(ENTRY) ( \
    ((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE) \
)

#define IS_PWR_REGULATOR_VOLTAGE(VOLTAGE) ( \
    ((VOLTAGE) == PWR_Regulator_Voltage_Scale1) || \
    ((VOLTAGE) == PWR_Regulator_Voltage_Scale2) \
)

#define IS_PWR_GET_FLAG(FLAG) ( \
    ((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
    ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_BRR) || \
    ((FLAG) == PWR_FLAG_VOSRDY) \
)

#define IS_PWR_CLEAR_FLAG(FLAG) ( \
    ((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) \
)

void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_BackupRegulatorCmd(FunctionalState NewState);
void PWR_MainRegulatorModeConfig(uint32_t PWR_Regulator_Voltage);
void PWR_FlashPowerDownCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#ifdef __cplusplus
    }
#endif

#endif

