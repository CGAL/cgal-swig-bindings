from __future__ import print_function
from CGAL import CGAL_Triangulation_3
from CGAL import CGAL_Kernel
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Triangle_2
from CGAL.CGAL_Kernel import COLLINEAR
from CGAL.CGAL_Kernel import POSITIVE

triangulation = CGAL_Triangulation_3 .Delaunay_triangulation_3()
list_of_weighted_points = []
list_of_weighted_points.append(CGAL_Kernel.Point_3(1, 1, 1))
list_of_weighted_points.append(CGAL_Kernel.Point_3(2, 2, 2))
list_of_weighted_points.append(CGAL_Kernel.Point_3(441, 41, 84))
list_of_weighted_points.append(CGAL_Kernel.Point_3(1, 1, 8))
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

t1 = Triangle_2(Point_2(0, 0), Point_2(1, 0), Point_2(0, 1))
t2 = Triangle_2(Point_2(1, 1), Point_2(1, 0), Point_2(0, 1))
object = CGAL_Kernel.intersection(t1, t2)
assert object.is_Segment_2()
print(object.get_Segment_2())

# test for memory leak: infinite loop
# mylist=[]
# while 1:
#  triangulation.adjacent_vertices(v,mylist)
#  triangulation.incident_edges(v,mylist)
#  triangulation.incident_facets(v,mylist)
#  print(len(mylist))
#  mylist=[]

p1 = CGAL_Kernel.Point_3(0, 0, 0)
p2 = CGAL_Kernel.Point_3(1, 0, 0)
p3 = CGAL_Kernel.Point_3(1, 1, 0)
p4 = CGAL_Kernel.Point_3(0, 1, 0)
p4b = CGAL_Kernel.Point_3(0, 1, 1)

o1 = CGAL_Kernel.orientation(p1, p2, p3, p4)
o2 = CGAL_Kernel.orientation(p1, p2, p3, p4b)

assert(COLLINEAR == o1)
assert(POSITIVE == o2)
