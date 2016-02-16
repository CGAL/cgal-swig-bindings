// ------------------------------------------------------------------------------
// Copyright (c) 2013 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


%module (package="CGAL") CGAL_HalfedgeDS

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_HalfedgeDS)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include  "SWIG_CGAL/Common/Iterator.h"

%{
#include <SWIG_CGAL/HalfedgeDS/typedefs.h>
#include <SWIG_CGAL/HalfedgeDS/all_includes.h>
%}

//include files


%pragma(java) jniclassimports=%{
  import java.util.Iterator;
  import java.util.Collection;
  import CGAL.Kernel.Point_2;
%}

//definitions
%include "SWIG_CGAL/HalfedgeDS/HalfedgeDS.h"
%include "SWIG_CGAL/HalfedgeDS/HalfedgeDS_handles.h"
%include "SWIG_CGAL/HalfedgeDS/HalfedgeDS_decorator.h"
%include "SWIG_CGAL/HalfedgeDS/General_modifier.h"

//template instantiations of handles
SWIG_CGAL_declare_identifier_of_template_class(HDS_Halfedge_handle,HDSHalfedge_wrapper<HDS_d>)
SWIG_CGAL_declare_identifier_of_template_class(HDS_Face_handle,HDSFace_wrapper<HDS_d>)
%typemap(javaimports)                       HDSVertex_wrapper %{import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(HDS_Vertex_handle,HDSVertex_wrapper<HDS_d>)

//Iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,HDS_Vertex_handle,)
SWIG_CGAL_declare_identifier_of_template_class(HDS_Vertex_iterator,SWIG_CGAL_Iterator< HDS_d::Vertex_iterator, HDSVertex_wrapper<HDS_d> >)
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,HDS_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(HDS_Halfedge_iterator,SWIG_CGAL_Iterator< HDS_d::Halfedge_iterator, HDSHalfedge_wrapper<HDS_d> >)
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,HDS_Face_handle,)
SWIG_CGAL_declare_identifier_of_template_class(HDS_Face_iterator,SWIG_CGAL_Iterator< HDS_d::Face_iterator, HDSFace_wrapper<HDS_d> >)

//general modifier for convenience
%typemap(javaimports)       General_modifier<HDS_d> %{import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(HalfedgeDS_modifier,General_modifier<HDS_d>)
// template instantiation of HDS class
%typemap(javaimports)                       HalfedgeDS_wrapper %{import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(HalfedgeDS,HalfedgeDS_wrapper<HDS_d>)
// template instantiation of HDS decorator class
%typemap(javaimports)                       HalfedgeDS_decorator_wrapper %{import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(HalfedgeDS_decorator,HalfedgeDS_decorator_wrapper<HDS_d>)

#ifdef SWIG_CGAL_HAS_HalfedgeDS_USER_PACKAGE
%include "SWIG_CGAL/User_packages/HalfedgeDS/extensions.i"
#endif
