%module CGAL_Polyhedron_3


%include "../common.i"
%import  "../Kernel/Point_3.h"
%import  "../Kernel/Plane_3.h"
//%import  "../Kernel/Kernel.i" This is an alternative to the two previous import
%import  "../Common/Macros.h"
%import  "../Common/Input_iterator.h"

//include files
%{
  #include "Polyhedron_3.h"
  #include "polyhedron_3_handles.h"
  #include "polyhedron_3_iterators.h"
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection;%}

//definitions
%include "Polyhedron_3.h"
%include "polyhedron_3_handles.h"
%include "polyhedron_3_iterators.h"
%include "Modifier_base.h"

%include "../Polyhedron_3/config.i"

//template instantiation
%template(Polyhedron_3_Halfedge_handle)             CGAL_Halfedge_handle<Polyhedron_3_>;
#ifndef NO_VERTEX_HANDLE_IMPORTS
%typemap(javaimports)                               CGAL_Vertex_handle<Polyhedron_3_>%{import CGAL.Kernel.Point_3;%}
#endif
%template(Polyhedron_3_Vertex_handle)               CGAL_Vertex_handle<Polyhedron_3_>;
#ifdef CGAL_SWIG_FACET_SUPPORTS_PLANE
%typemap(javaimports)                               CGAL_Facet_handle<Polyhedron_3_>%{import CGAL.Kernel.Plane_3;%}
#endif
%template(Polyhedron_3_Facet_handle)                CGAL_Facet_handle<Polyhedron_3_>;

%typemap(javaimports)                     Polyhedron_3_wrapper %{import CGAL.Kernel.Point_3;%}
%template(Polyhedron_3)                     Polyhedron_3_wrapper< Polyhedron_3_,CGAL_Vertex_handle<Polyhedron_3_>,CGAL_Halfedge_handle<Polyhedron_3_>,CGAL_Facet_handle<Polyhedron_3_> >;

%template(Polyhedron_3_Modifier_base)                  Modifier_base< Polyhedron_3_ >;

//Iterators
Iterator_for_java(CGAL_Halfedge_iterator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Halfedge_iterator) CGAL_Halfedge_iterator< Polyhedron_3_,CGAL_Halfedge_handle<Polyhedron_3_> >;

Iterator_for_java(CGAL_Edge_iterator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Edge_iterator) CGAL_Edge_iterator< Polyhedron_3_,CGAL_Halfedge_handle<Polyhedron_3_> >;

Iterator_for_java(CGAL_Vertex_iterator,Polyhedron_3_Vertex_handle,)
%template(Polyhedron_3_Vertex_iterator) CGAL_Vertex_iterator< Polyhedron_3_,CGAL_Vertex_handle<Polyhedron_3_> >;

Iterator_for_java(CGAL_Facet_iterator,Polyhedron_3_Facet_handle,)
%template(Polyhedron_3_Facet_iterator) CGAL_Facet_iterator< Polyhedron_3_,CGAL_Facet_handle<Polyhedron_3_> >;

Iterator_for_java(CGAL_Point_iterator,Point_3,import CGAL.Kernel.Point_3;)
%template(Polyhedron_3_Point_iterator) CGAL_Point_iterator< Polyhedron_3_,Point_3>; 

#ifdef CGAL_SWIG_FACET_SUPPORTS_PLANE
Iterator_for_java(CGAL_Plane_iterator,Plane_3,import CGAL.Kernel.Plane_3;)
%template(Polyhedron_3_Plane_iterator) CGAL_Plane_iterator< Polyhedron_3_,Plane_3>; 
#endif

Iterator_for_java(CGAL_Halfedge_around_vertex_circulator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Halfedge_around_vertex_circulator) CGAL_Halfedge_around_vertex_circulator< Polyhedron_3_,CGAL_Halfedge_handle<Polyhedron_3_> >;

Iterator_for_java(CGAL_Halfedge_around_facet_circulator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Halfedge_around_facet_circulator) CGAL_Halfedge_around_facet_circulator< Polyhedron_3_,CGAL_Halfedge_handle<Polyhedron_3_> >;

