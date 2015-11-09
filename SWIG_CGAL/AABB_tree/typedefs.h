// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_AABB_TREE_TYPEDEFS_H
#define SWIG_CGAL_AABB_TREE_TYPEDEFS_H

#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
#include <CGAL/AABB_polyhedron_segment_primitive.h>
#include <CGAL/AABB_integer_primitive.h>

// Polyhedron Triangle Primitive
typedef CGAL::AABB_polyhedron_triangle_primitive<EPIC_Kernel,Polyhedron_3_>     CGAL_PTP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_PTP>                                CGAL_PTP_T;
typedef CGAL::AABB_tree<CGAL_PTP_T>                                             CGAL_PTP_Tree;
// Polyhedron Segment Primitive
typedef CGAL::AABB_polyhedron_segment_primitive<EPIC_Kernel,Polyhedron_3_>      CGAL_PSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_PSP>                                CGAL_PSP_T;
typedef CGAL::AABB_tree<CGAL_PSP_T>                                             CGAL_PSP_Tree;
// Triangle Soup Primitive
typedef CGAL::AABB_integer_primitive<EPIC_Kernel::Triangle_3>                   CGAL_TSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_TSP>                                CGAL_TSP_T;
typedef CGAL::AABB_tree<CGAL_TSP_T>                                             CGAL_TSP_Tree;
// Segment Soup Primitive
typedef CGAL::AABB_integer_primitive<EPIC_Kernel::Segment_3>                    CGAL_SSP;
typedef CGAL::AABB_traits<EPIC_Kernel, CGAL_SSP>                                CGAL_SSP_T;
typedef CGAL::AABB_tree<CGAL_SSP_T>                                             CGAL_SSP_Tree;

#endif //SWIG_CGAL_AABB_TREE_TYPEDEFS_H
