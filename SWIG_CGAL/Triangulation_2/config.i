#ifdef SWIGJAVA
#define ADD_JAVA_DATA_IN_FACET_CDT_PLUS_2 //define this variable to add a jobject in faces of CDT_plus_2
#define ADD_JAVA_DATA_IN_SIMPLICES_DT2 //define this variable to add a jobject in faces and vertices of DT2
%{
#define ADD_JAVA_DATA_IN_FACET_CDT_PLUS_2 
#define  ADD_JAVA_DATA_IN_SIMPLICES_DT2
%}
#endif



#ifdef ADD_JAVA_DATA_IN_FACET_CDT_PLUS_2
#define NEED_JAVA_DATA_IMPORT
#else
  #ifdef ADD_JAVA_DATA_IN_SIMPLICES_DT2
    #define NEED_JAVA_DATA_IMPORT
  #endif
#endif


#ifdef NEED_JAVA_DATA_IMPORT
%import "SWIG_CGAL/Java/JavaData.h"
%import "SWIG_CGAL/Java/Macro.i"
%{
#include <SWIG_CGAL/Java/JavaData.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
%}
#endif


#ifdef ADD_JAVA_DATA_IN_FACET_CDT_PLUS_2
//assign JavaData to Face_handle of CGAL_CDTplus2
#define i_Face_handle_CDT2_plus   SWIG_Triangulation_2::CGAL_Face_handle<CGAL_CDTplus2,Point_2>
#define i_Vertex_handle_CDT2_plus SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_CDTplus2,Point_2>
add_JavaData_info_to_class(i_Face_handle_CDT2_plus,)
add_JavaData_info_to_class(i_Vertex_handle_CDT2_plus,import CGAL.Kernel.Point_2;)
#endif


#ifdef ADD_JAVA_DATA_IN_SIMPLICES_DT2
//assign JavaData to Face_handle of CGAL_CDTplus2
#define i_Face_handle_DT2 SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>
#define i_Vertex_handle_DT2 SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>
add_JavaData_info_to_class(i_Face_handle_DT2,)
add_JavaData_info_to_class(i_Vertex_handle_DT2,import CGAL.Kernel.Point_2;)
#endif

//macros defining the underlying types used
%{
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>  
  
typedef CGAL::Triangulation_2<EPIC_Kernel>                                  CGAL_T2;
#ifdef ADD_JAVA_DATA_IN_SIMPLICES_DT2
typedef CGAL::Triangulation_vertex_base_with_info_2<JavaData,EPIC_Kernel>   Vbase_DT2;
typedef CGAL::Triangulation_face_base_with_info_2<JavaData,EPIC_Kernel>     Fbase_DT2;
typedef CGAL::Triangulation_data_structure_2<Vbase_DT2,Fbase_DT2>           TDS_DT2;
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel,TDS_DT2>                 CGAL_DT2;
#else
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel>                         CGAL_DT2;
#endif
typedef CGAL::Regular_triangulation_euclidean_traits_2<EPIC_Kernel>         CGAL_regular_traits;
typedef CGAL::Regular_triangulation_2<CGAL_regular_traits>                  CGAL_RT2;
typedef CGAL::Constrained_triangulation_2<EPIC_Kernel>                      CGAL_CT2;
typedef CGAL::Constrained_Delaunay_triangulation_2<EPIC_Kernel>             CGAL_CDT2;
#ifndef ADD_JAVA_DATA_IN_FACET_CDT_PLUS_2
typedef CGAL::Constrained_triangulation_plus_2<CGAL_CDT2>                   CGAL_CDTplus2;
#else
#include  <CGAL/Triangulation_face_base_with_info_2.h>  
typedef CGAL::Triangulation_vertex_base_2<EPIC_Kernel>                      Vb;
typedef CGAL::Triangulation_face_base_with_info_2<JavaData,EPIC_Kernel>     Fbi;
typedef CGAL::Constrained_triangulation_face_base_2<EPIC_Kernel, Fbi>       Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>                         TDS;
typedef CGAL::Exact_intersections_tag                                       Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<EPIC_Kernel, TDS, Itag>  CDT;
typedef CGAL::Constrained_triangulation_plus_2<CDT>                         CGAL_CDTplus2;  
#endif
typedef std::pair<Point_2::cpp_base,Point_2::cpp_base>                      iConstraint;
%}

//macro to decide which class to expose
#define SWIG_EXPOSE_TRIANGULATION_2
#define SWIG_EXPOSE_DELAUNAY_TRIANGULATION_2
#define SWIG_EXPOSE_REGULAR_TRIANGULATION_2
#define SWIG_EXPOSE_CONSTRAINED_TRIANGULATION_2
#define SWIG_EXPOSE_CONSTRAINED_DELAUNAY_TRIANGULATION_2
#define SWIG_EXPOSE_CONSTRAINED_DELAUNAY_TRIANGULATION_PLUS_2


