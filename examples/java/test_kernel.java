import CGAL.Kernel.Point_2;
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Segment_2;
import CGAL.Kernel.Segment_3;
import CGAL.Kernel.Polygon_2;
import CGAL.Kernel.Direction_3;
import CGAL.Kernel.Vector_3;
import java.util.LinkedList;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Kernel.Object;
import CGAL.Kernel.Sphere_3;
import CGAL.Kernel.Bounded_side;
import CGAL.Kernel.Bbox_3;


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
    
    Vector_3 v=new Vector_3(1,1,1);
    Direction_3 d= v.direction();

    Segment_3 seg1=new Segment_3(new Point_3(-1,0,0),new Point_3(1,0,0));
    Segment_3 seg2=new Segment_3(new Point_3(0,1,0),new Point_3(0,-1,0));
    Object obj=CGAL_Kernel.intersection(seg1,seg2);
    assert obj.is_Point_3();
    System.out.println(obj.get_Point_3());
    
    Point_3 p=new Point_3(0,0,0);
    Sphere_3 s=new Sphere_3(p,1);
    assert s.bounded_side(p)==Bounded_side.ON_BOUNDED_SIDE;
    
    Bbox_3 bbox1 = p.bbox();
    Bbox_3 bbox2 = p.bbox();
  }


}

