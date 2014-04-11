from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL import CGAL_Convex_hull_2

L=[]
L.append( Point_2(0,0) )
L.append( Point_2(1,0) )
L.append( Point_2(0,1) )
L.append( Point_2(1,1) )
L.append( Point_2(0.5,0.5) )
L.append( Point_2(0.25,0.25) )

result = []
CGAL_Convex_hull_2.convex_hull_2(L, result)

for  p in  result:
  print(p)


L.append( Point_2(2,2) )
n=Point_2()

CGAL_Convex_hull_2.ch_n_point(L,n)
print(n)
