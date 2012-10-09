// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Origin.h>
#include <SWIG_CGAL/Kernel/Point_2_decl.h>
#include <SWIG_CGAL/Kernel/Point_3_decl.h>
#include <SWIG_CGAL/Kernel/Vector_2_decl.h>
#include <SWIG_CGAL/Kernel/Vector_3_decl.h>
#include <CGAL/Origin.h>

Point_2 Origin::operator+(const Vector_2& v) const {return Point_2( CGAL::ORIGIN+v.get_data() ); }
Point_2 Origin::operator-(const Vector_2& v) const {return Point_2( CGAL::ORIGIN-v.get_data() ); }
Point_3 Origin::operator+(const Vector_3& v) const {return Point_3( CGAL::ORIGIN+v.get_data() ); }
Point_3 Origin::operator-(const Vector_3& v) const {return Point_3( CGAL::ORIGIN-v.get_data() ); }
Vector_2 Origin::operator-(const Point_2& p) const {return Vector_2( CGAL::ORIGIN-p.get_data() ); }
Vector_3 Origin::operator-(const Point_3& p) const {return Vector_3( CGAL::ORIGIN-p.get_data() ); }
