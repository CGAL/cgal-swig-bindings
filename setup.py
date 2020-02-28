import os
import pathlib
import glob
import shutil

import sys
from distutils.core import setup

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as build_ext_orig
from distutils.command.build_py import build_py as build_py_orig
from setuptools.command.install import install
from distutils.command.build import build
from wheel.bdist_wheel import bdist_wheel



dependencies_list = ['gmp', 'mpfr', 'boost_serialization', 'boost_iostreams', 'boost_zlib', 'boost_bzip2', 'tbb.dll', 'tbbmalloc', 'las.dll', 'zlib.dll', 'boost_regex']

#find all dependencies dll in the PATH and put them in a map {dll file : full path to dll path}
if sys.platform == 'win32'or sys.platform == 'cygwin':
  env_path_content = os.getenv('PATH')
  all_dll = {}
  for p in env_path_content.split(";"):
    p_rep=p.replace("\"","")
    files=[]
    if os.path.isdir(p_rep):
      files=os.listdir(p_rep)
    for f in files:
      if '.dll' in f:
        #truncate f:
        for dep in dependencies_list:
          if dep in f:
            all_dll[f] = p_rep+"\\"+f
  print(all_dll)
            
class BuildWheelCommand(bdist_wheel):

  user_options = bdist_wheel.user_options + [
      ('cgal-dir=', None, 'Specify the path to the CGAL installation directory.'),
      ('boost-dir=', None, 'Specify the path to the Boost include directory.'),
      ('boost-serialization-lib=', None, 'Specify the path to the Boost Serialization library file.'),
      ('boost-iostreams-lib=', None, 'Specify the path to the Boost IOStreams library file.'),
      ('boost-serialization-include-dir=', None, 'Specify the path to the Boost Serialization include directory.'),
      ('boost-iostreams-include-dir=', None, 'Specify the path to the Boost IOStreams include directory.'),
      ('boost-regex-lib=', None, 'Specify the path to the Boost Regex library file.'),
      ('laslib-include-dir=', None, 'Specify the path to the Laslib incude directory.'),
      ('laslib-lib=', None, 'Specify the path to the Laslib library file.'),
      ('tbb-include-dir=', None, 'Specify the path to the TBB include directory.'),
      ('tbb-lib=', None, 'Specify the path to the TBB library file.'),
      ('tbb-malloc-include-dir=', None, 'Specify the path to the TBB malloc include directory.'),
      ('tbb-malloc-lib=', None, 'Specify the path to the TBB malloc library file.'),
      ('installation-prefix=', None, 'Specify the path to the directory where the CGAL libraries will be installed.'),
      ('eigen3-dir=', None, 'Specify the path to the Eigen 3 incude directory.'),
      ('gmp-include-dir=', None, 'Specify the path to the gmp incude directory.'),
      ('gmp-lib=', None, 'Specify the path to the gmp library file.'),
      ('mpfr-include-dir=', None, 'Specify the path to the mpfr incude directory.'),
      ('mpfr-lib=', None, 'Specify the path to the mpfr library file.'),
      ('zlib-include-dir=', None, 'Specify the path to the zlib incude directory.'),
      ('zlib-lib=', None, 'Specify the path to the zlib library file.'),
      ('cmake-prefix-path=', None, 'Specify the path to a directory that can be used as CMAKE_PREFIX_PATH, that would contain all headers and libraries. '),
      ('generator=', None, 'The generator to use for cmake.'),
      ('cmake=', None, 'Specify the path to the cmake executable.')
      ]

  def initialize_options(self):
      bdist_wheel.initialize_options(self)
      self.cgal_dir= None
      self.boost_dir= None
      self.tbb_include_dir= None
      self.tbb_lib= None
      self.tbb_malloc_include_dir= None
      self.tbb_malloc_lib= None
      self.installation_prefix= None
      self.boost_serialization_lib= None
      self.boost_iostreams_lib= None
      self.boost_regex_lib= None
      self.boost_serialization_include_dir= None
      self.boost_iostreams_include_dir= None
      self.laslib_include_dir= None
      self.laslib_lib= None
      self.eigen3_dir= None
      self.gmp_include_dir= None
      self.gmp_lib= None
      self.mpfr_include_dir= None
      self.mpfr_lib= None
      self.zlib_include_dir= None
      self.zlib_lib= None
      self.cmake_prefix_path= None
      self.generator= None
      self.cmake= None


class InstallCommand(install):
    user_options = install.user_options + [
      ('cgal-dir=', None, 'Specify the path to the CGAL installation directory.'),
      ('boost-dir=', None, 'Specify the path to the Boost include directory.'),
      ('boost-serialization-lib=', None, 'Specify the path to the Boost Serialization library file.'),
      ('boost-iostreams-lib=', None, 'Specify the path to the Boost IOStreams library file.'),
      ('boost-regex-lib=', None, 'Specify the path to the Boost Regex library file.'),
      ('boost-serialization-include-dir=', None, 'Specify the path to the Boost Serialization include directory.'),
      ('boost-iostreams-include-dir=', None, 'Specify the path to the Boost IOStreams include directory.'),
      ('laslib-include-dir=', None, 'Specify the path to the Laslib incude directory.'),
      ('laslib-lib=', None, 'Specify the path to the Laslib library file.'),
      ('tbb-include-dir=', None, 'Specify the path to the TBB include directory.'),
      ('tbb-lib=', None, 'Specify the path to the TBB library directory.'),
      ('tbb-malloc-include-dir=', None, 'Specify the path to the TBB malloc include directory.'),
      ('tbb-malloc-lib-dir=', None, 'Specify the path to the TBB malloc library directory.'),
      ('installation-prefix=', None, 'Specify the path to the directory where the CGAL libraries will be installed.'),
      ('eigen3-dir=', None, 'Specify the path to the Eigen 3 incude directory.'),
      ('gmp-include-dir=', None, 'Specify the path to the gmp incude directory.'),
      ('gmp-lib=', None, 'Specify the path to the gmp library file.'),
      ('mpfr-include-dir=', None, 'Specify the path to the mpfr incude directory.'),
      ('mpfr-lib=', None, 'Specify the path to the mpfr library file.'),
      ('zlib-include-dir=', None, 'Specify the path to the zlib incude directory.'),
      ('zlib-lib=', None, 'Specify the path to the zlib library file.'),
      ('cmake-prefix-path=', None, 'Specify the path to a directory that can be used as CMAKE_PREFIX_PATH, that would contain all headers and libraries. '),
      ('generator=', None, 'The generator to use for cmake.'),
      ('cmake=', None, 'Specify the path to the cmake executable.')
      ]

    def initialize_options(self):
      install.initialize_options(self)
      self.cgal_dir= None
      self.boost_dir= None
      self.tbb_include_dir= None
      self.tbb_lib= None
      self.tbb_malloc_include_dir= None
      self.tbb_malloc_lib= None
      self.installation_prefix= None
      self.boost_serialization_lib= None
      self.boost_iostreams_lib= None
      self.boost_regex_lib= None
      self.boost_serialization_include_dir= None
      self.boost_iostreams_include_dir= None
      self.laslib_include_dir= None
      self.laslib_lib= None
      self.eigen3_dir= None
      self.gmp_include_dir= None
      self.gmp_lib= None
      self.mpfr_include_dir= None
      self.mpfr_lib= None
      self.zlib_include_dir= None
      self.zlib_lib= None
      self.cmake_prefix_path= None
      self.generator= None
      self.cmake= None


class BuildCommand(build):
    user_options = build.user_options + [
      ('cgal-dir=', None, 'Specify the path to the CGAL installation directory.'),
      ('boost-dir=', None, 'Specify the path to the Boost include directory.'),
      ('boost-serialization-lib=', None, 'Specify the path to the Boost Serialization library file.'),
      ('boost-iostreams-lib=', None, 'Specify the path to the Boost IOStreams library file.'),
      ('boost-regex-lib=', None, 'Specify the path to the Boost Regex library file.'),
      ('boost-serialization-include-dir=', None, 'Specify the path to the Boost Serialization include directory.'),
      ('boost-iostreams-include-dir=', None, 'Specify the path to the Boost IOStreams include directory.'),
      ('laslib-include-dir=', None, 'Specify the path to the Laslib incude directory.'),
      ('laslib-lib=', None, 'Specify the path to the Laslib library file.'),
      ('tbb-include-dir=', None, 'Specify the path to the TBB include directory.'),
      ('tbb-lib=', None, 'Specify the path to the TBB library directory.'),
      ('tbb-malloc-include-dir=', None, 'Specify the path to the TBB malloc include directory.'),
      ('tbb-malloc-lib-dir=', None, 'Specify the path to the TBB malloc library directory.'),
      ('installation-prefix=', None, 'Specify the path to the directory where the CGAL libraries will be installed.'),
      ('eigen3-dir=', None, 'Specify the path to the Eigen 3 incude directory.'),
      ('gmp-include-dir=', None, 'Specify the path to the gmp incude directory.'),
      ('gmp-lib=', None, 'Specify the path to the gmp library file.'),
      ('mpfr-include-dir=', None, 'Specify the path to the mpfr incude directory.'),
      ('mpfr-lib=', None, 'Specify the path to the mpfr library file.'),
      ('zlib-include-dir=', None, 'Specify the path to the zlib incude directory.'),
      ('zlib-lib=', None, 'Specify the path to the zlib library file.'),
      ('cmake-prefix-path=', None, 'Specify the path to a directory that can be used as CMAKE_PREFIX_PATH, that would contain all headers and libraries. '),
      ('generator=', None, 'The generator to use for cmake.'),
      ('cmake=', None, 'Specify the path to the cmake executable.')
      ]
    
    def initialize_options(self):
      build.initialize_options(self)
      self.cgal_dir= None
      self.boost_dir= None
      self.tbb_include_dir= None
      self.tbb_lib= None
      self.tbb_malloc_include_dir= None
      self.tbb_malloc_lib= None
      self.installation_prefix= None
      self.boost_serialization_lib= None
      self.boost_iostreams_lib= None
      self.boost_regex_lib= None
      self.boost_serialization_include_dir= None
      self.boost_iostreams_include_dir= None
      self.laslib_include_dir= None
      self.laslib_lib= None
      self.eigen3_dir= None
      self.gmp_include_dir= None
      self.gmp_lib= None
      self.mpfr_include_dir= None
      self.mpfr_lib= None
      self.zlib_include_dir= None
      self.zlib_lib= None
      self.cmake_prefix_path= None
      self.generator= None
      self.cmake= None

    def finalize_options(self):
        build.finalize_options(self)
        self.set_undefined_options('install', ('cgal_dir', 'cgal_dir'),
                                   ('boost_dir', 'boost_dir'),
                                   ('tbb_include_dir','tbb_include_dir'),
                                   ('tbb_lib','tbb_lib'),
                                   ('tbb_malloc_include_dir','tbb_malloc_include_dir'),
                                   ('tbb_malloc_lib','tbb_malloc_lib'),
                                   ('installation_prefix', 'installation_prefix'),
                                   ('boost_serialization_lib', 'boost_serialization_lib'),
                                   ('boost_iostreams_lib', 'boost_iostreams_lib'),
                                   ('boost_regex_lib', 'boost_regex_lib'),
                                   ('boost_serialization_include_dir', 'boost_serialization_include_dir'),
                                   ('boost_iostreams_include_dir', 'boost_iostreams_include_dir'),
                                   ('laslib_include_dir', 'laslib_include_dir'),
                                   ('laslib_lib', 'laslib_lib'),
                                   ('eigen3_dir', 'eigen3_dir'),
                                   ('gmp_include_dir', 'gmp_include_dir'),
                                   ('gmp_lib', 'gmp_lib'),
                                   ('mpfr_include_dir', 'mpfr_include_dir'),
                                   ('mpfr_lib', 'mpfr_lib'),
                                   ('zlib_include_dir','zlib_include_dir'),
                                   ('zlib_lib', 'zlib_lib'),
                                   ('cmake_prefix_path','cmake_prefix_path'),
                                   ('generator', 'generator'),
                                   ('cmake', 'cmake')
                                   )
        self.set_undefined_options('bdist_wheel', ('cgal_dir', 'cgal_dir'),
                                   ('boost_dir', 'boost_dir'),
                                   ('tbb_include_dir','tbb_include_dir'),
                                   ('tbb_lib','tbb_lib'),
                                   ('tbb_malloc_include_dir','tbb_malloc_include_dir'),
                                   ('tbb_malloc_lib','tbb_malloc_lib'),
                                   ('installation_prefix', 'installation_prefix'),
                                   ('boost_serialization_lib', 'boost_serialization_lib'),
                                   ('boost_iostreams_lib', 'boost_iostreams_lib'),
                                   ('boost_regex_lib', 'boost_regex_lib'),
                                   ('boost_serialization_include_dir', 'boost_serialization_include_dir'),
                                   ('boost_iostreams_include_dir', 'boost_iostreams_include_dir'),
                                   ('laslib_include_dir', 'laslib_include_dir'),
                                   ('laslib_lib', 'laslib_lib'),
                                   ('eigen3_dir', 'eigen3_dir'),
                                   ('gmp_include_dir', 'gmp_include_dir'),
                                   ('gmp_lib', 'gmp_lib'),
                                   ('mpfr_include_dir', 'mpfr_include_dir'),
                                   ('mpfr_lib', 'mpfr_lib'),
                                   ('zlib_include_dir','zlib_include_dir'),
                                   ('zlib_lib', 'zlib_lib'),
                                   ('cmake_prefix_path','cmake_prefix_path'),
                                   ('generator', 'generator'),
                                   ('cmake', 'cmake')
                                   )
    def set_undefined_options(self, src_cmd, *option_pairs):
       src_cmd_obj = self.distribution.get_command_obj(src_cmd)
      # Remove "src_cmd_obj.ensure_finalized()" to keep from calling install.finalize_options()
      # several times, as it will fail the second time.
       for (src_option, dst_option) in option_pairs:
         if getattr(self, dst_option) is None:
             setattr(self, dst_option, getattr(src_cmd_obj, src_option))


class build_py(build_py_orig):

    user_options = build_py_orig.user_options + [
      ('cgal-dir=', None, 'Specify the path to the CGAL installation directory.'),
      ('boost-dir=', None, 'Specify the path to the Boost include directory.'),
      ('boost-serialization-lib=', None, 'Specify the path to the Boost Serialization library file.'),
      ('boost-iostreams-lib=', None, 'Specify the path to the Boost IOStreams library file.'),
      ('boost-regex-lib=', None, 'Specify the path to the Boost Regex library file.'),
      ('boost-serialization-include-dir=', None, 'Specify the path to the Boost Serialization include directory.'),
      ('boost-iostreams-include-dir=', None, 'Specify the path to the Boost IOStreams include directory.'),
      ('laslib-include-dir=', None, 'Specify the path to the Laslib incude directory.'),
      ('laslib-lib=', None, 'Specify the path to the Laslib library file.'),
      ('tbb-include-dir=', None, 'Specify the path to the TBB include directory.'),
      ('tbb-lib=', None, 'Specify the path to the TBB library directory.'),
      ('tbb-malloc-include-dir=', None, 'Specify the path to the TBB malloc include directory.'),
      ('tbb-malloc-lib-dir=', None, 'Specify the path to the TBB malloc library directory.'),
      ('installation-prefix', None, 'Specify the path to the directory where the CGAL libraries will be installed.'),
      ('eigen3-dir', None, 'Specify the path to the Eigen 3 incude directory.'),
      ('gmp-include-dir=', None, 'Specify the path to the gmp incude directory.'),
      ('gmp-lib=', None, 'Specify the path to the gmp library file.'),
      ('mpfr-include-dir=', None, 'Specify the path to the mpfr incude directory.'),
      ('mpfr-lib=', None, 'Specify the path to the mpfr library file.'),
      ('zlib-include-dir=', None, 'Specify the path to the zlib incude directory.'),
      ('zlib-lib=', None, 'Specify the path to the zlib library file.'),
      ('cmake-prefix-path=', None, 'Specify the path to a directory that can be used as CMAKE_PREFIX_PATH, that would contain all headers and libraries. '),
      ('generator=', None, 'The generator to use for cmake.'),
      ('cmake=', None, 'Specify the path to the cmake executable.')
        ]

    def initialize_options(self):
      build_py_orig.initialize_options(self)
      self.cgal_dir= None
      self.boost_dir= None
      self.tbb_include_dir= None
      self.tbb_lib= None
      self.tbb_malloc_include_dir= None
      self.tbb_malloc_lib= None
      self.installation_prefix= None
      self.boost_serialization_lib= None
      self.boost_iostreams_lib= None
      self.boost_regex_lib= None
      self.boost_serialization_include_dir= None
      self.boost_iostreams_include_dir= None
      self.laslib_include_dir= None
      self.laslib_lib= None
      self.eigen3_dir= None
      self.gmp_include_dir= None
      self.gmp_lib= None
      self.mpfr_include_dir= None
      self.mpfr_lib= None
      self.zlib_include_dir= None
      self.zlib_lib= None
      self.cmake_prefix_path= None
      self.generator= None
      self.cmake= None

    def finalize_options(self):
        build_py_orig.finalize_options(self)
        self.set_undefined_options('build', ('cgal_dir', 'cgal_dir'),
                                   ('boost_dir', 'boost_dir'),
                                   ('tbb_include_dir','tbb_include_dir'),
                                   ('tbb_lib','tbb_lib'),
                                   ('tbb_malloc_include_dir','tbb_malloc_include_dir'),
                                   ('tbb_malloc_lib','tbb_malloc_lib'),
                                   ('installation_prefix', 'installation_prefix'),
                                   ('boost_serialization_lib', 'boost_serialization_lib'),
                                   ('boost_iostreams_lib', 'boost_iostreams_lib'),
                                   ('boost_serialization_include_dir', 'boost_serialization_include_dir'),
                                   ('boost_iostreams_include_dir', 'boost_iostreams_include_dir'),
                                   ('boost_regex_lib', 'boost_regex_lib'),
                                   ('laslib_include_dir', 'laslib_include_dir'),
                                   ('laslib_lib', 'laslib_lib'),
                                   ('eigen3_dir', 'eigen3_dir'),
                                   ('gmp_include_dir', 'gmp_include_dir'),
                                   ('gmp_lib', 'gmp_lib'),
                                   ('mpfr_include_dir', 'mpfr_include_dir'),
                                   ('mpfr_lib', 'mpfr_lib'),
                                   ('zlib_include_dir','zlib_include_dir'),
                                   ('zlib_lib', 'zlib_lib'),
                                   ('cmake_prefix_path','cmake_prefix_path'),
                                   ('generator', 'generator'),
                                   ('cmake', 'cmake')
                                   )
        #Must call build_cmake() as soon as possible because the package directory
        #doesn't exist until it is finished, which means that all the checks for
        #it will fail.
        
        self.build_cmake()
        self.data_files = self.get_data_files()


    def build_cmake(self):        
        cwd = pathlib.Path().absolute()

        build_temp = pathlib.Path("build")
        build_temp.mkdir(parents=True, exist_ok=True)
        config = 'Release'
        cmake_args = [
            '-DBUILD_JAVA=OFF',
            '-DBUILD_PYTHON=ON',
            '-DCMAKE_BUILD_TYPE=Release',
        ]
        if self.cgal_dir is not None:
            cmake_args.append('-DCGAL_DIR='+self.cgal_dir)
        if self.boost_dir is not None:
            cmake_args.append('-DBoost_INCLUDE_DIR='+self.boost_dir)
        if self.tbb_include_dir is not None:
            cmake_args.append('-DTBB_INCLUDE_DIR='+self.tbb_include_dir)
        if self.tbb_lib is not None:
            cmake_args.append('-DTBB_LIBRARY_RELEASE='+self.tbb_lib)
        if self.tbb_malloc_include_dir is not None:
            cmake_args.append('-DTBB_MALLOC_LIBRARY_RELEASE='+self.tbb_malloc_include_dir)
        if self.tbb_malloc_lib is not None:
            cmake_args.append('-DTBB_MALLOC_INCLUDE_DIR='+self.tbb_malloc_lib)
        if self.installation_prefix is not None:
            cmake_args.append('-DCMAKE_INSTALL_PREFIX='+self.installation_prefix)
        if self.boost_serialization_lib is not None:
            cmake_args.append('-DBoost_SERIALIZATION_LIBRARY_RELEASE='+self.boost_serialization_lib)
        if self.boost_iostreams_lib is not None:
            cmake_args.append('-DBoost_IOSTREAMS_LIBRARY_RELEASE='+self.boost_iostreams_lib)
        if self.boost_regex_lib is not None:
            cmake_args.append('-DBoost_REGEX_LIBRARY_RELEASE='+self.boost_regex_lib)
            
        if self.boost_serialization_include_dir is not None:
            cmake_args.append('-DBoost_SERIALIZATION_INCLUDE_DIR='+self.boost_serialization_include_dir)
        if self.boost_iostreams_include_dir is not None:
            cmake_args.append('-DBoost_IOSTREAMS_INCLUDE_DIR='+self.boost_iostreams_include_dir)
        
      
        if self.laslib_include_dir is not None:
            cmake_args.append('-DLASLIB_INCLUDE_DIR='+self.laslib_include_dir)
        if self.laslib_lib is not None:
            cmake_args.append('-DLASLIB_LIBRARIES='+self.laslib_lib)
        if self.eigen3_dir is not None:
            cmake_args.append('-DEIGEN3_INCLUDE_DIR='+self.eigen3_dir)
        if self.gmp_include_dir is not None:
            cmake_args.append('-DGMP_INCLUDE_DIR='+self.gmp_include_dir)
        if self.gmp_lib is not None:
            cmake_args.append('-DGMP_LIBRARIES='+self.gmp_lib)
        if self.mpfr_include_dir is not None:
            cmake_args.append('-DMPFR_INCLUDE_DIR='+self.mpfr_include_dir)
        if self.mpfr_lib is not None:
            cmake_args.append('-DMPFR_LIBRARIES='+self.mpfr_lib)
        if self.zlib_include_dir is not None:
            cmake_args.append('-DZLIB_INCLUDE_DIR='+self.zlib_include_dir)
        if self.zlib_lib is not None:
            cmake_args.append('-DZLIB_LIBRARIES='+self.zlib_lib)
        if self.cmake_prefix_path is not None:
          cmake_args.append('-DCMAKE_PREFIX_PATH='+self.cmake_prefix_path)
            
        
        if sys.platform == 'win32' or sys.platform == 'cygwin':
          build_args = [
          '--config', 'Release'
          ]
        else:
          build_args = [
          '--', '-j4'
          ]
        self.cmake_cmd= 'cmake'
        if self.cmake is not None:
          self.cmake_cmd=self.cmake
        os.chdir(str(build_temp))
        self.dry_run=None
        if self.generator:
          self.spawn([self.cmake_cmd, '-G', self.generator, str(cwd)] + cmake_args)
        else:
          self.spawn([self.cmake_cmd, str(cwd)] + cmake_args)
        self.spawn([self.cmake_cmd, '--build', '.'] + build_args)
        
        if sys.platform == 'win32'or sys.platform == 'cygwin':  #if windows, fetch the dlls in build/Release/lib
          for dll in glob.glob("lib/Release/*.dll"):
            shutil.copyfile(dll, os.path.join('', 'build-python/CGAL/'+os.path.basename(dll)))            
        else:      #if on a UNIX system, get cgal libs with auditwheel-like programs, so make install.
          self.spawn([self.cmake_cmd, '--install', '.'] )
        os.chdir(str(cwd))


CGAL_modules = [
    'Box_intersection_d',
    'Convex_hull_2',
    'Convex_hull_3',
    'Classification',
    'HalfedgeDS',
    'Interpolation',
    'Mesh_2',
    'Point_set_3',
    'Point_set_processing_3',
    'Polygon_mesh_processing',
    'Polyhedron_3',
    'Polyline_simplification_2',
    'Shape_detection',
    'Spatial_searching',
    'Voronoi_diagram_2',
    'AABB_tree',
    'Advancing_front_surface_reconstruction',
    'Alpha_shape_2',
    'Kernel',
    'Mesh_3',
    'Surface_mesher',
    'Triangulation_2',
    'Triangulation_3'
]

extensions = []


class my_build_ext(build_ext_orig):
        def build_extension(self, ext):
          if sys.platform == 'win32'or sys.platform == 'cygwin':
            lib_ext='.pyd'
          else:
            lib_ext='.so'
          import os.path
          if '_cpp' in ext.name: #will not happen in windows
            shutil.copyfile(os.path.join('', './build/lib/'+ext.name+lib_ext), self.get_ext_fullpath(ext.name))
          else:
            shutil.copyfile(os.path.join('', './build/build-python/'+ext.name+lib_ext), self.get_ext_fullpath(ext.name))


#collect CGAL modules
for mod_name in CGAL_modules:
    e = Extension('CGAL/_CGAL_'+mod_name,
                  sources=[])
    extensions.append(e)

if sys.platform == 'win32' or sys.platform == 'cygwin':
          bin_temp = pathlib.Path("build/build-python/CGAL/")
          bin_temp.mkdir(parents=True, exist_ok=True)
          for dll in all_dll:
            shutil.copyfile(all_dll[dll], os.path.join('', 'build/build-python/CGAL/'+dll))            
            
setup(name='cgal',
      version='5.0.2',
      author="CGAL Project",
      description="CGAL bindings, allowing to use some of the CGAL library in python.",
      packages=['CGAL'],
      package_dir = {'CGAL': 'build/build-python/CGAL'},
      url="https://github.com/CGAL/cgal-swig-bindings",
      python_requires='>=2.7',
      classifiers = [
        'Development Status :: 5 - Production/Stable',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)',
        'Natural Language :: English',
        'Operating System :: iOS',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: Unix',
        'Programming Language :: C++',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 3',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Mathematics',
        'Topic :: Software Development :: Libraries'
    ],
      install_requires=['numpy'],
      package_data={'CGAL': ['*.dll']},
      cmdclass={
        'install' : InstallCommand,
        'build' : BuildCommand,
        'build_py' : build_py,
        'build_ext': my_build_ext,
        'bdist_wheel' : BuildWheelCommand,
    },
      ext_modules = extensions)
