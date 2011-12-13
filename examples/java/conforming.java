import CGAL.Kernel.Point_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2_Vertex_handle;
import CGAL.Mesh_2.CGAL_Mesh_2;


public class conforming {
  public static void main(String arg[]){
    Constrained_Delaunay_triangulation_2 cdt=new Constrained_Delaunay_triangulation_2();

    // construct a constrained triangulation
    Constrained_Delaunay_triangulation_2_Vertex_handle va = cdt.insert(new Point_2( 5., 5.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vb = cdt.insert(new Point_2(-5., 5.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vc = cdt.insert(new Point_2( 4., 3.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vd = cdt.insert(new Point_2( 5.,-5.));
    Constrained_Delaunay_triangulation_2_Vertex_handle ve = cdt.insert(new Point_2( 6., 6.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vf = cdt.insert(new Point_2(-6., 6.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vg = cdt.insert(new Point_2(-6.,-6.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vh = cdt.insert(new Point_2( 6.,-6.));

    cdt.insert_constraint(va,vb);
    cdt.insert_constraint(vb,vc);
    cdt.insert_constraint(vc,vd);
    cdt.insert_constraint(vd,va);
    cdt.insert_constraint(ve,vf);
    cdt.insert_constraint(vf,vg);
    cdt.insert_constraint(vg,vh);
    cdt.insert_constraint(vh,ve);

    System.out.println("Number of vertices before: "+ cdt.number_of_vertices());

    // make it conforming Delaunay
    CGAL_Mesh_2.make_conforming_Delaunay_2(cdt);

    System.out.println("Number of vertices after make_conforming_Delaunay_2: "+cdt.number_of_vertices());

    // then make it conforming Gabriel
    CGAL_Mesh_2.make_conforming_Gabriel_2(cdt);

    System.out.println("Number of vertices after make_conforming_Gabriel_2: "+cdt.number_of_vertices() );
  }
}
