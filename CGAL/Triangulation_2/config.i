#ifdef SWIGJAVA
#define ADD_JAVA_DATA_IN_FACET //define this variable to add a jobject in faces of CDT_plus_2
%{ #define ADD_JAVA_DATA_IN_FACET %}
#endif



#ifdef ADD_JAVA_DATA_IN_FACET
%import "../Java/JavaData.h"
%import "../Java/Macro.i"
%{
#include "../Java/JavaData.h"
%}
//assign JavaData to Face_handle of CGAL_CDTplus2
#define i_Face_handle CGAL_Face_handle<CGAL_CDTplus2,Point_2>
add_JavaData_info_to_class(i_Face_handle,)
#endif

//macros defining the underlying types used
%{
typedef CGAL::Triangulation_2<EPIC_Kernel>                                  CGAL_T2;
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel>                         CGAL_DT2;
typedef CGAL::Regular_triangulation_euclidean_traits_2<EPIC_Kernel>         CGAL_regular_traits;
typedef CGAL::Regular_triangulation_2<CGAL_regular_traits>                  CGAL_RT2;
typedef CGAL::Constrained_triangulation_2<EPIC_Kernel>                      CGAL_CT2;
typedef CGAL::Constrained_Delaunay_triangulation_2<EPIC_Kernel>             CGAL_CDT2;
#ifndef ADD_JAVA_DATA_IN_FACET
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
%}

//macro to decide which class to expose
#define SWIG_EXPOSE_TRIANGULATION_2
#define SWIG_EXPOSE_DELAUNAY_TRIANGULATION_2
#define SWIG_EXPOSE_REGULAR_TRIANGULATION_2
#define SWIG_EXPOSE_CONSTRAINED_TRIANGULATION_2
#define SWIG_EXPOSE_CONSTRAINED_DELAUNAY_TRIANGULATION_2
#define SWIG_EXPOSE_CONSTRAINED_DELAUNAY_TRIANGULATION_PLUS_2


