// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_BBOX_2_IMPL_H
#define SWIG_CGAL_KERNEL_BBOX_2_IMPL_H

#include <SWIG_CGAL/Kernel/Bbox_2_impl.h>

Bbox_2  Bbox_2::operator+(const Bbox_2& b) const {return Bbox_2( get_data() + b.get_data() );}

Bbox_2&  Bbox_2::operator+=(const Bbox_2& b)
{
  get_data()=get_data()+b.get_data();
  return *this;
}
#endif
