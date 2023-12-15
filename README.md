<img align="right" src="https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/docs/gen_stm32_logo.png" width="25%">

# STM32 project skeleton generator

**gen_stm32** is toolset for generation STM32 project skeleton for
development of embedded applications.

Developed in **[python](https://www.python.org/)** code.

The README is used to introduce the modules and provide instructions on
how to install the modules, any machine dependencies it may have and any
other information that should be provided before the modules are installed.

[![gen_stm32 python checker](https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python_checker.yml/badge.svg)](https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python_checker.yml) [![gen_stm32 package checker](https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_package_checker.yml/badge.svg)](https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_package.yml) [![GitHub issues open](https://img.shields.io/github/issues/vroncevic/gen_stm32.svg)](https://github.com/vroncevic/gen_stm32/issues) [![GitHub contributors](https://img.shields.io/github/contributors/vroncevic/gen_stm32.svg)](https://github.com/vroncevic/gen_stm32/graphs/contributors)

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Installation](#installation)
    - [Install using pip](#install-using-pip)
    - [Install using build](#install-using-build)
    - [Install using py setup](#install-using-py-setup)
    - [Install using docker](#install-using-docker)
- [Dependencies](#dependencies)
- [Tool structure](#tool-structure)
- [Docs](#docs)
- [Copyright and licence](#copyright-and-licence)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

### Installation

![debian linux os](https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/docs/debtux.png)

[![gen_stm32 python3 build](https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python3_build.yml/badge.svg)](https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python3_build.yml)

Currently there are three ways to install package
* Install process based on using pip mechanism
* Install process based on build mechanism
* Install process based on setup.py mechanism
* Install process based on docker mechanism

##### Install using pip

Python package is located at **[pypi.org](https://pypi.org/project/gen_stm32/)**.

You can install by using pip

```bash
#python3
pip3 install gen_stm32
```

##### Install using build

Navigate to release **[page](https://github.com/vroncevic/gen_stm32/releases/)** download and extract release archive.

To install **gen_stm32** type the following

```bash
tar xvzf gen_stm32-x.y.z.tar.gz
cd gen_stm32-x.y.z/
# python3
wget https://bootstrap.pypa.io/get-pip.py
python3 get-pip.py 
python3 -m pip install --upgrade setuptools
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade build
pip3 install -r requirements.txt
python3 -m build --no-isolation --wheel
pip3 install ./dist/gen_stm32-*-py3-none-any.whl
rm -f get-pip.py
chmod 755 /usr/local/lib/python3.10/dist-packages/usr/local/bin/gen_stm32_run.py
ln -s /usr/local/lib/python3.10/dist-packages/usr/local/bin/gen_stm32_run.py /usr/local/bin/gen_stm32_run.py
```

##### Install using py setup

Navigate to **[release page](https://github.com/vroncevic/gen_stm32/releases)** download and extract release archive.

To install **gen_stm32** locate and run setup.py with arguments

```bash
tar xvzf gen_stm32-x.y.z.tar.gz
cd gen_stm32-x.y.z
# python3
pip3 install -r requirements.txt
python3 setup.py install_lib
python3 setup.py install_egg_info
```

##### Install using docker

You can use Dockerfile to create image/container.

### Dependencies

This module requires these other modules and libraries

* ats_utilities https://vroncevic.github.io/ats_utilities

### Tool structure

gen_stm32 is based on OOP.

Generator structure

```bash
gen_stm32/
    ├── conf/
    │   ├── gen_stm32.logo
    │   ├── gen_stm32.cfg
    │   ├── gen_stm32_util.cfg
    │   ├── project.yaml
    │   └── template/
    │       ├── build/
    │       │   ├── includes/
    │       │   │   └── STM32F4xx_StdPeriph_Driver/
    │       │   │       └── src/
    │       │   │           └── subdir.template
    │       │   ├── Makefile.template
    │       │   ├── objects.template
    │       │   ├── source/
    │       │   │   └── subdir.template
    │       │   └── sources.template
    │       ├── includes/
    │       │   ├── CMSIS/
    │       │   │   ├── arm_common_tables.template
    │       │   │   ├── arm_math.template
    │       │   │   ├── core_cm0.template
    │       │   │   ├── core_cm3.template
    │       │   │   ├── core_cm4_simd.template
    │       │   │   ├── core_cm4.template
    │       │   │   ├── core_cmFunc.template
    │       │   │   └── core_cmInstr.template
    │       │   ├── STM32F4xx/
    │       │   │   ├── stm32f4xx_conf.template
    │       │   │   ├── stm32f4xx.template
    │       │   │   └── system_stm32f4xx.template
    │       │   └── STM32F4xx_StdPeriph_Driver/
    │       │       ├── inc/
    │       │       │   ├── misc.template
    │       │       │   ├── stm32f4xx_adc.template
    │       │       │   ├── stm32f4xx_can.template
    │       │       │   ├── stm32f4xx_crc.template
    │       │       │   ├── stm32f4xx_cryp.template
    │       │       │   ├── stm32f4xx_dac.template
    │       │       │   ├── stm32f4xx_dbgmcu.template
    │       │       │   ├── stm32f4xx_dcmi.template
    │       │       │   ├── stm32f4xx_dma.template
    │       │       │   ├── stm32f4xx_exti.template
    │       │       │   ├── stm32f4xx_flash.template
    │       │       │   ├── stm32f4xx_fsmc.template
    │       │       │   ├── stm32f4xx_gpio.template
    │       │       │   ├── stm32f4xx_hash.template
    │       │       │   ├── stm32f4xx_i2c.template
    │       │       │   ├── stm32f4xx_iwdg.template
    │       │       │   ├── stm32f4xx_pwr.template
    │       │       │   ├── stm32f4xx_rcc.template
    │       │       │   ├── stm32f4xx_rng.template
    │       │       │   ├── stm32f4xx_rtc.template
    │       │       │   ├── stm32f4xx_sdio.template
    │       │       │   ├── stm32f4xx_spi.template
    │       │       │   ├── stm32f4xx_syscfg.template
    │       │       │   ├── stm32f4xx_tim.template
    │       │       │   ├── stm32f4xx_usart.template
    │       │       │   └── stm32f4xx_wwdg.template
    │       │       └── src/
    │       │           ├── misc.template
    │       │           ├── stm32f4xx_adc.template
    │       │           ├── stm32f4xx_can.template
    │       │           ├── stm32f4xx_crc.template
    │       │           ├── stm32f4xx_cryp_aes.template
    │       │           ├── stm32f4xx_cryp_des.template
    │       │           ├── stm32f4xx_cryp_tdes.template
    │       │           ├── stm32f4xx_cryp.template
    │       │           ├── stm32f4xx_dac.template
    │       │           ├── stm32f4xx_dbgmcu.template
    │       │           ├── stm32f4xx_dcmi.template
    │       │           ├── stm32f4xx_dma.template
    │       │           ├── stm32f4xx_exti.template
    │       │           ├── stm32f4xx_flash.template
    │       │           ├── stm32f4xx_fsmc.template
    │       │           ├── stm32f4xx_gpio.template
    │       │           ├── stm32f4xx_hash_md5.template
    │       │           ├── stm32f4xx_hash_sha1.template
    │       │           ├── stm32f4xx_hash.template
    │       │           ├── stm32f4xx_i2c.template
    │       │           ├── stm32f4xx_iwdg.template
    │       │           ├── stm32f4xx_pwr.template
    │       │           ├── stm32f4xx_rcc.template
    │       │           ├── stm32f4xx_rng.template
    │       │           ├── stm32f4xx_rtc.template
    │       │           ├── stm32f4xx_sdio.template
    │       │           ├── stm32f4xx_spi.template
    │       │           ├── stm32f4xx_syscfg.template
    │       │           ├── stm32f4xx_tim.template
    │       │           ├── stm32f4xx_usart.template
    │       │           └── stm32f4xx_wwdg.template
    │       ├── scripts/
    │       │   └── arm_cortex_m4_512.template
    │       └── source/
    │           ├── main.template
    │           ├── startup_stm32f4xx.template
    │           ├── syscall.template
    │           ├── system_stm32f4xx.template
    │           └── tinynew.template
    ├── __init__.py
    ├── log/
    │   └── gen_stm32.log
    ├── pro/
    │   ├── __init__.py
    │   ├── read_template.py
    │   └── write_template.py
    └── run/
        └── gen_stm32_run.py

    19 directories, 89 files
```

### Docs

[![Documentation Status](https://readthedocs.org/projects/gen-stm32/badge/?version=latest)](https://gen-stm32.readthedocs.io/en/latest/?badge=latest)

More documentation and info at

* [gen_stm32.readthedocs.io](https://gen-stm32.readthedocs.io/)
* [www.python.org](https://www.python.org/)

### Copyright and licence

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Copyright (C) 2018 - 2024 by [vroncevic.github.io/gen_stm32](https://vroncevic.github.io/gen_stm32)

**gen_stm32** is free software; you can redistribute it and/or modify
it under the same terms as Python itself, either Python version 3.x or,
at your option, any later version of Python 3 you may have available.

Lets help and support PSF.

[![Python Software Foundation](https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/docs/psf-logo-alpha.png)](https://www.python.org/psf/)

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.python.org/psf/donations/)