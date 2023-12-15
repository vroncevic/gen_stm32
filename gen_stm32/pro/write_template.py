# -*- coding: UTF-8 -*-

'''
Module
    write_template.py
Copyright
    Copyright (C) 2018 - 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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
    Defines class WriteTemplate with attribute(s) and method(s).
    Creates an API for writing source and build modules.
'''

import sys
from typing import List, Dict
from os import getcwd, chmod, makedirs
from os.path import exists
from string import Template

try:
    from ats_utilities.config_io.file_check import FileCheck
    from ats_utilities.console_io.verbose import verbose_message
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from ats_utilities.exceptions.ats_value_error import ATSValueError
except ImportError as ats_error_message:
    # Force close python ATS ##################################################
    sys.exit(f'\n{__file__}\n{ats_error_message}\n')

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2024, https://vroncevic.github.io/gen_stm32'
__credits__: List[str] = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.2.1'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class WriteTemplate(FileCheck):
    '''
        Defines class WriteTemplate with attribute(s) and method(s).
        Creates an API for writing source and build modules.

        It defines:

            :attributes:
                | _GEN_VERBOSE - Console text indicator for process-phase.
            :methods:
                | __init__ - Initials WriteTemplate constructor.
                | write - Writes a templates with parameters.
    '''

    _GEN_VERBOSE: str = 'GEN_STM32::PRO::WRITE_TEMPLATE'

    def __init__(self, verbose: bool = False) -> None:
        '''
            Initials WriteTemplate constructor.

            :param verbose: Enable/Disable verbose option
            :type verbose: <bool>
            :exceptions: None
        '''
        FileCheck.__init__(self, verbose)
        verbose_message(verbose, [f'{self._GEN_VERBOSE} init writer'])

    def write(
        self,
        templates: List[Dict[str, str]],
        pro_name: str | None,
        verbose: bool = False
    ) -> bool:
        '''
            Writes a templates with parameters.

            :param templates: Templates with params
            :type templates: <List[Dict[str, str]]>
            :param pro_name: Project name | None
            :type pro_name: <str> | <NoneType>
            :param verbose: Enable/Disable verbose option
            :type verbose: <bool>
            :return: True (success operation) | False
            :rtype: <bool>
            :exceptions: ATSTypeError | ATSValueError
        '''
        error_msg: str | None = None
        error_id: int | None = None
        error_msg, error_id = self.check_params([
            ('list:templates', templates), ('str:pro_name', pro_name)
        ])
        if error_id == self.TYPE_ERROR:
            raise ATSTypeError(error_msg)
        if not bool(templates):
            raise ATSValueError('missing templates')
        all_stat: List[bool] = []
        pro_dir: str = f'{getcwd()}/{pro_name}/'
        build_dir: str = f'{pro_dir}build/'
        build_src_dir: str = f'{build_dir}source/'
        driver: str = 'STM32F4xx_StdPeriph_Driver'
        build_inc_dir: str = f'{build_dir}includes/{driver}/src/'
        scripts_dir: str = f'{pro_dir}scripts/'
        source_dir: str = f'{pro_dir}source/'
        includes_dir: str = f'{pro_dir}includes/'
        cmsis_dir: str = f'{includes_dir}CMSIS/'
        stm32f4xx_dir: str = f'{includes_dir}STM32F4xx/'
        stm32f4xx_driver_src_dir: str = f'{includes_dir}{driver}/src/'
        stm32f4xx_driver_inc_dir: str = f'{includes_dir}{driver}/inc/'
        num_of_modules: int = len(templates)
        check_structure: bool = any([
            not exists(pro_dir), not exists(build_dir),
            not exists(build_src_dir), not exists(build_inc_dir),
            not exists(scripts_dir), not exists(source_dir),
            not exists(includes_dir), not exists(cmsis_dir),
            not exists(stm32f4xx_dir),
            not exists(stm32f4xx_driver_src_dir),
            not exists(stm32f4xx_driver_inc_dir)
        ])
        if check_structure:
            makedirs(pro_dir)
            makedirs(build_dir)
            makedirs(build_src_dir)
            makedirs(build_inc_dir)
            makedirs(scripts_dir)
            makedirs(source_dir)
            makedirs(includes_dir)
            makedirs(cmsis_dir)
            makedirs(stm32f4xx_dir)
            makedirs(stm32f4xx_driver_src_dir)
            makedirs(stm32f4xx_driver_inc_dir)
        for template_content in templates:
            module_name: str = list(template_content.keys())[0]
            template: Template = Template(template_content[module_name])
            module_path: str = f'{pro_dir}{module_name}'
            verbose_message(
                verbose, [f'{self._GEN_VERBOSE} generate module', module_path]
            )
            with open(module_path, 'w', encoding='utf-8') as module_file:
                module_content: str = template.substitute(
                    {'PRO': f'{pro_name}'}
                )
                module_file.write(module_content)
                chmod(module_path, 0o666)
                self.check_path(module_path, verbose)
                self.check_mode('w', verbose)
                if 'makefile'.capitalize() in module_path:
                    self.check_format(module_path, 'makefile', verbose)
                else:
                    self.check_format(
                        module_path, module_path.split('.')[1], verbose
                    )
                if self.is_file_ok():
                    all_stat.append(True)
                else:
                    all_stat.append(False)
        return all([
            bool(all_stat), all(all_stat), len(all_stat) == num_of_modules
        ])
