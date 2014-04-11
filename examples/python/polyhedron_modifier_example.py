from __future__ import print_function
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3_Halfedge_handle
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3_Modifier_1
from CGAL.CGAL_Kernel import Point_3



P = Polyhedron_3()
modifier=Polyhedron_3_Modifier_1()
P.delegate(modifier.get_modifier())
print(P.size_of_vertices())
