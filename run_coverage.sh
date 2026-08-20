#!/bin/bash
#
# @brief   gen_stm32
# @version 1.2.6
# @date    Sat Aug 08 07:35:10 2026
# @company None, free software to use 2026
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

python3 coverage/ats_coverage.py gen_stm32
pylint gen_stm32 > gen_stm32.report
echo "Done"
