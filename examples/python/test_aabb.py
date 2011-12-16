from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Segment_3
from CGAL.CGAL_Kernel import Triangle_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_AABB_tree import AABB_tree_Polyhedron_3_Facet
from CGAL.CGAL_AABB_tree import AABB_tree_Triangle_3_soup

poly=Polyhedron_3()
poly.make_tetrahedron(Point_3(0,0,0),Point_3(1,0,0),Point_3(0,1,0),Point_3(0,0,1))
tree=AABB_tree_Polyhedron_3_Facet()

lst=[]
for f in poly.facets():
  lst.append(f)

tree.rebuild(lst)
tree=AABB_tree_Polyhedron_3_Facet(lst)
print tree.size()

lst=[]

for f in poly.facets():
  p1=f.halfedge().vertex().point()
  p2=f.halfedge().next().vertex().point()
  p3=f.halfedge().next().next().vertex().point()
  t=Triangle_3(p1,p2,p3)
  lst.append(t)



tree2=AABB_tree_Triangle_3_soup(lst)

s=Segment_3(Point_3(-0.5,-0.5,0.5),Point_3(0.5,0.5,0.5))

l=[]
tree2.all_intersected_primitives(s,l)

for i in l:
  print i
