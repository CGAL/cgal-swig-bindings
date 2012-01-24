SET (LIBSTOLINKWITH CGAL_Kernel_cpp)
add_swig_cgal_library(CGAL_Alpha_shape_2_cpp "Object.cpp")
ADD_SWIG_CGAL_JAVA_MODULE  (Alpha_shape_2 ${LIBSTOLINKWITH} CGAL_Alpha_shape_2_cpp CGAL_Java_cpp)
ADD_SWIG_CGAL_PYTHON_MODULE(Alpha_shape_2 ${LIBSTOLINKWITH} CGAL_Alpha_shape_2_cpp)
