// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_AABB_TREE_TYPEDEFS_H
#define SWIG_CGAL_AABB_TREE_TYPEDEFS_H

#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits_3.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_integer_primitive.h>

template <class Polyhedron, class Base>
struct Primitive_wrapper : Base
{
  template <class T>
  Primitive_wrapper(T t)
    : Base(t, Polyhedron())
  {}
};

// Polyhedron Triangle Primitive
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron_3_>                 CGAL_PTP_base;
typedef Primitive_wrapper<Polyhedron_3_,CGAL_PTP_base>                          CGAL_PTP;
typedef CGAL::AABB_traits_3<EPIC_Kernel, CGAL_PTP>                              CGAL_PTP_T;
typedef CGAL::AABB_tree<CGAL_PTP_T>                                             CGAL_PTP_Tree;
// Polyhedron Segment Primitive
typedef CGAL::AABB_halfedge_graph_segment_primitive<Polyhedron_3_>              CGAL_PSP_base;
typedef Primitive_wrapper<Polyhedron_3_,CGAL_PSP_base>                          CGAL_PSP;
typedef CGAL::AABB_traits_3<EPIC_Kernel, CGAL_PSP>                              CGAL_PSP_T;
typedef CGAL::AABB_tree<CGAL_PSP_T>                                             CGAL_PSP_Tree;
// Triangle Soup Primitive
typedef CGAL::AABB_integer_primitive<EPIC_Kernel::Triangle_3>                   CGAL_TSP;
typedef CGAL::AABB_traits_3<EPIC_Kernel, CGAL_TSP>                              CGAL_TSP_T;
typedef CGAL::AABB_tree<CGAL_TSP_T>                                             CGAL_TSP_Tree;
// Segment Soup Primitive
typedef CGAL::AABB_integer_primitive<EPIC_Kernel::Segment_3>                    CGAL_SSP;
typedef CGAL::AABB_traits_3<EPIC_Kernel, CGAL_SSP>                              CGAL_SSP_T;
typedef CGAL::AABB_tree<CGAL_SSP_T>                                             CGAL_SSP_Tree;

#endif //SWIG_CGAL_AABB_TREE_TYPEDEFS_H
