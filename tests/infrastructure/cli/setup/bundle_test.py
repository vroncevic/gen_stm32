# -*- coding: UTF-8 -*-

'''
Module
    bundle_test.py
Info
    Unit tests for CLIBundle.
'''

from __future__ import annotations

import unittest
from unittest.mock import Mock

from ats_utilities.option.imanager import IOptionManager

from gen_stm32.infrastructure.cli.setup.bundle import CLIBundle
from gen_stm32.core.service.iservice import IService


class TestCLIBundle(unittest.TestCase):

    def test_cli_bundle_to_dict(self) -> None:
        mock_service = Mock(spec=IService)
        mock_parser = Mock(spec=IOptionManager)
        
        bundle = CLIBundle(
            service=mock_service,
            parser=mock_parser,
            commands=[]
        )
        
        data = bundle.to_dict()
        self.assertEqual(data['service'], mock_service)
        self.assertEqual(data['parser'], mock_parser)
        self.assertEqual(data['commands'], [])
