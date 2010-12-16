import CGAL.Kernel.Point_2;
import CGAL.Kernel.Segment_2;
import CGAL.Kernel.Polygon_2;
import java.util.LinkedList;


public class test_kernel {
  public static void main(String arg[]){
    LinkedList<Point_2> ptlst=new LinkedList<Point_2>();
    ptlst.add( new Point_2(0,0) );
    ptlst.add( new Point_2(0,1) );
    ptlst.add( new Point_2(1,1) );
    
    Polygon_2 poly=new Polygon_2(ptlst.iterator());
    
    System.out.println("poly.size() "+poly.size());
    
    for ( Point_2 p : poly.vertices() )
      System.out.println(p);

    for ( Segment_2 p : poly.edges() )
      System.out.println(p);
    
    
    
  }


}

