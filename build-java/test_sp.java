import CGAL.Kernel.Point_2;
import CGAL.Kernel.Point_3;
import CGAL.Spatial_searching.Orthogonal_incremental_neighbor_search_tree_2;
import CGAL.Spatial_searching.Orthogonal_incremental_neighbor_search_2;
import CGAL.Spatial_searching.Orthogonal_incremental_neighbor_search_tree_3;
import CGAL.Spatial_searching.Orthogonal_incremental_neighbor_search_3;
import CGAL.Spatial_searching.K_neighbor_search_tree_2;
import CGAL.Spatial_searching.K_neighbor_search_2;
import CGAL.Spatial_searching.Point_with_transformed_distance_2;
import CGAL.Spatial_searching.Point_with_transformed_distance_3;
import CGAL.Spatial_searching.Fuzzy_sphere_2;
import CGAL.Spatial_searching.Fuzzy_iso_box_2;
import java.util.LinkedList;

public class test_sp {
  
  public static void test_2d()
  {
    LinkedList<Point_2> lst=new LinkedList<Point_2>();
    lst.add( new Point_2(0,0) );
    lst.add( new Point_2(0,4) );
    lst.add( new Point_2(44,0) );
    lst.add( new Point_2(44,5) );
    lst.add( new Point_2(444,51) );
    lst.add( new Point_2(14,1) );
      
    Orthogonal_incremental_neighbor_search_tree_2 tree= new Orthogonal_incremental_neighbor_search_tree_2(lst.iterator());
    
    for (Point_2 p : tree.iterator())
      System.out.println(p);
    Orthogonal_incremental_neighbor_search_2 search = new Orthogonal_incremental_neighbor_search_2(tree,new Point_2(0,0));
    
    for (Point_with_transformed_distance_2 p : search.iterator())
      System.out.println(p.getFirst()+" "+p.getSecond());
  
    LinkedList<Point_2> lst_search = new LinkedList<Point_2>();
    Fuzzy_sphere_2 fs = new Fuzzy_sphere_2(new Point_2(0,0),8);
    Fuzzy_iso_box_2 fb = new Fuzzy_iso_box_2(new Point_2(-4,-4),new Point_2(4,4.1));
    tree.search(lst_search,fs);
    System.out.println(lst_search.size());
    tree.search(lst_search,fb);
    System.out.println(lst_search.size());
    
    K_neighbor_search_tree_2 tree2= new K_neighbor_search_tree_2();
    tree2.insert_range(lst.iterator());
    K_neighbor_search_2 search2 = new K_neighbor_search_2(tree2,new Point_2(0,0),3);
    for (Point_with_transformed_distance_2 p : search2.iterator())
      System.out.println(p.getFirst()+" "+p.getSecond());        
  }
  
  public static void test_3d()
  {
    
    LinkedList<Point_3> lst=new LinkedList<Point_3>();
    lst.add( new Point_3(0,0,1) );
    lst.add( new Point_3(0,4,2) );
    lst.add( new Point_3(44,0,3) );
    lst.add( new Point_3(44,5,4) );
    lst.add( new Point_3(444,51,5) );
    lst.add( new Point_3(14,1,7) );    
    
    Orthogonal_incremental_neighbor_search_tree_3 tree=new Orthogonal_incremental_neighbor_search_tree_3(lst.iterator());
    
    Orthogonal_incremental_neighbor_search_3 search = new Orthogonal_incremental_neighbor_search_3(tree,new Point_3(0,0,0));
    
    for (Point_with_transformed_distance_3 p : search.iterator())
      System.out.println(p.getFirst()+" "+p.getSecond());    
    
  }
  
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Spatial_searching");
    test_2d();
    test_3d();
    

  }
  
}