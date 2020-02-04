from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Weighted_point_3
from CGAL.CGAL_Triangulation_3 import Regular_triangulation_3

triangulation = Regular_triangulation_3()
list_of_weighted_points = []
list_of_weighted_points.append(Weighted_point_3(Point_3(1, 1, 1), 34))
list_of_weighted_points.append(Weighted_point_3(Point_3(1, 56, 2), 334))
list_of_weighted_points.append(Weighted_point_3(Point_3(1, 3, 1), 3))
list_of_weighted_points.append(Weighted_point_3(Point_3(1, 1, 33), 4))
triangulation.insert(list_of_weighted_points)
print("OK")
list_of_weighted_points.append(1)
try:
    triangulation.insert(list_of_weighted_points)
except Exception:
    print("list does not contains only points")
try:
    triangulation.insert(3)
except Exception:
    print("Not a list")

all_adjacent_vertices = []
v = 0
for p in triangulation.finite_vertices():
    triangulation.finite_adjacent_vertices(p, all_adjacent_vertices)
    v = p
    print(p.point())

print("length of all_adjacent_vertices ", len(all_adjacent_vertices))
try:
    triangulation.adjacent_vertices(v, 3)
except Exception:
    print("Not a list")

# test for memory leak: infinite loop
mylist = []
i = 5000
while i != 0:
    triangulation.adjacent_vertices(v, mylist)
    triangulation.incident_edges(v, mylist)
    triangulation.incident_facets(v, mylist)
    print(i, end='')
    mylist = []
    i -= 1
print("done")
