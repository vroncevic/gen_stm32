# -*- coding: UTF-8 -*-

'''
Module
    dep_validator.py
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
    Validator for the gen_stm32 bundle dependencies.
'''

from __future__ import annotations

from collections.abc import Mapping

from ats_utilities.validation.check_type import istype
from ats_utilities.validation.check_value import not_none

from gen_stm32.setup.dependencies import GenSTM32BundleDependencies
from gen_stm32.setup.keys import GenSTM32BundleKeys

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class GenSTM32BundleDependenciesValidator:
    '''
        Validator for the gen_stm32 bundle dependencies.

        It defines:

            :methods:
                | validate - Validates the gen_stm32 bundle dependencies.
    '''

    @classmethod
    def validate(cls, dependencies: GenSTM32BundleDependencies) -> None:
        '''
            Validates the gen_stm32 bundle dependencies.

            :param dependencies: The gen_stm32 bundle dependencies to be validated.
            :exceptions:
                | ATSValueError: The gen_stm32 bundle dependencies must be provided and have proper values.
                | ATSTypeError:  The gen_stm32 bundle dependencies must be an instance of Mapping and its
                |                attributes must be instances of their respective types.
        '''
        ctx: str = 'gen_stm32_bundle_dependencies_validator::validate(...)'
        msg_dependencies_none: str = 'the gen_stm32 bundle dependencies must be provided'
        msg_dependencies_istype: str = 'the gen_stm32 bundle dependencies must be a Mapping'

        not_none(dependencies, ctx, msg_dependencies_none)
        istype(dependencies, Mapping, ctx, msg_dependencies_istype)

        for attr_name, expected_type in GenSTM32BundleKeys.get_dependency_to_type().items():
            msg_attr_name_none: str = f'the {attr_name.replace("_", " ")} must be provided'
            msg_attr_name_istype: str = f'the {attr_name.replace("_", " ")} must be an instance of {expected_type.__name__}'

            attribute = dependencies.get(attr_name)

            not_none(attribute, ctx, msg_attr_name_none)
            istype(attribute, expected_type, ctx, msg_attr_name_istype)
