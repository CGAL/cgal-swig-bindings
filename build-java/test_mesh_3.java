import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Mesh_3.Mesh_3_Complex_3_in_triangulation_3;
import CGAL.Mesh_3.CGAL_Mesh_3;
import CGAL.Mesh_3.Mesh_optimization_return_code;
import CGAL.Mesh_3.Polyhedral_mesh_domain_3;
import CGAL.Mesh_3.Mesh_3_parameters;
import CGAL.Mesh_3.Default_mesh_criteria;
import CGAL.Mesh_3.User_mesh_criteria;
import CGAL.Mesh_3.Cell_predicate; //TEST
import java.util.LinkedList;

public class test_mesh_3 {
  public static void main(String arg[]){
    System.loadLibrary("CGAL_Mesh_3");
    
    Polyhedron_3 poly=new Polyhedron_3("elephant.off");
    Mesh_3_parameters params=new Mesh_3_parameters();
    Polyhedral_mesh_domain_3 domain= new Polyhedral_mesh_domain_3(poly);
    //Default_mesh_criteria criteria = new  Default_mesh_criteria(25,0.15,0.008,3);
    Mesh3CellCriteria pred=new Mesh3CellCriteria();//TEST
    Cell_predicate caller =new Cell_predicate(pred,"evaluate","LCGAL/Mesh_3/Mesh_3_regular_triangulation_3_Cell_handle;","LCGAL/Mesh_3/Mesh_3_Badness;");//TEST
    User_mesh_criteria criteria = new  User_mesh_criteria(caller);//TEST
    
    System.out.println("Make initial mesh...");
    
    Mesh_3_Complex_3_in_triangulation_3 res=
      CGAL_Mesh_3.make_mesh_3(domain,criteria,params);
    System.out.println("Done");
    res.output_to_medit("/tmp/medit_out.mesh");    

    System.out.println("Refining mesh...");
    Default_mesh_criteria new_criteria = new Default_mesh_criteria(0,0,0,3,0.03);

    // Mesh refinement
    CGAL_Mesh_3.refine_mesh_3(res, domain, new_criteria,params);
    
    System.out.println("Done");
    res.output_to_medit("/tmp/medit_out_ref.mesh");
  }
};