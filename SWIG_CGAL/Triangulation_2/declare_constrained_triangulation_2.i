// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_triangulation_2.i"


//Expose a constrained triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
// --MODULENAME name of the module the class will be declared
%define SWIG_CGAL_declare_constrained_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,MODULENAME)
  SWIG_CGAL_declare_triangulation_2_internal(Internal_Triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_2,CGAL::Tag_false)

  //typemaps for Edge_output_iterator
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  %define EXPOSEDNAME##_Edge_output_iterator Constrained_triangulation_2_wrapper< CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle< CPPTYPE,Point_2 >,SWIG_Triangulation_2::CGAL_Face_handle< CPPTYPE,Point_2 > >::Edge_output_iterator %enddef
  %{
  typedef std::pair<SWIG_Triangulation_2::CGAL_Face_handle< CPPTYPE,Point_2 >,int> CLASSNAME_PREFIX##_Edge;
  %}
  SWIG_CGAL_output_iterator_typemap_in(EXPOSEDNAME##_Edge_output_iterator,CLASSNAME_PREFIX##_Edge,CLASSNAME_PREFIX##_Edge,CPPTYPE::Edge,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_##CPPTYPE##_Point_2_t_int_t,"LCGAL/"#MODULENAME"/" #CLASSNAME_PREFIX "_Edge;")
  #else
  %include "SWIG_CGAL/Common/Output_iterator_wrapper.h"  
  %define i##EXPOSEDNAME##_Triangulation_Edge  std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2>,int > %enddef
  SWIG_CGAL_declare_generic_output_iterator(EXPOSEDNAME##_Edge_output_iterator,EXPOSEDNAME##_Edge_output_iterator_nested_iterator,i##EXPOSEDNAME##_Triangulation_Edge)
  #endif
  %typemap(javaimports)          Constrained_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;  import CGAL.Triangulation_2.Constraint;%}
  SWIG_CGAL_declare_identifier_of_template_class(EXPOSEDNAME,Constrained_triangulation_2_wrapper<CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2> >)
%enddef


//Expose a constrained triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
// --MODULENAME name of the module the class will be declared
%define SWIG_CGAL_declare_constrained_triangulation_2(CLASSNAME,CPPTYPE,MODULENAME)
  SWIG_CGAL_declare_constrained_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE,MODULENAME)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_TRIANGULATION_2_I
