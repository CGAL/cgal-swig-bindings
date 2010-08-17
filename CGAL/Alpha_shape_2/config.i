
//macros defining the underlying types used
%{
//typedefs for Alpha_shape_2
typedef CGAL::Alpha_shape_vertex_base_2<EPIC_Kernel>                    CGAL_AS_vb;
typedef CGAL::Triangulation_face_base_2<EPIC_Kernel>                    CGAL_AS_fbb;
typedef CGAL::Alpha_shape_face_base_2<EPIC_Kernel,CGAL_AS_fbb>          CGAL_AS_fb;
typedef CGAL::Triangulation_data_structure_2<CGAL_AS_vb,CGAL_AS_fb>     CGAL_AS_Tds;
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel,CGAL_AS_Tds>         CGAL_DT2;
typedef CGAL::Alpha_shape_2<CGAL_DT2>                                   CGAL_AS2;
//typedefs for Weighted_alpha_shape_2 
typedef CGAL::Weighted_alpha_shape_euclidean_traits_2<EPIC_Kernel>      CGAL_WAS_Gt;
typedef CGAL::Regular_triangulation_vertex_base_2<CGAL_WAS_Gt>          CGAL_WAS_vbb;
typedef CGAL::Alpha_shape_vertex_base_2<CGAL_WAS_Gt,CGAL_WAS_vbb>       CGAL_WAS_vb;
typedef CGAL::Regular_triangulation_face_base_2<CGAL_WAS_Gt>            CGAL_WAS_fbb;
typedef CGAL::Alpha_shape_face_base_2<CGAL_WAS_Gt, CGAL_WAS_fbb>        CGAL_WAS_fb;
typedef CGAL::Triangulation_data_structure_2<CGAL_WAS_vb,CGAL_WAS_fb>   CGAL_WAS_Tds;
typedef CGAL::Regular_triangulation_2<CGAL_WAS_Gt,CGAL_WAS_Tds>         CGAL_RT2;
typedef CGAL::Alpha_shape_2<CGAL_RT2>                                   CGAL_WAS2;  
%}

//macro to decide which classes to expose
#define SWIG_EXPOSE_ALPHA_SHAPE_2
#define SWIG_EXPOSE_WEIGHTED_ALPHA_SHAPE_2

