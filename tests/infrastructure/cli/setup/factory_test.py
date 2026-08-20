# -*- coding: UTF-8 -*-

'''
Module
    factory_test.py
Info
    Unit tests for CLIBundleFactory class.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.option.imanager import IOptionManager

from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.infrastructure.cli.setup.factory import CLIBundleFactory


class DummyService:

    def execute(self, *, params: object) -> object:
        return None

    def is_initialized(self) -> bool:
        return True


class TestCLIBundleFactory(unittest.TestCase):

    def test_create_bundle_success(self) -> None:
        mock_service = DummyService()
        mock_parser = Mock(spec=IOptionManager)

        options = {
            'service': mock_service,
            'parser': mock_parser
        }
        bundle = CLIBundleFactory.create_bundle(options)
        self.assertIsInstance(bundle, CLIBundle)

    def test_get_version(self) -> None:
        self.assertEqual(CLIBundleFactory.get_version(), '1.0.5')
