// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_SPHERE_3_H
#define SWIG_CGAL_KERNEL_SPHERE_3_H

#include <sstream>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>
#include <SWIG_CGAL/Kernel/enum.h>

class SWIG_CGAL_KERNEL_DECL Sphere_3{
  EPIC_Kernel::Sphere_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Sphere_3 cpp_base;  
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Sphere_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Sphere_3(const Point_3& center, double squared_radius, Orientation o):data(center.get_data(),squared_radius,internal::make_conversion(o)){}
  Sphere_3(const Point_3& center, double squared_radius):data(center.get_data(),squared_radius){}
  Sphere_3(Point_3 p, Point_3 q, Point_3 r, Point_3 s):data(p.get_data(),q.get_data(),r.get_data(),s.get_data()){}
  Sphere_3(Point_3 p, Point_3 q, Point_3 r, Orientation o):data(p.get_data(),q.get_data(),r.get_data(),internal::make_conversion(o)){}
  Sphere_3(Point_3 p, Point_3 q, Point_3 r):data(p.get_data(),q.get_data(),r.get_data()){}
  Sphere_3(Point_3 p, Point_3 q, Orientation o):data(p.get_data(),q.get_data(),internal::make_conversion(o)){}
  Sphere_3(Point_3 p, Point_3 q):data(p.get_data(),q.get_data()){}
//  Sphere_3(Point_3 center, Orientation o):data(center.get_data(),internal::make_conversion(o)){}  
  Sphere_3(Point_3 center):data(center.get_data()){}
//Access Functions
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_3,center)
  SWIG_CGAL_FORWARD_CALL_0(double,squared_radius)
  SWIG_CGAL_FORWARD_CALL_0(Orientation,orientation)  
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(Oriented_side,oriented_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_positive_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_negative_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on,Point_3)
//  SWIG_CGAL_FORWARD_CALL_1(bool,has_on ( Circle_3<Kernel> p)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Sphere_3,opposite)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_3,bbox)
//Operators
  DEFINE_EQUALITY_OPERATORS(Sphere_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();    
  }
//Deep copy
  typedef Sphere_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_SPHERE_3_H


//Creation
// Sphere_3<Kernel> c ( Circle_3<Kernel> c);
//Miscellaneous
//  Sphere_3<Kernel>  c.orthogonal_transform ( Aff_transformation_3<Kernel> at)  
