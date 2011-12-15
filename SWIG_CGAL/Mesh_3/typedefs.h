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

//Triangle accessor allowing having Polyhedron with a
//different Kernel
template < class Polyhedron,class Poly_Kernel, class GT>
class SWIG_CGAL_Triangle_accessor_3
{
public:
  typedef typename GT::Triangle_3                    Triangle_3;
  typedef typename Polyhedron::Facet_const_iterator  Triangle_iterator;
  typedef typename Polyhedron::Facet_const_handle    Triangle_handle;

  SWIG_CGAL_Triangle_accessor_3() { }

  Triangle_iterator triangles_begin(const Polyhedron& p) const
  {
    return p.facets_begin();
  }

  Triangle_iterator triangles_end(const Polyhedron& p) const
  {
    return p.facets_end();
  }

  Triangle_3 triangle(const Triangle_handle& handle) const
  {
    typedef typename Poly_Kernel::Point_3 Point;
    const Point& a = handle->halfedge()->vertex()->point();
    const Point& b = handle->halfedge()->next()->vertex()->point();
    const Point& c = handle->halfedge()->next()->next()->vertex()->point();
    return Triangle_3(a,b,c);
  }
};

// Domain
typedef CGAL::Mesh_3::Robust_intersection_traits_3<EPIC_Kernel>           RIT3;
typedef SWIG_CGAL_Triangle_accessor_3<Polyhedron_3_,EPIC_Kernel,RIT3>     SGTA3;
typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron_3_, RIT3,SGTA3>         PMD;
typedef CGAL::Mesh_triangulation_3<PMD>::type                             MT_PMD;
typedef CGAL::Mesh_complex_3_in_triangulation_3<MT_PMD>                   C3T3_PMD;
// Criteria
typedef CGAL::Mesh_criteria_3<MT_PMD>                                     DMC;


#endif //SWIG_CGAL_MESH_3_TYPEDEFS_H
