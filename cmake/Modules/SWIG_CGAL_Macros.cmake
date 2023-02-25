MACRO(EXTRACT_CPP_AND_LIB_FILES)
  #recover cpp files to be compiled
  SET(source_files)
  SET(libstolinkwith)
  SET(flags)
  FOREACH(it ${ARGN})
    IF(${it} MATCHES ".*\\.cpp$")
      SET(source_files ${source_files} "${it}")
    ELSE(${it} MATCHES ".*\\.cpp$")
      IF(${it} MATCHES "-.*")
        SET(flags ${flags} "${it}")
      ELSE()
        SET(libstolinkwith ${libstolinkwith} "${it}")
      ENDIF()
    ENDIF(${it} MATCHES ".*\\.cpp$")
  ENDFOREACH(it)
ENDMACRO(EXTRACT_CPP_AND_LIB_FILES)


MACRO(ADD_SWIG_CGAL_LIBRARY libname)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${COMMON_LIBRARIES_PATH}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${COMMON_LIBRARIES_PATH}")
  EXTRACT_CPP_AND_LIB_FILES(${ARGN})
  add_library(${libname} SHARED ${source_files})
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
      SWIG_ADD_MODULE(${MODULENAME} java ${INTERFACE_FILES} ${source_files})
    else()
      SWIG_ADD_LIBRARY(${MODULENAME} LANGUAGE java SOURCES ${INTERFACE_FILES} ${source_files})
    endif()
    #don't split dlls with configuration dependent generators
    set_target_properties (${MODULENAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${JAVA_OUTDIR_PREFIX}/lib$<$<CONFIG:Release>:>")
    #link all modules with CGAL_Java_cpp as many if not all need it for the iterators for example
    SWIG_LINK_LIBRARIES(${MODULENAME} ${libstolinkwith} CGAL_Java_cpp)
  endif()
ENDMACRO(ADD_SWIG_CGAL_JAVA_MODULE)

MACRO(ADD_SWIG_CGAL_PYTHON_MODULE packagename)
  SET (MODULENAME "CGAL_${packagename}")
  SET (INTERFACE_FILES  "CGAL_${packagename}.i")

  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

  #recover cpp files to be compiled
  EXTRACT_CPP_AND_LIB_FILES(${ARGN})

  SET_SOURCE_FILES_PROPERTIES(${INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)

  #Build bindings for python
  if(BUILD_PYTHON)
    INCLUDE_DIRECTORIES(${Python_INCLUDE_DIRS})
    SET (CMAKE_SWIG_OUTDIR "${PYTHON_OUTDIR_PREFIX}/CGAL")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../User_packages/${packagename}/extensions.i")
      SET(CMAKE_SWIG_FLAGS  -DSWIG_CGAL_${packagename}_MODULE -DSWIG_CGAL_HAS_${packagename}_USER_PACKAGE)
    else()
      SET(CMAKE_SWIG_FLAGS  -DSWIG_CGAL_${packagename}_MODULE)
    endif()
    SET(CMAKE_SWIG_FLAGS ${flags} ${CMAKE_SWIG_FLAGS})
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL")
    SET(CMAKE_MODULE_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL")

    SWIG_ADD_LIBRARY(${MODULENAME}_python LANGUAGE python SOURCES ${INTERFACE_FILES} ${source_files})

    if (CMAKE_VERSION VERSION_LESS 3.13)
      set_target_properties (${SWIG_MODULE_${MODULENAME}_python_REAL_NAME} PROPERTIES OUTPUT_NAME ${MODULENAME})
      set_target_properties (${SWIG_MODULE_${MODULENAME}_python_REAL_NAME} PROPERTIES PREFIX "_")
    else ()
      set_target_properties (${MODULENAME}_python PROPERTIES OUTPUT_NAME ${MODULENAME})
    endif ()
    if (WIN32)
      swig_link_libraries (${MODULENAME}_python Python::Module)
    elseif (APPLE)
      set_target_properties(${SWIG_MODULE_${MODULENAME}_python_REAL_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif ()
    # .pyd/.so files must NOT be in a /Release or a /Debug directory, or their import path will be wrong.
    set_target_properties (${SWIG_MODULE_${MODULENAME}_python_REAL_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PYTHON_OUTDIR_PREFIX}/CGAL$<$<CONFIG:Release>:>")
    swig_link_libraries (${MODULENAME}_python ${libstolinkwith})
    install (FILES ${PYTHON_OUTDIR_PREFIX}/CGAL/${MODULENAME}.py DESTINATION ${PYTHON_MODULE_PATH}/CGAL)
    if (CMAKE_VERSION VERSION_LESS 3.13)
      install (TARGETS ${SWIG_MODULE_${MODULENAME}_python_REAL_NAME} DESTINATION ${PYTHON_MODULE_PATH}/CGAL)
    else ()
      install (TARGETS ${MODULENAME}_python DESTINATION ${PYTHON_MODULE_PATH}/CGAL)
    endif ()
  endif()
ENDMACRO(ADD_SWIG_CGAL_PYTHON_MODULE)

MACRO(ADD_SWIG_CGAL_RUBY_MODULE packagename)
  set (MODULENAME "CGAL_${packagename}")
  set (INTERFACE_FILES  "CGAL_${packagename}.i")
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

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
      SWIG_ADD_MODULE(${MODULENAME}_ruby ruby ${INTERFACE_FILES} ${source_files})
    else()
      SWIG_ADD_LIBRARY(${MODULENAME}_ruby LANGUAGE ruby SOURCES ${INTERFACE_FILES} ${source_files})
    endif()
    if (CMAKE_VERSION VERSION_LESS 3.13)
      set_target_properties (${SWIG_MODULE_${MODULENAME}_ruby_REAL_NAME} PROPERTIES OUTPUT_NAME ${MODULENAME})
      set_target_properties (${SWIG_MODULE_${MODULENAME}_ruby_REAL_NAME} PROPERTIES PREFIX "_")
    else ()
      set_target_properties (${MODULENAME}_ruby PROPERTIES OUTPUT_NAME ${MODULENAME})
    endif ()
    SWIG_LINK_LIBRARIES(${MODULENAME}_ruby ${libstolinkwith} ${RUBY_LIBRARY})
  endif()
ENDMACRO(ADD_SWIG_CGAL_RUBY_MODULE)

