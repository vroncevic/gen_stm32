# -*- coding: utf-8 -*-

import os
import sys
sys.path.insert(0, os.path.abspath('../../'))

project = u'gen_stm32'
copyright = u'2018 Vladimir Roncevic <elektron.ronca@gmail.com>'
author = u'Vladimir Roncevic <elektron.ronca@gmail.com>'
version = u'v1.1.0'
release = u'https://github.com/vroncevic/gen_stm32/releases'
extensions = ['sphinx.ext.autodoc', 'sphinx.ext.viewcode']
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
language = None
exclude_patterns = []
pygments_style = None
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
htmlhelp_basename = 'gen_stm32doc'
latex_elements = {}
latex_documents = [(
    master_doc, 'gen_stm32.tex', u'gen\\_stm32 Documentation',
    u'Vladimir Roncevic \\textless{}elektron.ronca@gmail.com\\textgreater{}',
    'manual'
)]
man_pages = [(
    master_doc, 'gen_stm32', u'gen_stm32 Documentation', [author], 1
)]
texinfo_documents = [(
    master_doc, 'gen_stm32', u'gen_stm32 Documentation', author, 'gen_stm32',
    'One line description of project.', 'Miscellaneous'
)]
epub_title = project
epub_exclude_files = ['search.html']
