# -*- coding: UTF-8 -*-

'''
Module
    gen_stm32_command_executor_test.py
Info
    Unit tests for GenSTM32CommandExecutor.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from gen_stm32.infrastructure.command.gen_stm32_command_definition import GenSTM32CommandDefinition
from gen_stm32.infrastructure.command.gen_stm32_command_executor import GenSTM32CommandExecutor
from gen_stm32.core.service.iservice import IService


class TestGenSTM32CommandExecutor(unittest.TestCase):

    def test_command_executor_init(self) -> None:
        mock_defn = Mock(spec=GenSTM32CommandDefinition)
        executor = GenSTM32CommandExecutor(mock_defn)
        self.assertEqual(executor.definition, mock_defn)

    def test_command_executor_execute_success(self) -> None:
        mock_defn = Mock(spec=GenSTM32CommandDefinition)
        executor = GenSTM32CommandExecutor(mock_defn)
        
        mock_service = Mock(spec=IService)
        mock_service.is_initialized = Mock(return_value=True)
        mock_service.execute = Mock(return_value={'returncode': 0, 'stdout': 'generated'})
        
        params = {'name': 'test'}
        res = executor.execute(params=params, service=mock_service)
        self.assertEqual(res, {'returncode': 0, 'stdout': 'generated'})
        mock_service.execute.assert_called_once_with(params=params)

    def test_command_executor_execute_not_initialized(self) -> None:
        mock_defn = Mock(spec=GenSTM32CommandDefinition)
        executor = GenSTM32CommandExecutor(mock_defn)
        
        mock_service = Mock(spec=IService)
        mock_service.is_initialized = Mock(return_value=False)
        
        res = executor.execute(params={}, service=mock_service)
        self.assertEqual(res['returncode'], 1)
        self.assertIn('service not initialized', res['stderr'])

    def test_command_executor_to_str(self) -> None:
        mock_defn = Mock(spec=GenSTM32CommandDefinition)
        executor = GenSTM32CommandExecutor(mock_defn)
        self.assertIsInstance(str(executor), str)
