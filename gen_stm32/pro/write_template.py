# -*- coding: UTF-8 -*-

'''
 Module
     write_template.py
 Copyright
     Copyright (C) 2018 Vladimir Roncevic <elektron.ronca@gmail.com>
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
     Define class WriteTemplate with attribute(s) and method(s).
     Created API for writing template content with parameters.
'''

import sys
from os import getcwd, chmod, makedirs
from os.path import exists
from string import Template

try:
    from ats_utilities.checker import ATSChecker
    from ats_utilities.config_io.base_check import FileChecking
    from ats_utilities.console_io.verbose import verbose_message
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from ats_utilities.exceptions.ats_bad_call_error import ATSBadCallError
except ImportError as ats_error_message:
    MESSAGE = '\n{0}\n{1}\n'.format(__file__, ats_error_message)
    sys.exit(MESSAGE)  # Force close python ATS ##############################

__author__ = 'Vladimir Roncevic'
__copyright__ = 'Copyright 2018, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.1.1'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class WriteTemplate(FileChecking):
    '''
        Define class WriteTemplate with attribute(s) and method(s).
        Created API for writing template content with parameters.
        It defines:

            :attributes:
                | GEN_VERBOSE - console text indicator for process-phase.
            :methods:
                | __init__ - initial constructor.
                | write - write a templates with parameters.
                | __str__ - dunder method for WriteTemplate.
    '''

    GEN_VERBOSE = 'GEN_STM32::PRO::WRITE_TEMPLATE'

    def __init__(self, verbose=False):
        '''
            Initial constructor.

            :param verbose: enable/disable verbose option.
            :type verbose: <bool>
            :exceptions: ATSTypeError | ATSBadCallError
        '''
        FileChecking.__init__(self, verbose=verbose)
        verbose_message(WriteTemplate.GEN_VERBOSE, verbose, 'init writer')

    def write(self, templates, project_name, verbose=False):
        '''
            Write a templates with parameters.

            :param templates: parameter templates.
            :type templates: <list>
            :param project_name: parameter project name.
            :type project_name: <str>
            :param verbose: enable/disable verbose option.
            :type verbose: <bool>
            :return: boolean status, True (success) | False.
            :rtype: <bool>
            :exceptions: ATSTypeError | ATSBadCallError
        '''
        checker, error, status = ATSChecker(), None, False
        error, status = checker.check_params([
            ('list:templates', templates), ('str:project_name', project_name)
        ])
        if status == ATSChecker.TYPE_ERROR:
            raise ATSTypeError(error)
        if status == ATSChecker.VALUE_ERROR:
            raise ATSBadCallError(error)
        statuses = []
        pro_dir = '{0}/{1}/'.format(getcwd(), project_name)
        build_dir = '{0}{1}/'.format(pro_dir, 'build')
        build_src_dir = '{0}{1}/'.format(build_dir, 'source')
        build_inc_dir = '{0}{1}/'.format(
            build_dir, 'includes/STM32F4xx_StdPeriph_Driver/src'
        )
        scripts_dir = '{0}{1}/'.format(pro_dir, 'scripts')
        source_dir = '{0}{1}/'.format(pro_dir, 'source')
        includes_dir = '{0}{1}/'.format(pro_dir, 'includes')
        cmsis_dir = '{0}{1}/'.format(includes_dir, 'CMSIS')
        stm32f4xx_dir = '{0}{1}/'.format(includes_dir, 'STM32F4xx')
        stm32f4xx_stdperiph_driver_src_dir = '{0}{1}/'.format(
            includes_dir, 'STM32F4xx_StdPeriph_Driver/src'
        )
        stm32f4xx_stdperiph_driver_inc_dir = '{0}{1}/'.format(
            includes_dir, 'STM32F4xx_StdPeriph_Driver/inc'
        )
        status, expected_num_of_modules = False, len(templates)
        check_structure = any([
            not exists(pro_dir), not exists(build_dir),
            not exists(build_src_dir), not exists(build_inc_dir),
            not exists(scripts_dir), not exists(source_dir),
            not exists(includes_dir), not exists(cmsis_dir),
            not exists(stm32f4xx_dir),
            not exists(stm32f4xx_stdperiph_driver_src_dir),
            not exists(stm32f4xx_stdperiph_driver_inc_dir)
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
            makedirs(stm32f4xx_stdperiph_driver_src_dir)
            makedirs(stm32f4xx_stdperiph_driver_inc_dir)
        for template_content in templates:
            module_name = template_content.keys()[0]
            template = Template(template_content[module_name])
            module_path = '{0}{1}'.format(pro_dir, module_name)
            verbose_message(
                WriteTemplate.GEN_VERBOSE, verbose,
                'generate module', module_path
            )
            with open(module_path, 'w') as module_file:
                module_content = template.substitute(
                    {'PRO': '{0}'.format(project_name)}
                )
                module_file.write(module_content)
                chmod(module_path, 0o666)
                self.check_path(module_path, verbose=verbose)
                self.check_mode('w', verbose=verbose)
                if 'makefile'.capitalize() in module_path:
                    self.check_format(
                        module_path, 'makefile', verbose=verbose
                    )
                else:
                    self.check_format(
                        module_path, module_path.split('.')[1],
                        verbose=verbose
                    )
                if self.is_file_ok():
                    statuses.append(True)
                else:
                    statuses.append(False)
        if all(statuses) and len(statuses) == expected_num_of_modules:
            status = True
        return status

    def __str__(self):
        '''
            Dunder method for WriteTemplate.

            :return: object in a human-readable format.
            :rtype: <str>
            :exceptions: None
        '''
        return '{0} ({1})'.format(
            self.__class__.__name__, FileChecking.__str__(self)
        )
