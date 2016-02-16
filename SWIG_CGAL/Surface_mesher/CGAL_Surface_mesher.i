// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Surface_mesher

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Surface_mesher)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"

//include files
%{
  #include  <SWIG_CGAL/Polyhedron_3/all_includes.h>
  #include  <SWIG_CGAL/Surface_mesher/Object.h>
  #include  <SWIG_CGAL/Triangulation_3/Delaunay_triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/Triangulation_3.h>
  #include  <SWIG_CGAL/Triangulation_3/triangulation_handles.h>
  #include  <SWIG_CGAL/Common/triple.h>
  #include  <SWIG_CGAL/Common/Iterator.h>
  #include  <SWIG_CGAL/Surface_mesher/all_includes.h>
%}

//import definitions of Polyhedron objects
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"

//definitions
%include "SWIG_CGAL/Triangulation_3/triangulation_handles.h"
%include "SWIG_CGAL/Triangulation_3/Triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/Delaunay_triangulation_3.h"
%include "SWIG_CGAL/Common/triple.h"
%include "SWIG_CGAL/Surface_mesher/C2T3.h"
%include "SWIG_CGAL/Surface_mesher/Surface_mesh_details.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import CGAL.Kernel.Line_3; import CGAL.Kernel.Ref_int; import CGAL.Kernel.Sphere_3; import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Tetrahedron_3; import java.util.Iterator; import java.util.Collection; import CGAL.Polyhedron_3.Polyhedron_3;%}
%pragma(java) moduleimports  =%{import CGAL.Polyhedron_3.Polyhedron_3;%} //for global functions

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper_3<CGAL::Tag_false>::Point_range,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Triangulation_3_wrapper::Triangulation_3_wrapper)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Delaunay_triangulation_3_wrapper::Delaunay_triangulation_3_wrapper)
#endif
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE

//local Object class: we cannot use the class from Kernel module as CGAL::Object uses RTTI
#ifdef SWIG_CGAL_Surface_mesher_MODULE
%include "SWIG_CGAL/Common/Object.i"
#endif

%import "SWIG_CGAL/Triangulation_3/declare_Delaunay_triangulation_3.i"
%include "SWIG_CGAL/Triangulation_3/Reference_wrappers.i"
SWIG_CGAL_declare_Delaunay_triangulation_3_with_memory_holder(Surface_mesh_default_triangulation_3,C2T3_DT,boost::shared_ptr<C2T3_DT>)

//typemap for output iterator
%{
typedef std::pair< SWIG_Triangulation_3::CGAL_Cell_handle<C2T3_DT,Point_3>,int >                              Surface_mesh_default_triangulation_3_Facet;
%}
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Complex_2_in_triangulation_3_Facet_output_iterator  C2T3_internal::Iterator_helper<Delaunay_triangulation_3_wrapper<C2T3_DT,SWIG_Triangulation_3::CGAL_Vertex_handle<C2T3_DT,Point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<C2T3_DT,Point_3>,boost::shared_ptr<C2T3_DT> > >::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Complex_2_in_triangulation_3_Facet_output_iterator,Surface_mesh_default_triangulation_3_Facet,Surface_mesh_default_triangulation_3_Facet,C2T3_DT::Facet,SWIGTYPE_p_std__pairT_SWIG_Triangulation_3__CGAL_Cell_handleT_C2T3_DT_Point_3_t_int_t,"LCGAL/Surface_mesher/Surface_mesh_default_triangulation_3_Facet;")
#endif //#else is not needed as the output_iterator type is already defined within declare_Delaunay_triangulation_3


//iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Surface_mesh_default_triangulation_3_Vertex_handle,import CGAL.Kernel.Point_3;)
SWIG_CGAL_declare_identifier_of_template_class(Surface_mesher_Complex_2_in_triangulation_3_Vertex_iterator,SWIG_CGAL_Iterator<C2T3::Vertex_iterator,SWIG_Triangulation_3::CGAL_Vertex_handle<C2T3_DT,Point_3> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Surface_mesh_default_triangulation_3_Facet,)
SWIG_CGAL_declare_identifier_of_template_class(Surface_mesh_default_triangulation_3_Facet_iterator,SWIG_CGAL_Iterator<C2T3::Facet_iterator,std::pair<SWIG_Triangulation_3::CGAL_Cell_handle<C2T3_DT,Point_3>,int> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Surface_mesh_default_triangulation_3_Edge,)
SWIG_CGAL_declare_identifier_of_template_class(Surface_mesh_default_triangulation_3_Edge_iterator,SWIG_CGAL_Iterator<C2T3::Edge_iterator,SWIG_CGAL::Triple<SWIG_Triangulation_3::CGAL_Cell_handle<C2T3_DT,Point_3>,int,int> >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Surface_mesh_default_triangulation_3_Edge,)
SWIG_CGAL_declare_identifier_of_template_class(Surface_mesh_default_triangulation_3_Boundary_edges_iterator,SWIG_CGAL_Iterator<C2T3::Boundary_edges_iterator,SWIG_CGAL::Triple<SWIG_Triangulation_3::CGAL_Cell_handle<C2T3_DT,Point_3>,int,int> >)


//main classes
//--C2T3
%typemap(javaimports)      C2T3_wrapper%{import java.util.Collection;%}
SWIG_CGAL_declare_identifier_of_template_class(Complex_2_in_triangulation_3,C2T3_wrapper<C2T3,Delaunay_triangulation_3_wrapper<C2T3_DT,SWIG_Triangulation_3::CGAL_Vertex_handle<C2T3_DT,Point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<C2T3_DT,Point_3>,boost::shared_ptr<C2T3_DT> > >)

//--
SWIG_CGAL_declare_identifier_of_template_class(Surface_mesh_default_criteria_3,Surface_mesh_criteria_3_wrapper<SMDC_3>)
//--
SWIG_CGAL_declare_identifier_of_template_class(Gray_level_image_3,Gray_level_image_3_wrapper<GLI_3>)
//--
%typemap(javaimports)      Implicit_surface_3_wrapper%{import CGAL.Kernel.Sphere_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Implicit_surface_Gray_level_image_3,Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >)

//import Polyhedron_3 wrapper type
SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper

//global functions
%inline %{
  #include <fstream>
  
  void output_surface_facets_to_off(const std::string& s,const Complex_2_in_triangulation_3_SWIG_wrapper& c2t3)
  {
    std::ofstream outfile(s.c_str());
    if (!outfile) std::cerr << "Error cannot create file: " << s << std::endl;
    else  CGAL::output_surface_facets_to_off(outfile,c2t3.get_data());
  }
  
  void output_surface_facets_to_polyhedron(const Complex_2_in_triangulation_3_SWIG_wrapper& c2t3,Polyhedron_3_SWIG_wrapper& poly)
  {
    CGAL::output_surface_facets_to_polyhedron( c2t3.get_data(),poly.get_data() );
  }

  void  make_surface_mesh(Complex_2_in_triangulation_3_SWIG_wrapper& c2t3,const Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >& surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag tag,int nb)
  {
    switch(tag){
      case MANIFOLD_TAG:
        CGAL::make_surface_mesh(c2t3.get_data(),surface.get_data(),criteria.get_data(),CGAL::Manifold_tag(),nb);
      break;
      case MANIFOLD_WITH_BOUNDARY_TAG:
        CGAL::make_surface_mesh(c2t3.get_data(),surface.get_data(),criteria.get_data(),CGAL::Manifold_with_boundary_tag(),nb);
      break;
      case NON_MANIFOLD_TAG:
        CGAL::make_surface_mesh(c2t3.get_data(),surface.get_data(),criteria.get_data(),CGAL::Non_manifold_tag(),nb);
      break;
    }
  }
  void  make_surface_mesh(Complex_2_in_triangulation_3_SWIG_wrapper& c2t3,const Implicit_surface_3_wrapper<IS_GLI_3,Gray_level_image_3_wrapper<GLI_3> >& surface,const Surface_mesh_criteria_3_wrapper<SMDC_3>& criteria, Surface_mesher_tag tag)
  {
    make_surface_mesh(c2t3,surface,criteria,tag,20);
  }
%}

#ifdef SWIG_CGAL_HAS_Surface_mesher_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Surface_mesher/extensions.i"
#endif
