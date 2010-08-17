import CGAL.Kernel.Point_2;
import CGAL.Kernel.Weighted_point_2;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Alpha_shape_2.Alpha_shape_2;
import CGAL.Alpha_shape_2.Weighted_alpha_shape_2;
import CGAL.Alpha_shape_2.Mode;
import CGAL.Alpha_shape_2.Classification_type;
import CGAL.Alpha_shape_2.Alpha_shape_2_Alpha_iterator;
import CGAL.Alpha_shape_2.Alpha_shape_2_Vertex_handle;
import CGAL.Alpha_shape_2.Alpha_shape_2_Face_handle;
import CGAL.Alpha_shape_2.Vertex_range;
import CGAL.Alpha_shape_2.Face_Interval_3;
import java.util.LinkedList;
import java.util.Iterator;

public class test_as2 {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Alpha_shape_2");
    Alpha_shape_2 t=new Alpha_shape_2(0,Mode.GENERAL);
    
    LinkedList<Point_2> lst=new LinkedList<Point_2>();
    lst.add( new Point_2(0,0) );
    lst.add( new Point_2(0,4) );
    lst.add( new Point_2(44,0) );
    lst.add( new Point_2(44,5) );
    lst.add( new Point_2(444,51) );
    lst.add( new Point_2(14,1) );
    
    t.make_alpha_shape(lst.iterator());
    
    for (Double d : t.alpha())
      System.out.println(d);
    
    for (Alpha_shape_2_Vertex_handle v : t.finite_vertices())
    {
      Classification_type type=t.classify(v);
      System.out.println(v.get_range().getFirst());
      switch(type){
        case INTERIOR:
          System.out.println("EXTERIOR"); break;
        case SINGULAR:
          System.out.println("SINGULAR"); break;
        case REGULAR:
          System.out.println("REGULAR"); break;
        case EXTERIOR:
          System.out.println("EXTERIOR"); break;
      }
    }
    
    for (Alpha_shape_2_Face_handle f : t.finite_faces())
    {
      Face_Interval_3 i=f.get_ranges(0);
      System.out.println(i.getFirst());
      System.out.println(i.getSecond());
      System.out.println(i.getThird());
    }
    
    Weighted_alpha_shape_2 was=new Weighted_alpha_shape_2();
    LinkedList<Weighted_point_2> lst_wp=new LinkedList<Weighted_point_2>();
    lst_wp.add( new Weighted_point_2( new Point_2(0,0) ,1 ) );
    lst_wp.add( new Weighted_point_2( new Point_2(0,4) ,1 ) );
    lst_wp.add( new Weighted_point_2( new Point_2(44,0) ,1 ) );
    lst_wp.add( new Weighted_point_2( new Point_2(44,5) ,1 ) );
    lst_wp.add( new Weighted_point_2( new Point_2(444,51) ,1 ) );
    lst_wp.add( new Weighted_point_2( new Point_2(14,1) ,1 ) );
    
    was.make_alpha_shape(lst_wp.iterator());
  }
}
