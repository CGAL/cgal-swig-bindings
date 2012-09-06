import CGAL.Kernel.Point_2;
import CGAL.Voronoi_diagram_2.Voronoi_diagram_2;
import CGAL.Voronoi_diagram_2.Voronoi_diagram_2_Halfedge_handle;
import CGAL.Voronoi_diagram_2.Voronoi_diagram_2_Vertex_handle;
import CGAL.Voronoi_diagram_2.Voronoi_diagram_2_Face_handle;
import CGAL.Voronoi_diagram_2.Voronoi_diagram_2_Ccb_halfedge_circulator;
import CGAL.Voronoi_diagram_2.Voronoi_diagram_2_Locate_result;
import java.util.Vector;


public class vd_2_point_location {

  public static void print_endpoint(Voronoi_diagram_2_Halfedge_handle e, boolean is_src) {
    System.out.print( "\t");
    if ( is_src ) {
      if ( e.has_source() )      System.out.println(e.source().point());
      else      System.out.println("point at infinity");
    } else {
      if ( e.has_target() )      System.out.println(e.target().point());
      else      System.out.println("point at infinity");
    }
  } 
  
  public static void main(String arg[]){
    Vector<Point_2> points = new Vector<Point_2>(7);
    points.add( new Point_2(0,0) );
    points.add( new Point_2(100,0) );
    points.add( new Point_2(100,100) );
    points.add( new Point_2(0,100) );
    points.add( new Point_2(200,0) );
    points.add( new Point_2(300,0) );
    points.add( new Point_2(350,0) );
    
    Voronoi_diagram_2 vd = new Voronoi_diagram_2(points.iterator());

    if ( ! vd.is_valid() ) throw new AssertionError("ERROR!!!!");

    
    Vector<Point_2> queries = new Vector<Point_2>(11);
    queries.add( new Point_2(0,0) );
    queries.add( new Point_2(50,50) );
    queries.add( new Point_2(0,50) );
    queries.add( new Point_2(50,40) );
    queries.add( new Point_2(10,20) );
    queries.add( new Point_2(150,0) );
    queries.add( new Point_2(150,200) );
    queries.add( new Point_2(200,0) );
    queries.add( new Point_2(250,0) );
    queries.add( new Point_2(300,0) );
    queries.add( new Point_2(325,10) );

    for( Point_2 p : queries)
    {
      System.out.print("Query point (");
      System.out.print(p);
      System.out.print(") lies on a Voronoi ");

      Voronoi_diagram_2_Locate_result lr = vd.locate(p);
      if ( lr.is_vertex_handle() ) {
        Voronoi_diagram_2_Vertex_handle v=lr.get_vertex_handle();
        System.out.println("vertex.");
        System.out.println("The Voronoi vertex is:\t");
        System.out.println(v.point());
      } else if ( lr.is_halfedge_handle() ) {
        Voronoi_diagram_2_Halfedge_handle e=lr.get_halfedge_handle();
        System.out.println("edge.");
        System.out.println("The source and target vertices of the Voronoi edge are:");
        print_endpoint(e, true);
        print_endpoint(e, false);
      } else if ( lr.is_face_handle() ) {
        Voronoi_diagram_2_Face_handle f=lr.get_face_handle();
        System.out.println("face.");
        System.out.println("The vertices of the Voronoi face are (in counterclockwise order):");
        Voronoi_diagram_2_Ccb_halfedge_circulator ec_start = f.outer_ccb();
        
        if (ec_start.hasNext()) {
          Voronoi_diagram_2_Halfedge_handle done = ec_start.next().clone();
          Voronoi_diagram_2_Halfedge_handle iter=null;
          do {
            iter=ec_start.next();
            print_endpoint(iter, false);  
          }while(!iter.equals(done));
        }  
        System.out.println();
      }
    }
  }
}
