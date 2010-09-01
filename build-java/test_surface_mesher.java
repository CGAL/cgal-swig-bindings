import CGAL.Kernel.Point_3;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3_Vertex_handle;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3_Facet;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3_Edge;
import CGAL.Surface_mesher.Complex_2_in_triangulation_3;

public class test_surface_mesher {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Surface_mesher");
    
    Surface_mesh_default_triangulation_3 tri=new Surface_mesh_default_triangulation_3();
    
    System.out.println(tri.number_of_vertices());

    Complex_2_in_triangulation_3 c2t3=new Complex_2_in_triangulation_3(tri);
    
    int i=0;
    for (Surface_mesh_default_triangulation_3_Vertex_handle v : c2t3.vertices())
      ++i;
    for (Surface_mesh_default_triangulation_3_Facet f : c2t3.facets())
      ++i;
    for (Surface_mesh_default_triangulation_3_Edge f : c2t3.edges())
      ++i;
    for (Surface_mesh_default_triangulation_3_Edge f : c2t3.boundary_edges())
      ++i;
    
  }
}
;