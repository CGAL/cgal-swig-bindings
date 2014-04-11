from __future__ import print_function
from sys import exit

from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Point_set_processing_3 import *

import os
datadir = os.environ.get('DATADIR', '../data')
datafile = datadir+'/oni.xyz'

#Reads a .xyz point set file in points[].
points=[];

if not read_xyz_points(datafile, points):
  print("Error: cannot read file data/oni.xyz")
  exit()

#Removes outliers using erase-remove idiom.
removed_percentage = 5.0; # percentage of points to remove
nb_neighbors = 24; # considers 24 nearest neighbor points
new_size=remove_outliers(points, nb_neighbors, removed_percentage)
points=points[0:new_size]
