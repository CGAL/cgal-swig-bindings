See https://github.com/CGAL/cgal-swig-bindings/wiki/User_package

Files list:
CGAL_Surface_mesh_skeletonization.i - Swig interface file.
structs.h - Added classes/structs. For now, contains the algorithm parameters' structs.
common.h - template functions, used by impl*.h files. Contains the algorithm running & output printing functions.
impl_polyhedron_3.h - algorithm implementation
CMakeLists.txt - how to build package. Note: requires CGAL::Eigen3_support in order to compile.