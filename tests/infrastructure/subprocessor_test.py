# -*- coding: UTF-8 -*-

'''
Module
    subprocessor_test.py
Info
    Unit tests for SubProcessor.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock, patch

from ats_utilities.generation.imanager import IGeneratorManager
from ats_utilities.logger.ilogger import ILogger

from gen_stm32.infrastructure.subprocessor import SubProcessor


class TestSubProcessor(unittest.TestCase):

    def test_subprocessor_init(self) -> None:
        mock_logger = Mock(spec=ILogger)
        mock_context = Mock()
        mock_context.logger = mock_logger
        mock_gen = Mock(spec=IGeneratorManager)
        mock_gen.get_context = Mock(return_value=mock_context)

        subp = SubProcessor(mock_gen)
        self.assertEqual(subp._generator, mock_gen)
        self.assertEqual(subp._logger, mock_logger)

    @patch('gen_stm32.infrastructure.subprocessor.walk')
    def test_subprocessor_run_success(self, mock_walk: Mock) -> None:
        mock_logger = Mock(spec=ILogger)
        mock_context = Mock()
        mock_context.logger = mock_logger
        mock_gen = Mock(spec=IGeneratorManager)
        mock_gen.get_context = Mock(return_value=mock_context)
        mock_gen.generate = Mock(return_value=True)

        mock_walk.return_value = [
            ('output_dir', [], ['file1.txt']),
            ('output_dir/subdir', [], ['file2.txt'])
        ]

        subp = SubProcessor(mock_gen)
        params = {'name': 'myapp', 'output': 'output_dir'}
        res = subp.run(params=params)

        self.assertEqual(res['returncode'], 0)
        self.assertIn('successfully generated', res['stdout'])
        mock_gen.generate.assert_called_once()
        mock_logger.write_log.assert_any_call(20, '    Generated files:')
        mock_logger.write_log.assert_any_call(20, '      file1.txt')
        mock_logger.write_log.assert_any_call(20, '      subdir/file2.txt')

    def test_subprocessor_run_fail(self) -> None:
        mock_logger = Mock(spec=ILogger)
        mock_context = Mock()
        mock_context.logger = mock_logger
        mock_gen = Mock(spec=IGeneratorManager)
        mock_gen.get_context = Mock(return_value=mock_context)
        mock_gen.generate = Mock(return_value=False)

        subp = SubProcessor(mock_gen)
        params = {'name': 'myapp', 'output': 'output_dir'}
        res = subp.run(params=params)

        self.assertEqual(res['returncode'], 1)
        self.assertIn('failed to generate myapp skeleton', res['stderr'])

    def test_subprocessor_run_exception(self) -> None:
        mock_logger = Mock(spec=ILogger)
        mock_context = Mock()
        mock_context.logger = mock_logger
        mock_gen = Mock(spec=IGeneratorManager)
        mock_gen.get_context = Mock(return_value=mock_context)
        mock_gen.generate = Mock(side_effect=Exception('Generation error'))

        subp = SubProcessor(mock_gen)
        params = {'name': 'myapp', 'output': 'output_dir'}
        res = subp.run(params=params)

        self.assertEqual(res['returncode'], 1)
        self.assertIn('failed to generate Generation error', res['stderr'])

    def test_subprocessor_is_initialized(self) -> None:
        mock_logger = Mock(spec=ILogger)
        mock_context = Mock()
        mock_context.logger = mock_logger
        mock_gen = Mock(spec=IGeneratorManager)
        mock_gen.get_context = Mock(return_value=mock_context)
        mock_gen.is_initialized = Mock(return_value=True)

        subp = SubProcessor(mock_gen)
        self.assertTrue(subp.is_initialized())

    def test_subprocessor_to_str(self) -> None:
        mock_logger = Mock(spec=ILogger)
        mock_context = Mock()
        mock_context.logger = mock_logger
        mock_gen = Mock(spec=IGeneratorManager)
        mock_gen.get_context = Mock(return_value=mock_context)

        subp = SubProcessor(mock_gen)
        self.assertIsInstance(str(subp), str)
