import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Mesh_3.Mesh_3_Complex_3_in_triangulation_3;
import CGAL.Mesh_3.CGAL_Mesh_3;
import CGAL.Mesh_3.Polyhedral_mesh_domain_3;
import CGAL.Mesh_3.Mesh_3_parameters;
import CGAL.Mesh_3.Default_mesh_criteria;


public class mesh_polyhedral_domain{
  public static void main(String arg[]){
    // Create input polyhedron
    Polyhedron_3 polyhedron=new Polyhedron_3("../data/elephant.off");

    // Create domain
    Polyhedral_mesh_domain_3 domain= new Polyhedral_mesh_domain_3(polyhedron);
    Mesh_3_parameters params=new Mesh_3_parameters();
    
    // Mesh criteria (no cell_size set)
    Default_mesh_criteria criteria = new  Default_mesh_criteria();
    criteria.facet_angle(25).facet_size(0.15).facet_distance(0.008).cell_radius_edge_ratio(3);
    // Mesh generation
    Mesh_3_Complex_3_in_triangulation_3 c3t3=CGAL_Mesh_3.make_mesh_3(domain,criteria,params);

    // Output
    c3t3.output_to_medit("out_1.mesh");

    // Set tetrahedron size (keep cell_radius_edge), ignore facets
    Default_mesh_criteria new_criteria = new Default_mesh_criteria();
    new_criteria.cell_radius_edge_ratio(3).cell_size(0.03);
    
    // Mesh refinement
    CGAL_Mesh_3.refine_mesh_3(c3t3, domain, new_criteria,params);

    // Output
    c3t3.output_to_medit("out_2.mesh");

  }
}
