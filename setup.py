import sys
import os
import subprocess
from skbuild_conan import setup

# Define CGAL modules
CGAL_MODULES = [
    'AABB_tree', 'Advancing_front_surface_reconstruction', 'Alpha_shape_2',
    'Alpha_wrap_3', 'Box_intersection_d', 'Classification', 'Convex_hull_2',
    'Convex_hull_3', 'HalfedgeDS', 'Interpolation', 'Kernel', 'Mesh_2',
    'Mesh_3', 'Point_set_3', 'Point_set_processing_3',
    'Polygon_mesh_processing', 'Polyhedron_3', 'Polyline_simplification_2',
    'Shape_detection', 'Spatial_searching', 'Surface_mesher',
    'Triangulation_2', 'Triangulation_3', 'Voronoi_diagram_2'
]

def get_cgal_version():
    try:
        result = subprocess.run(
            ['cmake', '-DGET_CGAL_VERSION=ON', '-S', '.', '-B', 'build-temp'],
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


os.environ['CMAKE_POLICY_VERSION_MINIMUM'] = '3.10'
os.environ['CFLAGS'] = '-std=gnu17'
os.environ['CXXFLAGS'] = '-std=gnu++17'

setup(
    name='cgal',
    version=os.environ.get('CGAL_PYTHON_MODULE_VERSION') or get_cgal_version(),
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
    conan_requirements=["cmake/[>=3.12 <4]"] + (["gmp/[>=6.3]", "mpfr/[>=4.2]"] if os.environ.get(
        'CGAL_PYTHON_MODULE_VERSION') else ["cgal/[>=6.0 <7.0]"]),
    packages=['CGAL'] + [f'CGAL.CGAL_{m}' for m in CGAL_MODULES],
    package_dir=(
        {'CGAL': 'SWIG_CGAL/files'} |
        {f'CGAL.CGAL_{m}': f'SWIG_CGAL/{m}' for m in CGAL_MODULES}
    ),
    include_package_data=True,
    python_requires='>=3.9',
    cmake_args=[
        '-DBUILD_JAVA=OFF',
        '-DBUILD_PYTHON=ON',
        '-DCMAKE_BUILD_TYPE=Release',
        f'-DPython_EXECUTABLE={sys.executable}'
    ],
)
