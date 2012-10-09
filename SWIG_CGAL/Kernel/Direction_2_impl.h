// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_DIRECTION_2_IMPL_H
#define SWIG_CGAL_KERNEL_DIRECTION_2_IMPL_H

#include <SWIG_CGAL/Kernel/Point_2_decl.h>
#include <SWIG_CGAL/Kernel/Segment_2_decl.h>
#include <SWIG_CGAL/Kernel/Line_2_decl.h>
#include <SWIG_CGAL/Kernel/Ray_2_decl.h>
#include <SWIG_CGAL/Kernel/Vector_2_decl.h>

//member functions involving elements that are in include conflict
Direction_2::Direction_2(const Vector_2& v):data(v.get_data()){}
Direction_2::Direction_2(const Line_2& l):data(l.get_data()){}
Direction_2::Direction_2(const Ray_2& r):data(r.get_data()){}
Direction_2::Direction_2(const Segment_2& s):data(s.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_2,Direction_2::vector,vector)
#endif //SWIG_CGAL_KERNEL_DIRECTION_2_IMPL_H
