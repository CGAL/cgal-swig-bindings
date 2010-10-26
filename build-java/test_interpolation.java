import CGAL.Triangulation_2.Delaunay_triangulation_2;
import CGAL.Kernel.Point_2;
import CGAL.Interpolation.CGAL_Interpolation;
import CGAL.Interpolation.Point_2_and_double;
import CGAL.Interpolation.Double_and_bool;
import java.util.LinkedList;

public class test_interpolation {
  public static void main(String arg[])
  {
    System.loadLibrary("CGAL_Interpolation");
    
    System.out.println("Testing interpolation");
    
    Delaunay_triangulation_2 dt= new Delaunay_triangulation_2();
    
    dt.insert(new Point_2(0,0));
    dt.insert(new Point_2(0,1));
    dt.insert(new Point_2(1,0));
    dt.insert(new Point_2(1.1,1.1));
    
    Point_2 p=new Point_2(0.5,0.5);
    
    LinkedList<Point_2_and_double> lst=new LinkedList<Point_2_and_double>();
    
    Double_and_bool db=CGAL_Interpolation.natural_neighbor_coordinates_2(dt,p,lst);
    
    if (!db.getSecond())
      throw new AssertionError("Point outside Convex hull");
    
    for (Point_2_and_double pd : lst)
      System.out.println(pd.getFirst()+" "+pd.getSecond()/db.getFirst());
  }
}
