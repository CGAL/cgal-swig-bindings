SET (LIBSTOLINKWITH CGAL_Kernel_cpp)
if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()

# cpp common library
ADD_SWIG_CGAL_LIBRARY(CGAL_Triangulation_3_cpp Object.cpp ${LIBSTOLINKWITH})

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Triangulation_3 ${LIBSTOLINKWITH} CGAL_Triangulation_3_cpp )
ADD_SWIG_CGAL_PYTHON_MODULE ( Triangulation_3 ${LIBSTOLINKWITH} CGAL_Triangulation_3_cpp )
ADD_SWIG_CGAL_RUBY_MODULE   ( Triangulation_3 ${LIBSTOLINKWITH} CGAL_Triangulation_3_cpp )
