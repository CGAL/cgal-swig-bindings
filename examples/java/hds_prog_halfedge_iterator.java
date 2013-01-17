import CGAL.HalfedgeDS.HalfedgeDS;
import CGAL.HalfedgeDS.HalfedgeDS_decorator;
import CGAL.HalfedgeDS.HDS_Halfedge_handle;

public class hds_prog_halfedge_iterator {
  public static void main(String arg[]){
    HalfedgeDS hds = new HalfedgeDS();
    HalfedgeDS_decorator decorator = new HalfedgeDS_decorator(hds);
    decorator.create_loop();
    decorator.create_segment();
    assert decorator.is_valid();
    
    int n = 0;
    for ( HDS_Halfedge_handle h : hds.halfedges() ){ ++n; }
    assert n == 4;
  }
}