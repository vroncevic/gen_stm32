# -*- coding: UTF-8 -*-

'''
Module
    dep_validator_test.py
Info
    Unit tests for GenSTM32BundleDependenciesValidator class.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.base.setup.bundle import BaseBundle

from gen_stm32.setup.dep_validator import GenSTM32BundleDependenciesValidator


class DummyService:

    def execute(self, *, params: object) -> object:
        return None

    def is_initialized(self) -> bool:
        return True


class DummySubProcessor:

    def run(self, *, params: object) -> dict[str, object]:
        return {}

    def is_initialized(self) -> bool:
        return True


class DummyCLI:

    def run(self) -> dict[str, object]:
        return {}

    def is_initialized(self) -> bool:
        return True


class TestGenSTM32BundleDependenciesValidator(unittest.TestCase):

    def test_validate_success(self) -> None:
        mock_base = Mock(spec=BaseBundle)
        dummy_service = DummyService()
        dummy_subprocessor = DummySubProcessor()
        dummy_cli = DummyCLI()

        dependencies = {
            'base': mock_base,
            'service': dummy_service,
            'subprocessor': dummy_subprocessor,
            'cli': dummy_cli
        }
        GenSTM32BundleDependenciesValidator.validate(dependencies)

    def test_validate_none(self) -> None:
        with self.assertRaises(Exception):
            GenSTM32BundleDependenciesValidator.validate(None)

    def test_validate_invalid_type(self) -> None:
        with self.assertRaises(Exception):
            GenSTM32BundleDependenciesValidator.validate("not_a_mapping")

    def test_validate_missing_dependency(self) -> None:
        mock_base = Mock(spec=BaseBundle)
        dummy_service = DummyService()
        dummy_subprocessor = DummySubProcessor()

        dependencies = {
            'base': mock_base,
            'service': dummy_service,
            'subprocessor': dummy_subprocessor
        }
        with self.assertRaises(Exception):
            GenSTM32BundleDependenciesValidator.validate(dependencies)

    def test_is_valid_success(self) -> None:
        mock_base = Mock(spec=BaseBundle)
        dummy_service = DummyService()
        dummy_subprocessor = DummySubProcessor()
        dummy_cli = DummyCLI()

        dependencies = {
            'base': mock_base,
            'service': dummy_service,
            'subprocessor': dummy_subprocessor,
            'cli': dummy_cli
        }
        self.assertTrue(GenSTM32BundleDependenciesValidator.is_valid(dependencies))

    def test_is_valid_failure(self) -> None:
        self.assertFalse(GenSTM32BundleDependenciesValidator.is_valid(None))
        self.assertFalse(GenSTM32BundleDependenciesValidator.is_valid("not_a_mapping"))
        dependencies = {
            'base': Mock(spec=BaseBundle),
            'service': DummyService(),
            'subprocessor': DummySubProcessor()
        }
        self.assertFalse(GenSTM32BundleDependenciesValidator.is_valid(dependencies))
