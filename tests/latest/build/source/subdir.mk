# subdir.mk
# Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
#
# latest is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# latest is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program_name.  If not, see <http://www.gnu.org/licenses/>.

INCLUDE_CMSIS = ../includes/CMSIS
INCLUDE_STM32F4XX = ../includes/STM32F4xx
INCLUDE_STM32F4XX_DRV = ../includes/STM32F4xx_StdPeriph_Driver/inc

CPP_SRCS += \
	../source/main.cpp \
	../source/tinynew.cpp

S_UPPER_SRCS += \
	../source/startup_stm32f4xx.S

C_SRCS += \
	../source/syscall.c \
	../source/system_stm32f4xx.c

C_DEPS += \
	./source/syscall.d \
	./source/system_stm32f4xx.d

OBJS += \
	./source/main.o \
	./source/startup_stm32f4xx.o \
	./source/syscall.o \
	./source/system_stm32f4xx.o \
	./source/tinynew.o

CPP_DEPS += \
	./source/main.d \
	./source/tinynew.d

source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-none-eabi-g++ -DHSE_VALUE=8000000 -DSTM32F4 -DARM_MATH_CM4 -DUSE_STDPERIPH_DRIVER -I "${INCLUDE_CMSIS}" -I "${INCLUDE_STM32F4XX}" -I "${INCLUDE_STM32F4XX_DRV}" -O0 -g3 -Wall -c -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MD -fno-common -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -MMD -MP -MF "$(@:%.o=%.d)" -MT "$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -I "${INCLUDE_CMSIS}" -I "${INCLUDE_STM32F4XX}" -I "${INCLUDE_STM32F4XX_DRV}" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -DHSE_VALUE=8000000 -DSTM32F4 -DARM_MATH_CM4 -DUSE_STDPERIPH_DRIVER -I "${INCLUDE_CMSIS}" -I "${INCLUDE_STM32F4XX}" -I "${INCLUDE_STM32F4XX_DRV}" -O0 -g3 -Wall -c -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MD -fno-common -MMD -MP -MF "$(@:%.o=%.d)" -MT "$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

