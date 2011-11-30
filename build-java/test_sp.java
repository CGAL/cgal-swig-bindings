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

import CGAL.Spatial_searching.Point_with_info_3;
import CGAL.Spatial_searching.Orthogonal_k_neighbor_search_tree_with_info_3;
import CGAL.Spatial_searching.Orthogonal_k_neighbor_search_with_info_3;
import CGAL.Spatial_searching.Point_with_info_with_transformed_distance_3;
import CGAL.Java.JavaData;
import java.util.LinkedList;



public class test_sp {
  
  public static void test_2d()
  {
    System.out.println("Test 2D");
    
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
    tree2.insert(lst.iterator());
    K_neighbor_search_2 search2 = new K_neighbor_search_2(tree2,new Point_2(0,0),3);
    for (Point_with_transformed_distance_2 p : search2.iterator())
      System.out.println(p.getFirst()+" "+p.getSecond());        
  }
  
  public static void test_3d()
  {
    System.out.println("Test 3D");
    LinkedList<Point_3> lst=new LinkedList<Point_3>();
    lst.add( new Point_3(0,0,1) );
    lst.add( new Point_3(0,4,2) );
    lst.add( new Point_3(44,0,3) );
    lst.add( new Point_3(44,5,4) );
    lst.add( new Point_3(444,51,5) );
    lst.add( new Point_3(14,1,7) );    
    
    Orthogonal_incremental_neighbor_search_tree_3 tree=new Orthogonal_incremental_neighbor_search_tree_3(lst.iterator());
    
   // Orthogonal_incremental_neighbor_search_3 search = new Orthogonal_incremental_neighbor_search_3(tree,new Point_3(0,0,0));
    Orthogonal_incremental_neighbor_search_3 search = new Orthogonal_incremental_neighbor_search_3(new Orthogonal_incremental_neighbor_search_tree_3(lst.iterator()),new Point_3(0,0,0));
    
    System.gc();
    System.runFinalization();
    try{
      Thread.sleep(100);
    }
    catch(InterruptedException e)
    {
    }
    
    for (Point_with_transformed_distance_3 p : search.iterator())
      System.out.println(p.getFirst()+" "+p.getSecond());    
    
  }
  
  public static void test_with_info_3()
  {
    System.out.println("Test with info");
    LinkedList<Point_with_info_3> lst=new LinkedList<Point_with_info_3>();
    lst.add( new Point_with_info_3( new Point_3(0,0,1),    new JavaData(new Integer(0)) ));
    lst.add( new Point_with_info_3( new Point_3(0,4,2),    new JavaData(new Integer(1)) ));
    lst.add( new Point_with_info_3( new Point_3(44,0,3),   new JavaData(new Integer(2)) ));
    lst.add( new Point_with_info_3( new Point_3(44,5,4),   new JavaData(new Integer(3)) ));
    lst.add( new Point_with_info_3( new Point_3(444,51,5), new JavaData(new Integer(4)) ));
    lst.add( new Point_with_info_3( new Point_3(14,1,7),   new JavaData(new Integer(5)) ));    
    
    Orthogonal_k_neighbor_search_tree_with_info_3 tree=new Orthogonal_k_neighbor_search_tree_with_info_3(lst.iterator());
    
    Orthogonal_k_neighbor_search_with_info_3 search = new Orthogonal_k_neighbor_search_with_info_3(tree,new Point_3(0,0,0),6);
    
    for (Point_with_info_with_transformed_distance_3 p : search.iterator())
      System.out.println("#"+ (Integer) p.getFirst().getSecond().get_data() +" "+p.getFirst().getFirst()+" "+p.getSecond());    
        
  }
  
  public static void main(String arg[]){
    test_2d();
    test_3d();
    test_with_info_3();
    

  }
  
}