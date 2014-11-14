// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_SEGMENT_3_DEF_H
#define SWIG_CGAL_KERNEL_SEGMENT_3_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_3.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>

class SWIG_CGAL_KERNEL_DECL Segment_3{
  EPIC_Kernel::Segment_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Segment_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Segment_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Segment_3():data(){}
  inline Segment_3(const Point_3& p1, const Point_3& p2);
//Operations
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_3,source)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_3,target)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_3,min)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Point_3,max)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_3,vertex,int)
  SWIG_CGAL_DECLARE_CALL_AND_REF_1(Point_3,point,int)
  SWIG_CGAL_FORWARD_CALL_0(double,squared_length)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Segment_3,opposite)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_DECLARE_CALL_1(bool,has_on,Point_3)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_3,to_vector)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_3,direction)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Line_3,supporting_line)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_3,bbox)
//Operators
  DEFINE_EQUALITY_OPERATORS(Segment_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Segment_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};





#endif //SWIG_CGAL_KERNEL_SEGMENT_3_DEF_H


//Segment_3<Kernel> s.transform ( Aff_transformation_3<Kernel> t)
//Point_3<Kernel> s.operator[] ( int i)
