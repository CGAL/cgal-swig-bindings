#ifndef SWIG_CGAL_KERNEL_VECTOR_2_H
#define SWIG_CGAL_KERNEL_VECTOR_2_H

#include <SWIG_CGAL/Kernel/include_conflicts_2.h>

#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Segment_2.h>
#include <SWIG_CGAL/Kernel/Line_2.h>
#include <SWIG_CGAL/Kernel/Ray_2.h>
#include <SWIG_CGAL/Kernel/Direction_2.h>


class SWIG_CGAL_KERNEL_DECL Vector_2{
  EPIC_Kernel::Vector_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Vector_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Vector_2(const cpp_base& base):data(base){}
  #endif //SWIG
//Creation
  Vector_2();
  Vector_2(const Point_2& a,const Point_2& b);
  Vector_2(const Segment_2& s);
  Vector_2(const Ray_2& r);
  Vector_2(const Line_2& l);
  Vector_2(int x, int y);
  Vector_2(double x, double y);
//Operations
  FORWARD_CALL_0(double,x)
  FORWARD_CALL_0(double,y)
  FORWARD_CALL_1(double,cartesian,int)
  FORWARD_CALL_0(int,dimension)
  DECLARE_CALL_AND_REF_0(Direction_2,direction)
  FORWARD_CALL_AND_REF_1(Vector_2,perpendicular,Orientation)
  FORWARD_CALL_0(double,squared_length)
//
  bool equals(const Vector_2&);
  std::string toString();
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Vector_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_VECTOR_2_H

//  Vector_2(Null_vector NULL_VECTOR);
//  double v.operator[] ( int i) returns cartesian(i).
//  FORWARD_CALL_0(Vector_2,transform,Aff_transformation_2)
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

