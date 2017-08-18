from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Mesh_2 import Mesh_2_Constrained_Delaunay_triangulation_2
from CGAL.CGAL_Mesh_2 import Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle
from CGAL.CGAL_Mesh_2 import Delaunay_mesh_size_criteria_2
from CGAL.CGAL_Mesh_2 import Default_Delaunay_mesher_2
from CGAL import CGAL_Mesh_2


cdt=Mesh_2_Constrained_Delaunay_triangulation_2()
va = cdt.insert( Point_2(-2,0) )
vb = cdt.insert( Point_2(0,-2) )
vc = cdt.insert( Point_2(2,0) )
vd = cdt.insert( Point_2(0,1) )
cdt.insert( Point_2(2, 0.6) )

cdt.insert_constraint(va, vb);
cdt.insert_constraint(vb, vc);
cdt.insert_constraint(vc, vd);
cdt.insert_constraint(vd, va);

print("Number of vertices: ", cdt.number_of_vertices() );
print("Meshing...");
mesher = Default_Delaunay_mesher_2(cdt);
mesher.set_criteria(Delaunay_mesh_size_criteria_2(0.125, 0.05));
mesher.refine_mesh();

print("Number of vertices: ", cdt.number_of_vertices() )
print("Run Lloyd optimization...")
CGAL_Mesh_2.cgal_lloyd_optimize_mesh_2(cdt, 0, 10)
print("done.")
print("Number of vertices: ", cdt.number_of_vertices() )
