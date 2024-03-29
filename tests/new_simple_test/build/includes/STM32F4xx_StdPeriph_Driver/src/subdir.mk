# subdir.mk
# Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
#
# new_simple_test is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# new_simple_test is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program_name.  If not, see <http://www.gnu.org/licenses/>.

INCLUDE_CMSIS = ../includes/CMSIS
INCLUDE_STM32F4XX = ../includes/STM32F4xx
INCLUDE_STM32F4XX_DRV = ../includes/STM32F4xx_StdPeriph_Driver/inc

C_SRCS += \
	../includes/STM32F4xx_StdPeriph_Driver/src/misc.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
	../includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c 

C_DEPS += \
	./includes/STM32F4xx_StdPeriph_Driver/src/misc.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.d \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.d 

OBJS += \
	./includes/STM32F4xx_StdPeriph_Driver/src/misc.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.o \
	./includes/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.o 

includes/STM32F4xx_StdPeriph_Driver/src/%.o: ../includes/STM32F4xx_StdPeriph_Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -DHSE_VALUE=8000000 -DSTM32F4 -DARM_MATH_CM4 -DUSE_STDPERIPH_DRIVER -I "${INCLUDE_CMSIS}" -I "${INCLUDE_STM32F4XX}" -I "${INCLUDE_STM32F4XX_DRV}" -O0 -g3 -Wall -c -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MD -fno-common -MMD -MP -MF "$(@:%.o=%.d)" -MT "$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

