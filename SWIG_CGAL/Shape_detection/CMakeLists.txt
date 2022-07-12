SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

find_package(Eigen3 3.1.0)

if (EIGEN3_FOUND)
  include(CGAL_Eigen3_support)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} CGAL::Eigen3_support)
  if (TBB_FOUND)
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
  endif()
  # Modules
  ADD_SWIG_CGAL_JAVA_MODULE   ( Shape_detection ${LIBSTOLINKWITH} )
  ADD_SWIG_CGAL_PYTHON_MODULE ( Shape_detection ${LIBSTOLINKWITH} "-keyword" )
  ADD_SWIG_CGAL_RUBY_MODULE   ( Shape_detection ${LIBSTOLINKWITH} )
else()
    message(STATUS "NOTICE: Shape_detection bindings requires Eigen version 3.1 or greater, and will not be compiled.")
endif()
