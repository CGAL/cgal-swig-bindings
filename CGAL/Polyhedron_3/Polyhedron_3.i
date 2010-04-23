%module Polyhedron_3

//config.i
//===============================
%{#define CGAL_SWIG_FACET_WITH_SUPPORT_PLANE%}
#define CGAL_SWIG_FACET_WITH_SUPPORT_PLANE

%define Polyhedron_3_
CGAL::Polyhedron_3<EPIC_Kernel>
%enddef

//~ %define Polyhedron_3_
//~ CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_3>
//~ %enddef

%define Halfedge_handle_
CGAL_Halfedge_handle<Polyhedron_3_> 
%enddef

%define Vertex_handle_
CGAL_Vertex_handle<Polyhedron_3_> 
%enddef

%define Facet_handle_
CGAL_Facet_handle<Polyhedron_3_>
%enddef
//===============================

%include "../common.i"
%import  "../Kernel/Point_3.h"
%import  "../Kernel/Plane_3.h"
%import  "../Common/Macros.h"
%import  "../Common/Input_iterator.h"

//include files
%{
  #include "Polyhedron_3.h"
  #include "polyhedron_3_handles.h"
  #include "polyhedron_3_iterators.h"
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3;%}


//definitions
%include "Polyhedron_3.h"
%include "polyhedron_3_handles.h"
%include "polyhedron_3_iterators.h"


//template instantiation
%template(Polyhedron_3_Halfedge_handle)             Halfedge_handle_;
%typemap(javaimports)                               CGAL_Vertex_handle%{import CGAL.Kernel.Point_3;%}
%template(Polyhedron_3_Vertex_handle)               Vertex_handle_;
%typemap(javaimports)                               CGAL_Facet_handle%{import CGAL.Kernel.Plane_3;%}
%template(Polyhedron_3_Facet_handle)                Facet_handle_;

%typemap(javaimports)                     Polyhedron_3 %{import CGAL.Kernel.Point_3;%}
%template(Polyhedron)                     Polyhedron_3< Polyhedron_3_,Vertex_handle_,Halfedge_handle_,Facet_handle_ >;

//Iterators
Iterator_for_java(CGAL_Halfedge_iterator,Polyhedron_3_Halfedge_handle,;)
%template(Polyhedron_3_Halfedge_iterator) CGAL_Halfedge_iterator< Polyhedron_3_,Halfedge_handle_ >;

Iterator_for_java(CGAL_Edge_iterator,Polyhedron_3_Halfedge_handle,;)
%template(Polyhedron_3_Edge_iterator) CGAL_Edge_iterator< Polyhedron_3_,Halfedge_handle_ >;

Iterator_for_java(CGAL_Vertex_iterator,Polyhedron_3_Vertex_handle,;)
%template(Polyhedron_3_Vertex_iterator) CGAL_Vertex_iterator< Polyhedron_3_,Vertex_handle_ >;

Iterator_for_java(CGAL_Facet_iterator,Polyhedron_3_Facet_handle,;)
%template(Polyhedron_3_Facet_iterator) CGAL_Facet_iterator< Polyhedron_3_,Facet_handle_ >;

Iterator_for_java(CGAL_Point_iterator,Point_3,import CGAL.Kernel.Point_3;)
%template(Polyhedron_3_Point_iterator) CGAL_Point_iterator< Polyhedron_3_,Point_3>; 

#ifdef CGAL_SWIG_FACET_WITH_SUPPORT_PLANE
Iterator_for_java(CGAL_Plane_iterator,Plane_3,import CGAL.Kernel.Plane_3;)
%template(Polyhedron_3_Plane_iterator) CGAL_Plane_iterator< Polyhedron_3_,Plane_3>; 
#endif

Iterator_for_java(CGAL_Halfedge_around_vertex_circulator,Polyhedron_3_Halfedge_handle,;)
%template(Polyhedron_3_Halfedge_around_vertex_circulator) CGAL_Halfedge_around_vertex_circulator< Polyhedron_3_,Halfedge_handle_ >;

Iterator_for_java(CGAL_Halfedge_around_facet_circulator,Polyhedron_3_Halfedge_handle,;)
%template(Polyhedron_3_Halfedge_around_facet_circulator) CGAL_Halfedge_around_facet_circulator< Polyhedron_3_,Halfedge_handle_ >;

