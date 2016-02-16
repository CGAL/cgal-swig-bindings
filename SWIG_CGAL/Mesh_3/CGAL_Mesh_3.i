// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Mesh_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Mesh_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"

//include files
%{
  #define SWIG_CGAL_NO_TRIANGULATION_STRING_OUTPUT //I/O are broken for C3T3 triangulation
  #include  <SWIG_CGAL/Kernel/typedefs.h>
  #include  <SWIG_CGAL/Mesh_3/Object.h>
  #include  <SWIG_CGAL/Triangulation_3/Regular_triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/Triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/triangulation_handles.h>
  #include  <SWIG_CGAL/Common/triple.h>
  #include  <SWIG_CGAL/Common/Variant.h>
  #include  <SWIG_CGAL/Common/Optional.h>
  #include  <SWIG_CGAL/Mesh_3/all_includes.h>
%}

//definitions

#define SWIG_CGAL_NO_TRIANGULATION_STRING_OUTPUT //I/O are broken for C3T3 triangulation
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Optional.h"
%include "SWIG_CGAL/Common/triple.h"
%include "SWIG_CGAL/Common/Variant.h"
%include "SWIG_CGAL/Triangulation_3/triangulation_handles.h"
%include "SWIG_CGAL/Triangulation_3/Triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/Regular_triangulation_3.h"
%include "SWIG_CGAL/Mesh_3/C3T3.h"
%include "SWIG_CGAL/Mesh_3/Mesh_domains.h"
%include "SWIG_CGAL/Mesh_3/Mesh_criteria.h"
%include "SWIG_CGAL/Mesh_3/parameters.h"

%import "SWIG_CGAL/Triangulation_3/declare_regular_triangulation_3.i"

%include "std_pair.i"
SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Quality,std::pair<int,double>)
SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Badness,Optional< std::pair<int,double> >)

%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"
      
%pragma(java) jniclassimports=%{import CGAL.Kernel.Weighted_point_3; import CGAL.Kernel.Ref_int; import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Tetrahedron_3; import java.util.Collection; import java.util.Iterator; import CGAL.Polyhedron_3.Polyhedron_3;%}

//extends Cell and vertex handles of Regular triangulation
%extend SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>{
  int subdomain_index(){return $self->get_data()->subdomain_index();}
  void set_subdomain_index(int i){$self->get_data()->set_subdomain_index(i);}
  bool is_facet_on_surface (int i) {return $self->get_data()->is_facet_on_surface(i);}
  void set_facet_on_surface(int i,std::pair<int,int> p){$self->get_data()->set_surface_index(i,p);}
  bool is_facet_visited(int i){return $self->get_data()->is_facet_visited(i);}
  void set_facet_visited(int i){$self->get_data()->set_facet_visited(i);}
  Weighted_point_3 get_facet_surface_center(int i){return Weighted_point_3($self->get_data()->get_facet_surface_center(i));}
  void set_facet_surface_center(int i,const Weighted_point_3& p) {return $self->get_data()->set_facet_surface_center(i,p.get_data());}
}
%extend SWIG_Triangulation_3::CGAL_Vertex_handle<MT_PMD,Weighted_point_3>{
  int in_dimension() {return $self->get_data()->in_dimension();}
  void set_dimension(int d){$self->get_data()->set_dimension(d);}
  Variant< int, std::pair<int,int> > index(){return $self->get_data()->index();}
  void set_index(const Variant< int, std::pair<int,int> >& v){$self->get_data()->set_index(v.get_data());}
//Internal
  double meshing_info(){return $self->get_data()->meshing_info();}
  void set_meshing_info (double d) {$self->get_data()->set_meshing_info(d);}
}


%{
  template < class T1, class T2 >
  std::ostream&
  operator<<(std::ostream &os,
             const std::pair<T1,T2>& p)
  {
    os << p.first << " " << p.second;
    return os;
  }               
%}

//Regular triangulation
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper_3<CGAL::Tag_true>::Point_range,Weighted_point_3,Weighted_point_3,Weighted_point_3::cpp_base,SWIGTYPE_p_Weighted_point_3,"(LCGAL/Kernel/Weighted_point_3;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Triangulation_3_wrapper::Triangulation_3_wrapper)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Regular_triangulation_3_wrapper::Regular_triangulation_3_wrapper)
#endif
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE


//local Object class: we cannot use the class from Kernel module as CGAL::Object uses RTTI
#ifdef SWIG_CGAL_Mesh_3_MODULE
%include "SWIG_CGAL/Common/Object.i"
#endif

%include "SWIG_CGAL/Triangulation_3/Reference_wrappers.i"
SWIG_CGAL_declare_regular_triangulation_3_with_memory_holder(Mesh_3_regular_triangulation_3,MT_PMD,boost::shared_ptr<C3T3_PMD>)

//iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Mesh_3_regular_triangulation_3_Cell_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Complex_3_in_triangulation_3_Cell_iterator,SWIG_CGAL_Iterator<C3T3_PMD::Cell_iterator,SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Mesh_3_regular_triangulation_3_Facet,)
SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Complex_3_in_triangulation_3_Facet_iterator,SWIG_CGAL_Iterator<C3T3_PMD::Facet_iterator,std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,int> >)

//Types of Index
SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Surface_index,std::pair<int,int>)
SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Index,Variant<int,std::pair<int,int> >)


SWIG_CGAL_declare_identifier_of_template_class(Mesh_3_Complex_3_in_triangulation_3,C3T3_wrapper<  C3T3_PMD,
                                                                                                  Regular_triangulation_3_wrapper<MT_PMD,SWIG_Triangulation_3::CGAL_Vertex_handle<MT_PMD,Weighted_point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,boost::shared_ptr<C3T3_PMD> >,
                                                                                                  Variant< int, std::pair<int,int> >,
                                                                                                  std::pair<int,int>,
                                                                                                  int >)

//Polyhedral mesh domain
SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper
%typemap(javaimports)      Polyhedral_mesh_domain_3_wrapper%{import CGAL.Polyhedron_3.Polyhedron_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Polyhedral_mesh_domain_3,Polyhedral_mesh_domain_3_wrapper<PMD,Polyhedron_3_SWIG_wrapper,Variant< int, std::pair<int,int> >,std::pair<int,int>,int >)


//Default criteria
SWIG_CGAL_declare_identifier_of_template_class(Default_mesh_criteria,Mesh_criteria_with_fields_wrapper<DMC,double,double,double,double>)


%import "SWIG_CGAL/Mesh_3/declare_global_functions.i"

declare_global_functions(Mesh_3_Complex_3_in_triangulation_3_SWIG_wrapper)
//Functions polyhedral mesh domain
declare_global_functions_domain(Mesh_3_Complex_3_in_triangulation_3_SWIG_wrapper,Polyhedral_mesh_domain_3_SWIG_wrapper)
declare_global_functions_domain_criteria(Mesh_3_Complex_3_in_triangulation_3_SWIG_wrapper,Polyhedral_mesh_domain_3_SWIG_wrapper,Default_mesh_criteria_SWIG_wrapper,Mesh_3_parameters)

#ifdef SWIGJAVA
%include "SWIG_CGAL/Mesh_3/java_extensions.i"
#endif

#ifdef SWIG_CGAL_HAS_Mesh_3_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Mesh_3/extensions.i"
#endif
