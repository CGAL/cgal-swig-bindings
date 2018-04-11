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

#ifndef SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_SKELETONIZATION_H
#define SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_SKELETONIZATION_H

#include <CGAL/extract_mean_curvature_flow_skeleton.h>
#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <CGAL/boost/graph/copy_face_graph.h>

class Surface_mesh_skeletonization
{
  template <class VertexToSkeleton>
  static
  void convert_skeleton(const CGAL::Mean_curvature_flow_skeletonization<PolygonMesh>::Skeleton& cpp_skeleton,
                        VertexToSkeleton& vertex_to_skeleton,
                        PolygonMeshSkeletonJNI& java_skeleton)
  {
    typedef CGAL::Mean_curvature_flow_skeletonization<PolygonMesh>::Skeleton Skeleton;
    typename boost::property_map<Skeleton, boost::vertex_index_t>::type vidmap =
      get(boost::vertex_index, cpp_skeleton);

    java_skeleton.set_capacities(num_vertices(cpp_skeleton), num_edges(cpp_skeleton));
    BOOST_FOREACH(typename Skeleton::vertex_descriptor vd, vertices(cpp_skeleton))
    {
      std::size_t vid = get(vidmap, vd);
      const CGAL::Mean_curvature_flow_skeletonization<PolygonMesh>::Vmap& info = cpp_skeleton[vd];
      java_skeleton.push_back_point(info.point.x(), info.point.y(), info.point.z());
      BOOST_FOREACH(int vd, info.vertices)
      {
        put(vertex_to_skeleton, typename PolygonMesh::Vertex_descriptor(vd), vid);
      }
    }
    BOOST_FOREACH(typename Skeleton::edge_descriptor ed, edges(cpp_skeleton))
    {
      java_skeleton.push_back_edge(get(vidmap, source(ed, cpp_skeleton)),
                                   get(vidmap, target(ed, cpp_skeleton)));
    }
  }

public:
  static
  void extract_mean_curvature_flow_skeleton(PolygonMesh& pm,
                                            PolygonMeshSkeletonJNI skeleton,
                                            PolygonMeshIntPropertyJNI& vertex_int_map)
  {
    CGAL::Mean_curvature_flow_skeletonization<PolygonMesh>::Skeleton cpp_skeleton;
    CGAL::extract_mean_curvature_flow_skeleton(pm, cpp_skeleton);
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Vertex_descriptor, int>
      vertex_to_skeleton(vertex_int_map);

    convert_skeleton(cpp_skeleton, vertex_to_skeleton, skeleton);
  }

  class Mean_curvature_flow_skeletonization{
    typedef CGAL::Mean_curvature_flow_skeletonization<PolygonMesh> cpp_base;
    cpp_base base;
    PolygonMeshIntPropertyJNI vintmap;

    const cpp_base& get_data() const {return base;}
          cpp_base& get_data()       {return base;}
  public:
  // Construction
    Mean_curvature_flow_skeletonization(PolygonMesh& pm, PolygonMeshIntPropertyJNI& vertex_int_map)
      : base(pm), vintmap(vertex_int_map) {}
  // Local Remeshing Parameters
    SWIG_CGAL_FORWARD_CALL_0(double, max_triangle_angle)
    SWIG_CGAL_FORWARD_CALL_0(double, min_edge_length)
    SWIG_CGAL_FORWARD_CALL_1(void, set_max_triangle_angle, double)
    SWIG_CGAL_FORWARD_CALL_1(void, set_min_edge_length, double)
  // Algorithm Termination Parameters
    SWIG_CGAL_FORWARD_CALL_0(int,max_iterations)
    SWIG_CGAL_FORWARD_CALL_0(double, area_variation_factor)
    SWIG_CGAL_FORWARD_CALL_1(void, set_max_iterations, int)
    SWIG_CGAL_FORWARD_CALL_1(void, set_area_variation_factor, double)
  // Vertex Motion Parameters
    SWIG_CGAL_FORWARD_CALL_0(double, quality_speed_tradeoff)
    SWIG_CGAL_FORWARD_CALL_0(bool, is_medially_centered)
    SWIG_CGAL_FORWARD_CALL_0(double, medially_centered_speed_tradeoff)
    SWIG_CGAL_FORWARD_CALL_1(void, set_quality_speed_tradeoff, double)
    SWIG_CGAL_FORWARD_CALL_1(void, set_is_medially_centered, bool)
    SWIG_CGAL_FORWARD_CALL_1(void, set_medially_centered_speed_tradeoff, double)
  // High Level Function
    void run(PolygonMeshSkeletonJNI skeleton)
    {
      CGAL::Mean_curvature_flow_skeletonization<PolygonMesh>::Skeleton cpp_skeleton;
      get_data()(cpp_skeleton);
      PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Vertex_descriptor, int>
        vertex_to_skeleton(vintmap);
      convert_skeleton(cpp_skeleton, vertex_to_skeleton, skeleton);
    }
  // Low Level Functions
    SWIG_CGAL_FORWARD_CALL_0(void, contract_geometry)
    SWIG_CGAL_FORWARD_CALL_0(int, collapse_edges)
    SWIG_CGAL_FORWARD_CALL_0(int, split_faces)
    SWIG_CGAL_FORWARD_CALL_0(int, detect_degeneracies)
    SWIG_CGAL_FORWARD_CALL_0(void, contract)
    SWIG_CGAL_FORWARD_CALL_0(void, contract_until_convergence)
    void convert_to_skeleton(PolygonMeshSkeletonJNI skeleton)
    {
      CGAL::Mean_curvature_flow_skeletonization<PolygonMesh>::Skeleton cpp_skeleton;
      get_data().convert_to_skeleton(cpp_skeleton);

      PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Vertex_descriptor, int>
        vertex_to_skeleton(vintmap);
      convert_skeleton(cpp_skeleton, vertex_to_skeleton, skeleton);
    }

    void meso_skeleton(PolygonMesh& pm)
    {
      CGAL::copy_face_graph(get_data().meso_skeleton(), pm);
    }
  };
};

#endif //SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_DEFORMATION_H
