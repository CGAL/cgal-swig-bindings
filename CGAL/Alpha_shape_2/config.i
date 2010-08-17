
//macros defining the underlying types used
%{
typedef CGAL::Alpha_shape_vertex_base_2<EPIC_Kernel>            CGAL_AS_vb;
typedef CGAL::Triangulation_face_base_2<EPIC_Kernel>            CGAL_AS_fbb;
typedef CGAL::Alpha_shape_face_base_2<EPIC_Kernel,CGAL_AS_fbb>  CGAL_AS_fb;
typedef CGAL::Triangulation_default_data_structure_2
          <EPIC_Kernel,CGAL_AS_vb,CGAL_AS_fb>                   Tds;
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel,Tds>         CGAL_DT2;
typedef CGAL::Alpha_shape_2<CGAL_DT2>                           CGAL_AS2;
%}

//macro to decide which class to expose
#define SWIG_EXPOSE_ALPHA_SHAPE_2

