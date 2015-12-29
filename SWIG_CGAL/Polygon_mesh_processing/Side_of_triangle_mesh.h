// ------------------------------------------------------------------------------
// Copyright (c) 2015 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_PMP_SIDE_OF_TRIANGLE_MESH_H
#define SWIG_CGAL_PMP_SIDE_OF_TRIANGLE_MESH_H

#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <CGAL/Side_of_triangle_mesh.h>

template <class Polyhedron_wrapper>
class Side_of_triangle_mesh_wrapper
{
  typedef Side_of_triangle_mesh_wrapper<Polyhedron_wrapper> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);

public:
  #ifndef SWIG
  typedef CGAL::Side_of_triangle_mesh<typename Polyhedron_wrapper::cpp_base, EPIC_Kernel> cpp_base;
  cpp_base data;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif

  Side_of_triangle_mesh_wrapper(Polyhedron_wrapper& poly)
    : data(poly.get_data())
  {}

  // TODO this constructor requires an update of the AABB-tree wrapped package
  //      to the new API using BGL
  // Side_of_triangle_mesh_wrapper(AABB_tree& tree)
  //   : data(poly.get_data())
  // {}

  Bounded_side bounded_side(Point_3& p){
    return Bounded_side( data(p.get_data()) );
  }
};


#endif //SWIG_CGAL_PMP_SIDE_OF_TRIANGLE_MESH_H
