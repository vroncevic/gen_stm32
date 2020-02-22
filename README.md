# STM32 project skeleton generator.

gen_stm32 is toolset for generation STM32 project skeleton for
development of embedded applications.

Developed in python code: 100%.

The README is used to introduce the modules and provide instructions on
how to install the modules, any machine dependencies it may have and any
other information that should be provided before the modules are installed.

### INSTALLATION

To install this set of modules type the following:

```
cp -R ~/gen_stm32_scripts/bin/   /root/scripts/gen_stm32/ver.1.0/
cp -R ~/gen_stm32_scripts/conf/  /root/scripts/gen_stm32/ver.1.0/
cp -R ~/gen_stm32_scripts/log/   /root/scripts/gen_stm32/ver.1.0/
```

### DEPENDENCIES

This module requires these other modules and libraries:

* ats_utilities https://vroncevic.github.io/ats_utilities

### GENERATION FLOW OF STM32 PROJECT SETUP

Base flow of generation process:

![alt tag](https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/python-tool-docs/gen_stm32_flow.png)

### TOOL STRUCTURE

gen_stm32 is based on Template mechanism:

![alt tag](https://raw.githubusercontent.com/vroncevic/gen_stm32/dev/python-tool-docs/gen_stm32.png)

### COPYRIGHT AND LICENCE

Copyright (C) 2019 by https://vroncevic.github.io/gen_stm32/

This tool is free software; you can redistribute it and/or modify
it under the same terms as Python itself, either Python version 2.7/3.4 or,
at your option, any later version of Python 3 you may have available.

:sparkles:
