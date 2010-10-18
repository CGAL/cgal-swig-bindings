
#define IMPORT_ONLY_POLYHEDRON_TYPES
%include "SWIG_CGAL/Polyhedron_3/config.i"
#undef IMPORT_ONLY_POLYHEDRON_TYPES

//defining types used
%{
#include <CGAL/Mesh_3/Robust_intersection_traits_3.h>

#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>

#include <CGAL/Polyhedral_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>
#include <CGAL/refine_mesh_3.h>

// Domain
#warning tmp
//~ typedef CGAL::Mesh_3::Robust_intersection_traits_3<EPIC_Kernel> GT;
//~ typedef CGAL::Polyhedron_3<GT>                                  Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron_3_, EPIC_Kernel>   PMD;
typedef CGAL::Mesh_triangulation_3<PMD>::type                        MT_PMD;
typedef CGAL::Mesh_complex_3_in_triangulation_3<MT_PMD>              C3T3_PMD;

// Criteria
typedef CGAL::Mesh_criteria_3<MT_PMD>                                DMC;

#ifdef SWIGJAVA
//for java criteria
#include <SWIG_CGAL/Java/Java_caller_code.h>
#endif

%}