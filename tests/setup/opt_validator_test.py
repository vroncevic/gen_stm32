# -*- coding: UTF-8 -*-

'''
Module
    opt_validator_test.py
Info
    Unit tests for GenSTM32BundleOptionsValidator class.
'''

from __future__ import annotations

import unittest

from gen_stm32.setup.opt_validator import GenSTM32BundleOptionsValidator


class TestGenSTM32BundleOptionsValidator(unittest.TestCase):

    def test_validate_success(self) -> None:
        options = {'info_file': 'some_path'}
        GenSTM32BundleOptionsValidator.validate(options)

    def test_validate_none(self) -> None:
        with self.assertRaises(Exception):
            GenSTM32BundleOptionsValidator.validate(None)

    def test_validate_invalid_type(self) -> None:
        with self.assertRaises(Exception):
            GenSTM32BundleOptionsValidator.validate("not_a_mapping")

    def test_validate_invalid_option_type(self) -> None:
        with self.assertRaises(Exception):
            options = {'info_file': 123}
            GenSTM32BundleOptionsValidator.validate(options)

    def test_is_valid_success(self) -> None:
        options = {'info_file': 'some_path'}
        self.assertTrue(GenSTM32BundleOptionsValidator.is_valid(options))

    def test_is_valid_failure(self) -> None:
        self.assertFalse(GenSTM32BundleOptionsValidator.is_valid(None))
        self.assertFalse(GenSTM32BundleOptionsValidator.is_valid("not_a_mapping"))
        self.assertFalse(GenSTM32BundleOptionsValidator.is_valid({'info_file': 123}))
