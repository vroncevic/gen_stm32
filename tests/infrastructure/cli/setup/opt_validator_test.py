# -*- coding: UTF-8 -*-

'''
Module
    opt_validator_test.py
Info
    Unit tests for CLIBundleOptionsValidator class.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.option.imanager import IOptionManager

from gen_stm32.infrastructure.cli.setup.opt_validator import CLIBundleOptionsValidator


class DummyService:

    def execute(self, *, params: object) -> object:
        return None

    def is_initialized(self) -> bool:
        return True


class TestCLIBundleOptionsValidator(unittest.TestCase):

    def test_validate_success(self) -> None:
        mock_service = DummyService()
        mock_parser = Mock(spec=IOptionManager)

        options = {
            'service': mock_service,
            'parser': mock_parser
        }
        CLIBundleOptionsValidator.validate(options)

    def test_validate_none(self) -> None:
        with self.assertRaises(Exception):
            CLIBundleOptionsValidator.validate(None)

    def test_validate_invalid_type(self) -> None:
        with self.assertRaises(Exception):
            CLIBundleOptionsValidator.validate("invalid")

    def test_validate_missing_option(self) -> None:
        mock_service = DummyService()
        options = {
            'service': mock_service
        }
        with self.assertRaises(Exception):
            CLIBundleOptionsValidator.validate(options)

    def test_validate_invalid_option_type(self) -> None:
        mock_parser = Mock(spec=IOptionManager)
        options = {
            'service': "not_a_service",
            'parser': mock_parser
        }
        with self.assertRaises(Exception):
            CLIBundleOptionsValidator.validate(options)

    def test_is_valid_success(self) -> None:
        mock_service = DummyService()
        mock_parser = Mock(spec=IOptionManager)

        options = {
            'service': mock_service,
            'parser': mock_parser
        }
        self.assertTrue(CLIBundleOptionsValidator.is_valid(options))

    def test_is_valid_failure(self) -> None:
        self.assertFalse(CLIBundleOptionsValidator.is_valid(None))
        self.assertFalse(CLIBundleOptionsValidator.is_valid("invalid"))
        options = {
            'service': DummyService()
        }
        self.assertFalse(CLIBundleOptionsValidator.is_valid(options))
