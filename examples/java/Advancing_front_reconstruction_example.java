import CGAL.Kernel.Point_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Advancing_front_surface_reconstruction.CGAL_Advancing_front_surface_reconstruction;

import java.util.Vector;

public class Advancing_front_reconstruction_example{
  public static void main(String arg[]){

    Point_set_3 points = new Point_set_3("../data/oni.xyz");
    if (points.empty())
    {
      System.out.println("Error: cannot read file ../data/oni.xyz");
      return;
    }

    Polyhedron_3 P = new Polyhedron_3();

    CGAL_Advancing_front_surface_reconstruction.
      advancing_front_surface_reconstruction(points, P);

    P.write_to_file("oni.off");
  }
}
