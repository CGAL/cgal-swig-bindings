import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_processing_3.CGAL_Point_set_processing_3;

import java.util.Vector;

public class Point_set_processing_3_test{
  public static void main(String arg[]){
    Vector<Point_3> points = new Vector<Point_3>();

    System.out.println("Running read_xyz_points..." );
    CGAL_Point_set_processing_3.read_xyz_points("../data/oni.xyz", points);
    System.out.println(points.size()+" points read" );

    System.out.println( "Average point spacing is "+CGAL_Point_set_processing_3.compute_average_spacing(points.iterator(),24) );

    System.out.println("Running jet_smooth_point_set..." );
    CGAL_Point_set_processing_3.jet_smooth_point_set(points.iterator(),24);

    double avg_space=CGAL_Point_set_processing_3.compute_average_spacing(points.iterator(),24);
    System.out.println( "Average point spacing is "+ avg_space);

    System.out.println("Running grid_simplify_point_set..." );
    int new_size=CGAL_Point_set_processing_3.grid_simplify_point_set(points.iterator(), avg_space/5);
    points.setSize(new_size);
    System.out.println(new_size+" points remaining" );

    System.out.println("Running random_simplify_point_set..." );
    new_size=CGAL_Point_set_processing_3.random_simplify_point_set(points.iterator(), 1);
    points.setSize(new_size);
    System.out.println(new_size+" points remaining" );

    System.out.println("Running remove_outliers..." );
    new_size=CGAL_Point_set_processing_3.remove_outliers(points.iterator(), 24, 1.5);
    points.setSize(new_size);
    System.out.println(new_size+" points remaining" );

    Vector<Vector_3> normals = new Vector<Vector_3>();

    System.out.println("Running jet_estimate_normals..." );
    CGAL_Point_set_processing_3.jet_estimate_normals(points.iterator(), normals, 24);
    System.out.println(normals.size()+" normal vectors set" );

    System.out.println("Running mst_orient_normals..." );
    new_size=CGAL_Point_set_processing_3.mst_orient_normals(points.iterator(), normals.iterator(), 24);
    points.setSize(new_size);
    System.out.println(new_size+" points remaining" );
    System.out.println(normals.size()+" normal vectors set" );

    normals.removeAllElements();
    System.out.println("Running pca_estimate_normals..." );
    CGAL_Point_set_processing_3.pca_estimate_normals(points.iterator(), normals, 24);
    System.out.println(normals.size()+" normal vectors set" );

    System.out.println("Running write_xyz_points_and_normals..." );
    CGAL_Point_set_processing_3.write_xyz_points_and_normals("oni.xyz", points.iterator(), normals.iterator());
    normals.removeAllElements();
    points.removeAllElements();

    System.out.println("Running read_xyz_points_and_normals..." );
    CGAL_Point_set_processing_3.read_xyz_points_and_normals("oni.xyz", points, normals);
    System.out.println(normals.size()+" normal vectors read" );






  }
}