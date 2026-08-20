# -*- coding: UTF-8 -*-

'''
Module
    setup.py
Copyright
    Copyright (C) 2018 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
    gen_stm32 is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    gen_stm32 is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    Defines setup for tool gen_stm32.
'''
from __future__ import annotations

from os import walk
from os.path import abspath, dirname, join, relpath
from setuptools import setup, find_packages

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/gen_stm32'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/gen_stm32/blob/dev/LICENSE'
__version__ = '1.2.5'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'

THIS_DIR = abspath(dirname(__file__))
long_description = None

with open(join(THIS_DIR, 'README.md'), encoding='utf-8') as readme:
    long_description = readme.read()

PROGRAMMING_LANG = 'Programming Language :: Python ::'
VERSIONS = ['3.12', '3.13', '3.14']
SUPPORTED_PY_VERSIONS = [f'{PROGRAMMING_LANG} {VERSION}' for VERSION in VERSIONS]
PYP_CLASSIFIERS = SUPPORTED_PY_VERSIONS

def find_package_data(pkg: str) -> list[str]:
    '''
        Finds all files in package to include in package_data.

        :param pkg: The package folder name.
        :return: The list of package files relative to the package folder.
        :exceptions: None.
    '''
    package_data: list[str] = []

    for root, dirs, files in walk(pkg):
        dirs[:] = [d for d in dirs if d != '__pycache__']

        for file in files:
            if file.endswith('.pyc') or file == '.editorconfig':
                continue

            full_path = join(root, file)
            rel_path = relpath(full_path, pkg)
            package_data.append(rel_path)

    return package_data

setup(
    name='gen_stm32',
    version='1.2.5',
    description='STM32 project skeleton generator',
    author='Vladimir Roncevic',
    author_email='elektron.ronca@gmail.com',
    url='https://vroncevic.github.io/gen_stm32/',
    license='GPL-3.0-or-later',
    long_description=long_description,
    long_description_content_type='text/markdown',
    keywords='STM, STM32, project, C, Unix, Linux',
    platforms='POSIX',
    classifiers=PYP_CLASSIFIERS,
    packages=find_packages(exclude=['tests', 'tests.*', '*.*.pyc', '*.pyo']),
    install_requires=['ats-utilities'],
    package_data={
        'gen_stm32': find_package_data('gen_stm32')
    }
)
