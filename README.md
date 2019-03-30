[![Build Status](https://travis-ci.org/CGAL/cgal-swig-bindings.svg?branch=master)](https://travis-ci.org/CGAL/cgal-swig-bindings)

# cgal-bindings
CGAL bindings using SWIG

For details, refer to the [wiki](https://github.com/CGAL/cgal-swig-bindings/wiki).

# install python binding with *setup.py*

1. Install the cgal-swig-bindings refer to [installation](https://github.com/CGAL/cgal-swig-bindings/wiki/Installation). A python installation process is shown below, the installation directory is set to *[cgal-swig-bindings_root/pycgal/src/]*.

    ```
    git clone https://github.com/chengaoyu/cgal-swig-bindings
    cd cgal-swig-bindings
    mkdir bukid/CGAL -p
    cd build/CGAL
    cmake -DCGAL_DIR=/usr/lib/CGAL -DBUILD_JAVA=OFF -DPYTHON_OUTDIR_PREFIX=../../pycgal/src
    make -j N ### where N is the number of your computation cores.  
    ```

2. Install the python binding library with *setup.py*. We have the pycgal library and a *setup.py*. We then install pycgal so that it can be import elsewhere.
   
    ```
    cd ../../pycgal
    python setup.py install
    ```
    
3. Validate the installation.
    ```
    cd ../examples
    python test.py
    ```
   If you see the output like:
    ```
    OK
    list does not contains only points
    Not a list
    2 2 2
    441 41 84
    1 1 1
    1 1 8
    length of all_adjacent_vertices  12
    Not a list
    0 1 1 0
    ```
   Congratulations! You have just installed the python binding of CGAL.