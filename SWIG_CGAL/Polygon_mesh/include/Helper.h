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

#ifndef SWIG_CGAL_POLYGON_MESH_HELPER_H
#define SWIG_CGAL_POLYGON_MESH_HELPER_H

#include <CGAL/boost/graph/helpers.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <CGAL/IO/OFF_reader.h>

#include <sstream>

struct Helper{
  typedef PolygonMesh::Halfedge_descriptor HD;
  typedef PolygonMesh::Edge_descriptor ED;
  typedef PolygonMesh::Face_descriptor FD;
  typedef PolygonMesh::Vertex_descriptor VD;

  static void clear (PolygonMesh& pm){
    CGAL::clear(pm);
  }

  static bool is_bivalent (int hd, PolygonMesh& pm){
   return CGAL::is_bivalent(HD(hd), pm);
  }
  static bool is_bivalent_mesh (PolygonMesh& pm){
    return CGAL::is_bivalent_mesh(pm);
  }

  static bool is_border (int hd, PolygonMesh& pm){
    return CGAL::is_border(HD(hd), pm);
  }

  /// return a halfedge_descriptor >=0 if the vertex is on the border
  /// and -1 otherwise
  static int is_vertex_on_border (int vd, PolygonMesh& pm)
  {
    boost::optional<HD> res = CGAL::is_border(VD(vd), pm);
    if (res) return *res;
    return -1;
  }

  // this function needs to be renamed since there is no distinction
  // on edge and halfedge descriptors
  static bool is_edge_on_border (int ed, PolygonMesh& pm){
    return CGAL::is_border(ED(ed), pm);
  }

  static bool is_border_edge (int hd, PolygonMesh& pm){
    return CGAL::is_border_edge(HD(hd), pm);
  }

  static bool is_closed (PolygonMesh& pm){
    return CGAL::is_closed(pm);
  }

  static bool is_hexahedron (int hd, PolygonMesh& pm){
   return CGAL::is_hexahedron(HD(hd), pm);
  }

  static bool is_isolated_quad (int hd, PolygonMesh& pm){
   return CGAL::is_isolated_quad(HD(hd), pm);
  }

  static bool is_isolated_triangle (int hd, PolygonMesh& pm){
   return CGAL::is_isolated_triangle(HD(hd), pm);
  }

  static bool is_quad (int hd, PolygonMesh& pm){
   return CGAL::is_quad(HD(hd), pm);
  }

  static bool is_quad_mesh (PolygonMesh& pm){
    return CGAL::is_quad_mesh(pm);
  }

  static bool is_tetrahedron (int hd, PolygonMesh& pm){
   return CGAL::is_tetrahedron(HD(hd), pm);
  }

  static bool is_triangle (int hd, PolygonMesh& pm){
   return CGAL::is_triangle(HD(hd), pm);
  }

  static bool is_triangle_mesh (PolygonMesh& pm){
    return CGAL::is_triangle_mesh(pm);
  }

  static bool is_trivalent (int hd, PolygonMesh& pm){
   return CGAL::is_trivalent(HD(hd), pm);
  }

  static bool is_trivalent_mesh (PolygonMesh& pm){
    return CGAL::is_trivalent_mesh(pm);
  }

  /// TODO halfedge_descriptor CGAL::make_triangle (const P &p0, const P &p1, const P &p2, Graph &g)
  /// TODO halfedge_descriptor CGAL::make_quad (const P &p0, const P &p1, const P &p2, const P &p3, Graph &g)
  /// TODO halfedge_descriptor CGAL::make_hexahedron (const P &p0, const P &p1, const P &p2, const P &p3, const P &p4, const P &p5, const P &p6, const P &p7, Graph &g)
  /// TODO halfedge_descriptor CGAL::make_tetrahedron (const P &p0, const P &p1, const P &p2, const P &p3, Graph &g)


  // non-CGAL one
  static void read_off(PolygonMesh& pm, const char* fname)
  {
    std::vector< CGAL::Simple_cartesian<double>::Point_3 > points;
    std::vector< std::vector<std::size_t> > polygons;
    std::ifstream in(fname);
    CGAL::read_OFF(in, points, polygons);
    PMP::polygon_soup_to_polygon_mesh(points, polygons, pm);
  }

  static void write_off(PolygonMesh& pm, const char* fname)
  {
    std::ofstream output(fname);
    std::vector<int> vids(pm.vertexCapacity(), -1);
    int i=-1;
    output << "OFF\n " << pm.numberOfVertices() << " " << pm.numberOfFaces() << " 0\n";
    BOOST_FOREACH(PolygonMesh::Vertex_descriptor vi, pm.vertices())
    {
      vids[(int) vi]=++i;
      output << get(get(boost::vertex_point, pm), vi) << "\n";
    }
    BOOST_FOREACH(PolygonMesh::Face_descriptor fi, pm.faces())
    {
      std::size_t nbf = CGAL::halfedges_around_face(halfedge(fi, pm), pm).size();
      output << nbf;
      BOOST_FOREACH(PolygonMesh::Halfedge_descriptor hi, CGAL::halfedges_around_face(halfedge(fi, pm), pm))
        output << " " << vids[(int) target(hi,pm)];
      output << "\n";
    }
  }

  static void read_xyz(PointSet& ps, const char* fname, bool clear=true)
  {
    if (clear)
      ps.clear();
    CGAL::Simple_cartesian<double>::Point_3 p(0,0,0);
    std::ifstream in(fname);
    std::string line;
    std::istringstream iss;

    getline(in,line);
    iss.str(line);
    int n=0;
    iss >> n;
    ps.add_points(n);
    for (int i=0; i<n; ++i)
    {
      getline(in,line);
      iss.clear();
      iss.str(line);
      iss >> p;
      ps.set_point(i, p);
    }
  }

  static void write_xyz(PointSet& ps, const char* fname)
  {
    std::ofstream output(fname);
    output << ps.size() << "\n";
    for (int i=0; i<ps.size(); ++i)
      output << ps.point<CGAL::Simple_cartesian<double>::Point_3>(i) << "\n";
  }
};

#endif //SWIG_CGAL_POLYGON_MESH_HELPER_H
