import CGAL.Kernel.Point_3;
import CGAL.Triangulation_3.DT3_T;

public class test {
  public static void main(String arg[]){
  System.loadLibrary("Kernel");
  System.loadLibrary("Triangulation_3");

  Point_3 p=new Point_3(1,1,1);
  System.out.println(p);    
  DT3_T t=new DT3_T();
  t.insert(p);
    
  }
}
