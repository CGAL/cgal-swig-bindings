find_package(CGAL)

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  find_package(SWIG)
  if ( SWIG_FOUND )


  FIND_PACKAGE(PythonLibs)
  INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

  SET(CMAKE_SWIG_FLAGS "")

  SET_SOURCE_FILES_PROPERTIES(DT3.i PROPERTIES CPLUSPLUS ON)
  SET_SOURCE_FILES_PROPERTIES(DT3.i PROPERTIES SWIG_FLAGS "-includeall")
  SWIG_ADD_MODULE(EPIC_Kernel python DT3.i EPIC_Kernel.cpp)
  #SWIG_ADD_MODULE(EPIC_Kernel java DT3.i EPIC_Kernel.cpp)
#  SWIG_LINK_LIBRARIES(EPIC_Kernel ${PYTHON_LIBRARIES})


  else()
    message(STATUS "NOTICE: This program requires the SWIG include files and binary program, and will not be compiled.")
  endif()
else()
    message(STATUS "NOTICE: This program requires the CGAL library, and will not be compiled.")
endif()
