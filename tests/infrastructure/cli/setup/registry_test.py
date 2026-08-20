# -*- coding: UTF-8 -*-

'''
Module
    registry_test.py
Info
    Unit tests for CLIBundleRegistry class.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.option.imanager import IOptionManager

from gen_stm32.core.service.iservice import IService
from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.infrastructure.cli.setup.registry import CLIBundleRegistry


class DummyService:

    def execute(self, *, params: object) -> object:
        return None

    def is_initialized(self) -> bool:
        return True


class TestCLIBundleRegistry(unittest.TestCase):

    def test_create_bundle_success(self) -> None:
        mock_service = DummyService()
        mock_parser = Mock(spec=IOptionManager)

        dependencies = {
            'service': mock_service,
            'parser': mock_parser,
            'commands': []
        }
        bundle = CLIBundleRegistry.create_bundle(dependencies)
        self.assertIsInstance(bundle, CLIBundle)
        self.assertEqual(bundle.service, mock_service)
        self.assertEqual(bundle.parser, mock_parser)

    def test_create_bundle_invalid_dependencies(self) -> None:
        with self.assertRaises(Exception):
            CLIBundleRegistry.create_bundle(None)

    def test_get_version(self) -> None:
        self.assertEqual(CLIBundleRegistry.get_version(), '1.0.5')
