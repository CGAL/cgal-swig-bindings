import os
import pathlib
import glob
import shutil

import sys

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as build_ext_orig
from setuptools.command.install import install
from setuptools.command.install_lib import install_lib
from setuptools.command.build import build
from wheel.bdist_wheel import bdist_wheel


# [
#   'boost_iostreams',
# 'boost_serialization',
# 'gmp',
# 'gmpxx',
# 'mpfr',
# 'tbb',
# 'tbbmalloc',
# 'z'
# ]

dependencies_list = ['gmp', 'mpfr', 'mpir.dll', 'boost_serialization', 'boost_iostreams', 'boost_zlib', 'boost_bzip2', 'tbb.dll', 'tbbmalloc', 'las.dll', 'zlib.dll', 'boost_regex']

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

  all_keys=""
  for key in all_dll:
    all_keys+=(key+";")

  for dep in dependencies_list:
    if not dep in all_keys:
      print("ERROR: Missing dependency: "+dep)


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
    'Triangulation_3',
    'Alpha_wrap_3'
]

extensions = []


#collect CGAL modules
for mod_name in CGAL_modules:
    e = Extension('CGAL/_CGAL_'+mod_name,
                  sources=[])
    extensions.append(e)



def get_options():
  return [
           ('cgal-dir=', None, 'Specify the path to the CGAL installation directory.'),
           ('boost-dir=', None, 'Specify the path to the Boost include directory.'),
           ('boost-serialization-lib=', None, 'Specify the path to the Boost Serialization library file.'),
           ('boost-iostreams-lib=', None, 'Specify the path to the Boost IOStreams library file.'),
           ('boost-regex-lib=', None, 'Specify the path to the Boost Regex library file.'),
           ('boost-serialization-include-dir=', None, 'Specify the path to the Boost Serialization include directory.'),
           ('boost-iostreams-include-dir=', None, 'Specify the path to the Boost IOStreams include directory.'),
           ('boost-root=', None, 'Specify the path to the Boost root directory.'),
           ('laslib-include-dir=', None, 'Specify the path to the Laslib incude directory.'),
           ('laslib-lib=', None, 'Specify the path to the Laslib library file.'),
           ('tbb-include-dir=', None, 'Specify the path to the TBB include directory.'),
           ('tbb-lib=', None, 'Specify the path to the TBB library directory.'),
           ('tbb-malloc-include-dir=', None, 'Specify the path to the TBB malloc include directory.'),
           ('tbb-malloc-lib-dir=', None, 'Specify the path to the TBB malloc library directory.'),
           ('eigen3-dir=', None, 'Specify the path to the Eigen 3 incude directory.'),
           ('gmp-include-dir=', None, 'Specify the path to the gmp incude directory.'),
           ('gmp-lib=', None, 'Specify the path to the gmp library file.'),
           ('mpfr-include-dir=', None, 'Specify the path to the mpfr incude directory.'),
           ('mpfr-lib=', None, 'Specify the path to the mpfr library file.'),
           ('zlib-include-dir=', None, 'Specify the path to the zlib incude directory.'),
           ('zlib-lib=', None, 'Specify the path to the zlib library file.'),
           ('cmake-prefix-path=', None, 'Specify the path to a directory that can be used as CMAKE_PREFIX_PATH, that would contain all headers and libraries. '),
           ('generator=', None, 'The generator to use for cmake.'),
           ('python-executable=', None, 'The path to the python executable.'),
           ('python-root=', None, 'The path to the Python root directory.'),
           ('cmake=', None, 'Specify the path to the cmake executable.')
         ]

def get_option_pairs():
  values ={('cgal_dir', 'cgal_dir'),
         ('boost_dir', 'boost_dir'),
         ('tbb_include_dir','tbb_include_dir'),
         ('tbb_lib','tbb_lib'),
         ('tbb_malloc_include_dir','tbb_malloc_include_dir'),
         ('tbb_malloc_lib','tbb_malloc_lib'),
         ('boost_serialization_lib', 'boost_serialization_lib'),
         ('boost_iostreams_lib', 'boost_iostreams_lib'),
         ('boost_regex_lib', 'boost_regex_lib'),
         ('boost_serialization_include_dir', 'boost_serialization_include_dir'),
         ('boost_iostreams_include_dir', 'boost_iostreams_include_dir'),
         ('boost_root', 'boost_root'),
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
         ('python_root', 'python_root'),
         ('python_executable', 'python_executable'),
         ('cmake', 'cmake')}
  return values

def init_values(obj):
  obj.cgal_dir= None
  obj.boost_dir= None
  obj.boost_root=None
  obj.tbb_include_dir= None
  obj.tbb_lib= None
  obj.tbb_malloc_include_dir= None
  obj.tbb_malloc_lib= None
  obj.boost_serialization_lib= None
  obj.boost_iostreams_lib= None
  obj.boost_regex_lib= None
  obj.boost_serialization_include_dir= None
  obj.boost_iostreams_include_dir= None
  obj.laslib_include_dir= None
  obj.laslib_lib= None
  obj.eigen3_dir= None
  obj.gmp_include_dir= None
  obj.gmp_lib= None
  obj.mpfr_include_dir= None
  obj.mpfr_lib= None
  obj.zlib_include_dir= None
  obj.zlib_lib= None
  obj.cmake_prefix_path= None
  obj.generator= None
  obj.cmake= None
  obj.python_root= None
  obj.python_executable= sys.executable

class BuildWheelCommand(bdist_wheel):
  user_options = bdist_wheel.user_options + get_options()

  def initialize_options(self):
      bdist_wheel.initialize_options(self)
      init_values(self)

  def run(self):
    build_ext = self.reinitialize_command('build_ext',
                                        reinit_subcommands=True)
    path=self.bdist_dir
    path=path.replace("build/", "")
    path=path.replace("build\\", "")
    setattr(build_ext, 'install_dir', path)
    bdist_wheel.run(self)

class InstallCommand(install):
  user_options = install.user_options + get_options()
  def initialize_options(self):
    install.initialize_options(self)
    init_values(self)



class InstallLibCommand(install_lib):
  user_options = install_lib.user_options + get_options()

  def initialize_options(self):
    install_lib.initialize_options(self)
    init_values(self)

  def finalize_options(self):
    install_lib.finalize_options(self)
    self.set_undefined_options('install', *get_option_pairs())
    self.set_undefined_options('bdist_wheel', *get_option_pairs())


  def build(self):
    if not self.skip_build:
      if self.distribution.has_ext_modules():
          self.run_command('build_ext')
      if self.distribution.has_pure_modules():
          self.run_command('build_py')


  def run(self):
    self.cmake_cmd= 'cmake'
    if self.cmake is not None:
      self.cmake_cmd=self.cmake
    path=self.install_dir
    path=path.replace("build/", "")
    path=path.replace("build\\", "")
    path=os.path.join(path, 'CGAL')
    cwd = pathlib.Path().absolute()
    build_temp = pathlib.Path("build")
    os.chdir(str(build_temp))
    self.spawn([self.cmake_cmd, '-DBUILD_TYPE=Release', '-P', 'cmake_install.cmake'] )
    if sys.platform == 'win32'or sys.platform == 'cygwin':  #if windows, fetch the dlls in build/Release/lib
      for dll in all_dll:
        print("Copying "+all_dll[dll]+" to "+os.path.join(path,dll))
        shutil.copyfile(all_dll[dll], os.path.join(path,dll))
      for dll in glob.glob("lib/Release/*.dll"):
        shutil.copyfile(dll, os.path.join(path,os.path.basename(dll)))
    os.chdir(cwd)

class BuildCommand(build):
    user_options = build.user_options + get_options()

    def __init__(self, *args):
      super().__init__(*args)
      self.sub_commands = [('build_ext',     build.has_ext_modules),
                      ('build_clib',    build.has_c_libraries),
                      ('build_py',      build.has_pure_modules),
                      ('build_scripts', build.has_scripts),
                     ]


    def initialize_options(self):
      build.initialize_options(self)
      init_values(self)

    def finalize_options(self):
        build.finalize_options(self)
        self.set_undefined_options('install', *get_option_pairs())
        self.set_undefined_options('bdist_wheel', *get_option_pairs())


    def set_undefined_options(self, src_cmd, *option_pairs):
       src_cmd_obj = self.distribution.get_command_obj(src_cmd)
      # Remove "src_cmd_obj.ensure_finalized()" to keep from calling install.finalize_options()
      # several times, as it will fail the second time.
       for (src_option, dst_option) in option_pairs:
         if getattr(self, dst_option) is None:
             setattr(self, dst_option, getattr(src_cmd_obj, src_option))





class my_build_ext(build_ext_orig):
    user_options = build_ext_orig.user_options + get_options()

    def initialize_options(self):
      build_ext_orig.initialize_options(self)
      self.install_userbase= None
      init_values(self)
      self.install_dir= None

    def finalize_options(self):
      build_ext_orig.finalize_options(self)
      self.set_undefined_options('build', *get_option_pairs())
      self.set_undefined_options('install', ('install_platlib', 'install_dir'))


    def build_extension(self, ext):
      if sys.platform == 'win32'or sys.platform == 'cygwin':
        lib_ext='.pyd'
      else:
        lib_ext='.so'
      import os.path
      shutil.copyfile(os.path.join('.', 'build','build-python',ext.name+lib_ext), self.get_ext_fullpath(ext.name))


    def run(self):

        cwd = pathlib.Path().absolute()
        build_temp = pathlib.Path("build")
        build_temp.mkdir(parents=True, exist_ok=True)
        config = 'Release'
        cmake_args = [
            '-DBUILD_JAVA=OFF',
            '-DBUILD_PYTHON=ON',
            '-DCMAKE_BUILD_TYPE=Release',
        ]
        if sys.platform == 'win32' or sys.platform == 'cygwin':
            cmake_args.append('-DBoost_LIB_DIAGNOSTIC_DEFINITIONS=TRUE')

        if self.install_dir is not None:
            cmake_args.append('-DCMAKE_INSTALL_PREFIX='+self.install_dir)
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
        if self.boost_root is not None:
            cmake_args.append('-DBoost_DIR='+self.boost_root)

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
        if self.python_executable is not None:
          cmake_args.append('-DPython_EXECUTABLE='+self.python_executable)
        if self.python_root is not None:
          cmake_args.append('-DPython_ROOT_DIR='+self.python_root)
          if sys.platform != 'win32'or sys.platform == 'cygwin':
            cmake_args.append('-DPython_EXECUTABLE='+os.path.join(self.python_root, 'bin','python'))

        cmake_args.append('-DINSTALL_FROM_SETUP=ON')
        cmake_args.append('-DBoost_DEBUG=TRUE')


        if sys.platform == 'win32' or sys.platform == 'cygwin':
          build_args = [
          '--config', 'Release'
          ]
        else:
          build_args = [
          '--', '-j{}'.format(os.cpu_count())
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
        os.chdir(str(cwd))
        build_directory = pathlib.Path(os.path.join(self.build_lib, 'CGAL'))
        build_directory.mkdir(parents=True, exist_ok=True)
        build_ext_orig.build_extensions(self)



setup(name='cgal',
      version=os.environ.get('CGAL_PYTHON_MODULE_VERSION') or '5.4.1',
      author="CGAL Project",
      description="CGAL bindings, allowing to use some of the CGAL library in Python.",
      long_description="The CGAL Bindings project allows to use some packages of CGAL, the Computational Algorithms Library with Python. This project is still experimental and more packages will be added. For more information, please visit https://github.com/CGAL/cgal-swig-bindings/wiki.",
      long_description_content_type="text/markdown",
      packages=['CGAL'],
      package_dir = { 'CGAL': '.' },
      #package_dir = {'CGAL': 'build/build-python/CGAL'},
      url="https://github.com/CGAL/cgal-swig-bindings",
      python_requires='>=3.6',
      classifiers = [
        'Development Status :: 5 - Production/Stable',
        'Environment :: Console',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)',
        'Natural Language :: English',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: Unix',
        'Programming Language :: C++',
        'Programming Language :: Python :: 3',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Mathematics',
        'Topic :: Software Development :: Libraries'
    ],
      install_requires=['numpy'],
      package_data={'CGAL': ['*.dll']},
      cmdclass={
        'install' : InstallCommand,
        'install_lib' : InstallLibCommand,
        'build' : BuildCommand,
        'build_ext': my_build_ext,
        'bdist_wheel' : BuildWheelCommand,
    },
      ext_modules = extensions)
