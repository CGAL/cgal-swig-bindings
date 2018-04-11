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

#ifndef SWIG_CGAL_POLYGON_MESH_SURFACE_RECONSTRUCTION_3_H
#define SWIG_CGAL_POLYGON_MESH_SURFACE_RECONSTRUCTION_3_H

#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/poisson_surface_reconstruction.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>

#include "properties_PointSet.h"

struct Surface_reconstruction_3
{  
  typedef EPIC_Kernel::Point_3 Point_3;
  typedef EPIC_Kernel::Vector_3 Vector_3;
  typedef PointSet_point_map<PointSet, Point_3> Point_map;
  typedef PointSet_property<PolygonMeshDoublePropertyJNI, Vector_3> Normal_map;
  
  static
  void advancing_front_surface_reconstruction(PointSet& ps,
                                              PolygonMesh& pm,
                                              double radius_ratio_bound = 5,
                                              double  beta = 0.52)
  {
    std::vector< CGAL::cpp11::array<std::size_t,3> > faces;
    std::vector<Point_3> points;
    points.reserve(ps.size());
    std::copy(ps.points_begin<Point_3>(), ps.points_end<Point_3>(), std::back_inserter(points));

    CGAL::advancing_front_surface_reconstruction(points.begin(), points.end(),
      std::back_inserter(faces), radius_ratio_bound, beta);
    
    CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(points, faces, pm);
          
  }

  static
  bool poisson_surface_reconstruction_delaunay(PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map, PolygonMesh& pm,
                                                double spacing,
                                                double sm_angle = 20.0,
                                                double sm_radius = 30.0,
                                                double sm_distance = 0.375)
  {
    return CGAL::poisson_surface_reconstruction_delaunay(
              ps.begin(), ps.end(),
              Point_map(ps), Normal_map(point_double_map),
              pm,
              spacing, sm_angle, sm_radius, sm_distance, CGAL::Manifold_tag());
  }
};

#endif 
