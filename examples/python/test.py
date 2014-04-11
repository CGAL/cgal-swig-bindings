from __future__ import print_function
from CGAL import CGAL_Triangulation_3
from CGAL import CGAL_Kernel
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Triangle_2

t=CGAL_Triangulation_3 .Delaunay_triangulation_3()
l=[]
l.append(CGAL_Kernel.Point_3(1,1,1))
l.append(CGAL_Kernel.Point_3(2,2,2))
l.append(CGAL_Kernel.Point_3(441,41,84))
l.append(CGAL_Kernel.Point_3(1,1,8))
t.insert(l)
print("OK")
l.append(1)
try:
  t.insert(l)
except:
  print("list does not contains only points")
try:
  t.insert(3)
except:
  print("Not a list")

all_adjacent_vertices=[]
v=0
for p in t.finite_vertices():
  t.finite_adjacent_vertices(p,all_adjacent_vertices)
  v=p
  print(p.point())

print("length of all_adjacent_vertices ",len(all_adjacent_vertices))
try:
  t.adjacent_vertices(v,3)
except:
  print("Not a list")

t1=Triangle_2(Point_2(0,0),Point_2(1,0),Point_2(0,1))
t2=Triangle_2(Point_2(1,1),Point_2(1,0),Point_2(0,1))
object = CGAL_Kernel.intersection(t1,t2)
assert object.is_Segment_2()
print(object.get_Segment_2())

#test for memory leak: infinite loop
#mylist=[]
#while 1:
#  t.adjacent_vertices(v,mylist)
#  t.incident_edges(v,mylist)
#  t.incident_facets(v,mylist)
#  print(len(mylist))
#  mylist=[]
