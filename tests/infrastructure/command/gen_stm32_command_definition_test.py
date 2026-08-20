# -*- coding: UTF-8 -*-

'''
Module
    gen_stm32_command_definition_test.py
Info
    Unit tests for GenSTM32CommandDefinition.
'''

from __future__ import annotations

import unittest

from gen_stm32.infrastructure.command.gen_stm32_command_definition import GenSTM32CommandDefinition


class TestGenSTM32CommandDefinition(unittest.TestCase):

    def test_command_definition_properties(self) -> None:
        defn = GenSTM32CommandDefinition()
        self.assertEqual(defn.name, 'create')
        self.assertEqual(defn.help_text, 'Generate STM32 project skeleton')
        self.assertEqual(len(defn.options), 2)
        self.assertEqual(defn.options[0].name, '--name')
        self.assertEqual(defn.options[1].name, '--output')

    def test_command_definition_to_str(self) -> None:
        defn = GenSTM32CommandDefinition()
        self.assertIsInstance(str(defn), str)
