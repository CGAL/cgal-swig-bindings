// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_LINE_3_IMPL_H
#define SWIG_CGAL_KERNEL_LINE_3_IMPL_H
//member functions involving elements that are in include conflict
Line_3::Line_3(const Point_3& p, Direction_3& d):data(p.get_data(),d.get_data()){}
Line_3::Line_3(const Point_3& p, Vector_3& v):data(p.get_data(),v.get_data()){}
Line_3::Line_3(const Segment_3& s):data(s.get_data()){}
Line_3::Line_3(const Ray_3& r):data(r.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_1(Plane_3,Line_3::perpendicular_plane,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Line_3,Line_3::opposite,opposite)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Line_3::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Line_3::direction,direction)
#endif //SWIG_CGAL_KERNEL_LINE_3_IMPL_H
