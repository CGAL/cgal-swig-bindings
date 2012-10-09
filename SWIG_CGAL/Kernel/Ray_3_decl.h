// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_RAY_3_DEF_H
#define SWIG_CGAL_KERNEL_RAY_3_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_3.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Common/Macros.h>

class SWIG_CGAL_KERNEL_DECL Ray_3{
  EPIC_Kernel::Ray_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Ray_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Ray_3(const cpp_base& base):data(base){}
  #endif

//Creation
  inline Ray_3(const Point_3& p,const Point_3& q);
  inline Ray_3(const Point_3& p,const Direction_3& d);
  inline Ray_3(const Point_3& p,const Vector_3& v);
  inline Ray_3(const Point_3& p,const Line_3& l);
//Operations
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_3,source)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_3,point,int)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_3,direction)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_3,to_vector)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Line_3,supporting_line)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Ray_3,opposite)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on,Point_3)
//Operators
  DEFINE_EQUALITY_OPERATORS(Ray_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Ray_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_RAY_3_DEF_H
//  Ray_3<Kernel> r.transform ( Aff_transformation_3<Kernel> t)
