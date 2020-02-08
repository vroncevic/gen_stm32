/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * system_stm32f4xx.h
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * system_stm32f4xx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and STMicroelectronics License.
 *
 * system_stm32f4xx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the STMicroelectronics License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SYSTEM_STM32F4XX_H
#define __SYSTEM_STM32F4XX_H

#ifdef __cplusplus
    extern "C" {
#endif

extern uint32_t SystemCoreClock;
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
    }
#endif

#endif

