import CGAL.Kernel.Point_3;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Triangulation_3.Delaunay_triangulation_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3_Vertex_handle;
import java.util.Iterator;
import java.util.LinkedList;

public class test {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Triangulation_3");

    Delaunay_triangulation_3 t=new Delaunay_triangulation_3();
    //~ t.insert(p);
      
    Point_3 [] array=new Point_3[4];
    array[0]=new Point_3(1,1,1);
    array[1]=new Point_3(1,4,3);
    array[2]=new Point_3(22,3,3);
    array[3]=new Point_3(142,3,34);

    LinkedList<Point_3> lst=new LinkedList<Point_3>();
    lst.add( array[0] );
    lst.add( array[1] );
    lst.add( array[2] );
    lst.add( array[3] );
    
    t.insert_range(lst.iterator());
    System.out.println("insert range OK");
    
    Iterator<Delaunay_triangulation_3_Vertex_handle> it=t.finite_vertices();
    //for (Point_3 pt : array){
    //  System.out.println(pt.getCPtr(pt));
    //  System.out.println(pt);
    //}
    
    for (Delaunay_triangulation_3_Vertex_handle v : t.finite_vertices())
      System.out.println(v.point());
    
    System.out.println(lst.size());

    for (Point_3 pti : lst)
      System.out.println(pti);
  
    
    LinkedList<Delaunay_triangulation_3_Vertex_handle> adj_vertices=new LinkedList<Delaunay_triangulation_3_Vertex_handle>();
    for (Delaunay_triangulation_3_Vertex_handle v : t.finite_vertices())
      t.adjacent_vertices(v,adj_vertices);
    System.out.println("Nb adjacent vertices "+adj_vertices.size());
    
    System.out.println("Squared distance");
    System.out.println(CGAL_Kernel.squared_distance(array[0],array[1]));
    //~ while (true){
      //~ t.test_outputit(lst);
      //~ lst.clear();
      //~ System.gc();
      //~ System.runFinalization();

    //~ }
  }


}
