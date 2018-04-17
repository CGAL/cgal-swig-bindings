import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Convex_hull_3.CGAL_Convex_hull_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import java.util.LinkedList;


public class test_convex_hull_3 {
  public static void main(String arg[]){
    LinkedList<Point_3> pts=new LinkedList<Point_3>();

    pts.add( new Point_3(0, 0, 0) );
    pts.add( new Point_3(0, 1, 0) );
    pts.add( new Point_3(1, 1, 0) );
    pts.add( new Point_3(1, 0, 0) );
    pts.add( new Point_3(0, 0, 1) );
    pts.add( new Point_3(0, 1, 1) );
    pts.add( new Point_3(1, 1, 1) );
    pts.add( new Point_3(1, 0, 1) );

    Polyhedron_3 res = new Polyhedron_3();

    CGAL_Convex_hull_3.convex_hull_3(pts.iterator(), res);
    System.out.println("convex hull has " + res.size_of_vertices() + " vertices");
    System.out.println("is strongly convex: "+CGAL_Convex_hull_3.is_strongly_convex_3(res));

    LinkedList<Plane_3> planes=new LinkedList<Plane_3>();
    planes.add( new Plane_3(-1, 0, 0, 0) );
    planes.add( new Plane_3(1, 0, 0, -1) );
    planes.add( new Plane_3(0, -1, 0, 0) );
    planes.add( new Plane_3(0, 1, 0, -1) );
    planes.add( new Plane_3(0, 0, -1, 0) );
    planes.add( new Plane_3(0, 0, 1, -1) );

    res.clear();
    CGAL_Convex_hull_3.halfspace_intersection_3(planes.iterator(), res);
    System.out.println("halfspace intersection has " + res.size_of_vertices() + " vertices");
  }
}
