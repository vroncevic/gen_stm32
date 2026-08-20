# -*- coding: UTF-8 -*-

'''
Module
    engine_test.py
Info
    Unit tests for concrete Service.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from gen_stm32.core.service.engine import Service
from gen_stm32.core.service.isubprocessor import ISubProcessor
from gen_stm32.core.model.project_setup import ProjectSetup


class TestService(unittest.TestCase):

    def test_service_init_success(self) -> None:
        mock_subprocessor = Mock(spec=ISubProcessor)
        service = Service(mock_subprocessor)
        self.assertEqual(service._subprocessor, mock_subprocessor)

    def test_service_init_none(self) -> None:
        with self.assertRaises(ValueError):
            Service(None)

    def test_service_init_invalid_type(self) -> None:
        with self.assertRaises(TypeError):
            Service("invalid_subprocessor")

    def test_service_execute(self) -> None:
        mock_subprocessor = Mock(spec=ISubProcessor)
        mock_subprocessor.run = Mock(return_value={"returncode": 0})
        service = Service(mock_subprocessor)
        mock_params = Mock(spec=ProjectSetup)
        res = service.execute(params=mock_params)
        self.assertEqual(res, {"returncode": 0})
        mock_subprocessor.run.assert_called_once_with(params=mock_params)

    def test_service_is_initialized(self) -> None:
        mock_subprocessor = Mock(spec=ISubProcessor)
        mock_subprocessor.is_initialized = Mock(return_value=True)
        service = Service(mock_subprocessor)
        self.assertTrue(service.is_initialized())
        mock_subprocessor.is_initialized.assert_called_once()
