# -*- coding: UTF-8 -*-

'''
Module
    dependencies.py
Copyright
    Copyright (C) 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
    GenSTM32 bundle dependencies for the gen_stm32 bundle.
'''

from __future__ import annotations

from typing import TypedDict

from ats_utilities.base.setup.bundle import BaseBundle

from gen_stm32.core.service.iservice import IService
from gen_stm32.core.service.isubprocessor import ISubProcessor
from gen_stm32.infrastructure.cli.icli import ICLI

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class GenSTM32BundleDependencies(TypedDict):
    '''
        GenSTM32 bundle dependencies for the gen_stm32 bundle.

        It defines:

            :attributes:
                | base - The base bundle with the base components for the gen_stm32 bundle.
                | service - The service orchestrating the gen_stm32's execution for the gen_stm32 bundle.
                | subprocessor - The adapter executing the gen_stm32's sub-processes for the gen_stm32 bundle.
                | cli - The command-line interface adapter for the gen_stm32 bundle.
    '''

    base: BaseBundle
    service: IService
    subprocessor: ISubProcessor
    cli: ICLI
