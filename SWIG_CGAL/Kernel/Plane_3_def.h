// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_PLANE_3_DEF_H
#define SWIG_CGAL_KERNEL_PLANE_3_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_3.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/Point_2.h>

class SWIG_CGAL_KERNEL_DECL Plane_3{
  EPIC_Kernel::Plane_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Plane_3 cpp_base;  
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Plane_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Plane_3(){}
  Plane_3(double a,double b,double c,double d):data(a,b,c,d){}
  inline Plane_3(const Point_3& p,const Point_3& q,const Point_3& r);
  inline Plane_3(const Point_3& p,const Vector_3& v);
  inline Plane_3(const Point_3& p,const Direction_3& d);
  inline Plane_3(const Line_3& l,const Point_3& p);
  inline Plane_3(const Ray_3& r,const Point_3& p);
  inline Plane_3(const Segment_3& s,const Point_3& p);
//Operations
  SWIG_CGAL_FORWARD_CALL_0(double,a)
  SWIG_CGAL_FORWARD_CALL_0(double,b)
  SWIG_CGAL_FORWARD_CALL_0(double,c)
  SWIG_CGAL_FORWARD_CALL_0(double,d)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_3,projection,Point_3)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Plane_3,opposite)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_3,point)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_3,orthogonal_vector)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Line_3,perpendicular_line,Point_3)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_3,orthogonal_direction)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_3,base1)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_3,base2)
//2D Conversion
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_2,to_2d,Point_3)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_3,to_3d,Point_2)
//Predicates
  SWIG_CGAL_DECLARE_CALL_1(Oriented_side,oriented_side,Point_3)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on,Point_3)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on_positive_side,Point_3)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on_negative_side,Point_3)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on,Line_3)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
//Operators
  DEFINE_EQUALITY_OPERATORS(Plane_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Plane_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};


#endif //SWIG_CGAL_KERNEL_PLANE_3_DEF_H

//Plane_3(const Circle_3& c);
//SWIG_CGAL_FORWARD_CALL_1(bool,has_on,Circle_3)
//Miscellaneous
//Plane_3<Kernel> h.transform ( Aff_transformation_3<Kernel> t)

