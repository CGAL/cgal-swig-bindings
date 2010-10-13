%module CGAL_Mesh_3


%include "SWIG_CGAL/common.i"
%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/Weighted_point_3.h"
%import  "SWIG_CGAL/Kernel/Segment_3.h"
%import  "SWIG_CGAL/Kernel/Triangle_3.h"
%import  "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%import  "SWIG_CGAL/Kernel/enum.h"


//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
  #include  <SWIG_CGAL/Triangulation_3/Regular_triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/Triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/triangulation_handles.h>
  #include  <SWIG_CGAL/Polyhedron_3/Polyhedron_3.h>
  #include  <SWIG_CGAL/Polyhedron_3/polyhedron_3_handles.h>  
  #include  <SWIG_CGAL/Common/triple.h>
  #include  <SWIG_CGAL/Common/Variant.h>
  #include  <SWIG_CGAL/Mesh_3/C3T3.h>
  #include  <SWIG_CGAL/Mesh_3/Mesh_domains.h>
  #include  <SWIG_CGAL/Mesh_3/Mesh_criteria.h>
  #include  <SWIG_CGAL/Mesh_3/parameters.h>
%}

//definitions

%include "SWIG_CGAL/Common/Input_iterator.h"
%include "SWIG_CGAL/Common/triple.h"
%include "SWIG_CGAL/Common/Variant.h"
%include "SWIG_CGAL/Triangulation_3/triangulation_handles.h"
%include "SWIG_CGAL/Triangulation_3/Triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/triangulation_iterators.h"
%include "SWIG_CGAL/Triangulation_3/Regular_triangulation_3.h"
%include "SWIG_CGAL/Mesh_3/C3T3.h"
%include "SWIG_CGAL/Mesh_3/Mesh_domains.h"
%include "SWIG_CGAL/Mesh_3/Mesh_criteria.h"
%include "SWIG_CGAL/Mesh_3/parameters.h"

%import "SWIG_CGAL/Triangulation_3/declare_regular_triangulation_3.i"

%include "std_pair.i"

%include "SWIG_CGAL/Mesh_3/config.i"
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"
      
%pragma(java) jniclassimports=%{import CGAL.Kernel.Weighted_point_3; import java.util.Collection; import java.util.Iterator; import CGAL.Polyhedron_3.Polyhedron_3;%}

//Regular triangulation
Typemap_for_Input_iterator(Weighting_helper_3<CGAL::Tag_true>::Point_range,Weighted_point_3,Weighted_point_3,Weighted_point_3::cpp_base,SWIGTYPE_p_Weighted_point_3,"(LCGAL/Kernel/Weighted_point_3;)J",insert_range)
Declare_regular_triangulation_3(Mesh_3_regular_triangulation_3,MT_PMD)

//iterators
Iterator_for_java(CGAL_Cell_iterator,Mesh_3_regular_triangulation_3_Cell_handle,)
%template(Mesh_3_Complex_3_in_triangulation_3_Cell_iterator) CGAL_Cell_iterator<C3T3_PMD,CGAL_Cell_handle<MT_PMD,Weighted_point_3> >;

Iterator_for_java(CGAL_Facet_iterator,Mesh_3_regular_triangulation_3_Facet,)
%template(Mesh_3_Complex_3_in_triangulation_3_Facet_iterator) CGAL_Facet_iterator<C3T3_PMD,std::pair<CGAL_Cell_handle<MT_PMD,Weighted_point_3>,int> >;

//Types of Index
%template(Mesh_3_Surface_index) std::pair<int,int>;
%template(Mesh_3_Index) Variant<int,std::pair<int,int> >;


%define T_C3T3_wrapper C3T3_wrapper<  C3T3_PMD,
                                      Regular_triangulation_3_wrapper<MT_PMD,CGAL_Vertex_handle<MT_PMD,Weighted_point_3>,CGAL_Cell_handle<MT_PMD,Weighted_point_3> >,
                                      Variant< int, std::pair<int,int> >,
                                      std::pair<int,int>,
                                      int > 
%enddef
%template (Mesh_3_Complex_3_in_triangulation_3) T_C3T3_wrapper;

%{
  typedef C3T3_wrapper <  C3T3_PMD,
                          Regular_triangulation_3_wrapper<MT_PMD,CGAL_Vertex_handle<MT_PMD,Weighted_point_3>,CGAL_Cell_handle<MT_PMD,Weighted_point_3> >,
                          Variant< int, std::pair<int,int> >,
                          std::pair<int,int>,
                          int  >
  T_C3T3_wrapper;
%}


//Polyhedral mesh domain
%define Polyhedron_3_type Polyhedron_3_wrapper< Polyhedron_3_,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > %enddef
%{
typedef Polyhedron_3_wrapper< Polyhedron_3_,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > Polyhedron_3_type;
%}

%define Polyhedral_mesh_domain_3_type Polyhedral_mesh_domain_3_wrapper<PMD,Polyhedron_3_type,Variant< int, std::pair<int,int> >,std::pair<int,int>,int > %enddef
%{
  typedef Polyhedral_mesh_domain_3_wrapper<PMD,Polyhedron_3_type,Variant< int, std::pair<int,int> >,std::pair<int,int>,int > Polyhedral_mesh_domain_3_type; 
%}
%typemap(javaimports)      Polyhedral_mesh_domain_3_wrapper%{import CGAL.Polyhedron_3.Polyhedron_3;%}
%template (Polyhedral_mesh_domain_3) Polyhedral_mesh_domain_3_type;


//Default criteria
%template(Default_mesh_criteria) Default_mesh_criteria_wrapper<DMC>;


//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

%import "SWIG_CGAL/Mesh_3/declare_global_functions.i"

declare_global_functions(T_C3T3_wrapper,Polyhedral_mesh_domain_3_type,Default_mesh_criteria_wrapper<DMC>,Mesh_3_parameters)

