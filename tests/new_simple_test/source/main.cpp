/**
 * main.cpp
 * Copyright (C) 2011 STMicroelectronics
 * Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
 * 
 * new_simple_test is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * new_simple_test is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void delay(uint32_t ms);

int main() {
    uint32_t counter;
    GPIO_InitTypeDef ledGPIO;

    // On startup, all peripheral clocks are disabled.
    // Before using a GPIO pin, its peripheral clock must be enabled.
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    // Initialize the GPIO Pins below.
    GPIO_StructInit(&ledGPIO);
    ledGPIO.GPIO_Mode = GPIO_Mode_OUT;
    ledGPIO.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &ledGPIO);

    do {
        counter = 0;
        while (1) {
            counter++;
            GPIO_ToggleBits(GPIOA, GPIO_Pin_6);
            delay(250);
        };
    } while (1);

    return 0;
}

void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}

