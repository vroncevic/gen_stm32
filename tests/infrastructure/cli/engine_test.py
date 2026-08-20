# -*- coding: UTF-8 -*-

'''
Module
    engine_test.py
Info
    Unit tests for concrete CLI.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.exceptions import ATSRuntimeError
from ats_utilities.option.imanager import IOptionManager
from gen_stm32.infrastructure.command.icommand_definition import ICommandDefinition

from gen_stm32.infrastructure.cli.engine import CLI
from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.core.service.iservice import IService
from gen_stm32.infrastructure.command.icommand_executor import ICommandExecutor
from gen_stm32.infrastructure.command.command import CommandBundle


class TestCLI(unittest.TestCase):

    def test_cli_init_success(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        
        mock_def = Mock(spec=ICommandDefinition)
        mock_def.name = 'create'
        mock_executor = Mock(spec=ICommandExecutor)
        
        mock_cmd = Mock(spec=CommandBundle)
        mock_cmd.definition = mock_def
        mock_cmd.executor = mock_executor

        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[mock_cmd]
        )

        cli = CLI(bundle)
        self.assertEqual(cli._service, mock_service)
        self.assertEqual(cli._parser, mock_parser)
        self.assertIn('create', cli._executors)
        mock_parser.register_commands.assert_called_once_with([mock_def])

    def test_cli_run_success(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        mock_parser.parse_command = Mock(return_value=('create', {'name': 'test'}))
        
        mock_def = Mock(spec=ICommandDefinition)
        mock_def.name = 'create'
        mock_executor = Mock(spec=ICommandExecutor)
        mock_executor.execute = Mock(return_value={'returncode': 0, 'stdout': 'ok', 'stderr': ''})
        
        mock_cmd = Mock(spec=CommandBundle)
        mock_cmd.definition = mock_def
        mock_cmd.executor = mock_executor

        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[mock_cmd]
        )

        cli = CLI(bundle)
        res = cli.run()
        self.assertEqual(res, {'returncode': 0, 'stdout': 'ok', 'stderr': ''})
        mock_executor.execute.assert_called_once_with(params={'name': 'test'}, service=mock_service)

    def test_cli_run_command_not_found(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        mock_parser.parse_command = Mock(return_value=('unknown', {}))
        
        mock_def = Mock(spec=ICommandDefinition)
        mock_def.name = 'create'
        mock_executor = Mock(spec=ICommandExecutor)
        
        mock_cmd = Mock(spec=CommandBundle)
        mock_cmd.definition = mock_def
        mock_cmd.executor = mock_executor

        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[mock_cmd]
        )

        cli = CLI(bundle)
        res = cli.run()
        self.assertEqual(res['returncode'], 1)
        self.assertIn('command not found', res['stderr'])

    def test_cli_run_exception(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        mock_parser.parse_command = Mock(side_effect=ATSRuntimeError('Parser error'))
        
        mock_def = Mock(spec=ICommandDefinition)
        mock_def.name = 'create'
        mock_executor = Mock(spec=ICommandExecutor)
        
        mock_cmd = Mock(spec=CommandBundle)
        mock_cmd.definition = mock_def
        mock_cmd.executor = mock_executor

        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[mock_cmd]
        )

        cli = CLI(bundle)
        res = cli.run()
        self.assertEqual(res['returncode'], 1)
        self.assertIn('Parser error', res['stderr'])

    def test_cli_is_initialized(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[]
        )
        cli = CLI(bundle)
        self.assertTrue(cli.is_initialized())

    def test_cli_to_str(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[]
        )
        cli = CLI(bundle)
        self.assertIsInstance(str(cli), str)
