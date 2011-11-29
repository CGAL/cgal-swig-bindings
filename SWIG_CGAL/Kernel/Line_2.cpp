// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Line_2.h>

//member functions involving elements that are in include conflict
Line_2::Line_2(const Point_2& p,const Direction_2& d):data(p.get_data(),d.get_data()){}
Line_2::Line_2(const Point_2& p,const Vector_2& v):data(p.get_data(),v.get_data()){}
Line_2::Line_2(const Segment_2& s):data(s.get_data()){}
Line_2::Line_2(const Ray_2& r):data(r.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_2,Line_2::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_2,Line_2::direction,direction)
