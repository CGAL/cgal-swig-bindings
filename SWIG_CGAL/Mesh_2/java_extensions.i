// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

%include "SWIG_CGAL/Java/Java_caller_code.h"
%include "SWIG_CGAL/Mesh_2/Quality.h"
%define T_User_crit_simple Java_criteria_wrapper< Java_Is_bad_wrapper<Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness>,SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C> >,Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness> > %enddef
%{
  #include <SWIG_CGAL/Mesh_2/Quality.h>
  #include <SWIG_CGAL/Java/Java_caller_code.h>
  typedef Java_criteria_wrapper< Java_Is_bad_wrapper<Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness>,SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C> >,Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness> > T_User_crit_simple;  
%}

SWIG_CGAL_declare_identifier_of_template_class(Quality_pair,Quality_pair_wrapper<DM2_C>)
SWIG_CGAL_declare_identifier_of_template_class(Mesh_2_predicate,Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness>)
SWIG_CGAL_declare_identifier_of_template_class(User_mesh_criteria_simple_2,T_User_crit_simple)

declare_refine_global_functions(Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper, T_User_crit_simple)
