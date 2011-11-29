// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_ENUM_H
#define SWIG_CGAL_KERNEL_ENUM_H

#include <SWIG_CGAL/Common/Macros.h>

enum Oriented_side { ON_NEGATIVE_SIDE=-1, ON_ORIENTED_BOUNDARY=0, ON_POSITIVE_SIDE=1};
enum Bounded_side{ ON_UNBOUNDED_SIDE = -1,ON_BOUNDARY,ON_BOUNDED_SIDE};
enum Orientation {NEGATIVE=-1,RIGHT_TURN=-1,CLOCKWISE=-1,ZERO=0,COPLANAR=0,COLLINEAR=0,LEFT_TURN=1,COUNTERCLOCKWISE=1,POSITIVE=1}; 

namespace internal{
  SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM(Oriented_side)
  SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM(Bounded_side)
  SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM(Orientation)
}//namespace internal

#endif //SWIG_CGAL_KERNEL_ENUM_H
