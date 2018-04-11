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

#ifndef SWIG_CGAL_POLYGON_MESH_PMP_H
#define SWIG_CGAL_POLYGON_MESH_PMP_H

#include <CGAL/polygon_mesh_processing.h>
#include <CGAL/Polygon_mesh_processing/random_perturbation.h>
#include <CGAL/Polygon_mesh_processing/distance.h>
#include <CGAL/Polygon_mesh_slicer.h>
#include <CGAL/Side_of_triangle_mesh.h>
#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <boost/shared_ptr.hpp>
#include <boost/function_output_iterator.hpp>

#ifndef SWIG
namespace PMP=CGAL::Polygon_mesh_processing;
namespace params=PMP::parameters;
#endif

struct Polygon_mesh_processing{

  typedef PolygonMesh::Halfedge_descriptor HD;
  typedef PolygonMesh::Edge_descriptor ED;
  typedef PolygonMesh::Face_descriptor FD;
  typedef PolygonMesh::Vertex_descriptor VD;

// Meshing Functions
//   CGAL::Polygon_mesh_processing::fair()
  static
  void fair(PolygonMesh& pm,
            RangeIndexJNI vertex_range)
  {
    if (vertex_range.indices == NULL)
      PMP::fair(pm,vertices(pm));
    else
      PMP::fair(pm,make_range(vertex_range));
  }

  static
  void fair(PolygonMesh& pm,
            RangeIndexJNI vertex_range,
            int fairing_continuity)
  {
    if (vertex_range.indices == NULL)
      PMP::fair(pm,vertices(pm),
                params::fairing_continuity(fairing_continuity));
    else
      PMP::fair(pm,make_range(vertex_range),
                params::fairing_continuity(fairing_continuity));
  }

//   CGAL::Polygon_mesh_processing::refine()
  static
  void refine( PolygonMesh& pm,
               RangeIndexJNI face_range,
               WritableRangeIndexJNI face_output,
               WritableRangeIndexJNI vertex_output)
  {
    if (face_range.indices == NULL)
      PMP::refine(pm, faces(pm),
                  std::back_inserter(face_output),
                  std::back_inserter(vertex_output));
    else
      PMP::refine(pm,
                  make_range(face_range),
                  std::back_inserter(face_output),
                  std::back_inserter(vertex_output));
  }
  static
  void refine( PolygonMesh& pm,
               RangeIndexJNI face_range,
               WritableRangeIndexJNI face_output,
               WritableRangeIndexJNI vertex_output,
               double density_control_factor)
  {
    if (face_range.indices == NULL)
      PMP::refine(pm, faces(pm),
                  std::back_inserter(face_output),
                  std::back_inserter(vertex_output),
                  PMP::parameters::density_control_factor(density_control_factor));
    else
      PMP::refine(pm,
                  make_range(face_range),
                  std::back_inserter(face_output),
                  std::back_inserter(vertex_output),
                  PMP::parameters::density_control_factor(density_control_factor));
  }
//   CGAL::Polygon_mesh_processing::triangulate_face()
  static
  void triangulate_face(int fd, PolygonMesh& pm)
  {
    PMP::triangulate_face(FD(fd), pm);
  }

//   CGAL::Polygon_mesh_processing::triangulate_faces()
  static
  void triangulate_faces(PolygonMesh& pm)
  {
    PMP::triangulate_faces(pm);
  }

  static
  void triangulate_faces(RangeIndexJNI face_range,
                         PolygonMesh& pm)
  {
    if (face_range.indices == NULL)
      PMP::triangulate_faces(faces(pm), pm);
    else
      PMP::triangulate_faces(make_range(face_range), pm);
  }

  //   CGAL::Polygon_mesh_processing::isotropic_remeshing() (4.8)
  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           int number_of_iterations,
                           RangeIndexJNI constrained_edges,
                           bool protect_constraints=false)
  {
    std::set<int> cst_edges;
    if (constrained_edges.indices==NULL)
      cst_edges.insert(edges(pm).first, edges(pm).second);
    else
      cst_edges.insert(constrained_edges.indices,
                       constrained_edges.indices+constrained_edges.size);

    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(Constrained_edge_map(cst_edges))
                               .protect_constraints(protect_constraints)
                            );
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(Constrained_edge_map(cst_edges))
                               .protect_constraints(protect_constraints)
                            );
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           int number_of_iterations,
                           RangeIndexJNI constrained_edges,
                           RangeIndexJNI constrained_vertices,
                           bool protect_constraints=false)
  {
    std::set<int> cst_edges;
    std::set<int> cst_vertices;
    if (constrained_edges.indices==NULL)
      cst_edges.insert(edges(pm).first, edges(pm).second);
    else
      cst_edges.insert(constrained_edges.indices,
                       constrained_edges.indices+constrained_edges.size);

    if (constrained_vertices.indices==NULL)
      cst_vertices.insert(vertices(pm).first, vertices(pm).second);
    else
      cst_vertices.insert(constrained_vertices.indices,
                          constrained_vertices.indices+constrained_vertices.size);

    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(Constrained_edge_map(cst_edges))
                               .vertex_is_constrained_map(Constrained_vertex_map(cst_vertices))
                               .protect_constraints(protect_constraints)
                            );
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(Constrained_edge_map(cst_edges))
                               .vertex_is_constrained_map(Constrained_vertex_map(cst_vertices))
                               .protect_constraints(protect_constraints)
                            );
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           int number_of_iterations,
                           PolygonMeshBoolPropertyJNI& edge_bool_map,
                           bool protect_constraints=false)
  {
    PolygonMesh_property<PolygonMeshBoolPropertyJNI, PolygonMesh::Edge_descriptor, bool> ecm(edge_bool_map);
    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(ecm)
                               .protect_constraints(protect_constraints)
                            );
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(ecm)
                               .protect_constraints(protect_constraints)
                            );
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           int number_of_iterations,
                           PolygonMeshBoolPropertyJNI& edge_bool_map,
                           PolygonMeshBoolPropertyJNI& vertex_bool_map,
                           bool protect_constraints=false)
  {
    PolygonMesh_property<PolygonMeshBoolPropertyJNI, PolygonMesh::Vertex_descriptor, bool> vcm(vertex_bool_map);
    PolygonMesh_property<PolygonMeshBoolPropertyJNI, PolygonMesh::Edge_descriptor, bool> ecm(edge_bool_map);

    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(ecm)
                               .vertex_is_constrained_map(vcm)
                               .protect_constraints(protect_constraints)
                            );
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .edge_is_constrained_map(ecm)
                               .vertex_is_constrained_map(vcm)
                               .protect_constraints(protect_constraints)
                            );
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           int number_of_iterations,
                           bool protect_constraints)
  {
    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .protect_constraints(protect_constraints)
                            );
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations)
                               .protect_constraints(protect_constraints)
                            );
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           bool protect_constraints)
  {
    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::protect_constraints(protect_constraints));
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::protect_constraints(protect_constraints));
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm,
                           int number_of_iterations)
  {
    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations));
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm,
                               params::number_of_iterations(number_of_iterations));
  }

  static
  void isotropic_remeshing(RangeIndexJNI face_range,
                           double target_edge_length,
                           PolygonMesh& pm)
  {
    if (face_range.indices==NULL)
      PMP::isotropic_remeshing(faces(pm), target_edge_length, pm);
    else
      PMP::isotropic_remeshing(make_range(face_range), target_edge_length, pm);
  }
//   CGAL::Polygon_mesh_processing::split_long_edges() (4.8)
  static
  void split_long_edges(RangeIndexJNI edge_range,
                        double max_length,
                        PolygonMesh& pm)
  {
    if (edge_range.indices==NULL)
      PMP::split_long_edges(edges(pm), max_length, pm);
    else
      PMP::split_long_edges(make_range(edge_range), max_length, pm);
  }

// CGAL::Polygon_mesh_processing::random_perturbation() (4.11)
#if CGAL_VERSION_NR > 1041001000
  static
  void random_perturbation(RangeIndexJNI vertex_range,
                           PolygonMesh& pm,
                           double perturbation_max_size,
                           bool do_project = true,
                           int random_seed = -1)
  {
    if (vertex_range.indices == NULL)
    {
      if (random_seed>=0)
        PMP::random_perturbation(vertices(pm), pm, perturbation_max_size,
                                 params::do_project(do_project));
      else
        PMP::random_perturbation(vertices(pm), pm, perturbation_max_size,
                                 params::do_project(do_project).random_seed(random_seed));
    }
    else
    {
      if (random_seed>=0)
        PMP::random_perturbation(make_range(vertex_range), pm, perturbation_max_size,
                                 params::do_project(do_project));
      else
        PMP::random_perturbation(make_range(vertex_range), pm, perturbation_max_size,
                                 params::do_project(do_project).random_seed(random_seed));
    }
  }

  static
  void random_perturbation(RangeIndexJNI vertex_range,
                           PolygonMesh& pm,
                           double perturbation_max_size,
                           RangeIndexJNI constrained_vertices,
                           bool do_project = true,
                           int random_seed = -1)
  {
    std::set<int> cst_vertices;
    if (constrained_vertices.indices==NULL)
      cst_vertices.insert(vertices(pm).first, vertices(pm).second);
    else
      cst_vertices.insert(constrained_vertices.indices,
                          constrained_vertices.indices+constrained_vertices.size);

    if (vertex_range.indices == NULL)
    {
      if (random_seed>=0)
        PMP::random_perturbation(vertices(pm), pm, perturbation_max_size,
                                 params::do_project(do_project)
                                 .vertex_is_constrained_map(Constrained_vertex_map(cst_vertices)));
      else
        PMP::random_perturbation(vertices(pm), pm, perturbation_max_size,
                                 params::do_project(do_project).random_seed(random_seed)
                                 .vertex_is_constrained_map(Constrained_vertex_map(cst_vertices)));
    }
    else
    {
      if (random_seed>=0)
        PMP::random_perturbation(make_range(vertex_range), pm, perturbation_max_size,
                                 params::do_project(do_project)
                                 .vertex_is_constrained_map(Constrained_vertex_map(cst_vertices)));
      else
        PMP::random_perturbation(make_range(vertex_range), pm, perturbation_max_size,
                                 params::do_project(do_project).random_seed(random_seed)
                                 .vertex_is_constrained_map(Constrained_vertex_map(cst_vertices)));
    }
  }
#endif
// Hole Filling Functions
//   CGAL::Polygon_mesh_processing::triangulate_hole()
  static
  void triangulate_hole(PolygonMesh& pm,
                        int hd,
                        WritableRangeIndexJNI face_output,
                        bool use_delaunay = true)
  {
    CGAL::Polygon_mesh_processing::triangulate_hole(pm, HD(hd),
                                                    std::back_inserter(face_output),
                                                    params::use_delaunay_triangulation(use_delaunay));
  }
//   CGAL::Polygon_mesh_processing::triangulate_and_refine_hole()
  static
  void triangulate_and_refine_hole( PolygonMesh& pm,
                                    int hd,
                                    WritableRangeIndexJNI face_output,
                                    WritableRangeIndexJNI vertex_output,
                                    bool use_delaunay = true)
  {
    PMP::triangulate_and_refine_hole(pm, HD(hd),
                                     std::back_inserter(face_output),
                                     std::back_inserter(vertex_output),
                                     params::use_delaunay_triangulation(use_delaunay));
  }
  static
  void triangulate_and_refine_hole( PolygonMesh& pm,
                                    int hd,
                                    WritableRangeIndexJNI face_output,
                                    WritableRangeIndexJNI vertex_output,
                                    double density_control_factor,
                                    bool use_delaunay = true)
  {
    PMP::triangulate_and_refine_hole(pm, HD(hd),
                                     std::back_inserter(face_output),
                                     std::back_inserter(vertex_output),
                                     params::density_control_factor(density_control_factor).
                                     use_delaunay_triangulation(use_delaunay));
  }
//   CGAL::Polygon_mesh_processing::triangulate_refine_and_fair_hole()
  static
  void triangulate_refine_and_fair_hole( PolygonMesh& pm,
                                         int hd,
                                         WritableRangeIndexJNI face_output,
                                         WritableRangeIndexJNI vertex_output,
                                         bool use_delaunay = true)
  {
    PMP::triangulate_refine_and_fair_hole(pm, HD(hd),
                                          std::back_inserter(face_output),
                                          std::back_inserter(vertex_output),
                                          params::use_delaunay_triangulation(use_delaunay));
  }
  static
  void triangulate_refine_and_fair_hole( PolygonMesh& pm,
                                         int hd,
                                         WritableRangeIndexJNI face_output,
                                         WritableRangeIndexJNI vertex_output,
                                         double density_control_factor,
                                         bool use_delaunay = true)
  {
    PMP::triangulate_refine_and_fair_hole(pm, HD(hd),
                                          std::back_inserter(face_output),
                                          std::back_inserter(vertex_output),
                                          params::density_control_factor(density_control_factor).
                                                  use_delaunay_triangulation(use_delaunay));
  }
  static
  void triangulate_refine_and_fair_hole( PolygonMesh& pm,
                                         int hd,
                                         WritableRangeIndexJNI face_output,
                                         WritableRangeIndexJNI vertex_output,
                                         double density_control_factor,
                                         int fairing_continuity,
                                         bool use_delaunay = true)
  {
    PMP::triangulate_refine_and_fair_hole(pm, HD(hd),
                                          std::back_inserter(face_output),
                                          std::back_inserter(vertex_output),
                                          params::density_control_factor(density_control_factor).
                                          fairing_continuity(fairing_continuity).
                                          use_delaunay_triangulation(use_delaunay));
  }

// //   CGAL::Polygon_mesh_processing::triangulate_hole_polyline()
//   static
//   void triangulate_hole_polyline (Point_3_range points,
//                                   Point_3_range third_points,
//                                   Integer_triple_output_iterator out)
//   {
//     PMP::triangulate_hole_polyline(CGAL::make_range(points),
//                                    CGAL::make_range(third_points),
//                                    out);
//   }
//
//   static
//   void triangulate_hole_polyline (Point_3_range points,
//                                    Integer_triple_output_iterator out)
//   {
//     PMP::triangulate_hole_polyline( CGAL::make_range(points),
//                                     out);
//   }
//

//
// Predicate Functions
//   CGAL::Polygon_mesh_processing::does_self_intersect()
  static
  bool does_self_intersect(PolygonMesh& pm)
  {
    return PMP::does_self_intersect(pm);
  }
// //   CGAL::Polygon_mesh_processing::self_intersections()
//   void self_intersections(PolygonMesh& pm,
//                           Facet_pair_output_iterator out)
//   {
//     PMP::self_intersections(pm, out);
//   }
//
// Orientation Functions
//   CGAL::Polygon_mesh_processing::is_outward_oriented()
  static
  bool is_outward_oriented(PolygonMesh& pm)
  {
    return PMP::is_outward_oriented(pm);
  }
//   CGAL::Polygon_mesh_processing::reverse_face_orientations()
  static
  void reverse_face_orientations(PolygonMesh& pm)
  {
    PMP::reverse_face_orientations(pm);
  }
  static
  void reverse_face_orientations(RangeIndexJNI face_range,
                                 PolygonMesh& pm)
  {
    if (face_range.indices==NULL)
      PMP::reverse_face_orientations(faces(pm), pm);
    else
      PMP::reverse_face_orientations(make_range(face_range), pm);
  }
//   CGAL::Polygon_mesh_processing::orient_polygon_soup()
  // static
  // bool orient_polygon_soup(std::vector<Point_3>& points,
  //                          std::vector< std::vector<int> >& polygons)
  // {
  //   std::size_t nb_pts = points.size();
  //   std::vector< Point_3::cpp_base > cgal_points;
  //   cgal_points.reserve(nb_pts);
  //   BOOST_FOREACH(const Point_3& pt, points)
  //     cgal_points.push_back( pt.get_data() );
  //   bool res = PMP::orient_polygon_soup(cgal_points, polygons);
  //   if (cgal_points.size()>nb_pts)
  //     for (std::size_t i=nb_pts;i<cgal_points.size();++i)
  //       points.push_back( Point_3(cgal_points[i]) );
  //   return res;
  // }
//
// Combinatorial Repairing Functions
//   CGAL::Polygon_mesh_processing::stitch_borders()
  static
  void stitch_borders(PolygonMesh& pm)
  {
    PMP::stitch_borders(pm);
  }
  // void stitch_borders(PolygonMesh& pm,
  //                     Halfedge_pair_range hedges)
  // {
  //   PMP::stitch_borders(pm, hedges);
  // }

// CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh() (4.9)
#if CGAL_VERSION_NR > 1040801000
  static
  bool is_triangle_soup_a_polygon_mesh(boost::shared_ptr< std::vector< std::vector<int> > > polygons)
  {
    return PMP::is_polygon_soup_a_polygon_mesh(*polygons);
  }
#endif

//   CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh()
  // void polygon_soup_to_polygon_mesh(const std::vector<Point_3>& points,
  //                                   const std::vector< std::vector<int> >& polygons,
  //                                   PolygonMesh& pm)
  // {
  //   std::size_t nb_pts = points.size();
  //   std::vector< Point_3::cpp_base > cgal_points;
  //   cgal_points.reserve(nb_pts);
  //   BOOST_FOREACH(const Point_3& pt, points)
  //     cgal_points.push_back( pt.get_data() );
  //   PMP::polygon_soup_to_polygon_mesh(cgal_points, polygons, pm);
  // }
  static
  void triangle_soup_to_polygon_mesh(boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points,
                                     boost::shared_ptr< std::vector< std::vector<int> > > polygons,
                                     PolygonMesh& pm)
  {
    PMP::polygon_soup_to_polygon_mesh(*points, *polygons, pm);
  }

//   CGAL::Polygon_mesh_processing::remove_isolated_vertices() (4.8)
  static
  void remove_isolated_vertices(PolygonMesh& pm)
  {
    PMP::remove_isolated_vertices(pm);
  }

//
// Normal Computation Functions
//   CGAL::Polygon_mesh_processing::compute_face_normal()
  // static
  // Vector_3 compute_face_normal(Polyhedron_3_Facet_handle_SWIG_wrapper& face,
  //                              PolygonMesh& pm)
  // {
  //   return PMP::compute_face_normal(face.get_data(), pm);
  // }
  // static
  // void compute_face_normal(Polyhedron_3_Facet_handle_SWIG_wrapper& face,
  //                          PolygonMesh& pm,
  //                          Vector_3& output_normal)
  // {
  //   output_normal=Vector_3(
  //       PMP::compute_face_normal(face.get_data(), pm) );
  // }
//   CGAL::Polygon_mesh_processing::compute_face_normals()
  static
  void compute_face_normals(PolygonMesh& pm,
                            PolygonMeshDoublePropertyJNI& face_double_map)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Face_descriptor, EPIC_Kernel::Vector_3> pmap(face_double_map);
    PMP::compute_face_normals(pm, pmap);
  }
//   CGAL::Polygon_mesh_processing::compute_vertex_normal()
  // static
  // Vector_3 compute_vertex_normal(Polyhedron_3_Vertex_handle_SWIG_wrapper& vertex,
  //                                PolygonMesh& pm)
  // {
  //   return PMP::compute_vertex_normal(vertex.get_data(), pm);
  // }
  // static
  // void compute_vertex_normal(Polyhedron_3_Vertex_handle_SWIG_wrapper& vertex,
  //                            PolygonMesh& pm,
  //                            Vector_3& output_normal)
  // {
  //   output_normal=Vector_3(
  //       PMP::compute_vertex_normal(vertex.get_data(), pm) );
  // }
//   CGAL::Polygon_mesh_processing::compute_vertex_normals()
  static
  void compute_vertex_normals(PolygonMesh& pm,
                              PolygonMeshDoublePropertyJNI& vertex_double_map)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Vertex_descriptor, EPIC_Kernel::Vector_3> pmap(vertex_double_map);
    PMP::compute_vertex_normals(pm, pmap);
  }
//   CGAL::Polygon_mesh_processing::compute_normals()
//
  static
  void compute_normals(PolygonMesh& pm,
                       PolygonMeshDoublePropertyJNI& vertex_double_map,
                       PolygonMeshDoublePropertyJNI& face_double_map)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Vertex_descriptor, EPIC_Kernel::Vector_3> vpmap(vertex_double_map);
    PolygonMesh_property<PolygonMeshDoublePropertyJNI, PolygonMesh::Face_descriptor, EPIC_Kernel::Vector_3> fpmap(face_double_map);
    PMP::compute_normals(pm, vpmap, fpmap);
  }

// Connected Components
//   CGAL::Polygon_mesh_processing::connected_component()
  static
  void connected_component (int seed_face,
                            PolygonMesh& pm,
                            WritableRangeIndexJNI face_output)
  {
    PMP::connected_component(FD(seed_face), pm, std::back_inserter(face_output));
  }

  static
  void connected_component (int seed_face,
                            PolygonMesh& pm,
                            WritableRangeIndexJNI face_output,
                            PolygonMeshBoolPropertyJNI& edge_bool_map)
  {
    PolygonMesh_property<PolygonMeshBoolPropertyJNI, PolygonMesh::Edge_descriptor, bool> ecm(edge_bool_map);
    PMP::connected_component(FD(seed_face), pm, std::back_inserter(face_output),
                             PMP::parameters::edge_is_constrained_map(ecm));
  }

//   CGAL::Polygon_mesh_processing::connected_components()
  static
  int connected_components(PolygonMesh& pm,
                           PolygonMeshIntPropertyJNI& face_int_map)
  {
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Face_descriptor, int> pmap(face_int_map);
    return PMP::connected_components(pm, pmap);
  }

  static
  int
  connected_components(PolygonMesh& pm,
                       PolygonMeshIntPropertyJNI& face_int_map,
                       PolygonMeshBoolPropertyJNI& edge_bool_map)
  {
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Face_descriptor, int> f_ccs(face_int_map);
    PolygonMesh_property<PolygonMeshBoolPropertyJNI, PolygonMesh::Edge_descriptor, bool> ecm(edge_bool_map);
    return PMP::connected_components(pm, f_ccs, PMP::parameters::edge_is_constrained_map(ecm));
  }

//   CGAL::Polygon_mesh_processing::keep_large_connected_components() (4.8)
  static
  int keep_large_connected_components(PolygonMesh& pm,
                                      int threshold_components_to_keep)
  {
    return PMP::keep_large_connected_components(pm,
                                                threshold_components_to_keep);
  }

//   CGAL::Polygon_mesh_processing::keep_largest_connected_components()
  static
  int keep_largest_connected_components(PolygonMesh& pm,
                                        int nb_components_to_keep)
  {
    return PMP::keep_largest_connected_components(pm,
                                                  nb_components_to_keep);
  }
//   CGAL::Polygon_mesh_processing::keep_connected_components()
  static
  void keep_connected_components(PolygonMesh& pm,
                                 RangeIndexJNI face_range)
  {
    if (face_range.indices!=NULL)
      PMP::keep_connected_components(pm,
                                     make_range(face_range));
  }
  static
  void keep_connected_components(PolygonMesh& pm,
                                 boost::shared_ptr<std::vector<int> > components_to_keep,
                                 PolygonMeshIntPropertyJNI& face_int_map)
  {
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Face_descriptor, int> pmap(face_int_map);
    PMP::keep_connected_components(pm,
                                   *components_to_keep,
                                   pmap);
  }

//   CGAL::Polygon_mesh_processing::remove_connected_components()
  static
  void remove_connected_components( PolygonMesh& pm,
                                    RangeIndexJNI face_range)
  {
    if (face_range.indices==NULL)
      CGAL::clear(pm);
    else
      PMP::remove_connected_components(pm,
                                       make_range(face_range));
  }

  static
  void remove_connected_components(PolygonMesh& pm,
                                   boost::shared_ptr<std::vector<int> > components_to_remove,
                                   PolygonMeshIntPropertyJNI& face_int_map)
  {
    PolygonMesh_property<PolygonMeshIntPropertyJNI, PolygonMesh::Face_descriptor, int> pmap(face_int_map);
    PMP::remove_connected_components(pm,
                                     *components_to_remove,
                                     pmap);
  }

//
// Corefinement and Boolean Operation Functions
//

// CGAL::Polygon_mesh_processing::corefine_and_compute_union() (4.10)
  static
  void corefine_and_compute_union(PolygonMesh& pm1, PolygonMesh& pm2, PolygonMesh& pm_out)
  {
    if (same_java_meshes(pm1, pm_out))
      PMP::corefine_and_compute_union(pm1, pm2, pm1);
    else
      if (same_java_meshes(pm2, pm_out))
        PMP::corefine_and_compute_union(pm1, pm2, pm2);
      else
        PMP::corefine_and_compute_union(pm1, pm2, pm_out);
  }

// CGAL::Polygon_mesh_processing::corefine_and_compute_difference() (4.10)
  static
  void corefine_and_compute_difference(PolygonMesh& pm1, PolygonMesh& pm2, PolygonMesh& pm_out)
  {
    if (same_java_meshes(pm1, pm_out))
      PMP::corefine_and_compute_difference(pm1, pm2, pm1);
    else
      if (same_java_meshes(pm2, pm_out))
        PMP::corefine_and_compute_difference(pm1, pm2, pm2);
      else
        PMP::corefine_and_compute_difference(pm1, pm2, pm_out);
  }

// CGAL::Polygon_mesh_processing::corefine_and_compute_intersection() (4.10)
  static
  void corefine_and_compute_intersection(PolygonMesh& pm1, PolygonMesh& pm2, PolygonMesh& pm_out)
  {
    if (same_java_meshes(pm1, pm_out))
    {
      PMP::corefine_and_compute_intersection(pm1, pm2, pm1);
    }
    else
      if (same_java_meshes(pm2, pm_out))
        PMP::corefine_and_compute_intersection(pm1, pm2, pm2);
      else
        PMP::corefine_and_compute_intersection(pm1, pm2, pm_out);
  }

//   CGAL::Polygon_mesh_processing::corefine() (4.10)
  static
  void corefine(PolygonMesh& pm1, PolygonMesh& pm2)
  {
    if (!same_java_meshes(pm1, pm2))
      PMP::corefine(pm1, pm2);
  }

// CGAL::Polygon_mesh_processing::surface_intersection() (4.10)
static
void surface_intersection(PolygonMesh& pm1,
                          PolygonMesh& pm2,
                          PolygonMeshMultiPolylineJNI multi_polylines,
                          bool throw_on_self_intersection = false)
{
  Vector_of_points_putter<PolygonMeshMultiPolylineJNI> putter(multi_polylines);
  PMP::surface_intersection(pm1, pm2,
                            boost::make_function_output_iterator(putter),
                            throw_on_self_intersection);
}

// CGAL::Polygon_mesh_processing::does_bound_a_volume() (4.10)
  static
  bool does_bound_a_volume(PolygonMesh& pm)
  {
    return PMP::does_bound_a_volume(pm);
  }


//
// Geometric Measure functions
//   CGAL::Polygon_mesh_processing::face_area()
  static
  double face_area(int fd,
                   PolygonMesh& pm)
  {
    return PMP::face_area(FD(fd), pm);
  }
//   CGAL::Polygon_mesh_processing::area() (4.8)
  static
  double area(RangeIndexJNI face_range,
              PolygonMesh& pm)
  {
    if (face_range.indices==NULL)
      return PMP::area(pm);
    else
      return PMP::area(make_range(face_range), pm);
  }
  static
  double area(PolygonMesh& pm)
  {
    return PMP::area(pm);
  }
//   CGAL::Polygon_mesh_processing::volume() (4.8)
  static
  double volume(PolygonMesh& pm)
  {
    return PMP::volume(pm);
  }
//   CGAL::Polygon_mesh_processing::edge_length() (4.8)
  static
  double edge_length(int hd,
                     PolygonMesh& pm)
  {
    return PMP::edge_length(HD(hd), pm);
  }
//   CGAL::Polygon_mesh_processing::face_border_length() (4.8)
  static
  double face_border_length(int hd,
                            PolygonMesh& pm)
  {
    return PMP::face_border_length(HD(hd), pm);
  }
//
// Distance Functions
//

//CGAL::Polygon_mesh_processing::approximate_Hausdorff_distance()
  static
  double approximate_Hausdorff_distance(PolygonMesh& pm1, PolygonMesh& pm2)
  {
    return PMP::approximate_Hausdorff_distance<CGAL::Sequential_tag>(pm1, pm2);
  }
//CGAL::Polygon_mesh_processing::approximate_symmetric_Hausdorff_distance()
  static
  double approximate_symmetric_Hausdorff_distance(PolygonMesh& pm1, PolygonMesh& pm2)
  {
    return PMP::approximate_symmetric_Hausdorff_distance<CGAL::Sequential_tag>(pm1, pm2);
  }
//CGAL::Polygon_mesh_processing::approximate_max_distance_to_point_set()
  static
  double approximate_max_distance_to_point_set(PolygonMesh& pm,
    boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points,
    double precision)
  {
    return PMP::approximate_max_distance_to_point_set(pm, *points, precision);
  }

  static
  double approximate_max_distance_to_point_set(PolygonMesh& pm,
                                               PointSet& ps,
                                               double precision)
  {
    return PMP::approximate_max_distance_to_point_set(pm, ps.points<EPIC_Kernel::Point_3>(), precision);
  }
//CGAL::Polygon_mesh_processing::max_distance_to_triangle_mesh()
  static
  double max_distance_to_triangle_mesh(boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points,
    PolygonMesh& pm)
  {
    return PMP::max_distance_to_triangle_mesh<CGAL::Sequential_tag>(*points, pm);
  }
  static
  double max_distance_to_triangle_mesh(PointSet& ps,
                                       PolygonMesh& pm)
  {
    return PMP::max_distance_to_triangle_mesh<CGAL::Sequential_tag>(
      ps.points<EPIC_Kernel::Point_3>(), pm);
  }
//CGAL::Polygon_mesh_processing::sample_triangle_mesh()
  static
  void sample_triangle_mesh(PolygonMesh& pm,
                            PointSet& ps)
  {
    PMP::sample_triangle_mesh(pm, ps.inserter());
  }

//
// Miscellaneous
//   CGAL::Polygon_mesh_processing::bbox() (4.8)
  // static
  // Bbox_3 bbox(PolygonMesh& pm)
  // {
  //   return Bbox_3( PMP::bbox(pm));
  // }

//   CGAL::Polygon_mesh_processing::vertex_bbox() (4.8)
  // static
  // Bbox_3 vertex_bbox(PolygonMesh& pm)
  // {
  //   return Bbox_3( PMP::vertex_bbox(pm));
  // }

//   CGAL::Polygon_mesh_processing::edge_bbox() (4.8)
  // static
  // Bbox_3 edge_bbox(PolygonMesh& pm)
  // {
  //   return Bbox_3( PMP::edge_bbox(pm));
  // }

//   CGAL::Polygon_mesh_processing::face_bbox() (4.8)
  // static
  // Bbox_3 face_bbox(PolygonMesh& pm)
  // {
  //   return Bbox_3( PMP::face_bbox(pm));
  // }

//   CGAL::Polygon_mesh_processing::border_halfedges() (4.8)
  static
  void border_halfedges(RangeIndexJNI face_range,
                        PolygonMesh& pm,
                        WritableRangeIndexJNI halfedge_output)
  {
    if (face_range.indices==NULL)
      PMP::border_halfedges(faces(pm), pm, std::back_inserter(halfedge_output));
    else
      PMP::border_halfedges(make_range(face_range), pm, std::back_inserter(halfedge_output));
  }

// Polygon_mesh_slicer
  static
  void polygon_mesh_slicer( PolygonMesh& pm,
                            boost::shared_ptr< std::vector<EPIC_Kernel::Plane_3> > planes,
                            PolygonMeshMultiPolylineJNI multi_polylines)
  {
    CGAL::Polygon_mesh_slicer<PolygonMesh, EPIC_Kernel> slicer(pm);
    std::size_t nb_planes = planes->size();
    Vector_of_points_putter<PolygonMeshMultiPolylineJNI> putter(multi_polylines);

    for (std::size_t i=0; i<nb_planes; ++i)
      slicer((*planes)[i], boost::make_function_output_iterator(putter));
  }

// Side_of_triangle_mesh
  static
  boost::shared_ptr< std::vector<int> >
  side_of_triangle_mesh( PolygonMesh& pm,
                         boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points )
  {
    CGAL::Side_of_triangle_mesh<PolygonMesh, EPIC_Kernel> side(pm);
    std::size_t nb_pts=points->size();
    boost::shared_ptr< std::vector<int> > res(new std::vector<int>(nb_pts));
    for(std::size_t i=0;i<nb_pts; ++i)
      res->operator[](i)=(int) side(points->operator[](i));
    return res;
  }

  static
  void
  side_of_triangle_mesh( PolygonMesh& pm,
                         std::pair<double*, int> points_and_size,
                         int* out)
  {
    CGAL::Side_of_triangle_mesh<PolygonMesh, EPIC_Kernel> side(pm);
    int nb_pts=points_and_size.second/3;

    for(int i=0;i<nb_pts; ++i)
      out[i]=(int) side(EPIC_Kernel::Point_3(
                          points_and_size.first[3*i],
                          points_and_size.first[3*i+1],
                          points_and_size.first[3*i+2]) );
  }

  static
  void
  side_of_triangle_mesh( PolygonMesh& pm,
                         PointSet& ps,
                         PolygonMeshIntPropertyJNI& point_int_map)
  {
    CGAL::Side_of_triangle_mesh<PolygonMesh, EPIC_Kernel> side(pm);
    int nb_pts=ps.size();

    for(int i=0;i<nb_pts; ++i)
      point_int_map.values[ps.index(i)]=side(ps.point<EPIC_Kernel::Point_3>(i));
  }
};

#endif // SWIG_CGAL_POLYGON_MESH_PMP_H
