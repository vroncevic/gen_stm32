# makefile
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

RM := rm -rf

-include sources.mk
-include source/subdir.mk
-include includes/STM32F4xx_StdPeriph_Driver/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
    ifneq ($(strip $(C_UPPER_DEPS)),)
        -include $(C_UPPER_DEPS)
    endif
    ifneq ($(strip $(M_DEPS)),)
        -include $(M_DEPS)
    endif
    ifneq ($(strip $(CP_DEPS)),)
        -include $(CP_DEPS)
    endif
    ifneq ($(strip $(MI_DEPS)),)
        -include $(MI_DEPS)
    endif
    ifneq ($(strip $(C_DEPS)),)
        -include $(C_DEPS)
    endif
    ifneq ($(strip $(CC_DEPS)),)
        -include $(CC_DEPS)
    endif
    ifneq ($(strip $(C++_DEPS)),)
        -include $(C++_DEPS)
    endif
    ifneq ($(strip $(M_UPPER_DEPS)),)
        -include $(M_UPPER_DEPS)
    endif
    ifneq ($(strip $(I_DEPS)),)
        -include $(I_DEPS)
    endif
    ifneq ($(strip $(CXX_DEPS)),)
        -include $(CXX_DEPS)
    endif
    ifneq ($(strip $(MII_DEPS)),)
        -include $(MII_DEPS)
    endif
    ifneq ($(strip $(MM_DEPS)),)
        -include $(MM_DEPS)
    endif
    ifneq ($(strip $(CPP_DEPS)),)
        -include $(CPP_DEPS)
    endif
endif

all: latest.hex

latest.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	arm-none-eabi-gcc -L "../scripts" -Tarm_cortex_m4_512.ld -nostartfiles -Wl,--gc-sections -mthumb -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "latest.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

latest.hex: latest.elf
	arm-none-eabi-objcopy -O ihex "latest.elf" "latest.hex"

clean:
	$(RM) $(C_UPPER_DEPS)$(M_DEPS)$(CP_DEPS)$(MI_DEPS)$(C_DEPS)$(CC_DEPS)$(C++_DEPS)$(M_UPPER_DEPS)$(I_DEPS)$(EXECUTABLES)$(OBJS)$(CXX_DEPS)$(MII_DEPS)$(MM_DEPS)$(CPP_DEPS) ${PRO}.elf ${PRO}.hex
	@echo ' '

