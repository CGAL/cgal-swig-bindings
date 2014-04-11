from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Point_set_processing_3 import *


import os
datadir = os.environ.get('DATADIR', '../data')
datafile = datadir+'/oni.xyz'
points = []

print("Running read_xyz_points...")
read_xyz_points(datafile, points)
print(len(points), " points read")

print( "Average point spacing is ", compute_average_spacing(points,24))

print("Running jet_smooth_point_set...")
jet_smooth_point_set(points,24)

avg_space=compute_average_spacing(points,24)
print ("Average point spacing is ",  avg_space)

print("Running grid_simplify_point_set..." )
new_size=grid_simplify_point_set(points, avg_space/5)
points=points[0:new_size]
print( new_size, " points remaining")

print("Running random_simplify_point_set...")
new_size=random_simplify_point_set(points, 1)
points=points[0:new_size]
print( new_size, " points remaining")

print("Running remove_outliers...")
new_size=remove_outliers(points, 24, 1.5)
points=points[0:new_size]
print( new_size, " points remaining")

normals = []

print("Running jet_estimate_normals...")
jet_estimate_normals(points, normals, 24)
print(len(normals), " normal vectors set")

print("Running mst_orient_normals...")
new_size=mst_orient_normals(points, normals, 24)
points=points[0:new_size]
print(new_size, " points remaining")
print(len(normals), " normal vectors set")

normals=[]
print("Running pca_estimate_normals...")
pca_estimate_normals(points, normals, 24)
print(len(normals), " normal vectors set")

print("Running write_xyz_points_and_normals...")
write_xyz_points_and_normals("oni.xyz", points, normals)
normals=[]
points=[]

print("Running read_xyz_points_and_normals...")
read_xyz_points_and_normals(datafile, points, normals)
print(len(normals), " normal vectors read")
