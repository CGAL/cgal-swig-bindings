import CGAL.Kernel.Point_2;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Vertex_handle;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Edge;
import CGAL.Triangulation_2.Constraint;
import java.util.Iterator;
import java.util.LinkedList;

public class test_t2 {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Triangulation_2");

    Constrained_Delaunay_triangulation_plus_2 t=new Constrained_Delaunay_triangulation_plus_2();
      
    Point_2 [] array=new Point_2[4];
    array[0]=new Point_2(1,1);
    array[1]=new Point_2(1,4);
    array[2]=new Point_2(22,3);
    array[3]=new Point_2(142,34);
    
    LinkedList<Point_2> lst=new LinkedList<Point_2>();
    lst.add( array[0] );
    lst.add( array[1] );
    lst.add( array[2] );
    lst.add( array[3] );
    
    t.insert_range(lst.iterator());
      
    LinkedList<Constrained_Delaunay_triangulation_plus_2_Edge> edge_list=new LinkedList<Constrained_Delaunay_triangulation_plus_2_Edge>();
    
    Constraint c=new Constraint(new Point_2(44,12),new Point_2(77,41));
    
    t.push_back(c);
    
    for (Constrained_Delaunay_triangulation_plus_2_Vertex_handle v : t.finite_vertices()){
      System.out.println(v.point());
      t.incident_constraints(v,edge_list);
    }
    
    System.out.println("Nb edges "+edge_list.size());
    
    
    
  }


}
 