%{#define CGAL_SWIG_FACET_SUPPORTS_PLANE%}
#define CGAL_SWIG_FACET_SUPPORTS_PLANE

%define Polyhedron_3_
CGAL::Polyhedron_3<EPIC_Kernel>
%enddef

// %define Polyhedron_3_
// CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_3>
// %enddef

%define Halfedge_handle_
CGAL_Halfedge_handle<Polyhedron_3_> 
%enddef

%define Vertex_handle_
CGAL_Vertex_handle<Polyhedron_3_> 
%enddef

%define Facet_handle_
CGAL_Facet_handle<Polyhedron_3_>
%enddef

%{ #include "modifier_example.h" %}
%include "Modifier_base.h"
%template(Polyhedron_3_Modifier_1)                     Modifier_wrapper< Polyhedron_3_,Build_triangle<Polyhedron_3_::HalfedgeDS> >;
%template(Polyhedron_3_Modifier_2)                     Modifier_wrapper< Polyhedron_3_,Build_square<Polyhedron_3_::HalfedgeDS> >;

