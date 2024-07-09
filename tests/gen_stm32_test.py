# -*- coding: UTF-8 -*-

'''
Module
    gen_stm32_test.py
Copyright
    Copyright (C) 2018-2024 Vladimir Roncevic <elektron.ronca@gmail.com>
    gen_stm8 is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    gen_stm8 is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    Defines class GenSTM32TestCase with attribute(s) and method(s).
    Creates test cases for checking functionalities of GenSTM32.
Execute
    python3 -m unittest -v gen_stm32_test
'''

import sys
from typing import List
from os import makedirs, rmdir
from unittest import TestCase, main

try:
    from gen_stm32 import GenSTM32
except ImportError as test_error_message:
    # Force close python test #################################################
    sys.exit(f'\n{__file__}\n{test_error_message}\n')

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2024, https://vroncevic.github.io/gen_stm8'
__credits__: List[str] = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm8/blob/dev/LICENSE'
__version__ = '1.2.4'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class GenSTM32TestCase(TestCase):
    '''
        Defines class GenSTM32TestCase with attribute(s) and method(s).
        Creates test cases for checking functionalities of GenSTM32.
        GenSTM32 unit tests.

        It defines:

            :attributes:
                | None
            :methods:
                | setUp - Call before test case.
                | tearDown - Call after test case.
                | test_default_create - Default on create (not None).
                | test_missing_args - Test missing args.
                | test_wrong_arg - Test wrong arg.
                | test_process - Generate project structure.
                | test_pro_already_exists - Test pro already exists.
    '''

    def setUp(self) -> None:
        '''Call before test case.'''

    def tearDown(self) -> None:
        '''Call after test case.'''

    def test_default_create(self) -> None:
        '''Default on create (not None)'''
        generator: GenSTM32 = GenSTM32()
        self.assertIsNotNone(generator)

    def test_missing_args(self) -> None:
        '''Test missing args'''
        sys.argv.clear()
        generator: GenSTM32 = GenSTM32()
        self.assertFalse(generator.process())

    def test_wrong_arg(self) -> None:
        '''Test wrong arg'''
        sys.argv.clear()
        sys.argv.insert(0, '-d')
        sys.argv.insert(1, 'wrong')
        generator: GenSTM32 = GenSTM32()
        self.assertFalse(generator.process())

    def test_process(self) -> None:
        '''Generate project structure'''
        sys.argv.clear()
        sys.argv.insert(0, '-n')
        sys.argv.insert(1, 'latest')
        generator: GenSTM32 = GenSTM32()
        self.assertTrue(generator.process())

    def test_pro_already_exists(self) -> None:
        '''Test pro already exists'''
        sys.argv.clear()
        sys.argv.insert(0, '-n')
        sys.argv.insert(1, 'fresh_new')
        generator: GenSTM32 = GenSTM32()
        makedirs('fresh_new')
        self.assertFalse(generator.process())
        rmdir('fresh_new')


if __name__ == '__main__':
    main()
