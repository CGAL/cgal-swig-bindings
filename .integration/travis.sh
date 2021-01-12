#!/bin/bash

set -e
set -x
export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64
pycodestyle --show-source --show-pep8 $PYCODESTYLE_CONVENTIONS $CGAL_PYTHON_EXAMPLES || pycodestyle --statistics $PYCODESTYLE_CONVENTIONS -qq $CGAL_PYTHON_EXAMPLES
if [ $(python -c "import sys; print(sys.version_info.major)") = "3" ]  && [ "$1" = "Linux" ]; then
  python -m pip install --verbose wheelhouse/*
  cd examples/python
  for test_file in ./*.py; do python $test_file; done
  cd ../..
  if [ -n "$DO_UPLOAD" ]; then
    twine upload -r testpypi wheelhouse/*  -u "cgal" -p "${{ secrets.TEST_PYPI_PASSWORD }}" --non-interactive --skip-existing
  fi
  
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/.local/ -DBUILD_PYTHON=OFF .
  make -j2 VERBOSE=1 && make install -j2 && make tests -j2 VERBOSE=1 && ctest -j2 --output-on-failure
elif [ $(python -c "import sys; print(sys.version_info.major)") = "3" ]  && [ "$1" =  "macOS" ]; then
  python -m pip install --verbose fixed_wheel/* --user
  cd examples/python
  for test_file in ./*.py; do python $test_file; done
  cd ../..
  cmake -DCGAL_DIR=/usr/local/opt/cgal/lib/cmake/CGAL -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/.local/ -DBUILD_PYTHON=OFF .
  make -j2 VERBOSE=1 && make install -j2 && make tests -j2 VERBOSE=1 && ctest -j2 --output-on-failure
  if [ -n "$DO_UPLOAD" ]; then
    twine upload -r testpypi fixed_wheel/*  -u "cgal" -p "${{ secrets.TEST_PYPI_PASSWORD }}" --non-interactive --skip-existing
  fi
else
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/.local/ -DPython_FIND_VERSION_MAJOR=2 .
  make -j2 VERBOSE=1 && make install -j2 && make tests -j2 VERBOSE=1 && ctest -j2 --output-on-failure
fi
