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

#ifndef SWIG_CGAL_POLYGON_MESH_PSP_H
#define SWIG_CGAL_POLYGON_MESH_PSP_H

#include <CGAL/bilateral_smooth_point_set.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/edge_aware_upsample_point_set.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/hierarchy_simplify_point_set.h>
#include <CGAL/jet_estimate_normals.h>
#include <CGAL/jet_smooth_point_set.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/pca_estimate_normals.h>
#include <CGAL/random_simplify_point_set.h>
#include <CGAL/remove_outliers.h>
#include <CGAL/vcm_estimate_normals.h>
#include <CGAL/wlop_simplify_and_regularize_point_set.h>
#include <CGAL/estimate_scale.h>
#include <CGAL/Shape_detection_3.h>
#include <CGAL/structure_point_set.h>


#include "properties_PointSet.h"

struct Point_set_processing_3
{
  typedef EPIC_Kernel::Point_3 Point_3;
  typedef EPIC_Kernel::Vector_3 Vector_3;
  typedef PointSet_point_map<PointSet, Point_3> Point_map;
  typedef PointSet_property<PolygonMeshDoublePropertyJNI, Vector_3> Normal_map;

  static
  double bilateral_smooth_point_set(
    PointSet& ps,
    PolygonMeshDoublePropertyJNI& point_double_map,
    int k,
    double sharpness_angle)
  {
    #if CGAL_VERSION_NR > 1041200000
    return CGAL::bilateral_smooth_point_set<CGAL::Sequential_tag>
      (ps, k,
       CGAL::parameters::point_map(Point_map(ps)).
                         normal_map(Normal_map(point_double_map)).
                         sharpness_angle(sharpness_angle)
       );
    #else
    return CGAL::bilateral_smooth_point_set<CGAL::Sequential_tag>
      (ps.begin(), ps.end(),
       Point_map(ps), Normal_map(point_double_map),
       k, sharpness_angle);
    #endif
  }


  static
  double compute_average_spacing(PointSet& ps,
                                 int k)
  {
    #if CGAL_VERSION_NR > 1041200000
    return CGAL::compute_average_spacing<CGAL::Sequential_tag>
      (ps, k, CGAL::parameters::point_map(Point_map(ps)));
    #else
    return CGAL::compute_average_spacing<CGAL::Sequential_tag>
      (ps.begin(), ps.end(), Point_map(ps), k);
    #endif
  }

  static
  void edge_aware_upsample_point_set(
    PointSet& ps,
    PolygonMeshDoublePropertyJNI& point_double_map,
    double sharpness_angle = 30,
    double edge_sensitivity = 1,
    double neighbor_radius = 6,
    int number_of_output_points = 1000)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::edge_aware_upsample_point_set<CGAL::Sequential_tag>
      (ps, ps.inserter(Normal_map(point_double_map)),
       CGAL::parameters::point_map(Point_map(ps)).
                         normal_map(Normal_map(point_double_map)).
                         sharpness_angle(sharpness_angle).
                         edge_sensitivity(edge_sensitivity).
                         neighbor_radius(neighbor_radius).
                         number_of_output_points(number_of_output_points));
    #else
    CGAL::edge_aware_upsample_point_set<CGAL::Sequential_tag>
      (ps.begin(), ps.end(),
       ps.inserter(Normal_map(point_double_map)),
       Point_map(ps), Normal_map(point_double_map),
       sharpness_angle, edge_sensitivity, neighbor_radius, number_of_output_points);
    #endif
  }

  static
  void grid_simplify_point_set(PointSet& ps, double epsilon)
  {
    #if CGAL_VERSION_NR > 1041200000
    ps.resize(
      ps.distance(
        CGAL::grid_simplify_point_set(ps, epsilon,
                                      CGAL::parameters::point_map(Point_map(ps)))));
    #else
    ps.resize(
      ps.distance(
        CGAL::grid_simplify_point_set(ps.begin(), ps.end(), Point_map(ps), epsilon)));
    #endif
  }

  static
  void hierarchy_simplify_point_set(PointSet& ps, int size = 10, double var_max = 0.333)
  {
    #if CGAL_VERSION_NR > 1041200000
    ps.resize(
      ps.distance(
        CGAL::hierarchy_simplify_point_set(ps,
                                           CGAL::parameters::point_map(Point_map(ps)).
                                           size(size).
                                           maximum_variation(var_max))));
    #else
    ps.resize(
      ps.distance(
        CGAL::hierarchy_simplify_point_set(ps.begin(), ps.end(), Point_map(ps), size, var_max,
                                          CGAL::Default_diagonalize_traits<double, 3>())));
    #endif
  }

  static
  void jet_estimate_normals(PointSet& ps,
                            PolygonMeshDoublePropertyJNI& point_double_map,
                            int k,
                            int degree_fitting = 2)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::jet_estimate_normals<CGAL::Sequential_tag>
      (ps, k,
       CGAL::parameters::point_map(Point_map(ps)).
                         normal_map(Normal_map(point_double_map)).
                         degree_fitting(degree_fitting));
    #else
        CGAL::jet_estimate_normals<CGAL::Sequential_tag>
      (ps.begin(), ps.end(),
       Point_map(ps), Normal_map(point_double_map),
       k, EPIC_Kernel(), degree_fitting);
    #endif
  }

  static
  void jet_smooth_point_set(
    PointSet& ps, int k, int degree_fitting = 2, int degree_monge = 2)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::jet_smooth_point_set<CGAL::Sequential_tag>
      (ps, k,
       CGAL::parameters::point_map(Point_map(ps)).
                         degree_fitting(degree_fitting).
                         degree_monge(degree_monge));
    #else
    CGAL::jet_smooth_point_set<CGAL::Sequential_tag>
      (ps.begin(), ps.end(), Point_map(ps), k, EPIC_Kernel(), degree_fitting, degree_monge);
    #endif

  }

  static
  int mst_orient_normals(PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map, int k)
  {
    #if CGAL_VERSION_NR > 1041200000
    return ps.distance(CGAL::mst_orient_normals(ps, k,
                                                CGAL::parameters::point_map(Point_map(ps)).
                                                                  normal_map(Normal_map(point_double_map))));
    #else
    return ps.distance(CGAL::mst_orient_normals(ps.begin(), ps.end(),Point_map(ps), Normal_map(point_double_map), k));
    #endif
  }

  static
  void  pca_estimate_normals(PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map, int k)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::pca_estimate_normals<CGAL::Sequential_tag>(ps, k,
                                                     CGAL::parameters::point_map(Point_map(ps)).
                                                                       normal_map(Normal_map(point_double_map)));
    #else
    CGAL::pca_estimate_normals<CGAL::Sequential_tag>(ps.begin(), ps.end(), Point_map(ps), Normal_map(point_double_map), k);
    #endif
  }

  static
  void random_simplify_point_set(PointSet& ps, double removed_percentage)
  {
    #if CGAL_VERSION_NR > 1041200000
    ps.resize(
      ps.distance(
        CGAL::random_simplify_point_set(ps, removed_percentage)));
    #else
    ps.resize(
      ps.distance(
        CGAL::random_simplify_point_set(ps.begin(), ps.end(), Point_map(ps), removed_percentage)));
    #endif
  }

  static
  void remove_outliers(PointSet& ps, int k, double threshold_percent)
  {
    #if CGAL_VERSION_NR > 1041200000
    ps.resize(
      ps.distance(CGAL::remove_outliers(ps, k,
                                        CGAL::parameters::point_map(Point_map(ps)).
                                        threshold_percent(threshold_percent))));
    #else
    ps.resize(
      ps.distance(CGAL::remove_outliers(ps.begin(), ps.end(), Point_map(ps), k, threshold_percent)));
    #endif
  }

  static
  void vcm_estimate_normals(PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map, double offset_radius, double convolution_radius)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::vcm_estimate_normals(ps, offset_radius, convolution_radius,
                               CGAL::parameters::point_map(Point_map(ps)).
                                                 normal_map(Normal_map(point_double_map)));
    #else
    CGAL::vcm_estimate_normals(ps.begin(), ps.end(), Point_map(ps), Normal_map(point_double_map), offset_radius, convolution_radius);
    #endif
  }

  static
  void vcm_estimate_normals(PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map, double offset_radius, int nb_neighbors_convolve)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::vcm_estimate_normals(ps, offset_radius, static_cast<unsigned int>(nb_neighbors_convolve),
                               CGAL::parameters::point_map(Point_map(ps)).
                                                 normal_map(Normal_map(point_double_map)));
    #else
    CGAL::vcm_estimate_normals(ps.begin(), ps.end(), Point_map(ps), Normal_map(point_double_map), offset_radius, static_cast<unsigned int>(nb_neighbors_convolve));
    #endif
  }

  static
  void wlop_simplify_and_regularize_point_set(
    PointSet& input_ps,
    PointSet& output_ps,
    const double select_percentage = 5,
    double neighbor_radius = -1,
    const unsigned int max_iter_number = 35,
    const bool require_uniform_sampling = false)
  {
    #if CGAL_VERSION_NR > 1041200000
    CGAL::wlop_simplify_and_regularize_point_set<CGAL::Sequential_tag>
      (input_ps, output_ps.inserter(),
       CGAL::parameters::point_map(Point_map(input_ps)).
                         select_percentage(select_percentage).
                         neighbor_radius(neighbor_radius).
                         number_of_iterations(max_iter_number).
                         require_uniform_sampling(require_uniform_sampling));
    #else
    CGAL::wlop_simplify_and_regularize_point_set<CGAL::Sequential_tag>
      (input_ps.begin(), input_ps.end(),
       output_ps.inserter(),
       Point_map(input_ps),
       select_percentage,
       neighbor_radius,
       max_iter_number,
       require_uniform_sampling);
    #endif
  }

  static
  int estimate_global_k_neighbor_scale(PointSet& ps)
  {
    #if CGAL_VERSION_NR > 1041200000
    return static_cast<int>(
      CGAL::estimate_global_k_neighbor_scale(ps, CGAL::parameters::point_map(Point_map(ps))));
    #else
    return static_cast<int>(
      CGAL::estimate_global_k_neighbor_scale(ps.begin(), ps.end(), Point_map(ps)));
    #endif
  }

  static
  double estimate_global_range_scale(PointSet& ps)
  {
    #if CGAL_VERSION_NR > 1041200000
    return static_cast<int>(
      CGAL::estimate_global_range_scale(ps, CGAL::parameters::point_map(Point_map(ps))));
    #else
    return static_cast<int>(
      CGAL::estimate_global_range_scale(ps.begin(), ps.end(), Point_map(ps)));
    #endif
  }

  static
  void
  estimate_local_k_neighbor_scales(PointSet& input_ps, PointSet& ps, PolygonMeshIntPropertyJNI& point_int_map)
  {
    std::vector<int> res;
    res.reserve(ps.size());
    #if CGAL_VERSION_NR > 1041200000
    CGAL::estimate_local_k_neighbor_scales(input_ps, ps, std::back_inserter(res),
                                           CGAL::parameters::point_map(Point_map(input_ps)).
                                           query_point_map(Point_map(ps))
                                           );
    #else
    CGAL::estimate_local_k_neighbor_scales(input_ps.begin(), input_ps.end(), Point_map(input_ps),
                                           ps.begin(), ps.end(), Point_map(ps),
                                           std::back_inserter(res));
    #endif
    for (int i=0; i <ps.size(); ++i)
      point_int_map.values[ ps.index(i) ] = res[i];

  }

  static
  void
  estimate_local_range_scales(PointSet& input_ps, PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map)
  {
    std::vector<double> res;
    res.reserve(ps.size());
    #if CGAL_VERSION_NR > 1041200000
    CGAL::estimate_local_range_scales(input_ps, ps, std::back_inserter(res),
                                      CGAL::parameters::point_map(Point_map(input_ps)).
                                                        query_point_map(Point_map(ps))
                                      );
    #else
    CGAL::estimate_local_range_scales(input_ps.begin(), input_ps.end(), Point_map(input_ps),
                                      ps.begin(), ps.end(), Point_map(ps),
                                      std::back_inserter(res));
    #endif
    for (int i=0; i <ps.size(); ++i)
      point_double_map.values[ ps.index(i) ] = res[i];

  }

  static
  void structure_point_set(PointSet& ps, PolygonMeshDoublePropertyJNI& point_double_map, double epsilon, double attraction_factor=3)
  {
    // Efficient RANSAC types
    #if CGAL_VERSION_NR > 1041200000
    typedef CGAL::Shape_detection_3::Shape_detection_traits
      <EPIC_Kernel, PointSet, Point_map, Normal_map>           Traits;
    #else
    typedef CGAL::Shape_detection_3::Efficient_RANSAC_traits
      <EPIC_Kernel, PointSet, Point_map, Normal_map>           Traits;
    #endif
    typedef CGAL::Shape_detection_3::Efficient_RANSAC<Traits>    Efficient_ransac;
    typedef CGAL::Shape_detection_3::Plane<Traits>               Plane;

    Efficient_ransac ransac;
    ransac.set_input(ps, Point_map(ps), Normal_map(point_double_map));
    ransac.add_shape_factory<Plane>();
    ransac.detect();

    #if CGAL_VERSION_NR > 1041200000
    CGAL::structure_point_set(ps.begin(), ps.end(),
                              Point_map(ps), Normal_map(point_double_map),
                              ps.inserter(Normal_map(point_double_map)),
                              ransac,
                              epsilon, attraction_factor);
    #else
    CGAL::structure_point_set(ps.begin(), ps.end(),
                              Point_map(ps), Normal_map(point_double_map),
                              ps.inserter(Normal_map(point_double_map)),
                              ransac,
                              epsilon, attraction_factor);
    #endif
  }

  // Not wrapped as would require a covarience matrix per point.
  // CGAL::compute_vcm()
  // CGAL::vcm_is_on_feature_edge()
};

#endif