cmake_minimum_required(VERSION 2.8)


PROJECT(CGAL-bindings)


find_package(CGAL)
find_package(SWIG REQUIRED)
option( BUILD_PYTHON "Build python bindings" ON )
option( BUILD_JAVA "Build java bindings" ON )

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  
  if (SWIG_FOUND)
    SET (UseSWIG ON)
    INCLUDE(${SWIG_USE_FILE})  
    
    MACRO(SWIG_ADD_MODULE name language)
      SWIG_MODULE_INITIALIZE(${name} ${language})
      SET(swig_dot_i_sources)
      SET(swig_other_sources)
      FOREACH(it ${ARGN})
        IF(${it} MATCHES ".*\\.i$")
          SET(swig_dot_i_sources ${swig_dot_i_sources} "${it}")
        ELSE(${it} MATCHES ".*\\.i$")
          SET(swig_other_sources ${swig_other_sources} "${it}")
        ENDIF(${it} MATCHES ".*\\.i$")
      ENDFOREACH(it)

      SET(swig_generated_sources)
      FOREACH(it ${swig_dot_i_sources})
        SWIG_ADD_SOURCE_TO_MODULE(${name} swig_generated_source ${it})
        SET(swig_generated_sources ${swig_generated_sources} "${swig_generated_source}")
      ENDFOREACH(it)
      GET_DIRECTORY_PROPERTY(swig_extra_clean_files ADDITIONAL_MAKE_CLEAN_FILES)
      SET_DIRECTORY_PROPERTIES(PROPERTIES
        ADDITIONAL_MAKE_CLEAN_FILES "${swig_extra_clean_files};${swig_generated_sources}")
      ADD_LIBRARY(${SWIG_MODULE_${name}_REAL_NAME}
        SHARED
        ${swig_generated_sources}
        ${swig_other_sources})
      STRING(TOLOWER "${language}" swig_lowercase_language)
      IF ("${swig_lowercase_language}" STREQUAL "java")
        IF (APPLE)
            # In java you want:
            #      System.loadLibrary("LIBRARY");
            # then JNI will look for a library whose name is platform dependent, namely
            #   MacOS  : libLIBRARY.jnilib
            #   Windows: LIBRARY.dll
            #   Linux  : libLIBRARY.so
            SET_TARGET_PROPERTIES (${SWIG_MODULE_${name}_REAL_NAME} PROPERTIES SUFFIX ".jnilib")
          ENDIF (APPLE)
      ENDIF ("${swig_lowercase_language}" STREQUAL "java")
      IF ("${swig_lowercase_language}" STREQUAL "python")
        # this is only needed for the python case where a _modulename.so is generated
        SET_TARGET_PROPERTIES(${SWIG_MODULE_${name}_REAL_NAME} PROPERTIES PREFIX "")
        # Python extension modules on Windows must have the extension ".pyd"
        # instead of ".dll" as of Python 2.5.  Older python versions do support
        # this suffix.
        # http://docs.python.org/whatsnew/ports.html#SECTION0001510000000000000000
        # <quote>
        # Windows: .dll is no longer supported as a filename extension for extension modules.
        # .pyd is now the only filename extension that will be searched for.
        # </quote>
        IF(WIN32 AND NOT CYGWIN)
          SET_TARGET_PROPERTIES(${SWIG_MODULE_${name}_REAL_NAME} PROPERTIES SUFFIX ".pyd")
        ENDIF(WIN32 AND NOT CYGWIN)
      ENDIF ("${swig_lowercase_language}" STREQUAL "python")
    ENDMACRO(SWIG_ADD_MODULE)

    if (${BUILD_PYTHON})
      FIND_PACKAGE(PythonLibs)
    endif()
    if (${BUILD_JAVA})
      FIND_PACKAGE(JNI)
    endif()
    
    if (PYTHONLIBS_FOUND)
      SET (PYTHONBUILDPATH "${CMAKE_CURRENT_SOURCE_DIR}/../build-python/CGAL/")
      configure_file(files/__init__.py ${PYTHONBUILDPATH}/__init__.py  COPYONLY)
      LINK_DIRECTORIES(${PYTHONBUILDPATH})
      MESSAGE("Found Python libs.")
      MESSAGE("CGAL-SWIG Python libs will be written in ${CMAKE_CURRENT_SOURCE_DIR}/../build-python/CGAL.")
    endif()
    if (JAVA_INCLUDE_PATH)
      SET (JAVALIBPATH "${CMAKE_CURRENT_SOURCE_DIR}/../build-java/lib")
      MESSAGE("Found JNI: JNI include dirs ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2}.")
      MESSAGE("CGAL-SWIG Java libs will be written in ${CMAKE_CURRENT_SOURCE_DIR}/../build-java/lib.")
      MESSAGE("CGAL-SWIG Java files will be written in ${CMAKE_CURRENT_SOURCE_DIR}/../build-java/CGAL.")
    endif()

    add_subdirectory(Kernel)
    add_subdirectory(Java)
    add_subdirectory(Triangulation_3)
    add_subdirectory(Triangulation_2)
    add_subdirectory(Polyhedron_3)
  else()
    message(STATUS "NOTICE: This program requires the SWIG include files and binary program, and will not be compiled.")
  endif()
else()
    message(STATUS "NOTICE: This program requires the CGAL library, and will not be compiled.")
endif()