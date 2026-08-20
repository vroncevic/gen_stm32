# -*- coding: UTF-8 -*-

'''
Module
    keys_test.py
Info
    Unit tests for GenSTM32BundleKeys class.
'''

from __future__ import annotations

import unittest
from types import MappingProxyType

from gen_stm32.setup.keys import GenSTM32BundleKeys


class TestGenSTM32BundleKeys(unittest.TestCase):

    def test_get_dependency_to_type(self) -> None:
        deps = GenSTM32BundleKeys.get_dependency_to_type()
        self.assertIsInstance(deps, MappingProxyType)
        self.assertIn(GenSTM32BundleKeys.DEPENDENCY_BASE, deps)
        self.assertIn(GenSTM32BundleKeys.DEPENDENCY_SERVICE, deps)
        self.assertIn(GenSTM32BundleKeys.DEPENDENCY_SUBPROCESSOR, deps)
        self.assertIn(GenSTM32BundleKeys.DEPENDENCY_CLI, deps)

    def test_get_option_to_type(self) -> None:
        opts = GenSTM32BundleKeys.get_option_to_type()
        self.assertIsInstance(opts, MappingProxyType)
        self.assertIn(GenSTM32BundleKeys.OPTION_INFO_FILE, opts)
