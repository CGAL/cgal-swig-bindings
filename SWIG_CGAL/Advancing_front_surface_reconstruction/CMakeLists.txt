SET (LIBSTOLINKWITH CGAL_Kernel_cpp)
if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()
# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Advancing_front_surface_reconstruction ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_PYTHON_MODULE ( Advancing_front_surface_reconstruction ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_RUBY_MODULE   ( Advancing_front_surface_reconstruction ${LIBSTOLINKWITH} )

