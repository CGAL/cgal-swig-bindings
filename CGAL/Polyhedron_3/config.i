//~ %{#define CGAL_SWIG_FACET_SUPPORTS_PLANE%}
//~ #define CGAL_SWIG_FACET_SUPPORTS_PLANE

//~ %define Polyhedron_3_
//~ CGAL::Polyhedron_3<EPIC_Kernel>
//~ %enddef

// %define Polyhedron_3_
// CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_3>
// %enddef

%import "../Java/JavaData.h"
%{
#include "../Java/JavaData.h"
#include "Polyhedron_items_with_id_and_info_3.h"
%}

%define Polyhedron_3_
CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_and_info_3<JavaData> >
%enddef

%define Halfedge_handle_
CGAL_Halfedge_handle<Polyhedron_3_> 
%enddef

%define Vertex_handle_
CGAL_Vertex_handle<Polyhedron_3_> 
%enddef

%define Facet_handle_
CGAL_Facet_handle<Polyhedron_3_>
%enddef

//modifiers examples
%{ #include "modifier_example.h" %}
%include "Modifier_base.h"
%template(Polyhedron_3_Modifier_1)                     Modifier_wrapper< Polyhedron_3_,Build_triangle<Polyhedron_3_::HalfedgeDS> >;
%template(Polyhedron_3_Modifier_2)                     Modifier_wrapper< Polyhedron_3_,Build_square<Polyhedron_3_::HalfedgeDS> >;


//assign JavaData to handles
%define add_JavaData_info_to_class(CNAME,EXTRA)
%extend CNAME {
  JavaData& info(){
    return $self->get_data_ref()->info();
  }
}
%typemap(javaimports)                               CNAME %{import CGAL.Java.JavaData; EXTRA%}
%enddef

add_JavaData_info_to_class( Halfedge_handle_,)
add_JavaData_info_to_class( Vertex_handle_,import CGAL.Kernel.Point_3;)
add_JavaData_info_to_class( Facet_handle_,)

