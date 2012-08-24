SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

# cpp common library
ADD_SWIG_CGAL_LIBRARY ( CGAL_Alpha_shape_2_cpp Object.cpp ${LIBSTOLINKWITH} )

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Alpha_shape_2 ${LIBSTOLINKWITH} CGAL_Alpha_shape_2_cpp )
ADD_SWIG_CGAL_PYTHON_MODULE ( Alpha_shape_2 ${LIBSTOLINKWITH} CGAL_Alpha_shape_2_cpp )
ADD_SWIG_CGAL_RUBY_MODULE   ( Alpha_shape_2 ${LIBSTOLINKWITH} CGAL_Alpha_shape_2_cpp )
