// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_RAY_2_DEF_H
#define SWIG_CGAL_KERNEL_RAY_2_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_2.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Ray_2{
  EPIC_Kernel::Ray_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Ray_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Ray_2(const cpp_base& base):data(base){}
  #endif

//Creation
  inline Ray_2(const Point_2& p,const Point_2& q);
  inline Ray_2(const Point_2& p,const Direction_2& d);
  inline Ray_2(const Point_2& p,const Vector_2& v);
  inline Ray_2(const Point_2& p,const Line_2& l);
//Operations
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_2,source)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_2,point,int)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_2,direction)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_2,to_vector)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Line_2,supporting_line)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Ray_2,opposite)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_horizontal)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_vertical)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on,Point_2)
  SWIG_CGAL_DECLARE_CALL_1(bool,collinear_has_on,Point_2)
//Operators
  DEFINE_EQUALITY_OPERATORS(Ray_2)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Ray_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_RAY_2_DEF_H

//Miscellaneous
// Ray_2<Kernel>  r.transform ( Aff_transformation_2<Kernel> t)

