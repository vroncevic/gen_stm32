<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [STM32 project skeleton generator.](#stm32-project-skeleton-generator)
    - [INSTALLATION](#installation)
    - [DEPENDENCIES](#dependencies)
    - [GENERATION FLOW OF STM32 PROJECT SETUP](#generation-flow-of-stm32-project-setup)
    - [TOOL STRUCTURE](#tool-structure)
    - [COPYRIGHT AND LICENCE](#copyright-and-licence)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# STM32 project skeleton generator.

gen_stm32 is toolset for generation STM32 project skeleton for
development of embedded applications.

Developed in python code: 100%.

The README is used to introduce the modules and provide instructions on
how to install the modules, any machine dependencies it may have and any
other information that should be provided before the modules are installed.

![Python package](https://github.com/vroncevic/gen_stm32/workflows/Python%20package/badge.svg?branch=master)
 [![GitHub issues open](https://img.shields.io/github/issues/vroncevic/gen_stm32.svg)](https://github.com/vroncevic/gen_stm32/issues)
 [![GitHub contributors](https://img.shields.io/github/contributors/vroncevic/gen_stm32.svg)](https://github.com/vroncevic/gen_stm32/graphs/contributors)

### INSTALLATION
Navigate to release [page](https://github.com/vroncevic/gen_stm32/releases/tag/v1.0) download and extract release archive.

To install this set of modules type the following:

```
tar xvzf gen_stm32-1.0.tar.gz
cd gen_stm32-1.0/python-tool
cp -R ~/bin/   /root/scripts/gen_stm32/
cp -R ~/conf/  /root/scripts/gen_stm32/
cp -R ~/log/   /root/scripts/gen_stm32/
```

### DEPENDENCIES

This module requires these other modules and libraries:

* ats_utilities https://vroncevic.github.io/ats_utilities

### GENERATION FLOW OF STM32 PROJECT SETUP

Base flow of generation process:

![alt tag](https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/python-tool-docs/gen_stm32_flow.png)

### TOOL STRUCTURE

gen_stm32 is based on Template mechanism:

![alt tag](https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/python-tool-docs/gen_stm32.png)

Generator structure:

```
.
├── bin
│   ├── gen_stm32.py
│   ├── gen_stm32_run.py
│   └── stm32_pro
│       ├── __init__.py
│       ├── read_template.py
│       ├── stm32_setup.py
│       └── write_template.py
├── conf
│   ├── gen_stm32.cfg
│   ├── gen_stm32_util.cfg
│   ├── project_setup.yaml
│   ├── project_template.yaml
│   └── template
│       ├── build
│       │   ├── includes
│       │   │   └── STM32F4xx_StdPeriph_Driver
│       │   │       └── src
│       │   │           └── subdir.template
│       │   ├── Makefile.template
│       │   ├── objects.template
│       │   ├── source
│       │   │   └── subdir.template
│       │   └── sources.template
│       ├── includes
│       │   ├── CMSIS
│       │   │   ├── arm_common_tables.h
│       │   │   ├── arm_math.h
│       │   │   ├── core_cm0.h
│       │   │   ├── core_cm3.h
│       │   │   ├── core_cm4.h
│       │   │   ├── core_cm4_simd.h
│       │   │   ├── core_cmFunc.h
│       │   │   └── core_cmInstr.h
│       │   ├── STM32F4xx
│       │   │   ├── stm32f4xx_conf.h
│       │   │   ├── stm32f4xx.h
│       │   │   └── system_stm32f4xx.h
│       │   └── STM32F4xx_StdPeriph_Driver
│       │       ├── inc
│       │       │   ├── misc.h
│       │       │   ├── stm32f4xx_adc.h
│       │       │   ├── stm32f4xx_can.h
│       │       │   ├── stm32f4xx_crc.h
│       │       │   ├── stm32f4xx_cryp.h
│       │       │   ├── stm32f4xx_dac.h
│       │       │   ├── stm32f4xx_dbgmcu.h
│       │       │   ├── stm32f4xx_dcmi.h
│       │       │   ├── stm32f4xx_dma.h
│       │       │   ├── stm32f4xx_exti.h
│       │       │   ├── stm32f4xx_flash.h
│       │       │   ├── stm32f4xx_fsmc.h
│       │       │   ├── stm32f4xx_gpio.h
│       │       │   ├── stm32f4xx_hash.h
│       │       │   ├── stm32f4xx_i2c.h
│       │       │   ├── stm32f4xx_iwdg.h
│       │       │   ├── stm32f4xx_pwr.h
│       │       │   ├── stm32f4xx_rcc.h
│       │       │   ├── stm32f4xx_rng.h
│       │       │   ├── stm32f4xx_rtc.h
│       │       │   ├── stm32f4xx_sdio.h
│       │       │   ├── stm32f4xx_spi.h
│       │       │   ├── stm32f4xx_syscfg.h
│       │       │   ├── stm32f4xx_tim.h
│       │       │   ├── stm32f4xx_usart.h
│       │       │   └── stm32f4xx_wwdg.h
│       │       └── src
│       │           ├── misc.c
│       │           ├── stm32f4xx_adc.c
│       │           ├── stm32f4xx_can.c
│       │           ├── stm32f4xx_crc.c
│       │           ├── stm32f4xx_cryp_aes.c
│       │           ├── stm32f4xx_cryp.c
│       │           ├── stm32f4xx_cryp_des.c
│       │           ├── stm32f4xx_cryp_tdes.c
│       │           ├── stm32f4xx_dac.c
│       │           ├── stm32f4xx_dbgmcu.c
│       │           ├── stm32f4xx_dcmi.c
│       │           ├── stm32f4xx_dma.c
│       │           ├── stm32f4xx_exti.c
│       │           ├── stm32f4xx_flash.c
│       │           ├── stm32f4xx_fsmc.c
│       │           ├── stm32f4xx_gpio.c
│       │           ├── stm32f4xx_hash.c
│       │           ├── stm32f4xx_hash_md5.c
│       │           ├── stm32f4xx_hash_sha1.c
│       │           ├── stm32f4xx_i2c.c
│       │           ├── stm32f4xx_iwdg.c
│       │           ├── stm32f4xx_pwr.c
│       │           ├── stm32f4xx_rcc.c
│       │           ├── stm32f4xx_rng.c
│       │           ├── stm32f4xx_rtc.c
│       │           ├── stm32f4xx_sdio.c
│       │           ├── stm32f4xx_spi.c
│       │           ├── stm32f4xx_syscfg.c
│       │           ├── stm32f4xx_tim.c
│       │           ├── stm32f4xx_usart.c
│       │           └── stm32f4xx_wwdg.c
│       ├── scripts
│       │   └── arm_cortex_m4_512.template
│       └── source
│           ├── main.template
│           ├── startup_stm32f4xx.template
│           ├── syscall.template
│           ├── system_stm32f4xx.template
│           └── tinynew.template
└── log
    └── gen_stm32.log
```

### COPYRIGHT AND LICENCE

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Copyright (C) 2019 by https://vroncevic.github.io/gen_stm32/

This tool is free software; you can redistribute it and/or modify
it under the same terms as Python itself, either Python version 2.7/3.4 or,
at your option, any later version of Python 3 you may have available.

:sparkles:
