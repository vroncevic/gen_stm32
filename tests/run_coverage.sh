#!/bin/bash
#
# @brief   gen_stm32
# @version v1.0.1
# @date    Sat Aug 11 09:58:41 2018
# @company None, free software to use 2018
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

rm -rf htmlcov gen_stm32_coverage.xml gen_stm32_coverage.json .coverage
rm -rf new_simple_test/ full_simple/ latest/
python3 -m coverage run -m --source=../gen_stm32 unittest discover -s ./ -p '*_test.py' -vvv
python3 -m coverage html -d htmlcov
python3 -m coverage xml -o gen_stm32_coverage.xml 
python3 -m coverage json -o gen_stm32_coverage.json
python3 -m coverage report --format=markdown -m
python3 ats_coverage.py -n gen_stm32
rm htmlcov/.gitignore
echo "Done"