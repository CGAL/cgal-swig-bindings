// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_POINT_2_IMPL_H
#define SWIG_CGAL_KERNEL_POINT_2_IMPL_H

#include <SWIG_CGAL/Kernel/Vector_2.h>
#include <SWIG_CGAL/Kernel/Origin.h>
#include <CGAL/Origin.h>

Vector_2 Point_2::operator-(Point_2& p) {return Vector_2( get_data() - p.get_data() );}
Point_2  Point_2::operator+(Vector_2& v) {return Point_2( get_data() + v.get_data() );}
Point_2  Point_2::operator-(Vector_2& v) {return Point_2( get_data() - v.get_data() );}
Vector_2  Point_2::operator-(const Origin&) {return Vector_2( get_data() - CGAL::ORIGIN ); }

Point_2&  Point_2::operator+=(Vector_2& v)
{
  get_data()=get_data()+v.get_data();
  return *this;
}
Point_2&  Point_2::operator-=(Vector_2& v)
{
  get_data()=get_data()-v.get_data();
  return *this;
}
#endif
