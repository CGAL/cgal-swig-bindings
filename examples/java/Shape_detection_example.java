import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Point_set_3.Point_set_3_Int_map;
import CGAL.Shape_detection.CGAL_Shape_detection;

public class Shape_detection_example{
  public static void main(String arg[]){

    String datafile = "../data/cube.pwn";
    Point_set_3 points = new Point_set_3(datafile);

    System.out.println(points.size() + " points read");

    System.out.println("Detecting planes with region growing (sphere query)");
    Point_set_3_Int_map plane_map = points.add_int_map("plane_index");
    int nb_planes = CGAL_Shape_detection.region_growing (points, plane_map,
                                                         20); // min_points
    System.out.println(nb_planes + " planes(s) detected");

    System.out.println("Detecting planes with region growing (k-neighbor query)");
    nb_planes = CGAL_Shape_detection.region_growing (points, plane_map,
                                                     20, // min_points
                                                     -1, -1, 0.9, // default params
                                                     12); // k
    System.out.println(nb_planes + " planes(s) detected");
    
    System.out.println("Detecting planes with efficient RANSAC");
    String[] planes = CGAL_Shape_detection.efficient_RANSAC (points, plane_map);
    System.out.println(planes.length + " planes(s) detected, first 10 planes are:");
    for (int s = 0; s < Math.min(planes.length, 10); s ++)
      System.out.println(" * " + s + " : " + planes[s]);

    System.out.println("Detecting cylinders with efficient RANSAC");
    Point_set_3_Int_map cylinder_map = points.add_int_map("cylinder_index");
    String[] cylinders = CGAL_Shape_detection.efficient_RANSAC (points, cylinder_map,
                                                                1, -1, -1, 0.9, 0.01, // default params
                                                                false, // planes
                                                                false, // cones
                                                                true); // cylinders
    System.out.println(cylinders.length + " cylinders(s) detected, first 10 cylinders are:");
    for (int s = 0; s < Math.min(cylinders.length, 10); s ++)
      System.out.println(" * " + s + " : " + cylinders[s]);

    System.out.println("Detecting everything possible with efficient RANSAC (custom parameters)");
    Point_set_3_Int_map shape_map = points.add_int_map("shape_index");
    String[] shapes = CGAL_Shape_detection.efficient_RANSAC (points, shape_map,
                                                             5, 1., 1.2, 0.85, 0.05,
                                                             true, true, true, true, true);
    System.out.println(shapes.length + " shapes(s) detected, first 10 shapes are:");
    for (int s = 0; s < Math.min(shapes.length, 10); s ++)
      System.out.println(" * " + s + " : " + shapes[s]);

    // Counting types of shapes
    nb_planes = 0;
    int nb_cones = 0,
      nb_cylinders = 0,
      nb_spheres = 0,
      nb_tori = 0;
    for (String s : shapes)
    {
      String type = s.split(" ")[1];
      if (type.equals("cone")) nb_cones += 1;
      if (type.equals("cylinder")) nb_cylinders += 1;
      if (type.equals("planes")) nb_planes += 1;
      if (type.equals("spheres")) nb_spheres += 1;
      if (type.equals("torus")) nb_tori += 1;
    }
    System.out.println("Number of shapes by type:");
    System.out.println(" * " + nb_cones + " cone(s)");
    System.out.println(" * " + nb_cylinders + " cylinder(s)");
    System.out.println(" * " + nb_planes + " planes(s)");
    System.out.println(" * " + nb_spheres + " spheres(s)");
    System.out.println(" * " + nb_tori + " torus/i");

    System.out.println("Recovering inliers of first shape");
    Point_set_3 inliers_of_first_shape = new Point_set_3();
    for (int idx : points.indices())
      if (shape_map.get(idx) == 0)
        inliers_of_first_shape.insert(points.point(idx));
    System.out.println(inliers_of_first_shape.size() + " inliers(s) recovered");
  }
}
