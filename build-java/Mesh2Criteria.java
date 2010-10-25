import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle;
import CGAL.Mesh_2.Face_badness;


public class Mesh2Criteria {

  public Face_badness evaluate(Object obj)
  {
    System.out.println(".....Call 1...");
    return Face_badness.NOT_BAD;
  }

  public Face_badness evaluate(Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle fh,Object obj)
  {
    System.out.println(".....Call 2...");
    obj=new Object();
    return Face_badness.NOT_BAD;
  }
  
}