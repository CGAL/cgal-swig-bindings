#!/bin/bash
# Use with ``source osx_utils.sh``
set -e

# Get our own location on this filesystem, load common utils
MULTIBUILD_DIR=$(dirname "${BASH_SOURCE[0]}")
source $MULTIBUILD_DIR/common_utils.sh

MACPYTHON_URL=https://www.python.org/ftp/python
MACPYTHON_PY_PREFIX=/Library/Frameworks/Python.framework/Versions
WORKING_SDIR=working

# As of 7 December 2021 - latest Python of each version with binary download
# available.
# See: https://www.python.org/downloads/mac-osx/
LATEST_2p7=2.7.18
LATEST_3p5=3.5.4
LATEST_3p6=3.6.8
LATEST_3p7=3.7.9
LATEST_3p8=3.8.10
LATEST_3p9=3.9.9
LATEST_3p10=3.10.1


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
    elif [ $ver == 3 ] || [ $ver == "3.10" ]; then
        echo $LATEST_3p10
    elif [ $ver == "3.9" ]; then
        echo $LATEST_3p9
    elif [ $ver == "3.8" ]; then
        echo $LATEST_3p8
    elif [ $ver == "3.7" ]; then
        echo $LATEST_3p7
    elif [ $ver == "3.6" ]; then
        echo $LATEST_3p6
    elif [ $ver == "3.5" ]; then
        echo $LATEST_3p5
    else
        echo "Can't fill version $ver" 1>&2
        exit 1
    fi
}

function macpython_sdk_list_for_version {
    # return a list of SDK targets supported for a given CPython version
    # Parameters
    #   $py_version (python version in major.minor.extra format)
    # eg
    #  macpython_sdks_for_version 2.7.15
    #  >> 10.6 10.9
    local _ver=$(fill_pyver $1)
    local _major=${_ver%%.*}
    local _return

    if [ "$(uname -m)" = "arm64" ]; then
        _return="11.0"
    elif [ "$_major" -eq "2" ]; then
        [ $(lex_ver $_ver) -lt $(lex_ver 2.7.18) ] && _return="10.6"
        [ $(lex_ver $_ver) -ge $(lex_ver 2.7.15) ] && _return="$_return 10.9"
    elif [ "$_major" -eq "3" ]; then
        [ $(lex_ver $_ver) -lt $(lex_ver 3.8)    ] && _return="10.6"
        [ $(lex_ver $_ver) -ge $(lex_ver 3.6.5)  ] && _return="$_return 10.9"
    else
        echo "Error version=${_ver}, expecting 2.x or 3.x" 1>&2
        exit 1
    fi
    echo $_return
}

function macpython_sdk_for_version {
    # assumes the output of macpython_sdk_list_for_version is a list
    # of SDK versions XX.Y in sorted order, eg "10.6 10.9" or "10.9"
    echo $(macpython_sdk_list_for_version $1) | awk -F' ' '{print $NF}'
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
    #       if defined, the minimum macOS SDK version that Python is
    #       built for, eg: "10.6" or "10.9", if not defined, infers
    #       this from $py_version using macpython_sdk_for_version
    local py_version=$1
    local inst_ext=$(pyinst_ext_for_version $py_version)
    # Use the universal2 installer if we are on arm64
    # universal2 installer for python 3.8 needs macos 11.0 to run on
    # and therefore x86_64 builds use the intel only installer.
    # Note that intel only installer can create universal2 wheels, but
    # creates intel only wheels by default. When PLAT=universal2
    # we set the env variable _PYTHON_HOST_PLATFORM to change this
    # default.
    if [ "$(uname -m)" == "arm64" ] || [ $(lex_ver $py_version) -ge $(lex_ver 3.10.0) ]; then
      if [ "$py_version" == "3.9.1" ]; then
        echo "python-${py_version}-macos11.0.${inst_ext}"
      else
        echo "python-${py_version}-macos11.${inst_ext}"
      fi
    else
      local py_osx_ver=${2:-$(macpython_sdk_for_version $py_version)}
      echo "python-${py_version}-macosx${py_osx_ver}.${inst_ext}"
    fi
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
    if [[ $distutils_plat =~ macosx-(1[0-9]\.[0-9]+)-(.*) ]]; then
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
    if [[ $distutils_plat =~ macosx-(1[0-9]\.[0-9]+)-(.*) ]]; then
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
    if [[ "$version" =~ ^pypy ]]; then
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
    #         The Python implementation to install, e.g. "3.6", "pypy-5.4" or "pypy3.6-7.2"
    #     $py_osx_ver: {major.minor | not defined}
    #       if defined, the macOS version that CPython is built for, e.g.
    #       "10.6" or "10.9". Ignored for PyPy
    local version=$1
    local py_osx_ver=$2
    local impl=$(macpython_impl_for_version $version)
    if [[ "$impl" == "pp" ]]; then
        install_pypy $version
    elif [[ "$impl" == "cp" ]]; then
        local stripped_ver=$(strip_macpython_ver_prefix $version)
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
    local retval=""
    mkdir -p $DOWNLOADS_SDIR
    # exit early on curl errors, but don't let it exit the shell
    cmd_notexit curl -f $MACPYTHON_URL/$py_stripped/${py_inst} > $inst_path || retval=$?
    if [ ${retval:-0} -ne 0 ]; then
      echo "Python download failed! Check ${py_inst} exists on the server."
      exit $retval
    fi

    if [ "${py_inst: -3}" == "dmg" ]; then
        hdiutil attach $inst_path -mountpoint /Volumes/Python
        inst_path=/Volumes/Python/Python.mpkg
    fi
    sudo installer -pkg $inst_path -target /
    local py_mm=${py_version%.*}
    PYTHON_EXE=$MACPYTHON_PY_PREFIX/$py_mm/bin/python$py_mm
    # Install certificates for Python 3.6
    local inst_cmd="/Applications/Python ${py_mm}/Install Certificates.command"
    if [ -e "$inst_cmd" ]; then
        sh "$inst_cmd"
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

    if [ "$USE_CCACHE" == "1" ]; then
        activate_ccache
    fi

    remove_travis_ve_pip
    install_macpython $version $py_osx_ver
    PIP_CMD="$PYTHON_EXE -m pip"
    # Python 3.5 no longer compatible with latest pip
    if [ "$(get_py_mm)" == "3.5" ]; then
        # https://stackoverflow.com/a/29751768/1939576
        curl -LO https://bootstrap.pypa.io/pip/3.5/get-pip.py
        $PYTHON_EXE get-pip.py
        rm get-pip.py
    else
        $PYTHON_EXE -m ensurepip
        $PIP_CMD install --upgrade pip
    fi

    if [ -n "$venv_dir" ]; then
        install_virtualenv
        make_workon_venv $venv_dir
        source $venv_dir/bin/activate
    else
        export PATH="`dirname $PYTHON_EXE`:$PATH"
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
    # https://github.com/multi-build/multibuild/issues/24#issue-221951587
    command -v pkg-config > /dev/null 2>&1 || brew install pkg-config
}

function activate_ccache {

    brew install ccache
    export PATH=/usr/local/opt/ccache/libexec:$PATH
    export CCACHE_CPP2=1

    # Prove to the developer that ccache is activated
    echo "Using C compiler: $(which clang)"
}

function macos_intel_native_build_setup {
    # Setup native build for single arch x86_64 wheels
    export PLAT="x86_64"
    export _PYTHON_HOST_PLATFORM="macosx-${MB_PYTHON_OSX_VER}-x86_64"
    export CFLAGS+=" -arch x86_64"
    export CXXFLAGS+=" -arch x86_64"
    export ARCHFLAGS+=" -arch x86_64"
    export CPPFLAGS+=" -arch x86_64"
    export LDFLAGS+=" -arch x86_64"
}

function macos_intel_cross_build_setup {
    echo "universal2 builds on arm64 are not supported yet."
    exit 1
}

function macos_arm64_cross_build_setup {
    # Setup cross build for single arch arm_64 wheels
    export PLAT="arm64"
    export BUILD_PREFIX=/opt/arm64-builds
    sudo mkdir -p $BUILD_PREFIX/lib $BUILD_PREFIX/include
    sudo chown -R $USER $BUILD_PREFIX
    update_env_for_build_prefix
    export _PYTHON_HOST_PLATFORM="macosx-11.0-arm64"
    export CFLAGS+=" -arch arm64"
    export CXXFLAGS+=" -arch arm64"
    export CPPFLAGS+=" -arch arm64"
    export ARCHFLAGS+=" -arch arm64"
    export FCFLAGS+=" -arch arm64"
    export FC=$FC_ARM64
    export F90=${F90_ARM64:-${FC}}
    export F77=${F77_ARM64:-${FC}}
    export MACOSX_DEPLOYMENT_TARGET="11.0"
    export CROSS_COMPILING=1
    export LDFLAGS+=" -arch arm64 -L$BUILD_PREFIX/lib -Wl,-rpath,$BUILD_PREFIX/lib ${FC_ARM64_LDFLAGS:-}"
    # This would automatically let autoconf know that we are cross compiling for arm64 darwin
    export host_alias="aarch64-apple-darwin20.0.0"
}

function macos_arm64_native_build_setup {
    # Setup native build for single arch arm_64 wheels
    export PLAT="arm64"
    # We don't want universal2 builds and only want an arm64 build
    export _PYTHON_HOST_PLATFORM="macosx-11.0-arm64"
    export ARCHFLAGS+="-arch arm64"
    $@
}

function fuse_macos_intel_arm64 {
    local wheelhouse=$(abspath ${WHEEL_SDIR:-wheelhouse})
    local py_osx_ver=$(echo ${MB_PYTHON_OSX_VER} | sed "s/\./_/g")
    mkdir -p tmp_fused_wheelhouse
    for whl in $wheelhouse/*.whl; do
       if [[ "$whl" == *macosx_${py_osx_ver}_x86_64.whl ]]; then
           whl_base=$(echo $whl | rev | cut -c 23- | rev)
           if [[ -f "${whl_base}macosx_11_0_arm64.whl" ]]; then
               delocate-fuse $whl "${whl_base}macosx_11_0_arm64.whl" -w tmp_fused_wheelhouse
               mv tmp_fused_wheelhouse/$(basename $whl) $wheelhouse/$(basename ${whl_base})macosx_${py_osx_ver}_universal2.whl
               # Since we want one wheel that's installable for testing we are deleting the *_x86_64 wheel.
               # We are not deleting arm64 wheel because the size is lower and homebrew/conda-forge python
               # will use them by default
               rm $whl
           fi
       fi
    done
}

function wrap_wheel_builder {
    if [[ "${PLAT:-}" == "universal2" ]]; then
        if [[ "$(uname -m)" == "arm64" ]]; then
            (macos_intel_cross_build_setup && $@)
            rm -rf *-stamp
            (macos_arm64_native_build_setup && $@)
        else
            (macos_intel_native_build_setup && $@)
            rm -rf *-stamp
            (macos_arm64_cross_build_setup && $@)
        fi
        fuse_macos_intel_arm64
    elif [[ "${PLAT:-}" == "arm64" ]]; then
        if [[ "$(uname -m)" == "arm64" ]]; then
            (macos_arm64_native_build_setup && $@)
        else
            (macos_arm64_cross_build_setup && $@)
        fi
    elif [[ "${PLAT:-}" == "x86_64" ]]; then
        if [[ "$(uname -m)" == "x86_64" ]]; then
            (macos_intel_native_build_setup && $@)
        else
            (macos_intel_cross_build_setup && $@)
        fi
    else
        $@
    fi
}
