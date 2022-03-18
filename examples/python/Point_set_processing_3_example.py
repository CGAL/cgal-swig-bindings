from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Point_set_3 import Point_set_3
from CGAL.CGAL_Point_set_processing_3 import *

import os

datadir = os.environ.get('DATADIR', '../data')
datafile = datadir + '/oni.xyz'

print("Running read_xyz_points...")
points = Point_set_3(datafile)
print(points.size(), "points read")

k = estimate_global_k_neighbor_scale(points)
print("K-neighbor scale is", k)

avg_space = compute_average_spacing(points, k)
print("Average point spacing is", avg_space)

print("Running bilateral_smooth_point_set...")
bilateral_smooth_point_set(points, 3 * k)

scale = estimate_global_range_scale(points)
print("Range scale is", scale)

print("Running jet_smooth_point_set...")
jet_smooth_point_set(points, 3 * k, neighbor_radius=scale * 2)

print("Running edge_aware_upsample_point_set...")
edge_aware_upsample_point_set(points, number_of_output_points=2000)
print(points.size(), "points after upsampling")

avg_space = compute_average_spacing(points, k)
print("Average point spacing is", avg_space)

print("Running wlop_simplify_and_regularize_point_set...")
wlop_point_set = Point_set_3()
wlop_simplify_and_regularize_point_set(
    points,  # input
    wlop_point_set)  # Output
print("Output of WLOP has", points.size(), "points")

print("Running grid_simplify_point_set...")
grid_simplify_point_set(points, avg_space / 5)
print(points.size(), "point(s) remaining,", points.garbage_size(),
      "point(s) removed")
points.collect_garbage()

print("Running hierarchy_simplify_point_set...")
hierarchy_simplify_point_set(points)
print(points.size(), "point(s) remaining,", points.garbage_size(),
      "point(s) removed")

print("Cancelling removals")
points.cancel_removals()
print(points.size(), "point(s) remaining,", points.garbage_size(),
      "point(s) removed")

print("Running random_simplify_point_set...")
random_simplify_point_set(points, 1)
print(points.size(), "point(s) remaining,", points.garbage_size(),
      "point(s) removed")
points.collect_garbage()

print("Running remove_outliers...")
remove_outliers(points, 24, threshold_percent=1.5)
print(points.size(), "point(s) remaining,", points.garbage_size(),
      "point(s) removed")
points.collect_garbage()

points.add_normal_map()

print("Running jet_estimate_normals...")
jet_estimate_normals(points, 24)

print("Running mst_orient_normals...")
mst_orient_normals(points, 24)

print("Running pca_estimate_normals...")
pca_estimate_normals(points, 24)

print("Writing to ply")
points.write("oni.ply")
