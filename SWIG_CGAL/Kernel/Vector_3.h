#ifndef SWIG_CGAL_KERNEL_VECTOR_3_H
#define SWIG_CGAL_KERNEL_VECTOR_3_H

#include <SWIG_CGAL/Kernel/include_conflicts_3.h>

#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Line_3.h>
#include <SWIG_CGAL/Kernel/Direction_3.h>


class SWIG_CGAL_KERNEL_DECL Vector_3{
  EPIC_Kernel::Vector_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Vector_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Vector_3(const cpp_base& base):data(base){}
  #endif //SWIG
//Creation
  Vector_3();
  Vector_3(const Point_3& a,const Point_3& b);
  Vector_3(const Segment_3& s);
  Vector_3(const Ray_3& r);
  Vector_3(const Line_3& l);
  Vector_3(int x, int y, int z);
  Vector_3(double x, double y, double z);
//Operations
  SWIG_CGAL_FORWARD_CALL_0(double,x)
  SWIG_CGAL_FORWARD_CALL_0(double,y)
  SWIG_CGAL_FORWARD_CALL_0(double,z)
  SWIG_CGAL_FORWARD_CALL_1(double,cartesian,int)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_3,direction)
  SWIG_CGAL_FORWARD_CALL_0(double,squared_length)
  SWIG_CGAL_FORWARD_CALL_0(int,dimension)
//

  void set_coordinates(double x,double y,double z){
    data=cpp_base(x,y,z);
  };

  bool equals(const Vector_3&);
  std::string toString();
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Vector_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_VECTOR_3_H

//Kernel::FT v.operator[] ( int i) returns cartesian(i).
//Cartesian_const_iterator v.cartesian_begin () returns an iterator to the Cartesian coordinates of v, starting with the 0th coordinate.
//Cartesian_const_iterator v.cartesian_end () returns an off the end iterator to the Cartesian coordinates of v.
//Vector_3<Kernel> v.transform ( Aff_transformation_3<Kernel> t)
//Operators
//Vector_3<Kernel> v.operator+ ( w) Addition.
//Vector_3<Kernel> v.operator- ( w) Subtraction.
//Vector_3<Kernel> v.operator- () Returns the opposite vector.
//Kernel::FT v.operator* ( w) returns the scalar product (= inner product) of the two vectors.
//Vector_3<Kernel> operator* ( v, Kernel::RT s) Multiplication with a scalar from the right.
//Vector_3<Kernel> operator* ( v, Kernel::FT s) Multiplication with a scalar from the right.
//Vector_3<Kernel> operator* ( Kernel::RT s, v) Multiplication with a scalar from the left.
//Vector_3<Kernel> operator* ( Kernel::FT s, v) Multiplication with a scalar from the left.
//Vector_3<Kernel> v.operator/ ( Kernel::RT s) Division by a scalar.

