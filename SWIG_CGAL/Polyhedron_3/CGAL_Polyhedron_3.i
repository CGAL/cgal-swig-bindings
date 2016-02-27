// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Polyhedron_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Polyhedron_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%import  "SWIG_CGAL/Common/Iterator.h"

%{ 
#include <SWIG_CGAL/Polyhedron_3/all_includes.h> 
%}
#ifdef SWIG_CGAL_Polyhedron_MODULE
#ifdef SWIGJAVA
%include "SWIG_CGAL/Polyhedron_3/java_extensions.i"
#endif

#ifdef SWIGPYTHON
%include "SWIG_CGAL/Polyhedron_3/python_extensions.i"
#endif
#endif

//include files


%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

//definitions
%include "SWIG_CGAL/Polyhedron_3/Polyhedron_3.h"
%include "SWIG_CGAL/Polyhedron_3/polyhedron_3_handles.h"
%include "SWIG_CGAL/Polyhedron_3/general_modifier.h"

//template instantiation
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Halfedge_handle,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>)
#ifndef NO_VERTEX_HANDLE_IMPORTS
%typemap(javaimports)                               SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>%{import CGAL.Kernel.Point_3;%}
#endif
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Vertex_handle,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>)
#ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
%typemap(javaimports)                               SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>%{import CGAL.Kernel.Plane_3;%}
#endif
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Facet_handle,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>)

%typemap(javaimports)                       Polyhedron_3_wrapper %{import CGAL.Kernel.Point_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3,Polyhedron_3_wrapper< Polyhedron_3_,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >)

//general modifier
%typemap(javaimports)       General_modifier<Polyhedron_3_::HalfedgeDS> %{import CGAL.Kernel.Point_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_modifier,General_modifier<Polyhedron_3_::HalfedgeDS>)

//Iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Halfedge_iterator,SWIG_CGAL_Iterator< Polyhedron_3_::Halfedge_iterator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Edge_iterator,SWIG_CGAL_Iterator< Polyhedron_3_::Edge_iterator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Vertex_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Vertex_iterator,SWIG_CGAL_Iterator< Polyhedron_3_::Vertex_iterator,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Polyhedron_3_Facet_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Facet_iterator,SWIG_CGAL_Iterator< Polyhedron_3_::Facet_iterator,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_3,import CGAL.Kernel.Point_3;)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Point_iterator,SWIG_CGAL_Iterator< Polyhedron_3_::Point_iterator,Point_3>)

#ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Plane_3,import CGAL.Kernel.Plane_3;)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Plane_iterator,SWIG_CGAL_Iterator< Polyhedron_3_::Plane_iterator,Plane_3>)
#endif

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator,Polyhedron_3_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Halfedge_around_vertex_circulator,SWIG_CGAL_Circulator< Polyhedron_3_::Halfedge_around_vertex_circulator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator,Polyhedron_3_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Polyhedron_3_Halfedge_around_facet_circulator,SWIG_CGAL_Circulator< Polyhedron_3_::Halfedge_around_facet_circulator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >)

#ifdef SWIG_CGAL_HAS_Polyhedron_3_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Polyhedron_3/extensions.i"
#endif
