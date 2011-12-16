import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Kernel.Plane_3;
import CGAL.Kernel.Segment_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.AABB_tree_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Optional_Object_and_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Object_and_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Object;
import java.util.LinkedList;


public class AABB_polyhedron_facet_intersection_example{
  public static void main(String arg[]){
    Point_3 p=new Point_3(1.0, 0.0, 0.0);
    Point_3 q=new Point_3(0.0, 1.0, 0.0);
    Point_3 r=new Point_3(0.0, 0.0, 1.0);
    Point_3 s=new Point_3(0.0, 0.0, 0.0);
    Polyhedron_3 polyhedron=new Polyhedron_3();
    polyhedron.make_tetrahedron(p, q, r, s);

    // constructs AABB tree
    AABB_tree_Polyhedron_3_Facet_handle tree = new AABB_tree_Polyhedron_3_Facet_handle(polyhedron.facets());

    // constructs segment query
    Point_3 a = new Point_3(-0.2, 0.2, -0.2);
    Point_3 b = new Point_3(1.3, 0.2, 1.3);
    Segment_3 segment_query=new Segment_3(a,b);

    // tests intersections with segment query
    if(tree.do_intersect(segment_query))
      System.out.println("intersection(s)");
    else
      System.out.println("no intersection");

    // computes #intersections with segment query
    System.out.println(tree.number_of_intersected_primitives(segment_query)+" intersection(s)");

    // computes first encountered intersection with segment query
    // (generally a point)
    Optional_Object_and_Polyhedron_3_Facet_handle intersection =
        tree.any_intersection(segment_query);
    if(!intersection.empty())
    {
      // gets intersection object
      Object_and_Polyhedron_3_Facet_handle op = intersection.value();
      Object object = op.getFirst();
      if(object.is_Point_3())
        System.out.println("intersection object is a point");
    }

    // computes all intersections with segment query (as pairs object - primitive_id)
    LinkedList<Object_and_Polyhedron_3_Facet_handle> intersections=new LinkedList<Object_and_Polyhedron_3_Facet_handle>();
    tree.all_intersections(segment_query,intersections);

    // computes all intersected primitives with segment query as primitive ids
    LinkedList<Polyhedron_3_Facet_handle> primitives = new LinkedList<Polyhedron_3_Facet_handle>();
    tree.all_intersected_primitives(segment_query,primitives);

    // constructs plane query
    Vector_3 vec = new Vector_3(0.0,0.0,1.0);
    Plane_3 plane_query = new Plane_3(a,vec);

    // computes first encountered intersection with plane query
    // (generally a segment)
    intersection = tree.any_intersection(plane_query);
    if(!intersection.empty())
    {
      // gets intersection object
      Object_and_Polyhedron_3_Facet_handle op = intersection.value();
      Object object = op.getFirst();
      if(object.is_Segment_3())
        System.out.println("intersection object is a segment");
    }
  }
}


