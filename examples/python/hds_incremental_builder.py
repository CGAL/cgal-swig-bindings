from __future__ import print_function
from CGAL.CGAL_HalfedgeDS import HalfedgeDS_modifier
from CGAL.CGAL_HalfedgeDS import HalfedgeDS
from CGAL.CGAL_HalfedgeDS import HalfedgeDS_decorator
from CGAL.CGAL_HalfedgeDS import ABSOLUTE_INDEXING
from CGAL.CGAL_Kernel import Point_2

#declare a modifier interfacing the incremental_builder
m=HalfedgeDS_modifier()

#define a triangle
m.begin_surface(3,1)
m.add_vertex(Point_2(0,0))
m.add_vertex(Point_2(0,1))
m.add_vertex(Point_2(1,0.5))
m.begin_facet()
m.add_vertex_to_facet(0)
m.add_vertex_to_facet(1)
m.add_vertex_to_facet(2)
m.end_facet()


hds=HalfedgeDS()
#create the triangle in P
hds.delegate(m)
print("(v,f,e) = ", hds.size_of_vertices(), hds.size_of_faces(), divmod(hds.size_of_halfedges(),2)[0])

#clear the modifier
m.clear()

#define another triangle, reusing vertices in the polyhedron
m.begin_surface(1,1,0,ABSOLUTE_INDEXING)
m.add_vertex(Point_2(-1,0.5))
m.begin_facet()
m.add_vertex_to_facet(1)
m.add_vertex_to_facet(0)
m.add_vertex_to_facet(3)
m.end_facet()

#append a triangle incident to the existing one
hds.delegate(m)
print("(v,f,e) = ", hds.size_of_vertices(), hds.size_of_faces(), divmod(hds.size_of_halfedges(),2)[0])

assert HalfedgeDS_decorator(hds).is_valid()
