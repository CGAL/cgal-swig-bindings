import CGAL.Kernel.Point_3;
import CGAL.Kernel.Sphere_3;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3_Vertex_handle;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3_Facet;
import CGAL.Surface_mesher.Surface_mesh_default_triangulation_3_Edge;
import CGAL.Surface_mesher.Complex_2_in_triangulation_3;
import CGAL.Surface_mesher.CGAL_Surface_mesher;
import CGAL.Surface_mesher.Gray_level_image_3;
import CGAL.Surface_mesher.Implicit_surface_Gray_level_image_3;
import CGAL.Surface_mesher.Surface_mesh_default_criteria_3;
import CGAL.Surface_mesher.Surface_mesher_tag;
import CGAL.Polyhedron_3.Polyhedron_3;
import java.util.LinkedList;
import java.io.File;

public class test_surface_mesher {
  public static void main(String arg[]){
    Surface_mesh_default_triangulation_3 tri=new Surface_mesh_default_triangulation_3();
    
    System.out.println(tri.number_of_vertices());

    Complex_2_in_triangulation_3 c2t3=new Complex_2_in_triangulation_3(tri);

    LinkedList<Surface_mesh_default_triangulation_3_Facet> lst=new LinkedList<Surface_mesh_default_triangulation_3_Facet>();
    
    int i=0;
    for (Surface_mesh_default_triangulation_3_Vertex_handle v : c2t3.vertices()){
      c2t3.incident_facets(v,lst);
      ++i;
    }
    for (Surface_mesh_default_triangulation_3_Facet f : c2t3.facets())
      ++i;
    for (Surface_mesh_default_triangulation_3_Edge f : c2t3.edges())
      ++i;
    for (Surface_mesh_default_triangulation_3_Edge f : c2t3.boundary_edges())
      ++i;

    File f = new File("skull_2.9.inr");
    if(!f.isFile()){
      System.err.println("Error: Cannot open skull_2.9.inr");
      return;
    }

    Gray_level_image_3 image=new Gray_level_image_3("skull_2.9.inr",2.9);
       
    Sphere_3 sphere=new Sphere_3(new Point_3(122., 102., 117.),200.*200.*2);
    Implicit_surface_Gray_level_image_3 surface=new Implicit_surface_Gray_level_image_3(image, sphere, 1e-5);
    Surface_mesh_default_criteria_3 criteria=new Surface_mesh_default_criteria_3(30.,5.,5.);
    
    
    CGAL_Surface_mesher.make_surface_mesh(c2t3,surface,criteria,Surface_mesher_tag.MANIFOLD_TAG);
    
    CGAL_Surface_mesher.output_surface_facets_to_off("/tmp/test_out.off",c2t3);    
    
    Polyhedron_3 poly=new Polyhedron_3();
    
    CGAL_Surface_mesher.output_surface_facets_to_polyhedron(c2t3,poly);
    System.out.println(poly.size_of_vertices()+" "+poly.size_of_halfedges()+" "+poly.size_of_facets());
  }
};