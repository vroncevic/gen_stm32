# -*- coding: UTF-8 -*-

'''
Module
    validator_test.py
Info
    Unit tests for CLIBundleValidator class.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.option.imanager import IOptionManager

from gen_stm32.core.service.iservice import IService
from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.infrastructure.cli.setup.validator import CLIBundleValidator


class DummyService:

    def execute(self, *, params: object) -> object:
        return None

    def is_initialized(self) -> bool:
        return True


class TestCLIBundleValidator(unittest.TestCase):

    def test_validate_success(self) -> None:
        mock_service = DummyService()
        mock_parser = Mock(spec=IOptionManager)
        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[]
        )
        CLIBundleValidator.validate(bundle)

    def test_validate_none(self) -> None:
        with self.assertRaises(Exception):
            CLIBundleValidator.validate(None)

    def test_validate_invalid_type(self) -> None:
        with self.assertRaises(Exception):
            CLIBundleValidator.validate("invalid")

    def test_is_valid_success(self) -> None:
        mock_service = DummyService()
        mock_parser = Mock(spec=IOptionManager)
        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[]
        )
        self.assertTrue(CLIBundleValidator.is_valid(bundle))

    def test_is_valid_failure(self) -> None:
        self.assertFalse(CLIBundleValidator.is_valid(None))
        self.assertFalse(CLIBundleValidator.is_valid("invalid"))
