// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_SEGMENT_2_IMPL_H
#define SWIG_CGAL_KERNEL_SEGMENT_2_IMPL_H

#include <SWIG_CGAL/Kernel/Point_2_decl.h>
#include <SWIG_CGAL/Kernel/Vector_2_decl.h>
#include <SWIG_CGAL/Kernel/Line_2_decl.h>
#include <SWIG_CGAL/Kernel/Direction_2_decl.h>

//member functions involving elements that are in include conflict
Segment_2::Segment_2(const Point_2& p,const Point_2& q):data(p.get_data(),q.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_2,Segment_2::source,source)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_2,Segment_2::target,target)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_2,Segment_2::min,min)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_2,Segment_2::max,max)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_2,Segment_2::vertex,vertex,int)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Point_2,Segment_2::point,point,int)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Segment_2::has_on,has_on,Point_2)
SWIG_CGAL_FORWARD_CALL_SCOPE_1(bool,Segment_2::collinear_has_on,collinear_has_on,Point_2)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_2,Segment_2::direction,direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_2,Segment_2::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Line_2,Segment_2::supporting_line,supporting_line)
#endif //SWIG_CGAL_KERNEL_SEGMENT_2_IMPL_H
