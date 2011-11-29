// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_SPATIAL_SEARCHING_FUZZY_OBJECTS_H
#define SWIG_CGAL_SPATIAL_SEARCHING_FUZZY_OBJECTS_H

#include <SWIG_CGAL/Common/Macros.h>


template <class Cpp_base,class Point_d>
class Fuzzy_sphere_wrapper
{
  Cpp_base data;
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  
//Creation
  Fuzzy_sphere_wrapper(const Point_d& center, double radius, double epsilon):data(internal::make_conversion(center),radius,epsilon){}
  Fuzzy_sphere_wrapper(const Point_d& center, double radius):data(internal::make_conversion(center),radius){}
//Operations
  SWIG_CGAL_FORWARD_CALL_1(bool,contains,Point_d)
//Deep copy
  typedef Fuzzy_sphere_wrapper<Cpp_base,Point_d> Self;
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
};

//Operations
//  bool  s.inner_range_intersects ( Kd_tree_rectangle<FT> rectangle)
//  bool  s.outer_range_contains ( Kd_tree_rectangle<FT> rectangle)



template <class Cpp_base,class Point_d>
class Fuzzy_iso_box_wrapper
{
  Cpp_base data;
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  
//Creation
  Fuzzy_iso_box_wrapper (const Point_d& p,const Point_d& q, double epsilon):data(internal::make_conversion(p),internal::make_conversion(q),epsilon){}
  Fuzzy_iso_box_wrapper (const Point_d& p,const Point_d& q):data(internal::make_conversion(p),internal::make_conversion(q)){}
//Operations
  SWIG_CGAL_FORWARD_CALL_1(bool,contains,Point_d)    
//Deep copy
  typedef Fuzzy_iso_box_wrapper<Cpp_base,Point_d> Self;
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
};

//Operations
//  bool  b.inner_range_intersects ( Kd_tree_rectangle<FT> rectangle)
//  bool  b.outer_range_contains ( Kd_tree_rectangle<FT> rectangle)






#endif //SWIG_CGAL_SPATIAL_SEARCHING_FUZZY_OBJECTS_H
