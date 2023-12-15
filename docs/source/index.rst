STM32 project skeleton generator
--------------------------------

**gen_stm32** is toolset for generation STM32 project skeleton for development of embedded applications.

Developed in `python <https://www.python.org/>`_ code.

The README is used to introduce the tool and provide instructions on
how to install the tool, any machine dependencies it may have and any
other information that should be provided before the tool is installed.

|gen_stm32 python checker| |gen_stm32 python package| |github issues| |documentation status| |github contributors|

.. |gen_stm32 python checker| image:: https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python_checker.yml/badge.svg
   :target: https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python_checker.yml

.. |gen_stm32 python package| image:: https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_package_checker.yml/badge.svg
   :target: https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_package.yml

.. |github issues| image:: https://img.shields.io/github/issues/vroncevic/gen_stm32.svg
   :target: https://github.com/vroncevic/gen_stm32/issues

.. |github contributors| image:: https://img.shields.io/github/contributors/vroncevic/gen_stm32.svg
   :target: https://github.com/vroncevic/gen_stm32/graphs/contributors

.. |documentation status| image:: https://readthedocs.org/projects/gen-avr8/badge/?version=latest
   :target: https://gen-avr8.readthedocs.io/en/latest/?badge=latest

.. toctree::
   :maxdepth: 4
   :caption: Contents

   modules
   self

Installation
-------------

|gen_stm32 python3 build|

.. |gen_stm32 python3 build| image:: https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python3_build.yml/badge.svg
   :target: https://github.com/vroncevic/gen_stm32/actions/workflows/gen_stm32_python3_build.yml

Navigate to release `page`_ download and extract release archive.

.. _page: https://github.com/vroncevic/gen_stm32/releases

To install **gen_stm32** type the following

.. code-block:: bash

    tar xvzf gen_stm32-x.y.z.tar.gz
    cd gen_stm32-x.y.z/
    # python3
    wget https://bootstrap.pypa.io/get-pip.py
    python3 get-pip.py 
    python3 -m pip install --upgrade setuptools
    python3 -m pip install --upgrade pip
    python3 -m pip install --upgrade build
    pip3 install -r requirements.txt
    python3 -m build --no-isolation --wheel
    pip3 install ./dist/gen_stm32-*-py3-none-any.whl
    rm -f get-pip.py
    chmod 755 /usr/local/lib/python3.10/dist-packages/usr/local/bin/gen_stm32_run.py
    ln -s /usr/local/lib/python3.10/dist-packages/usr/local/bin/gen_stm32_run.py /usr/local/bin/gen_stm32_run.py

You can use Docker to create image/container, or You can use pip to install

.. code-block:: bash

    # pyton3
    pip3 install gen-stm32


Dependencies
-------------

**gen_stm32** requires next modules and libraries

* `ats-utilities - Python App/Tool/Script Utilities <https://pypi.org/project/ats-utilities/>`_

Tool structure
---------------

**gen_stm32** is based on OOP.

Code structure:

.. code-block:: bash

    gen_stm32/
        ├── conf/
        │   ├── gen_stm32.logo
        │   ├── gen_stm32.cfg
        │   ├── gen_stm32_util.cfg
        │   ├── project.yaml
        │   └── template/
        │       ├── build/
        │       │   ├── includes/
        │       │   │   └── STM32F4xx_StdPeriph_Driver/
        │       │   │       └── src/
        │       │   │           └── subdir.template
        │       │   ├── Makefile.template
        │       │   ├── objects.template
        │       │   ├── source/
        │       │   │   └── subdir.template
        │       │   └── sources.template
        │       ├── includes/
        │       │   ├── CMSIS/
        │       │   │   ├── arm_common_tables.template
        │       │   │   ├── arm_math.template
        │       │   │   ├── core_cm0.template
        │       │   │   ├── core_cm3.template
        │       │   │   ├── core_cm4_simd.template
        │       │   │   ├── core_cm4.template
        │       │   │   ├── core_cmFunc.template
        │       │   │   └── core_cmInstr.template
        │       │   ├── STM32F4xx/
        │       │   │   ├── stm32f4xx_conf.template
        │       │   │   ├── stm32f4xx.template
        │       │   │   └── system_stm32f4xx.template
        │       │   └── STM32F4xx_StdPeriph_Driver/
        │       │       ├── inc/
        │       │       │   ├── misc.template
        │       │       │   ├── stm32f4xx_adc.template
        │       │       │   ├── stm32f4xx_can.template
        │       │       │   ├── stm32f4xx_crc.template
        │       │       │   ├── stm32f4xx_cryp.template
        │       │       │   ├── stm32f4xx_dac.template
        │       │       │   ├── stm32f4xx_dbgmcu.template
        │       │       │   ├── stm32f4xx_dcmi.template
        │       │       │   ├── stm32f4xx_dma.template
        │       │       │   ├── stm32f4xx_exti.template
        │       │       │   ├── stm32f4xx_flash.template
        │       │       │   ├── stm32f4xx_fsmc.template
        │       │       │   ├── stm32f4xx_gpio.template
        │       │       │   ├── stm32f4xx_hash.template
        │       │       │   ├── stm32f4xx_i2c.template
        │       │       │   ├── stm32f4xx_iwdg.template
        │       │       │   ├── stm32f4xx_pwr.template
        │       │       │   ├── stm32f4xx_rcc.template
        │       │       │   ├── stm32f4xx_rng.template
        │       │       │   ├── stm32f4xx_rtc.template
        │       │       │   ├── stm32f4xx_sdio.template
        │       │       │   ├── stm32f4xx_spi.template
        │       │       │   ├── stm32f4xx_syscfg.template
        │       │       │   ├── stm32f4xx_tim.template
        │       │       │   ├── stm32f4xx_usart.template
        │       │       │   └── stm32f4xx_wwdg.template
        │       │       └── src/
        │       │           ├── misc.template
        │       │           ├── stm32f4xx_adc.template
        │       │           ├── stm32f4xx_can.template
        │       │           ├── stm32f4xx_crc.template
        │       │           ├── stm32f4xx_cryp_aes.template
        │       │           ├── stm32f4xx_cryp_des.template
        │       │           ├── stm32f4xx_cryp_tdes.template
        │       │           ├── stm32f4xx_cryp.template
        │       │           ├── stm32f4xx_dac.template
        │       │           ├── stm32f4xx_dbgmcu.template
        │       │           ├── stm32f4xx_dcmi.template
        │       │           ├── stm32f4xx_dma.template
        │       │           ├── stm32f4xx_exti.template
        │       │           ├── stm32f4xx_flash.template
        │       │           ├── stm32f4xx_fsmc.template
        │       │           ├── stm32f4xx_gpio.template
        │       │           ├── stm32f4xx_hash_md5.template
        │       │           ├── stm32f4xx_hash_sha1.template
        │       │           ├── stm32f4xx_hash.template
        │       │           ├── stm32f4xx_i2c.template
        │       │           ├── stm32f4xx_iwdg.template
        │       │           ├── stm32f4xx_pwr.template
        │       │           ├── stm32f4xx_rcc.template
        │       │           ├── stm32f4xx_rng.template
        │       │           ├── stm32f4xx_rtc.template
        │       │           ├── stm32f4xx_sdio.template
        │       │           ├── stm32f4xx_spi.template
        │       │           ├── stm32f4xx_syscfg.template
        │       │           ├── stm32f4xx_tim.template
        │       │           ├── stm32f4xx_usart.template
        │       │           └── stm32f4xx_wwdg.template
        │       ├── scripts/
        │       │   └── arm_cortex_m4_512.template
        │       └── source/
        │           ├── main.template
        │           ├── startup_stm32f4xx.template
        │           ├── syscall.template
        │           ├── system_stm32f4xx.template
        │           └── tinynew.template
        ├── __init__.py
        ├── log/
        │   └── gen_stm32.log
        ├── pro/
        │   ├── __init__.py
        │   ├── read_template.py
        │   └── write_template.py
        └── run/
            └── gen_stm32_run.py

    19 directories, 89 files

Copyright and licence
-----------------------

|License: GPL v3| |License: Apache 2.0|

.. |License: GPL v3| image:: https://img.shields.io/badge/License-GPLv3-blue.svg
   :target: https://www.gnu.org/licenses/gpl-3.0

.. |License: Apache 2.0| image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg
   :target: https://opensource.org/licenses/Apache-2.0

Copyright (C) 2018 - 2024 by `vroncevic.github.io/gen_stm32 <https://vroncevic.github.io/gen_stm32>`_

**gen_stm32** is free software; you can redistribute it and/or modify
it under the same terms as Python itself, either Python version 3.x or,
at your option, any later version of Python 3 you may have available.

Lets help and support PSF.

|python software foundation|

.. |python software foundation| image:: https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/docs/psf-logo-alpha.png
   :target: https://www.python.org/psf/

|donate|

.. |donate| image:: https://www.paypalobjects.com/en_us/i/btn/btn_donatecc_lg.gif
   :target: https://www.python.org/psf/donations/

Indices and tables
------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
