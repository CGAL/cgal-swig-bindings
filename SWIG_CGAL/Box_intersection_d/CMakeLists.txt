SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Box_intersection_d ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_PYTHON_MODULE ( Box_intersection_d ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_RUBY_MODULE   ( Box_intersection_d ${LIBSTOLINKWITH} )
