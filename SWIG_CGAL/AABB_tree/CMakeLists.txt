SET (LIBSTOLINKWITH CGAL_Kernel_cpp)
include_directories(include)
ADD_SWIG_CGAL_JAVA_MODULE  (AABB_tree "Object.cpp" ${LIBSTOLINKWITH} CGAL_Java_cpp)
ADD_SWIG_CGAL_PYTHON_MODULE(AABB_tree "Object.cpp" ${LIBSTOLINKWITH})
