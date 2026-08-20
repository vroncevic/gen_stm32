# -*- coding: UTF-8 -*-

'''
Module
    registry.py
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
    Encapsulates core gen_stm32 components for simplification of gen_stm32 bundle.
'''

from __future__ import annotations

from ats_utilities.base.setup.bundle import BaseBundle

from gen_stm32.core.service.iservice import IService
from gen_stm32.core.service.isubprocessor import ISubProcessor
from gen_stm32.infrastructure.cli.icli import ICLI
from gen_stm32.setup.bundle import GenSTM32Bundle
from gen_stm32.setup.validator import GenSTM32BundleValidator
from gen_stm32.setup.keys import GenSTM32BundleKeys
from gen_stm32.setup.dependencies import GenSTM32BundleDependencies
from gen_stm32.setup.dep_validator import GenSTM32BundleDependenciesValidator

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class GenSTM32BundleRegistry:
    '''
        Encapsulates core gen_stm32 components for simplification of gen_stm32 bundle.

        It defines:

            :methods:
                | create_bundle - Creates the gen_stm32 bundle.
                | get_version - Returns the registry version.
    '''

    @classmethod
    def create_bundle(cls, dependencies: GenSTM32BundleDependencies) -> GenSTM32Bundle:
        '''
            Creates the gen_stm32 bundle.

            :param dependencies: The gen_stm32 bundle dependencies.
            :return: The gen_stm32 bundle.
            :exceptions:
                | ATSValueError: The gen_stm32 bundle dependencies must be provided and have proper values.
                | ATSTypeError:  The gen_stm32 bundle dependencies must be an instance of Mapping and its
                |                attributes must be instances of their respective types.
                | ATSValueError: The gen_stm32 bundle must be provided and have proper values.
                | ATSTypeError:  The gen_stm32 bundle must be an instance of GenSTM32Bundle and
                |                its attributes must be instances of their respective types.
        '''
        GenSTM32BundleDependenciesValidator.validate(dependencies)

        base: BaseBundle | None = dependencies.get(GenSTM32BundleKeys.DEPENDENCY_BASE) if dependencies else None
        service: IService | None = dependencies.get(GenSTM32BundleKeys.DEPENDENCY_SERVICE) if dependencies else None
        subprocessor: ISubProcessor | None = dependencies.get(GenSTM32BundleKeys.DEPENDENCY_SUBPROCESSOR) if dependencies else None
        cli: ICLI | None = dependencies.get(GenSTM32BundleKeys.DEPENDENCY_CLI) if dependencies else None

        bundle: GenSTM32Bundle = GenSTM32Bundle(base=base, service=service, subprocessor=subprocessor, cli=cli)

        GenSTM32BundleValidator.validate(bundle)

        return bundle

    @classmethod
    def get_version(cls) -> str:
        '''
            Returns the registry version.

            :return: The registry version.
            :exceptions: None.
        '''
        return __version__
