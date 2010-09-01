%module CGAL_Surface_mesher


%include "../common.i"
%import  "../Common/Macros.h"
%import  "../Kernel/Point_3.h"
%import  "../Kernel/Segment_3.h"
%import  "../Kernel/Tetrahedron_3.h"
%import  "../Kernel/Triangle_3.h"
%import  "../Kernel/enum.h"
%include "../Common/Input_iterator.h"

%include "config.i"

//include files
%{
  #include "../Triangulation_3/Delaunay_triangulation_3.h"
  #include "../Triangulation_3/Triangulation_3.h"
  #include "../Triangulation_3/triangulation_handles.h"
  #include "../Common/triple.h"
  #include "../Triangulation_3/triangulation_iterators.h"
  #include "C2T3.h"
%}

//definitions
%include "../Triangulation_3/triangulation_handles.h"
%include "../Triangulation_3/Triangulation_3.h"
%include "../Triangulation_3/Delaunay_triangulation_3.h"
%include "../Triangulation_3/triangulation_iterators.h"
%include "../Common/triple.h"
%include "C2T3.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection;%}


%import "../Triangulation_3/declare_Delaunay_triangulation_3.i"
Declare_Delaunay_triangulation_3(Surface_mesh_default_triangulation_3,C2T3_DT)

//typemap for output iterator
%define Complex_2_in_triangulation_3_Facet_output_iterator  C2T3_internal::Iterator_helper<Delaunay_triangulation_3_wrapper<C2T3_DT,CGAL_Vertex_handle<C2T3_DT,Point_3>,CGAL_Cell_handle<C2T3_DT,Point_3> > >::output %enddef
%{
typedef std::pair< CGAL_Cell_handle<C2T3_DT,Point_3>,int >                              Surface_mesh_default_triangulation_3_Facet;
%}
Typemap_for_Output_iterator(Complex_2_in_triangulation_3_Facet_output_iterator,Surface_mesh_default_triangulation_3_Facet,Surface_mesh_default_triangulation_3_Facet,C2T3_DT::Facet,SWIGTYPE_p_std__pairT_CGAL_Cell_handleT_C2T3_DT_Point_3_t_int_t,"LCGAL/Surface_mesher/Surface_mesh_default_triangulation_3_Facet;")

//iterators
Iterator_for_java(CGAL_Vertex_iterator,Surface_mesh_default_triangulation_3_Vertex_handle,import CGAL.Kernel.Point_3;)
%template(Surface_mesher_Complex_2_in_triangulation_3_CGAL_Vertex_iterator) CGAL_Vertex_iterator<C2T3,CGAL_Vertex_handle<C2T3_DT,Point_3> >;

Iterator_for_java(CGAL_Facet_iterator,Surface_mesh_default_triangulation_3_Facet,)
%template(Surface_mesh_default_triangulation_3_Facet_iterator) CGAL_Facet_iterator<C2T3,std::pair<CGAL_Cell_handle<C2T3_DT,Point_3>,int> >;

Iterator_for_java(CGAL_Edge_iterator,Surface_mesh_default_triangulation_3_Edge,)
%template(Surface_mesh_default_triangulation_3_Edge_iterator) CGAL_Edge_iterator<C2T3,CGAL_SWIG::Triple<CGAL_Cell_handle<C2T3_DT,Point_3>,int,int> >;

Iterator_for_java(CGAL_Boundary_edges_iterator,Surface_mesh_default_triangulation_3_Edge,)
%template(Surface_mesh_default_triangulation_3_Boundary_edges_iterator) CGAL_Boundary_edges_iterator<C2T3,CGAL_SWIG::Triple<CGAL_Cell_handle<C2T3_DT,Point_3>,int,int> >;


%template (Complex_2_in_triangulation_3) C2T3_wrapper<C2T3,Delaunay_triangulation_3_wrapper<C2T3_DT,CGAL_Vertex_handle<C2T3_DT,Point_3>,CGAL_Cell_handle<C2T3_DT,Point_3> > >;
