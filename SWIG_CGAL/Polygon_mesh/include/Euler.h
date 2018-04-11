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

#ifndef SWIG_CGAL_POLYGON_MESH_EULER_H
#define SWIG_CGAL_POLYGON_MESH_EULER_H

#include <CGAL/boost/graph/Euler_operations.h>
#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>

struct Euler{
  typedef PolygonMesh::Halfedge_descriptor HD;
  typedef PolygonMesh::Edge_descriptor ED;
  typedef PolygonMesh::Face_descriptor FD;
  typedef PolygonMesh::Vertex_descriptor VD;

  /// returns a halfedge_descriptor
  static int add_center_vertex(int hd, PolygonMesh& pm){
    return CGAL::Euler::add_center_vertex(HD(hd), pm);
  }

  /// returns an edge_descriptor
  static int add_edge(int vd1, int vd2, PolygonMesh& pm){
    return CGAL::Euler::add_edge(VD(vd1), VD(vd2), pm);
  }

  /// returns a face_descriptor
  static int add_face(RangeIndexJNI vertex_range, PolygonMesh& pm){
    return CGAL::Euler::add_face(
      CGAL::make_range(vertex_range.indices, vertex_range.indices+vertex_range.size),
      pm);
  }

  /// returns a halfedge_descriptor
  static int add_face_to_border(int hd1, int hd2, PolygonMesh& pm){
    return CGAL::Euler::add_face_to_border(HD(hd1), HD(hd2), pm);
  }

  /// returns a halfedge_descriptor
  static int add_vertex_and_face_to_border(int hd1, int hd2, PolygonMesh& pm){
    return CGAL::Euler::add_vertex_and_face_to_border(HD(hd1), HD(hd2), pm);
  }

  /// returns a vertex_descriptor
  static int collapse_edge(int ed, PolygonMesh& pm){
    return CGAL::Euler::collapse_edge(ED(ed), pm);
  }

  /// returns a vertex_descriptor
  static int collapse_edge (int ed, PolygonMesh& pm, RangeIndexJNI constrained_edges)
  {
    if (constrained_edges.indices==NULL) return -1;
    std::set<int> cst_edges(constrained_edges.indices,
                            constrained_edges.indices+constrained_edges.size);
    return CGAL::Euler::collapse_edge(ED(ed), pm,
                            Constrained_edge_map(cst_edges));
  }

  static bool does_satisfy_link_condition(int ed, PolygonMesh& pm){
    return CGAL::Euler::does_satisfy_link_condition(ED(ed), pm);
  }

  static void fill_hole(int hd, PolygonMesh& pm){
    CGAL::Euler::fill_hole(HD(hd), pm);
  }

  static void flip_edge(int hd, PolygonMesh& pm){
    CGAL::Euler::flip_edge (HD(hd), pm);
  }

  /// returns a halfedge_descriptor
  static int join_face(int hd, PolygonMesh& pm){
    return CGAL::Euler::join_face(HD(hd), pm);
  }

  /// returns a halfedge_descriptor
  static int join_loop(int hd1, int hd2, PolygonMesh& pm){
    return CGAL::Euler::join_loop(HD(hd1), HD(hd2), pm);
  }

  /// returns a halfedge_descriptor
  static int join_vertex(int hd, PolygonMesh& pm){
    return CGAL::Euler::join_vertex(HD(hd), pm);
  }

  static void make_hole(int hd, PolygonMesh& pm){
    CGAL::Euler::make_hole(HD(hd), pm);
  }

  /// returns a halfedge_descriptor
  static int remove_center_vertex(int hd, PolygonMesh& pm){
    return CGAL::Euler::remove_center_vertex(HD(hd), pm);
  }

  static void remove_face(int hd, PolygonMesh& pm){
    CGAL::Euler::remove_face (HD(hd), pm);
  }

  /// returns a halfedge_descriptor
  static int split_edge(int hd, PolygonMesh& pm){
    return CGAL::Euler::split_edge(HD(hd), pm);
  }

  /// returns a halfedge_descriptor
  static int split_face(int hd1, int hd2, PolygonMesh& pm){
    return CGAL::Euler::split_face(HD(hd1), HD(hd2), pm);
  }

  /// returns a halfedge_descriptor
  static int split_loop(int hd1, int hd2, int hd3, PolygonMesh& pm){
    return CGAL::Euler::split_loop(HD(hd1), HD(hd2), HD(hd3), pm);
  }

  /// returns a halfedge_descriptor
  static int split_vertex(int hd1, int hd2, PolygonMesh& pm){
    return CGAL::Euler::split_vertex(HD(hd1), HD(hd2), pm);
  }
};

#endif // SWIG_CGAL_POLYGON_MESH_EULER_H
