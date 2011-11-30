// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Polyhedron_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Polyhedron_3");
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Polyhedron_3 failed to load. \n" + e);
      throw e;
    }
  }
%}


%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%import  "SWIG_CGAL/Common/Iterator.h"

%include "SWIG_CGAL/Polyhedron_3/config.i"
//include files
%{
  #include <SWIG_CGAL/Polyhedron_3/Polyhedron_3.h>
  #include <SWIG_CGAL/Polyhedron_3/polyhedron_3_handles.h>
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

//definitions
%include "SWIG_CGAL/Polyhedron_3/Polyhedron_3.h"
%include "SWIG_CGAL/Polyhedron_3/polyhedron_3_handles.h"
%include "SWIG_CGAL/Polyhedron_3/Modifier_base.h"


//template instantiation
%template(Polyhedron_3_Halfedge_handle)             SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>;
#ifndef NO_VERTEX_HANDLE_IMPORTS
%typemap(javaimports)                               SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>%{import CGAL.Kernel.Point_3;%}
#endif
%template(Polyhedron_3_Vertex_handle)               SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>;
#ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
%typemap(javaimports)                               SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>%{import CGAL.Kernel.Plane_3;%}
#endif
%template(Polyhedron_3_Facet_handle)                SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>;

%typemap(javaimports)                       Polyhedron_3_wrapper %{import CGAL.Kernel.Point_3;%}
%template(Polyhedron_3)                     Polyhedron_3_wrapper< Polyhedron_3_,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >;

%template(Polyhedron_3_Modifier_base)                  Modifier_base< Polyhedron_3_ >;



//Iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Halfedge_iterator) SWIG_CGAL_Iterator< Polyhedron_3_::Halfedge_iterator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Edge_iterator) SWIG_CGAL_Iterator< Polyhedron_3_::Edge_iterator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Vertex_handle,)
%template(Polyhedron_3_Vertex_iterator) SWIG_CGAL_Iterator< Polyhedron_3_::Vertex_iterator,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_> >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Facet_handle,)
%template(Polyhedron_3_Facet_iterator) SWIG_CGAL_Iterator< Polyhedron_3_::Facet_iterator,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_3,import CGAL.Kernel.Point_3;)
%template(Polyhedron_3_Point_iterator) SWIG_CGAL_Iterator< Polyhedron_3_::Point_iterator,Point_3>; 

#ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Plane_3,import CGAL.Kernel.Plane_3;)
%template(Polyhedron_3_Plane_iterator) SWIG_CGAL_Iterator< Polyhedron_3_::Plane_iterator,Plane_3>; 
#endif

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Halfedge_around_vertex_circulator) SWIG_CGAL_Circulator< Polyhedron_3_::Halfedge_around_vertex_circulator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator,Polyhedron_3_Halfedge_handle,)
%template(Polyhedron_3_Halfedge_around_facet_circulator) SWIG_CGAL_Circulator< Polyhedron_3_::Halfedge_around_vertex_circulator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;

