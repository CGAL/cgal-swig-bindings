import CGAL.Kernel.Point_2;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle;
import CGAL.Mesh_2.Delaunay_mesh_size_criteria_2;
import CGAL.Mesh_2.CGAL_Mesh_2;


public class mesh_global {
  public static void main(String arg[]){
    Mesh_2_Constrained_Delaunay_triangulation_2 cdt=new Mesh_2_Constrained_Delaunay_triangulation_2();
    
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle va = cdt.insert(new Point_2(-4,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vb = cdt.insert(new Point_2(0,-1));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vc = cdt.insert(new Point_2(4,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vd = cdt.insert(new Point_2(0,1));
    cdt.insert(new Point_2(2, 0.6));

    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);

    System.out.println("Number of vertices: "+cdt.number_of_vertices());

    System.out.println("Meshing the triangulation...");

    CGAL_Mesh_2.refine_Delaunay_mesh_2(cdt, new Delaunay_mesh_size_criteria_2(0.125, 0.5));

    System.out.println("Number of vertices: "+cdt.number_of_vertices());
  }
}

