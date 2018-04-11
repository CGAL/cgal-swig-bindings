// Copyright (c) 2018 GeometryFactory (France).
// All rights reserved.
//
// This file if part of CGAL PolygonMesh java wrapper.
// It is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this file.  If not, see <https://www.gnu.org/licenses/>.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// $URL$
// $Id$
// SPDX-License-Identifier: AGPL-3.0+
//

#ifndef SWIG_CGAL_POLYGON_MESH_ASFR_H
#define SWIG_CGAL_POLYGON_MESH_ASFR_H

#ifndef SWIG

struct Edge_length_and_perimeter_priority
{

  double edge_bound;
  double perimeter_bound;

  Edge_length_and_perimeter_priority(double e, double p)
    : edge_bound(e)
    , perimeter_bound(p)
  {}

  template <typename AdvancingFront, typename Cell_handle>
  double operator() (const AdvancingFront& adv, Cell_handle& c,
                     const int& index) const
  {
    // bound == 0 is better than bound < infinity
    // as it avoids the distance computations
    if (edge_bound == 0 && perimeter_bound==0)
      return adv.smallest_radius_delaunay_sphere (c, index);

    // If perimeter or edge length > bound, return infinity so that facet is not used
    double e = sqrt(squared_distance(c->vertex((index+1)%4)->point(),
                                     c->vertex((index+2)%4)->point()));
    double p = e;

    if (p>perimeter_bound || e>edge_bound) return adv.infinity();

    e = sqrt(squared_distance(c->vertex((index+2)%4)->point(),
                              c->vertex((index+3)%4)->point()));
    p += e;

    if (p>perimeter_bound || e>edge_bound) return adv.infinity();
    e = sqrt(squared_distance(c->vertex((index+1)%4)->point(),
                              c->vertex((index+3)%4)->point()));
    p += e;

    if (p>perimeter_bound || e>edge_bound) return adv.infinity();

    // Otherwise, return usual priority value: smallest radius of
    // delaunay sphere
    return adv.smallest_radius_delaunay_sphere (c, index);
  }
};

#endif


#include <SWIG_CGAL/Advancing_front_surface_reconstruction/impl.h>

struct Advancing_front_surface_reconstruction{
  static
  void advancing_front_surface_reconstruction(
    boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points,
    PolygonMesh& pm,
    double triangle_edge_length_bound = 0,
    double triangle_perimeter_bound = 0,
    double radius_ratio_bound = 5,
    double beta = 0.52)
  {
    Edge_length_and_perimeter_priority priority(triangle_edge_length_bound, triangle_perimeter_bound);
    Construct_face_graph<PolygonMesh> cfg(pm, points->begin(), points->end());
    CGAL::advancing_front_surface_reconstruction(cfg.points_begin(), cfg.points_end(), cfg, priority, radius_ratio_bound, beta);
  }
};

#endif // SWIG_CGAL_POLYGON_MESH_ASFR_H
