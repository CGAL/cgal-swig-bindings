import CGAL.Mesh_3.Mesh_3_regular_triangulation_3_Cell_handle;
import CGAL.Mesh_3.Mesh_3_Badness;
import CGAL.Mesh_3.Mesh_3_Quality;

public class Mesh3CellCriteria {

  public Mesh_3_Badness evaluate(Mesh_3_regular_triangulation_3_Cell_handle ch)
  {
    System.out.println("Inside evaluate");
    System.out.println(ch.vertex(0).point().x());
    System.out.println(ch.vertex(0).point().y());
    System.out.println(ch.vertex(0).point().z());
    //~ double d=ch.vertex(0).point().x()+ch.vertex(0).point().y()+ch.vertex(0).point().z();
    //~ Mesh_3_Quality q=new Mesh_3_Quality(3,d);
    Mesh_3_Badness bad=new Mesh_3_Badness();
    return bad;
  }
  
}