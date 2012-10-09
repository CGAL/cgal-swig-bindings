// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_SEGMENT_3_IMPL_H
#define SWIG_CGAL_KERNEL_SEGMENT_3_IMPL_H

#include <SWIG_CGAL/Kernel/Point_3_decl.h>
#include <SWIG_CGAL/Kernel/Line_3_decl.h>
#include <SWIG_CGAL/Kernel/Vector_3_decl.h>
#include <SWIG_CGAL/Kernel/Direction_3_decl.h>

//member functions involving elements that are in include conflict
Segment_3::Segment_3(const Point_3& p1, const Point_3& p2):data(p1.get_data(), p2.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_3,Segment_3::source,source)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_3,Segment_3::target,target)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_3,Segment_3::min,min)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_3,Segment_3::max,max)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_3,Segment_3::vertex,vertex,int)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_3,Segment_3::point,point,int)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Segment_3::has_on,has_on,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Segment_3::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Segment_3::direction,direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Line_3,Segment_3::supporting_line,supporting_line)
#endif //SWIG_CGAL_KERNEL_SEGMENT_3_IMPL_H
