
import setuptools
from setuptools import setup
from distutils.extension import Extension

kernel = Extension("CGAL_Kernel",sources=["SWIG_CGAL/Kernel/CGAL_Kernel.i"])


setup(
    name="cgal-bindings",
    description="Bindings so you can use certain CGAL classes in Python",
    ext_package = "CGAL",
    ext_modules = [kernel]
)


