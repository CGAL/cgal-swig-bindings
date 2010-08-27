from CGAL import CGAL_Kernel
from CGAL import CGAL_Polyhedron_3
from CGAL import CGAL_AABB_tree

poly=CGAL_Polyhedron_3.Polyhedron_3()
poly.make_tetrahedron(CGAL_Kernel.Point_3(0,0,0),CGAL_Kernel.Point_3(1,0,0),CGAL_Kernel.Point_3(0,1,0),CGAL_Kernel.Point_3(0,0,1))
tree=CGAL_AABB_tree.AABB_tree_Polyhedron_3_Facet()

lst=[]
for f in poly.facets():
  lst.append(f)

tree.rebuild(lst);
tree=CGAL_AABB_tree.AABB_tree_Polyhedron_3_Facet(lst)
print tree.size()

lst=[]

for f in poly.facets():
  p1=f.halfedge().vertex().point()
  p2=f.halfedge().next().vertex().point()
  p3=f.halfedge().next().next().vertex().point()
  t=CGAL_Kernel.Triangle_3(p1,p2,p3)
  lst.append(t)



tree2=CGAL_AABB_tree.AABB_tree_Triangle_3_soup(lst)

s=CGAL_Kernel.Segment_3(CGAL_Kernel.Point_3(-0.5,-0.5,0.5),CGAL_Kernel.Point_3(0.5,0.5,0.5))

l=[]
tree2.all_intersected_primitives(s,l)

for i in l:
  print i
