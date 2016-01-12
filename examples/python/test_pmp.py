from __future__ import print_function

from CGAL import CGAL_Polygon_mesh_processing
from CGAL.CGAL_Polygon_mesh_processing import Facet_pair
from CGAL.CGAL_Polygon_mesh_processing import Polygon_mesh_slicer
from CGAL.CGAL_Polygon_mesh_processing import Side_of_triangle_mesh
from CGAL.CGAL_Polygon_mesh_processing import Halfedge_pair
from CGAL.CGAL_Polygon_mesh_processing import Integer_triple
from CGAL.CGAL_Polygon_mesh_processing import Point_3_Vector
from CGAL.CGAL_Polygon_mesh_processing import Polygon_Vector
from CGAL.CGAL_Polygon_mesh_processing import Polylines
from CGAL.CGAL_Polygon_mesh_processing import Int_Vector

from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3_Halfedge_handle
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3_Facet_handle
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3_Vertex_handle
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Plane_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Kernel import Bbox_3
from CGAL.CGAL_Kernel import ON_BOUNDARY, ON_UNBOUNDED_SIDE, ON_BOUNDED_SIDE


def get_poly():
  P=Polyhedron_3()
  P.make_tetrahedron(Point_3(1,0,0), Point_3(0,0,1),Point_3(0,0,0),Point_3(0,1,0))
  return P

def test_meshing_functions():
  print("Testing meshing functions...")
  P=get_poly()
  vlist = []
  for vh in P.vertices():
    vlist.append(vh)
  del vlist[-1]
# fair
  CGAL_Polygon_mesh_processing.fair(P, vlist)
  P=get_poly();
  vlist=[]
  for vh in P.vertices():
    vlist.append(vh)
  del vlist[-1]
  CGAL_Polygon_mesh_processing.fair(P, vlist, 2)
# refine
  P=get_poly();
  flist = []
  for fh in P.facets():
    flist.append(fh)
  outf = []
  outv = []
  CGAL_Polygon_mesh_processing.refine(P, flist, outf, outv)
  flist = []
  for fh in P.facets():
    flist.append(fh)
  CGAL_Polygon_mesh_processing.refine(P, flist, outf, outv,1.41)
#  triangulate_faces
  CGAL_Polygon_mesh_processing.triangulate_faces(P)
# // isotropic_remeshing (4.8)
  P=get_poly()
  hlist = []
  for hh in P.halfedges():
    hlist.append(hh)
  flist = []
  for fh in P.facets():
    flist.append(fh)
  CGAL_Polygon_mesh_processing.isotropic_remeshing(flist, 0.25, P, 3, hlist, False)
  P.write_to_file("iso_remesh.off")
  flist = []
  for fh in P.facets():
    flist.append(fh)
  CGAL_Polygon_mesh_processing.isotropic_remeshing(flist, 0.25, P, 3)
  flist = []
  for fh in P.facets():
    flist.append(fh)
  CGAL_Polygon_mesh_processing.isotropic_remeshing(flist, 0.25, P)
# split_long_edges
  hlist = []
  for hh in P.halfedges():
    hlist.append(hh)
  CGAL_Polygon_mesh_processing.split_long_edges(hlist,0.1,P)

def test_hole_filling_functions():
  print("Testing hole filling functions...")
  P=get_poly()
  hlist = []
  for hh in P.halfedges():
    hlist.append(hh)
  h=P.make_hole(hlist[0])
  outf = []
  outv = []
# triangulate_hole
  CGAL_Polygon_mesh_processing.triangulate_hole(P,h,outf)
# triangulate_and_refine_hole
  h=P.make_hole(hlist[0])
  CGAL_Polygon_mesh_processing.triangulate_and_refine_hole(P, h, outf, outv)
  h=P.make_hole(hlist[0])
  CGAL_Polygon_mesh_processing.triangulate_and_refine_hole(P, h, outf, outv,1.4)
# triangulate_refine_and_fair_hole
  h=P.make_hole(hlist[0])
  CGAL_Polygon_mesh_processing.triangulate_refine_and_fair_hole(P, h, outf, outv)
  h=P.make_hole(hlist[0])
  CGAL_Polygon_mesh_processing.triangulate_refine_and_fair_hole(P, h, outf, outv, 1.4)
  h=P.make_hole(hlist[0])
  CGAL_Polygon_mesh_processing.triangulate_refine_and_fair_hole(P, h, outf, outv, 1.4, 1)
# triangulate_hole_polyline
  points = [Point_3(0,0,0), Point_3(1,0,0), Point_3(0,1,0)]
  third_points = [Point_3(0.5,-1,0), Point_3(1,1,0), Point_3(-1,0.5,0)]
  ints_out = []
  CGAL_Polygon_mesh_processing.triangulate_hole_polyline(points, third_points, ints_out)
  CGAL_Polygon_mesh_processing.triangulate_hole_polyline(points, ints_out)

def test_predicate_functions():
  P=get_poly()
  print("Testing predicate functions...")
#  does_self_intersect
  CGAL_Polygon_mesh_processing.does_self_intersect(P)
# self_intersections
  out = []
  CGAL_Polygon_mesh_processing.self_intersections(P, out)


def test_orientation_functions():
  P=get_poly()
  print("Testing predicate functions...")
# is_outward_oriented
  CGAL_Polygon_mesh_processing.is_outward_oriented(P)
# reverse_face_orientations
  CGAL_Polygon_mesh_processing.reverse_face_orientations(P)
  flist = []
  for fh in P.facets():
    flist.append(fh)
  CGAL_Polygon_mesh_processing.reverse_face_orientations(flist,P)
# orient_polygon_soup
  points = Point_3_Vector()
  points.reserve(3)
  points.append( Point_3(0,0,0) )
  points.append( Point_3(0,1,0) )
  points.append( Point_3(1,0,0) )
  polygons = Polygon_Vector()
  polygon = Int_Vector()
  polygon.reserve(3)
  polygon.append(0)
  polygon.append(1)
  polygon.append(2)
  polygons.append(polygon)
  CGAL_Polygon_mesh_processing.orient_polygon_soup(points, polygons)

def test_combinatorial_repairing_functions():
  print("Testing combinarial repairing functions...")
  P = Polyhedron_3()
  P.make_triangle(Point_3(0,0,0), Point_3(1,0,0), Point_3(0,1,0))
  P.make_triangle(Point_3(1,0,0), Point_3(0,0,0), Point_3(0,-1,0))
# stitch_borders
  CGAL_Polygon_mesh_processing.stitch_borders(P)
#
  P.clear()
  h1 = P.make_triangle(Point_3(0,0,0), Point_3(1,0,0), Point_3(0,1,0))
  h2 = P.make_triangle(Point_3(1,0,0), Point_3(0,0,0), Point_3(0,-1,0))
  h1=h1.opposite()
  while (h1.vertex().point()!=Point_3(1,0,0)):
    h1=h1.next()
  h2=h2.opposite()
  while (h2.vertex().point()!=Point_3(0,0,0)):
    h2=h2.next()
  hpairs = []
  hpairs.append( Halfedge_pair(h1,h2) )
  CGAL_Polygon_mesh_processing.stitch_borders(P, hpairs)

# polygon_soup_to_polygon_mesh
  P = Polyhedron_3()
  points = Point_3_Vector()
  points.reserve(3)
  points.append( Point_3(0,0,0) )
  points.append( Point_3(0,1,0) )
  points.append( Point_3(1,0,0) )
  polygons = Polygon_Vector()
  polygon = Int_Vector()
  polygon.reserve(3)
  polygon.append(0)
  polygon.append(1)
  polygon.append(2)
  polygons.append(polygon)
  CGAL_Polygon_mesh_processing.polygon_soup_to_polygon_mesh(points, polygons, P)
  assert(P.size_of_vertices()==3)

# remove_isolated_vertices (4.8)
  CGAL_Polygon_mesh_processing.remove_isolated_vertices(P)

def test_normal_computation_functions():
  P=get_poly()
  print("Testing normal computation functions...")
# compute_face_normal
  for fh in P.facets():
    v = CGAL_Polygon_mesh_processing.compute_face_normal(fh, P)
    CGAL_Polygon_mesh_processing.compute_face_normal(fh, P, v)

# compute_face_normals
  normals = []
  CGAL_Polygon_mesh_processing.compute_face_normals(P, normals)
  assert(len(normals)==P.size_of_facets())
# compute_vertex_normal
  for vh in P.vertices():
    v = CGAL_Polygon_mesh_processing.compute_vertex_normal(vh, P)
    CGAL_Polygon_mesh_processing.compute_vertex_normal(vh, P, v)

# compute_vertex_normals
  normals = []
  CGAL_Polygon_mesh_processing.compute_vertex_normals(P, normals)
  assert(len(normals)==P.size_of_vertices())

def test_connected_components_functions():
  print("Testing connected components functions...")
  P=get_poly()
# connected_component
  flist=[]
  for fh in P.facets():
    CGAL_Polygon_mesh_processing.connected_component(fh,P,flist)
# connected_components
  cc_facet_ids=CGAL_Polygon_mesh_processing.connected_components(P)
  assert(len(cc_facet_ids)==P.size_of_facets())
# keep_large_connected_components (4.8)
  CGAL_Polygon_mesh_processing.keep_large_connected_components(P,1)
# keep_largest_connected_components
  CGAL_Polygon_mesh_processing.keep_largest_connected_components(P,1)
# keep_connected_components
  for fh in P.facets():
    CGAL_Polygon_mesh_processing.keep_connected_components(P, flist)
  cc_to_keep=[0]
  CGAL_Polygon_mesh_processing.keep_connected_components(P, cc_to_keep, cc_facet_ids)
# remove_connected_components
  CGAL_Polygon_mesh_processing.remove_connected_components(P,flist)
  assert(P.empty())
  P=get_poly()
  CGAL_Polygon_mesh_processing.remove_connected_components(P, cc_to_keep, cc_facet_ids)
  assert(P.empty())

def test_geometric_measure_functions():
  print("Testing geometric measure functions...")
# face_area (4.8)
  P=get_poly()
  for fh in P.facets():
    CGAL_Polygon_mesh_processing.face_area(fh,P)
# area (4.8)
  flist = []
  for fh in P.facets():
    flist.append(fh)
  CGAL_Polygon_mesh_processing.area(flist,P)
  CGAL_Polygon_mesh_processing.area(P)
# volume (4.8)
  CGAL_Polygon_mesh_processing.volume(P)
# edge_length (4.8)
  for hh in P.halfedges():
    CGAL_Polygon_mesh_processing.edge_length(hh,P)
# face_border_length (4.8)
  for hh in P.halfedges():
    CGAL_Polygon_mesh_processing.face_border_length(hh,P)

def test_miscellaneous_functions():
  print("Testing miscellaneous functions...")
  P=get_poly()
# bbox_3 (4.8)
  CGAL_Polygon_mesh_processing.bbox_3(P)
  hlist = []
# border_halfedges (4.8)
  flist = []
  for fh in P.facets():
    flist.append(fh)
    break
  CGAL_Polygon_mesh_processing.border_halfedges(flist, P, hlist)
  assert(len(hlist)==3)

def test_polygon_mesh_slicer():
  print("Testing Polygon_mesh_slicer...")
  P=get_poly()
  slicer = Polygon_mesh_slicer(P)
  slice = Polylines()
  slicer.slice(Plane_3(1,0,0,-0.5), slice)
  assert(slice.size()==1)
  assert(len(slice[0])!=0)

def test_side_of_triangle_mesh():
  print("Testing Side_of_triangle_mesh...")
  P=get_poly()
  f = Side_of_triangle_mesh(P)
  assert(f.bounded_side(Point_3(0.25,0.25,0.25))==ON_BOUNDED_SIDE )
  assert(f.bounded_side(Point_3(0,0,0))==ON_BOUNDARY )
  assert(f.bounded_side(Point_3(4,0,0))==ON_UNBOUNDED_SIDE )


test_meshing_functions()
test_hole_filling_functions()
test_predicate_functions()
test_orientation_functions()
test_combinatorial_repairing_functions()
test_normal_computation_functions()
test_connected_components_functions()
test_geometric_measure_functions()
test_miscellaneous_functions()
test_polygon_mesh_slicer()
test_side_of_triangle_mesh()
