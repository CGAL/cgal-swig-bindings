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

for p in t.finite_vertices():
  print p.point()

print "length of l ",len(l)
t.test_outputit(l)
print len(l)

for e in l:
  print e

print "END"
try:
  t.test_outputit(3)
except:
  print "Not a list"

#test for memory leak: infinite loop
while 1:
  t.test_outputit(l)
  rr=l.pop()

