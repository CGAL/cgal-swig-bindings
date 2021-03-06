// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_POINT_3_IMPL_H
#define SWIG_CGAL_KERNEL_POINT_3_IMPL_H

#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Kernel/Origin.h>

Vector_3 Point_3::operator-(Point_3& p) {return Vector_3( get_data() - p.get_data() );}
Point_3  Point_3::operator+(Vector_3& v) {return Point_3( get_data() + v.get_data() );}
Point_3  Point_3::operator-(Vector_3& v) {return Point_3( get_data() - v.get_data() );}
Vector_3 Point_3::operator-(const Origin&) {return Vector_3( get_data() - CGAL::ORIGIN ); }

Point_3&  Point_3::operator+=(Vector_3& v) 
{
  get_data()=get_data()+v.get_data();
  return *this;
}
Point_3&  Point_3::operator-=(Vector_3& v)
{
  get_data()=get_data()-v.get_data();
  return *this;
}

#endif //SWIG_CGAL_KERNEL_POINT_3_IMPL_H
