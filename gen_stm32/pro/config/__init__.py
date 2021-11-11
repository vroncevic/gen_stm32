# -*- coding: UTF-8 -*-

'''
 Module
     __init__.py
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
     Defined class ProConfig with attribute(s) and method(s).
     Defined project configuration container.
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


class ProConfig:
    '''
        Defined class ProConfig with attribute(s) and method(s).
        Defined project configuration container.
        It defines:

            :attributes:
                | GEN_VERBOSE - console text indicator for process-phase.
                | TEMPLATES - templates key.
                | MODULES - modules key.
                | FORMAT - format for template file.
                | __verbose - enable/disable verbose option.
                | __config - configuration dictionary.
            :methods:
                | __init__ - initial constructor.
                | pro_name - property methods for set/get operations.
                | is_config_ok - checking is project configuration ok.
                | __str__ - dunder method for ProConfig.
    '''

    GEN_VERBOSE = 'GEN_STM32::PRO::CONFIG::PRO_CONFIG'
    TEMPLATES, MODULES, FORMAT = 'templates', 'modules', 'template'

    def __init__(self, verbose=False):
        '''
            Initial constructor.

            :param verbose: enable/disable verbose option.
            :type verbose: <bool>
            :exceptions: None
        '''
        self.__verbose = verbose
        self.__config = None
        verbose_message(
            ProConfig.GEN_VERBOSE, verbose, 'init project configuration'
        )

    @property
    def config(self):
        '''
            Property method for getting project configuration.

            :return: formatted project configuration | None.
            :rtype: <dict> | <NoneType>
            :exceptions: None
        '''
        return self.__config

    @config.setter
    def config(self, config):
        '''
            Property method for setting project configuration.

            :param config: set project configuration.
            :type config: <dict>
            :exceptions: ATSTypeError | ATSBadCallError
        '''
        checker, error, status = ATSChecker(), None, False
        error, status = checker.check_params([('dict:config', config)])
        if status == ATSChecker.TYPE_ERROR:
            raise ATSTypeError(error)
        if status == ATSChecker.VALUE_ERROR:
            raise ATSBadCallError(error)
        self.__config = config
        verbose_message(
            ProConfig.GEN_VERBOSE, self.__verbose, 'set config', config
        )

    def is_config_ok(self):
        '''
            Checking is project configuration ok.

            :return: boolean status, True (ok) | False.
            :rtype: <bool>
            :exceptions: None
        '''
        return all([
            self.__config is not None, isinstance(self.__config, dict)
        ])

    def __str__(self):
        '''
            Dunder method for ProConfig.

            :return: object in a human-readable format.
            :rtype: <str>
            :exceptions: None
        '''
        return '{0} ({1}, {2})'.format(
            self.__class__.__name__, str(self.__verbose), str(self.__config)
        )
