import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Kernel.Segment_3;
import CGAL.Kernel.Triangle_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.AABB_tree.AABB_tree_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.AABB_tree_Polyhedron_3_Halfedge_handle;
import CGAL.AABB_tree.AABB_tree_Triangle_3_soup;
import CGAL.AABB_tree.Point_and_Polyhedron_3_Halfedge_handle;
import CGAL.AABB_tree.Optional_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Optional_Object_and_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Optional_Integer;
import CGAL.AABB_tree.Object_and_Integer;
import CGAL.AABB_tree.Object_and_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Object_and_Polyhedron_3_Halfedge_handle;
import CGAL.AABB_tree.AABB_tree_Segment_3_soup;

import CGAL.AABB_tree.Object;
import CGAL.Kernel.CGAL_Kernel;

import java.util.LinkedList;
import java.util.Vector;

public class test_aabb {
  public static void test_insert_from_array(){
    System.out.println("test_insert_from_array");
    double[] s1 = {1,2,3,6,4,5};
    double[] s2 = {1,2,3,16,41,51};
    double[] s3 = {1,2,3,65,45,5};
    double[] s4 = {1,2,3,64,44,5};

    double[][] segments = {s1, s2, s3, s4};

    AABB_tree_Segment_3_soup tree_seg = new AABB_tree_Segment_3_soup();
    tree_seg.insert_from_array(segments);
    if (tree_seg.size()!=4) throw new AssertionError("invalid size");

    Segment_3 s=new Segment_3(new Point_3(1,2,3),new Point_3(0,0,0));
    if (tree_seg.do_intersect(s))
      System.out.println(" OK");
    else
      throw new AssertionError("do_intersect should return true");

    double [] t1 = {0,0,0,0,0,1,0,0,-1};
    double [] t2 = {0,0,0,0,0,1,0,1,-1};
    double [] t3 = {0,0,0,0,0,1,0,2,-1};
    double [] t4 = {0,0,0,0,0,1,0,3,-1};

    double[][] triangles = {t1, t2, t3, t4};

    AABB_tree_Triangle_3_soup tree_tri = new AABB_tree_Triangle_3_soup();
    tree_tri.insert_from_array(triangles);
    if (tree_tri.size()!=4) throw new AssertionError("invalid size");

    if (tree_seg.do_intersect(s))
      System.out.println(" OK");
    else
      throw new AssertionError("do_intersect should return true");

  }

  public static void main(String arg[]){
    System.out.println("Testing");
    test_insert_from_array();

    LinkedList<Segment_3> segments = new LinkedList<Segment_3>();
    segments.add(new Segment_3(new Point_3(1,2,3),new Point_3(6,4,5)));
    segments.add(new Segment_3(new Point_3(1,2,3),new Point_3(16,41,51)));
    segments.add(new Segment_3(new Point_3(1,2,3),new Point_3(65,45,5)));
    segments.add(new Segment_3(new Point_3(1,2,3),new Point_3(64,44,5)));
    
    AABB_tree_Segment_3_soup tree_seg = new AABB_tree_Segment_3_soup(segments.iterator());

    Polyhedron_3 poly=new Polyhedron_3();
    poly.make_tetrahedron(new Point_3(0,0,0),new Point_3(1,0,0),new Point_3(0,1,0),new Point_3(0,0,1));
    
    AABB_tree_Polyhedron_3_Facet_handle tree=new AABB_tree_Polyhedron_3_Facet_handle(poly.facets());
    AABB_tree_Polyhedron_3_Halfedge_handle tree2=new AABB_tree_Polyhedron_3_Halfedge_handle(poly.edges());
    
    System.out.println(tree.size());
    System.out.println(tree2.size());
    
    Segment_3 s=new Segment_3(new Point_3(-0.5,-0.5,0.5),new Point_3(0.5,0.5,0.5));
    
    if (tree.do_intersect(s))
      System.out.println("OK");
    else
      throw new AssertionError("oops 0");
    
    Segment_3 s2=new Segment_3(new Point_3(5,0,0.5),new Point_3(-5,0,0.5));

    if (tree2.do_intersect(s))
      System.out.println("OK");
    else
      throw new AssertionError("oops 1");
    
    LinkedList<Polyhedron_3_Facet_handle> lst_fh = new LinkedList<Polyhedron_3_Facet_handle>();
    LinkedList<Polyhedron_3_Halfedge_handle> lst_hh = new LinkedList<Polyhedron_3_Halfedge_handle>();
    tree.all_intersected_primitives(s,lst_fh);
    tree2.all_intersected_primitives(s2,lst_hh);
    System.out.println(lst_fh.size());
    System.out.println(lst_hh.size());
    
    Point_and_Polyhedron_3_Halfedge_handle pair_phh=tree2.closest_point_and_primitive(new Point_3(5,0,0.5));
    Polyhedron_3_Halfedge_handle hh=pair_phh.getSecond();
    
    Optional_Polyhedron_3_Facet_handle opt=tree.any_intersected_primitive(s);
    if (!opt.empty())
      System.out.println("OK");
    else
      throw new AssertionError("oops 2");
    
    Segment_3 seg1=new Segment_3(new Point_3(-1,0,0),new Point_3(1,0,0));
    Segment_3 seg2=new Segment_3(new Point_3(0,1,0),new Point_3(0,-1,0));
    CGAL.Kernel.Object obj=CGAL_Kernel.intersection(seg1,seg2);
    if (obj.is_Point_3())
      System.out.println(obj.get_Point_3());
    else
      throw new AssertionError("oops 3");      
    
    Optional_Object_and_Polyhedron_3_Facet_handle opt_obj_fh=tree.any_intersection(s);
    if (!opt_obj_fh.empty())
    {
      Object_and_Polyhedron_3_Facet_handle opfh=opt_obj_fh.value();
      Object obj1=opfh.getFirst();
      if ( obj1.is_Point_3() )
        System.out.println("OK");
      else
        throw new AssertionError("oops 4");
      Polyhedron_3_Facet_handle fh=opfh.getSecond();
    }
    else
      throw new AssertionError("oops 5");
    
    LinkedList<Object_and_Polyhedron_3_Facet_handle> lst_ofh = new LinkedList<Object_and_Polyhedron_3_Facet_handle>();
    LinkedList<Object_and_Polyhedron_3_Halfedge_handle> lst_ohh = new LinkedList<Object_and_Polyhedron_3_Halfedge_handle>();
    
    tree.all_intersections(s,lst_ofh);
    tree2.all_intersections(s2,lst_ohh);
    
    if (lst_fh.size()==lst_ofh.size())
      System.out.println("OK");
    else
      throw new AssertionError("oops 6");

    if (lst_hh.size()==lst_ohh.size())
      System.out.println("OK");
    else
      throw new AssertionError("oops 7");
    LinkedList<Point_3> lst_pt=new LinkedList<Point_3>();
    lst_pt.add(new Point_3(0,0,0));
    lst_pt.add(new Point_3(0,1,0));
    tree.accelerate_distance_queries(lst_pt.iterator());
    
    Vector<Triangle_3> triangles=new Vector<Triangle_3>();
    for (Polyhedron_3_Facet_handle pfh : poly.facets())
      triangles.add(new Triangle_3(pfh.halfedge().vertex().point(),pfh.halfedge().next().vertex().point(),pfh.halfedge().opposite().vertex().point()));
    AABB_tree_Triangle_3_soup tree3=new AABB_tree_Triangle_3_soup(triangles.iterator());
    Optional_Integer opt_int=tree3.any_intersected_primitive(s);
    if (!opt_int.empty())
      System.out.println("OK "+opt_int.value());
    else
      throw new AssertionError("oops 8");
    
    LinkedList<Integer> lst_int=new LinkedList<Integer>();
    tree3.all_intersected_primitives(s,lst_int);
    System.out.println(lst_int.size());
    for (Integer i : lst_int)
      System.out.println("index "+i);
    
    LinkedList<Object_and_Integer> lst_obj_int=new LinkedList<Object_and_Integer>();
    tree3.all_intersections(s,lst_obj_int);
    System.out.println(lst_obj_int.size());
    
  }
  
}
