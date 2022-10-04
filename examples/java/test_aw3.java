import CGAL.Alpha_wrap_3.CGAL_Alpha_wrap_3;
import CGAL.Alpha_wrap_3.Point_3_Vector;
import CGAL.Alpha_wrap_3.Polygon_Vector;
import CGAL.Alpha_wrap_3.Int_Vector;

import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Kernel.Point_3;
import java.util.LinkedList;

public class test_aw3 {
  public static void main(String arg[]){
    // test with a mesh as input
    Polyhedron_3 P=new Polyhedron_3("../data/elephant.off");
    Polyhedron_3 Q=new Polyhedron_3();
    CGAL_Alpha_wrap_3.alpha_wrap_3(P, 0.1, 0.01, Q);
    Q.write_to_file("elephant_alpha_wrapped.off");

    // test with soup
    Point_3_Vector points = new Point_3_Vector();
    points.reserve(3);
    points.add( new Point_3(0,0,0) );
    points.add( new Point_3(0,1,0) );
    points.add( new Point_3(1,0,0) );
    Polygon_Vector polygons = new Polygon_Vector();
    Int_Vector polygon = new Int_Vector();
    polygon.reserve(3);
    polygon.add(0);
    polygon.add(1);
    polygon.add(2);
    polygons.add(polygon);
    CGAL_Alpha_wrap_3.alpha_wrap_3(points, polygons, 0.1, 0.01, Q);
    Q.write_to_file("soup_wrapped.off");

    //test with a point set as input
    CGAL_Alpha_wrap_3.alpha_wrap_3(points, 0.1, 0.5, Q);
    Q.write_to_file("points_wrapped.off");
  }
}
