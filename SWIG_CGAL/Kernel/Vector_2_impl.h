// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_VECTOR_2_IMPL_H
#define SWIG_CGAL_KERNEL_VECTOR_2_IMPL_H

#include <SWIG_CGAL/Kernel/Point_2_decl.h>
#include <SWIG_CGAL/Kernel/Segment_2_decl.h>
#include <SWIG_CGAL/Kernel/Line_2_decl.h>
#include <SWIG_CGAL/Kernel/Ray_2_decl.h>
#include <SWIG_CGAL/Kernel/Direction_2_decl.h>

//member functions involving elements that are in include conflict
Vector_2::Vector_2(const Point_2& a,const Point_2& b):data(a.get_data(),b.get_data()){}
Vector_2::Vector_2(const Segment_2& s):data(s.get_data()){}
Vector_2::Vector_2(const Ray_2& r):data(r.get_data()){}
Vector_2::Vector_2(const Line_2& l):data(l.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_2,Vector_2::direction,direction)
#endif //SWIG_CGAL_KERNEL_VECTOR_2_IMPL_H
