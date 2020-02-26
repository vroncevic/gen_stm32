# -*- coding: UTF-8 -*-
# read_template.py
# Copyright (C) 2020 Vladimir Roncevic <elektron.ronca@gmail.com>
#
# gen_stm32 is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# gen_stm32 is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.
#

import sys
from os.path import isdir, dirname

try:
    from pathlib import Path

    from ats_utilities.config.yaml.yaml2object import Yaml2Object
    from ats_utilities.config.file_checking import FileChecking
    from ats_utilities.console_io.verbose import verbose_message
    from ats_utilities.console_io.error import error_message
except ImportError as e:
    msg = "\n{0}\n{1}\n".format(__file__, e)
    sys.exit(msg)  # Force close python ATS ##################################

__author__ = 'Vladimir Roncevic'
__copyright__ = 'Copyright 2020, Free software to use and distributed it.'
__credits__ = ['Vladimir Roncevic']
__license__ = 'GNU General Public License (GPL)'
__version__ = '1.0.0'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class ReadTemplate(FileChecking):
    """
        Define class ReadTemplate with attribute(s) and method(s).
        Read a template files and return a content.
        It defines:
            attribute:
                __slots__ - Setting class slots
                VERBOSE - Console text indicator for current process-phase
                __TEMPLATE_DIR - Template dir path
                __PROJECT_TEMPLATE - Project template structure
                __PROJECT_SETUP - Final project structure
                __FORMAT - File format for template
                __template_dir - Absolute file path of template dir
                __tmp_cfg - Yaml object for project templates
                __pro_cfg - Yaml object for project description
            method:
                __init__ - Initial constructor
                read - Read a template and return a string representation
    """

    __slots__ = (
        'VERBOSE',
        '__TEMPLATE_DIR',
        '__PROJECT_TEMPLATE',
        '__PROJECT_SETUP',
        '__FORMAT',
        '__template_dir',
        '__tmp_cfg',
        '__pro_cfg'
    )
    VERBOSE = 'GEN_STM32::STM32_PRO::READ_TEMPLATE'
    __TEMPLATE_DIR = '/../../conf/template/'
    __PROJECT_TEMPLATE = 'project_template.yaml'
    __PROJECT_SETUP = 'project_setup.yaml'
    __FORMAT = 'template'

    def __init__(self, verbose=False):
        """
            Setting template dir from configuration directory.
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :exceptions: None
        """
        verbose_message(
            ReadTemplate.VERBOSE, verbose, 'Initial reader'
        )
        FileChecking.__init__(self, verbose=verbose)
        current_dir = Path(__file__).parent
        template_dir = "{0}{1}".format(
            current_dir, ReadTemplate.__TEMPLATE_DIR
        )
        check_template_dir = isdir(template_dir)
        if check_template_dir:
            self.__template_dir = template_dir
            tmp = "{0}/../{1}".format(
                self.__template_dir, ReadTemplate.__PROJECT_TEMPLATE
            )
            self.__tmp_cfg = Yaml2Object(tmp)
            pro = "{0}/../{1}".format(
                self.__template_dir, ReadTemplate.__PROJECT_SETUP
            )
            self.__pro_cfg = Yaml2Object(pro)
        else:
            self.__template_dir = None
            self.__tmp_cfg = None
            self.__pro_cfg = None

    def read(self, verbose=False):
        """
            Read template structure.
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :return: Template content for setup project | None
            :rtype: <dict> | <NoneType>
            :exceptions: None
        """
        template_file_exists, setup_content, template_file = False, {}, None
        verbose_message(ReadTemplate.VERBOSE, verbose, 'Loading template')
        check_cfg = all(
            [
                bool(self.__template_dir),
                bool(self.__tmp_cfg),
                bool(self.__pro_cfg)
            ]
        )
        if check_cfg:
            tmp_cfg = self.__tmp_cfg.read_configuration(verbose=verbose)
            pro_cfg = self.__pro_cfg.read_configuration(verbose=verbose)
            zipped_section_dicts = zip(tmp_cfg.keys(), pro_cfg.keys())
            for tmp_sec, pro_sec in zipped_section_dicts:
                tmp_cfg[tmp_sec] = tmp_cfg[tmp_sec].split(' ')
                pro_cfg[pro_sec] = pro_cfg[pro_sec].split(' ')
            for tmp_sec, pro_sec in zipped_section_dicts:
                item_list = []
                zipped_item_dicts = zip(tmp_cfg[pro_sec], pro_cfg[tmp_sec])
                for tmp_item, pro_item in zipped_item_dicts:
                    if tmp_sec == pro_sec:
                        if '.template' in tmp_item:
                            template_module = None
                            template_file = "{0}{1}".format(
                                self.__template_dir, tmp_item
                            )
                            tmp_check = self.check_file(
                                file_path=template_file, verbose=verbose
                            )
                            if tmp_check:
                                with open(template_file, 'r') as tmpl:
                                    template_module = tmpl.read()
                                item_list.append(
                                    {tmp_item: [pro_item, template_module]}
                                )
                                setup_content[tmp_sec] = item_list
                        else:
                            module_dir = dirname(__file__)
                            mid_path = '/../../conf/template/includes/'
                            tmp_item = "{0}{1}{2}".format(
                                module_dir, mid_path, tmp_item
                            )
                            item_list.append({tmp_item: pro_item})
                            setup_content[tmp_sec] = item_list
                    else:
                        error_message(
                            ReadTemplate.VERBOSE, 'Not aligned templates'
                        )
        return setup_content

