// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_3_DECLARE_DELAUNAY_TRIANGULATION_3_I
#define SWIG_CGAL_TRIANGULATION_3_DECLARE_DELAUNAY_TRIANGULATION_3_I

%import "SWIG_CGAL/Triangulation_3/declare_triangulation_3.i"


//Expose a Delaunay triangulation_3
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
// --MEMHOLDER is used if the triangulation pointer is hold by another class, it is a shared_ptr in that case and void* otherwise
%define SWIG_CGAL_declare_Delaunay_triangulation_3_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,MEMHOLDER)
  SWIG_CGAL_declare_triangulation_3_internal(Internal_Triangulation_3_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_3,CGAL::Tag_false,MEMHOLDER)
  
  %typemap(javaimports)          Delaunay_triangulation_3_wrapper%{import CGAL.Kernel.Point_3; import CGAL.Kernel.Line_3; import CGAL.Kernel.Bounded_side; import java.util.Iterator; import java.util.Collection;%}  
  SWIG_CGAL_declare_identifier_of_template_class(EXPOSEDNAME,Delaunay_triangulation_3_wrapper<CPPTYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,Point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,Point_3>,MEMHOLDER >)
%enddef


//Expose a Delaunay_triangulation_3
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define SWIG_CGAL_declare_Delaunay_triangulation_3(CLASSNAME,CPPTYPE)
  SWIG_CGAL_declare_Delaunay_triangulation_3_internal(CLASSNAME,CLASSNAME,CPPTYPE,void*)
%enddef
  
//Expose a Delaunay_triangulation_3 with a memory holder
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
// --MEMHOLDER is used if the triangulation pointer is hold by another class
%define SWIG_CGAL_declare_Delaunay_triangulation_3_with_memory_holder(CLASSNAME,CPPTYPE,MEMHOLDER)
  SWIG_CGAL_declare_Delaunay_triangulation_3_internal(CLASSNAME,CLASSNAME,CPPTYPE,MEMHOLDER)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_3_DECLARE_DELAUNAY_TRIANGULATION_3_I
