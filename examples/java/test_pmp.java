import CGAL.Polygon_mesh_processing.CGAL_Polygon_mesh_processing;
import CGAL.Polygon_mesh_processing.Facet_pair;
import CGAL.Polygon_mesh_processing.Polygon_mesh_slicer;
import CGAL.Polygon_mesh_processing.Side_of_triangle_mesh;
import CGAL.Polygon_mesh_processing.Halfedge_pair;
import CGAL.Polygon_mesh_processing.Integer_triple;
import CGAL.Polygon_mesh_processing.Point_3_Vector;
import CGAL.Polygon_mesh_processing.Polygon_Vector;
import CGAL.Polygon_mesh_processing.Polylines;
import CGAL.Polygon_mesh_processing.Int_Vector;

import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Vertex_handle;
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Kernel.Vector_3;
import CGAL.Kernel.Bbox_3;
import CGAL.Kernel.Bounded_side;

import java.util.LinkedList;

public class test_pmp {
  public static Polyhedron_3 get_poly() {
    Polyhedron_3 P=new Polyhedron_3();
    P.make_tetrahedron(  new Point_3( 1, 0, 0),
                         new Point_3( 0, 0, 1),
                         new Point_3( 0, 0, 0),
                         new Point_3( 0, 1, 0));
    return P;
  }

  public static void test_meshing_functions(){
    System.out.println("Testing meshing functions...");
    Polyhedron_3 P=get_poly();
    LinkedList<Polyhedron_3_Vertex_handle> vlist = new LinkedList<Polyhedron_3_Vertex_handle>();
    for (Polyhedron_3_Vertex_handle vh : P.vertices())
      vlist.add(vh.clone());
    vlist.pop();
// fair
    CGAL_Polygon_mesh_processing.fair(P, vlist.iterator());
    P=get_poly();
    vlist.clear();
    for (Polyhedron_3_Vertex_handle vh : P.vertices())
      vlist.add(vh.clone());
    vlist.pop();
    CGAL_Polygon_mesh_processing.fair(P, vlist.iterator(),2);
// refine
    P=get_poly();
    LinkedList<Polyhedron_3_Facet_handle> flist = new LinkedList<Polyhedron_3_Facet_handle>();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
    LinkedList<Polyhedron_3_Facet_handle> outf = new LinkedList<Polyhedron_3_Facet_handle>();
    LinkedList<Polyhedron_3_Vertex_handle> outv = new LinkedList<Polyhedron_3_Vertex_handle>();
    CGAL_Polygon_mesh_processing.refine(P, flist.iterator(), outf, outv);
    flist.clear();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
    CGAL_Polygon_mesh_processing.refine(P, flist.iterator(), outf, outv,1.41);
    flist.clear();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
// triangulate_face (4.8)
    CGAL_Polygon_mesh_processing.triangulate_face(flist.getFirst(), P);
// triangulate_faces
    CGAL_Polygon_mesh_processing.triangulate_faces(P);
    CGAL_Polygon_mesh_processing.triangulate_faces(flist.iterator(),P); // (4.8)
// isotropic_remeshing (4.8)
    P=get_poly();
    LinkedList<Polyhedron_3_Halfedge_handle> hlist = new LinkedList<Polyhedron_3_Halfedge_handle>();
    for (Polyhedron_3_Halfedge_handle hh : P.halfedges())
      hlist.add(hh.clone());
    flist.clear();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
    CGAL_Polygon_mesh_processing.isotropic_remeshing(
      flist.iterator(), 0.25, P, 3, hlist.iterator(), false);
    P.write_to_file("iso_remesh.off");
    flist.clear();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
    CGAL_Polygon_mesh_processing.isotropic_remeshing(
      flist.iterator(), 0.25, P, 3);
    flist.clear();
    for (Polyhedron_3_Facet_handle fh : P.facets())
       flist.add(fh.clone());
    CGAL_Polygon_mesh_processing.isotropic_remeshing(
      flist.iterator(),0.25, P);
// split_long_edges
    hlist.clear();
    for (Polyhedron_3_Halfedge_handle hh : P.halfedges())
      hlist.add(hh.clone());
    CGAL_Polygon_mesh_processing.split_long_edges(hlist.iterator(), 0.1, P);
  }

  public static void test_hole_filling_functions()
  {
    System.out.println("Testing hole filling functions...");
    Polyhedron_3 P=get_poly();
    LinkedList<Polyhedron_3_Halfedge_handle> hlist = new LinkedList<Polyhedron_3_Halfedge_handle>();
    for (Polyhedron_3_Halfedge_handle hh : P.halfedges())
      hlist.add(hh.clone());
    Polyhedron_3_Halfedge_handle h=P.make_hole(hlist.getFirst());
    LinkedList<Polyhedron_3_Facet_handle> outf = new LinkedList<Polyhedron_3_Facet_handle>();
    LinkedList<Polyhedron_3_Vertex_handle> outv = new LinkedList<Polyhedron_3_Vertex_handle>();
//triangulate_hole
    CGAL_Polygon_mesh_processing.triangulate_hole(P,h,outf);
//triangulate_and_refine_hole
    h=P.make_hole(hlist.getFirst());
    CGAL_Polygon_mesh_processing.triangulate_and_refine_hole(P, h, outf, outv);
    h=P.make_hole(hlist.getFirst());
    CGAL_Polygon_mesh_processing.triangulate_and_refine_hole(P, h, outf, outv,1.4);
//triangulate_refine_and_fair_hole
    h=P.make_hole(hlist.getFirst());
    CGAL_Polygon_mesh_processing.triangulate_refine_and_fair_hole(P, h, outf, outv);
    h=P.make_hole(hlist.getFirst());
    CGAL_Polygon_mesh_processing.triangulate_refine_and_fair_hole(P, h, outf, outv, 1.4);
    h=P.make_hole(hlist.getFirst());
    CGAL_Polygon_mesh_processing.triangulate_refine_and_fair_hole(P, h, outf, outv, 1.4, 1);
// triangulate_hole_polyline
    LinkedList<Point_3> points = new LinkedList<Point_3>();
    points.add( new Point_3( 0, 0, 0) );
    points.add( new Point_3( 1, 0, 0) );
    points.add( new Point_3( 0, 1, 0) );
    LinkedList<Point_3> third_points = new LinkedList<Point_3>();
    third_points.add( new Point_3( 0.5, -1, 0) );
    third_points.add( new Point_3( 1, 1, 0) );
    third_points.add( new Point_3( -1, 0.5, 0) );
    LinkedList<Integer_triple> ints_out = new LinkedList<Integer_triple>();
    CGAL_Polygon_mesh_processing.triangulate_hole_polyline(
      points.iterator(), third_points.iterator(), ints_out);
    CGAL_Polygon_mesh_processing.triangulate_hole_polyline(
      points.iterator(), ints_out);
  }

  public static void test_predicate_functions()
  {
    Polyhedron_3 P=get_poly();
    System.out.println("Testing predicate functions...");
// does_self_intersect
    CGAL_Polygon_mesh_processing.does_self_intersect(P);
// self_intersections
    LinkedList<Facet_pair> out = new LinkedList<Facet_pair>();
    CGAL_Polygon_mesh_processing.self_intersections(P, out);
  }

  public static void test_orientation_functions()
  {
    Polyhedron_3 P=get_poly();
    System.out.println("Testing predicate functions...");
// is_outward_oriented
    CGAL_Polygon_mesh_processing.is_outward_oriented(P);
// reverse_face_orientations
    CGAL_Polygon_mesh_processing.reverse_face_orientations(P);
    LinkedList<Polyhedron_3_Facet_handle> flist = new LinkedList<Polyhedron_3_Facet_handle>();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
    CGAL_Polygon_mesh_processing.reverse_face_orientations(flist.iterator(),P);
//   orient_polygon_soup
    Point_3_Vector points = new Point_3_Vector();
    points.reserve(3);
    points.add( new Point_3(0,0,0) );
    points.add( new Point_3(0,1,0) );
    points.add( new Point_3(1,0,0) );
    Polygon_Vector polygons = new Polygon_Vector();
    Int_Vector polygon = new Int_Vector();
    polygon.reserve(3);
    polygon.add(0);
    polygon.add(1);
    polygon.add(2);
    polygons.add(polygon);
    CGAL_Polygon_mesh_processing.orient_polygon_soup(points, polygons);
  }

  public static void test_combinatorial_repairing_functions()
  {
    System.out.println("Testing combinarial repairing functions...");

    Polyhedron_3 P = new Polyhedron_3();
    P.make_triangle(new Point_3(0,0,0), new Point_3(1,0,0), new Point_3(0,1,0));
    P.make_triangle(new Point_3(1,0,0), new Point_3(0,0,0), new Point_3(0,-1,0));
    // stitch_borders
    CGAL_Polygon_mesh_processing.stitch_borders(P);

    P.clear();
    Polyhedron_3_Halfedge_handle h1 =
      P.make_triangle(new Point_3(0,0,0), new Point_3(1,0,0), new Point_3(0,1,0));
    Polyhedron_3_Halfedge_handle h2 =
      P.make_triangle(new Point_3(1,0,0), new Point_3(0,0,0), new Point_3(0,-1,0));
    h1=h1.opposite();
    while(!h1.vertex().point().equals(new Point_3(1,0,0))){ h1=h1.next();}
    h2=h2.opposite();
    while(!h2.vertex().point().equals(new Point_3(0,0,0))){ h2=h2.next();}
    LinkedList<Halfedge_pair> hpairs = new LinkedList<Halfedge_pair>();
    hpairs.add( new Halfedge_pair(h1,h2) );
    CGAL_Polygon_mesh_processing.stitch_borders(P, hpairs.iterator());

// polygon_soup_to_polygon_mesh
    P = new Polyhedron_3();
    Point_3_Vector points = new Point_3_Vector();
    points.reserve(3);
    points.add( new Point_3(0,0,0) );
    points.add( new Point_3(0,1,0) );
    points.add( new Point_3(1,0,0) );
    Polygon_Vector polygons = new Polygon_Vector();
    Int_Vector polygon = new Int_Vector();
    polygon.reserve(3);
    polygon.add(0);
    polygon.add(1);
    polygon.add(2);
    polygons.add(polygon);
    CGAL_Polygon_mesh_processing.polygon_soup_to_polygon_mesh(points, polygons, P);
    if (P.size_of_vertices()!=3)
      throw new AssertionError("Pb 0");
    P = new Polyhedron_3();
    double [] pt_array = {0,0,0,0,1,0,1,0,0};
    int [] id_array = {0,1,2};
    CGAL_Polygon_mesh_processing.polygon_soup_to_polygon_mesh(pt_array, id_array, P);
    if (P.size_of_vertices()!=3)
      throw new AssertionError("Pb 0 bis");
// remove_isolated_vertices (4.8)
    CGAL_Polygon_mesh_processing.remove_isolated_vertices(P);
  }

  public static void test_normal_computation_functions()
  {
    Polyhedron_3 P=get_poly();
    System.out.println("Testing normal computation functions...");
// compute_face_normal
    for(Polyhedron_3_Facet_handle fh : P.facets()){
      Vector_3 v = CGAL_Polygon_mesh_processing.compute_face_normal(fh, P);
      CGAL_Polygon_mesh_processing.compute_face_normal(fh, P, v);
    }
// compute_face_normals
    LinkedList<Vector_3> normals = new LinkedList<Vector_3>();
    CGAL_Polygon_mesh_processing.compute_face_normals(P, normals);
    if (normals.size()!=P.size_of_facets()) throw new AssertionError("Pb 5");
//  compute_vertex_normal
    for(Polyhedron_3_Vertex_handle vh : P.vertices()){
      Vector_3 v = CGAL_Polygon_mesh_processing.compute_vertex_normal(vh, P);
      CGAL_Polygon_mesh_processing.compute_vertex_normal(vh, P, v);
    }
//  compute_vertex_normals
    normals.clear();
    CGAL_Polygon_mesh_processing.compute_vertex_normals(P, normals);
    if (normals.size()!=P.size_of_vertices()) throw new AssertionError("Pb 6");
  }

  public static void test_connected_components_functions()
  {
    System.out.println("Testing connected components functions...");
    Polyhedron_3 P=get_poly();
// connected_component
    LinkedList<Polyhedron_3_Facet_handle> flist=new LinkedList<Polyhedron_3_Facet_handle>();
    for(Polyhedron_3_Facet_handle fh : P.facets())
      CGAL_Polygon_mesh_processing.connected_component(fh,P,flist);
// connected_components
    int[] cc_facet_ids=CGAL_Polygon_mesh_processing.connected_components(P);
    if (cc_facet_ids.length!=P.size_of_facets()) throw new AssertionError("Pb 2");
// keep_large_connected_components (4.8)
    CGAL_Polygon_mesh_processing.keep_large_connected_components(P,1);
// keep_largest_connected_components
    CGAL_Polygon_mesh_processing.keep_largest_connected_components(P,1);
// keep_connected_components
    for(Polyhedron_3_Facet_handle fh : P.facets())
      CGAL_Polygon_mesh_processing.keep_connected_components(P, flist.iterator());
    int[] cc_to_keep = new int[1];
    cc_to_keep[0]=0;
    CGAL_Polygon_mesh_processing.keep_connected_components(P, cc_to_keep, cc_facet_ids);
// remove_connected_components
    CGAL_Polygon_mesh_processing.remove_connected_components(P, flist.iterator());
    if (!P.empty()) throw new AssertionError("Pb 3");
    P=get_poly();
    CGAL_Polygon_mesh_processing.remove_connected_components(P, cc_to_keep, cc_facet_ids);
    if (!P.empty()) throw new AssertionError("Pb 4");
  }

  public static void test_geometric_measure_functions()
  {
    System.out.println("Testing geometric measure functions...");
// face_area (4.8)
    Polyhedron_3 P=get_poly();
    for(Polyhedron_3_Facet_handle fh : P.facets())
      CGAL_Polygon_mesh_processing.face_area(fh,P);
// area (4.8)
    LinkedList<Polyhedron_3_Facet_handle> flist = new LinkedList<Polyhedron_3_Facet_handle>();
    for (Polyhedron_3_Facet_handle fh : P.facets())
      flist.add(fh.clone());
    CGAL_Polygon_mesh_processing.area(flist.iterator(),P);
    CGAL_Polygon_mesh_processing.area(P);
// volume (4.8)
    CGAL_Polygon_mesh_processing.volume(P);
// edge_length (4.8)
    for(Polyhedron_3_Halfedge_handle hh : P.halfedges())
      CGAL_Polygon_mesh_processing.edge_length(hh,P);
// face_border_length (4.8)
    for(Polyhedron_3_Halfedge_handle hh : P.halfedges())
      CGAL_Polygon_mesh_processing.face_border_length(hh,P);
  }

  public static void test_miscellaneous_functions()
  {
    System.out.println("Testing miscellaneous functions...");
    Polyhedron_3 P=get_poly();
// bbox_3 (4.8)
    CGAL_Polygon_mesh_processing.bbox_3(P);
    LinkedList<Polyhedron_3_Halfedge_handle> hlist = new LinkedList<Polyhedron_3_Halfedge_handle>();
// border_halfedges (4.8)
    LinkedList<Polyhedron_3_Facet_handle> flist = new LinkedList<Polyhedron_3_Facet_handle>();
    for (Polyhedron_3_Facet_handle fh : P.facets()){
      flist.add(fh.clone());
      break;
    }
    CGAL_Polygon_mesh_processing.border_halfedges(flist.iterator(), P, hlist);
    if (hlist.size()!=3)
      throw new AssertionError("Pb 1");
  }

  public static void test_polygon_mesh_slicer()
  {
    System.out.println("Testing Polygon_mesh_slicer...");
    Polyhedron_3 P=get_poly();
    Polygon_mesh_slicer slicer = new Polygon_mesh_slicer(P);
    Polylines slice = new Polylines();
    slicer.slice(new Plane_3(1,0,0,-0.5), slice);
    if (slice.size()!=1) throw new AssertionError("Incorrect size");
    if (slice.get(0).size()==0) throw new AssertionError("no points created");
  }

  public static void test_side_of_triangle_mesh()
  {
    System.out.println("Testing Side_of_triangle_mesh...");
    Polyhedron_3 P=get_poly();
    Side_of_triangle_mesh f = new Side_of_triangle_mesh(P);
    if (f.bounded_side(new Point_3(0.25,0.25,0.25))!=Bounded_side.ON_BOUNDED_SIDE )
      throw new AssertionError("Pt should be on bounded side");
    if (f.bounded_side(new Point_3(0,0,0))!=Bounded_side.ON_BOUNDARY )
      throw new AssertionError("Pt should be on boundary");
    if (f.bounded_side(new Point_3(4,0,0))!=Bounded_side.ON_UNBOUNDED_SIDE )
      throw new AssertionError("Pt should be on unbounded side");
  }

  public static void main(String arg[]){
    test_meshing_functions();
    test_hole_filling_functions();
    test_predicate_functions();
    test_orientation_functions();
    test_combinatorial_repairing_functions();
    test_normal_computation_functions();
    test_connected_components_functions();
    test_geometric_measure_functions();
    test_miscellaneous_functions();
    test_polygon_mesh_slicer();
    test_side_of_triangle_mesh();
  }
}
