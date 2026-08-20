# -*- coding: UTF-8 -*-

'''
Module
    factory.py
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
    Factory for creating the gen_stm32 bundle.
'''

from __future__ import annotations

from ats_utilities.base.setup.factory import BaseBundleFactory
from ats_utilities.base.setup.bundle import BaseBundle
from ats_utilities.base.setup.options import BaseBundleOptions
from ats_utilities.context.bundle import ContextBundle
from ats_utilities.context.factory import ContextBundleFactory

from gen_stm32.setup.bundle import GenSTM32Bundle
from gen_stm32.setup.options import GenSTM32BundleOptions
from gen_stm32.setup.registry import GenSTM32BundleRegistry
from gen_stm32.setup.dependencies import GenSTM32BundleDependencies
from gen_stm32.setup.opt_validator import GenSTM32BundleOptionsValidator
from gen_stm32.setup.keys import GenSTM32BundleKeys
from gen_stm32.core.service.engine import Service
from gen_stm32.infrastructure.subprocessor import SubProcessor
from gen_stm32.infrastructure.cli.engine import CLI
from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.infrastructure.cli.setup.dependencies import CLIBundleDependencies
from gen_stm32.infrastructure.cli.setup.registry import CLIBundleRegistry
from gen_stm32.infrastructure.command.command import CommandBundle
from gen_stm32.infrastructure.command.gen_stm32_command_definition import GenSTM32CommandDefinition
from gen_stm32.infrastructure.command.gen_stm32_command_executor import GenSTM32CommandExecutor

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class GenSTM32BundleFactory:
    '''
        Factory for creating the gen_stm32 bundle.

        It defines:

            :attributes:
                | _info_file - Path to the gen_stm32 info file.
            :methods:
                | create_bundle - Creates the gen_stm32 bundle with optional pre-configured options.
                | get_version - Returns the factory version.
    '''

    _info_file: str = 'gen_stm32/infrastructure/config/gen_stm32.cfg'

    @classmethod
    def create_bundle(cls, options: GenSTM32BundleOptions | None = None) -> GenSTM32Bundle:
        '''
            Creates the gen_stm32 bundle with optional pre-configured options.

            :param options: The pre-configured options for the gen_stm32 bundle.
            :return: The gen_stm32 bundle.
            :exceptions:
                | ATSValueError: The gen_stm32 bundle options must be provided and have proper values.
                | ATSTypeError:  The gen_stm32 bundle options must be an instance of Mapping and its
                |                attributes must be instances of their respective types.
                | ATSValueError: The gen_stm32 bundle dependencies must be provided and have proper values.
                | ATSTypeError:  The gen_stm32 bundle dependencies must be an instance of Mapping and its
                |                attributes must be instances of their respective types.
                | ATSValueError: The gen_stm32 bundle must be provided and have proper values.
                | ATSTypeError:  The gen_stm32 bundle must be an instance of GenSTM32Bundle and
                |                its attributes must be instances of their respective types.
        '''
        if options is not None:
            GenSTM32BundleOptionsValidator.validate(options)

        info_file = options.get(GenSTM32BundleKeys.OPTION_INFO_FILE) if options else cls._info_file

        context_bundle: ContextBundle = ContextBundleFactory.create_bundle()

        base_bundle: BaseBundle = BaseBundleFactory.create_bundle(
            options=BaseBundleOptions(
                info_file=info_file,
                use_generator=True,
                context_bundle=context_bundle
            )
        )

        subprocessor: SubProcessor = SubProcessor(generator=base_bundle.generation_manager)

        service: Service = Service(subprocessor=subprocessor)

        gen_stm32_definition: GenSTM32CommandDefinition = GenSTM32CommandDefinition()

        gen_stm32_bundle: CommandBundle = CommandBundle(
            definition=gen_stm32_definition,
            executor=GenSTM32CommandExecutor(gen_stm32_definition)
        )

        cli_bundle: CLIBundle = CLIBundleRegistry.create_bundle(
            dependencies=CLIBundleDependencies(
                service=service,
                parser=base_bundle.option_manager,
                commands=[gen_stm32_bundle]
            )
        )

        cli: CLI = CLI(cli_bundle)

        return GenSTM32BundleRegistry.create_bundle(
            dependencies=GenSTM32BundleDependencies(
                base=base_bundle,
                service=service,
                subprocessor=subprocessor,
                cli=cli
            )
        )

    @classmethod
    def get_version(cls) -> str:
        '''
            Returns the factory version.

            :return: The factory version.
            :exceptions: None.
        '''
        return __version__
