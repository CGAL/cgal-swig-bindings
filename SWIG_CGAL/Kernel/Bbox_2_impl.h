// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
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
