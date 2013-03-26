import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_processing_3.CGAL_Point_set_processing_3;

import java.util.Vector;



public class remove_outliers_example{
  public static void main(String arg[]){
    
  // Reads a .xyz point set file in points[].
  Vector<Point_3> points = new Vector<Point_3>();
  if ( !CGAL_Point_set_processing_3.read_xyz_points("../data/oni.xyz",points) )
  {
    System.out.println("Error: cannot read file ../data/oni.xyz");
    return;
  }

  // Removes outliers using erase-remove idiom.
  double removed_percentage = 5.0; // percentage of points to remove
  int nb_neighbors = 24; // considers 24 nearest neighbor points
  int new_size=CGAL_Point_set_processing_3.remove_outliers(points.iterator(), nb_neighbors, removed_percentage);
  points.setSize(new_size);
  }
}
