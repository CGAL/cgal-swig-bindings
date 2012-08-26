import CGAL.Kernel.Point_2;
import CGAL.Convex_hull_2.CGAL_Convex_hull_2;
import java.util.LinkedList;
import java.util.Vector;


public class test_convex_hull_2 {
  public static void main(String arg[]){
    LinkedList<Point_2> L=new LinkedList<Point_2>();
    L.add( new Point_2(0,0) );
    L.add( new Point_2(1,0) );
    L.add( new Point_2(0,1) );
    L.add( new Point_2(1,1) );
    L.add( new Point_2(0.5,0.5) );
    L.add( new Point_2(0.25,0.25) );
    
    LinkedList<Point_2> result = new LinkedList<Point_2>();
    
    CGAL_Convex_hull_2.convex_hull_2(L.iterator(), result);
    
    for( Point_2 p : result)
    {
      System.out.println(p);
    }

    L.add( new Point_2(2,2) );
    Point_2 n=new Point_2();
    
    CGAL_Convex_hull_2.ch_n_point(L.iterator(),n);
    System.out.println(n);
  }
}

