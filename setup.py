
import setuptools
from setuptools import setup
from distutils.extension import Extension
import os
import sys
from os.path import join
from ctypes.util import find_library    # Useful function for findings libs (cross platform too)


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

# The subdirectories in SWIG_CGAL which contain swig interface files
CGAL_modules = [
    "AABB_tree",
    "Alpha_shape_2",
    "Box_intersection_d",
    "Convex_hull_2",
    "HalfedgeDS",
    "Interpolation",
    "Kernel",
    "Mesh_2",
    "Mesh_3",
    "Point_set_processing_3",
    "Polyhedron_3",
    "Spatial_searching",
    "Surface_mesher",
    "Triangulation_2",
    "Triangulation_3",
    "Voronoi_diagram_2"
]

if find_library('cgal') is None:
    sys.exit("You don't appear to have cgal installed")

if find_library('imageio') is None:
    sys.stderr.write("ImageIO is not installed, skipping Surface_mesher")
    CGAL_modules.remove("Surface_mesher")



# Translate the names of folders into actual Extension instances
extensions = []
for mod_name in CGAL_modules:
    include_dirs = ["./"]
    if mod_name=="AABB_tree":   # This one has its own include directory
        include_dirs.append("SWIG_CGAL/{0}/include".format(mod_name))
    e = Extension("_" + mod_name,
                  sources=["SWIG_CGAL/{0}/CGAL_{0}.i".format(mod_name)],
                  swig_opts=["-c++"],
                  include_dirs=include_dirs)

    extensions.append(e)


setup(
    name="cgal-bindings",
    description="Bindings so you can use certain CGAL classes in Python",
    packages=['CGAL'],
    ext_package='CGAL',
    ext_modules = extensions,
    package_dir = {'': 'build-python'}
)

