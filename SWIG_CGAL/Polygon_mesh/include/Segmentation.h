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

#ifndef SWIG_CGAL_POLYGON_MESH_SEGMENTATION_H
#define SWIG_CGAL_POLYGON_MESH_SEGMENTATION_H

#include <CGAL/mesh_segmentation.h>

struct Triangulated_surface_mesh_segmentation
{
  static
  std::pair<double, double>
  sdf_values(PolygonMesh& pm,
             PolygonMeshDoublePropertyJNI& face_double_map,
             double cone_angle=2.0/3.0 * 3.14,
             int number_of_rays=25,
             bool postprocess=true)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Face_descriptor, double> sdf_map(face_double_map);
    return CGAL::sdf_values(pm, sdf_map, cone_angle, number_of_rays, postprocess);
  }

  static
  std::pair< double, double >
  sdf_values_postprocessing(PolygonMesh& pm,
                            PolygonMeshDoublePropertyJNI& face_double_map)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Face_descriptor, double> sdf_map(face_double_map);
    return CGAL::sdf_values_postprocessing(pm, sdf_map);
  }

  static
  int
  segmentation_from_sdf_values (PolygonMesh& pm,
                                PolygonMeshDoublePropertyJNI& face_double_map,
                                PolygonMeshIntPropertyJNI& face_int_map,
                                int number_of_clusters=5,
                                double smoothing_lambda=0.26,
                                bool output_cluster_ids=false)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Face_descriptor, double> sdf_map(face_double_map);
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Face_descriptor, unsigned> segment_map(face_int_map);
    return CGAL::segmentation_from_sdf_values(pm, sdf_map, segment_map, number_of_clusters, smoothing_lambda, output_cluster_ids);
  }

  static
  int
  segmentation_via_sdf_values (PolygonMesh& pm,
                               PolygonMeshIntPropertyJNI& face_int_map,
                               int number_of_clusters=5,
                               double smoothing_lambda=0.26,
                               bool output_cluster_ids=false)
  {
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Face_descriptor, unsigned> segment_map(face_int_map);
    return CGAL::segmentation_via_sdf_values(pm, segment_map, number_of_clusters, smoothing_lambda, output_cluster_ids);
  }
};

#endif // SWIG_CGAL_POLYGON_MESH_SEGMENTATION_H
