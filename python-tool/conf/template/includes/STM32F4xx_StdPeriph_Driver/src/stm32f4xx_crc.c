/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * stm32f4xx_crc.c
 * 
 * This file provides all the CRC firmware functions.
 * 
 * Version V1.0.0
 * Target Processor Cortex-M4/Cortex-M3
 * 
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * stm32f4xx_crc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version and ARM License.
 *
 * stm32f4xx_crc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * See the ARM License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx_crc.h"

void CRC_ResetDR(void) {
    /* Reset CRC generator */
    CRC->CR = CRC_CR_RESET;
}

/**
 * Computes the 32-bit CRC of a given data word(32-bit).
 * Data: data word(32-bit) to compute its CRC
 * retval 32-bit CRC
 */
uint32_t CRC_CalcCRC(uint32_t Data) {
    CRC->DR = Data;
    return (CRC->DR);
}

/**
 * Computes the 32-bit CRC of a given buffer of data word(32-bit).
 * pBuffer: pointer to the buffer containing the data to be computed
 * BufferLength: length of the buffer to be computed
 * retval 32-bit CRC
 */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength) {
    uint32_t index = 0;
    for(index = 0; index < BufferLength; index++) {
        CRC->DR = pBuffer[index];
    }
    return (CRC->DR);
}

/**
 * Returns the current CRC value.
 * None
 * retval 32-bit CRC
 */
uint32_t CRC_GetCRC(void) {
    return (CRC->DR);
}

/**
 * Stores a 8-bit data in the Independent Data(ID) register.
 * IDValue: 8-bit value to be stored in the ID register 
 * retval None
 */
void CRC_SetIDRegister(uint8_t IDValue) {
    CRC->IDR = IDValue;
}

/**
 * Returns the 8-bit data stored in the Independent Data(ID) register
 * None
 * retval 8-bit value of the ID register 
 */
uint8_t CRC_GetIDRegister(void) {
    return (CRC->IDR);
}

