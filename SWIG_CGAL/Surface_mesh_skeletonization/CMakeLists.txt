SET (LIBSTOLINKWITH CGAL_Kernel_cpp CGAL::Eigen3_support)
if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()
# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Surface_mesh_skeletonization ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_PYTHON_MODULE ( Surface_mesh_skeletonization ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_RUBY_MODULE   ( Surface_mesh_skeletonization ${LIBSTOLINKWITH} )
