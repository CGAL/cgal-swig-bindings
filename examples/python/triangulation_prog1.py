from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Triangulation_2 import Triangulation_2
from CGAL.CGAL_Triangulation_2 import Triangulation_2_Vertex_circulator
from CGAL.CGAL_Triangulation_2 import Triangulation_2_Vertex_handle

points=[]
points.append( Point_2(1,0) )
points.append( Point_2(3,2) )
points.append( Point_2(4,5) )
points.append( Point_2(9,8) )
points.append( Point_2(7,4) )
points.append( Point_2(5,2) )
points.append( Point_2(6,3) )
points.append( Point_2(10,1) )

t=Triangulation_2()
t.insert(points)

vc = t.incident_vertices(t.infinite_vertex())

if vc.hasNext():
  done = vc.next()
  iter=Triangulation_2_Vertex_handle()
  while(1):
    iter=vc.next()
    print(iter.point())
    if iter == done:
      break
