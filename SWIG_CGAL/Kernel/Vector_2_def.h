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
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Segment_2_def.h>
#include <SWIG_CGAL/Kernel/Line_2_def.h>
#include <SWIG_CGAL/Kernel/Ray_2_def.h>
#include <SWIG_CGAL/Kernel/Direction_2_def.h>


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
  Vector_2(const Point_2& a,const Point_2& b):data(a.get_data(),b.get_data()){}
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
//equality functions
  bool equals(const Vector_2& r){return data==r.get_data();}
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Vector_2& r){return data!=r.get_data();}
  #endif
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
};

#endif //SWIG_CGAL_KERNEL_VECTOR_2_DEF_H

//  Vector_2(Null_vector NULL_VECTOR);
//  double v.operator[] ( int i) returns cartesian(i).
//  SWIG_CGAL_FORWARD_CALL_0(Vector_2,transform,Aff_transformation_2)
//  Cartesian_const_iterator v.cartesian_begin () returns an iterator to the Cartesian coordinates of v, starting with the 0th coordinate.
//  Cartesian_const_iterator v.cartesian_end () returns an off the end iterator to the Cartesian coordinates of v.
//Operators
//  Vector_2 v.operator+ ( w) Addition.
//  Vector_2 v.operator- ( w) Subtraction.
//  Vector_2 v.operator- () returns the opposite vector.
//  Kernel::FT v.operator* ( w) returns the scalar product (= inner product) of the two vectors.
//  Vector_2 operator* ( v, Kernel::RT s) Multiplication with a scalar from the right.
//  Vector_2 operator* ( v, Kernel::FT s) Multiplication with a scalar from the right.
//  Vector_2 operator* ( Kernel::RT s, v) Multiplication with a scalar from the left.
//  Vector_2 operator* ( Kernel::FT s, v) Multiplication with a scalar from the left.
//  Vector_2 v.operator/ ( Kernel::RT s) Division by a scalar.

