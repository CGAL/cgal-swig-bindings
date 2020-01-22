import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Point_set_processing_3.CGAL_Point_set_processing_3;

import java.util.Vector;

public class Point_set_processing_3_example{
  public static void main(String arg[]){

    String datafile = "../data/oni.xyz";
    Point_set_3 points = new Point_set_3(datafile);

    System.out.println(points.size() + " points read");

    int k = CGAL_Point_set_processing_3.estimate_global_k_neighbor_scale(points);
    System.out.println("K-neighbor scale is " + k);

    double avg_space = CGAL_Point_set_processing_3.compute_average_spacing(points,k);
    System.out.println("Average point spacing is " + avg_space);

    System.out.println("Running bilateral_smooth_point_set...");
    CGAL_Point_set_processing_3.bilateral_smooth_point_set(points,3*k);

    double scale = CGAL_Point_set_processing_3.estimate_global_range_scale(points);
    System.out.println("Range scale is" + scale);

    System.out.println("Running jet_smooth_point_set...");
    CGAL_Point_set_processing_3.jet_smooth_point_set(points,3*k);

    System.out.println("Running edge_aware_upsample_point_set...");
    CGAL_Point_set_processing_3.edge_aware_upsample_point_set(points);
    System.out.println(points.size() + " points after upsampling");

    avg_space = CGAL_Point_set_processing_3.compute_average_spacing(points,k);
    System.out.println ("Average point spacing is " + avg_space);

    System.out.println("Running wlop_simplify_and_regularize_point_set..." );
    Point_set_3 wlop_point_set = new Point_set_3();
    CGAL_Point_set_processing_3.wlop_simplify_and_regularize_point_set(points, // input
                                                                       wlop_point_set); // Output
    
    System.out.println("Output of WLOP has " + points.size() + " points");
                                       
    System.out.println("Running grid_simplify_point_set..." );
    CGAL_Point_set_processing_3.grid_simplify_point_set(points, avg_space/5);
    System.out.println(points.size() + " point(s) remaining, " + points.garbage_size() + " point(s) removed");
    points.collect_garbage();

    System.out.println("Running hierarchy_simplify_point_set..." );
    CGAL_Point_set_processing_3.hierarchy_simplify_point_set(points);
    System.out.println(points.size() + " point(s) remaining, " + points.garbage_size() + " point(s) removed");

    System.out.println("Cancelling removals");
    points.cancel_removals();
    System.out.println(points.size() + " point(s) remaining, " + points.garbage_size() + " point(s) removed");


    System.out.println("Running random_simplify_point_set...");
    CGAL_Point_set_processing_3.random_simplify_point_set(points, 1);
    System.out.println(points.size() + " point(s) remaining, " + points.garbage_size() + " point(s) removed");

    points.collect_garbage();

    System.out.println("Running remove_outliers...");
    CGAL_Point_set_processing_3.remove_outliers(points, 24);
    System.out.println(points.size() + " point(s) remaining, " + points.garbage_size() + " point(s) removed");
    points.collect_garbage();

    points.add_normal_map();

    System.out.println("Running jet_estimate_normals...");
    CGAL_Point_set_processing_3.jet_estimate_normals(points, 24);

    System.out.println("Running mst_orient_normals...");
    CGAL_Point_set_processing_3.mst_orient_normals(points, 24);

    System.out.println("Running pca_estimate_normals...");
    CGAL_Point_set_processing_3.pca_estimate_normals(points, 24);

    System.out.println("Writing to ply");
    points.write("oni.ply");
  }
}
