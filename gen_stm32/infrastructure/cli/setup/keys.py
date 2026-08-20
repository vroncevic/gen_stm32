# -*- coding: UTF-8 -*-

'''
Module
    keys.py
Copyright
    Copyright (C) 2017 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
    Runtime components and interface constraints for the CLI bundle.
'''

from __future__ import annotations

from collections.abc import Sequence
from typing import ClassVar
from types import MappingProxyType

from ats_utilities.option.imanager import IOptionManager

from gen_stm32.core.service.iservice import IService

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.2.6'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class CLIBundleKeys:
    '''
        Runtime components and interface constraints for the CLI bundle.

        It defines:

            :attributes:
                | DEPENDENCY_SERVICE - The service interface constant of the CLI bundle.
                | DEPENDENCY_PARSER - The parser interface constant of the CLI bundle.
                | DEPENDENCY_COMMANDS - The commands constant of the CLI bundle.
                | OPTION_SERVICE - The service option constant of the CLI bundle.
                | OPTION_PARSER - The parser option constant of the CLI bundle.
            :methods:
                | get_dependency_to_type - Returns the mapping of the CLI bundle dependencies to their types.
                | get_option_to_type - Returns the mapping of the CLI bundle options to their types.
    '''

    # Dependency Keys
    DEPENDENCY_SERVICE: ClassVar[str] = 'service'
    DEPENDENCY_PARSER: ClassVar[str] = 'parser'
    DEPENDENCY_COMMANDS: ClassVar[str] = 'commands'

    # Option Keys
    OPTION_SERVICE: ClassVar[str] = 'service'
    OPTION_PARSER: ClassVar[str] = 'parser'

    @classmethod
    def get_dependency_to_type(cls) -> MappingProxyType[str, type]:
        '''
            Returns the mapping of the CLI bundle dependencies to their types.

            :return: The mapping of the CLI bundle dependencies to their types.
            :exceptions: None.
        '''
        return MappingProxyType({
            cls.DEPENDENCY_SERVICE: IService,
            cls.DEPENDENCY_PARSER: IOptionManager,
            cls.DEPENDENCY_COMMANDS: Sequence,
        })

    @classmethod
    def get_option_to_type(cls) -> MappingProxyType[str, type]:
        '''
            Returns the mapping of the CLI bundle options to their types.

            :return: The mapping of the CLI bundle options to their types.
            :exceptions: None.
        '''
        return MappingProxyType({
            cls.OPTION_SERVICE: IService,
            cls.OPTION_PARSER: IOptionManager,
        })
