import CGAL.Kernel.Point_2;
import CGAL.Kernel.Weighted_point_2;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2;
import CGAL.Triangulation_2.Regular_triangulation_2;
import CGAL.Triangulation_2.Delaunay_triangulation_2;
import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle;
import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle;
import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Vertex_handle;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Face_handle;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Edge;
import CGAL.Triangulation_2.Constraint;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Constraint;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2_Context;
import CGAL.Triangulation_2.Locate_type;
import CGAL.Kernel.Ref_int;
import CGAL.Triangulation_2.Ref_Locate_type_2;
import CGAL.Java.JavaData;
import java.util.Iterator;
import java.util.LinkedList;

public class test_t2 {
  public static void main(String arg[]){
    Locate_type lc=Locate_type.VERTEX;
    
    LinkedList<Constraint> cst_list=new LinkedList<Constraint>();
    cst_list.add(new Constraint(new Point_2(10,10),new Point_2(15,15)));
    cst_list.add(new Constraint(new Point_2(100,100),new Point_2(155,151)));
    cst_list.add(new Constraint(new Point_2(104,410),new Point_2(154,1514)));
    
    Constrained_Delaunay_triangulation_plus_2 t=new Constrained_Delaunay_triangulation_plus_2(cst_list.iterator());
    
    System.out.println("Nb vertices after insert_constraint_range "+t.number_of_vertices());    
      
    Point_2 [] array=new Point_2[4];
    array[0]=new Point_2(1,1);
    array[1]=new Point_2(1,4);
    array[2]=new Point_2(22,3);
    array[3]=new Point_2(142,34);
    
    LinkedList<Point_2> lst=new LinkedList<Point_2>();
    lst.add( array[0] );
    lst.add( array[1] );
    lst.add( array[2] );
    lst.add( array[3] );
    
    t.insert(lst.iterator());
    
    System.out.println("Nb vertices after insert_range "+t.number_of_vertices());
    
    LinkedList<Constrained_Delaunay_triangulation_plus_2_Edge> edge_list=new LinkedList<Constrained_Delaunay_triangulation_plus_2_Edge>();
    
    Constraint c=new Constraint(new Point_2(44,12),new Point_2(77,41));
    
    t.push_back(c);
    
    System.out.println("Nb vertices after push_back "+t.number_of_vertices());
    
    for (Constrained_Delaunay_triangulation_plus_2_Vertex_handle v : t.finite_vertices()){
      System.out.println(v.point());
      t.incident_constraints(v,edge_list);
    }
    
    System.out.println("Nb edges "+edge_list.size());
    
    
    
    Constrained_Delaunay_triangulation_plus_2_Context ctxt = 
      t.context( edge_list.getFirst().getFirst().vertex((edge_list.getFirst().getSecond()+1)%3),
                 edge_list.getFirst().getFirst().vertex((edge_list.getFirst().getSecond()+2)%3)
               );
    
    int vic=0;
    for (Constrained_Delaunay_triangulation_plus_2_Vertex_handle vh : ctxt.vertices())
      ++vic;
    System.out.println("Nb vertices in ctxt "+vic);
    int vic2=0;
    for (Constrained_Delaunay_triangulation_plus_2_Vertex_handle vh : ctxt.current())
      ++vic2;
    System.out.println("Nb vertices in current ctxt "+vic2);


    int nb_ctxt=0;
    for (Constrained_Delaunay_triangulation_plus_2_Context ictxt : 
          t.contexts( edge_list.getFirst().getFirst().vertex((edge_list.getFirst().getSecond()+1)%3),
                      edge_list.getFirst().getFirst().vertex((edge_list.getFirst().getSecond()+2)%3))
        )
      ++nb_ctxt;
    System.out.println("Nb contexts "+nb_ctxt);    
    
    int j=0;
    for (Constrained_Delaunay_triangulation_plus_2_Constraint cdtp_sc : t.subconstraints()){
      ++j;
      int k=0;
      for (Constrained_Delaunay_triangulation_plus_2_Vertex_handle vh : t.vertices_in_constraint(cdtp_sc.getFirst(),cdtp_sc.getSecond()) )
        ++k;
      System.out.println("Nb subvertices "+k);
    }    
    System.out.println("Nb subconstrained edges "+j);

   
    int i=0;
    for (Constrained_Delaunay_triangulation_plus_2_Constraint cdtp_c : t.constraints()){
      ++i;
    }
    System.out.println("Nb constrained edges "+i);
    
    
    System.out.println("Test setting a Integer to facets");
    double dbl=0.;
    for (Constrained_Delaunay_triangulation_plus_2_Face_handle fh : t.all_faces()){
      fh.info().set_data(new Double(dbl));
      dbl+=1.;
    }
    //check values are still the same
    dbl=0.;
    boolean ok=true;
    for (Constrained_Delaunay_triangulation_plus_2_Face_handle fh : t.all_faces()){
      Double stored=(Double) fh.info().get_data();
      if (! stored.equals(new Double(dbl)) ) ok=false;
      dbl+=1.;
    }
    
    if (ok) System.out.println("all "+dbl+" are OK");
    else    throw new AssertionError("ERROR!!!!");

    System.out.println("Test regular triangulation");
    LinkedList<Weighted_point_2> wlst=new LinkedList<Weighted_point_2>();
    wlst.add( new Weighted_point_2(array[0],34.) );
    wlst.add( new Weighted_point_2(array[1],35.) );
    wlst.add( new Weighted_point_2(array[2],31.) );
    wlst.add( new Weighted_point_2(array[3],30.) );
    wlst.add( new Weighted_point_2(new Point_2(21.9,3),0) );
    System.out.println("List size "+wlst.size());
    Regular_triangulation_2 rt=new Regular_triangulation_2();
    rt.insert(wlst.iterator());
    System.out.println("Nb vertices "+rt.number_of_vertices());
    int shv=0;
    for (Regular_triangulation_2_Vertex_handle rtvh : rt.hidden_vertices())
      ++shv;
    System.out.println("Nb hidden vertices: "+shv);
    
    
    System.out.println("Testing Delaunay triangulation 2 with info in vertices and faces");
    Delaunay_triangulation_2 dt2 = new Delaunay_triangulation_2();
    dt2.insert(lst.iterator());
    int k=0;
    for (Delaunay_triangulation_2_Vertex_handle vh : dt2.finite_vertices())
      vh.info().set_data(new Double(++k));
    for (Delaunay_triangulation_2_Vertex_handle vh : dt2.finite_vertices())
      System.out.println( vh.info().get_data() );

    for (Delaunay_triangulation_2_Face_handle fh : dt2.finite_faces())
      fh.info().set_data(new Double(++k));
    for (Delaunay_triangulation_2_Face_handle fh : dt2.finite_faces()){
      JavaData jd = new JavaData();
      fh.get_info(jd);
      System.out.println( jd.get_data() );
      jd.set_data(new Double(8888));
      fh.set_info(jd);
    }
    for (Delaunay_triangulation_2_Face_handle fh : dt2.finite_faces())
      System.out.println( fh.info().get_data() );

    Ref_Locate_type_2 loc = new Ref_Locate_type_2();
    Ref_int rint = new Ref_int();
    Delaunay_triangulation_2_Face_handle res =dt2.locate(array[0],loc,rint);
    if (loc.object()==Locate_type.VERTEX && res.vertex(rint.object()).point().equals(array[0])) System.out.println("Locate OK");
    else    throw new AssertionError("ERROR!!!!");
    
  }


}

