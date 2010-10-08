%module CGAL_Surface_mesher


%include "SWIG_CGAL/common.i"
%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/Point_3.h"
%import  "SWIG_CGAL/Kernel/Sphere_3.h"
%import  "SWIG_CGAL/Kernel/Segment_3.h"
%import  "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%import  "SWIG_CGAL/Kernel/Triangle_3.h"
%import  "SWIG_CGAL/Kernel/enum.h"
%include "SWIG_CGAL/Common/Input_iterator.h"
%import  "SWIG_CGAL/Polyhedron_3/Polyhedron_3.h"
%import  "SWIG_CGAL/Polyhedron_3/polyhedron_3_handles.h"

//include files
%{
  #include  <SWIG_CGAL/Polyhedron_3/Polyhedron_3.h>
  #include  <SWIG_CGAL/Polyhedron_3/polyhedron_3_handles.h>  
  #include  <SWIG_CGAL/Triangulation_3/Delaunay_triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/Triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/triangulation_handles.h>
  #include  <SWIG_CGAL/Common/triple.h>
  #include  <SWIG_CGAL/Triangulation_3/triangulation_iterators.h>
  #include  <SWIG_CGAL/Surface_mesher/Surface_mesh_details.h>
  #include  <SWIG_CGAL/Surface_mesher/C2T3.h>
%}

%include "SWIG_CGAL/Surface_mesher/config.i"

//import definitions of Polyhedron objects
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"

//definitions
%include "SWIG_CGAL/Triangulation_3/triangulation_handles.h"
%include "SWIG_CGAL/Triangulation_3/Triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/Delaunay_triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/triangulation_iterators.h"
%include "SWIG_CGAL/Common/triple.h"
%include "SWIG_CGAL/Surface_mesher/C2T3.h"
%include "SWIG_CGAL/Surface_mesher/Surface_mesh_details.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import CGAL.Kernel.Sphere_3; import java.util.Iterator; import java.util.Collection; import CGAL.Polyhedron_3.Polyhedron_3;%}
%pragma(java) moduleimports  =%{import CGAL.Polyhedron_3.Polyhedron_3;%} //for global functions

%import "SWIG_CGAL/Triangulation_3/declare_Delaunay_triangulation_3.i"
Declare_Delaunay_triangulation_3(Surface_mesh_default_triangulation_3,C2T3_DT)

//typemap for output iterator
%define Complex_2_in_triangulation_3_Facet_output_iterator  C2T3_internal::Iterator_helper<Delaunay_triangulation_3_wrapper<C2T3_DT,CGAL_Vertex_handle<C2T3_DT,Point_3>,CGAL_Cell_handle<C2T3_DT,Point_3> > >::output %enddef
%{
typedef std::pair< CGAL_Cell_handle<C2T3_DT,Point_3>,int >                              Surface_mesh_default_triangulation_3_Facet;
%}
Typemap_for_Output_iterator(Complex_2_in_triangulation_3_Facet_output_iterator,Surface_mesh_default_triangulation_3_Facet,Surface_mesh_default_triangulation_3_Facet,C2T3_DT::Facet,SWIGTYPE_p_std__pairT_CGAL_Cell_handleT_C2T3_DT_Point_3_t_int_t,"LCGAL/Surface_mesher/Surface_mesh_default_triangulation_3_Facet;")

//iterators
Iterator_for_java(CGAL_Vertex_iterator,Surface_mesh_default_triangulation_3_Vertex_handle,import CGAL.Kernel.Point_3;)
%template(Surface_mesher_Complex_2_in_triangulation_3_Vertex_iterator) CGAL_Vertex_iterator<C2T3,CGAL_Vertex_handle<C2T3_DT,Point_3> >;

Iterator_for_java(CGAL_Facet_iterator,Surface_mesh_default_triangulation_3_Facet,)
%template(Surface_mesh_default_triangulation_3_Facet_iterator) CGAL_Facet_iterator<C2T3,std::pair<CGAL_Cell_handle<C2T3_DT,Point_3>,int> >;

Iterator_for_java(CGAL_Edge_iterator,Surface_mesh_default_triangulation_3_Edge,)
%template(Surface_mesh_default_triangulation_3_Edge_iterator) CGAL_Edge_iterator<C2T3,CGAL_SWIG::Triple<CGAL_Cell_handle<C2T3_DT,Point_3>,int,int> >;

Iterator_for_java(CGAL_Boundary_edges_iterator,Surface_mesh_default_triangulation_3_Edge,)
%template(Surface_mesh_default_triangulation_3_Boundary_edges_iterator) CGAL_Boundary_edges_iterator<C2T3,CGAL_SWIG::Triple<CGAL_Cell_handle<C2T3_DT,Point_3>,int,int> >;


//main classes
//--C2T3
%typemap(javaimports)      C2T3_wrapper%{import java.util.Collection;%}
%define T_C2T2_wrapper C2T3_wrapper<C2T3,Delaunay_triangulation_3_wrapper<C2T3_DT,CGAL_Vertex_handle<C2T3_DT,Point_3>,CGAL_Cell_handle<C2T3_DT,Point_3> > > %enddef
%{
typedef C2T3_wrapper<C2T3,Delaunay_triangulation_3_wrapper<C2T3_DT,CGAL_Vertex_handle<C2T3_DT,Point_3>,CGAL_Cell_handle<C2T3_DT,Point_3> > >  T_C2T2_wrapper;
%}
%template (Complex_2_in_triangulation_3) T_C2T2_wrapper;
//--
%template (Surface_mesh_default_criteria_3) Surface_mesh_criteria_3_wrapper<SMDC_3>;
//--
%template (Gray_level_image_3) Gray_level_image_3_wrapper<GLI_3>;
//--
%typemap(javaimports)      Implicit_surface_3_wrapper%{import CGAL.Kernel.Sphere_3;%}
%template (Implicit_surface_Gray_level_image_3) Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >;

%define Polyhedron_3_type Polyhedron_3_wrapper< Polyhedron_3_,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > %enddef
%{
typedef Polyhedron_3_wrapper< Polyhedron_3_,SWIG_Polyhedron_3::CGAL_Vertex_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > Polyhedron_3_type;
%}

//global functions

%include "std_string.i"
void output_surface_facets_to_off(const std::string& s,const T_C2T2_wrapper&);
void output_surface_facets_to_polyhedron(const T_C2T2_wrapper&,Polyhedron_3_type&);

//general
//void  make_surface_mesh(T_C2T2_wrapper& c2t3,Surface surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag Tag,int initial_number_of_points = 20)
void  make_surface_mesh(T_C2T2_wrapper& c2t3,const Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >& surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag Tag);
void  make_surface_mesh(T_C2T2_wrapper& c2t3,const Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >& surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag Tag,int);

%{
  #include <fstream>
  
  void output_surface_facets_to_off(const std::string& s,const T_C2T2_wrapper& c2t3)
  {
    std::ofstream outfile(s.c_str());
    if (!outfile) std::cerr << "Error cannot create file: " << s << std::endl;
    else  CGAL::output_surface_facets_to_off(outfile,c2t3.get_data());
  }
  
  void output_surface_facets_to_polyhedron(const T_C2T2_wrapper& c2t3,Polyhedron_3_type& poly)
  {
    CGAL::output_surface_facets_to_polyhedron( c2t3.get_data(),poly.get_data_ref() );
  }

  void  make_surface_mesh(T_C2T2_wrapper& c2t3,const Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >& surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag tag,int nb)
  {
    switch(tag){
      case MANIFOLD_TAG:
        CGAL::make_surface_mesh(c2t3.get_data_ref(),surface.get_data(),criteria.get_data(),CGAL::Manifold_tag(),nb);
      break;
      case MANIFOLD_WITH_BOUNDARY_TAG:
        CGAL::make_surface_mesh(c2t3.get_data_ref(),surface.get_data(),criteria.get_data(),CGAL::Manifold_with_boundary_tag(),nb);
      break;
      case NON_MANIFOLD_TAG:
        CGAL::make_surface_mesh(c2t3.get_data_ref(),surface.get_data(),criteria.get_data(),CGAL::Non_manifold_tag(),nb);
      break;
    }
  }
  void  make_surface_mesh(T_C2T2_wrapper& c2t3,const Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >& surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag tag)
  {
    make_surface_mesh(c2t3,surface,criteria,tag,20);
  }
  
%}




