// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_NATURAL_NEIGHBOR_COORDINATES_2_I
#define SWIG_CGAL_INTERPOLATION_DECLARE_NATURAL_NEIGHBOR_COORDINATES_2_I

//import Delaunay_triangulation_2 types
SWIG_CGAL_import_Delaunay_triangulation_2_SWIG_wrapper
SWIG_CGAL_import_Delaunay_triangulation_2_Edge_SWIG_wrapper

%{
  typedef std::pair<Point_2,double> Point_2_and_double_wrapper;
  typedef std::pair<Point_2::cpp_base,double> Point_2_and_double_base;
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef std::pair<Input_iterator_wrapper<Delaunay_triangulation_2_Edge_SWIG_wrapper,CGAL_DT2::Edge>,Input_iterator_wrapper<Delaunay_triangulation_2_Edge_SWIG_wrapper,CGAL_DT2::Edge> > DT2_Edge_iterator;
  typedef boost::function_output_iterator< Container_writer<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > > iPoint_2_and_double_output_iterator;
  #else
  typedef Generic_input_iterator< Delaunay_triangulation_2_Edge_SWIG_wrapper > DT2_Edge_iterator;
  typedef Generic_output_iterator< std::pair<Point_2,double> > iPoint_2_and_double_output_iterator;
  #endif  
%}

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define DT2_Edge_iterator std::pair<Input_iterator_wrapper<Delaunay_triangulation_2_Edge_SWIG_wrapper,CGAL_DT2::Edge>,Input_iterator_wrapper<Delaunay_triangulation_2_Edge_SWIG_wrapper,CGAL_DT2::Edge> > %enddef
%define iPoint_2_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > >  %enddef
SWIG_CGAL_output_iterator_typemap_in(iPoint_2_and_double_output_iterator,Point_2_and_double_wrapper,Point_2_and_double,Point_2_and_double_base,SWIGTYPE_p_std__pairT_Point_2_double_t,"LCGAL/Interpolation/Point_2_and_double;")
SWIG_CGAL_input_iterator_typemap_in(DT2_Edge_iterator,Delaunay_triangulation_2_Edge_SWIG_wrapper,Delaunay_triangulation_2_Edge,CGAL_DT2::Edge,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_DT2_Point_2_t_int_t,"(LCGAL/Triangulation_2/Delaunay_triangulation_2_Edge;)J",natural_neighbor_coordinates_2)
#else
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
%define iPoint_2_and_double_output_iterator Generic_output_iterator< std::pair<Point_2,double> >  %enddef
%define iPoint_2_and_double std::pair<Point_2,double> %enddef
SWIG_CGAL_declare_generic_output_iterator(Point_2_and_double_output_iterator,Point_2_and_double_output_iterator_nested_iterator,iPoint_2_and_double)
%define DT2_Edge_iterator  Generic_input_iterator< Delaunay_triangulation_2_Edge_SWIG_wrapper > %enddef
//input iterator
%template(Delaunay_triangulation_2_Edge_input_iterator)  Generic_input_iterator< Delaunay_triangulation_2_Edge_SWIG_wrapper >;
#endif


#ifdef SWIGPYTHON
//to have the type SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_DT2_Point_2_t_int_t defined
%types(std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>*, std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>);
%template() std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>;
#endif
%inline %{
  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const Delaunay_triangulation_2_SWIG_wrapper& dt,const Point_2& p,iPoint_2_and_double_output_iterator out,const SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>& start)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,start.get_data()) );
  }

  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const Delaunay_triangulation_2_SWIG_wrapper& dt,const Point_2& p,iPoint_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out) );
  }

  std::pair<double,bool>
  natural_neighbor_coordinates_2(const Delaunay_triangulation_2_SWIG_wrapper& dt,const Point_2& p,iPoint_2_and_double_output_iterator out,DT2_Edge_iterator its)
  {
    //we need to make a copy as the algorithm uses operator-- on the iterator, which is not defined in our case.
    std::list<CGAL_DT2::Edge> edges;
    std::copy(SWIG_CGAL::get_begin(its),SWIG_CGAL::get_end(its),std::back_inserter(edges));
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,edges.begin(),edges.end()) );
  }
  
  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const Delaunay_triangulation_2_SWIG_wrapper& dt,const SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>& vh,iPoint_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),vh.get_data(),out) );
  }
%}

#endif // SWIG_CGAL_INTERPOLATION_DECLARE_NATURAL_NEIGHBOR_COORDINATES_2_I
