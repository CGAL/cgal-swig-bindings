import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Point_set_3.Point_set_3_Vector_map;
import CGAL.Point_set_3.Point_set_3_Float_map;

import java.util.Vector;

public class Point_set_3_example{
  public static void main(String arg[]){

    Point_set_3 points = new Point_set_3();
    String datafile = "../data/oni.xyz";

    // Insertions
    int idx = points.insert();
    System.out.println("Point " + idx + " inserted = " + points.point(idx));
    
    idx = points.insert (new Point_3(0, 1, 2));
    System.out.println("Point " + idx + " inserted = " + points.point(idx));

    points.insert_range (new double[] { 2., 4., 5., 2, 3, 4 });

    // Iterate and display points
    System.out.println("Point set:");
    for (Point_3 p : points.points())
      System.out.println(" * " + p);
    
    // With normal
    points.add_normal_map();
    idx = points.insert (new Point_3(6, 7, 8), new Vector_3 (1, 1, 1));

    System.out.println("Point " + idx + " inserted = ( " + points.point(idx)
                       + " ), ( " + points.normal(idx) + " )");

    // Access/modification through normal map
    Point_set_3_Vector_map normal_map = points.normal_map();

    if (normal_map.is_valid())
    {
      System.out.println("Normal 3 = " + normal_map.get(3));
      normal_map.set (2, new Vector_3 (1, 2, 3));
      System.out.println("Normal 2 = " + normal_map.get(2));
    }

    // Iterate and display normals
    System.out.println("Normal set:");
    for (Vector_3 n : points.normals())
      System.out.println(" * " + n);

    // Removal
    System.out.println("Removing point at index 2...");
    points.remove(2);
    System.out.println("Point set has " + points.size() + " point(s) and " +
                       points.garbage_size() + " garbage point(s)");

    // Iterate and display points+normals through indices
    System.out.println("Point set:");
    for (int i : points.indices())
      System.out.println(" (" + i + ") Point = ( " + points.point(i) + " ), Normal = ( "
                         + points.normal(i) + " )");

    // Removing points only puts them in garbage, we can display it too
    System.out.println("Garbage:");
    for (int i : points.garbage())
      System.out.println(" (" + i + ") Point = ( " + points.point(i) + " ), Normal = ( "
                         + points.normal(i) + " )");

    // Collect the garbage and remove them for good if we don't need them anymore
    System.out.println("Collecting garbage...");
    points.collect_garbage();
    System.out.println("Point set has " + points.size() + " point(s) and " +
                       points.garbage_size() + " garbage point(s)");

    // Dynamic property addition
    System.out.println("Adding intensity map...");
    Point_set_3_Float_map intensity = points.add_float_map("intensity");
    
    if (intensity.is_valid())
    {
      // Display properties
      String[] properties = points.properties();
      System.out.print("Point set has the following properties:");
      for (String p : properties)
        System.out.print(" '" + p + "'");
      System.out.println("");
    
      System.out.println("Setting intensity(1)=1.25 and intensity(8)=0.5");
      intensity.set(1, 1.25);
      intensity.set(3, 0.5);

      // Displaying intensity through indices
      for (int i : points.indices())
        System.out.println (" * Intensity( " + i + " ) = " + intensity.get(i));

      // Displaying intensity as a range
      System.out.println("Intensity range:");
      for (double i : points.range(intensity))
        System.out.println(" * " + i);

      // Removing the map
      points.remove_float_map(intensity);
    }

    // Reading a file
    System.out.println("Clearing and reading" + datafile);
    points.clear();
    points.read(datafile);
    System.out.println("Point set has " + points.size() + " point(s) and " +
                       points.garbage_size() + " garbage point(s)");
    
    String[] properties = points.properties();
    System.out.print(datafile + " has the following properties:");
    for (String p : properties)
      System.out.print(" '" + p + "'");
    System.out.println("");

    // Writing the point set to different formats
    System.out.println("Writing output to xyz...");
    if (!points.write("test.xyz"))
      System.out.println("Cannot write test.xyz"); // this sould NOT be displayed
    System.out.println("Writing output to off...");
    if (!points.write("test.off"))
      System.out.println("Cannot write test.off"); // this sould NOT be displayed
    System.out.println("Writing output to ply...");
    if (!points.write("test.ply"))
      System.out.println("Cannot write test.ply"); // this sould NOT be displayed
    System.out.println("Trying to write output to doc...");
    if (!points.write("test.doc"))
      System.out.println("Cannot write test.doc"); // this should be displayed
  }

}
