from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3
from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3_Cell_handle
from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3_Vertex_handle
from CGAL.CGAL_Triangulation_3 import Ref_Locate_type_3
from CGAL.CGAL_Triangulation_3 import VERTEX
from CGAL.CGAL_Kernel import Ref_int



L=[]
L.append( Point_3(0,0,0) )
L.append( Point_3(1,0,0) )
L.append( Point_3(0,1,0) )

T=Delaunay_triangulation_3(L)

n=T.number_of_vertices()

V=[]
V.append( Point_3(0,0,1) )
V.append( Point_3(1,1,1) )
V.append( Point_3(2,2,2) )

n = n + T.insert(V)

assert n==6
assert T.is_valid()

lt=Ref_Locate_type_3()
li=Ref_int()
lj=Ref_int()
p=Point_3(0,0,0)

c = T.locate(p, lt, li, lj)
assert lt.object() == VERTEX
assert c.vertex(li.object()).point() == p


v = c.vertex( (li.object()+1)&3 )
nc = c.neighbor(li.object())

nli=Ref_int()
assert nc.has_vertex( v, nli )

T.write_to_file("output",14)

T1 = Delaunay_triangulation_3()
T1.read_from_file("output")

assert T1.is_valid()
assert T1.number_of_vertices() == T.number_of_vertices()
assert T1.number_of_cells() == T.number_of_cells()
