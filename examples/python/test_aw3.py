from __future__ import print_function

from CGAL import CGAL_Alpha_wrap_3
from CGAL.CGAL_Alpha_wrap_3 import Point_3_Vector
from CGAL.CGAL_Alpha_wrap_3 import Polygon_Vector
from CGAL.CGAL_Alpha_wrap_3 import Int_Vector

from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Kernel import Point_3

import os

datadir = os.environ.get('DATADIR', '../data')

# test with a mesh as input
P = Polyhedron_3(datadir + '/elephant.off')
Q = Polyhedron_3()
CGAL_Alpha_wrap_3.alpha_wrap_3(P, 0.1, 0.01, Q)
Q.write_to_file("elephant_alpha_wrapped.off")

# test with a soup as input
points = Point_3_Vector()
points.reserve(3)
points.append(Point_3(0, 0, 0))
points.append(Point_3(0, 1, 0))
points.append(Point_3(1, 0, 0))
polygons = Polygon_Vector()
polygon = Int_Vector()
polygon.reserve(3)
polygon.append(0)
polygon.append(1)
polygon.append(2)
polygons.append(polygon)
CGAL_Alpha_wrap_3.alpha_wrap_3(points, polygons, 0.1, 0.01, Q)
Q.write_to_file("soup_wrapped.off")

# test with a point set as input
CGAL_Alpha_wrap_3.alpha_wrap_3(points, 0.1, 0.5, Q)
Q.write_to_file("points_wrapped.off")
