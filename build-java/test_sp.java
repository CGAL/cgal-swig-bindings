import CGAL.Kernel.Point_2;
import CGAL.Spatial_searching.Orthogonal_incremental_neighbor_search_tree_2;
import CGAL.Spatial_searching.Orthogonal_incremental_neighbor_search_2;
import CGAL.Spatial_searching.Point_with_transformed_distance_2;
import java.util.LinkedList;

public class test_sp {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Spatial_searching");
    
    Orthogonal_incremental_neighbor_search_tree_2 tree= new Orthogonal_incremental_neighbor_search_tree_2();
    LinkedList<Point_2> lst=new LinkedList<Point_2>();
    lst.add( new Point_2(0,0) );
    lst.add( new Point_2(0,4) );
    lst.add( new Point_2(44,0) );
    lst.add( new Point_2(44,5) );
    lst.add( new Point_2(444,51) );
    lst.add( new Point_2(14,1) );
      
    tree.insert_range(lst.iterator());
    
    for (Point_2 p : tree.iterator())
      System.out.println(p);
    Orthogonal_incremental_neighbor_search_2 search = new Orthogonal_incremental_neighbor_search_2(tree,new Point_2(0,0));
    
    for (Point_with_transformed_distance_2 p : search.iterator())
      System.out.println(p.getFirst()+" "+p.getSecond());
  }
  
}