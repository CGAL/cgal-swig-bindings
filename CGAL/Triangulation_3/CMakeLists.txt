cmake_minimum_required(VERSION 2.6)


SET (MODULENAME "Triangulation_3")
SET (INTERFACE_FILES  "${MODULENAME}.i")
SET (OBJECT_FILES "")
SET (JAVA_OBJECT_FILES "")
SET (PYTHON_OBJECT_FILES "")
SET (JAVAPACKAGENAME "CGAL.${MODULENAME}")
SET (JAVABUILDPATH "../../build-java/CGAL/${MODULENAME}")
SET (JAVALIBPATH "../../build-java/lib")
SET (PYTHONBUILDPATH "../../build-python/CGAL")

find_package(CGAL)

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  find_package(SWIG REQUIRED)
  
  if ( SWIG_FOUND )
    SET (UseSWIG ON)
    INCLUDE(${SWIG_USE_FILE})
    
    FIND_PACKAGE(PythonLibs)

    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
    
    SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)
    
    #Build bindings for python
    if(PYTHONLIBS_FOUND)
      INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})
      LINK_DIRECTORIES(${PYTHONBUILDPATH})
      SET (CMAKE_SWIG_OUTDIR ${PYTHONBUILDPATH})
      SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PYTHONBUILDPATH})
      SWIG_ADD_MODULE(${MODULENAME} python ${INTERFACE_FILES} ${OBJECT_FILES} ${PYTHON_OBJECT_FILES})

      SWIG_LINK_LIBRARIES(${MODULENAME} :${PYTHONBUILDPATH}/_Kernel${CMAKE_SHARED_LIBRARY_SUFFIX})
      
      configure_file(../files/__init__.py ${PYTHONBUILDPATH}/__init__.py  COPYONLY)
    else()
      message("Python has not be found,  cgal-python will not be compiled.")
    endif()
    
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
      SWIG_LINK_LIBRARIES(${MODULENAME} Kernel)
    else()
      message("JNI has not be found,  cgal-java will not be compiled.")
    endif()

    
  else()
    message(STATUS "NOTICE: This program requires the SWIG include files and binary program, and will not be compiled.")
  endif()
else()
    message(STATUS "NOTICE: This program requires the CGAL library, and will not be compiled.")
endif()
