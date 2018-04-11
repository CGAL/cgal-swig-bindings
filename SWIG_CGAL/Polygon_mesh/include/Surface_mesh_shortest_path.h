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

#ifndef SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_SHORTEST_PATH_H
#define SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_SHORTEST_PATH_H

#include <CGAL/Surface_mesh_shortest_path/Surface_mesh_shortest_path_traits.h>
#include <CGAL/Surface_mesh_shortest_path/Surface_mesh_shortest_path.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_tree.h>

struct Surface_mesh_shortest_path
{
  static
  void shortest_paths(PolygonMesh& pm,
                      boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > source_points,
                      boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > target_points,
                      PolygonMeshMultiPolylineJNI multi_polylines)
  {
    typedef CGAL::Surface_mesh_shortest_path_traits<EPIC_Kernel, PolygonMesh> Traits;
    typedef CGAL::Surface_mesh_shortest_path<Traits> Surface_mesh_shortest_path;
    typedef CGAL::AABB_face_graph_triangle_primitive<PolygonMesh> AABB_face_graph_primitive;
    typedef CGAL::AABB_traits<EPIC_Kernel, AABB_face_graph_primitive> AABB_face_graph_traits;
    CGAL::AABB_tree<AABB_face_graph_traits> tree(faces(pm).begin(), faces(pm).end(), pm);
    
    Surface_mesh_shortest_path shortest_paths(pm);
    BOOST_FOREACH(const EPIC_Kernel::Point_3& pt, *source_points)
    {
      Surface_mesh_shortest_path::Face_location loc = shortest_paths.locate(pt, tree);
      shortest_paths.add_source_point(loc);
    }
    
    Points_putter<PolygonMeshMultiPolylineJNI> putter(multi_polylines);
    BOOST_FOREACH(const EPIC_Kernel::Point_3& pt, *target_points)
    {
      Surface_mesh_shortest_path::Face_location loc = shortest_paths.locate(pt, tree);
      multi_polylines.beginPolyline();
      shortest_paths.shortest_path_points_to_source_points(loc.first, loc.second, boost::make_function_output_iterator(putter));
      multi_polylines.endPolyline();
    } 
  }
};

#endif // SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_SHORTEST_PATH_H
