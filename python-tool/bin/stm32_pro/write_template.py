# -*- coding: UTF-8 -*-

"""
 Module
     write_template.py
 Copyright
     Copyright (C) 2019 Vladimir Roncevic <elektron.ronca@gmail.com>
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
     Write template content with parameters to a project setup.
"""

import sys
from errno import EEXIST
from inspect import stack
from os import getcwd, chmod, listdir, makedirs
from os.path import exists, dirname
from string import Template
from shutil import copy

try:
    from ats_utilities.console_io.verbose import verbose_message
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from ats_utilities.exceptions.ats_bad_call_error import ATSBadCallError
except ImportError as error:
    MESSAGE = "\n{0}\n{1}\n".format(__file__, error)
    sys.exit(MESSAGE)  # Force close python ATS ##############################

__author__ = 'Vladimir Roncevic'
__copyright__ = 'Copyright 2020, Free software to use and distributed it.'
__credits__ = ['Vladimir Roncevic']
__license__ = 'GNU General Public License (GPL)'
__version__ = '1.0.0'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class WriteTemplate(object):
    """
        Define class WriteTemplate with attribute(s) and method(s).
        Write template content with parameters to a project setup.
        It defines:
            attribute:
                __slots__ - Setting class slots
                __template - Template object
                VERBOSE - Console text indicator for current process-phase
            method:
                __init__ - Initial constructor
                write - Write a template content to a project setup
    """

    __slots__ = ('VERBOSE', '__template')
    VERBOSE = 'GEN_STM32::STM32_PRO::WRITE_TEMPLATE'

    def __init__(self, verbose=False):
        """
            Initial constructor
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :exceptions: None
        """
        verbose_message(WriteTemplate.VERBOSE, verbose, 'Initial writer')
        self.__template = None

    def mkdirs(self, filename, verbose=False):
        """
            Create project directories
            :param filename: filename path
            :type filename: <str>
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :exception: ATSBadCallError | ATSTypeError
        """
        func, current_dir = stack()[0][3], getcwd()
        filename_txt = 'First argument: expected filename <str> object'
        filename_msg = "{0} {1} {2}".format('def', func, filename_txt)
        if filename is None or not filename:
            raise ATSBadCallError(filename_msg)
        if not isinstance(filename, str):
            raise ATSTypeError(filename_msg)
        filename = "{0}/{1}".format(current_dir, filename)
        verbose_message(
            WriteTemplate.VERBOSE, verbose, "create dir {0}".format(filename)
        )
        if not exists(dirname(filename)):
            try:
                makedirs(dirname(filename))
            except OSError as exc:
                # Guard against race condition
                if exc.errno != EEXIST:
                    raise

    def write(self, project_data, verbose=False):
        """
            Write setup content to file.
            :param project_data: Project data
            :type project_data: <dict>
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :return: True (success) | False
            :rtype: <bool>
            :exception: ATSBadCallError | ATSTypeError
        """
        status, project_name = False, None
        func, current_dir = stack()[0][3], getcwd()
        setup_txt = 'First argument: expected project_data <dict> object'
        setup_msg = "{0} {1} {2}".format('def', func, setup_txt)
        if project_data is None or not project_data:
            raise ATSBadCallError(setup_msg)
        if not isinstance(project_data, dict):
            raise ATSTypeError(setup_msg)
        project_name = project_data['name']
        for section in project_data.keys():
            if section == 'name':
                continue
            for section_item in project_data[section]:
                for section_item_key in section_item.keys():
                    if section == 'includes':
                        filename = section_item[section_item_key]
                    else:
                        filename = section_item[section_item_key][0]
                    self.mkdirs(filename, verbose=verbose)
        for section in project_data.keys():
            if section == 'name':
                continue
            elif section == 'includes':
                for include_dir in project_data[section]:
                    src_dir = include_dir.keys()[0]
                    dst_dir = "{0}/{1}".format(
                        current_dir, include_dir.values()[0]
                    )
                    for filename in listdir(src_dir):
                        if filename.endswith('.h') or filename.endswith('.c'):
                            copy(
                                "{0}{1}".format(src_dir, filename), dst_dir
                            )
            else:
                for section_item in project_data[section]:
                    for section_item_template in section_item.keys():
                        status = False
                        module_name = "{0}/{1}".format(
                            current_dir, section_item[section_item_template][0]
                        )
                        module_content = section_item[section_item_template][1]
                        verbose_message(
                            WriteTemplate.VERBOSE, verbose,
                            'Write project file', module_name
                        )
                        project = {'PRO': "{0}".format(project_name)}
                        self.__template = Template(module_content)
                        if self.__template:
                            with open(module_name, 'w') as setup_file:
                                setup_file.write(
                                    self.__template.substitute(project)
                                )
                                chmod(module_name, 0o666)
                                status = True
        return True if status else False
