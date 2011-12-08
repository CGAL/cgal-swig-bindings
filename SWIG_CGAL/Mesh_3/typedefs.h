// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_3_TYPEDEFS_H
#define SWIG_CGAL_MESH_3_TYPEDEFS_H

#include <CGAL/Mesh_3/Robust_intersection_traits_3.h>

#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>

#include <CGAL/Polyhedral_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>
#include <CGAL/refine_mesh_3.h>

#include <SWIG_CGAL/Polyhedron_3/all_includes.h>

// Domain
#warning tmp
//typedef CGAL::Mesh_3::Robust_intersection_traits_3<EPIC_Kernel> GT;
//typedef CGAL::Polyhedron_3<GT>                                  Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron_3_, EPIC_Kernel>   PMD;
typedef CGAL::Mesh_triangulation_3<PMD>::type                        MT_PMD;
typedef CGAL::Mesh_complex_3_in_triangulation_3<MT_PMD>              C3T3_PMD;

// Criteria
typedef CGAL::Mesh_criteria_3<MT_PMD>                                DMC;


#endif //SWIG_CGAL_MESH_3_TYPEDEFS_H
