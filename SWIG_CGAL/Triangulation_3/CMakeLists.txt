SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

# cpp common library
ADD_SWIG_CGAL_LIBRARY(CGAL_Triangulation_3_cpp Object.cpp ${LIBSTOLINKWITH})

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Triangulation_3 ${LIBSTOLINKWITH} CGAL_Triangulation_3_cpp )
ADD_SWIG_CGAL_PYTHON_MODULE ( Triangulation_3 ${LIBSTOLINKWITH} CGAL_Triangulation_3_cpp )
ADD_SWIG_CGAL_RUBY_MODULE   ( Triangulation_3 ${LIBSTOLINKWITH} CGAL_Triangulation_3_cpp )
