from __future__ import print_function
from sys import exit
from sys import stderr

from CGAL import CGAL_Advancing_front_surface_reconstruction
from CGAL import CGAL_Point_set_processing_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Kernel import Point_3


points = []
if not CGAL_Point_set_processing_3.read_xyz_points("../data/oni.xyz", points):
  stderr.write("Error: cannot read file ../data/oni.xyz\n")
  exit()

P = Polyhedron_3()

CGAL_Advancing_front_surface_reconstruction.advancing_front_surface_reconstruction(points, P);

P.write_to_file("oni.off");

