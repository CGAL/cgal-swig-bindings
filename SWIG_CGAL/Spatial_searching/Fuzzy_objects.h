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
  cpp_base& get_data_ref() {return data;}
  #endif
  
//Creation
  Fuzzy_sphere_wrapper(const Point_d& center, double radius, double epsilon):data(center.get_data(),radius,epsilon){}
  Fuzzy_sphere_wrapper(const Point_d& center, double radius):data(center.get_data(),radius){}
//Operations
  FORWARD_CALL_1(bool,contains,Point_d)
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
  cpp_base& get_data_ref() {return data;}
  #endif
  
//Creation
  Fuzzy_iso_box_wrapper (const Point_d& p,const Point_d& q, double epsilon):data(p.get_data(),q.get_data(),epsilon){}
  Fuzzy_iso_box_wrapper (const Point_d& p,const Point_d& q):data(p.get_data(),q.get_data()){}
//Operations
  FORWARD_CALL_1(bool,contains,Point_d)    
};

//Operations
//  bool  b.inner_range_intersects ( Kd_tree_rectangle<FT> rectangle)
//  bool  b.outer_range_contains ( Kd_tree_rectangle<FT> rectangle)






#endif //SWIG_CGAL_SPATIAL_SEARCHING_FUZZY_OBJECTS_H
