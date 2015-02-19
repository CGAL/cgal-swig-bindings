// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_constrained_triangulation_2.i"


//Expose a constrained Delaunay triangulation 2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
// --MODULENAME name of the module the class will be declared
%define SWIG_CGAL_declare_constrained_Delaunay_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,MODULENAME)
  SWIG_CGAL_declare_constrained_triangulation_2_internal(Internal_Contrained_triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,MODULENAME)

  %typemap(javaimports)          Constrained_Delaunay_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;  import CGAL.Triangulation_2.Constraint;%}
  SWIG_CGAL_declare_identifier_of_template_class(EXPOSEDNAME,Constrained_Delaunay_triangulation_2_wrapper<CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,Point_2> >)
%enddef


//Expose a constrained Delaunay triangulation 2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
// --MODULENAME name of the module the class will be declared
%define SWIG_CGAL_declare_constrained_Delaunay_triangulation_2(CLASSNAME,CPPTYPE,MODULENAME)
  SWIG_CGAL_declare_constrained_Delaunay_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE,MODULENAME)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_I
