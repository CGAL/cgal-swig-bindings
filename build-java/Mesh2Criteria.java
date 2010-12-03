import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle;
import CGAL.Mesh_2.Face_badness;
import CGAL.Mesh_2.Quality_pair;

public class Mesh2Criteria {

  public Face_badness evaluate(Quality_pair obj)
  {
    System.out.println(".....Call 1...");
    return Face_badness.NOT_BAD;
  }

  public Face_badness evaluate(Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle fh,Quality_pair obj)
  {
    System.out.println(".....Call 2...");
    obj=new Quality_pair();
    return Face_badness.NOT_BAD;
  }
 
}