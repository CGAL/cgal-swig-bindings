// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_TRIANGULATION_3_TYPEDEFS_H
#define SWIG_CGAL_TRIANGULATION_3_TYPEDEFS_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Regular_triangulation_euclidean_traits_3.h>
#include <CGAL/Delaunay_triangulation_3.h>

typedef CGAL::Triangulation_3<EPIC_Kernel>                              CGAL_T3;
typedef CGAL::Delaunay_triangulation_3<EPIC_Kernel>                     CGAL_DT3;
typedef CGAL::Regular_triangulation_euclidean_traits_3<EPIC_Kernel>     RT_traits;
typedef CGAL::Regular_triangulation_3< RT_traits >                      CGAL_RT3;

#endif //SWIG_CGAL_TRIANGULATION_3_TYPEDEFS_H
