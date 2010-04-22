%module Polyhedron_3

%include "../common.i"
%import  "../Kernel/Point_3.h"
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
%template(PH_halfedge_handle)     CGAL_Halfedge_handle<Polyhedron>;

%typemap(javaimports)                     Polyhedron_3 %{import CGAL.Kernel.Point_3;%}
%template(Polyhedron)                     Polyhedron_3<Polyhedron,CGAL_Halfedge_handle<Polyhedron> >;

//Iterators
Iterator_for_java(CGAL_Halfedge_iterator,PH_halfedge_handle)
%template(PH_halfedge_iterator) CGAL_Halfedge_iterator<Polyhedron>;

