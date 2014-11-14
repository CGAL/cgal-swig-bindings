// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_TRIANGLE_3_H
#define SWIG_CGAL_KERNEL_TRIANGLE_3_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <SWIG_CGAL/Common/Macros.h>


class SWIG_CGAL_KERNEL_DECL Triangle_3{
  EPIC_Kernel::Triangle_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Triangle_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Triangle_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Triangle_3():data(){}
  Triangle_3(const Point_3& p,const Point_3& q,const Point_3& r):data(p.get_data(),q.get_data(),r.get_data()){}
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_3,vertex,int)
  SWIG_CGAL_FORWARD_CALL_0(Plane_3,supporting_plane)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on,Point_3)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(double,squared_area)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_3,bbox)
//Operators
  DEFINE_EQUALITY_OPERATORS(Triangle_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Triangle_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_TRIANGLE_3_H

//Miscellaneous
//  Triangle_3<Kernel>  t.transform ( Aff_transformation_3<Kernel> at)
