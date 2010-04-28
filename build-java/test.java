import CGAL.Kernel.Point_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3_Vertex_handle;
import java.util.Iterator;

public class test {
  public static void main(String arg[]){
  System.loadLibrary("CGAL_Triangulation_3");

  //~ Point_3 p=new Point_3(1,1,1);
  //~ System.out.println(p);    
  Delaunay_triangulation_3 t=new Delaunay_triangulation_3();
  //~ t.insert(p);
    
  Point_3 [] array=new Point_3[4];
  array[0]=new Point_3(1,1,1);
  array[1]=new Point_3(1,4,3);
  array[2]=new Point_3(22,3,3);
  array[3]=new Point_3(142,3,34);
    
  t.insert_range(array);
    
  Iterator<Delaunay_triangulation_3_Vertex_handle> it=t.finite_vertices();
  //for (Point_3 pt : array){
  //  System.out.println(pt.getCPtr(pt));
  //  System.out.println(pt);
  //}
  
  for (Delaunay_triangulation_3_Vertex_handle v : t.finite_vertices())
    System.out.println(v.point());
  }
}
