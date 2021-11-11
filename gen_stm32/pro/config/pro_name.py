# -*- coding: UTF-8 -*-

'''
 Module
     pro_name.py
 Copyright
     Copyright (C) 2018 Vladimir Roncevic <elektron.ronca@gmail.com>
     gen_stm8 is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by the
     Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
     gen_stm8 is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
     See the GNU General Public License for more details.
     You should have received a copy of the GNU General Public License along
     with this program. If not, see <http://www.gnu.org/licenses/>.
 Info
     Defined class ProName with attribute(s) and method(s).
     Defined API for project name with preparations for generation.
'''

import sys

try:
    from ats_utilities.checker import ATSChecker
    from ats_utilities.console_io.verbose import verbose_message
    from ats_utilities.exceptions.ats_type_error import ATSTypeError
    from ats_utilities.exceptions.ats_bad_call_error import ATSBadCallError
except ImportError as ats_error_message:
    MESSAGE = '\n{0}\n{1}\n'.format(__file__, ats_error_message)
    sys.exit(MESSAGE)  # Force close python ATS ##############################

__author__ = 'Vladimir Roncevic'
__copyright__ = 'Copyright 2018, Free software to use and distributed it.'
__credits__ = ['Vladimir Roncevic']
__license__ = 'https://github.com/vroncevic/gen_stm8/blob/dev/LICENSE'
__version__ = '1.1.1'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


class ProName:
    '''
        Defined class ProName with attribute(s) and method(s).
        Defined API for project name with preparations for generation.
        It defines:

            :attributes:
                | GEN_VERBOSE - console text indicator for process-phase.
                | __verbose - enable/disable verbose option.
                | __pro_name - project name.
            :methods:
                | __init__ - initial constructor.
                | pro_name - property methods for set/get operations.
                | is_pro_name_ok - checking is project name ok.
                | __str__ - dunder method for ProName.
    '''

    GEN_VERBOSE = 'GEN_STM32::PRO::CONFIG::PRO_NAME'

    def __init__(self, verbose=False):
        '''
            Initial constructor.

            :param verbose: enable/disable verbose option.
            :type verbose: <bool>
            :exceptions: None
        '''
        self.__verbose = verbose
        self.__pro_name = None
        verbose_message(ProName.GEN_VERBOSE, verbose, 'init project name')

    @property
    def pro_name(self):
        '''
            Property method for getting project name.

            :return: formatted project name | None.
            :rtype: <str> | <NoneType>
            :exceptions: None
        '''
        return self.__pro_name

    @pro_name.setter
    def pro_name(self, pro_name):
        '''
            Property method for setting project name.

            :param pro_name: set project name.
            :type pro_name: <str>
            :exceptions: ATSTypeError | ATSBadCallError
        '''
        checker, error, status = ATSChecker(), None, False
        error, status = checker.check_params([('str:pro_name', pro_name)])
        if status == ATSChecker.TYPE_ERROR:
            raise ATSTypeError(error)
        if status == ATSChecker.VALUE_ERROR:
            raise ATSBadCallError(error)
        self.__pro_name = pro_name
        verbose_message(
            ProName.GEN_VERBOSE, self.__verbose, 'set project name', pro_name
        )

    def is_pro_name_ok(self):
        '''
            Checking is project name ok.

            :return: boolean status, True (not None) | False.
            :rtype: <bool>
            :exceptions: None
        '''
        return all([
            self.__pro_name is not None, isinstance(self.__pro_name, str)
        ])

    def __str__(self):
        '''
            Dunder method for ProName.

            :return: object in a human-readable format.
            :rtype: <str>
            :exceptions: None
        '''
        return '{0} ({1}, {2})'.format(
            self.__class__.__name__, str(self.__verbose), self.__pro_name
        )
