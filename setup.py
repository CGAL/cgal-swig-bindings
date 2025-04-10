import os
import pathlib
import sys
import shutil
import subprocess
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as build_ext_orig
from wheel.bdist_wheel import bdist_wheel

# Define dependencies
DEPENDENCIES = [
    'gmp', 'mpfr', 'boost_serialization', 'boost_iostreams', 'boost_zlib',
    'boost_bzip2', 'tbb', 'tbbmalloc', 'zlib', 'boost_regex'
]

# Define CGAL modules
CGAL_MODULES = [
    'Box_intersection_d', 'Convex_hull_2', 'Convex_hull_3', 'Classification',
    'HalfedgeDS', 'Interpolation', 'Mesh_2', 'Point_set_3',
    'Point_set_processing_3', 'Polygon_mesh_processing', 'Polyhedron_3',
    'Polyline_simplification_2', 'Shape_detection', 'Spatial_searching',
    'Voronoi_diagram_2', 'AABB_tree', 'Advancing_front_surface_reconstruction',
    'Alpha_shape_2', 'Kernel', 'Mesh_3', 'Surface_mesher', 'Triangulation_2',
    'Triangulation_3', 'Alpha_wrap_3'
]

# Create extensions
extensions = [
    Extension(f'CGAL._CGAL_{mod_name}', sources=[]) for mod_name in CGAL_MODULES
]

class BuildExt(build_ext_orig):
    def run(self):
        cwd = pathlib.Path(__file__).parent.absolute()  # Ensure the correct path to CMakeLists.txt
        build_temp = pathlib.Path("build")
        build_temp.mkdir(parents=True, exist_ok=True)

        # Copy CMakeLists.txt to the build directory if needed
        cmake_file = cwd / "CMakeLists.txt"
        if cmake_file.exists():
            shutil.copy(cmake_file, build_temp / "CMakeLists.txt")

        cmake_args = [
            '-DBUILD_JAVA=OFF',
            '-DBUILD_PYTHON=ON',
            '-DCMAKE_BUILD_TYPE=Release',
            f'-DPython_EXECUTABLE={sys.executable}'
        ]

        os.chdir(str(build_temp))
        self.spawn(['cmake', str(cwd)] + cmake_args)
        self.spawn(['cmake', '--build', '.', '--', f'-j{os.cpu_count()}'])
        os.chdir(str(cwd))

def get_cgal_version():
    try:
        result = subprocess.run(
            ['cmake', '-DGET_CGAL_VERSION=ON''-S', '.', '-B', 'build-temp'],
            capture_output=True, text=True, check=True
        )
        for line in result.stdout.splitlines():
            if 'CGAL version:' in line:
                return line.split(':')[1].strip()
    except subprocess.CalledProcessError as e:
        print(f"Error running cmake: {e}")
    except FileNotFoundError:
        print("CMake not found. Please ensure it is installed and available in the PATH.")
    return '0.0.0'  # Default to a valid version string if extraction fails

setup(
    name='cgal',
    version=get_cgal_version(),  # Dynamically fetch CGAL version
    author="CGAL Project",
    description="CGAL bindings for Python.",
    long_description="""
        The CGAL Bindings project allows the use of some packages of CGAL, the
        Computational Geometry Algorithms Library, with Python. This project is
        experimental, and more packages will be added over time.
        For more information, visit https://github.com/CGAL/cgal-swig-bindings/wiki.
    """,
    long_description_content_type="text/markdown",
    url="https://github.com/CGAL/cgal-swig-bindings",
    packages=['CGAL'],
    package_dir={'CGAL': '.'},
    package_data={'CGAL': ['*.dll']},
    cmdclass={
        'build_ext': BuildExt,
        'bdist_wheel': bdist_wheel,
    },
    ext_modules=extensions,
)
