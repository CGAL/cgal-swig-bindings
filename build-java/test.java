import CGAL.Kernel.Point_3;
import CGAL.Triangulation_3.DT3_T;
import CGAL.Triangulation_3.DT3_Vertex_handle;

public class test {
  public static void main(String arg[]){
  System.loadLibrary("Kernel");
  System.loadLibrary("Triangulation_3");

  //~ Point_3 p=new Point_3(1,1,1);
  //~ System.out.println(p);    
  DT3_T t=new DT3_T();
  //~ t.insert(p);
    
  Point_3 [] array=new Point_3[4];
  array[0]=new Point_3(1,1,1);
  array[1]=new Point_3(1,4,3);
  array[2]=new Point_3(22,3,3);
  array[3]=new Point_3(142,3,34);
    
  t.insert_range(array);
    
  //for (Point_3 pt : array){
  //  System.out.println(pt.getCPtr(pt));
  //  System.out.println(pt);
  //}
  
  for (DT3_Vertex_handle v : t.finite_vertices())
    System.out.println(v.point());
  }
}
