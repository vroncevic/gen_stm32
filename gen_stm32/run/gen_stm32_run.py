#!/usr/bin/env python
# -*- coding: UTF-8 -*-

'''
Module
    gen_stm32_run.py
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
    Main entry point of tool gen_stm32.
'''

import sys
from typing import List

try:
    from gen_stm32 import GenSTM32
except ImportError as ats_error_message:  # pragma: no cover
    # Force exit python #######################################################
    sys.exit(f'\n{__file__}\n{ats_error_message}\n')  # pragma: no cover

__author__: str = 'Vladimir Roncevic'
__copyright__: str = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__: List[str] = ['Vladimir Roncevic', 'Python Software Foundation']
__license__: str = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__: str = '1.2.5'
__maintainer__: str = 'Vladimir Roncevic'
__email__: str = 'elektron.ronca@gmail.com'
__status__: str = 'Updated'

if __name__ == '__main__':
    TOOL: GenSTM32 = GenSTM32(verbose=False)
    TOOL.process(verbose=False)
