cmake_minimum_required(VERSION 2.8)

SET (PACKAGENAME "Java")
SET (MODULENAME "CGAL_${PACKAGENAME}")
SET (INTERFACE_FILES  "${MODULENAME}.i")
SET (OBJECT_FILES "")
SET (JAVA_OBJECT_FILES "JavaData.cpp")
SET (JAVAPACKAGENAME "CGAL.${PACKAGENAME}")
SET (JAVABUILDPATH "../../build-java/CGAL/${PACKAGENAME}")
SET (JAVALIBPATH "../../build-java/lib")

find_package(CGAL)

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  find_package(SWIG REQUIRED)
  
  if ( SWIG_FOUND )
    SET (UseSWIG ON)
    INCLUDE(${SWIG_USE_FILE})
    
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
    
    SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)
    
    #Build bindings for java
    find_package(JNI)
    if (JAVA_INCLUDE_PATH)
      MESSAGE("JNI include dirs ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2}")
      INCLUDE_DIRECTORIES(BEFORE ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
      LINK_DIRECTORIES(${JAVALIBPATH})
      SET (CMAKE_SWIG_OUTDIR ${JAVABUILDPATH})
      SET(CMAKE_SWIG_FLAGS -package ${JAVAPACKAGENAME})
      SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${JAVALIBPATH})
      SWIG_ADD_MODULE(${MODULENAME} java ${INTERFACE_FILES} ${OBJECT_FILES} ${JAVA_OBJECT_FILES})
    else()
      message("JNI has not be found,  cgal-java will not be compiled.")
    endif()

    
  else()
    message(STATUS "NOTICE: This program requires the SWIG include files and binary program, and will not be compiled.")
  endif()
else()
    message(STATUS "NOTICE: This program requires the CGAL library, and will not be compiled.")
endif()
