# -*- coding: UTF-8 -*-

'''
Module
    icli.py
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
    Defines abstract interface ICLI for the command line interface.
'''

from __future__ import annotations

from typing import Protocol, runtime_checkable

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


@runtime_checkable
class ICLI(Protocol):
    '''
        Abstract interface for the command line interface.

        It defines:

            :methods:
                | run - Parses command line arguments and executes selected command strategy.
                | is_initialized - Checks if the CLI is initialized.
    '''

    def run(self) -> dict[str, object]:
        '''
            Parses command line arguments and executes selected command strategy.

            :return: The execution result.
            :exceptions: None.
        '''
        ...

    def is_initialized(self) -> bool:
        '''
            Checks if the CLI is initialized.

            :return: True if initialized, False otherwise.
            :exceptions: None.
        '''
        ...
