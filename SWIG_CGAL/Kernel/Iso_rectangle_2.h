// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_ISO_RECTANGLE_2_H
#define SWIG_CGAL_KERNEL_ISO_RECTANGLE_2_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Bbox_2.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Common/Macros.h>


class SWIG_CGAL_KERNEL_DECL Iso_rectangle_2
{
  EPIC_Kernel::Iso_rectangle_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Iso_rectangle_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Iso_rectangle_2(const cpp_base& base):data(base){}
  #endif
//Creation
  Iso_rectangle_2(Point_2& p,Point_2& q):data(p.get_data(),q.get_data()){}
  Iso_rectangle_2(Point_2& p,Point_2& q,int i):data(p.get_data(),q.get_data(),i){}
  Iso_rectangle_2(Point_2& left, Point_2& right, Point_2& bottom, Point_2& top):data(left.get_data(),right.get_data(),bottom.get_data(),top.get_data()){}
  Iso_rectangle_2(double min_hx, double min_hy, double max_hx, double max_hy, double hw = 1):data(min_hx,min_hy,max_hx,max_hy,hw){}
//Operations
  DEFINE_EQUALITY_OPERATORS(Iso_rectangle_2)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,vertex,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,min)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,max)
  SWIG_CGAL_FORWARD_CALL_0(double,xmin)
  SWIG_CGAL_FORWARD_CALL_0(double,ymin)
  SWIG_CGAL_FORWARD_CALL_0(double,xmax)
  SWIG_CGAL_FORWARD_CALL_0(double,ymax)
  SWIG_CGAL_FORWARD_CALL_1(double,min_coord,int)
  SWIG_CGAL_FORWARD_CALL_1(double,max_coord,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_2,bbox)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_2)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(double,area)
};

#endif //SWIG_CGAL_KERNEL_ISO_RECTANGLE_2_H

//Miscellaneous
//Iso_rectangle_2<Kernel> transform ( Aff_transformation_2<Kernel> t) const

