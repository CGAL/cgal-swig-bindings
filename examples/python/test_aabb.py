from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Segment_3
from CGAL.CGAL_Kernel import Triangle_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_AABB_tree import AABB_tree_Polyhedron_3_Facet_handle
from CGAL.CGAL_AABB_tree import AABB_tree_Triangle_3_soup
from CGAL.CGAL_AABB_tree import AABB_tree_Segment_3_soup


def test_insert_from_array():
  print("test_insert_from_array")
  s1 = [1,2,3,6,4,5]
  s2 = [1,2,3,16,41,51]
  s3 = [1,2,3,65,45,5]
  s4 = [1,2,3,64,44,5]

  segments = [s1, s2, s3, s4]

  tree_seg = AABB_tree_Segment_3_soup()
  tree_seg.insert_from_array(segments)
  assert(tree_seg.size()==4)

  s=Segment_3(Point_3(1,2,3), Point_3(0,0,0))
  assert(tree_seg.do_intersect(s))

  t1 = [0,0,0,0,0,1,0,0,-1]
  t2 = [0,0,0,0,0,1,0,1,-1]
  t3 = [0,0,0,0,0,1,0,2,-1]
  t4 = [0,0,0,0,0,1,0,3,-1]

  triangles = [t1, t2, t3, t4]

  tree_tri = AABB_tree_Triangle_3_soup()
  tree_tri.insert_from_array(triangles)
  assert(tree_tri.size()==4)

  assert(tree_seg.do_intersect(s))


test_insert_from_array()

poly=Polyhedron_3()
poly.make_tetrahedron(Point_3(0,0,0),Point_3(1,0,0),Point_3(0,1,0),Point_3(0,0,1))
tree=AABB_tree_Polyhedron_3_Facet_handle()

lst=[]
for f in poly.facets():
  lst.append(f)

tree.rebuild(lst)
tree=AABB_tree_Polyhedron_3_Facet_handle(lst)
print(tree.size())

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
  print(i)
