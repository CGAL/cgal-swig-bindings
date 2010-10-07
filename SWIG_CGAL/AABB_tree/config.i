
#define IMPORT_ONLY_POLYHEDRON_TYPES
%include "SWIG_CGAL/Polyhedron_3/config.i"
#undef IMPORT_ONLY_POLYHEDRON_TYPES

%{

#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
#include <CGAL/AABB_polyhedron_segment_primitive.h>
#include <CGAL/AABB_integer_primitive.h>


// Polyhedron Triangle Primitive
typedef CGAL::AABB_polyhedron_triangle_primitive<EPIC_Kernel,Polyhedron_3_>     CGAL_PTP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_PTP>                                CGAL_PTP_T;
typedef CGAL::AABB_tree<CGAL_PTP_T>                                             CGAL_PTP_Tree;
// Polyhedron Segment Primitive
typedef CGAL::AABB_polyhedron_segment_primitive<EPIC_Kernel,Polyhedron_3_>      CGAL_PSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_PSP>                                CGAL_PSP_T;
typedef CGAL::AABB_tree<CGAL_PSP_T>                                             CGAL_PSP_Tree;
// Triangle Soup Primitive
typedef CGAL::AABB_integer_primitive<EPIC_Kernel::Triangle_3>                   CGAL_TSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_TSP>                                CGAL_TSP_T;
typedef CGAL::AABB_tree<CGAL_TSP_T>                                             CGAL_TSP_Tree;
// Segment Soup Primitive
typedef CGAL::AABB_integer_primitive<EPIC_Kernel::Segment_3>                    CGAL_SSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_SSP>                                CGAL_SSP_T;
typedef CGAL::AABB_tree<CGAL_SSP_T>                                             CGAL_SSP_Tree;

%}