from CGAL.CGAL_HalfedgeDS import HalfedgeDS
from CGAL.CGAL_HalfedgeDS import HalfedgeDS_decorator
from CGAL.CGAL_HalfedgeDS import HDS_Halfedge_handle


hds = HalfedgeDS()
decorator = HalfedgeDS_decorator(hds)
decorator.create_loop()
decorator.create_segment()
assert decorator.is_valid()

n = 0
for h in hds.halfedges():
  n+=1

assert n == 4
