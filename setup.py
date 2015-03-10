
import setuptools
from setuptools import setup
from distutils.extension import Extension
import os
import os.path
import sys
from ctypes.util import find_library    # Useful function for findings libs (cross platform too)
import distutils.sysconfig
import distutils.ccompiler
import re

def touch(fname, times=None):
    with open(fname, 'a'):
        os.utime(fname, times)



# Find all the header and library paths
# At least the ones relevant to CGAL
def get_all_paths():
    def path_split(path_string):
        if os.name=='nt':
            sep = ';'
        else:
            sep = ':'
        return path_string.split(sep)

    def environ_path(environ_var):
        if environ_var in os.environ:
            return path_split(os.environ[environ_var])
        else:
            return []

    header_paths, library_paths = [], []
    compiler = distutils.ccompiler.new_compiler()
    distutils.sysconfig.customize_compiler(compiler)

    # Only UnixCompiler has this attribute at the moment
    # It contains all the arguments passed to the compiler, some of which are paths
    if hasattr(compiler,'compiler_so'):
        for arg_or_path in compiler.compiler_so:
            if arg_or_path.startswith("-I/"):
                header_paths.append(arg_or_path[2:])
            if arg_or_path.startswith("-L/"):
                library_paths.append(arg_or_path[2:])
    if os.name=='nt':
        # Our only hope is that they've set the %CGAL_DIR% var
        # The cgal installer does this
        cgal_dir = os.environ.get("CGAL_DIR")
        if cgal_dir is not None:
            header_paths.append(os.path.join(cgal_dir, "include"))
            library_paths.append(os.path.join(cgal_dir, "lib"))
            library_paths.append(os.path.join(cgal_dir, "bin"))
    else:
        for hvar in ['CPATH',
                    'C_INCLUDE_PATH',
                    'CPLUS_INCLUDE_PATH']:
            header_paths += environ_path(hvar)
        for lvar in ['LD_LIBRARY_PATH',
                     'LIBRARY_PATH']:
            library_paths += environ_path(lvar)
        header_paths.append("/usr/include")         # Will be filtered out on Windows
        header_paths.append("/usr/local/include")
        library_paths.append("/usr/lib")
        library_paths.append("/usr/lib64")
        library_paths.append("/usr/local/lib")
        library_paths.append("/usr/local/lib64")
    header_paths = filter(os.path.isdir, header_paths)
    library_paths = filter(os.path.isdir, library_paths)
    return list(set(header_paths)), list(set(library_paths))      #uniquify


# Find a file inside the header/library search paths
# Case insensitive
def find_in_paths(search_paths, search):
    for path in search_paths:
        for file in os.listdir(path):
            if file.lower() == search.lower():
                return os.path.join(path, file)
    return None



# This is the directory where the CMake build puts everything by default
OUT_DIR = os.path.abspath('build-python')

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
    "Point_set_processing_3",       # needs eigen3
    "Polyhedron_3",
    "Spatial_searching",
    "Surface_mesher",               # needs imageio components (CGAL was built with imageio)
    "Triangulation_2",
    "Triangulation_3",
    "Voronoi_diagram_2"
]


INCLUDE_DIRS = ["./","SWIG_CGAL/AABB_tree/include"]
MACROS = ['CGAL_USE_GMP', 'CGAL_USE_MPFR', 'CGAL_USE_ZLIB']
MACROS = [(s, None) for s in MACROS]
HEADER_PATHS, LIBRARY_PATHS = get_all_paths()
CGAL_HEADER_PATH  = find_in_paths(HEADER_PATHS, 'cgal')

if find_library('cgal') is None and CGAL_HEADER_PATH is None:
    sys.exit("You don't appear to have cgal installed")

#Make some guesses as to where that CGALConfig.make file is
CGAL_CONFIG_SEARCH = [
    os.environ.get("CGAL_DIR", ""),
    find_in_paths(LIBRARY_PATHS, 'cgal') or ""
]
CGAL_CONFIG_SEARCH = filter(os.path.isdir, CGAL_CONFIG_SEARCH)
CGAL_CONFIG_SEARCH += HEADER_PATHS


# Use CGALConfig.make to see if it was build with imageio
WITH_IMAGEIO = False
cgal_config = find_in_paths(CGAL_CONFIG_SEARCH, "CGALConfig.cmake")
if cgal_config is not None and os.path.isfile(cgal_config):
    file = open(cgal_config)
    for line in file:
        if line.replace(" ","").replace('"',' ').lower().startswith('set(with_cgal_imageio on'):
            WITH_IMAGEIO = True
            print "Found image IO"
            break

if not WITH_IMAGEIO:
    sys.stderr.write("ImageIO is not installed, skipping Surface_mesher\n")
    CGAL_modules.remove("Surface_mesher")


EIGEN3_PATH = find_in_paths(HEADER_PATHS, 'eigen3')
if EIGEN3_PATH is None:
    sys.stderr.write("No Eigen3 found, skipping Point_set_processing_3\n")
    CGAL_modules.remove("Point_set_processing_3")
else:
    # It is possible that they've installed Eigen3 but didn't build it into CGAL
    # In that case...no idea
    INCLUDE_DIRS.append(EIGEN3_PATH)
    MACROS.append(('CGAL_EIGEN3_ENABLED', None))


# compiler = distutils.ccompiler.new_compiler()
# distutils.sysconfig.customize_compiler(compiler)
# print compiler.compiler_so
# sys.exit()

# Translate the names of folders into actual Extension instances
extensions = []
for mod_name in CGAL_modules:
    # if mod_name=="AABB_tree":   # This one has its own include directory
    #     include_dirs.append("SWIG_CGAL/AABB_tree/include")
    macros = MACROS[:]
    macros.append(("_CGAL_{0}_EXPORTS".format(mod_name), None))
    e = Extension("_CGAL_" + mod_name,
                  sources=["SWIG_CGAL/{0}/CGAL_{0}.i".format(mod_name)],
                  swig_opts=["-c++","-outdir",PACKAGE_DIR],
                  define_macros=macros,
                  include_dirs=INCLUDE_DIRS,
                  extra_compile_args=["-fPIC"])

    extensions.append(e)


setup(
    name="cgal-bindings",
    description="Bindings so you can use certain CGAL classes in Python",
    packages=['CGAL'],
    ext_package='CGAL',
    ext_modules = extensions,
    package_dir = {'': 'build-python'}
)

