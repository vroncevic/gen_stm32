# -*- coding: UTF-8 -*-
# stm32_setup.py
# Copyright (C) 2018 Vladimir Roncevic <elektron.ronca@gmail.com>
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
from inspect import stack

try:
    from stm32_pro.read_template import ReadTemplate
    from stm32_pro.write_template import WriteTemplate

    from ats_utilities.console_io.verbose import verbose_message
    from ats_utilities.console_io.error import error_message
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from ats_utilities.exceptions.ats_bad_call_error import ATSBadCallError
except ImportError as e:
    msg = "\n{0}\n{1}\n".format(__file__, e)
    sys.exit(msg)  # Force close python ATS ##################################

__author__ = 'Vladimir Roncevic'
__copyright__ = 'Copyright 2019, Free software to use and distributed it.'
__credits__ = ['Vladimir Roncevic']
__license__ = 'GNU General Public License (GPL)'
__version__ = '1.0.0'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class STM32Setup(object):
    """
        Define class STM32Setup with attribute(s) and method(s).
        Generate project skeleton.
        It defines:
            attribute:
                __slots__ - Setting class slots
                VERBOSE - Console text indicator for current process-phase
                __reader - Reader API
                __writer - Writer API
            method:
                __init__ - Initial constructor
                gen_pro_setup - Generate project skeleton
    """

    __slots__ = ('VERBOSE', '__reader', '__writer')
    VERBOSE = 'GEN_STM32::STM32_SETUP::STM32SETUP'

    def __init__(self, verbose=False):
        """
            Initial constructor
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :exceptions: None
        """
        verbose_message(STM32Setup.VERBOSE, verbose, 'Initial setup')
        self.__reader = ReadTemplate(verbose=verbose)
        self.__writer = WriteTemplate(verbose=verbose)

    def gen_pro_setup(self, project_name, verbose=False):
        """
            Generate setup.py for python package.
            :param project_name: PRoject name
            :type project_name: <str>
            :param verbose: Enable/disable verbose option
            :type verbose: <bool>
            :return: True (success) | False
            :rtype: <bool>
            :exceptions: ATSBadCallError | ATSTypeError
        """
        func, status, setup_content = stack()[0][3], False, None
        project_txt = 'Argument: expected project_name <str> object'
        project_msg = "{0} {1} {2}".format('def', func, project_txt)
        if project_name is None or not project_name:
            raise ATSBadCallError(project_msg)
        if not isinstance(project_name, str):
            raise ATSTypeError(project_msg)
        verbose_message(
            STM32Setup.VERBOSE, verbose, 'Generating project', project_name
        )
        project_data = self.__reader.read(verbose=verbose)
        project_data['name'] = project_name
        if bool(project_data):
            status = self.__writer.write(project_data, verbose=verbose)
        return True if status else False

