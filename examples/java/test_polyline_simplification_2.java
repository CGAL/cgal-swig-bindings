import CGAL.Kernel.Polygon_2;
import CGAL.Kernel.Point_2;
import CGAL.Polyline_simplification_2.CGAL_Polyline_simplification_2;
import CGAL.Polyline_simplification_2.Stop_below_count_ratio_threshold;
import CGAL.Polyline_simplification_2.Squared_distance_cost;
import CGAL.Polyline_simplification_2.PS2_Constrained_Delaunay_triangulation_plus_2;
import CGAL.Polyline_simplification_2.PS2_Constrained_Delaunay_triangulation_plus_2_Constraint_id;
import CGAL.Polyline_simplification_2.PS2_Constrained_Delaunay_triangulation_plus_2_Vertex_handle;

import java.util.LinkedList;

public class test_polyline_simplification_2 {
  public static void main(String arg[]){

    LinkedList<Point_2> ptlst=new LinkedList<Point_2>();
    ptlst.add( new Point_2(0,0) );
    ptlst.add( new Point_2(0,1) );
    ptlst.add( new Point_2(1,1) );

    // test polygon function
    Polygon_2 poly=new Polygon_2(ptlst.iterator());
    Polygon_2 poly_simplified = CGAL_Polyline_simplification_2.simplify(poly, new Squared_distance_cost(), new Stop_below_count_ratio_threshold(0.5));

    // test point version
    LinkedList<Point_2> outlist =  new LinkedList<Point_2>();
    CGAL_Polyline_simplification_2.simplify(ptlst.iterator(), new Squared_distance_cost(), new Stop_below_count_ratio_threshold(0.5), outlist);

    // test cdt version
    LinkedList<Point_2> polyline1=new LinkedList<Point_2>();
    polyline1.add( new Point_2(0,0) );
    polyline1.add( new Point_2(0,1) );
    polyline1.add( new Point_2(0,2) );
    polyline1.add( new Point_2(0,3) );

    LinkedList<Point_2> polyline2=new LinkedList<Point_2>();
    polyline2.add( new Point_2(1,0) );
    polyline2.add( new Point_2(1,1) );
    polyline2.add( new Point_2(1,2) );
    polyline2.add( new Point_2(1,3) );

    LinkedList<Point_2> polyline3=new LinkedList<Point_2>();
    polyline3.add( new Point_2(-1,-1) );
    polyline3.add( new Point_2( 2,-1) );
    polyline3.add( new Point_2( 2, 4) );
    polyline3.add( new Point_2(-1, 4) );

    PS2_Constrained_Delaunay_triangulation_plus_2 cdt = new PS2_Constrained_Delaunay_triangulation_plus_2();
    PS2_Constrained_Delaunay_triangulation_plus_2_Constraint_id cid1 = cdt.insert_constraint(polyline1.iterator());
    PS2_Constrained_Delaunay_triangulation_plus_2_Constraint_id cid2 = cdt.insert_constraint(polyline2.iterator());
    // consider polyline3 as closed
    PS2_Constrained_Delaunay_triangulation_plus_2_Constraint_id cid3 = cdt.insert_constraint(polyline3.iterator(),true);

    //simplify only one polyline
    CGAL_Polyline_simplification_2.simplify(cdt, cid1, new Squared_distance_cost(), new Stop_below_count_ratio_threshold(0.5)); //simplify only
    //simplify all polylines
    CGAL_Polyline_simplification_2.simplify(cdt, new Squared_distance_cost(), new Stop_below_count_ratio_threshold(0.5));

    System.out.println("Vertices of first polyline");
    for (PS2_Constrained_Delaunay_triangulation_plus_2_Vertex_handle vh : cdt.vertices_in_constraint(cid1) )
    {
      System.out.println(vh.point());
    }

    System.out.println("Vertices of second polyline");
    for (PS2_Constrained_Delaunay_triangulation_plus_2_Vertex_handle vh : cdt.vertices_in_constraint(cid2) )
    {
      System.out.println(vh.point());
    }

    System.out.println("Vertices of third polyline, note the last vertex is duplicated since it is closed");
    for (PS2_Constrained_Delaunay_triangulation_plus_2_Vertex_handle vh : cdt.vertices_in_constraint(cid3) )
    {
      System.out.println(vh.point());
    }
  }
}