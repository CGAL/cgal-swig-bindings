import CGAL.Mesh_2.CGAL_Mesh_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2_Vertex_handle;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle;
import CGAL.Mesh_2.Constrained_Delaunay_triangulation_conformer_2;
import CGAL.Mesh_2.Delaunay_mesh_size_criteria_2;
import CGAL.Mesh_2.Default_Delaunay_mesher_2;
import CGAL.Mesh_2.User_mesh_criteria_simple_2;
import CGAL.Mesh_2.Mesh_2_predicate;
import java.util.LinkedList;
import CGAL.Kernel.Point_2;
import CGAL.Mesh_2.Face_badness;

public class test_mesh_2 {
  public static void test_conforming()
  {
    Constrained_Delaunay_triangulation_2 cdt=new Constrained_Delaunay_triangulation_2();
      
    Constrained_Delaunay_triangulation_2_Vertex_handle
      va = cdt.insert(new Point_2( 5., 5.)),
      vb = cdt.insert(new Point_2(-5., 5.)),
      vc = cdt.insert(new Point_2( 4., 3.)),
      vd = cdt.insert(new Point_2( 5.,-5.)),
      ve = cdt.insert(new Point_2( 6., 6.)),
      vf = cdt.insert(new Point_2(-6., 6.)),
      vg = cdt.insert(new Point_2(-6.,-6.)),
      vh = cdt.insert(new Point_2( 6.,-6.));

    cdt.insert_constraint(va,vb);
    cdt.insert_constraint(vb,vc);
    cdt.insert_constraint(vc,vd);
    cdt.insert_constraint(vd,va);
    cdt.insert_constraint(ve,vf);
    cdt.insert_constraint(vf,vg);
    cdt.insert_constraint(vg,vh);
    cdt.insert_constraint(vh,ve);

    System.out.println("Number of vertices before: "+cdt.number_of_vertices());

    // make it conforming Delaunay
    CGAL_Mesh_2.make_conforming_Delaunay_2(cdt);
    

    System.out.println("Number of vertices after make_conforming_Delaunay_2: "+cdt.number_of_vertices());

    // then make it conforming Gabriel
    CGAL_Mesh_2.make_conforming_Gabriel_2(cdt);

    System.out.println("Number of vertices after make_conforming_Gabriel_2: "+cdt.number_of_vertices());
    Constrained_Delaunay_triangulation_conformer_2 conf= new Constrained_Delaunay_triangulation_conformer_2(cdt);
    if (! conf.is_conforming_Gabriel() ) throw new AssertionError("oops");
    if (! conf.is_conforming_Delaunay() ) throw new AssertionError("oops");    
  }

  public static void test_meshing(){

    //test meshing
      
    Mesh_2_Constrained_Delaunay_triangulation_2 cdt=new Mesh_2_Constrained_Delaunay_triangulation_2();
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle va = cdt.insert(new Point_2(2,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vb = cdt.insert(new Point_2(0,2));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vc = cdt.insert(new Point_2(-2,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vd = cdt.insert(new Point_2(0,-2));

    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);

    va = cdt.insert(new Point_2(3,3));
    vb = cdt.insert(new Point_2(-3,3));
    vc = cdt.insert(new Point_2(-3,-3));
    vd = cdt.insert(new Point_2(3,0-3));

    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);

    LinkedList<Point_2> list_of_seeds=new LinkedList<Point_2>();

    list_of_seeds.add(new Point_2(0, 0));

    System.out.println("Number of vertices: " + cdt.number_of_vertices() );

    System.out.println("Meshing the domain...");
    CGAL_Mesh_2.refine_Delaunay_mesh_2(cdt, list_of_seeds.iterator(),new Delaunay_mesh_size_criteria_2());

    System.out.println("Number of vertices: " + cdt.number_of_vertices() );
    System.out.println("Number of finite faces: " + cdt.number_of_faces() );
    int mesh_faces_counter = 0;
    for(Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle f : cdt.finite_faces() )
    {
      if(f.is_in_domain()) ++mesh_faces_counter;
    }
    System.out.println("Number of faces in the mesh domain: " + mesh_faces_counter );

    Mesh2Criteria mpred_base= new Mesh2Criteria();
    Mesh_2_predicate mpred=new Mesh_2_predicate(mpred_base,"evaluate","CGAL/Mesh_2/Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle","CGAL/Mesh_2/Quality_pair","CGAL/Mesh_2/Face_badness");
    //~ CGAL_Mesh_2.refine_Delaunay_mesh_2(cdt, list_of_seeds.iterator(),new User_mesh_criteria_simple_2(mpred));
    CGAL_Mesh_2.refine_Delaunay_mesh_2(cdt,new User_mesh_criteria_simple_2(mpred));
  }
  public static void test_mesh_class()
  {
    Mesh_2_Constrained_Delaunay_triangulation_2 cdt=new Mesh_2_Constrained_Delaunay_triangulation_2();

    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle va = cdt.insert(new Point_2(-4,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vb = cdt.insert(new Point_2(0,-1));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vc = cdt.insert(new Point_2(4,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vd = cdt.insert(new Point_2(0,1));
    cdt.insert(new Point_2(2, 0.6));

    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);

    System.out.println("Number of vertices: " + cdt.number_of_vertices() );

    System.out.println("Meshing the triangulation with default criterias...");

    Default_Delaunay_mesher_2 mesher=new Default_Delaunay_mesher_2(cdt);
    mesher.refine_mesh();

    System.out.println("Number of vertices: " + cdt.number_of_vertices() );

    System.out.println("Meshing with new criterias..." );
    // 0.125 is the default shape bound. It corresponds to abound 20.6 degree.
    // 0.5 is the upper bound on the length of the longuest edge.
    // See reference manual for Delaunay_mesh_size_traits_2<K>.
    mesher.set_criteria(new Delaunay_mesh_size_criteria_2(0.125, 0.5));
    mesher.refine_mesh();

    System.out.println("Number of vertices: " + cdt.number_of_vertices() );
  }
  
  public static void main(String arg[]){
    test_conforming();
    test_meshing();
    test_mesh_class();
  }
};