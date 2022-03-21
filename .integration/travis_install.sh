#!/bin/bash
set -x
if [ $(python -c "import sys; print(sys.version_info.major)") = "3" ] && [ "$1" = "Linux" ]; then
  docker pull cgal/python-wheel:manylinux2014
  docker run --rm -v/cgal:/cgal -v${PWD}:/cgal-bindings -ePYTHON_VERSION_MINOR=$(python -c "import sys; print(sys.version_info.minor)") -t cgal/python-wheel:manylinux2014
elif [ $(python -c "import sys; print(sys.version_info.major)") = "3" ] && [ "$1" = "macOS" ]; then
  which python
  python -m pip install delocate
  python setup.py bdist_wheel --cgal-dir=/usr/local/opt/cgal/lib/cmake/CGAL
  delocate-wheel -w fixed_wheel dist/*.whl 
fi
