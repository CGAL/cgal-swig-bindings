#.. _license:
#
#*********************
#Copyright and License
#*********************
#
#The multibuild package, including all examples, code snippets and attached
#documentation is covered by the 2-clause BSD license.
#
#    Copyright (c) 2013-2019, Matt Terry and Matthew Brett; all rights
#    reserved.
#
#    Redistribution and use in source and binary forms, with or without
#    modification, are permitted provided that the following conditions are
#    met:
#
#    1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
#    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
#    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#!/bin/bash
# Use with ``source osx_utils.sh``
set -e
set -x
# Get our own location on this filesystem, load common utils
MULTIBUILD_DIR=$(dirname "${BASH_SOURCE[0]}")
source $MULTIBUILD_DIR/common_utils.sh

MACPYTHON_URL=https://www.python.org/ftp/python
MACPYTHON_PY_PREFIX=/Library/Frameworks/Python.framework/Versions
MACPYTHON_DEFAULT_OSX="10.9"
MB_PYTHON_OSX_VER=${MB_PYTHON_OSX_VER:-$MACPYTHON_DEFAULT_OSX}
GET_PIP_URL=https://bootstrap.pypa.io/get-pip.py
DOWNLOADS_SDIR=downloads
WORKING_SDIR=working

# As of 20 Oct 2019 - latest Python of each version with binary download
# available.
# See: https://www.python.org/downloads/mac-osx/
LATEST_2p7=2.7.17
LATEST_3p5=3.5.4
LATEST_3p6=3.6.8
LATEST_3p7=3.7.5
LATEST_3p8=3.8.0


function check_python {
    if [ -z "$PYTHON_EXE" ]; then
        echo "PYTHON_EXE variable not defined"
        exit 1
    fi
}

function check_pip {
    if [ -z "$PIP_CMD" ]; then
        echo "PIP_CMD variable not defined"
        exit 1
    fi
}

function check_var {
    if [ -z "$1" ]; then
        echo "required variable not defined"
        exit 1
    fi
}

function get_py_digit {
    check_python
    $PYTHON_EXE -c "import sys; print(sys.version_info[0])"
}

function get_py_mm {
    check_python
    $PYTHON_EXE -c "import sys; print('{0}.{1}'.format(*sys.version_info[0:2]))"
}

function get_py_mm_nodot {
    check_python
    $PYTHON_EXE -c "import sys; print('{0}{1}'.format(*sys.version_info[0:2]))"
}

function get_py_prefix {
    check_python
    $PYTHON_EXE -c "import sys; print(sys.prefix)"
}

function fill_pyver {
    # Convert major or major.minor format to major.minor.micro
    #
    # Hence:
    # 2 -> 2.7.11  (depending on LATEST_2p7 value)
    # 2.7 -> 2.7.11  (depending on LATEST_2p7 value)
    local ver=$1
    check_var $ver
    if [[ $ver =~ [0-9]+\.[0-9]+\.[0-9]+ ]]; then
        # Major.minor.micro format already
        echo $ver
    elif [ $ver == 2 ] || [ $ver == "2.7" ]; then
        echo $LATEST_2p7
    elif [ $ver == 3 ] || [ $ver == "3.7" ]; then
        echo $LATEST_3p7
    elif [ $ver == "3.6" ]; then
        echo $LATEST_3p6
    elif [ $ver == "3.5" ]; then
        echo $LATEST_3p5
    elif [ $ver == "3.8" ]; then
        echo $LATEST_3p8
    else
        echo "Can't fill version $ver" 1>&2
        exit 1
    fi
}

function pyinst_ext_for_version {
    # echo "pkg" or "dmg" depending on the passed Python version
    # Parameters
    #   $py_version (python version in major.minor.extra format)
    #
    # Earlier Python installers are .dmg, later are .pkg.
    local py_version=$1
    check_var $py_version
    py_version=$(fill_pyver $py_version)
    local py_0=${py_version:0:1}
    if [ $py_0 -eq 2 ]; then
        if [ "$(lex_ver $py_version)" -ge "$(lex_ver 2.7.9)" ]; then
            echo "pkg"
        else
            echo "dmg"
        fi
    elif [ $py_0 -ge 3 ]; then
		echo "pkg"
    fi
}

function pyinst_fname_for_version {
    # echo filename for OSX installer file given Python and minimum
    # macOS versions
    # Parameters
    #   $py_version (Python version in major.minor.extra format)
    #   $py_osx_ver: {major.minor | not defined}
    #       if defined, the macOS version that Python is built for, e.g.
    #       "10.6" or "10.9", if not defined, uses the default
    #       MACPYTHON_DEFAULT_OSX
    #       Note: this is the version the Python is built for, and hence
    #       the min version supported, NOT the version of the current system
    local py_version=$1
    local py_osx_ver=${2:-$MACPYTHON_DEFAULT_OSX}
    local inst_ext=$(pyinst_ext_for_version $py_version)
    echo "python-${py_version}-macosx${py_osx_ver}.${inst_ext}"
}

function get_macpython_arch {
    # echo arch (e.g. intel or x86_64), extracted from the distutils platform tag
    # Parameters
    #   $distutils_plat   PEP425 style platform tag, or if not provided, calls
    #                       the function get_distutils_platform, provided by
    #                       common_utils.sh. Fails if this is not a mac platform
    #
    # Note: MUST only be called after the version of Python used to build the
    # target wheel has been installed and is on the path
    local distutils_plat=${1:-$(get_distutils_platform)}
    if [[ $distutils_plat =~ macosx-(10\.[0-9]+)-(.*) ]]; then
        echo ${BASH_REMATCH[2]}
    else
        echo "Error parsing macOS distutils platform '$distutils_plat'"
        exit 1
    fi
}

function get_macpython_osx_ver {
    # echo minimum macOS version (e.g. 10.9) from the distutils platform tag
    # Parameters
    #   $distutils_plat   PEP425 style platform tag, or if not provided, calls
    #                       the function get_distutils_platform, provided by
    #                       common_utils.sh. Fails if this is not a mac platform
    #
    # Note: MUST only be called after the version of Python used to build the
    # target wheel has been installed and is on the path
    local distutils_plat=${1:-$(get_distutils_platform)}
    if [[ $distutils_plat =~ macosx-(10\.[0-9]+)-(.*) ]]; then
        echo ${BASH_REMATCH[1]}
    else
        echo "Error parsing macOS distutils platform '$distutils_plat'"
        exit 1
    fi
}

function macpython_arch_for_version {
    # echo arch (intel or x86_64) that a version of Python is expected
    # to be built for
    # Parameters
    #   $py_ver     Python version, in the format (major.minor.patch) for
    #               CPython, or pypy-(major.minor) for PyPy
    #   $py_osx_ver minimum macOS version the target Python is built for
    #               (major.minor)
    local py_ver=$1
    local py_osx_ver=${2:-$MB_PYTHON_OSX_VER}
    check_var $1
    if [[ $(macpython_impl_for_version $py_ver) == "cp" ]]; then
        if [[ "$py_osx_ver" == "10.6" ]]; then
            echo "intel"
        elif [[ "$py_osx_ver" == "10.9" ]]; then
            echo "x86_64"
        else
            echo "Unexpected CPython macOS version: ${py_osx_ver}, supported values: 10.6 and 10.9"
            exit 1
        fi
    else
        echo "x86_64"
    fi
}

function macpython_impl_for_version {
    # echo Python implementation (cp for CPython, pp for PyPy) given a
    # suitably formatted version string
    # Parameters:
    #     $version : [implementation-]major[.minor[.patch]]
    #         Python implementation, e.g. "3.6" for CPython or
    #         "pypy-5.4" for PyPy
    local version=$1
    check_var $1
    if [[ "$version" =~ pypy-([0-9\.]+) ]]; then
        echo pp
    elif [[ "$version" =~ ([0-9\.]+) ]]; then
        echo cp
    else
        echo "config error: Issue parsing this implementation in install_python:"
        echo "    version=$version"
        exit 1
    fi
}

function strip_macpython_ver_prefix {
    # strip any implementation prefix from a Python version string
    # Parameters:
    #     $version : [implementation-]major[.minor[.patch]]
    #         Python implementation, e.g. "3.6" for CPython or
    #         "pypy-5.4" for PyPy
    local version=$1
    check_var $1
    if [[ "$version" =~ (pypy-)?([0-9\.]+) ]]; then
        echo ${BASH_REMATCH[2]}
    fi
}

function install_macpython {
    # Install Python and set $PYTHON_EXE to the installed executable
    # Parameters:
    #     $version : [implementation-]major[.minor[.patch]]
    #         The Python implementation to install, e.g. "3.6" or "pypy-5.4"
    #     $py_osx_ver: {major.minor | not defined}
    #       if defined, the macOS version that CPython is built for, e.g.
    #       "10.6" or "10.9". Ignored for PyPy
    local version=$1
    local py_osx_ver=$2
    local impl=$(macpython_impl_for_version $version)
    local stripped_ver=$(strip_macpython_ver_prefix $version)
    if [[ "$impl" == "pp" ]]; then
        install_mac_pypy $stripped_ver
    elif [[ "$impl" == "cp" ]]; then
        install_mac_cpython $stripped_ver $py_osx_ver
    else
        echo "Unexpected Python impl: ${impl}"
        exit 1
    fi
}

function install_mac_cpython {
    # Installs Python.org Python
    # Parameters
    #   $py_version
    #       Version given in major or major.minor or major.minor.micro e.g
    #       "3" or "3.7" or "3.7.1".
    #   $py_osx_ver
    #       {major.minor | not defined}
    #       if defined, the macOS version that Python is built for, e.g.
    #        "10.6" or "10.9"
    # sets $PYTHON_EXE variable to Python executable
    local py_version=$(fill_pyver $1)
    local py_osx_ver=$2
    local py_stripped=$(strip_ver_suffix $py_version)
    local py_inst=$(pyinst_fname_for_version $py_version $py_osx_ver)
    local inst_path=$DOWNLOADS_SDIR/$py_inst
    mkdir -p $DOWNLOADS_SDIR
    curl $MACPYTHON_URL/$py_stripped/${py_inst} > $inst_path
    if [ "${py_inst: -3}" == "dmg" ]; then
        hdiutil attach $inst_path -mountpoint /Volumes/Python
        inst_path=/Volumes/Python/Python.mpkg
    fi
    sudo installer -pkg $inst_path -target /
    local py_mm=${py_version:0:3}
    PYTHON_EXE=$MACPYTHON_PY_PREFIX/$py_mm/bin/python$py_mm
    # Install certificates for Python 3.6
    local inst_cmd="/Applications/Python ${py_mm}/Install Certificates.command"
    if [ -e "$inst_cmd" ]; then
        sh "$inst_cmd"
    fi
}

function install_mac_pypy {
    # Installs pypy.org PyPy
    # Parameter $version
    # Version given in major or major.minor or major.minor.micro e.g
    # "3" or "3.7" or "3.7.1".
    # sets $PYTHON_EXE variable to python executable
    local py_version=$(fill_pypy_ver $1)
    local py_build=$(get_pypy_build_prefix $py_version)$py_version-osx64
    local py_zip=$py_build.tar.bz2
    local zip_path=$DOWNLOADS_SDIR/$py_zip
    mkdir -p $DOWNLOADS_SDIR
    wget -nv $PYPY_URL/${py_zip} -P $DOWNLOADS_SDIR
    untar $zip_path
    PYTHON_EXE=$(realpath $py_build/bin/pypy)
}

function install_pip {
    # Generic install pip
    # Gets needed version from version implied by $PYTHON_EXE
    # Installs pip into python given by $PYTHON_EXE
    # Assumes pip will be installed into same directory as $PYTHON_EXE
    check_python
    mkdir -p $DOWNLOADS_SDIR
    local py_mm=`get_py_mm`
    local get_pip_path=$DOWNLOADS_SDIR/get-pip.py
    curl $GET_PIP_URL > $get_pip_path
    # Travis VMS now install pip for system python by default - force install
    # even if installed already.
    sudo $PYTHON_EXE $get_pip_path --ignore-installed $pip_args
    PIP_CMD="sudo $(dirname $PYTHON_EXE)/pip$py_mm"
    # Append pip_args if present (avoiding trailing space cf using variable
    # above).
    if [ -n "$pip_args" ]; then
        PIP_CMD="$PIP_CMD $pip_args"
    fi
}

function install_virtualenv {
    # Generic install of virtualenv
    # Installs virtualenv into python given by $PYTHON_EXE
    # Assumes virtualenv will be installed into same directory as $PYTHON_EXE
    check_pip
    # Travis VMS install virtualenv for system python by default - force
    # install even if installed already
    $PIP_CMD install virtualenv --ignore-installed
    check_python
    VIRTUALENV_CMD="$(dirname $PYTHON_EXE)/virtualenv"
}

function make_workon_venv {
    # Make a virtualenv in given directory ('venv' default)
    # Set $PYTHON_EXE, $PIP_CMD to virtualenv versions
    # Parameter $venv_dir
    #    directory for virtualenv
    local venv_dir=$1
    if [ -z "$venv_dir" ]; then
        venv_dir="venv"
    fi
    venv_dir=`abspath $venv_dir`
    check_python
    $PYTHON_EXE -m virtualenv $venv_dir
    PYTHON_EXE=$venv_dir/bin/python
    PIP_CMD=$venv_dir/bin/pip
}

function remove_travis_ve_pip {
    # Remove travis installs of virtualenv and pip
    # FIXME: What if virtualenv is installed but pip is not?
    if [ "$(sudo which virtualenv)" == /usr/local/bin/virtualenv ] && [ "$(sudo which pip)" == /usr/local/bin/pip ]; then
        sudo pip uninstall -y virtualenv;
    fi
    if [ "$(sudo which pip)" == /usr/local/bin/pip ]; then
        sudo pip uninstall -y pip;
    fi
}

function set_py_vars {
    # Used by terryfy project; left here for back-compatibility
    pushd $(dirname $PYTHON_EXE)
    ln -s $PYTHON_EXE python
    popd
    export PATH="`dirname $PYTHON_EXE`:$PATH"
    export PYTHON_EXE PIP_CMD
}

function get_macpython_environment {
    # Set up MacPython environment
    # Parameters:
    #     $version : [implementation-]major[.minor[.patch]]
    #         The Python implementation to install, e.g. "3.6" or "pypy-5.4"
    #     $venv_dir : {directory_name|not defined}
    #         If defined - make virtualenv in this directory, set python / pip
    #         commands accordingly
    #     $py_osx_ver: {major.minor | not defined}
    #         if defined, the macOS version that Python is built for, e.g.
    #         "10.6" or "10.9", if not defined, use the version from MB_PYTHON_OSX_VER
    #
    # Installs Python
    # Sets $PYTHON_EXE to path to Python executable
    # Sets $PIP_CMD to full command for pip (including sudo if necessary)
    # If $venv_dir defined, Sets $VIRTUALENV_CMD to virtualenv executable
    # Puts directory of $PYTHON_EXE on $PATH
    local version=$1
    local venv_dir=$2
    local py_osx_ver=${3:-$MB_PYTHON_OSX_VER}

    #remove_travis_ve_pip
    install_macpython $version $py_osx_ver
    install_pip

    if [ -n "$venv_dir" ]; then
        install_virtualenv
        make_workon_venv $venv_dir
        set_py_vars
        source $venv_dir/bin/activate
    else
        set_py_vars
    fi
    export PYTHON_EXE PIP_CMD
}

function install_delocate {
    check_pip
    $PIP_CMD install delocate
}

function repair_wheelhouse {
    local wheelhouse=$1
    install_delocate
    delocate-wheel $wheelhouse/*.whl # copies library dependencies into wheel
}

function install_pkg_config {
    # Install pkg-config avoiding error from homebrew
    # See :
    # https://github.com/matthew-brett/multibuild/issues/24#issue-221951587
    command -v pkg-config > /dev/null 2>&1 || brew install pkg-config
}

function activate_ccache {

    brew install ccache
    export PATH=/usr/local/opt/ccache/libexec:$PATH
    export CCACHE_CPP2=1

    # Prove to the developer that ccache is activated
    echo "Using C compiler: $(which clang)"
}
