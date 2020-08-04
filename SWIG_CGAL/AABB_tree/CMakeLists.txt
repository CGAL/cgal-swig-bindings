SET (LIBSTOLINKWITH CGAL_Kernel_cpp)
if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()
include_directories(include)
if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()
# cpp common library
ADD_SWIG_CGAL_LIBRARY ( CGAL_AABB_tree_cpp Object.cpp ${LIBSTOLINKWITH} )

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( AABB_tree  ${LIBSTOLINKWITH} CGAL_AABB_tree_cpp )
ADD_SWIG_CGAL_PYTHON_MODULE ( AABB_tree  ${LIBSTOLINKWITH} CGAL_AABB_tree_cpp )
ADD_SWIG_CGAL_RUBY_MODULE   ( AABB_tree  ${LIBSTOLINKWITH} CGAL_AABB_tree_cpp )
