# -*- coding: UTF-8 -*-

'''
Module
    read_template_test.py
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
    Defines class ReadTemplateTestCase with attribute(s) and method(s).
    Creates test cases for checking functionalities of ReadTemplate.
Execute
    python3 -m unittest -v read_template_test
'''

import sys
from typing import Any, List, Dict
from os.path import dirname, realpath
from unittest import TestCase, main

try:
    from ats_utilities.config_io.yaml.yaml2object import Yaml2Object
    from ats_utilities.exceptions.ats_value_error import ATSValueError
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from gen_stm32.pro.read_template import ReadTemplate
except ImportError as test_error_message:
    # Force close python test #################################################
    sys.exit(f'\n{__file__}\n{test_error_message}\n')

__author__: str = 'Vladimir Roncevic'
__copyright__: str = '(C) 2026, https://vroncevic.github.io/gen_stm8'
__credits__: List[str] = ['Vladimir Roncevic', 'Python Software Foundation']
__license__: str = 'https://github.com/vroncevic/gen_stm8/blob/dev/LICENSE'
__version__: str = '1.2.5'
__maintainer__: str = 'Vladimir Roncevic'
__email__: str = 'elektron.ronca@gmail.com'
__status__: str = 'Updated'


class ReadTemplateTestCase(TestCase):
    '''
        Defines class ReadTemplateTestCase with attribute(s) and method(s).
        Creates test cases for checking functionalities of ReadTemplate.
        ReadTemplate unit tests.

        It defines:

            :attributes:
                | None
            :methods:
                | setUp - call before test case.
                | tearDown - call after test case.
                | test_read_template_create - Test read templates create.
                | test_read_template_empty - Test read templates empty.
                | test_read_template_none - Test read templates None.
                | test_read_template - Test read templates.
    '''

    def setUp(self) -> None:
        '''Call before test case.'''

    def tearDown(self) -> None:
        '''Call after test case.'''

    def test_read_template_create(self) -> None:
        '''Test read templates create'''
        template = ReadTemplate()
        self.assertIsNotNone(template)

    def test_read_template_empty(self) -> None:
        '''Test read templates empty'''
        template = ReadTemplate()
        templates: Dict[Any, Any] = {}
        with self.assertRaises(ATSValueError):
            self.assertFalse(
                template.read(templates)
            )

    def test_read_template_none(self) -> None:
        '''Test read templates None'''
        template = ReadTemplate()
        with self.assertRaises(ATSTypeError):
            self.assertFalse(
                template.read(None)  # type: ignore
            )

    def test_read_template(self) -> None:
        '''Test read templates'''
        current_dir: str = dirname(realpath(__file__))
        pro: str = '/../gen_stm32/conf/project.yaml'
        template = ReadTemplate()
        yml2obj = Yaml2Object(f'{current_dir}{pro}')
        self.assertTrue(bool(template.read(yml2obj.read_configuration())))


if __name__ == '__main__':
    main()
