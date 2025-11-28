#!/usr/bin/env python
# -*- coding: UTF-8 -*-

'''
Module
    setup.py
Copyright
    Copyright (C) 2018 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
    gen_stm32 is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    gen_stm32 is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    Defines setup for tool gen_stm32.
'''

from __future__ import print_function
from typing import List, Optional
from os.path import abspath, dirname, join
from setuptools import setup

__author__: str = 'Vladimir Roncevic'
__copyright__: str = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__: List[str] = ['Vladimir Roncevic', 'Python Software Foundation']
__license__: str = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__: str = '1.2.5'
__maintainer__: str = 'Vladimir Roncevic'
__email__: str = 'elektron.ronca@gmail.com'
__status__: str = 'Updated'

TOOL_DIR: str = 'gen_stm32/'
CONF: str = 'conf'
BUILD: str = 'conf/template/build/'
BUILD_SRC: str = 'conf/template/build/includes/STM32F4xx_StdPeriph_Driver/src/'
BUILD_INC: str = 'conf/template/build/source/'
CMSIS: str = 'conf/template/includes/CMSIS/'
STM32F4XX: str = 'conf/template/includes/STM32F4xx/'
DRIVER_INC: str = 'conf/template/includes/STM32F4xx_StdPeriph_Driver/inc/'
DRIVER_SRC: str = 'conf/template/includes/STM32F4xx_StdPeriph_Driver/src/'
SCRIPTS: str = 'conf/template/scripts/'
SOURCE: str = 'conf/template/source/'
LOG: str = 'log'
THIS_DIR: str = abspath(dirname(__file__))
long_description: Optional[str] = None
with open(join(THIS_DIR, 'README.md'), encoding='utf-8') as readme:
    long_description = readme.read()
PROGRAMMING_LANG: str = 'Programming Language :: Python ::'
VERSIONS: List[str] = ['3.10', '3.11', '3.12']
SUPPORTED_PY_VERSIONS: List[str] = [
    f'{PROGRAMMING_LANG} {VERSION}' for VERSION in VERSIONS
]
PYP_CLASSIFIERS: List[str] = SUPPORTED_PY_VERSIONS
setup(
    name='gen_stm32',
    version='1.2.5',
    description='STM32 project skeleton generator',
    author='Vladimir Roncevic',
    author_email='elektron.ronca@gmail.com',
    url='https://vroncevic.github.io/gen_stm32/',
    license='GPL-3.0-or-later',
    long_description=long_description,
    long_description_content_type='text/markdown',
    keywords='STM, STM32, project, C, Unix, Linux',
    platforms='POSIX',
    classifiers=PYP_CLASSIFIERS,
    packages=['gen_stm32', 'gen_stm32.pro'],
    install_requires=['ats-utilities'],
    package_data={
        'gen_stm32': [
            'py.typed',
            f'{CONF}/gen_stm32.logo',
            f'{CONF}/gen_stm32.cfg',
            f'{CONF}/gen_stm32_util.cfg',
            f'{CONF}/project.yaml',
            f'{BUILD}Makefile.template',
            f'{BUILD}objects.template',
            f'{BUILD}sources.template',
            f'{BUILD_INC}subdir.template',
            f'{BUILD_INC}subdir.template',
            f'{CMSIS}arm_common_tables.template',
            f'{CMSIS}arm_math.template',
            f'{CMSIS}core_cm0.template',
            f'{CMSIS}core_cm3.template',
            f'{CMSIS}core_cm4.template',
            f'{CMSIS}core_cm4_simd.template',
            f'{CMSIS}core_cmFunc.template',
            f'{CMSIS}core_cmInstr.template',
            f'{STM32F4XX}stm32f4xx.template',
            f'{STM32F4XX}stm32f4xx_conf.template',
            f'{STM32F4XX}system_stm32f4xx.template',
            f'{DRIVER_INC}misc.template',
            f'{DRIVER_INC}stm32f4xx_adc.template',
            f'{DRIVER_INC}stm32f4xx_can.template',
            f'{DRIVER_INC}stm32f4xx_crc.template',
            f'{DRIVER_INC}stm32f4xx_cryp.template',
            f'{DRIVER_INC}stm32f4xx_dac.template',
            f'{DRIVER_INC}stm32f4xx_dbgmcu.template',
            f'{DRIVER_INC}stm32f4xx_dcmi.template',
            f'{DRIVER_INC}stm32f4xx_dma.template',
            f'{DRIVER_INC}stm32f4xx_exti.template',
            f'{DRIVER_INC}stm32f4xx_flash.template',
            f'{DRIVER_INC}stm32f4xx_fsmc.template',
            f'{DRIVER_INC}stm32f4xx_gpio.template',
            f'{DRIVER_INC}stm32f4xx_hash.template',
            f'{DRIVER_INC}stm32f4xx_i2c.template',
            f'{DRIVER_INC}stm32f4xx_iwdg.template',
            f'{DRIVER_INC}stm32f4xx_pwr.template',
            f'{DRIVER_INC}stm32f4xx_rcc.template',
            f'{DRIVER_INC}stm32f4xx_rng.template',
            f'{DRIVER_INC}stm32f4xx_rtc.template',
            f'{DRIVER_INC}stm32f4xx_sdio.template',
            f'{DRIVER_INC}stm32f4xx_spi.template',
            f'{DRIVER_INC}stm32f4xx_syscfg.template',
            f'{DRIVER_INC}stm32f4xx_tim.template',
            f'{DRIVER_INC}stm32f4xx_usart.template',
            f'{DRIVER_INC}stm32f4xx_wwdg.template',
            f'{DRIVER_INC}misc.template',
            f'{DRIVER_INC}stm32f4xx_adc.template',
            f'{DRIVER_INC}stm32f4xx_can.template',
            f'{DRIVER_INC}stm32f4xx_crc.template',
            f'{DRIVER_INC}stm32f4xx_cryp_aes.template',
            f'{DRIVER_INC}stm32f4xx_cryp_des.template',
            f'{DRIVER_INC}stm32f4xx_cryp_tdes.template',
            f'{DRIVER_INC}stm32f4xx_cryp.template',
            f'{DRIVER_INC}stm32f4xx_dac.template',
            f'{DRIVER_INC}stm32f4xx_dbgmcu.template',
            f'{DRIVER_INC}stm32f4xx_dcmi.template',
            f'{DRIVER_INC}stm32f4xx_dma.template',
            f'{DRIVER_INC}stm32f4xx_exti.template',
            f'{DRIVER_INC}stm32f4xx_flash.template',
            f'{DRIVER_INC}stm32f4xx_fsmc.template',
            f'{DRIVER_INC}stm32f4xx_gpio.template',
            f'{DRIVER_INC}stm32f4xx_hash_md5.template',
            f'{DRIVER_INC}stm32f4xx_hash_sha1.template',
            f'{DRIVER_INC}stm32f4xx_hash.template',
            f'{DRIVER_INC}stm32f4xx_i2c.template',
            f'{DRIVER_INC}stm32f4xx_iwdg.template',
            f'{DRIVER_INC}stm32f4xx_pwr.template',
            f'{DRIVER_INC}stm32f4xx_rcc.template',
            f'{DRIVER_INC}stm32f4xx_rng.template',
            f'{DRIVER_INC}stm32f4xx_rtc.template',
            f'{DRIVER_INC}stm32f4xx_sdio.template',
            f'{DRIVER_INC}stm32f4xx_spi.template',
            f'{DRIVER_INC}stm32f4xx_syscfg.template',
            f'{DRIVER_INC}stm32f4xx_tim.template',
            f'{DRIVER_INC}stm32f4xx_usart.template',
            f'{DRIVER_INC}stm32f4xx_wwdg.template',
            f'{SCRIPTS}arm_cortex_m4_512.template',
            f'{SOURCE}main.template',
            f'{SOURCE}startup_stm32f4xx.template',
            f'{SOURCE}syscall.template',
            f'{SOURCE}system_stm32f4xx.template',
            f'{SOURCE}tinynew.template',
            f'{LOG}/gen_stm32.log'
        ]
    },
    data_files=[
        ('/usr/local/bin/', [f'{TOOL_DIR}run/gen_stm32_run.py'])
    ]
)
