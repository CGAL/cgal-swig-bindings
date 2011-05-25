SET (JAVA_OBJECT_FILES JavaData.cpp global_functions.cpp)
add_swig_cgal_library(CGAL_Java_cpp ${JAVA_OBJECT_FILES})
ADD_SWIG_CGAL_JAVA_MODULE(Java CGAL_Java_cpp)
