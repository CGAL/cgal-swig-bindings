%{

#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
#include <CGAL/AABB_polyhedron_segment_primitive.h>
#include <CGAL/AABB_triangle_primitive.h>
#include <CGAL/AABB_segment_primitive.h>  

//TEMPORAIRE
#include "../Java/JavaData.h"
#include "../Polyhedron_3/Polyhedron_items_with_id_and_info_3.h"
typedef CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_and_info_3<JavaData> > Polyhedron_3_;
typedef CGAL_Facet_handle<Polyhedron_3_> Polyhedron_3_Facet_handle;
  
// Polyhedron Triangle Primitive
typedef CGAL::AABB_polyhedron_triangle_primitive<EPIC_Kernel,Polyhedron_3_>     CGAL_PTP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_PTP>                                CGAL_PTP_T;
typedef CGAL::AABB_tree<CGAL_PTP_T>                                             CGAL_PTP_Tree;
// Polyhedron Segment Primitive
typedef CGAL::AABB_polyhedron_segment_primitive<EPIC_Kernel,Polyhedron_3_>      CGAL_PSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_PSP>                                CGAL_PSP_T;
typedef CGAL::AABB_tree<CGAL_PSP_T>                                             CGAL_PSP_Tree;
// Triangle Soup Primitive
typedef std::list<Triangle_3>::iterator                                         TMP_Iterator;
typedef CGAL::AABB_triangle_primitive<EPIC_Kernel,TMP_Iterator>                 CGAL_TSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_TSP>                                CGAL_TSP_T;
typedef CGAL::AABB_tree<CGAL_TSP_T>                                             CGAL_TSP_Tree;
// Segment Soup Primitive
typedef std::list<Segment_3>::iterator                                          TMP_Iterator1;
typedef CGAL::AABB_segment_primitive<EPIC_Kernel,TMP_Iterator1>                 CGAL_SSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_SSP>                                CGAL_SSP_T;
typedef CGAL::AABB_tree<CGAL_SSP_T>                                             CGAL_SSP_Tree;

%}