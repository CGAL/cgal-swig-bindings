import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Mesh_3.Mesh_3_Complex_3_in_triangulation_3;
import CGAL.Mesh_3.CGAL_Mesh_3;
import CGAL.Mesh_3.Mesh_optimization_return_code;
import CGAL.Mesh_3.Polyhedral_mesh_domain_3;
import CGAL.Mesh_3.Mesh_3_parameters;
import CGAL.Mesh_3.Default_mesh_criteria;
import CGAL.Mesh_3.User_mesh_criteria;
import CGAL.Mesh_3.Cell_predicate;
import CGAL.Mesh_3.Facet_predicate;
import java.util.LinkedList;

public class test_mesh_3 {
  public static void main(String arg[]){
    Polyhedron_3 poly=new Polyhedron_3("../data/elephant.off");
    Mesh_3_parameters params=new Mesh_3_parameters();
    Polyhedral_mesh_domain_3 domain= new Polyhedral_mesh_domain_3(poly);
    Mesh3CellCriteria cell_pred_base=new Mesh3CellCriteria();
    Mesh3FacetCriteria facet_pred_base=new Mesh3FacetCriteria();
    Cell_predicate cell_pred =new Cell_predicate(cell_pred_base,"evaluate","CGAL/Mesh_3/Mesh_3_regular_triangulation_3_Cell_handle","CGAL/Mesh_3/Mesh_3_Badness");
    Facet_predicate facet_pred =new Facet_predicate(facet_pred_base,"evaluate","CGAL/Mesh_3/Mesh_3_regular_triangulation_3_Facet","CGAL/Mesh_3/Mesh_3_Badness");
    User_mesh_criteria criteria = new  User_mesh_criteria(cell_pred,facet_pred);
    
    System.out.println("Make initial mesh...");
    
    Mesh_3_Complex_3_in_triangulation_3 res=
      CGAL_Mesh_3.make_mesh_3(domain,criteria,params);
    System.out.println("Done");
    res.output_to_medit("/tmp/medit_out.mesh");    

    System.out.println("Refining mesh...");
    Default_mesh_criteria new_criteria = new Default_mesh_criteria();
    new_criteria.cell_radius_edge_ratio(3).cell_size(0.03);

    // Mesh refinement
    CGAL_Mesh_3.refine_mesh_3(res, domain, new_criteria,params);
    
    System.out.println("Done");
    res.output_to_medit("/tmp/medit_out_ref.mesh");
  }
};