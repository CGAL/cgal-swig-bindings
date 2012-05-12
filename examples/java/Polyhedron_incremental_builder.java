import CGAL.Kernel.Point_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_modifier;
import CGAL.Polyhedron_3.Modifier_mode;


public class Polyhedron_incremental_builder {
  public static void main(String arg[]){
    //declare a modifier interfacing the incremental_builder
    Polyhedron_modifier m = new Polyhedron_modifier();

    //define a triangle
    m.begin_surface(3,1);
    m.add_vertex(new Point_3(0,0,0));
    m.add_vertex(new Point_3(0,1,0));
    m.add_vertex(new Point_3(1,0.5,0));
    m.begin_facet();
    m.add_vertex_to_facet(0);
    m.add_vertex_to_facet(1);
    m.add_vertex_to_facet(2);
    m.end_facet();


    Polyhedron_3 P = new Polyhedron_3();
    //create the triangle in P
    P.delegate(m);
    System.out.println("(v,f,e) = "+P.size_of_vertices()+" "+P.size_of_facets()+" "+P.size_of_halfedges()/2);
    
    //clear the modifier
    m.clear();

    //define another triangle, reusing vertices in the polyhedron
    m.begin_surface(1,1,0,Modifier_mode.ABSOLUTE_INDEXING);
    m.add_vertex(new Point_3(-1,0.5,0));
    m.begin_facet();
    m.add_vertex_to_facet(1);
    m.add_vertex_to_facet(0);
    m.add_vertex_to_facet(3);
    m.end_facet();

    //append a triangle incident to the existing one
    P.delegate(m);
    System.out.println("(v,f,e) = "+P.size_of_vertices()+" "+P.size_of_facets()+" "+P.size_of_halfedges()/2);
    if (! P.is_valid() )
      throw new AssertionError("Polyhedron is not_valid");
    
  }
    
};
