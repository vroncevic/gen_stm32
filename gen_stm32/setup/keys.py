# -*- coding: UTF-8 -*-

'''
Module
    keys.py
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
    Runtime components and interface constraints for the gen_stm32 bundle.
'''

from __future__ import annotations

from typing import ClassVar
from types import MappingProxyType

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


class GenSTM32BundleKeys:
    '''
        Runtime components and interface constraints for the gen_stm32 bundle.

        It defines:

            :attributes:
                | DEPENDENCY_BASE - The base bundle constant for the gen_stm32 bundle.
                | DEPENDENCY_SERVICE - The service interface constant for the gen_stm32 bundle.
                | DEPENDENCY_SUBPROCESSOR - The subprocessor interface constant for the gen_stm32 bundle.
                | DEPENDENCY_CLI - The cli interface constant for the gen_stm32 bundle.
                | OPTION_INFO_FILE - The info file option constant for the gen_stm32 bundle.
            :methods:
                | get_dependency_to_type - Returns the mapping of the gen_stm32 bundle dependencies to their types.
                | get_option_to_type - Returns the mapping of the gen_stm32 bundle options to their types.
    '''

    # Dependency Keys
    DEPENDENCY_BASE: ClassVar[str] = 'base'
    DEPENDENCY_SERVICE: ClassVar[str] = 'service'
    DEPENDENCY_SUBPROCESSOR: ClassVar[str] = 'subprocessor'
    DEPENDENCY_CLI: ClassVar[str] = 'cli'

    # Option Keys
    OPTION_INFO_FILE: ClassVar[str] = 'info_file'

    @classmethod
    def get_dependency_to_type(cls) -> MappingProxyType[str, type]:
        '''
            Returns the mapping of the gen_stm32 bundle dependencies to their types.

            :return: The mapping of the gen_stm32 bundle dependencies to their types.
            :exceptions: None.
        '''
        return MappingProxyType({
            cls.DEPENDENCY_BASE: BaseBundle,
            cls.DEPENDENCY_SERVICE: IService,
            cls.DEPENDENCY_SUBPROCESSOR: ISubProcessor,
            cls.DEPENDENCY_CLI: ICLI,
        })

    @classmethod
    def get_option_to_type(cls) -> MappingProxyType[str, type]:
        '''
            Returns the mapping of the gen_stm32 bundle options to their types.

            :return: The mapping of the gen_stm32 bundle options to their types.
            :exceptions: None.
        '''
        return MappingProxyType({
            cls.OPTION_INFO_FILE: str,
        })
