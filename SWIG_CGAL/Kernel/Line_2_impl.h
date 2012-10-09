// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_LINE_2_IMPL_H
#define SWIG_CGAL_KERNEL_LINE_2_IMPL_H

#include <SWIG_CGAL/Kernel/Point_2_decl.h>
#include <SWIG_CGAL/Kernel/Vector_2_decl.h>
#include <SWIG_CGAL/Kernel/Ray_2_decl.h>
#include <SWIG_CGAL/Kernel/Direction_2_decl.h>
#include <SWIG_CGAL/Kernel/Segment_2_decl.h>

//member functions involving elements that are in include conflict
Line_2::Line_2(const Point_2& p,const Point_2& q):data(p.get_data(),q.get_data()){}
Line_2::Line_2(const Point_2& p,const Direction_2& d):data(p.get_data(),d.get_data()){}
Line_2::Line_2(const Point_2& p,const Vector_2& v):data(p.get_data(),v.get_data()){}
Line_2::Line_2(const Segment_2& s):data(s.get_data()){}
Line_2::Line_2(const Ray_2& r):data(r.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_2,Line_2::point,point,int)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_2,Line_2::projection,projection,Point_2)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(Oriented_side,Line_2::oriented_side,oriented_side,Point_2)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Line_2::has_on,has_on,Point_2)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Line_2::has_on_positive_side,has_on_positive_side,Point_2)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Line_2::has_on_negative_side,has_on_negative_side,Point_2)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Line_2,Line_2::perpendicular,perpendicular,Point_2)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_2,Line_2::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_2,Line_2::direction,direction)
#endif //SWIG_CGAL_KERNEL_LINE_2_IMPL_H
