import CGAL.Kernel.Point_2;
import CGAL.HalfedgeDS.HalfedgeDS;
import CGAL.HalfedgeDS.HalfedgeDS_modifier;
import CGAL.HalfedgeDS.HalfedgeDS_decorator;
import CGAL.HalfedgeDS.Modifier_mode;


public class hds_incremental_builder {
  public static void main(String arg[]){
    //declare a modifier interfacing the incremental_builder
    HalfedgeDS_modifier m = new HalfedgeDS_modifier();

    //define a triangle
    m.begin_surface(3,1);
    m.add_vertex(new Point_2(0,0));
    m.add_vertex(new Point_2(0,1));
    m.add_vertex(new Point_2(1,0.5));
    m.begin_facet();
    m.add_vertex_to_facet(0);
    m.add_vertex_to_facet(1);
    m.add_vertex_to_facet(2);
    m.end_facet();


    HalfedgeDS hds = new HalfedgeDS();
    //create the triangle in hds
    hds.delegate(m);
    System.out.println("(v,f,e) = "+hds.size_of_vertices()+" "+hds.size_of_faces()+" "+hds.size_of_halfedges()/2);
    
    //clear the modifier
    m.clear();

    //define another triangle, reusing vertices in the polyhedron
    m.begin_surface(1,1,0,Modifier_mode.ABSOLUTE_INDEXING);
    m.add_vertex(new Point_2(-1,0.5));
    m.begin_facet();
    m.add_vertex_to_facet(1);
    m.add_vertex_to_facet(0);
    m.add_vertex_to_facet(3);
    m.end_facet();

    //append a triangle incident to the existing one
    hds.delegate(m);
    System.out.println("(v,f,e) = "+hds.size_of_vertices()+" "+hds.size_of_faces()+" "+hds.size_of_halfedges()/2);

    HalfedgeDS_decorator decorator = new HalfedgeDS_decorator(hds);

    if (! decorator.is_valid() )
      throw new AssertionError("HDS is not_valid");

  }
    
};
