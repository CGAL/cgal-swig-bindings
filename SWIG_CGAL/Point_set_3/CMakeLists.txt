SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

find_package(LASLIB QUIET)
if (LASLIB_FOUND)
  include(${LASLIB_USE_FILE})
  include_directories(${LASLIB_INCLUDE_DIR})
  include_directories(${LASZIP_INCLUDE_DIR})
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} ${LASLIB_LIBRARIES})
else()
  message(STATUS "NOTICE : LAS IO requires LASlib and will not be available.")
endif()

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Point_set_3 ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_PYTHON_MODULE ( Point_set_3 ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_RUBY_MODULE   ( Point_set_3 ${LIBSTOLINKWITH} )
