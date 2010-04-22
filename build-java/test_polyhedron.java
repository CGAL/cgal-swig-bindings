import CGAL.Kernel.Point_3;
import CGAL.Polyhedron_3.Polyhedron;
import CGAL.Polyhedron_3.PH_halfedge_handle;
  
public class test_polyhedron {
  public static void main(String arg[]){
    System.loadLibrary("Kernel");
    System.loadLibrary("Polyhedron_3");

    Polyhedron p=new Polyhedron();
    p.make_triangle();
      
    System.out.println(p.size_of_vertices());
    
    int k=0;
    for (PH_halfedge_handle hh : p.halfedges())
      ++k;
    System.out.println(k);
  }
};
