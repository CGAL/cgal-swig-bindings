// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_VECTOR_2_DEF_H
#define SWIG_CGAL_KERNEL_VECTOR_2_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_2.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Vector_2{
  EPIC_Kernel::Vector_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Vector_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Vector_2(const cpp_base& base):data(base){}
  #endif

//Creation
  Vector_2():data(){}
  Vector_2(const Null_vector&):data(CGAL::NULL_VECTOR){}
  inline Vector_2(const Point_2& a,const Point_2& b);
  inline Vector_2(const Segment_2& s);
  inline Vector_2(const Ray_2& r);
  inline Vector_2(const Line_2& l);
  Vector_2(int x, int y):data(x,y){}
  Vector_2(double x, double y):data(x,y){}
//Operations
  SWIG_CGAL_FORWARD_CALL_0(double,x)
  SWIG_CGAL_FORWARD_CALL_0(double,y)
  SWIG_CGAL_FORWARD_CALL_1(double,cartesian,int)
  SWIG_CGAL_FORWARD_CALL_0(int,dimension)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_2,direction)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vector_2,perpendicular,Orientation)
  SWIG_CGAL_FORWARD_CALL_0(double,squared_length)
//Operators
  SWIG_CGAL_FORWARD_CALL_1(Vector_2,operator+,Vector_2)
  SWIG_CGAL_FORWARD_CALL_1(Vector_2,operator-,Vector_2)
  SWIG_CGAL_FORWARD_CALL_0(Vector_2,operator-)
  double operator*(const Vector_2& v) const {
    return get_data() * v.get_data();
  }
  Vector_2 operator*(double d) const {
    return Vector_2( d * get_data() );
  }
  SWIG_CGAL_FORWARD_CALL_1(Vector_2,operator/,double)
  inline bool operator==(const Null_vector&){return get_data()==CGAL::NULL_VECTOR;}
  DEFINE_EQUALITY_OPERATORS(Vector_2)
//Operators added for convenience
  Vector_2& operator+=(Vector_2& v) {get_data()=get_data()+v.get_data(); return *this;}
  Vector_2& operator-=(Vector_2& v) {get_data()=get_data()-v.get_data(); return *this;}
  Vector_2& operator*=(double d) { get_data()=d*get_data(); return *this;}
  Vector_2& operator/=(double d) { get_data()=get_data()/d; return *this;}
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Vector_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
//Operations added for convenience
  void normalize(){
    get_data()=get_data()/sqrt( get_data().squared_length() );
  }
};

#endif //SWIG_CGAL_KERNEL_VECTOR_2_DEF_H

//  Vector_2(Null_vector NULL_VECTOR);
//  double v.operator[] ( int i) returns cartesian(i).
//  SWIG_CGAL_FORWARD_CALL_0(Vector_2,transform,Aff_transformation_2)
//  Cartesian_const_iterator v.cartesian_begin () returns an iterator to the Cartesian coordinates of v, starting with the 0th coordinate.
//  Cartesian_const_iterator v.cartesian_end () returns an off the end iterator to the Cartesian coordinates of v.

