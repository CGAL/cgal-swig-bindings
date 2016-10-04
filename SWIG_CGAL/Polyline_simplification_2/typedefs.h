// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_POLYLINE_SIMPLIFICATION_2_TYPEDEFS_H
#define SWIG_CGAL_POLYLINE_SIMPLIFICATION_2_TYPEDEFS_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Triangulation_2/typedefs.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Polyline_simplification_2/simplify.h>
#include <CGAL/Polyline_simplification_2/Squared_distance_cost.h>

typedef CDT_TDS::Vertex PS_Vb_base;
typedef CGAL::Polyline_simplification_2::Vertex_base_2<EPIC_Kernel,PS_Vb_base>  PS_Vb;
typedef CGAL::Constrained_triangulation_face_base_2<EPIC_Kernel>          PS_Fb;
typedef CGAL::Triangulation_data_structure_2<PS_Vb, PS_Fb>               PS_TDS;
typedef CGAL::Constrained_Delaunay_triangulation_2<
  EPIC_Kernel, PS_TDS, CGAL::Exact_predicates_tag>                       PS_CDT;
typedef CGAL::Constrained_triangulation_plus_2<PS_CDT>                 PS_CDTP2;


#endif //SWIG_CGAL_POLYLINE_SIMPLIFICATION_2_TYPEDEFS_H
