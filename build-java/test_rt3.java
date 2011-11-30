import CGAL.Kernel.Point_3;
import CGAL.Kernel.Weighted_point_3;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Triangulation_3.Regular_triangulation_3;
import CGAL.Triangulation_3.Regular_triangulation_3_Vertex_handle;
import java.util.LinkedList;
import java.util.Iterator;

public class test_rt3 {
  public static void main(String arg[]){
  Regular_triangulation_3 t=new Regular_triangulation_3();
    
  Regular_triangulation_3_Vertex_handle v1=t.insert(new Weighted_point_3(new Point_3(1,1,1),1));
  Regular_triangulation_3_Vertex_handle v2=t.insert(new Weighted_point_3(new Point_3(1,1,15),2),v1);
  Regular_triangulation_3_Vertex_handle v3=t.insert(new Weighted_point_3(new Point_3(154,11,5),3),v2.cell());
  Regular_triangulation_3_Vertex_handle v4=t.insert(new Weighted_point_3(new Point_3(14,0,45),4));
  
  t.clear();
    
  LinkedList<Weighted_point_3> lsti=new LinkedList<Weighted_point_3>();
  lsti.add(new Weighted_point_3(new Point_3(1,1,1),1));
  lsti.add(new Weighted_point_3(new Point_3(1,1,15),2));
  lsti.add(new Weighted_point_3(new Point_3(154,11,5),3));
  lsti.add(new Weighted_point_3(new Point_3(14,0,45),4));     
  t.insert(lsti.iterator());
  System.out.println("insert range OK");   
    
    
  Iterator<Regular_triangulation_3_Vertex_handle> it=t.finite_vertices();
  for (Regular_triangulation_3_Vertex_handle v : t.finite_vertices())
    System.out.println(v.point());
 
  }
}
