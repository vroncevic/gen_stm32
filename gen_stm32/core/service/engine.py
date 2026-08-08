# -*- coding: UTF-8 -*-

'''
Module
    engine.py
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
    Defines application service for file generation.
'''

from __future__ import annotations

from collections.abc import Mapping

from gen_stm32.core.model.project_setup import ProjectSetup
from gen_stm32.core.service.isubprocessor import ISubProcessor

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.0.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class Service:
    '''
        Service for orchestrating the file generation process.

        It defines:

            :attributes:
                | _subprocessor - Adapter for subprocessing.
            :methods:
                | execute - Generates and writes user files.
                | is_initialized - Checks if the service is initialized.
    '''

    subprocessor: ISubProcessor

    def __init__(self, subprocessor: ISubProcessor) -> None:
        '''
            Initializes the service.

            :param subprocessor: The subprocessor.
            :exceptions:
                | ValueError: The subprocessor must be provided.
                | TypeError:  The subprocessor must be of type ISubProcessor.
        '''
        ctx: str = 'service::init(...)'
        msg_subprocessor_none: str = 'the subprocessor must be provided'
        msg_subprocessor_istype: str = f'the subprocessor must be of type {ISubProcessor.__name__}'

        if subprocessor is None:
            raise ValueError(f'{ctx} - {msg_subprocessor_none}')

        if not isinstance(subprocessor, ISubProcessor):
            raise TypeError(f'{ctx} - {msg_subprocessor_istype}')

        self._subprocessor = subprocessor

    def execute(self, *, params: ProjectSetup) -> Mapping[str, object]:
        '''
            Generates stm32 configuration files.

            :param params: The ProjectSetup object.
            :return: The result of the execution (return code, stdout, stderr).
            :exceptions: None.
        '''
        return self._subprocessor.run(params=params)

    def is_initialized(self) -> bool:
        '''
            Checks if the service is initialized.

            :return: True if the service is initialized, False otherwise.
            :exceptions: None.
        '''
        return self._subprocessor.is_initialized()
