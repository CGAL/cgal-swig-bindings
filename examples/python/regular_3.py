from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Weighted_point_3
from CGAL.CGAL_Triangulation_3 import Regular_triangulation_3

# generate points on a 3D grid
P=[]

number_of_points = 0

for z in range(0,5):
  for y in range(0,5):
    for x in range(0,5):
        p = Point_3(x, y, z)
        w = (x+y-z*y*x)*2.0 # let's say this is the weight.
        P.append(Weighted_point_3(p, w))
        number_of_points+=1

T = Regular_triangulation_3()

# insert all points in a row (this is faster than one insert() at a time).
T.insert (P)

assert T.is_valid()
assert T.dimension() == 3

print("Number of vertices : ", T.number_of_vertices())

#removal of all vertices
count = 0
while T.number_of_vertices() > 0:
  T.remove (T.finite_vertices().next())
  count+=1


assert count == number_of_points
