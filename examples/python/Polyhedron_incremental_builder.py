from __future__ import print_function
from CGAL.CGAL_Polyhedron_3 import Polyhedron_modifier
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Polyhedron_3 import ABSOLUTE_INDEXING
from CGAL.CGAL_Kernel import Point_3

#declare a modifier interfacing the incremental_builder
m=Polyhedron_modifier()

#define a triangle
m.begin_surface(3,1)
m.add_vertex(Point_3(0,0,0))
m.add_vertex(Point_3(0,1,0))
m.add_vertex(Point_3(1,0.5,0))
m.begin_facet()
m.add_vertex_to_facet(0)
m.add_vertex_to_facet(1)
m.add_vertex_to_facet(2)
m.end_facet()


P=Polyhedron_3()
#create the triangle in P
P.delegate(m)
print("(v,f,e) = ", P.size_of_vertices(), P.size_of_facets(), divmod(P.size_of_halfedges(),2)[0])

#clear the modifier
m.clear()

#define another triangle, reusing vertices in the polyhedron
m.begin_surface(1,1,0,ABSOLUTE_INDEXING)
m.add_vertex(Point_3(-1,0.5,0))
m.begin_facet()
m.add_vertex_to_facet(1)
m.add_vertex_to_facet(0)
m.add_vertex_to_facet(3)
m.end_facet()

#append a triangle incident to the existing one
P.delegate(m)
print("(v,f,e) = ", P.size_of_vertices(), P.size_of_facets(), divmod(P.size_of_halfedges(),2)[0])

assert P.is_valid()
