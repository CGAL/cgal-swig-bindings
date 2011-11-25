#ifndef SWIG_CGAL_TRIANGULATION_3_DECLARE_TRIANGULATION_3_I
#define SWIG_CGAL_TRIANGULATION_3_DECLARE_TRIANGULATION_3_I

//Expose a triangulation_3
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
// --WTAG is CGAL::Tag_false if the cpp triangulation is not weighted and CGAL::Tag_true otherwise
// --MEMHOLDER is used if the triangulation pointer is hold by another class, it is a shared_ptr in that case and void* otherwise
%define Declare_triangulation_3_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,POINT_TYPE,WTAG,MEMHOLDER)
  //Handles
  %template(CLASSNAME_PREFIX##_Cell_handle)        SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>;
  %typemap(javaimports) SWIG_Triangulation_3::CGAL_Vertex_handle %{import CGAL.Kernel.POINT_TYPE;%}
  %template(CLASSNAME_PREFIX##_Vertex_handle)      SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>;

  %include "std_pair.i"
  %template(CLASSNAME_PREFIX##_Facet) std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int>;
  %template(CLASSNAME_PREFIX##_Edge)  SWIG_CGAL::Triple<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int,int>;

  //typemaps for Output iterators
  %define CLASSNAME_PREFIX##_Cell_handle_output_iterator  Triangulation_3_wrapper<CPPTYPE,POINT_TYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,WTAG,MEMHOLDER >::Cell_handle_output_iterator %enddef
  %define CLASSNAME_PREFIX##_Vertex_handle_output_iterator  Triangulation_3_wrapper<CPPTYPE,POINT_TYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,WTAG,MEMHOLDER >::Vertex_handle_output_iterator %enddef
  %define CLASSNAME_PREFIX##_Facet_output_iterator  Triangulation_3_wrapper<CPPTYPE,POINT_TYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,WTAG,MEMHOLDER >::Facet_output_iterator %enddef
  %define CLASSNAME_PREFIX##_Edge_output_iterator  Triangulation_3_wrapper<CPPTYPE,POINT_TYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,WTAG,MEMHOLDER >::Edge_output_iterator %enddef
  %{
  typedef SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>                              CLASSNAME_PREFIX##_Cell_handle;
  typedef SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>                            CLASSNAME_PREFIX##_Vertex_handle;
  typedef std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int>               CLASSNAME_PREFIX##_Facet;
  typedef SWIG_CGAL::Triple<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int,int>   CLASSNAME_PREFIX##_Edge;  
  %}
  SWIG_CGAL_output_iterator_typemap_in(CLASSNAME_PREFIX##_Cell_handle_output_iterator,CLASSNAME_PREFIX##_Cell_handle,CLASSNAME_PREFIX##_Cell_handle,CPPTYPE::Cell_handle,SWIGTYPE_p_SWIG_Triangulation_3__CGAL_Cell_handleT_##CPPTYPE##_##POINT_TYPE##_t,"LCGAL/Triangulation_3/" #CLASSNAME_PREFIX "_Cell_handle;")
  SWIG_CGAL_output_iterator_typemap_in(CLASSNAME_PREFIX##_Vertex_handle_output_iterator,CLASSNAME_PREFIX##_Vertex_handle,CLASSNAME_PREFIX##_Vertex_handle,CPPTYPE::Vertex_handle,SWIGTYPE_p_SWIG_Triangulation_3__CGAL_Vertex_handleT_##CPPTYPE##_##POINT_TYPE##_t,"LCGAL/Triangulation_3/" #CLASSNAME_PREFIX "_Vertex_handle;")
  SWIG_CGAL_output_iterator_typemap_in(CLASSNAME_PREFIX##_Edge_output_iterator,CLASSNAME_PREFIX##_Edge,CLASSNAME_PREFIX##_Edge,CPPTYPE::Edge,SWIGTYPE_p_SWIG_CGAL__TripleT_SWIG_Triangulation_3__CGAL_Cell_handleT_##CPPTYPE##_##POINT_TYPE##_t_int_int_t,"LCGAL/Triangulation_3/" #CLASSNAME_PREFIX "_Edge;")
  SWIG_CGAL_output_iterator_typemap_in(CLASSNAME_PREFIX##_Facet_output_iterator,CLASSNAME_PREFIX##_Facet,CLASSNAME_PREFIX##_Facet,CPPTYPE::Facet,SWIGTYPE_p_std__pairT_SWIG_Triangulation_3__CGAL_Cell_handleT_##CPPTYPE##_##POINT_TYPE##_t_int_t,"LCGAL/Triangulation_3/" #CLASSNAME_PREFIX "_Facet;")

  //Triangulation
  %typemap(javaimports)  Triangulation_3_wrapper%{import CGAL.Kernel.POINT_TYPE;import CGAL.Kernel.Segment_3; import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Tetrahedron_3; import CGAL.Kernel.Ref_int; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME) Triangulation_3_wrapper<CPPTYPE,POINT_TYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,WTAG,MEMHOLDER >;


  //Iterators and circulators
  SWIG_CGAL_set_as_java_iterator(CGAL_All_vertices_iterator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.POINT_TYPE;)
  %template(CLASSNAME_PREFIX##_All_vertices_iterator) CGAL_All_vertices_iterator<CPPTYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_Finite_vertices_iterator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.POINT_TYPE;)
  %template(CLASSNAME_PREFIX##_Finite_vertices_iterator) CGAL_Finite_vertices_iterator<CPPTYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_All_cells_iterator,CLASSNAME_PREFIX##_Cell_handle,)
  %template(CLASSNAME_PREFIX##_All_cells_iterator) CGAL_All_cells_iterator<CPPTYPE,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_Finite_cells_iterator,CLASSNAME_PREFIX##_Cell_handle,)
  %template(CLASSNAME_PREFIX##_Finite_cells_iterator) CGAL_Finite_cells_iterator<CPPTYPE,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_All_facets_iterator,CLASSNAME_PREFIX##_Facet,)
  %template(CLASSNAME_PREFIX##_All_facets_iterator) CGAL_All_facets_iterator<CPPTYPE,std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_Finite_facets_iterator,CLASSNAME_PREFIX##_Facet,)
  %template(CLASSNAME_PREFIX##_Finite_facets_iterator) CGAL_Finite_facets_iterator<CPPTYPE,std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_All_edges_iterator,CLASSNAME_PREFIX##_Edge,)
  %template(CLASSNAME_PREFIX##_All_edges_iterator) CGAL_All_edges_iterator<CPPTYPE,SWIG_CGAL::Triple<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int,int> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_Finite_edges_iterator,CLASSNAME_PREFIX##_Edge,)
  %template(CLASSNAME_PREFIX##_Finite_edges_iterator) CGAL_Finite_edges_iterator<CPPTYPE,SWIG_CGAL::Triple<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int,int> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_Point_iterator,POINT_TYPE,import CGAL.Kernel.POINT_TYPE;)
  %template(CLASSNAME_PREFIX##_Point_iterator) CGAL_Point_iterator<CPPTYPE,POINT_TYPE>;

  SWIG_CGAL_set_as_java_iterator(CGAL_Cell_circulator,CLASSNAME_PREFIX##_Cell_handle,)
  %template(CLASSNAME_PREFIX##_Cell_circulator) CGAL_Cell_circulator<CPPTYPE,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE> >;

  SWIG_CGAL_set_as_java_iterator(CGAL_Facet_circulator,CLASSNAME_PREFIX##_Facet,)
  %template(CLASSNAME_PREFIX##_Facet_circulator) CGAL_Facet_circulator<CPPTYPE,std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,POINT_TYPE>,int> >;
%enddef

//Expose a triangulation_3
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
%define Declare_triangulation_3(CLASSNAME,CPPTYPE)
  Declare_triangulation_3_internal(CLASSNAME,CLASSNAME,CPPTYPE,Point_3,CGAL::Tag_false,void*)
%enddef

//Expose a triangulation_3 with a memory holder
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
// --MEMHOLDER is used if the triangulation pointer is hold by another class
%define Declare_triangulation_3_with_memory_holder(CLASSNAME,CPPTYPE,MEMHOLDER)
  Declare_triangulation_3_internal(CLASSNAME,CLASSNAME,CPPTYPE,Point_3,CGAL::Tag_false,MEMHOLDER)
%enddef

#endif // SWIG_CGAL_TRIANGULATION_3_DECLARE_TRIANGULATION_3_I
