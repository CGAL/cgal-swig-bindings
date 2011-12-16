import CGAL.Kernel.Point_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;
import CGAL.Triangulation_3.Delaunay_triangulation_3_Vertex_handle;
import CGAL.Triangulation_3.Locate_type;
import CGAL.Triangulation_3.Ref_Locate_type_3;
import CGAL.Kernel.Ref_int;
import java.util.LinkedList;
import java.util.Vector;


public class simple_triangulation_3 {
  public static void main(String arg[]){
    LinkedList<Point_3> L=new LinkedList<Point_3>();
    L.add( new Point_3(0,0,0) );
    L.add( new Point_3(1,0,0) );
    L.add( new Point_3(0,1,0) );
    
    Delaunay_triangulation_3 T= new Delaunay_triangulation_3(L.iterator());
    
    int n=T.number_of_vertices();

    Vector<Point_3> V=new Vector<Point_3>(3);
    V.add(  new Point_3(0,0,1) );
    V.add(  new Point_3(1,1,1) );
    V.add(  new Point_3(2,2,2) );

    n = n + T.insert(V.iterator());
    
    assert n==6;
    assert T.is_valid();

    Ref_Locate_type_3 lt=new Ref_Locate_type_3();
    Ref_int li=new Ref_int();
    Ref_int lj=new Ref_int();
    Point_3 p=new Point_3(0,0,0);
   
    Delaunay_triangulation_3_Cell_handle c = T.locate(p, lt, li, lj);
    assert lt.object() == Locate_type.VERTEX;
    assert c.vertex(li.object()).point().equals(p);
    
    
    Delaunay_triangulation_3_Vertex_handle v = c.vertex( (li.object()+1)&3 );
    Delaunay_triangulation_3_Cell_handle nc = c.neighbor(li.object());

    Ref_int nli=new Ref_int();
    assert nc.has_vertex( v, nli );

    T.write_to_file("output");

    Delaunay_triangulation_3 T1 = new Delaunay_triangulation_3();
    T1.read_from_file("output");

    assert T1.is_valid();
    assert T1.number_of_vertices() == T.number_of_vertices();
    assert T1.number_of_cells() == T.number_of_cells();
  }
}

