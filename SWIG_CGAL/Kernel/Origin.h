// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_ORIGIN_H
#define SWIG_CGAL_KERNEL_ORIGIN_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/include_conflicts_2.h>
#include <SWIG_CGAL/Kernel/include_conflicts_3.h>

struct SWIG_CGAL_KERNEL_DECL Origin
{
  Point_2 operator+(const Vector_2&) const;
  Point_2 operator-(const Vector_2&) const;
  Point_3 operator+(const Vector_3&) const;
  Point_3 operator-(const Vector_3&) const;
  Vector_2 operator-(const Point_2&) const;
  Vector_3 operator-(const Point_3&) const;
};

struct SWIG_CGAL_KERNEL_DECL Null_vector{};

#endif //SWIG_CGAL_KERNEL_ORIGIN_H
