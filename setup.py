
import setuptools
from setuptools import setup
from distutils.extension import Extension
import os
from os.path import join


def touch(fname, times=None):
    with open(fname, 'a'):
        os.utime(fname, times)

OUT_DIR = 'build-python'

PACKAGE_DIR = os.path.join(OUT_DIR,"CGAL")

#Create the package directory structure if it doesn't already exist
#The existing Cmake install might already have made it
if not os.path.exists(PACKAGE_DIR):
    os.makedirs(PACKAGE_DIR)

initpy = os.path.join(PACKAGE_DIR, "__init__.py")
if not os.path.exists(initpy):
    touch(initpy)


kernel = Extension("_CGAL_Kernel",
                   sources=["SWIG_CGAL/Kernel/CGAL_Kernel.i"],
                   swig_opts=["-c++"],
                   include_dirs=['./'])



setup(
    name="cgal-bindings",
    description="Bindings so you can use certain CGAL classes in Python",
    packages=['CGAL'],
    ext_package='CGAL',
    ext_modules = [kernel],
    package_dir = {'': 'build-python'}
)


