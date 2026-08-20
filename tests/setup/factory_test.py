# -*- coding: UTF-8 -*-

'''
Module
    factory_test.py
Info
    Unit tests for GenSTM32BundleFactory class.
'''

from __future__ import annotations

import unittest

from gen_stm32.setup.bundle import GenSTM32Bundle
from gen_stm32.setup.factory import GenSTM32BundleFactory


class TestGenSTM32BundleFactory(unittest.TestCase):

    def test_create_bundle_default(self) -> None:
        bundle = GenSTM32BundleFactory.create_bundle()
        self.assertIsInstance(bundle, GenSTM32Bundle)

    def test_create_bundle_with_options(self) -> None:
        options = {'info_file': 'gen_stm32/infrastructure/config/gen_stm32.cfg'}
        bundle = GenSTM32BundleFactory.create_bundle(options)
        self.assertIsInstance(bundle, GenSTM32Bundle)

    def test_create_bundle_invalid_options(self) -> None:
        options = {'info_file': 123}
        with self.assertRaises(Exception):
            GenSTM32BundleFactory.create_bundle(options)

    def test_get_version(self) -> None:
        self.assertEqual(GenSTM32BundleFactory.get_version(), '1.0.5')
