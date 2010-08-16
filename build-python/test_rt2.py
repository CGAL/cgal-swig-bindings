from CGAL import CGAL_Kernel
from CGAL import CGAL_Triangulation_3

t=CGAL_Triangulation_3 .Regular_triangulation_3()
l=[]
l.append(CGAL_Kernel.Weighted_point_3(CGAL_Kernel.Point_3(1,1,1),34))
l.append(CGAL_Kernel.Weighted_point_3(CGAL_Kernel.Point_3(1,56,2),334))
l.append(CGAL_Kernel.Weighted_point_3(CGAL_Kernel.Point_3(1,3,1),3))
l.append(CGAL_Kernel.Weighted_point_3(CGAL_Kernel.Point_3(1,1,33),4))
t.insert_range(l)
print "OK"
l.append(1)
try:
  t.insert_range(l)
except:
  print "list does not contains only points"
try:
  t.insert_range(3)
except:
  print "Not a list"

all_adjacent_vertices=[]
v=0
for p in t.finite_vertices():
  t.finite_adjacent_vertices(p,all_adjacent_vertices)
  v=p
  print p.point()

print "length of all_adjacent_vertices ",len(all_adjacent_vertices)
try:
  t.adjacent_vertices(v,3)  
except:
  print "Not a list"

#test for memory leak: infinite loop
mylist=[]
while 1:
  t.adjacent_vertices(v,mylist)
  t.incident_edges(v,mylist)
  t.incident_facets(v,mylist)
  print len(mylist)
  mylist=[]

