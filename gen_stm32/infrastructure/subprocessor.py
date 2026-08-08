# -*- coding: UTF-8 -*-

'''
Module
    subprocessor.py
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
    Defines sub-processor adapter implementing ISubProcessor.
'''

from __future__ import annotations

from collections.abc import Mapping
from logging import INFO
from os import walk
from os.path import dirname, realpath, relpath
from datetime import datetime

from ats_utilities.generation.imanager import IGeneratorManager
from ats_utilities.generation.data import GeneratorData
from ats_utilities.logger.ilogger import ILogger
from ats_utilities.validation.check_value import not_none
from ats_utilities.validation.check_type import istype
from ats_utilities.utils.reflection import to_str

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.4.7'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class SubProcessor:
    '''
        Adapter that executes sub-processes.

        It defines:

            :attributes:
                | _scheme - Path to the scheme json file.
                | _templates - Path to the templates tgz file.
                | _generator - Generator manager used to generate code from templates.
                | _logger - Logger used to log messages.
            :methods:
                | run - Executes a sub-process.
                | is_initialized - Checks if the subprocessor is initialized.
                | __str__ - Returns the SubProcessor as string representation.
    '''

    _scheme: str = 'config/scheme.json'
    _templates: str = 'config/templates.tgz'
    _generator: IGeneratorManager
    _logger: ILogger

    def __init__(self, generator: IGeneratorManager) -> None:
        '''
            Initializes the SubProcessor adapter.

            :param generator: The generator manager.
            :exceptions:
                | ATSValueError: The generator must be provided.
                | ATSTypeError:  The generator must be an instance of IGenerator.
        '''
        ctx: str = 'subprocessor::init(...)'
        msg_generator_none: str = 'the generator must be provided'
        msg_generator_istype: str = f'the generator must be an instance of {IGeneratorManager.__name__}'

        not_none(generator, ctx, msg_generator_none)
        istype(generator, IGeneratorManager, ctx, msg_generator_istype)

        self._generator = generator
        self._logger = generator.get_context().logger

    def run(self, *, params: Mapping[str, object]) -> Mapping[str, object]:
        '''
            Executes the generator.

            :param params: The command parameters for generator.
            :return: Return code, stdout and stderr messages.
            :exceptions: None.
        '''
        try:
            current_dir: str = dirname(realpath(__file__))
            output_dir: str = params.get('output')
            project_name: str = params.get('name')
            scheme: str = f'{current_dir}/{self._scheme}'
            templates: str = f'{current_dir}/{self._templates}'

            success = self._generator.generate(
                data=GeneratorData(
                    archive_path=templates,
                    target_dir=output_dir,
                    template_key='base',
                    scheme=scheme,
                    template_values={
                        'project_name': project_name,
                        'PRO': project_name,
                        'YEAR': str(datetime.now().year),
                    }
                )
            )

            if success:
                self._logger.write_log(INFO, '    Generated files:',)

                for root, dirs, files in walk(output_dir):
                    for file in files:
                        rel_dir = relpath(root, output_dir)

                        if rel_dir == '.':
                            self._logger.write_log(INFO, f'      {file}')
                        else:
                            self._logger.write_log(INFO, f'      {rel_dir}/{file}')

            return {
                'returncode': 0 if success else 1,
                'stdout': f'{project_name} skeleton successfully generated.' if success else '',
                'stderr': f'failed to generate {project_name} skeleton.' if not success else ''
            }

        except Exception as exc:
            return {'returncode': 1, 'stdout': '', 'stderr': f'failed to generate {exc}'}

    def is_initialized(self) -> bool:
        '''
            Checks if the subprocessor is initialized.

            :return: True if the subprocessor is initialized, False otherwise.
            :exceptions: None.
        '''
        return self._generator.is_initialized()

    def __str__(self) -> str:
        '''
            Returns the SubProcessor as string representation.

            :return: The SubProcessor as string representation.
            :exceptions: None.
        '''
        return to_str(self)
