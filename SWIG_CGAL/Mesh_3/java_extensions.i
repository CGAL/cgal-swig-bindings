// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%{ 
  #include <SWIG_CGAL/Java/Java_caller_code.h>
%}

//to avoid conflict with Object from package
%typemap(jstype) jobject      "java.lang.Object"
%typemap(jtype) jobject       "java.lang.Object"

%include "SWIG_CGAL/Java/Java_caller_code.h"

%template(Cell_predicate) Java_caller_code<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,Optional< std::pair<int,double> > >;
%template(Facet_predicate) Java_caller_code<std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,int>,Optional< std::pair<int,double> > >;

%define JavaMeshCriteria Java_criteria_wrapper<MT_PMD,
                                               Java_caller_code<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,Optional< std::pair<int,double> > >,
                                               Java_caller_code<std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,int>,Optional< std::pair<int,double> > > > 
%enddef
%{typedef Java_criteria_wrapper<MT_PMD,
                                Java_caller_code<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,Optional< std::pair<int,double> > >,
                                Java_caller_code<std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,int>,Optional< std::pair<int,double> > > > JavaMeshCriteria;%}
%template(User_mesh_criteria) JavaMeshCriteria;
declare_global_functions_domain_criteria(Mesh_3_Complex_3_in_triangulation_3_SWIG_wrapper,Polyhedral_mesh_domain_3_SWIG_wrapper,JavaMeshCriteria,Mesh_3_parameters)
