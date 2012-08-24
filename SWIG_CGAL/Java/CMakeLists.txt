SET (JAVA_OBJECT_FILES JavaData.cpp global_functions.cpp)

# cpp common library only built if Java is on
if (${BUILD_JAVA})
  ADD_SWIG_CGAL_LIBRARY(CGAL_Java_cpp ${JAVA_OBJECT_FILES})
endif()

# Module
ADD_SWIG_CGAL_JAVA_MODULE( Java )
