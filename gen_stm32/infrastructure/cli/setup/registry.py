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
    Encapsulates core CLI components for simplification of CLI bundle.
'''

from __future__ import annotations

from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.infrastructure.cli.setup.validator import CLIBundleValidator
from gen_stm32.infrastructure.cli.setup.keys import CLIBundleKeys
from gen_stm32.infrastructure.cli.setup.dependencies import CLIBundleDependencies
from gen_stm32.infrastructure.cli.setup.dep_validator import CLIBundleDependenciesValidator

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class CLIBundleRegistry:
    '''
        Encapsulates core CLI components for simplification of CLI bundle.

        It defines:

            :methods:
                | create_bundle - Creates a CLI bundle.
    '''

    @classmethod
    def create_bundle(cls, dependencies: CLIBundleDependencies) -> CLIBundle:
        '''
            Creates a CLI bundle.

            :param dependencies: The CLI bundle dependencies.
            :return: CLI bundle.
            :exceptions:
                | ATSValueError: The CLI bundle dependencies must be provided and have proper values.
                | ATSTypeError:  The CLI bundle dependencies must be an instance of Mapping and its
                |                attributes must be instances of their respective types.
                | ATSValueError: The CLI bundle must be provided and have proper values.
                | ATSTypeError:  The CLI bundle must be an instance of CLIBundle and
                |                its attributes must be instances of their respective types.
        '''
        CLIBundleDependenciesValidator.validate(dependencies)

        bundle: CLIBundle = CLIBundle(
            service=dependencies.get(CLIBundleKeys.DEPENDENCY_SERVICE) if dependencies else None,
            parser=dependencies.get(CLIBundleKeys.DEPENDENCY_PARSER) if dependencies else None,
            commands=dependencies.get(CLIBundleKeys.DEPENDENCY_COMMANDS) if dependencies else None
        )

        CLIBundleValidator.validate(bundle)

        return bundle
