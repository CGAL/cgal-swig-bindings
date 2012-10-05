// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_DIRECTION_2_DEF_H
#define SWIG_CGAL_KERNEL_DIRECTION_2_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_2.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Direction_2{
  EPIC_Kernel::Direction_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Direction_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Direction_2(const cpp_base& base):data(base){}
  #endif

//Creation
  Direction_2(double x,double y):data(x,y){}
  inline Direction_2(const Vector_2& v);
  inline Direction_2(const Line_2& l);
  inline Direction_2(const Ray_2& r);
  inline Direction_2(const Segment_2& s);
//Operations
  SWIG_CGAL_FORWARD_CALL_1(double,delta,int)
  SWIG_CGAL_FORWARD_CALL_0(double,dx)
  SWIG_CGAL_FORWARD_CALL_0(double,dy)
  SWIG_CGAL_FORWARD_CALL_2(bool,counterclockwise_in_between,Direction_2,Direction_2)
//Miscellaneous
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_2,vector)
//Operators
  DEFINE_COMPARISON_OPERATORS(Direction_2)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Direction_2,operator-)
//IO
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Direction_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};  

#endif //SWIG_CGAL_KERNEL_DIRECTION_2_DEF_H

//Miscellaneous
//  Direction_2<Kernel>  d.transform ( Aff_transformation_2<Kernel> t)
