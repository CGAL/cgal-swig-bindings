MACRO(EXTRACT_CPP_AND_LIB_FILES)
  #recover cpp files to be compiled
  SET(object_files)
  SET(libstolinkwith)
  FOREACH(it ${ARGN})
    IF(${it} MATCHES ".*\\.cpp$")
      SET(object_files ${object_files} "${it}")
    ELSE(${it} MATCHES ".*\\.cpp$")
      SET(libstolinkwith ${libstolinkwith} "${it}")
    ENDIF(${it} MATCHES ".*\\.cpp$")
  ENDFOREACH(it)
ENDMACRO(EXTRACT_CPP_AND_LIB_FILES)


MACRO(ADD_SWIG_CGAL_LIBRARY libname)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${COMMON_LIBRARIES_PATH}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${COMMON_LIBRARIES_PATH}")
  EXTRACT_CPP_AND_LIB_FILES(${ARGN}) 
  add_library(${libname} SHARED ${object_files})
  target_link_libraries(${libname} ${libstolinkwith})
  install (TARGETS ${libname} RUNTIME DESTINATION bin
                              LIBRARY DESTINATION lib${LIB_SUFFIX}
                              ARCHIVE DESTINATION lib${LIB_SUFFIX})
ENDMACRO()

MACRO(ADD_SWIG_CGAL_JAVA_MODULE packagename)
  
  if (BUILD_JAVA AND JAVA_INCLUDE_PATH)
    SET (MODULENAME "CGAL_${packagename}")
    SET (INTERFACE_FILES  "CGAL_${packagename}.i")
    SET (JAVAPACKAGENAME "CGAL.${packagename}")
    SET (JAVABUILDPATH "${JAVA_OUTDIR_PREFIX}/CGAL/${packagename}")
    SET (SWIGCGAL_NO_FINALIZE_FOR_${packagename} OFF
         CACHE BOOL "Indicates if finalize() method in generated class should be removed in package ${packagename}")
    if(SWIGCGAL_NO_FINALIZE_FOR_${packagename})
      message(STATUS "${packagename}: No `finalize()` method will be generated for this package. `delete()` must be called explicitely")
      SET(CMAKE_SWIG_EXTRA_FLAGS -DSWIG_CGAL_NO_FINALIZE)
    endif()

    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
    INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    #recover cpp files to be compiled
    EXTRACT_CPP_AND_LIB_FILES(${ARGN})

    SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)
    
    #Build bindings for java
    INCLUDE_DIRECTORIES(BEFORE ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2})
    LINK_DIRECTORIES(${JAVALIBPATH})
    SET (CMAKE_SWIG_OUTDIR ${JAVABUILDPATH})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../User_packages/${packagename}/extensions.i")
      SET(CMAKE_SWIG_FLAGS -package ${JAVAPACKAGENAME} -DSWIG_CGAL_${packagename}_MODULE -DSWIG_CGAL_HAS_${packagename}_USER_PACKAGE ${CMAKE_SWIG_EXTRA_FLAGS})
    else()
      SET(CMAKE_SWIG_FLAGS -package ${JAVAPACKAGENAME} -DSWIG_CGAL_${packagename}_MODULE ${CMAKE_SWIG_EXTRA_FLAGS})
    endif()
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${JAVALIBPATH})
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${JAVALIBPATH})
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${JAVALIBPATH})
    if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
      SWIG_ADD_MODULE(${MODULENAME} java ${INTERFACE_FILES} ${object_files})
    else()
      SWIG_ADD_LIBRARY(${MODULENAME} LANGUAGE java SOURCES ${INTERFACE_FILES} ${object_files})
    endif()
    #link all modules with CGAL_Java_cpp as many if not all need it for the iterators for example
    SWIG_LINK_LIBRARIES(${MODULENAME} ${libstolinkwith} CGAL_Java_cpp)
  endif()
ENDMACRO(ADD_SWIG_CGAL_JAVA_MODULE)

MACRO(ADD_SWIG_CGAL_PYTHON_MODULE packagename)
  SET (MODULENAME "CGAL_${packagename}")
  SET (INTERFACE_FILES  "CGAL_${packagename}.i")
  
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
  INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

  #recover cpp files to be compiled
  EXTRACT_CPP_AND_LIB_FILES(${ARGN})

  SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)

  #Build bindings for python
  if(PYTHONLIBS_FOUND)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})
    SET (CMAKE_SWIG_OUTDIR "${PYTHON_OUTDIR_PREFIX}/CGAL")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../User_packages/${packagename}/extensions.i")
      SET(CMAKE_SWIG_FLAGS  -DSWIG_CGAL_${packagename}_MODULE -DSWIG_CGAL_HAS_${packagename}_USER_PACKAGE)
    else()
      SET(CMAKE_SWIG_FLAGS  -DSWIG_CGAL_${packagename}_MODULE)
    endif()
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL")
    SET(CMAKE_MODULE_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL")
    if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
      SWIG_ADD_MODULE(${MODULENAME} python ${INTERFACE_FILES} ${object_files})
    else()
      SWIG_ADD_LIBRARY(${MODULENAME} LANGUAGE python SOURCES ${INTERFACE_FILES} ${object_files})
    endif()
    SWIG_LINK_LIBRARIES(${MODULENAME} ${libstolinkwith})
    if ( LINK_PYTHON_LIBRARY )
      swig_link_libraries ( ${MODULENAME} ${PYTHON_LIBRARIES} )
    endif ()
    install (FILES ${PYTHON_OUTDIR_PREFIX}/CGAL/${MODULENAME}.py DESTINATION ${PYTHON_MODULE_PATH}/CGAL)
    install (TARGETS ${SWIG_MODULE_${MODULENAME}_REAL_NAME} DESTINATION ${PYTHON_MODULE_PATH}/CGAL)
  endif()
ENDMACRO(ADD_SWIG_CGAL_PYTHON_MODULE)

MACRO(ADD_SWIG_CGAL_RUBY_MODULE packagename)
  SET (MODULENAME "CGAL_${packagename}")
  SET (INTERFACE_FILES  "CGAL_${packagename}.i")
  
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
  INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

  #recover cpp files to be compiled
  EXTRACT_CPP_AND_LIB_FILES(${ARGN})

  SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)

  #Build bindings for ruby
  if(RUBY_FOUND)
    INCLUDE_DIRECTORIES(${RUBY_INCLUDE_PATH})
    SET (CMAKE_SWIG_OUTDIR "${RUBY_OUTDIR_PREFIX}/CGAL")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../User_packages/${packagename}/extensions.i")
      SET(CMAKE_SWIG_FLAGS  -DSWIG_CGAL_${packagename}_MODULE -DSWIG_CGAL_HAS_${packagename}_USER_PACKAGE)
    else()
      SET(CMAKE_SWIG_FLAGS  -DSWIG_CGAL_${packagename}_MODULE)
    endif()
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${RUBY_OUTDIR_PREFIX}/CGAL")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${RUBY_OUTDIR_PREFIX}/CGAL")
    SET(CMAKE_MODULE_OUTPUT_DIRECTORY "${RUBY_OUTDIR_PREFIX}/CGAL")
    if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
      SWIG_ADD_MODULE(${MODULENAME} ruby ${INTERFACE_FILES} ${object_files})
    else()
      SWIG_ADD_LIBRARY(${MODULENAME} LANGUAGE ruby SOURCES ${INTERFACE_FILES} ${object_files})
    endif()
    SET_TARGET_PROPERTIES(${SWIG_MODULE_${MODULENAME}_REAL_NAME} PROPERTIES PREFIX "")

    SWIG_LINK_LIBRARIES(${MODULENAME} ${libstolinkwith} ${RUBY_LIBRARY})
  endif()
ENDMACRO(ADD_SWIG_CGAL_RUBY_MODULE)

