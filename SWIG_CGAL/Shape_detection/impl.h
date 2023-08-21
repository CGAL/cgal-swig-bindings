// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_SHAPE_DETECTION_H
#define SWIG_CGAL_SHAPE_DETECTION_H

#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Point_set_3/Point_set_3.h>

#include <CGAL/Shape_detection/Efficient_RANSAC.h>
#include <CGAL/Shape_detection/Region_growing/Region_growing.h>
#if CGAL_VERSION_NR >= 1050600900
#include <CGAL/Shape_detection/Region_growing/Point_set.h>
#else
#include <CGAL/Shape_detection/Region_growing/Region_growing_on_point_set.h>
#endif

#include <boost/iterator/function_output_iterator.hpp>

#ifndef SWIG
template <typename NeighborQuery>
int
region_growing_impl (Point_set_3_wrapper<CGAL_PS3> point_set,
                     typename Point_set_3_wrapper<CGAL_PS3>::Int_map plane_map,
                     int min_points,
                     double epsilon,
                     double normal_treshold,
                     NeighborQuery& neighbor_query)
{
#if CGAL_VERSION_NR >= 1050600900
  typedef CGAL::Shape_detection::Point_set::Least_squares_plane_fit_region_for_point_set<CGAL_PS3> Region_type;
  typedef CGAL::Shape_detection::Region_growing<NeighborQuery, Region_type> Region_growing;

  // Init map for unassigned points to be -1
  for (int& idx : plane_map.get_data())
    idx = -1;

  double angle = 180 * std::acos(normal_treshold) / CGAL_PI;
  Region_type region_type =
    CGAL::Shape_detection::Point_set::make_least_squares_plane_fit_region(
                           point_set.get_data(),
                           CGAL::parameters::maximum_distance(epsilon).
                           maximum_angle(angle).
                           minimum_region_size(min_points));
  Region_growing region_growing (point_set.get_data(), neighbor_query, region_type);

  int plane_idx = 0;
  region_growing.detect
    (boost::make_function_output_iterator
     ([&](const std::pair<typename Region_type::Primitive,std::vector<typename Region_type::Item>>& primitive_and_region)
      {
        for (std::size_t idx : primitive_and_region.second)
          plane_map.set(*(point_set.get_data().begin() + idx), plane_idx);
        ++ plane_idx;
      }));

  return plane_idx;
#else
  typedef CGAL::Shape_detection::Point_set::Least_squares_plane_fit_region
    <EPIC_Kernel, CGAL_PS3, CGAL_PS3::Point_map, CGAL_PS3::Vector_map>
    Region_type;
  typedef CGAL::Shape_detection::Region_growing
    <CGAL_PS3, NeighborQuery, Region_type>
    Region_growing;

  // Init map for unassigned points to be -1
  for (int& idx : plane_map.get_data())
    idx = -1;

  double angle = 180 * std::acos(normal_treshold) / CGAL_PI;
  Region_type region_type (point_set.get_data(), epsilon, angle, min_points,
                           point_set.get_data().point_map(), point_set.get_data().normal_map());
  Region_growing region_growing (point_set.get_data(), neighbor_query, region_type);

  int plane_idx = 0;
  region_growing.detect
    (boost::make_function_output_iterator
     ([&](const std::vector<std::size_t>& region)
      {
        for (std::size_t idx : region)
          plane_map.set(*(point_set.get_data().begin() + idx), plane_idx);
        ++ plane_idx;
      }));

  return plane_idx;
#endif
}
#endif

int
region_growing (Point_set_3_wrapper<CGAL_PS3> point_set,
                typename Point_set_3_wrapper<CGAL_PS3>::Int_map plane_map,
                int min_points = 1,
                double epsilon = -1,
                double cluster_epsilon = -1,
                double normal_treshold = 0.9,
                int k = 0)
{
  if (epsilon == -1 && cluster_epsilon == -1)
  {
    CGAL::Bbox_3 bbox = CGAL::bbox_3 (point_set.get_data().points().begin(),
                                      point_set.get_data().points().end());
    double bbox_diagonal =
      CGAL::sqrt((bbox.xmax() - bbox.xmin()) * (bbox.xmax() - bbox.xmin())
                 + (bbox.ymax() - bbox.ymin()) * (bbox.ymax() - bbox.ymin())
                 + (bbox.zmax() - bbox.zmin()) * (bbox.zmax() - bbox.zmin()));

    if (epsilon == -1)
      epsilon = 0.01 * bbox_diagonal;
    if (cluster_epsilon == -1)
      cluster_epsilon = 0.01 * bbox_diagonal;
  }
#if CGAL_VERSION_NR >= 1050600900
  if (k == 0)
  {
   typedef CGAL::Shape_detection::Point_set::Sphere_neighbor_query_for_point_set<CGAL_PS3> Neighbor_query;

    Neighbor_query neighbor_query =
      CGAL::Shape_detection::Point_set::make_sphere_neighbor_query(
        point_set.get_data(), CGAL::parameters::sphere_radius(cluster_epsilon));
    return region_growing_impl (point_set, plane_map, min_points, epsilon, normal_treshold, neighbor_query);
  }
  else
  {
    typedef CGAL::Shape_detection::Point_set::K_neighbor_query_for_point_set<CGAL_PS3> Neighbor_query;

    Neighbor_query neighbor_query =
      CGAL::Shape_detection::Point_set::make_k_neighbor_query(
        point_set.get_data(), CGAL::parameters::k_neighbors(k));
    return region_growing_impl (point_set, plane_map, min_points, epsilon, normal_treshold, neighbor_query);
  }
#else
  if (k == 0)
  {
   typedef CGAL::Shape_detection::Point_set::Sphere_neighbor_query
      <EPIC_Kernel, CGAL_PS3, CGAL_PS3::Point_map>
      Neighbor_query;

    Neighbor_query neighbor_query (point_set.get_data(), cluster_epsilon, point_set.get_data().point_map());
    return region_growing_impl (point_set, plane_map, min_points, epsilon, normal_treshold, neighbor_query);
  }
  else
  {
    typedef CGAL::Shape_detection::Point_set::K_neighbor_query
      <EPIC_Kernel, CGAL_PS3, CGAL_PS3::Point_map>
      Neighbor_query;

    Neighbor_query neighbor_query (point_set.get_data(), k, point_set.get_data().point_map());
    return region_growing_impl (point_set, plane_map, min_points, epsilon, normal_treshold, neighbor_query);
  }

#endif

  return 0;
}


boost::shared_ptr<std::vector<std::string> >
efficient_RANSAC (Point_set_3_wrapper<CGAL_PS3> point_set,
                  typename Point_set_3_wrapper<CGAL_PS3>::Int_map shape_map,
                  int min_points = 1,
                  double epsilon = -1,
                  double cluster_epsilon = -1,
                  double normal_threshold = 0.9,
                  double probability = 0.01,
                  bool planes = true,
                  bool cones = false,
                  bool cylinders = false,
                  bool spheres = false,
                  bool tori = false)
{
  typedef CGAL::Shape_detection::Efficient_RANSAC_traits
    <EPIC_Kernel, CGAL_PS3, CGAL_PS3::Point_map, CGAL_PS3::Vector_map> Traits;
  typedef CGAL::Shape_detection::Efficient_RANSAC<Traits> Efficient_ransac;

  Efficient_ransac ransac;
  ransac.set_input (point_set.get_data(),
                    point_set.get_data().point_map(),
                    point_set.get_data().normal_map());

  if (planes)
    ransac.add_shape_factory<CGAL::Shape_detection::Plane<Traits> >();
  if (cones)
    ransac.add_shape_factory<CGAL::Shape_detection::Cone<Traits> >();
  if (cylinders)
    ransac.add_shape_factory<CGAL::Shape_detection::Cylinder<Traits> >();
  if (spheres)
    ransac.add_shape_factory<CGAL::Shape_detection::Sphere<Traits> >();
  if (tori)
    ransac.add_shape_factory<CGAL::Shape_detection::Torus<Traits> >();

  // Detection
  Efficient_ransac::Parameters parameters;
  parameters.probability = probability;
  parameters.min_points = min_points;
  parameters.epsilon = epsilon;
  parameters.cluster_epsilon = cluster_epsilon;
  parameters.normal_threshold = normal_threshold;
  ransac.detect (parameters);

  // Init map for unassigned points to be -1
  for (int& idx : shape_map.get_data())
    idx = -1;

  // Fill shape map
  boost::shared_ptr<std::vector<std::string> > output
    (new std::vector<std::string>());


  for (auto shape : ransac.shapes())
  {
    for (std::size_t idx : shape->indices_of_assigned_points())
      shape_map.set(*(point_set.get_data().begin() + idx), int(output->size()));
    output->push_back (shape->info());
  }

  return output;
}


#endif // SWIG_CGAL_SHAPE_DETECTION_H
