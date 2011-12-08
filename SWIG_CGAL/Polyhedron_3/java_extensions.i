// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

%import "SWIG_CGAL/Java/JavaData.h"
%import "SWIG_CGAL/Java/Macro.i"
%import "SWIG_CGAL/common.i"

//modifiers examples
%{
  #include "SWIG_CGAL/Polyhedron_3/modifier_example.h" 
%}
%include "SWIG_CGAL/Polyhedron_3/Modifier_base.h"

%template(Polyhedron_3_Modifier_base)                  Modifier_base< Polyhedron_3_ >;

//Advanced modifier that read points and triple of integer to add points 
//and facets to the polyhedron
%include "SWIG_CGAL//Common/triple.h"
%template(Integer_triple)  SWIG_CGAL::Triple<int,int,int>;
//typemap for input iterators
SWIG_CGAL_input_iterator_typemap_in(Point_range,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",set_modifier_data)
SWIG_CGAL_input_iterator_typemap_in(Triple_integer_range,Integer_triple,Integer_triple,iInteger_triple,SWIGTYPE_p_SWIG_CGAL__TripleT_int_int_int_t,"(LCGAL/Polyhedron_3/Integer_triple;)J",set_modifier_data)

%{
  #include <SWIG_CGAL/Common/triple.h>
  typedef SWIG_CGAL::Triple<int,int,int> iInteger_triple;
  
  #include <SWIG_CGAL/Polyhedron_3/Modifier_base.h>
  #include <CGAL/Polyhedron_3.h>
%}
%typemap(javaimports) Modifier_wrapper %{import CGAL.Kernel.Point_3; import java.util.Iterator;%} //need some imports for that modifier
%template(Polyhedron_3_Modifier_triangular_facets)     Modifier_wrapper< Polyhedron_3_,Build_triangular_facets_from_point_range<Polyhedron_3_::HalfedgeDS> >;

//add a method to Modifier_wrapper so that we can initialize data.
%extend Modifier_wrapper< Polyhedron_3_,Build_triangular_facets_from_point_range<Polyhedron_3_::HalfedgeDS> >{
  void set_modifier_data(Point_range pt_range,Triple_integer_range int_range){
    //We need to make a copy because the iterator may not be valid when delegate will be called
    std::copy (SWIG_CGAL::get_begin(pt_range),SWIG_CGAL::get_end(pt_range),$self->get_modifier_cpp_base().point_writer()); //copy points into the modifier
    std::copy (SWIG_CGAL::get_begin(int_range),SWIG_CGAL::get_end(int_range),$self->get_modifier_cpp_base().integer_triple_writer()); //copy triple of integer into the modifier
  }
}

//simple modifiers
%typemap(javaimports) Modifier_wrapper  %{ %} //clear imports (not needed for the others)
%template(Polyhedron_3_Modifier_1)                     Modifier_wrapper< Polyhedron_3_,Build_triangle<Polyhedron_3_::HalfedgeDS> >;
%template(Polyhedron_3_Modifier_2)                     Modifier_wrapper< Polyhedron_3_,Build_square<Polyhedron_3_::HalfedgeDS> >;

//assign JavaData to handles
SWIG_CGAL_add_JavaData_info_to_class( SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,)
SWIG_CGAL_add_JavaData_info_to_class( SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,import CGAL.Kernel.Point_3;)
SWIG_CGAL_add_JavaData_info_to_class( SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>,)

#define NO_VERTEX_HANDLE_IMPORTS //prevents SWIG_CGAL_add_JavaData_info_to_class to be overwritten

