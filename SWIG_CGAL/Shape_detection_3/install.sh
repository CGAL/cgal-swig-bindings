#!/bin/bash
#  install.sh
#  Cody Fagley
#  Authored on   October 21, 2019
#  Last Modified October 21, 2019

cd ../../..
cmake .
make

sudo cp -r build-python/CGAL /usr/lib/python3.8/

