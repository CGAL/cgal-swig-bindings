// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_TRIANGLE_2_H
#define SWIG_CGAL_KERNEL_TRIANGLE_2_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Bbox_2.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Common/Macros.h>


class SWIG_CGAL_KERNEL_DECL Triangle_2{
  EPIC_Kernel::Triangle_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Triangle_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Triangle_2(const cpp_base& base):data(base){}
  #endif

//Creation
  Triangle_2():data(){}
  Triangle_2(const Point_2& p,const Point_2& q,const Point_2& r):data(p.get_data(),q.get_data(),r.get_data()){}
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,vertex,int)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_positive_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_negative_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_0(Orientation,orientation)
  SWIG_CGAL_FORWARD_CALL_1(Oriented_side,oriented_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_2)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Triangle_2,opposite)
  SWIG_CGAL_FORWARD_CALL_0(double,area)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_2,bbox)
//Operators
  DEFINE_EQUALITY_OPERATORS(Triangle_2)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Triangle_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_TRIANGLE_2_H


//Miscellaneous
// Triangle_2<Kernel>   t.transform ( Aff_transformation_2<Kernel> at)
