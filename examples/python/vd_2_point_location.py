from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Voronoi_diagram_2 import Voronoi_diagram_2
from CGAL.CGAL_Voronoi_diagram_2 import Voronoi_diagram_2_Halfedge_handle
from CGAL.CGAL_Voronoi_diagram_2 import Voronoi_diagram_2_Vertex_handle
from CGAL.CGAL_Voronoi_diagram_2 import Voronoi_diagram_2_Face_handle
from CGAL.CGAL_Voronoi_diagram_2 import Voronoi_diagram_2_Ccb_halfedge_circulator
from CGAL.CGAL_Voronoi_diagram_2 import Voronoi_diagram_2_Locate_result




def print_endpoint(e,is_src):
  print("\t",end='')
  if is_src:
    if e.has_source():
      print(e.source().point())
    else:
      print("point at infinity")
  else:
    if e.has_target():
      print(e.target().point())
    else:
      print("point at infinity")


points = []
points.append( Point_2(0,0) )
points.append( Point_2(100,0) )
points.append( Point_2(100,100) )
points.append( Point_2(0,100) )
points.append( Point_2(200,0) )
points.append( Point_2(300,0) )
points.append( Point_2(350,0) )

vd = Voronoi_diagram_2(points)

assert( vd.is_valid() )


queries = []
queries.append( Point_2(0,0) )
queries.append( Point_2(50,50) )
queries.append( Point_2(0,50) )
queries.append( Point_2(50,40) )
queries.append( Point_2(10,20) )
queries.append( Point_2(150,0) )
queries.append( Point_2(150,200) )
queries.append( Point_2(200,0) )
queries.append( Point_2(250,0) )
queries.append( Point_2(300,0) )
queries.append( Point_2(325,10) )

for p in queries:
  print("Query point (", p ,") lies on a Voronoi",end='')
  lr = vd.locate(p)
  if lr.is_vertex_handle():
    v=lr.get_vertex_handle()
    print("vertex.")
    print("The Voronoi vertex is:\t")
    print(v.point())
  else:
    if lr.is_halfedge_handle():
      e=lr.get_halfedge_handle()
      print("edge.")
      print("The source and target vertices of the Voronoi edge are:")
      print_endpoint(e, True)
      print_endpoint(e, False)
    else:
      if lr.is_face_handle():
        f=lr.get_face_handle()
        print("face.")
        print("The vertices of the Voronoi face are (in counterclockwise order):")
        ec_start = f.outer_ccb()

        if ec_start.hasNext():
          done = ec_start.next()
          iter=Voronoi_diagram_2_Halfedge_handle()
          while(1):
            iter=ec_start.next()
            print_endpoint(iter, False)
            if iter == done:
              break
    print("")
