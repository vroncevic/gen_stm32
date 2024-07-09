# -*- coding: UTF-8 -*-

'''
Module
    gen_stm32_setup_test.py
Copyright
    Copyright (C) 2022-2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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
    Defines class STM32SetupTestCase with attribute(s) and method(s).
    Creates test cases for checking functionalities of STM32Setup.
Execute
    python3 -m unittest -v gen_stm32_setup_test
'''

import sys
from typing import List
from unittest import TestCase, main

try:
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from ats_utilities.exceptions.ats_value_error import ATSValueError
    from gen_stm32.pro import STM32Setup
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


class STM32SetupTestCase(TestCase):
    '''
        Defines class STM32SetupTestCase with attribute(s) and method(s).
        Creates test cases for checking functionalities of STM32Setup.
        STM32Setup unit tests.

        It defines:

            :attributes:
                | None
            :methods:
                | setUp - Call before test case.
                | tearDown - Call after test case.
                | test_default_create - Default on create is not None.
                | test_get_reader - Is reader ok.
                | test_get_writer - Is writer ok.
                | test_gen_project_empty - Create project with missing name.
                | test_gen_project_none - Create project with None name.
                | test_gen_project - Create project.
    '''

    def setUp(self) -> None:
        '''Call before test case.'''

    def tearDown(self) -> None:
        '''Call after test case.'''

    def test_default_create(self) -> None:
        '''Default on create is not None'''
        generator: STM32Setup = STM32Setup()
        self.assertIsNotNone(generator)

    def test_get_reader(self) -> None:
        '''Is reader ok'''
        generator: STM32Setup = STM32Setup()
        self.assertIsNotNone(generator.get_reader())

    def test_get_writer(self) -> None:
        '''Is writer ok'''
        generator: STM32Setup = STM32Setup()
        self.assertIsNotNone(generator.get_writer())

    def test_gen_project_empty(self) -> None:
        '''Create project with missing name'''
        generator: STM32Setup = STM32Setup()
        with self.assertRaises(ATSValueError):
            generator.gen_pro_setup("")

    def test_gen_project_none(self) -> None:
        '''Create project with None name'''
        generator: STM32Setup = STM32Setup()
        with self.assertRaises(ATSTypeError):
            generator.gen_pro_setup(None)

    def test_gen_project(self) -> None:
        '''Create project'''
        generator: STM32Setup = STM32Setup()
        self.assertTrue(generator.gen_pro_setup('full_simple'))


if __name__ == '__main__':
    main()
