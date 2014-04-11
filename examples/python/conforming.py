from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Triangulation_2 import Constrained_Delaunay_triangulation_2
from CGAL.CGAL_Triangulation_2 import Constrained_Delaunay_triangulation_2_Vertex_handle
from CGAL import CGAL_Mesh_2

cdt=Constrained_Delaunay_triangulation_2()

#construct a constrained triangulation
va = cdt.insert(Point_2( 5., 5.))
vb = cdt.insert(Point_2(-5., 5.))
vc = cdt.insert(Point_2( 4., 3.))
vd = cdt.insert(Point_2( 5.,-5.))
ve = cdt.insert(Point_2( 6., 6.))
vf = cdt.insert(Point_2(-6., 6.))
vg = cdt.insert(Point_2(-6.,-6.))
vh = cdt.insert(Point_2( 6.,-6.))

cdt.insert_constraint(va,vb)
cdt.insert_constraint(vb,vc)
cdt.insert_constraint(vc,vd)
cdt.insert_constraint(vd,va)
cdt.insert_constraint(ve,vf)
cdt.insert_constraint(vf,vg)
cdt.insert_constraint(vg,vh)
cdt.insert_constraint(vh,ve)

print("Number of vertices before: ", cdt.number_of_vertices())

#make it conforming Delaunay
CGAL_Mesh_2.make_conforming_Delaunay_2(cdt)

print("Number of vertices after make_conforming_Delaunay_2: ", cdt.number_of_vertices())

#then make it conforming Gabriel
CGAL_Mesh_2.make_conforming_Gabriel_2(cdt)

print("Number of vertices after make_conforming_Gabriel_2: ", cdt.number_of_vertices())
