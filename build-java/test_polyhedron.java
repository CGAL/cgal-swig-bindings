import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Java.JavaData;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Vertex_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Modifier_1;
import CGAL.Polyhedron_3.Polyhedron_3_Modifier_2;
import CGAL.Polyhedron_3.Polyhedron_3_Modifier_triangular_facets;
import CGAL.Polyhedron_3.Integer_triple;
import java.util.LinkedList;

public class test_polyhedron {
  public static void main(String arg[]){
    System.out.println("START");
    //~ Polyhedron_3 p=new Polyhedron_3("./elephant.off");
    Polyhedron_3 p=new Polyhedron_3();
    p.make_triangle();
      
    System.out.println(p.size_of_vertices());
    
    int h=0;
    for (Polyhedron_3_Halfedge_handle hh : p.halfedges()){
      hh.info().set_data(new Double(4));
      hh.set_id(5);
      ++h;
    }

    for (Polyhedron_3_Halfedge_handle hh : p.halfedges()){
      System.out.println((Double) hh.info().get_data());
      System.out.println(hh.id());
      ++h;
    }
    
    
    int v=0;
    for (Polyhedron_3_Vertex_handle hh : p.vertices()){
      hh.info().set_data(new Double(4));
      ++v;
    }
    int f=0;
    for (Polyhedron_3_Facet_handle hh : p.facets()){
      hh.info().set_data(new Double(4));
      ++f;
    }
    int e=0;
    for (Polyhedron_3_Halfedge_handle hh : p.edges())
      ++e;   

    int pt=0;
    for (Point_3 hh : p.points())
      ++pt;  

    int pl=0;
    //~ for (Plane_3 hh : p.planes())
      //~ ++pl; 
    
    System.out.println(v);
    System.out.println(f);
    System.out.println(h);
    System.out.println(e);
    System.out.println(pt);
    System.out.println(pl);
    
    System.out.println("clear");
    p.clear();
    Polyhedron_3_Modifier_1 modif=new Polyhedron_3_Modifier_1();
    p.delegate(modif.get_modifier());
    System.out.println(p.size_of_vertices());
    Polyhedron_3_Modifier_2 modif2=new Polyhedron_3_Modifier_2();
    p.delegate(modif2.get_modifier());   
    System.out.println(p.size_of_vertices());    
    
    //test with iterators
    LinkedList<Point_3> pt_list=new LinkedList<Point_3>();
    pt_list.add(new Point_3(10,10,10));
    pt_list.add(new Point_3(11,11,11));
    pt_list.add(new Point_3(11,11,54));
    pt_list.add(new Point_3(11,11,-54));
    LinkedList<Integer_triple> int_list=new LinkedList<Integer_triple>();
    int_list.add(new Integer_triple(0,1,2));
    int_list.add(new Integer_triple(1,0,3));
    
    Polyhedron_3_Modifier_triangular_facets modif3=new Polyhedron_3_Modifier_triangular_facets();
    modif3.set_modifier_data(pt_list.iterator(),int_list.iterator());
    p.delegate(modif3.get_modifier());   
    System.out.println(p.size_of_vertices()); 
    for (Polyhedron_3_Vertex_handle hh : p.vertices())
      System.out.println(hh.point()); 
  }
};
