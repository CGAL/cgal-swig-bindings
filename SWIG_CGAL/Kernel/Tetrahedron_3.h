// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_TETRAHEDRON_3_H
#define SWIG_CGAL_KERNEL_TETRAHEDRON_3_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Common/Macros.h>


class SWIG_CGAL_KERNEL_DECL Tetrahedron_3{
  EPIC_Kernel::Tetrahedron_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Tetrahedron_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Tetrahedron_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Tetrahedron_3():data(){}
  Tetrahedron_3(const Point_3& p,const Point_3& q,const Point_3& r,const Point_3& s):data(p.get_data(),q.get_data(),r.get_data(),s.get_data()){}
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_3,vertex,int)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_positive_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_negative_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_0(Orientation,orientation)
  SWIG_CGAL_FORWARD_CALL_1(Oriented_side,oriented_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_3)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(double,volume)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_3,bbox)
//Operators
  DEFINE_EQUALITY_OPERATORS(Tetrahedron_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Tetrahedron_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_TETRAHEDRON_3_H


//Miscellaneous
//  Tetrahedron_3<Kernel>  t.transform ( Aff_transformation_3<Kernel> at)
