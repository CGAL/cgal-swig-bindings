SET (LIBSTOLINKWITH CGAL_Kernel_cpp)
if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()

# cpp common library
add_swig_cgal_library(CGAL_Surface_mesher_cpp Object.cpp ${LIBSTOLINKWITH})

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Surface_mesher ${LIBSTOLINKWITH} CGAL_Surface_mesher_cpp )
ADD_SWIG_CGAL_PYTHON_MODULE ( Surface_mesher ${LIBSTOLINKWITH} CGAL_Surface_mesher_cpp )
ADD_SWIG_CGAL_RUBY_MODULE   ( Surface_mesher ${LIBSTOLINKWITH} CGAL_Surface_mesher_cpp )
