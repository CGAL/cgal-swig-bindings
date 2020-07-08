// ------------------------------------------------------------------------------
// Copyright (c) 2013 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_POINT_SET_PROCESSING_3_H
#define SWIG_CGAL_POINT_SET_PROCESSING_3_H

#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Point_set_3/Point_set_3.h>

#include <CGAL/bilateral_smooth_point_set.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/edge_aware_upsample_point_set.h>
#include <CGAL/estimate_scale.h>
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

#ifdef CGAL_LINKED_WITH_TBB
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif

void bilateral_smooth_point_set (Point_set_3_wrapper<CGAL_PS3> point_set, int k,
                                 double neighbor_radius = 0.,
                                 double sharpness_angle = 30.)
{
  CGAL::bilateral_smooth_point_set<Concurrency_tag>
    (point_set.get_data(), k,
     point_set.get_data().parameters().neighbor_radius(neighbor_radius).
     sharpness_angle(sharpness_angle));
}

double compute_average_spacing(Point_set_3_wrapper<CGAL_PS3> point_set, int k)
{
  return CGAL::compute_average_spacing<Concurrency_tag> (point_set.get_data(), k);
}

void edge_aware_upsample_point_set (Point_set_3_wrapper<CGAL_PS3> point_set,
                                    double sharpness_angle = 30.,
                                    double edge_sensitivity = 1.,
                                    double neighbor_radius = -1.,
                                    int number_of_output_points = 1000)
{
  CGAL::edge_aware_upsample_point_set<Concurrency_tag>
    (point_set.get_data(),
     boost::make_function_output_iterator
     ([&](const std::pair<EPIC_Kernel::Point_3, EPIC_Kernel::Vector_3>& p)
      {
        point_set.get_data().insert (p.first, p.second);
      }),
     point_set.get_data().parameters().sharpness_angle(sharpness_angle).
     edge_sensitivity(edge_sensitivity).
     neighbor_radius(neighbor_radius).
     number_of_output_points(number_of_output_points));
}

int estimate_global_k_neighbor_scale (Point_set_3_wrapper<CGAL_PS3> point_set)
{
  return CGAL::estimate_global_k_neighbor_scale (point_set.get_data());
}

double estimate_global_range_scale (Point_set_3_wrapper<CGAL_PS3> point_set)
{
  return CGAL::estimate_global_range_scale (point_set.get_data(), point_set.get_data().parameters());
}

// TODO if needed: estimate local scales

void grid_simplify_point_set (Point_set_3_wrapper<CGAL_PS3> point_set, double epsilon)
{
  point_set.get_data().remove_from
    (CGAL::grid_simplify_point_set (point_set.get_data(), epsilon));
}

void hierarchy_simplify_point_set (Point_set_3_wrapper<CGAL_PS3> point_set,
                                   int size = 10,
                                   double maximum_variation = 1./3.)
{
  point_set.get_data().remove_from
    (CGAL::hierarchy_simplify_point_set (point_set.get_data(),
                                         point_set.get_data().parameters().size(size).
                                         maximum_variation(maximum_variation)));
}

void jet_estimate_normals (Point_set_3_wrapper<CGAL_PS3> point_set, int k,
                           double neighbor_radius = 0.,
                           int degree_fitting = 2)
{
  point_set.get_data().add_normal_map();
  CGAL::jet_estimate_normals<Concurrency_tag>
    (point_set.get_data(), k,
     point_set.get_data().parameters().neighbor_radius (neighbor_radius).
     degree_fitting (degree_fitting));
}

void jet_smooth_point_set (Point_set_3_wrapper<CGAL_PS3> point_set, int k,
                           double neighbor_radius = 0.,
                           int degree_fitting = 2,
                           int degree_monge = 2)
{
  CGAL::jet_smooth_point_set<Concurrency_tag>
    (point_set.get_data(), k,
     point_set.get_data().parameters().neighbor_radius(neighbor_radius).
     degree_fitting(degree_fitting).
     degree_monge(degree_monge));
}

void mst_orient_normals (Point_set_3_wrapper<CGAL_PS3> point_set, int k,
                         double neighbor_radius = 0.,
                         typename Point_set_3_wrapper<CGAL_PS3>::Int_map
                         constrained_map = typename Point_set_3_wrapper<CGAL_PS3>::Int_map())
{
  if (constrained_map.is_valid())
    point_set.get_data().remove_from
      (CGAL::mst_orient_normals
       (point_set.get_data(), k,
        point_set.get_data().parameters().neighbor_radius (neighbor_radius).
        point_is_constrained_map(constrained_map.get_data())));
  else
    point_set.get_data().remove_from
      (CGAL::mst_orient_normals
       (point_set.get_data(), k,
        point_set.get_data().parameters().neighbor_radius (neighbor_radius)));
}

void pca_estimate_normals (Point_set_3_wrapper<CGAL_PS3> point_set, int k,
                           double neighbor_radius = 0.)
{
  point_set.get_data().add_normal_map();
  CGAL::pca_estimate_normals<Concurrency_tag>
    (point_set.get_data(), k, point_set.get_data().parameters().neighbor_radius(neighbor_radius));
}

void random_simplify_point_set (Point_set_3_wrapper<CGAL_PS3> point_set, double removed_percentage)
{
  point_set.get_data().remove_from
    (CGAL::random_simplify_point_set (point_set.get_data(), removed_percentage));
}

void remove_outliers (Point_set_3_wrapper<CGAL_PS3> point_set, int k,
                      double neighbor_radius = 0.,
                      double threshold_percent = 10.,
                      double threshold_distance = 0.)
{
  point_set.get_data().remove_from(
#if  ! defined SWIG && (CGAL_VERSION_MAJOR < 5  || (CGAL_VERSION_MAJOR ==5 && CGAL_VERSION_MINOR <1))
      CGAL::remove_outliers
#else
      CGAL::remove_outliers<Concurrency_tag>
#endif
     (point_set.get_data(), k,
                            point_set.get_data().parameters().neighbor_radius(neighbor_radius).
                            threshold_percent(threshold_percent).
                            threshold_distance(threshold_distance)));
}

// TODO: structure_point_set() if/once Shape_detection is wrapped

void vcm_estimate_normals (Point_set_3_wrapper<CGAL_PS3> point_set,
                           double offset_radius, double convolution_radius, int k = 0)
{
  point_set.get_data().add_normal_map();
  if (k == 0)
    CGAL::vcm_estimate_normals (point_set.get_data(), offset_radius, convolution_radius);
  else
    CGAL::vcm_estimate_normals (point_set.get_data(), offset_radius, (unsigned int)k);
}

void wlop_simplify_and_regularize_point_set (Point_set_3_wrapper<CGAL_PS3> input,
                                             Point_set_3_wrapper<CGAL_PS3> output,
                                             double select_percentage = 5.,
                                             double neighbor_radius = -1.,
                                             int number_of_iterations = 35,
                                             bool require_uniform_sampling = false)
{
  CGAL::wlop_simplify_and_regularize_point_set<Concurrency_tag>
    (input.get_data(),
     output.get_data().point_back_inserter(),
     input.get_data().parameters().select_percentage(select_percentage).
     neighbor_radius(neighbor_radius).
     number_of_iterations(number_of_iterations).
     require_uniform_sampling(require_uniform_sampling));
}


#endif //SWIG_CGAL_POINT_SET_PROCESSING_3_H
