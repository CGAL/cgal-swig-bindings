from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Kernel import Plane_3
from CGAL.CGAL_Kernel import Segment_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_AABB_tree import AABB_tree_Polyhedron_3_Facet_handle


p=Point_3(1.0, 0.0, 0.0)
q=Point_3(0.0, 1.0, 0.0)
r=Point_3(0.0, 0.0, 1.0)
s=Point_3(0.0, 0.0, 0.0)
polyhedron = Polyhedron_3()
polyhedron.make_tetrahedron(p, q, r, s)

#constructs AABB tree
tree = AABB_tree_Polyhedron_3_Facet_handle(polyhedron.facets())

#constructs segment query
a = Point_3(-0.2, 0.2, -0.2)
b = Point_3(1.3, 0.2, 1.3)
segment_query=Segment_3(a,b)

#tests intersections with segment query
if tree.do_intersect(segment_query):
    print("intersection(s)")
else:
    print("no intersection")

#computes #intersections with segment query
print(tree.number_of_intersected_primitives(segment_query)," intersection(s)")

#computes first encountered intersection with segment query
#(generally a point)
intersection = tree.any_intersection(segment_query)
if not intersection.empty():
  #gets intersection object
  op = intersection.value()
  object = op[0]
  if object.is_Point_3():
      print("intersection object is a point")


#computes all intersections with segment query (as pairs object - primitive_id)
intersections=[]
tree.all_intersections(segment_query,intersections)

#computes all intersected primitives with segment query as primitive ids
primitives = []
tree.all_intersected_primitives(segment_query,primitives)

#constructs plane query
vec = Vector_3(0.0,0.0,1.0)
plane_query = Plane_3(a,vec)

#computes first encountered intersection with plane query
#(generally a segment)
intersection = tree.any_intersection(plane_query)
if not intersection.empty():
  #gets intersection object
  op = intersection.value()
  object = op[0]
  if object.is_Segment_3():
    print("intersection object is a segment")
