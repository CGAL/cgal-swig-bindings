#!/bin/bash
# Utilities for both OSX and Docker Linux
# Python should be on the PATH

# Only source common_utils once
if [ -n "$COMMON_UTILS_SOURCED" ]; then
    return
fi
COMMON_UTILS_SOURCED=1

# Turn on exit-if-error
set -e

MULTIBUILD_DIR=$(dirname "${BASH_SOURCE[0]}")
DOWNLOADS_SDIR=downloads
PYPY_URL=https://downloads.python.org/pypy
# For back-compatibility.  We use the "ensurepip" module now
# instead of get-pip.py
GET_PIP_URL=https://bootstrap.pypa.io/get-pip.py

# Unicode width, default 32. Used here and in travis_linux_steps.sh
# In docker_build_wrap.sh it is passed in when calling "docker run"
# The docker test images also use it when choosing the python to run
# with, so it is passed in when calling "docker run" for tests.
UNICODE_WIDTH=${UNICODE_WIDTH:-32}

# Default Manylinux version
MB_ML_VER=${MB_ML_VER:-2014}

if [ $(uname) == "Darwin" ]; then
  IS_MACOS=1; IS_OSX=1;
else
  # In the manylinux_2_24 image, based on Debian9, "python" is not installed
  # so link in something for the various system calls before PYTHON_EXE is set
  which python || export PATH=/opt/python/cp39-cp39/bin:$PATH
fi


# Work round bug in travis xcode image described at
# https://github.com/direnv/direnv/issues/210
shell_session_update() { :; }

# Workaround for https://github.com/travis-ci/travis-ci/issues/8703
# suggested by Thomas K at
# https://github.com/travis-ci/travis-ci/issues/8703#issuecomment-347881274
unset -f cd
unset -f pushd
unset -f popd

function start_spinner {
    if [ -n "$MB_SPINNER_PID" ]; then
        return
    fi

    >&2 echo "Building libraries..."
    # Start a process that runs as a keep-alive
    # to avoid travis quitting if there is no output
    (while true; do
        sleep 60
        >&2 echo "Still building..."
    done) &
    MB_SPINNER_PID=$!
    disown
}

function stop_spinner {
    if [ ! -n "$MB_SPINNER_PID" ]; then
        return
    fi

    kill $MB_SPINNER_PID
    unset MB_SPINNER_PID

    >&2 echo "Building libraries finished."
}

function abspath {
    # Can work with any Python; need not be our installed Python.
    python -c "import os.path; print(os.path.abspath('$1'))"
}

function relpath {
    # Path of first input relative to second (or $PWD if not specified)
    # Can work with any Python; need not be our installed Python.
    python -c "import os.path; print(os.path.relpath('$1','${2:-$PWD}'))"
}

function realpath {
    # Can work with any Python; need not be our installed Python.
    python -c "import os; print(os.path.realpath('$1'))"
}

function lex_ver {
    # Echoes dot-separated version string padded with zeros
    # Thus:
    # 3.2.1 -> 003002001
    # 3     -> 003000000
    echo $1 | awk -F "." '{printf "%03d%03d%03d", $1, $2, $3}'
}

function unlex_ver {
    # Reverses lex_ver to produce major.minor.micro
    # Thus:
    # 003002001 -> 3.2.1
    # 003000000 -> 3.0.0
    echo "$((10#${1:0:3}+0)).$((10#${1:3:3}+0)).$((10#${1:6:3}+0))"
}

function strip_ver_suffix {
    echo $(unlex_ver $(lex_ver $1))
}

function is_function {
    # Echo "true" if input argument string is a function
    # Allow errors during "set -e" blocks.
    (set +e; $(declare -Ff "$1" > /dev/null) && echo true)
}

function gh_clone {
    git clone https://github.com/$1
}

# gh-clone was renamed to gh_clone, so we have this alias for
# backwards compatibility.
alias gh-clone=gh_clone

function set_opts {
    # Set options from input options string (in $- format).
    local opts=$1
    local chars="exhmBH"
    for (( i=0; i<${#chars}; i++ )); do
        char=${chars:$i:1}
        [ -n "${opts//[^${char}]/}" ] && set -$char || set +$char
    done
}

function suppress {
    # Run a command, show output only if return code not 0.
    # Takes into account state of -e option.
    # Compare
    # https://unix.stackexchange.com/questions/256120/how-can-i-suppress-output-only-if-the-command-succeeds#256122
    # Set -e stuff agonized over in
    # https://unix.stackexchange.com/questions/296526/set-e-in-a-subshell
    local tmp=$(mktemp tmp.XXXXXXXXX) || return
    local errexit_set
    echo "Running $@"
    if [[ $- = *e* ]]; then errexit_set=true; fi
    set +e
    ( if [[ -n $errexit_set ]]; then set -e; fi; "$@"  > "$tmp" 2>&1 ) ; ret=$?
    [ "$ret" -eq 0 ] || cat "$tmp"
    rm -f "$tmp"
    if [[ -n $errexit_set ]]; then set -e; fi
    return "$ret"
}

function expect_return {
  # Run a command, succeeding (returning 0) only if the commend returns a specified code
  # Parameters
  #   retcode   expected return code (which may be zero)
  #   command   the command called
  #
  #   any further arguments are passed to the called command
  #
  # Returns 1 if called with less than 2 arguments
  (( $# < 2 )) && echo "Must have at least 2 arguments" && return 1
  local retcode=$1
  local retval
  ( "${@:2}" ) || retval=$?
  [[ $retcode == ${retval:-0} ]] && return 0
  return ${retval:-1}
}

function cmd_notexit {
    # wraps a command, capturing its return code and preventing it
    # from exiting the shell. Handles -e / +e modes.
    # Parameters
    #    cmd - command
    #    any further parameters are passed to the wrapped command
    # If called without an argument, it will exit the shell with an error
    local cmd=$1
    if [ -z "$cmd" ];then echo "no command"; exit 1; fi
    if [[ $- = *e* ]]; then errexit_set=true; fi
    set +e
    ("${@:1}") ; retval=$?
    [[ -n $errexit_set ]] && set -e
    return $retval
}

function rm_mkdir {
    # Remove directory if present, then make directory
    local path=$1
    if [ -z "$path" ]; then echo "Need not-empty path"; exit 1; fi
    if [ -d "$path" ]; then rm -rf $path; fi
    mkdir $path
}

function untar {
    local in_fname=$1
    if [ -z "$in_fname" ];then echo "in_fname not defined"; exit 1; fi
    local extension=${in_fname##*.}
    case $extension in
        tar) tar -xf $in_fname ;;
        gz|tgz) tar -zxf $in_fname ;;
        bz2) tar -jxf $in_fname ;;
        zip) unzip -qq $in_fname ;;
        xz) if [ -n "$IS_MACOS" ]; then
              tar -xf $in_fname
            else
              if [[ ! $(type -P "unxz") ]]; then
                echo xz must be installed to uncompress file; exit 1
              fi
              unxz -c $in_fname | tar -xf -
            fi ;;
        *) echo Did not recognize extension $extension; exit 1 ;;
    esac
}

function install_rsync {
    # install rsync via package manager
    if [ -n "$IS_MACOS" ]; then
        # macOS. The colon in the next line is the null command
        :
    elif [[ $MB_ML_VER == "_2_24" ]]; then
        # debian:9 based distro
        [[ $(type -P rsync) ]] || apt-get install -y rsync
    else
        # centos based distro
        [[ $(type -P rsync) ]] || yum_install rsync
    fi
}

function fetch_unpack {
    # Fetch input archive name from input URL
    # Parameters
    #    url - URL from which to fetch archive
    #    archive_fname (optional) archive name
    #
    # Echos unpacked directory and file names.
    #
    # If `archive_fname` not specified then use basename from `url`
    # If `archive_fname` already present at download location, use that instead.
    local url=$1
    if [ -z "$url" ];then echo "url not defined"; exit 1; fi
    local archive_fname=${2:-$(basename $url)}
    local arch_sdir="${ARCHIVE_SDIR:-archives}"
    if [ -z "$IS_MACOS" ]; then
        local extension=${archive_fname##*.}
        if [ "$extension" == "xz" ]; then
            ensure_xz
        fi
    fi
    # Make the archive directory in case it doesn't exist
    mkdir -p $arch_sdir
    local out_archive="${arch_sdir}/${archive_fname}"
    # If the archive is not already in the archives directory, get it.
    if [ ! -f "$out_archive" ]; then
        # Source it from multibuild archives if available.
        local our_archive="${MULTIBUILD_DIR}/archives/${archive_fname}"
        if [ -f "$our_archive" ]; then
            ln -s $our_archive $out_archive
        else
            # Otherwise download it.
            curl -L $url > $out_archive
        fi
    fi
    # Unpack archive, refreshing contents, echoing dir and file
    # names.
    rm_mkdir arch_tmp
    install_rsync
    (cd arch_tmp && \
        untar ../$out_archive && \
        ls -1d * &&
        rsync --delete -ah * ..)
}

function clean_code {
    local repo_dir=${1:-$REPO_DIR}
    local build_commit=${2:-$BUILD_COMMIT}
    [ -z "$repo_dir" ] && echo "repo_dir not defined" && exit 1
    [ -z "$build_commit" ] && echo "build_commit not defined" && exit 1
    # The package $repo_dir may be a submodule. git submodules do not
    # have a .git directory. If $repo_dir is copied around, tools like
    # Versioneer which require that it be a git repository are unable
    # to determine the version.  Give submodule proper git directory
    fill_submodule "$repo_dir"
    (cd $repo_dir \
        && git fetch origin \
        && git checkout $build_commit \
        && git clean -fxd \
        && git reset --hard \
        && git submodule update --init --recursive)
}

function build_wheel_cmd {
    # Builds wheel with named command, puts into $WHEEL_SDIR
    #
    # Parameters:
    #     cmd  (optional, default "pip_wheel_cmd"
    #        Name of command for building wheel
    #     repo_dir  (optional, default $REPO_DIR)
    #
    # Depends on
    #     REPO_DIR  (or via input argument)
    #     WHEEL_SDIR  (optional, default "wheelhouse")
    #     BUILD_DEPENDS (optional, default "")
    #     MANYLINUX_URL (optional, default "") (via pip_opts function)
    local cmd=${1:-pip_wheel_cmd}
    local repo_dir=${2:-$REPO_DIR}
    [ -z "$repo_dir" ] && echo "repo_dir not defined" && exit 1
    local wheelhouse=$(abspath ${WHEEL_SDIR:-wheelhouse})
    start_spinner
    if [ -n "$(is_function "pre_build")" ]; then pre_build; fi
    stop_spinner
    if [ -n "$BUILD_DEPENDS" ]; then
        pip install $(pip_opts) $BUILD_DEPENDS
    fi
    (cd $repo_dir && $cmd $wheelhouse)
    repair_wheelhouse $wheelhouse
}

function pip_wheel_cmd {
    local abs_wheelhouse=$1
    pip wheel $(pip_opts) -w $abs_wheelhouse --no-deps .
}

function bdist_wheel_cmd {
    # Builds wheel with bdist_wheel, puts into wheelhouse
    #
    # It may sometimes be useful to use bdist_wheel for the wheel building
    # process.  For example, versioneer has problems with versions which are
    # fixed with bdist_wheel:
    # https://github.com/warner/python-versioneer/issues/121
    local abs_wheelhouse=$1
    check_python
    $PYTHON_EXE setup.py bdist_wheel
    cp dist/*.whl $abs_wheelhouse
}

function wrap_wheel_builder {
    # Wrapper for build commands, overwritten by macOS for universal2 or arm64 wheel building
    $@
}

function build_pip_wheel {
    # Standard wheel building command with pip wheel
    wrap_wheel_builder build_wheel_cmd "pip_wheel_cmd" $@
}

function build_bdist_wheel {
    # Wheel building with bdist_wheel. See bdist_wheel_cmd
    wrap_wheel_builder build_wheel_cmd "bdist_wheel_cmd" $@
}

function build_wheel {
    # Set default building method to pip
    wrap_wheel_builder build_pip_wheel $@
}

function build_index_wheel_cmd {
    # Builds wheel from some index, usually pypi
    #
    # Parameters:
    #     project_spec
    #        requirement to install, e.g. "tornado" or "tornado==4.4.1"
    #     *args
    #        Any other arguments to be passed to pip `install`  and `wheel`
    #        commands.
    #
    # Depends on
    #     WHEEL_SDIR  (optional, default "wheelhouse")
    #     BUILD_DEPENDS (optional, default "")
    #     MANYLINUX_URL (optional, default "") (via pip_opts function)
    #
    # You can also override `pip_opts` command to set indices other than pypi
    local project_spec=$1
    [ -z "$project_spec" ] && echo "project_spec not defined" && exit 1
    # Discard first argument to pass remainder to pip
    shift
    local wheelhouse=$(abspath ${WHEEL_SDIR:-wheelhouse})
    start_spinner
    if [ -n "$(is_function "pre_build")" ]; then pre_build; fi
    stop_spinner
    if [ -n "$BUILD_DEPENDS" ]; then
        pip install $(pip_opts) $@ $BUILD_DEPENDS
    fi
    pip wheel $(pip_opts) $@ -w $wheelhouse --no-deps $project_spec
    repair_wheelhouse $wheelhouse
}

function build_index_wheel {
    wrap_wheel_builder build_index_wheel_cmd $@
}

function pip_opts {
    [ -n "$MANYLINUX_URL" ] && echo "--find-links $MANYLINUX_URL"
}

function get_os {
    # Report OS as given by uname
    # Use any Python that comes to hand.
    python -c 'import platform; print(platform.uname()[0])'
}

function get_platform {
    # Report platform as given by uname
    # Use any Python that comes to hand.
    python -c 'import platform; print(platform.uname()[4])'
}

if [ "$(get_platform)" == x86_64 ] || \
    [ "$(get_platform)" == i686 ]; then IS_X86=1; fi

function get_distutils_platform {
    # Report platform as given by distutils get_platform.
    # This is the platform tag that pip will use.
    check_python
    $PYTHON_EXE -c "import distutils.util; print(distutils.util.get_platform())"
}

function install_wheel {
    # Install test dependencies and built wheel
    #
    # Pass any input flags to pip install steps
    #
    # Depends on:
    #     WHEEL_SDIR  (optional, default "wheelhouse")
    #     TEST_DEPENDS  (optional, default "")
    #     MANYLINUX_URL (optional, default "") (via pip_opts function)
    local wheelhouse=$(abspath ${WHEEL_SDIR:-wheelhouse})
    check_pip
    if [ -n "$TEST_DEPENDS" ]; then
        while read TEST_DEPENDENCY; do
            $PIP_CMD install $(pip_opts) $@ $TEST_DEPENDENCY
        done <<< "$TEST_DEPENDS"
    fi

    check_python
    check_pip

    $PIP_CMD install packaging
    local supported_wheels=$($PYTHON_EXE $MULTIBUILD_DIR/supported_wheels.py $wheelhouse/*.whl)
    if [ -z "$supported_wheels" ]; then
        echo "ERROR: no supported wheels found"
        exit 1
    fi
    # Install compatible wheel
    $PIP_CMD install $(pip_opts) $@ $supported_wheels
}

function install_run {
    # Depends on function `run_tests` defined in `config.sh`
    install_wheel
    mkdir tmp_for_test
    (cd tmp_for_test && run_tests)
    rmdir tmp_for_test  2>/dev/null || echo "Cannot remove tmp_for_test"
}

function fill_submodule {
    # Restores .git directory to submodule, if necessary
    # See:
    # https://stackoverflow.com/questions/41776331/is-there-a-way-to-reconstruct-a-git-directory-for-a-submodule
    local repo_dir="$1"
    [ -z "$repo_dir" ] && echo "repo_dir not defined" && exit 1
    local git_loc="$repo_dir/.git"
    # For ordinary submodule, .git is a file.
    [ -d "$git_loc" ] && return
    # Need to recreate .git directory for submodule
    local origin_url=$(cd "$repo_dir" && git config --get remote.origin.url)
    local repo_copy="$repo_dir-$RANDOM"
    git clone --recursive "$repo_dir" "$repo_copy"
    rm -rf "$repo_dir"
    mv "${repo_copy}" "$repo_dir"
    (cd "$repo_dir" && git remote set-url origin $origin_url)
}

# The latest versions of PyPy.
LATEST_PP_5p0=5.0.1
LATEST_PP_5p1=5.1.1
LATEST_PP_5p3=5.3.1
LATEST_PP_5p4=5.4.1
LATEST_PP_5p6=5.6.0
LATEST_PP_5p7=5.7.1
LATEST_PP_5p8=5.8.0
LATEST_PP_5p9=5.9.0
LATEST_PP_5=$LATEST_PP_5p9

LATEST_PP_6p0=6.0.0
LATEST_PP_6=$LATEST_PP_6p0

LATEST_PP_7p0=7.0.0
LATEST_PP_7p1=7.1.1
LATEST_PP_7p2=7.2.0
LATEST_PP_7p3=7.3.3
LATEST_PP_7=$LATEST_PP_7p3

function unroll_version {
    # Convert major or major.minor format to major.minor.micro using the above
    # values recursively
    # Parameters:
    #   $prefix : one of LATEST_PP or LATEST_PP3
    #   $version : major[.minor[.patch]]
    # Hence:
    #   LATEST_PP 5 -> 5.7.0
    #   LATEST 2.7 -> 2.7.11
    local prefix=$1
    local ver=$2
    local latest=${prefix}_${ver//./p}
    if [ -n "${!latest}" ]; then
        echo $(unroll_version ${prefix} ${!latest})
    else
        echo $ver
    fi
}

function install_pypy {
    # Installs pypy.org PyPy
    # Parameter $version
    # Version given in major or major.minor or major.minor.micro e.g
    # "3" or "3.7" or "3.7.1".
    # Uses $PLAT
    # sets $PYTHON_EXE variable to python executable

    local version=$1
    case "$PLAT" in
    "x86_64")  if [ -n "$IS_MACOS" ]; then
                   suffix="osx64";
               else
                   suffix="linux64";
               fi;;
    "i686")    suffix="linux32";;
    "ppc64le") suffix="ppc64le";;
    "s390x")    suffix="s390x";;
    "aarch64")  suffix="aarch64";;
    *) echo unknown platform "$PLAT"; exit 1;;
    esac

    # Need to convert pypy-7.2 to pypy2.7-v7.2.0 and pypy3.6-7.3 to pypy3.6-v7.3.0
    local prefix=$(get_pypy_build_prefix $version)
    # since prefix is pypy3.6v7.2 or pypy2.7v7.2, grab the 4th (0-index) letter
    local major=${prefix:4:1}
    # get the pypy version 7.2.0
    local py_version=$(fill_pypy_ver $(echo $version | cut -f2 -d-))

    local py_build=$prefix$py_version-$suffix
    local py_zip=$py_build.tar.bz2
    local zip_path=$DOWNLOADS_SDIR/$py_zip
    mkdir -p $DOWNLOADS_SDIR
    wget -nv $PYPY_URL/${py_zip} -P $DOWNLOADS_SDIR
    untar $zip_path
    # bug/feature: pypy package for pypy3 only has bin/pypy3 :(
    if [ "$major" == "3" ] && [ ! -x "$py_build/bin/pypy" ]; then
        ln $py_build/bin/pypy3 $py_build/bin/pypy
    fi
    PYTHON_EXE=$(realpath $py_build/bin/pypy)
    $PYTHON_EXE -mensurepip
    $PYTHON_EXE -mpip install --upgrade pip setuptools wheel
    if [ "$major" == "3" ] && [ ! -x "$py_build/bin/pip" ]; then
        ln $py_build/bin/pip3 $py_build/bin/pip
    fi
    PIP_CMD=pip
}

function fill_pypy_ver {
    # Convert major or major.minor format to major.minor.micro
    # Parameters:
    #   $version : major[.minor[.patch]]
    # Hence:
    #   5 -> 5.7.0
    echo $(unroll_version LATEST_PP $1)
}

function get_pypy_build_prefix {
    # Return the file prefix of a PyPy file
    # Parameters:
    #   $version : pypy version number, for example pypy-7.2 or pypy3.6-7.2
    local version=$1
    if [[ $version =~ pypy([0-9]+)\.([0-9]+)-([0-9]+)\.([0-9]+) ]]; then
        local py_major=${BASH_REMATCH[1]}
        local py_minor=${BASH_REMATCH[2]}
        echo "pypy$py_major.$py_minor-v"
    elif [[ $version =~ ([0-9]+)\.([0-9]+) ]]; then
        local major=${BASH_REMATCH[1]}
        local minor=${BASH_REMATCH[2]}
        if (( $major > 6 )); then
            echo "pypy2.7-v"
        elif (( $major > 5 || ($major == 5 && $minor >= 3) )); then
            echo "pypy2-v"
        else
            echo "pypy-"
        fi
    else
        echo "error: expected version like pypy-7.2 or pypy3.6-7.2, got $1" 1>&2
        exit 1
    fi
}

retry () {
    # Retry command (with arguments) up to 5 times
    # https://gist.github.com/fungusakafungus/1026804
    local retry_max=5
    local count=$retry_max
    while [ $count -gt 0 ]; do
        "$@" && break
        count=$(($count - 1))
        sleep 1
    done

    [ $count -eq 0 ] && {
        echo "Retry failed [$retry_max]: $@" >&2
        return 1
    }
    return 0
}

function install_pip {
    # Generic install pip
    echo "Deprecated - please see pip installs within the individual"
    echo "install functions for each Python type."
    echo "Multibuild itself no longer uses this function."
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
    $PYTHON_EXE $get_pip_path --ignore-installed $pip_args
    PIP_CMD=$(dirname $PYTHON_EXE)/pip$py_mm
    if [ "$USER" != "root" ]; then
        # inside a docker, there is no sudo but the user is already root
        PIP_CMD="sudo $PIP_CMD"
    fi
    # Append pip_args if present (avoiding trailing space cf using variable
    # above).
    if [ -n "$pip_args" ]; then
        PIP_CMD="$PIP_CMD $pip_args"
    fi
}

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

function get_py_mm {
    check_python
    $PYTHON_EXE -c "import sys; print('{0}.{1}'.format(*sys.version_info[0:2]))"
}

function cpython_path {
    # Return path to cpython given
    # * version (of form "2.7")
    # * u_width ("16" or "32" default "32")
    #
    # For back-compatibility "u" as u_width also means "32"
    local py_ver="${1:-2.7}"
    local abi_suff=m
    local u_width="${2:-${UNICODE_WIDTH}}"
    local u_suff=u
    # Python 3.8 and up no longer uses the PYMALLOC 'm' suffix
    # https://github.com/pypa/wheel/pull/303
    if [ $(lex_ver $py_ver) -ge $(lex_ver 3.8) ]; then
        abi_suff=""
    fi
    # Back-compatibility
    if [ "$u_width" == "u" ]; then u_width=32; fi
    # For Python >= 3.4, "u" suffix not meaningful
    if [ $(lex_ver $py_ver) -ge $(lex_ver 3.4) ] ||
        [ "$u_width" == "16" ]; then
        u_suff=""
    elif [ "$u_width" == "" ]; then
        u_width="32"
    elif [ "$u_width" != "32" ]; then
        echo "Incorrect u_width value $u_width"
        exit 1
    fi
    local no_dots=$(echo $py_ver | tr -d .)
    echo "/opt/python/cp${no_dots}-cp${no_dots}$abi_suff${u_suff}"
}
