// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_DIRECTION_3_IMPL_H
#define SWIG_CGAL_KERNEL_DIRECTION_3_IMPL_H

#include <SWIG_CGAL/Kernel/Segment_3_decl.h>
#include <SWIG_CGAL/Kernel/Line_3_decl.h>
#include <SWIG_CGAL/Kernel/Ray_3_decl.h>
#include <SWIG_CGAL/Kernel/Vector_3_decl.h>

//member functions involving elements that are in include conflict
Direction_3::Direction_3(const Vector_3& v):data(v.get_data()){}
Direction_3::Direction_3(const Line_3& l):data(l.get_data()){}
Direction_3::Direction_3(const Ray_3& r):data(r.get_data()){}
Direction_3::Direction_3(const Segment_3& s):data(s.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Direction_3::vector,vector)
#endif //SWIG_CGAL_KERNEL_DIRECTION_3_IMPL_H
