// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_VECTOR_3_DEF_H
#define SWIG_CGAL_KERNEL_VECTOR_3_DEF_H

#include <sstream>

#include <SWIG_CGAL/Kernel/include_conflicts_3.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/enum.h>

class SWIG_CGAL_KERNEL_DECL Vector_3{
  EPIC_Kernel::Vector_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Vector_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Vector_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Vector_3(){}
  Vector_3(const Null_vector&):data(CGAL::NULL_VECTOR){}
  inline Vector_3(const Point_3& a,const Point_3& b);
  inline Vector_3(const Segment_3& s);
  inline Vector_3(const Ray_3& r);
  inline Vector_3(const Line_3& l);
  Vector_3(int x, int y, int z):data(x,y,z){}
  Vector_3(double x, double y, double z):data(x,y,z){}
//Operations
  SWIG_CGAL_FORWARD_CALL_0(double,x)
  SWIG_CGAL_FORWARD_CALL_0(double,y)
  SWIG_CGAL_FORWARD_CALL_0(double,z)
  SWIG_CGAL_FORWARD_CALL_1(double,cartesian,int)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_3,direction)
  SWIG_CGAL_FORWARD_CALL_0(double,squared_length)
  SWIG_CGAL_FORWARD_CALL_0(int,dimension)
//Operators
  SWIG_CGAL_FORWARD_CALL_1(Vector_3,operator+,Vector_3)
  SWIG_CGAL_FORWARD_CALL_1(Vector_3,operator-,Vector_3)
  SWIG_CGAL_FORWARD_CALL_0(Vector_3,operator-)
  double operator*(const Vector_3& v) const {
    return get_data() * v.get_data();
  }
  Vector_3 operator*(double d) const {
    return Vector_3( d* get_data() );
  }
  SWIG_CGAL_FORWARD_CALL_1(Vector_3,operator/,double)
  inline bool operator==(const Null_vector&){return get_data()==CGAL::NULL_VECTOR;}
  DEFINE_EQUALITY_OPERATORS(Vector_3)
//Operators added for convenience
  Vector_3& operator+=(Vector_3& v) {get_data()=get_data()+v.get_data(); return *this;}
  Vector_3& operator-=(Vector_3& v) {get_data()=get_data()-v.get_data(); return *this;}
  Vector_3& operator*=(double d) { get_data()=d*get_data(); return *this;}
  Vector_3& operator/=(double d) { get_data()=get_data()/d; return *this;}
//added for convenience not allowed in CGAL
  void set_coordinates(double x,double y,double z){
    data=cpp_base(x,y,z);
  };

  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }

//Deep copy
  typedef Vector_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
//Operations added for convenience
  void normalize(){
    get_data()=get_data()/sqrt( get_data().squared_length() );
  }
};

#endif //SWIG_CGAL_KERNEL_VECTOR_3_DEF_H

//Kernel::FT v.operator[] ( int i) returns cartesian(i).
//Cartesian_const_iterator v.cartesian_begin () returns an iterator to the Cartesian coordinates of v, starting with the 0th coordinate.
//Cartesian_const_iterator v.cartesian_end () returns an off the end iterator to the Cartesian coordinates of v.
//Vector_3<Kernel> v.transform ( Aff_transformation_3<Kernel> t)

