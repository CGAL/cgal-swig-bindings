from CGAL import CGAL_Kernel
from CGAL import CGAL_Triangulation_2


constraints=[]

constraints.append(CGAL_Triangulation_2.Constraint(CGAL_Kernel.Point_2(745,118),CGAL_Kernel.Point_2(777,88)))
constraints.append(CGAL_Triangulation_2.Constraint(CGAL_Kernel.Point_2(744,888),CGAL_Kernel.Point_2(71177,88)))
constraints.append(CGAL_Triangulation_2.Constraint(CGAL_Kernel.Point_2(711,888),CGAL_Kernel.Point_2(7757,88)))
#constraints.append(54)

t=CGAL_Triangulation_2.Constrained_Delaunay_triangulation_plus_2(constraints)
#~ t=CGAL_Triangulation_2.Constrained_Delaunay_triangulation_plus_2()



print "Nb vertices ",t.number_of_vertices()


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

for e in lst:
  print e

print "Try point range insertion"
t.insert_range(lst)



#~ print t.number_of_vertices()



for v in t.finite_vertices():
  print v.point()

