// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_PLANE_3_IMPL_H
#define SWIG_CGAL_KERNEL_PLANE_3_IMPL_H

#include <SWIG_CGAL/Kernel/Point_3_decl.h>
#include <SWIG_CGAL/Kernel/Segment_3_decl.h>
#include <SWIG_CGAL/Kernel/Line_3_decl.h>
#include <SWIG_CGAL/Kernel/Ray_3_decl.h>
#include <SWIG_CGAL/Kernel/Vector_3_decl.h>
#include <SWIG_CGAL/Kernel/Direction_3_decl.h>

//member functions involving elements that are in include conflict
Plane_3::Plane_3(const Point_3& p,const Point_3& q,const Point_3& r):data(p.get_data(),q.get_data(),r.get_data()){}
Plane_3::Plane_3(const Point_3& p,const Vector_3& v):data(p.get_data(),v.get_data()){}
Plane_3::Plane_3(const Point_3& p,const Direction_3& d):data(p.get_data(),d.get_data()){}
Plane_3::Plane_3(const Line_3& l,const Point_3& p):data(l.get_data(),p.get_data()){}
Plane_3::Plane_3(const Ray_3& r,const Point_3& p):data(r.get_data(),p.get_data()){}
Plane_3::Plane_3(const Segment_3& s,const Point_3& p):data(s.get_data(),p.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_3,Plane_3::projection,projection,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Plane_3,Plane_3::opposite,opposite)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_3,Plane_3::point,point)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_2,Plane_3::to_2d,to_2d,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_3,Plane_3::to_3d,to_3d,Point_2)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(Oriented_side,Plane_3::oriented_side,oriented_side,Point_3)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Plane_3::has_on,has_on,Point_3)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Plane_3::has_on_positive_side,has_on_positive_side,Point_3)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Plane_3::has_on_negative_side,has_on_negative_side,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Plane_3::orthogonal_vector,orthogonal_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Line_3,Plane_3::perpendicular_line,perpendicular_line,Point_3)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Plane_3::has_on,has_on,Line_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Plane_3::orthogonal_direction,orthogonal_direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Plane_3::base1,base1)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Plane_3::base2,base2)
#endif //SWIG_CGAL_KERNEL_PLANE_3_IMPL_H
