import CGAL.Kernel.Point_3;
import CGAL.Kernel.Segment_3;
import CGAL.Kernel.Triangle_3;
import CGAL.AABB_tree.AABB_tree_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.AABB_tree_Triangle_3_soup;
import CGAL.AABB_tree.Optional_Object_and_Integer;
import CGAL.AABB_tree.Object_and_Integer;
import CGAL.AABB_tree.Object;
import CGAL.Kernel.CGAL_Kernel;

import java.util.LinkedList;
import java.util.Vector;

public class intersect_triangle_soup_with_polyline_aabb{
  public static void main(String[] args)
  {
    double [] t1 = {0,0,0, 2,0,0, 0,2,0};
    double [] t2 = {0,2,0, 2,0,0, 2,2,0};


    double[][] triangles = {t1, t2};

    AABB_tree_Triangle_3_soup tree_tri = new AABB_tree_Triangle_3_soup();
    tree_tri.insert_from_array(triangles);

    Segment_3 s=new Segment_3(new Point_3(0.5,0.5,1),new Point_3(0.5,0.5,-1));


    Optional_Object_and_Integer opt_seg_inter=tree_tri.any_intersection(s);
    if (!opt_seg_inter.empty())
    {
      Object_and_Integer seg_inter=opt_seg_inter.value();
      Object obj=seg_inter.getFirst();
      if ( obj.is_Point_3() ){
        Point_3 p = obj.get_Point_3();
        System.out.println("Intersection is the point "+p);
      }
      else
        if (obj.is_Segment_3())
          System.out.println("Intersection is a segment");
        else
          throw new AssertionError("Should never happen");
    }
  }
};
