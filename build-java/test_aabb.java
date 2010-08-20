import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.AABB_tree_test;

import java.util.LinkedList;

public class test_aabb {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_AABB_tree");
    System.loadLibrary("CGAL_Polyhedron_3");
    Polyhedron_3 poly=new Polyhedron_3();
    poly.make_tetrahedron(new Point_3(0,0,0),new Point_3(1,0,0),new Point_3(0,1,0),new Point_3(0,0,1));
    
    AABB_tree_test tree=new AABB_tree_test(poly.facets());
    
    System.out.println(tree.size());
    
  }
  
}