from CGAL import CGAL_Kernel
from CGAL import CGAL_Triangulation_3
t=CGAL_Triangulation_3 .Delaunay_triangulation_3()
l=[]
l.append(CGAL_Kernel.Point_3(1,1,1))
l.append(CGAL_Kernel.Point_3(2,2,2))
l.append(CGAL_Kernel.Point_3(441,41,84))
l.append(CGAL_Kernel.Point_3(1,1,8))
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
  t.adjacent_vertices(p,all_adjacent_vertices)
  v=p
  print p.point()

print "length of all_adjacent_vertices ",len(all_adjacent_vertices)
#~ try:
  #~ t.adjacent_vertices(v,3)  
#~ except:
  #~ print "Not a list"

#~ #test for memory leak: infinite loop
#~ while 1:
  #~ t.adjacent_vertices(v,all_adjacent_vertices)
  #~ rr=all_adjacent_vertices.pop()

