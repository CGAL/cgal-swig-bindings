#ifdef SWIGPYTHON

#ifndef IMPORT_ONLY_POLYHEDRON_TYPES
  %{#define CGAL_SWIG_FACET_SUPPORTS_PLANE%}
  #define CGAL_SWIG_FACET_SUPPORTS_PLANE
#endif //IMPORT_ONLY_POLYHEDRON_TYPES

%{
typedef CGAL::Polyhedron_3<EPIC_Kernel>     Polyhedron_3_;
%}

#endif //SWIGPYTHON

//typedef  CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_3> Polyhedron_3_;


#ifdef SWIGJAVA


%import "SWIG_CGAL/Java/JavaData.h"
%import "SWIG_CGAL/Java/Macro.i"
%import "SWIG_CGAL/common.i"
%{
#include "SWIG_CGAL/Java/JavaData.h"
#include "SWIG_CGAL/Polyhedron_3/Polyhedron_items_with_id_and_info_3.h"
%}


%{
typedef CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_and_info_3<JavaData> > Polyhedron_3_;
%}

#ifndef IMPORT_ONLY_POLYHEDRON_TYPES

//modifiers examples
%{ 
  #include "SWIG_CGAL/Polyhedron_3/modifier_example.h" 
%}
%include "SWIG_CGAL/Polyhedron_3/Modifier_base.h"


//Advanced modifier that read points and triple of integer to add points 
//and facets to the polyhedron
%include "SWIG_CGAL//Common/triple.h"
%template(Integer_triple)  CGAL_SWIG::Triple<int,int,int>;
//typemap for input iterators
Typemap_for_Input_iterator(Point_range,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",set_modifier_data)
Typemap_for_Input_iterator(Triple_integer_range,Integer_triple,Integer_triple,iInteger_triple,SWIGTYPE_p_CGAL_SWIG__TripleT_int_int_int_t,"(LCGAL/Polyhedron_3/Integer_triple;)J",set_modifier_data)

%{
  #include <SWIG_CGAL/Common/triple.h>
  typedef CGAL_SWIG::Triple<int,int,int> iInteger_triple;
  
  #include <SWIG_CGAL/Polyhedron_3/Modifier_base.h>
  #include <CGAL/Polyhedron_3.h>
%}
%typemap(javaimports) Modifier_wrapper %{import CGAL.Kernel.Point_3; import java.util.Iterator;%} //need some imports for that modifier
%template(Polyhedron_3_Modifier_triangular_facets)     Modifier_wrapper< Polyhedron_3_,Build_triangular_facets_from_point_range<Polyhedron_3_::HalfedgeDS> >;

//add a method to Modifier_wrapper so that we can initialize data.
%extend Modifier_wrapper< Polyhedron_3_,Build_triangular_facets_from_point_range<Polyhedron_3_::HalfedgeDS> >{
  void set_modifier_data(Point_range pt_range,Triple_integer_range int_range){
    //We need to make a copy because the iterator may not be valid when delegate will be called
    std::copy (pt_range.first,pt_range.second,$self->get_modifier_cpp_base().point_writer()); //copy points into the modifier
    std::copy (int_range.first,int_range.second,$self->get_modifier_cpp_base().integer_triple_writer()); //copy triple of integer into the modifier
  }
}

//simple modifiers
%typemap(javaimports) Modifier_wrapper  %{ %} //clear imports (not needed for the others)
%template(Polyhedron_3_Modifier_1)                     Modifier_wrapper< Polyhedron_3_,Build_triangle<Polyhedron_3_::HalfedgeDS> >;
%template(Polyhedron_3_Modifier_2)                     Modifier_wrapper< Polyhedron_3_,Build_square<Polyhedron_3_::HalfedgeDS> >;

//assign JavaData to handles
add_JavaData_info_to_class( SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,)
add_JavaData_info_to_class( SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,import CGAL.Kernel.Point_3;)
add_JavaData_info_to_class( SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>,)

#define NO_VERTEX_HANDLE_IMPORTS //prevents add_JavaData_info_to_class to be overwritten

#endif //IMPORT_ONLY_POLYHEDRON_TYPES

#endif //SWIGJAVA