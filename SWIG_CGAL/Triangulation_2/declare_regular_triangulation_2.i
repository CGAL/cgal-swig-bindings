// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_REGULAR_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_REGULAR_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_triangulation_2.i"


//Expose a Regular triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define SWIG_CGAL_declare_regular_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  SWIG_CGAL_declare_triangulation_2_internal(Internal_Triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Weighted_point_2,CGAL::Tag_true)

  SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.Weighted_point_2;)
  SWIG_CGAL_declare_identifier_of_template_class(CLASSNAME_PREFIX##_Hidden_vertices_iterator,SWIG_CGAL_Iterator<CPPTYPE::Hidden_vertices_iterator,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,Weighted_point_2> >)

  %typemap(javaimports)          Regular_triangulation_2_wrapper%{import CGAL.Kernel.Weighted_point_2; import CGAL.Kernel.Oriented_side; import java.util.Iterator; import java.util.Collection;%}
  SWIG_CGAL_declare_identifier_of_template_class(EXPOSEDNAME,Regular_triangulation_2_wrapper<CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,Weighted_point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Weighted_point_2> >)
%enddef


//Expose a Regular_triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define SWIG_CGAL_declare_regular_triangulation_2(CLASSNAME,CPPTYPE)
  SWIG_CGAL_declare_regular_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_REGULAR_TRIANGULATION_2_I
