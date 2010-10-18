import CGAL.Mesh_3.Mesh_3_regular_triangulation_3_Facet;
import CGAL.Mesh_3.Mesh_3_Badness;
import CGAL.Mesh_3.Mesh_3_Quality;

public class Mesh3FacetCriteria {

  public Mesh_3_Badness evaluate(Mesh_3_regular_triangulation_3_Facet f)
  {
    System.out.println("Inside facet evaluate");
    System.out.println(f.getFirst().vertex(0).point().x());
    System.out.println(f.getFirst().vertex(0).point().y());
    System.out.println(f.getFirst().vertex(0).point().z());
    //~ double d=ch.vertex(0).point().x()+ch.vertex(0).point().y()+ch.vertex(0).point().z();
    //~ Mesh_3_Quality q=new Mesh_3_Quality(3,d);
    Mesh_3_Badness bad=new Mesh_3_Badness();
    return bad;
  }
  
}