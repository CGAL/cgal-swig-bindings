import CGAL.Kernel.Point_3;
import CGAL.Kernel.Weighted_point_3;
import CGAL.Triangulation_3.Regular_triangulation_3;
import java.util.Vector;


public class regular_3 {
  public static void main(String arg[]){

    // generate points on a 3D grid
    Vector<Weighted_point_3> P=new Vector<Weighted_point_3>();

    int number_of_points = 0;

    for (int z=0 ; z<5 ; z++)
      for (int y=0 ; y<5 ; y++)
        for (int x=0 ; x<5 ; x++) {
            Point_3 p = new Point_3(x, y, z);
            double w = (x+y-z*y*x)*2.0; // let's say this is the weight.
            P.add(new Weighted_point_3(p, w));
            ++number_of_points;
        }

    Regular_triangulation_3 T = new Regular_triangulation_3();

    // insert all points in a row (this is faster than one insert() at a time).
    T.insert (P.iterator());

    assert T.is_valid();
    assert T.dimension() == 3;

    System.out.println("Number of vertices : " + T.number_of_vertices());

    // removal of all vertices
    int count = 0;
    while (T.number_of_vertices() > 0) {
        T.remove (T.finite_vertices().next());
        ++count;
    }

    assert count == number_of_points;
  }
}
