SET (OBJECT_FILES "Point_2.cpp" "Weighted_point_2.cpp" "Segment_2.cpp" "Triangle_2.cpp" "Ray_2.cpp" "Direction_2.cpp" "Line_2.cpp" "Vector_2.cpp" "Polygon_2.cpp" "Bbox_2.cpp")
SET (OBJECT_FILES ${OBJECT_FILES} "Point_3.cpp" "Weighted_point_3.cpp" "Sphere_3.cpp" "Plane_3.cpp" "Segment_3.cpp" "Line_3.cpp" "Triangle_3.cpp" "Tetrahedron_3.cpp" "Direction_3.cpp" "Ray_3.cpp" "Vector_3.cpp" "Bbox_3.cpp")
SET (OBJECT_FILES ${OBJECT_FILES} "Object.cpp" "global_functions.cpp" "Origin.cpp" "Iso_rectangle_2.cpp")

if (TBB_FOUND)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
endif()

# cpp common library
add_swig_cgal_library( CGAL_Kernel_cpp ${OBJECT_FILES} )

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Kernel CGAL_Kernel_cpp ${LIBSTOLINKWITH})
ADD_SWIG_CGAL_PYTHON_MODULE ( Kernel CGAL_Kernel_cpp ${LIBSTOLINKWITH})
ADD_SWIG_CGAL_RUBY_MODULE   ( Kernel CGAL_Kernel_cpp ${LIBSTOLINKWITH})
