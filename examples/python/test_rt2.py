from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Weighted_point_3
from CGAL.CGAL_Triangulation_3 import Regular_triangulation_3

t=Regular_triangulation_3()
l=[]
l.append(Weighted_point_3(Point_3(1,1,1),34))
l.append(Weighted_point_3(Point_3(1,56,2),334))
l.append(Weighted_point_3(Point_3(1,3,1),3))
l.append(Weighted_point_3(Point_3(1,1,33),4))
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

#test for memory leak: infinite loop
mylist=[]
i=5000
while i!=0:
  t.adjacent_vertices(v,mylist)
  t.incident_edges(v,mylist)
  t.incident_facets(v,mylist)
  print(i,end='')
  mylist=[]
  i-=1
print("done")
