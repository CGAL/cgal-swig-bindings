#ifndef SWIG_CGAL_DECLARE_TRIANGULATION_2_I
#define SWIG_CGAL_DECLARE_TRIANGULATION_2_I

//Expose a triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  //Handles
  %template(CLASSNAME_PREFIX##_Face_handle)        CGAL_Face_handle<CPPTYPE>;
  %typemap(javaimports) CGAL_Vertex_handle %{import CGAL.Kernel.Point_2;%}
  %template(CLASSNAME_PREFIX##_Vertex_handle)      CGAL_Vertex_handle<CPPTYPE>;

  //Edge
  %include "std_pair.i"
  %template(CLASSNAME_PREFIX##_Edge) std::pair<CGAL_Face_handle<CPPTYPE>,int>;

  //Triangulations
  %typemap(javaimports)          Triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Segment_2; import CGAL.Kernel.Triangle_2; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Triangulation_2_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE>,CGAL_Face_handle<CPPTYPE> >;


  //Iterators and circulators
  Iterator_for_java(CGAL_All_vertices_iterator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.Point_2;)
  %template(CLASSNAME_PREFIX##_All_vertices_iterator) CGAL_All_vertices_iterator<CPPTYPE,CGAL_Vertex_handle<CPPTYPE> >;

  Iterator_for_java(CGAL_Finite_vertices_iterator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.Point_2;)
  %template(CLASSNAME_PREFIX##_Finite_vertices_iterator) CGAL_Finite_vertices_iterator<CPPTYPE,CGAL_Vertex_handle<CPPTYPE> >;

  Iterator_for_java(CGAL_All_faces_iterator,CLASSNAME_PREFIX##_Face_handle,)
  %template(CLASSNAME_PREFIX##_All_faces_iterator) CGAL_All_faces_iterator<CPPTYPE,CGAL_Face_handle<CPPTYPE> >;

  Iterator_for_java(CGAL_Finite_faces_iterator,CLASSNAME_PREFIX##_Face_handle,)
  %template(CLASSNAME_PREFIX##_Finite_faces_iterator) CGAL_Finite_faces_iterator<CPPTYPE,CGAL_Face_handle<CPPTYPE> >;

  Iterator_for_java(CGAL_All_edges_iterator,CLASSNAME_PREFIX##_Edge,)
  %template(CLASSNAME_PREFIX##_All_edges_iterator) CGAL_All_edges_iterator<CPPTYPE,std::pair<CGAL_Face_handle<CPPTYPE>,int> >;

  Iterator_for_java(CGAL_Finite_edges_iterator,CLASSNAME_PREFIX##_Edge,)
  %template(CLASSNAME_PREFIX##_Finite_edges_iterator) CGAL_Finite_edges_iterator<CPPTYPE,std::pair<CGAL_Face_handle<CPPTYPE>,int> >;

  Iterator_for_java(CGAL_Point_iterator,Point_2,import CGAL.Kernel.Point_2;)
  %template(CLASSNAME_PREFIX##_Point_iterator) CGAL_Point_iterator<CPPTYPE,Point_2>;

  Iterator_for_java(CGAL_Line_face_circulator,CLASSNAME_PREFIX##_Face_handle,)
  %template(CLASSNAME_PREFIX##_Line_face_circulator) CGAL_Line_face_circulator<CPPTYPE,CGAL_Face_handle<CPPTYPE> >;

  Iterator_for_java(CGAL_Face_circulator,CLASSNAME_PREFIX##_Face_handle,)
  %template(CLASSNAME_PREFIX##_Face_circulator) CGAL_Face_circulator<CPPTYPE,CGAL_Face_handle<CPPTYPE> >;

  Iterator_for_java(CGAL_Edge_circulator,CLASSNAME_PREFIX##_Edge,)
  %template(CLASSNAME_PREFIX##_Edge_circulator) CGAL_Edge_circulator<CPPTYPE,std::pair<CGAL_Face_handle<CPPTYPE>,int > >;

  Iterator_for_java(CGAL_Edge_circulator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.Point_2;)
  %template(CLASSNAME_PREFIX##_Vertex_circulator) CGAL_Vertex_circulator<CPPTYPE,CGAL_Vertex_handle<CPPTYPE> >;
%enddef

//Expose a triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_triangulation_2(CLASSNAME,CPPTYPE)
  Declare_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_DECLARE_TRIANGULATION_2_I
