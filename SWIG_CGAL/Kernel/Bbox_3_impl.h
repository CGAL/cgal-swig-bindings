// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_BBOX_3_IMPL_H
#define SWIG_CGAL_KERNEL_BBOX_3_IMPL_H

#include <SWIG_CGAL/Kernel/Bbox_3_impl.h>

Bbox_3  Bbox_3::operator+(const Bbox_3& b) const {return Bbox_3( get_data() + b.get_data() );}

Bbox_3&  Bbox_3::operator+=(const Bbox_3& b)
{
  get_data()=get_data()+b.get_data();
  return *this;
}
#endif
