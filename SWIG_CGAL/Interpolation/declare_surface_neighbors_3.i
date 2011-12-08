// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBORS_3_H
#define SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBORS_3_H

//typedefs
SWIG_CGAL_import_Delaunay_triangulation_3_SWIG_wrapper
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Point_range_3 std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > %enddef
#else
%define Point_range_3 Generic_input_iterator<Point_3> %enddef
#endif
%{
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef boost::function_output_iterator< Container_writer<Point_3,Point_3::cpp_base > > iPoint_3_output_iterator;
  typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range_3;
  #else
  typedef Generic_output_iterator< Point_3 > iPoint_3_output_iterator;
  typedef Generic_input_iterator<Point_3> Point_range_3;
  #endif
%}

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
SWIG_CGAL_input_iterator_typemap_in(Point_range_3,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",surface_neighbors_3)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(surface_neighbors_certified_3)
#endif
%define iPoint_3_output_iterator boost::function_output_iterator< Container_writer<Point_3,Point_3::cpp_base > >  %enddef
SWIG_CGAL_output_iterator_typemap_in(iPoint_3_output_iterator,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"LCGAL/Kernel/Point_3;")
#else //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
%define iPoint_3_output_iterator Generic_output_iterator< Point_3 >  %enddef
SWIG_CGAL_declare_generic_output_iterator(Point_3_output_iterator,Point_3_output_iterator_nested_iterator,Point_3)
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE


%inline %{
  void surface_neighbors_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,iPoint_3_output_iterator out){
    CGAL::surface_neighbors_3(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),normal.get_data(),out,EPIC_Kernel());
  }
  
  bool surface_neighbors_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,iPoint_3_output_iterator out){
    return CGAL::surface_neighbors_certified_3(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),normal.get_data(),out,EPIC_Kernel()).second;
  }

  bool surface_neighbors_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,double max_distance,iPoint_3_output_iterator out){
    return CGAL::surface_neighbors_certified_3(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),normal.get_data(),max_distance,out,EPIC_Kernel()).second;
  }
  
  void surface_neighbors_3(const Delaunay_triangulation_3_SWIG_wrapper& dt,const Point_3& p,const Vector_3& normal,iPoint_3_output_iterator out,const SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3>& start){
    CGAL::surface_neighbors_3(dt.get_data(),p.get_data(),normal.get_data(),out,start.get_data());
  }
  
  void surface_neighbors_3(const Delaunay_triangulation_3_SWIG_wrapper& dt,const Point_3& p,const Vector_3& normal,iPoint_3_output_iterator out){
    CGAL::surface_neighbors_3(dt.get_data(),p.get_data(),normal.get_data(),out);
  }
%}

#endif //SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBORS_3_H
