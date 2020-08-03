#!/bin/bash
set -x
if [ $(python -c "import sys; print(sys.version_info.major)") = "3" ] && [ "$TRAVIS_OS_NAME" = "linux" ]; then
  docker pull cgal/python-wheel:manylinux2014
  docker run --rm -v/cgal:/cgal -v${TRAVIS_BUILD_DIR}:/cgal-bindings -ePYTHON_VERSION_MINOR=$(python -c "import sys; print(sys.version_info.minor)") -t cgal/python-wheel:manylinux2014
elif [ $(python -c "import sys; print(sys.version_info.major)") = "3" ] && [ "$TRAVIS_OS_NAME" = "osx" ]; then
  which python
  python -m pip install delocate
  python setup.py bdist_wheel --cgal-dir=/cgal --keep-temp --python-root=/Library/Frameworks/Python.framework/Versions/$MB_PYTHON_VERSION
  delocate-wheel -w fixed_wheel dist/*.whl 
fi

