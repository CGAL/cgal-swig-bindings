// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_CONVEX_HULL_2_H
#define SWIG_CGAL_CONVEX_HULL_2_H

#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_bykat.h>
#include <CGAL/ch_eddy.h>
#include <CGAL/ch_selected_extreme_points_2.h>
#include <CGAL/ch_graham_andrew.h> 
#include <CGAL/ch_jarvis.h>
#include <CGAL/ch_melkman.h>
#include <CGAL/convexity_check_2.h> 
#include <CGAL/convex_hull_2.h> 


#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>

#include <SWIG_CGAL/Kernel/Point_2.h>

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Kernel_object>
struct Kernel_iterator_helper{
  typedef typename internal::Converter<Kernel_object>::result_type Base;
  typedef std::pair<Input_iterator_wrapper<Kernel_object,Base>,Input_iterator_wrapper<Kernel_object,Base> > input;
  typedef boost::function_output_iterator< Container_writer<Kernel_object,Base> >                                       output;
};

typedef Kernel_iterator_helper<Point_2>::input       Point_range; 
typedef Kernel_iterator_helper<Point_2>::output      Point_output_iterator; 
#else
typedef Generic_input_iterator<Point_2>  Point_range;
typedef Generic_output_iterator<Point_2>  Point_output_iterator;
#endif

//using input iterators
void  convex_hull_2 (Point_range range, Point_output_iterator result){ CGAL::convex_hull_2( range.first, range.second, result ); }
void  ch_bykat (Point_range range, Point_output_iterator result){ CGAL::ch_bykat( range.first, range.second, result ); }
void  ch_eddy (Point_range range, Point_output_iterator result){ CGAL::ch_eddy( range.first, range.second, result ); }
void  ch_graham_andrew (Point_range range, Point_output_iterator result){ CGAL::ch_graham_andrew( range.first, range.second, result ); }
void  ch_melkman (Point_range range, Point_output_iterator result){ CGAL::ch_melkman( range.first, range.second, result ); }
void  ch_jarvis (Point_range range, Point_output_iterator result){ CGAL::ch_jarvis( range.first, range.second, result ); }
void  lower_hull_points_2 (Point_range range, Point_output_iterator result){ CGAL::lower_hull_points_2( range.first, range.second, result ); }
void  upper_hull_points_2 (Point_range range, Point_output_iterator result){ CGAL::upper_hull_points_2( range.first, range.second, result ); }

//using forward or bidirectionnal iterators
void  ch_akl_toussaint (Point_range range, Point_output_iterator result){ 
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  CGAL::ch_akl_toussaint( points.begin(), points.end(), result ); 
}

void  ch_graham_andrew_scan (Point_range range, Point_output_iterator result){ 
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  CGAL::ch_graham_andrew_scan( points.begin(), points.end(), result ); 
}

void ch_jarvis_march (Point_range range, const Point_2& start_p, const Point_2& stop_p, Point_output_iterator result){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  ch_jarvis_march(points.begin(), points.end(), start_p.get_data(), stop_p.get_data(), result);
}

bool is_ccw_strongly_convex_2 (Point_range range){ 
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  return CGAL::is_ccw_strongly_convex_2(points.begin(), points.end()); 
}
bool is_cw_strongly_convex_2 (Point_range range){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  return CGAL::is_cw_strongly_convex_2(points.begin(), points.end()); 
}

void ch_n_point (Point_range range, Point_2& n){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator it;
  CGAL::ch_n_point(points.begin(), points.end(), it);
  n=Point_2( *it );
}

void ch_s_point (Point_range range, Point_2& s){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator it;
  CGAL::ch_s_point(points.begin(), points.end(), it);
  s=Point_2( *it );
}

void ch_e_point (Point_range range, Point_2& e){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator it;
  CGAL::ch_e_point(points.begin(), points.end(), it);
  e=Point_2( *it );
}

void ch_w_point (Point_range range, Point_2& w){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator it;
  CGAL::ch_w_point(points.begin(), points.end(), it);
  w=Point_2( *it );
}

void ch_we_point (Point_range range, Point_2& w, Point_2& e){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator ite,itw;
  CGAL::ch_we_point(points.begin(), points.end(), itw, ite);
  w=Point_2( *itw );
  e=Point_2( *ite );
}

void ch_ns_point (Point_range range, Point_2& n, Point_2& s){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator itn,its;
  CGAL::ch_ns_point(points.begin(), points.end(), itn, its);
  n=Point_2( *itn );
  s=Point_2( *its );
}

void ch_nswe_point (Point_range range, Point_2& n, Point_2& s, Point_2& w, Point_2& e){
  //the function requires a forward iterator so we copy it....
  std::vector<Point_2::cpp_base> points(range.first,range.second);
  std::vector<Point_2::cpp_base>::iterator itn,its,itw,ite;
  CGAL::ch_nswe_point(points.begin(), points.end(), itn, its, itw, ite);
  n=Point_2( *itn );
  s=Point_2( *its );
  w=Point_2( *itw );
  e=Point_2( *ite );
}

#endif //SWIG_CGAL_CONVEX_HULL_2_H
