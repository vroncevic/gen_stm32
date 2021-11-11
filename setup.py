#!/usr/bin/env python
# -*- coding: UTF-8 -*-

'''
 Module
     setup.py
 Copyright
     Copyright (C) 2018 Vladimir Roncevic <elektron.ronca@gmail.com>
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
     Define setup for tool gen_stm32.
'''

from __future__ import print_function
import sys
from os.path import abspath, dirname, join, exists
from setuptools import setup

__author__ = 'Vladimir Roncevic'
__copyright__ = 'Copyright 2018, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.1.1'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'

def install_directory():
    '''
        Return the installation directory, or None.

        :return: path (success) | None.
        :rtype: <str> | <NoneType>
        :exceptions: None
    '''
    py_version = '{0}.{1}'.format(sys.version_info[0], sys.version_info[1])
    if '--github' in sys.argv:
        index = sys.argv.index('--github')
        sys.argv.pop(index)
        paths = (
            '{0}/lib/python{1}/dist-packages/'.format(sys.prefix, py_version),
            '{0}/lib/python{1}/site-packages/'.format(sys.prefix, py_version)
        )
    else:
        paths = (s for s in (
            '{0}/local/lib/python{1}/dist-packages/'.format(
                sys.prefix, py_version
            ),
            '{0}/local/lib/python{1}/site-packages/'.format(
                sys.prefix, py_version
            )
        ))
    message = None
    for path in paths:
        message = '[setup] check path {0}'.format(path)
        print(message)
        if exists(path):
            message = '[setup] use path {0}'.format(path)
            print(message)
            return path
    message = '[setup] no installation path found, check {0}\n'.format(
        sys.prefix
    )
    print(message)
    return None

INSTALL_DIR = install_directory()
TOOL_DIR = 'gen_stm32/'
BUILD = 'conf/template/build/'
BUILD_SRC = 'conf/template/build/includes/STM32F4xx_StdPeriph_Driver/src/'
BUILD_INC = 'conf/template/build/source/'
CMSIS = 'conf/template/includes/CMSIS/'
STM32F4XX = 'conf/template/includes/STM32F4xx/'
DRIVER_INC = 'conf/template/includes/STM32F4xx_StdPeriph_Driver/inc/'
DRIVER_SRC = 'conf/template/includes/STM32F4xx_StdPeriph_Driver/src/'
SCRIPTS = 'conf/template/scripts/'
SOURCE = 'conf/template/source/'
if not bool(INSTALL_DIR):
    print('[setup] force exit from install process')
    sys.exit(127)
THIS_DIR, LONG_DESCRIPTION = abspath(dirname(__file__)), None
with open(join(THIS_DIR, 'README.md')) as readme:
    LONG_DESCRIPTION = readme.read()
PROGRAMMING_LANG = 'Programming Language :: Python ::'
VERSIONS = ['2.7', '3', '3.2', '3.3', '3.4']
SUPPORTED_PY_VERSIONS = [
    '{0} {1}'.format(PROGRAMMING_LANG, VERSION) for VERSION in VERSIONS
]
LICENSE_PREFIX = 'License :: OSI Approved ::'
LICENSES = [
    'GNU Lesser General Public License v2 (LGPLv2)',
    'GNU Lesser General Public License v2 or later (LGPLv2+)',
    'GNU Lesser General Public License v3 (LGPLv3)',
    'GNU Lesser General Public License v3 or later (LGPLv3+)',
    'GNU Library or Lesser General Public License (LGPL)'
]
APPROVED_LICENSES = [
    '{0} {1}'.format(LICENSE_PREFIX, LICENSE) for LICENSE in LICENSES
]
PYP_CLASSIFIERS = SUPPORTED_PY_VERSIONS + APPROVED_LICENSES
setup(
    name='gen_stm32',
    version='1.1.1',
    description='STM32 project skeleton generator',
    author='Vladimir Roncevic',
    author_email='elektron.ronca@gmail.com',
    url='https://vroncevic.github.io/gen_stm32/',
    license='GPL 2018 Free software to use and distributed it.',
    long_description=LONG_DESCRIPTION,
    long_description_content_type='text/markdown',
    keywords='STM, STM32, project, C, Unix, Linux',
    platforms='POSIX',
    classifiers=PYP_CLASSIFIERS,
    packages=['gen_stm32', 'gen_stm32.pro', 'gen_stm32.pro.config'],
    install_requires=['ats-utilities'],
    package_data = {
        'gen_stm32': [
            'conf/gen_stm32.cfg',
            'conf/gen_stm32_util.cfg',
            'conf/project.yaml',
            '{0}{1}'.format(BUILD, 'Makefile.template'),
            '{0}{1}'.format(BUILD, 'objects.template'),
            '{0}{1}'.format(BUILD, 'sources.template'),
            '{0}{1}'.format(BUILD_INC, 'subdir.template'),
            '{0}{1}'.format(BUILD_SRC, 'subdir.template'),
            '{0}{1}'.format(CMSIS, 'arm_common_tables.template'),
            '{0}{1}'.format(CMSIS, 'arm_math.template'),
            '{0}{1}'.format(CMSIS, 'core_cm0.template'),
            '{0}{1}'.format(CMSIS, 'core_cm3.template'),
            '{0}{1}'.format(CMSIS, 'core_cm4.template'),
            '{0}{1}'.format(CMSIS, 'core_cm4_simd.template'),
            '{0}{1}'.format(CMSIS, 'core_cmFunc.template'),
            '{0}{1}'.format(CMSIS, 'core_cmInstr.template'),
            '{0}{1}'.format(STM32F4XX, 'stm32f4xx.template'),
            '{0}{1}'.format(STM32F4XX, 'stm32f4xx_conf.template'),
            '{0}{1}'.format(STM32F4XX, 'system_stm32f4xx.template'),
            '{0}{1}'.format(DRIVER_INC, 'misc.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_adc.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_can.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_crc.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_cryp.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_dac.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_dbgmcu.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_dcmi.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_dma.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_exti.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_flash.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_fsmc.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_gpio.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_hash.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_i2c.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_iwdg.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_pwr.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_rcc.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_rng.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_rtc.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_sdio.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_spi.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_syscfg.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_tim.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_usart.template'),
            '{0}{1}'.format(DRIVER_INC, 'stm32f4xx_wwdg.template'),
            '{0}{1}'.format(DRIVER_SRC, 'misc.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_adc.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_can.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_crc.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_cryp_aes.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_cryp_des.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_cryp_tdes.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_cryp.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_dac.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_dbgmcu.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_dcmi.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_dma.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_exti.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_flash.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_fsmc.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_gpio.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_hash_md5.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_hash_sha1.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_hash.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_i2c.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_iwdg.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_pwr.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_rcc.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_rng.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_rtc.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_sdio.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_spi.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_syscfg.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_tim.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_usart.template'),
            '{0}{1}'.format(DRIVER_SRC, 'stm32f4xx_wwdg.template'),
            '{0}{1}'.format(SCRIPTS, 'arm_cortex_m4_512.template'),
            '{0}{1}'.format(SOURCE, 'main.template'),
            '{0}{1}'.format(SOURCE, 'startup_stm32f4xx.template'),
            '{0}{1}'.format(SOURCE, 'syscall.template'),
            '{0}{1}'.format(SOURCE, 'system_stm32f4xx.template'),
            '{0}{1}'.format(SOURCE, 'tinynew.template'),
            'log/gen_stm32.log'
        ]
    },
    data_files=[('/usr/local/bin/', ['gen_stm32/run/gen_stm32_run.py'])]
)
