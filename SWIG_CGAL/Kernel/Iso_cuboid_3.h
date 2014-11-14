// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_ISO_CUBOID_3_H
#define SWIG_CGAL_KERNEL_ISO_CUBOID_3_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>
#include <SWIG_CGAL/Common/Macros.h>

// defined by windows.h, brought by CGAL headers
#ifdef far
#undef far
#endif

class SWIG_CGAL_KERNEL_DECL Iso_cuboid_3
{
  EPIC_Kernel::Iso_cuboid_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Iso_cuboid_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Iso_cuboid_3(const cpp_base& base):data(base){}
  #endif
//Creation
  Iso_cuboid_3(Point_3& p,Point_3& q):data(p.get_data(),q.get_data()){}
  Iso_cuboid_3(Point_3& p,Point_3& q,int i):data(p.get_data(),q.get_data(),i){}
  Iso_cuboid_3(Point_3& left, Point_3& right, Point_3& bottom, Point_3& top, Point_3& far, Point_3& close)
    :data(left.get_data(),right.get_data(),bottom.get_data(),top.get_data(),far.get_data(),close.get_data()){}
  Iso_cuboid_3(double min_hx, double min_hy, double min_hz, double max_hx, double max_hy, double max_hz, double hw = 1):data(min_hx,min_hy,min_hz,max_hx,max_hy,max_hz,hw){}
//Operations
  DEFINE_EQUALITY_OPERATORS(Iso_cuboid_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_3,vertex,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_3,min)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_3,max)
  SWIG_CGAL_FORWARD_CALL_0(double,xmin)
  SWIG_CGAL_FORWARD_CALL_0(double,ymin)
  SWIG_CGAL_FORWARD_CALL_0(double,zmin)
  SWIG_CGAL_FORWARD_CALL_0(double,xmax)
  SWIG_CGAL_FORWARD_CALL_0(double,ymax)
  SWIG_CGAL_FORWARD_CALL_0(double,zmax)
  SWIG_CGAL_FORWARD_CALL_1(double,min_coord,int)
  SWIG_CGAL_FORWARD_CALL_1(double,max_coord,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_3,bbox)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_3)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(double,volume)
};

#endif //SWIG_CGAL_KERNEL_ISO_CUBOID_3_H

//Miscellaneous
//Iso_cuboid_3<Kernel> transform ( Aff_transformation_3<Kernel> t) const

