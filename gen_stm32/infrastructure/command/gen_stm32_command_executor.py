# -*- coding: UTF-8 -*-

'''
Module
    gen_stm32_command_executor.py
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
    Defines GenSTM32CommandExecutor class.
'''

from __future__ import annotations

from collections.abc import Mapping

from ats_utilities.utils.reflection import to_str

from gen_stm32.infrastructure.command.icommand_definition import ICommandDefinition
from gen_stm32.core.service.iservice import IService

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class GenSTM32CommandExecutor:
    '''
        Command executor strategy for generating stm32 project files.

        It defines:

            :attributes:
                | definition - The command CLI metadata definition.
            :methods:
                | execute - Executes the subcommand.
                | __str__ - Returns the GenSTM32CommandExecutor as string representation.
    '''

    definition: ICommandDefinition

    def __init__(self, definition: ICommandDefinition) -> None:
        '''
            Initializes the command executor.

            :param definition: The command definition metadata.
        '''
        self.definition = definition

    def execute(self, *, params: Mapping[str, object], service: IService) -> Mapping[str, object]:
        '''
            Executes the subcommand.

            :param params: Subcommand parameters from CLI parser.
            :param service: Command orchestrator service instance.
            :return: The result of the subcommand execution.
        '''
        return service.execute(params=params) if service.is_initialized() else {
            'returncode': 1, 'stdout': '', 'stderr': 'service not initialized'
        }

    def __str__(self) -> str:
        '''
            Returns the GenSTM32CommandExecutor as string representation.

            :return: The GenSTM32CommandExecutor as string representation.
        '''
        return to_str(self)
