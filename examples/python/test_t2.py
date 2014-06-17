from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Triangulation_2 import Constraint
from CGAL.CGAL_Triangulation_2 import Constrained_Delaunay_triangulation_plus_2
from CGAL.CGAL_Triangulation_2 import Ref_Constrained_Delaunay_triangulation_plus_2_Face_handle
from CGAL.CGAL_Kernel import Ref_int

constraints=[]

constraints.append(Constraint(Point_2(745,118),Point_2(777,88)))
constraints.append(Constraint(Point_2(744,888),Point_2(71177,88)))
constraints.append(Constraint(Point_2(711,888),Point_2(7757,88)))

t=Constrained_Delaunay_triangulation_plus_2(constraints)

print("Nb vertices ",t.number_of_vertices())


v1=t.insert(Point_2(1,2))
v2=t.insert(Point_2(3,2))
v3=t.insert(Point_2(3,44))

lst=[]
lst.append(Point_2(34,4))
lst.append(Point_2(11,45))
lst.append(Point_2(11,7))

print(t.dimension())
for e in t.all_edges():
  if not t.is_infinite(e):
    print(t.segment(e))
  else:
    print("infinite edge")

for e in lst:
  print(e)

print("Try point range insertion")
t.insert(lst)


edges=[]

for v in t.finite_vertices():
  t.incident_constraints(v,edges)

rf=Ref_Constrained_Delaunay_triangulation_plus_2_Face_handle()
ri=Ref_int()
t.is_edge(edges[0][0].vertex(t.cw(edges[0][1])),
          edges[0][0].vertex(t.ccw(edges[0][1])),
          rf, ri );
assert( rf.object()==edges[0][0] or rf.object()==edges[0][0].neighbor( edges[1] ) )


print("Nb incident constraints ", len(edges))

print(t.number_of_vertices())



for v in t.finite_vertices():
  print(v.point())
