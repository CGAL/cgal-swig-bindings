import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.Kernel.Point_3;


public class polyhedron_prog_cube{
  
  public static Polyhedron_3_Halfedge_handle make_cube_3(Polyhedron_3 P){
    // appends a cube of size [0,1]^3 to the polyhedron P.
    assert P.is_valid();
    Polyhedron_3_Halfedge_handle h = P.make_tetrahedron( new Point_3( 1, 0, 0),
                                                         new Point_3( 0, 0, 1),
                                                         new Point_3( 0, 0, 0),
                                                         new Point_3( 0, 1, 0));
    Polyhedron_3_Halfedge_handle g = h.next().opposite().next();
    P.split_edge( h.next() );
    P.split_edge( g.next() );
    P.split_edge( g );
    h.next().vertex().set_point( new Point_3( 1, 0, 1) );
    g.next().vertex().set_point( new Point_3( 0, 1, 1) );
    g.opposite().vertex().set_point( new Point_3( 1, 1, 0) );
    Polyhedron_3_Halfedge_handle f = P.split_facet(g.next(),g.next().next().next());
    Polyhedron_3_Halfedge_handle e = P.split_edge(f);
    e.vertex().set_point( new Point_3( 1, 1, 1) );
    P.split_facet( e, f.next().next());
    assert P.is_valid();
    return h;
  }
  
  public static void main(String arg[]){
    Polyhedron_3 P=new Polyhedron_3();
    Polyhedron_3_Halfedge_handle h = make_cube_3(P);
    assert !P.is_tetrahedron(h);
  }
}
