# -*- coding: UTF-8 -*-

'''
Module
    bundle.py
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
    Defines the CLI bundle.
'''

from __future__ import annotations

from collections.abc import Sequence
from dataclasses import dataclass

from ats_utilities.option.imanager import IOptionManager
from ats_utilities.utils.reflection import instance_to_dict

from gen_stm32.core.service.iservice import IService
from gen_stm32.infrastructure.command.command import CommandBundle

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


@dataclass(slots=True, frozen=True, kw_only=True)
class CLIBundle:
    '''
        Defines the CLI bundle.

        It defines:

            :attributes:
                | service - The service orchestrating the generator.
                | parser - The argument parser for parsing CLI command arguments.
                | commands - The sequence of command pairs.
            :methods:
                | to_dict - Converts the CLI bundle to a dictionary.
    '''

    service: IService
    parser: IOptionManager
    commands: Sequence[CommandBundle]

    def to_dict(self) -> dict[str, object]:
        '''
            Converts the CLI bundle to a dictionary.

            :return: Dictionary representation of the CLI bundle.
            :exceptions: None.
        '''
        return instance_to_dict(self)
