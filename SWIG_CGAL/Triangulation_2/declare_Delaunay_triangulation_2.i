// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_triangulation_2.i"


//Expose a Delaunay triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define SWIG_CGAL_declare_Delaunay_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  SWIG_CGAL_declare_triangulation_2_internal(Internal_Triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_2,CGAL::Tag_false)

  %define iSWIG_##EXPOSEDNAME##_Edge_wrapper std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2>,int > %enddef
  %define iSWIG_##EXPOSEDNAME##_Face_wrapper SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2> %enddef
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  %define iSWIG_##EXPOSEDNAME##_wrapper Delaunay_triangulation_2_wrapper<CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2> > %enddef
  %define iSWIG_##EXPOSEDNAME##_Edge_base std::pair<CPPTYPE::Face_handle,int > %enddef
  SWIG_CGAL_output_iterator_typemap_in(iSWIG_##EXPOSEDNAME##_wrapper::Edge_output_iterator,iSWIG_##EXPOSEDNAME##_Edge_wrapper,CLASSNAME_PREFIX##_Edge,iSWIG_##EXPOSEDNAME##_Edge_base,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_##CPPTYPE##_Point_2_t_int_t,"LCGAL/Triangulation_2/" #EXPOSEDNAME "_Edge;")
  SWIG_CGAL_output_iterator_typemap_in(iSWIG_##EXPOSEDNAME##_wrapper::Face_output_iterator,iSWIG_##EXPOSEDNAME##_Face_wrapper,CLASSNAME_PREFIX##_Face_handle,CPPTYPE::Face_handle,SWIGTYPE_p_SWIG_Triangulation_2__CGAL_Face_handleT_##CPPTYPE##_Point_2_t,"LCGAL/Triangulation_2/" #EXPOSEDNAME "_Face_handle;")
  #else
  %include "SWIG_CGAL/Common/Output_iterator_wrapper.h"  
  SWIG_CGAL_declare_generic_output_iterator(EXPOSEDNAME##_Edge_output_iterator,EXPOSEDNAME##_Edge_output_iterator_nested_iterator,iSWIG_##EXPOSEDNAME##_Edge_wrapper)
  SWIG_CGAL_declare_generic_output_iterator(EXPOSEDNAME##_Face_handle_output_iterator,EXPOSEDNAME##_Face_handle_output_iterator_nested_iterator,iSWIG_##EXPOSEDNAME##_Face_wrapper)
  #endif

  %typemap(javaimports)          Delaunay_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;%}
  SWIG_CGAL_declare_identifier_of_template_class(EXPOSEDNAME,Delaunay_triangulation_2_wrapper<CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2> >)
%enddef


//Expose a Delaunay_triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define SWIG_CGAL_declare_Delaunay_triangulation_2(CLASSNAME,CPPTYPE)
  SWIG_CGAL_declare_Delaunay_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I
