from CGAL import CGAL_Kernel
from CGAL import CGAL_Triangulation_2
t=CGAL_Triangulation_2.Triangulation_2()
v1=t.insert(CGAL_Kernel.Point_2(1,2))
v2=t.insert(CGAL_Kernel.Point_2(3,2))
v3=t.insert(CGAL_Kernel.Point_2(3,44))

lst=[]
lst.append(CGAL_Kernel.Point_2(34,4))
lst.append(CGAL_Kernel.Point_2(11,45))
lst.append(CGAL_Kernel.Point_2(11,7))

print t.dimension()
for e in t.all_edges():
  if not t.is_infinite(e):
    print t.segment(e)
  else:
    print "infinite edge"

t.insert_range(lst)
print t.number_of_vertices()
