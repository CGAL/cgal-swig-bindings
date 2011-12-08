// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBOR_COORDINATES_3_H
#define SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBOR_COORDINATES_3_H

//typedefs
%define Point_3_and_double_base std::pair<Point_3::cpp_base,double> %enddef
%define Point_3_and_double_wrapper std::pair<Point_3,double> %enddef
%{
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef boost::function_output_iterator< Container_writer<std::pair<Point_3,double>,std::pair<Point_3::cpp_base,double> > >  iPoint_3_and_double_output_iterator;
  #else
  typedef Generic_output_iterator<std::pair<Point_3,double> >  iPoint_3_and_double_output_iterator;
  #endif
  typedef std::pair<Point_3::cpp_base,double> Point_3_and_double_base;
  typedef std::pair<Point_3,double> Point_3_and_double_wrapper;
%}

#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(surface_neighbor_coordinates_certified_3)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(surface_neighbor_coordinates_3)
#endif

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define iPoint_3_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Point_3,double>,std::pair<Point_3::cpp_base,double> > >  %enddef
SWIG_CGAL_output_iterator_typemap_in(iPoint_3_and_double_output_iterator,Point_3_and_double_wrapper,Point_3_and_double,Point_3_and_double_base,SWIGTYPE_p_std__pairT_Point_3_double_t,"LCGAL/Interpolation/Point_3_and_double;")
#else
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
%define iPoint_3_and_double_output_iterator Generic_output_iterator<std::pair<Point_3,double> >  %enddef
%define iPoint_3_and_double std::pair<Point_3,double>   %enddef
SWIG_CGAL_declare_generic_output_iterator(Point_3_and_double_output_iterator,Point_3_and_double_output_iterator_nested_iterator,iPoint_3_and_double)
#endif


%inline %{
  std::pair<double, bool > surface_neighbor_coordinates_3 (Point_range_3 range,const Point_3& p,const Vector_3& normal,iPoint_3_and_double_output_iterator out){
    return internal::extract_pair(CGAL::surface_neighbor_coordinates_3(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),normal.get_data(),out,EPIC_Kernel()));
  }

  SWIG_CGAL::Triple<double, bool, bool > surface_neighbor_coordinates_certified_3 (Point_range_3 range,const Point_3& p,const Vector_3& normal,iPoint_3_and_double_output_iterator out)  {
    return internal::extract_triple(CGAL::surface_neighbor_coordinates_certified_3(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),normal.get_data(),out,EPIC_Kernel()));
  }

  SWIG_CGAL::Triple<double, bool, bool > surface_neighbor_coordinates_certified_3 (Point_range_3 range,const Point_3& p,const Vector_3& normal,double max_distance,iPoint_3_and_double_output_iterator out){
    return internal::extract_triple(CGAL::surface_neighbor_coordinates_certified_3(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),normal.get_data(),max_distance,out,EPIC_Kernel()));
  }

  std::pair< double, bool > surface_neighbor_coordinates_3(const Delaunay_triangulation_3_SWIG_wrapper& dt,const Point_3& p,const Vector_3& normal,iPoint_3_and_double_output_iterator out,const SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3>& start){
    return internal::extract_pair(CGAL::surface_neighbor_coordinates_3(dt.get_data(),p.get_data(),normal.get_data(),out,start.get_data()));
  }

  std::pair< double, bool > surface_neighbor_coordinates_3(const Delaunay_triangulation_3_SWIG_wrapper& dt,const Point_3& p,const Vector_3& normal,iPoint_3_and_double_output_iterator out){
    return internal::extract_pair(CGAL::surface_neighbor_coordinates_3(dt.get_data(),p.get_data(),normal.get_data(),out));
  }
%}


#endif //SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBOR_COORDINATES_3_H
