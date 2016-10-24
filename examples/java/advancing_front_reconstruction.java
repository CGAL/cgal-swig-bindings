import CGAL.Advancing_front_surface_reconstruction.CGAL_Advancing_front_surface_reconstruction;
import CGAL.Point_set_processing_3.CGAL_Point_set_processing_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Kernel.Point_3;

import java.util.Vector;

public class advancing_front_reconstruction{
  public static void main(String arg[]){

    Vector<Point_3> points = new Vector<Point_3>();
    if ( !CGAL_Point_set_processing_3.read_xyz_points("../data/oni.xyz", points) )
    {
      System.out.println("Error: cannot read file ../data/oni.xyz");
      return;
    }

    Polyhedron_3 P = new Polyhedron_3();

    CGAL_Advancing_front_surface_reconstruction.
      advancing_front_surface_reconstruction(points.iterator(), P);

    P.write_to_file("oni.off");
  }
}
