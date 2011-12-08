// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_REGULAR_NEIGHBOR_COORDINATES_2_I
#define SWIG_CGAL_INTERPOLATION_DECLARE_REGULAR_NEIGHBOR_COORDINATES_2_I

//import Regular triangulation types
SWIG_CGAL_import_Regular_triangulation_2_SWIG_wrapper
SWIG_CGAL_import_Regular_triangulation_2_Edge_SWIG_wrapper
SWIG_CGAL_import_Regular_triangulation_2_Vertex_handle_SWIG_wrapper

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define RT2_Edge_iterator   std::pair<Input_iterator_wrapper<Regular_triangulation_2_Edge_SWIG_wrapper,CGAL_RT2::Edge>,Input_iterator_wrapper<Regular_triangulation_2_Edge_SWIG_wrapper,CGAL_RT2::Edge> > %enddef
%define RT2_Vertex_iterator std::pair<Input_iterator_wrapper<Regular_triangulation_2_Vertex_handle_SWIG_wrapper,CGAL_RT2::Vertex_handle>,Input_iterator_wrapper<Regular_triangulation_2_Vertex_handle_SWIG_wrapper,CGAL_RT2::Vertex_handle> > %enddef
#else
%define RT2_Edge_iterator   Generic_input_iterator< Regular_triangulation_2_Edge_SWIG_wrapper > %enddef
%define RT2_Vertex_iterator Generic_input_iterator< Regular_triangulation_2_Vertex_handle_SWIG_wrapper > %enddef
#endif

%{
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef boost::function_output_iterator< Container_writer<std::pair<Weighted_point_2,double>,std::pair<Weighted_point_2::cpp_base,double> > > iWeighted_point_2_and_double_output_iterator;
  #else
  typedef Generic_output_iterator< std::pair<Weighted_point_2,double> > iWeighted_point_2_and_double_output_iterator;
  #endif

  typedef std::pair<Weighted_point_2,double> Weighted_point_2_and_double_wrapper;
  typedef std::pair<Weighted_point_2::cpp_base,double> Weighted_point_2_and_double_base;
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef std::pair<Input_iterator_wrapper<Regular_triangulation_2_Edge_SWIG_wrapper,CGAL_RT2::Edge>,Input_iterator_wrapper<Regular_triangulation_2_Edge_SWIG_wrapper,CGAL_RT2::Edge> > RT2_Edge_iterator;
  typedef std::pair<Input_iterator_wrapper<Regular_triangulation_2_Vertex_handle_SWIG_wrapper,CGAL_RT2::Vertex_handle>,Input_iterator_wrapper<Regular_triangulation_2_Vertex_handle_SWIG_wrapper,CGAL_RT2::Vertex_handle> > RT2_Vertex_iterator;
  #else
  typedef Generic_input_iterator<Regular_triangulation_2_Edge_SWIG_wrapper> RT2_Edge_iterator;
  typedef Generic_input_iterator<Regular_triangulation_2_Vertex_handle_SWIG_wrapper> RT2_Vertex_iterator;
  #endif
%}

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define iWeighted_point_2_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Weighted_point_2,double>,std::pair<Weighted_point_2::cpp_base,double> > >  %enddef
SWIG_CGAL_output_iterator_typemap_in(iWeighted_point_2_and_double_output_iterator,Weighted_point_2_and_double_wrapper,Weighted_point_2_and_double,Weighted_point_2_and_double_base,SWIGTYPE_p_std__pairT_Weighted_point_2_double_t,"LCGAL/Interpolation/Weighted_point_2_and_double;")
SWIG_CGAL_input_iterator_typemap_in(RT2_Edge_iterator,Regular_triangulation_2_Edge_SWIG_wrapper,Regular_triangulation_2_Edge,CGAL_RT2::Edge,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_RT2_Weighted_point_2_t_int_t,"(LCGAL/Triangulation_2/Regular_triangulation_2_Edge;)J",regular_neighbor_coordinates_2)
SWIG_CGAL_input_iterator_typemap_in(RT2_Vertex_iterator,Regular_triangulation_2_Vertex_handle_SWIG_wrapper,Regular_triangulation_2_Vertex_handle,CGAL_RT2::Vertex_handle,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_RT2_Weighted_point_2_t_int_t,"(LCGAL/Triangulation_2/Regular_triangulation_2_Vertex_handle;)J",regular_neighbor_coordinates_2)
#else
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
%define iWeighted_point_2_and_double_output_iterator Generic_output_iterator< std::pair<Weighted_point_2,double> > %enddef
%define iWeighted_point_2_and_double std::pair<Weighted_point_2,double> %enddef
SWIG_CGAL_declare_generic_output_iterator(Weighted_point_2_and_double_output_iterator,Weighted_point_2_and_double_output_iterator_nested_iterator,iWeighted_point_2_and_double)
//input iterator
%template(Regular_triangulation_2_Edge_input_iterator) Generic_input_iterator< Regular_triangulation_2_Edge_SWIG_wrapper >; 
%template(Regular_triangulation_2_Vertex_handle_input_iterator) Generic_input_iterator< Regular_triangulation_2_Vertex_handle_SWIG_wrapper >; 
#endif


#ifdef SWIGPYTHON
//to have the type SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_RT2_Weighted_point_2_t_int_t defined
%types(std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>*, std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>);
%template() std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>;
#endif

%inline %{
  std::pair<double,bool> 
  regular_neighbor_coordinates_2(const Regular_triangulation_2_SWIG_wrapper& dt,const Weighted_point_2& p,iWeighted_point_2_and_double_output_iterator out,const SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>& start)
  {
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,start.get_data()) );
  }

  std::pair<double,bool> 
  regular_neighbor_coordinates_2(const Regular_triangulation_2_SWIG_wrapper& dt,const Weighted_point_2& p,iWeighted_point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),p.get_data(),out) );
  }

  std::pair<double,bool>
  regular_neighbor_coordinates_2(const Regular_triangulation_2_SWIG_wrapper& dt,const Weighted_point_2& p,iWeighted_point_2_and_double_output_iterator out,RT2_Edge_iterator erange,RT2_Vertex_iterator vrange)
  {
    //we need to make a copy as the algorithm uses operator-- on the iterator, which is not defined in our case.
    std::list<CGAL_RT2::Edge> edges;
    std::copy(SWIG_CGAL::get_begin(erange),SWIG_CGAL::get_end(erange),std::back_inserter(edges));
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,edges.begin(),edges.end(),SWIG_CGAL::get_begin(vrange),SWIG_CGAL::get_end(vrange)) );
  }
  
  std::pair<double,bool> 
  regular_neighbor_coordinates_2(const Regular_triangulation_2_SWIG_wrapper& dt,const SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2>& vh,iWeighted_point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),vh.get_data(),out) );
  }
%}

#endif // SWIG_CGAL_INTERPOLATION_DECLARE_REGULAR_NEIGHBOR_COORDINATES_2_I
