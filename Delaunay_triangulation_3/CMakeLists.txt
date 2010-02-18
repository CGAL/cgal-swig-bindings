cmake_minimum_required(VERSION 2.6)


SET (INTERFACE_FILES  "DT3.i")
SET (OBJECT_FILES "EPIC_Kernel.cpp")
SET (JAVA_OBJECT_FILES "JavaData.cpp")
SET (PYTHON_OBJECT_FILES "")

find_package(CGAL)

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  find_package(SWIG REQUIRED)
  
  if ( SWIG_FOUND )
    SET (UseSWIG ON)
    INCLUDE(${SWIG_USE_FILE})
    
    FIND_PACKAGE(PythonLibs)
    

    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

    SET(CMAKE_SWIG_FLAGS "")

    SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)
    #SET_SOURCE_FILES_PROPERTIES(DT3.i PROPERTIES SWIG_FLAGS "-includeall")
    if(PYTHONLIBS_FOUND)
      #INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH}) <-- deprecated
      INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})
      SWIG_ADD_MODULE(DT3 python ${INTERFACE_FILES} ${OBJECT_FILES} ${PYTHON_OBJECT_FILES})
    endif()
    SWIG_ADD_MODULE(DT3 java ${INTERFACE_FILES} ${OBJECT_FILES} ${JAVA_OBJECT_FILES})
    
    #SWIG_LINK_LIBRARIES(DT3 ${PYTHON_LIBRARIES})


  else()
    message(STATUS "NOTICE: This program requires the SWIG include files and binary program, and will not be compiled.")
  endif()
else()
    message(STATUS "NOTICE: This program requires the CGAL library, and will not be compiled.")
endif()
