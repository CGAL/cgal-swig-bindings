%module CGAL_Triangulation_2

%include "../common.i"
%import  "../Common/Macros.h"
%include "../Common/Input_iterator.h"

//include files
%{
  #include "Triangulation_2.h"
  #include "Delaunay_triangulation_2.h"
  #include "Regular_triangulation_2.h"
  #include "Constrained_triangulation_2.h"
  #include "Constrained_Delaunay_triangulation_2.h"
  #include "Constrained_triangulation_plus_2.h"
  #include "triangulation_handles.h"
  #include "triangulation_iterators.h"
%}

//definitions
%include "Triangulation_2.h"
%include "Delaunay_triangulation_2.h"
%include "Regular_triangulation_2.h"
%include "Constrained_triangulation_2.h"
%include "Constrained_Delaunay_triangulation_2.h"
%include "Constrained_triangulation_plus_2.h"
%include "triangulation_handles.h"
%include "triangulation_iterators.h"

Typemap_for_Input_iterator(Point_range,Point_2,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert_range)


//Handles
%template(Triangulation_2_Face_handle)        CGAL_Face_handle<EPIC_T2>;
%typemap(javaimports) CGAL_Vertex_handle %{import CGAL.Kernel.Point_2;%}
%template(Triangulation_2_Vertex_handle)      CGAL_Vertex_handle<EPIC_T2>;

//Edge
%include "std_pair.i"
%template(Triangulation_2_Edge) std::pair<CGAL_Face_handle<EPIC_T2>,int>;

//Constraint
%template(CT_Constraint) std::pair<Point_2,Point_2>;

//Triangulations
%typemap(javaimports) Triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Segment_2; import CGAL.Kernel.Triangle_2; import java.util.Iterator; import java.util.Collection;%}
%template(T2)         Triangulation_2_wrapper<EPIC_T2,CGAL_Vertex_handle<EPIC_T2>,CGAL_Face_handle<EPIC_T2> >;


//Iterators and circulators
Iterator_for_java(CGAL_All_vertices_iterator,Triangulation_2_Vertex_handle,import CGAL.Kernel.Point_2;)
%template(Triangulation_2_All_vertices_iterator) CGAL_All_vertices_iterator<EPIC_T2,CGAL_Vertex_handle<EPIC_T2> >;

Iterator_for_java(CGAL_Finite_vertices_iterator,Triangulation_2_Vertex_handle,import CGAL.Kernel.Point_2;)
%template(Triangulation_2_Finite_vertices_iterator) CGAL_Finite_vertices_iterator<EPIC_T2,CGAL_Vertex_handle<EPIC_T2> >;

Iterator_for_java(CGAL_All_faces_iterator,Triangulation_2_Face_handle,)
%template(Triangulation_2_All_faces_iterator) CGAL_All_faces_iterator<EPIC_T2,CGAL_Face_handle<EPIC_T2> >;

Iterator_for_java(CGAL_Finite_faces_iterator,Triangulation_2_Face_handle,)
%template(Triangulation_2_Finite_faces_iterator) CGAL_Finite_faces_iterator<EPIC_T2,CGAL_Face_handle<EPIC_T2> >;

Iterator_for_java(CGAL_All_edges_iterator,Triangulation_2_Edge,)
%template(Triangulation_2_All_edges_iterator) CGAL_All_edges_iterator<EPIC_T2,std::pair<CGAL_Face_handle<EPIC_T2>,int> >;

Iterator_for_java(CGAL_Finite_edges_iterator,Triangulation_2_Edge,)
%template(Triangulation_2_Finite_edges_iterator) CGAL_Finite_edges_iterator<EPIC_T2,std::pair<CGAL_Face_handle<EPIC_T2>,int> >;

Iterator_for_java(CGAL_Point_iterator,Point_2,import CGAL.Kernel.Point_2;)
%template(Triangulation_2_Point_iterator) CGAL_Point_iterator<EPIC_T2,Point_2>;

Iterator_for_java(CGAL_Line_face_circulator,Triangulation_2_Face_handle,)
%template(Triangulation_3_Line_face_circulator) CGAL_Line_face_circulator<EPIC_T2,CGAL_Face_handle<EPIC_T2> >;

Iterator_for_java(CGAL_Face_circulator,Triangulation_2_Face_handle,)
%template(Triangulation_3_Face_circulator) CGAL_Face_circulator<EPIC_T2,CGAL_Face_handle<EPIC_T2> >;

Iterator_for_java(CGAL_Edge_circulator,Triangulation_2_Edge,)
%template(Triangulation_3_Edge_circulator) CGAL_Edge_circulator<EPIC_T2,std::pair<CGAL_Face_handle<EPIC_T2>,int > >;

Iterator_for_java(CGAL_Edge_circulator,Triangulation_2_Vertex_handle,import CGAL.Kernel.Point_2;)
%template(Triangulation_3_Vertex_circulator) CGAL_Vertex_circulator<EPIC_T2,CGAL_Vertex_handle<EPIC_T2> >;

