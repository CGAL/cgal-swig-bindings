import CGAL.Kernel.Point_3;
import CGAL.Kernel.Triangle_3;
import CGAL.Kernel.Ray_3;
import CGAL.AABB_tree.AABB_tree_Triangle_3_soup;
import java.util.Vector;


public class AABB_triangle_3_example {
  public static void main(String arg[]){

    Point_3 a = new Point_3(1.0, 0.0, 0.0);
    Point_3 b = new Point_3(0.0, 1.0, 0.0);
    Point_3 c = new Point_3(0.0, 0.0, 1.0);
    Point_3 d = new Point_3(0.0, 0.0, 0.0);

    Vector<Triangle_3> triangles = new Vector<Triangle_3>();
    triangles.add(new Triangle_3(a,b,c));
    triangles.add(new Triangle_3(a,b,d));
    triangles.add(new Triangle_3(a,d,c));

    // constructs AABB tree
    AABB_tree_Triangle_3_soup tree = new AABB_tree_Triangle_3_soup(triangles.iterator());

    // counts #intersections
    Ray_3 ray_query =  new Ray_3(a,b);
    System.out.println(tree.number_of_intersected_primitives(ray_query)+" intersections(s) with ray query");

    // compute closest point and squared distance
    Point_3 point_query = new Point_3(2.0, 2.0, 2.0);
    Point_3 closest_point = tree.closest_point(point_query);
    double sqd = tree.squared_distance(point_query);
    System.out.println("squared distance: "+ sqd);
  }
}
