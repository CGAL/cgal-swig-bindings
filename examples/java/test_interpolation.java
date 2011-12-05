import CGAL.Triangulation_2.Delaunay_triangulation_2;
import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge;
import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle;
import CGAL.Kernel.Point_2;
import CGAL.Interpolation.CGAL_Interpolation;
import CGAL.Interpolation.Point_2_and_double;
import CGAL.Interpolation.Double_and_bool;
import CGAL.Interpolation.Data_access_double_2;
import CGAL.Interpolation.Data_access_vector_2;
import java.util.LinkedList;

public class test_interpolation {
  
  public static void test_linear_interpolation(){
    Delaunay_triangulation_2 dt=new Delaunay_triangulation_2();
    Data_access_double_2 function_values=new Data_access_double_2();

    double a=0.25;
    double bx=1.3;
    double by=-0.7;

    for (int y=0 ; y<3 ; y++)
      for (int x=0 ; x<3 ; x++){
        Point_2 p=new Point_2(x,y);
        dt.insert(p);
        function_values.set(p,a + bx* x+ by*y);
    }
    //coordinate computation
    Point_2 p=new Point_2(1.3,0.34);
    LinkedList<Point_2_and_double> coords=new LinkedList<Point_2_and_double>();
    double norm =
    CGAL_Interpolation.natural_neighbor_coordinates_2
    (dt, p,coords).getFirst();

    double res =  CGAL_Interpolation.linear_interpolation(coords.iterator(),norm,function_values);

    System.out.println( "   Tested interpolation on " + p + " interpolation: "
        + res + " exact: " + (a + bx* p.x()+ by* p.y()) );
  }
  
  public static void test_sibson_gradient()
  {
    Delaunay_triangulation_2 dt=new Delaunay_triangulation_2();
    Data_access_double_2 function_values=new Data_access_double_2();
    Data_access_vector_2 function_gradients=new Data_access_vector_2();

    //parameters for spherical function:
    double a=0.25;
    double bx=1.3; 
    double by=-0.7;
    double c=0.2;
    for (int y=0 ; y<4 ; y++)
      for (int x=0 ; x<4 ; x++){
        Point_2 p= new Point_2(x,y);
        dt.insert(p);
        function_values.set(p,a + bx* x+ by*y + c*(x*x+y*y));
      }
      CGAL_Interpolation.sibson_gradient_fitting_nn_2(dt,function_gradients,function_values);

      //coordiante computation
      Point_2 p=new Point_2(1.6,1.4);
      LinkedList<Point_2_and_double> coords=new LinkedList<Point_2_and_double>();
      double norm = CGAL_Interpolation.natural_neighbor_coordinates_2(dt, p,coords).getFirst();

      //Sibson interpolant: version without sqrt:
      Double_and_bool res =
      CGAL_Interpolation.sibson_c1_interpolation_square(coords.iterator(),norm,p,function_values,function_gradients);
      if(res.getSecond())
        System.out.println( "   Tested interpolation on " + p
                  + " interpolation: " + res.getFirst() + " exact: "
                  + (a + bx * p.x()+ by * p.y()+ c*(p.x()*p.x()+p.y()*p.y())) );
      else{
        System.out.println( "C^1 Interpolation not successful.");
        System.out.println( " not all function_gradients are provided.");
        System.out.println( " You may resort to linear interpolation.");
      }
  }
  
  
  public static void main(String arg[])
  {
    System.out.println("Testing interpolation");
    
    Delaunay_triangulation_2 dt= new Delaunay_triangulation_2();
    
    dt.insert(new Point_2(0,0));
    dt.insert(new Point_2(0,1));
    dt.insert(new Point_2(1,0));
    dt.insert(new Point_2(1.1,1.1));
    
    Point_2 p=new Point_2(0.5,0.5);
    
    LinkedList<Point_2_and_double> lst=new LinkedList<Point_2_and_double>();
    
    Double_and_bool db=CGAL_Interpolation.natural_neighbor_coordinates_2(dt,p,lst);
    
    if (!db.getSecond())
      throw new AssertionError("Point outside Convex hull");
    
    LinkedList<Delaunay_triangulation_2_Edge> edge_list=new LinkedList<Delaunay_triangulation_2_Edge>();
    Delaunay_triangulation_2_Face_handle fh = dt.finite_faces().next();
    
    LinkedList<Delaunay_triangulation_2_Face_handle> face_list=new LinkedList<Delaunay_triangulation_2_Face_handle>();
    dt.get_conflicts_and_boundary(p,face_list,edge_list,fh);
    
    CGAL_Interpolation.natural_neighbor_coordinates_2(dt,p,lst,edge_list.iterator());
    
    for (Point_2_and_double pd : lst)
      System.out.println(pd.getFirst()+" "+pd.getSecond()/db.getFirst());    
    
    test_linear_interpolation();
    test_sibson_gradient();
  }
}
