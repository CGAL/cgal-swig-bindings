from CGAL import Kernel
from CGAL import Triangulation_3
t=Triangulation_3 .DT3_T()
l=[]
l.append(Kernel.Point_3(1,1,1))
l.append(Kernel.Point_3(2,2,2))
l.append(Kernel.Point_3(441,41,84))
l.append(Kernel.Point_3(1,1,8))
t.insert_range(l)

for p in t.finite_vertices():
  print p.point()

