%module CGAL_Mesh_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Mesh_3");
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Mesh_3 failed to load. \n" + e);
      throw e;
    }
  }
%}


%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/Weighted_point_3.h"
%import  "SWIG_CGAL/Kernel/Segment_3.h"
%import  "SWIG_CGAL/Kernel/Triangle_3.h"
%import  "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%import  "SWIG_CGAL/Kernel/enum.h"
%import  "SWIG_CGAL/Kernel/Reference_wrappers.i"


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
  #include  <SWIG_CGAL/Common/Optional.h>
  #include  <SWIG_CGAL/Mesh_3/C3T3.h>
  #include  <SWIG_CGAL/Mesh_3/Mesh_domains.h>
  #include  <SWIG_CGAL/Mesh_3/Mesh_criteria.h>
  #include  <SWIG_CGAL/Mesh_3/parameters.h>
%}

//definitions

%include "SWIG_CGAL/Common/Input_iterator.h"
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
%template(Mesh_3_Quality) std::pair<int,double>;
%template(Mesh_3_Badness) Optional< std::pair<int,double> >;

%include "SWIG_CGAL/Mesh_3/config.i"
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

//Regular triangulation
%typemap(javaimports) SWIG_Triangulation_3::CGAL_Cell_handle %{import CGAL.Kernel.Weighted_point_3;%}
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper_3<CGAL::Tag_true>::Point_range,Weighted_point_3,Weighted_point_3,Weighted_point_3::cpp_base,SWIGTYPE_p_Weighted_point_3,"(LCGAL/Kernel/Weighted_point_3;)J",insert_range)
Declare_regular_triangulation_3_with_memory_holder(Mesh_3_regular_triangulation_3,MT_PMD,boost::shared_ptr<C3T3_PMD>)

//iterators
SWIG_CGAL_set_as_java_iterator(CGAL_Cell_iterator,Mesh_3_regular_triangulation_3_Cell_handle,)
%template(Mesh_3_Complex_3_in_triangulation_3_Cell_iterator) CGAL_Cell_iterator<C3T3_PMD,SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3> >;

SWIG_CGAL_set_as_java_iterator(CGAL_Facet_iterator,Mesh_3_regular_triangulation_3_Facet,)
%template(Mesh_3_Complex_3_in_triangulation_3_Facet_iterator) CGAL_Facet_iterator<C3T3_PMD,std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,int> >;

//Types of Index
%template(Mesh_3_Surface_index) std::pair<int,int>;
%template(Mesh_3_Index) Variant<int,std::pair<int,int> >;


%define T_C3T3_wrapper C3T3_wrapper<  C3T3_PMD,
                                      Regular_triangulation_3_wrapper<MT_PMD,SWIG_Triangulation_3::CGAL_Vertex_handle<MT_PMD,Weighted_point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,boost::shared_ptr<C3T3_PMD> >,
                                      Variant< int, std::pair<int,int> >,
                                      std::pair<int,int>,
                                      int > 
%enddef
%template (Mesh_3_Complex_3_in_triangulation_3) T_C3T3_wrapper;

%{
  typedef C3T3_wrapper <  C3T3_PMD,
                          Regular_triangulation_3_wrapper<MT_PMD,SWIG_Triangulation_3::CGAL_Vertex_handle<MT_PMD,Weighted_point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<MT_PMD,Weighted_point_3>,boost::shared_ptr<C3T3_PMD> >,
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
%define T_Mesh_criteria Default_mesh_criteria_wrapper<DMC> %enddef
%{typedef Default_mesh_criteria_wrapper<DMC> T_Mesh_criteria;%}
%template(Default_mesh_criteria) T_Mesh_criteria;


//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

%import "SWIG_CGAL/Mesh_3/declare_global_functions.i"

declare_global_functions(T_C3T3_wrapper)
declare_global_functions_domain(T_C3T3_wrapper,Polyhedral_mesh_domain_3_type)
declare_global_functions_domain_criteria(T_C3T3_wrapper,Polyhedral_mesh_domain_3_type,T_Mesh_criteria,Mesh_3_parameters)



#ifdef SWIGJAVA
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
declare_global_functions_domain_criteria(T_C3T3_wrapper,Polyhedral_mesh_domain_3_type,JavaMeshCriteria,Mesh_3_parameters)
#endif