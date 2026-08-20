# -*- coding: UTF-8 -*-

'''
Module
    validator.py
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
    Validator for the CLI bundle.
'''

from __future__ import annotations

from collections.abc import Sequence

from ats_utilities.option.imanager import IOptionManager
from ats_utilities.exceptions import ATSValueError, ATSTypeError
from ats_utilities.validation.check_value import not_none
from ats_utilities.validation.check_type import istype

from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.core.service.iservice import IService

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class CLIBundleValidator:
    '''
        Validator for the CLI bundle.

        It defines:

            :methods:
                | validate - Validates the CLI bundle.
                | is_valid - Checks if the CLI bundle is valid.
    '''

    @classmethod
    def validate(cls, bundle: CLIBundle) -> None:
        '''
            Validates the CLI bundle.

            :param bundle: The CLI bundle to be validated.
            :exceptions:
                | ATSValueError: The CLI bundle must be provided and have proper values.
                | ATSTypeError:  The CLI bundle must be an instance of CLIBundle and
                |                its attributes must be instances of their respective types.
        '''
        ctx: str = 'cli_bundle_validator::validate(...)'
        msg_bundle_none: str = 'the cli bundle must be provided'
        msg_bundle_istype: str = 'the cli bundle must be an instance of CLIBundle'
        msg_service_none: str = 'the service must be provided'
        msg_parser_none: str = 'the parser must be provided'
        msg_commands_none: str = 'the commands sequence must be provided'
        msg_service_istype: str = 'the service must be an instance of IService'
        msg_parser_istype: str = 'the parser must be an instance of IOptionManager'
        msg_commands_istype: str = 'the commands sequence must be an instance of CommandBundle'

        not_none(bundle, ctx, msg_bundle_none)
        istype(bundle, CLIBundle, ctx, msg_bundle_istype)

        not_none(bundle.service, ctx, msg_service_none)
        not_none(bundle.parser, ctx, msg_parser_none)
        not_none(bundle.commands, ctx, msg_commands_none)

        istype(bundle.service, IService, ctx, msg_service_istype)
        istype(bundle.parser, IOptionManager, ctx, msg_parser_istype)
        istype(bundle.commands, Sequence, ctx, msg_commands_istype)

    @classmethod
    def is_valid(cls, clibundle: CLIBundle) -> bool:
        '''
            Checks if the clibundle is valid.

            :param clibundle: The clibundle to be checked.
            :return: True if valid, False otherwise.
        '''
        try:
            cls.validate(clibundle)
            return True

        except (ATSValueError, ATSTypeError):
            return False

