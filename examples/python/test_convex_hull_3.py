from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Plane_3
from CGAL import CGAL_Convex_hull_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3

pts=[]
pts.append( Point_3(0, 0, 0) )
pts.append( Point_3(0, 1, 0) )
pts.append( Point_3(1, 1, 0) )
pts.append( Point_3(1, 0, 0) )
pts.append( Point_3(0, 0, 1) )
pts.append( Point_3(0, 1, 1) )
pts.append( Point_3(1, 1, 1) )
pts.append( Point_3(1, 0, 1) )

res = Polyhedron_3();

CGAL_Convex_hull_3.convex_hull_3(pts, res)

print("convex hull has ", res.size_of_vertices(), " vertices");
print("is strongly convex: ",CGAL_Convex_hull_3.is_strongly_convex_3(res));


planes=[];
planes.append(Plane_3(-1, 0, 0, 0) )
planes.append(Plane_3(1, 0, 0, -1) )
planes.append(Plane_3(0, -1, 0, 0) )
planes.append(Plane_3(0, 1, 0, -1) )
planes.append(Plane_3(0, 0, -1, 0) )
planes.append(Plane_3(0, 0, 1, -1) )

res.clear();
CGAL_Convex_hull_3.halfspace_intersection_3(planes, res);
print("halfspace intersection has ", res.size_of_vertices(), " vertices");
