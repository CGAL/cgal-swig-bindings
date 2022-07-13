SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

find_package(LASLIB QUIET)
if (LASLIB_FOUND)
  include(CGAL_LASLIB_support)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} CGAL::LASLIB_support)
else()
  message(STATUS "NOTICE : LAS IO requires LASlib and will not be available.")
endif()

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Point_set_3 ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_PYTHON_MODULE ( Point_set_3 ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_RUBY_MODULE   ( Point_set_3 ${LIBSTOLINKWITH} )
