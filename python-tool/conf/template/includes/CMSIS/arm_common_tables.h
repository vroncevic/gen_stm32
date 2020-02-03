/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * arm_common_tables.h
 * 
 * This file has extern declaration for common tables like Bitreverse,
 * reciprocal etc which are used across different functions.
 * 
 * Version V1.0.2
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * CMSIS DSP Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * CMSIS DSP Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ARM_COMMON_TABLES_H
#define _ARM_COMMON_TABLES_H

#include "arm_math.h"

extern uint16_t armBitRevTable[256];
extern q15_t armRecipTableQ15[64];
extern q31_t armRecipTableQ31[64];
extern const q31_t realCoefAQ31[1024];
extern const q31_t realCoefBQ31[1024];

#endif

