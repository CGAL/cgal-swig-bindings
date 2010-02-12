public class main {
  public static void main(String arg[]){
  System.loadLibrary("DT3");
  DT3_T t=new DT3_T();
    
  DT3_Vertex_handle v1=t.insert(new EPIC_Point_3(1,1,1));
  DT3_Vertex_handle v2=t.insert(new EPIC_Point_3(1,1,15),v1);
  DT3_Vertex_handle v3=t.insert(new EPIC_Point_3(154,11,5),v2.cell());
  DT3_Vertex_handle v4=t.insert(new EPIC_Point_3(14,0,45));
    
  Object o1=new Object();
  o1=(Object) new Double(4);
  System.out.println((Double) o1);
  //System.out.println( ((Double) v4.get_info()) );
    
  
  v4.set_info(o1);
  System.out.println( ((Double) v4.get_info()) );
  v4.set_info((Object) new Double(909));
  System.out.println( ((Double) v4.get_info()) );

  v4=t.move_point(v4,new EPIC_Point_3(14,0,46));
  t.remove(v4);
  
  v4=t.insert(new EPIC_Point_3(14,0,45));

  if ( v1.cell().index(v1) != v1.cell().vertex(v1.cell().index(v1)).cell().index(v1.cell().vertex(v1.cell().index(v1))) )
    System.out.println("Pb 0");
  DT3_Vertex_handle vi=t.infinite_vertex();
  DT3_Cell_handle ci=t.infinite_cell();
  
  if (!t.is_infinite(vi) || !t.is_infinite(ci)) System.out.println("Pb 1");
  
  System.out.println(t.dimension());
  System.out.println(t.number_of_vertices());
  System.out.println(t.number_of_cells());
  System.out.println(t.number_of_facets());
  System.out.println(t.number_of_edges());
  System.out.println(t.number_of_finite_cells());
  System.out.println(t.number_of_finite_facets());
  System.out.println(t.number_of_finite_edges());  

  if (!t.nearest_vertex(new EPIC_Point_3(1,1,1)).equals(t.nearest_vertex(new EPIC_Point_3(1,1,1),t.infinite_cell()))) System.out.println("Pb in nearest neighbor");
  
  int i=0;
  for (DT3_Vertex_handle vh: t.finite_vertices()){
    if (!t.is_infinite(vh)) ++i;
  }
  for (DT3_Vertex_handle vh: t.all_vertices())  --i;
  if (i!=-1) System.out.println("Pb 1");

  i=0;
  for (DT3_Cell_handle ch: t.finite_cells()){
    if (!t.is_infinite(ch)) --i;
    if (t.side_of_sphere(ch,v1.point()) != Bounded_side.ON_BOUNDARY) System.out.println("Pb side_of_sphere");
    if (t.side_of_circle(ch,0,ch.vertex(1).point())  != Bounded_side.ON_BOUNDARY) System.out.println("Pb side_of_circle");
    if (t.side_of_circle(new DT3_Facet(ch,0),ch.vertex(1).point())  != Bounded_side.ON_BOUNDARY) System.out.println("Pb side_of_circle");
  }
  for (DT3_Cell_handle ch: t.all_cells())  ++i;
  System.out.println(i+" infinite cells");

  i=0;
  for (DT3_Edge e: t.finite_edges())  if (!t.is_infinite(e)) {--i; if (t.is_Gabriel(e)!=t.is_Gabriel(e.getFirst(),e.getSecond(),e.getThird())) System.out.println("Pb 7");}
  for (DT3_Edge e: t.all_edges()){ ++i; if (t.is_infinite(e)!=t.is_infinite(e.getFirst(),e.getSecond(),e.getThird())) System.out.println("Pb 2");}
  System.out.println(i+" infinite edges");
  
  i=0;
  for (DT3_Facet f: t.finite_facets())  if (!t.is_infinite(f)) {
    --i;
    if (t.is_Gabriel(f)!=t.is_Gabriel(f.getFirst(),f.getSecond())) System.out.println("Pb 6");
    if (! t.are_equal(f,t.mirror_facet(t.mirror_facet(f))) )
      System.out.println("Pn mirror facet");
  }
  for (DT3_Facet f: t.all_facets()) { ++i; if (t.is_infinite(f)!=t.is_infinite(f.getFirst(),f.getSecond())) System.out.println("Pb 3");}

  System.out.println(i+" infinite facets");
  
  System.out.println("Points:");
  for(EPIC_Point_3 p:t.points())  System.out.println(p.x()+","+p.y()+","+p.z());

  if (!t.is_vertex(v1) || !t.is_cell(v2.cell()))
    System.out.println("Pb 4");
  
  if (! ci.equals(t.infinite_cell())) System.out.println("Pb cell equality test");
  
  if ((
        t.locate(new EPIC_Point_3(1,1,1)).equals(t.locate(new EPIC_Point_3(1,1,1),t.infinite_cell())) &&
        t.locate(new EPIC_Point_3(1,1,1)).equals(t.locate(new EPIC_Point_3(1,1,1),v1)) 
       )
     ){ System.out.println("Pb 5"); }
     
  boolean bool=true;
  if (! ( t.is_valid() && t.is_valid(bool) && t.is_valid(ci) && t.is_valid(ci,bool)) )
    System.out.println("Pb is_valid");
  if (!v1.point().equals(t.point(v1.cell(),v1.cell().index(v1))))
    System.out.println("Pb point1");
  if (!v1.point().equals(t.point(v1)) )
    System.out.println("Pb point2");
  
  
  DT3_T t2=new DT3_T(t);
  if (!t.equals(t2))
    System.out.println("Pb copy or equal");
  
  t.clear();
  
  //~ Vh_sc v1=t.insert(1,2,3);
  //~ Vh_sc v2=t.insert(1,3,3);
  //~ Vh_sc v3=t.insert(3,3,3);
  //~ System.out.println(t.number_of_vertices());
  //~ System.out.println(t.is_edge(v1,v2));
  //~ System.out.println(t.is_edge(v1,v3));
  //~ System.out.println(t.test_enum(0)==Locate_type.VERTEX);
  //~ Fvi_sc it=t.finite_vertices();
  //~ for (Vh_sc d : it){
  //~ // for (;it.hasNext();){
    //~ Point_3_sc p=d.point();
    //~ System.out.println(p.x());  
    //~ //System.out.println(it.next());  
  //~ }
  
  //~ Ffi_sc itf=t.finite_facets();
  //~ for (Facet_sc p : itf){
    //~ System.out.println(p.getSecond());  
  //~ }

  //~ Fei_sc ite=t.finite_edges();
  //~ for (Edge_sc p : ite){
    //~ System.out.println(p.getSecond());  
  //~ }
  
  //~ my_vector vect=new my_vector();
  //~ vect.add(1);
  //~ vect.add(2);
  //~ vect.add(3);
  
  //~ my_vector v=t.test_output();

  
  }
}
