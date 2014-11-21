import CGAL.Kernel.Point_2;
import CGAL.Kernel.Segment_2;
import CGAL.Kernel.Bbox_2;
import java.util.Vector;
import CGAL.Box_intersection_d.Collect_ids_callback_2;
import CGAL.Box_intersection_d.CGAL_Box_intersection_d;
import CGAL.Box_intersection_d.Box_with_id_2;
import CGAL.Box_intersection_d.Pair_of_int;

public class test_box_intersection_d{
  public static void main(String arg[]){

    //First set of segments
    Vector<Segment_2> segments_1=new Vector<Segment_2>();
    segments_1.add( new Segment_2(new Point_2(1,2), new Point_2(2,1) ) );
    segments_1.add( new Segment_2(new Point_2(1,3), new Point_2(2,3) ) );
    segments_1.add( new Segment_2(new Point_2(5,2), new Point_2(6,1) ) );

    //Second set of segments
    Vector<Segment_2> segments_2=new Vector<Segment_2>();
    segments_2.add( new Segment_2(new Point_2(1,1), new Point_2(2,2) ) );
    segments_2.add( new Segment_2(new Point_2(5,1), new Point_2(6,2) ) );
    segments_2.add( new Segment_2(new Point_2(5,3), new Point_2(6,3) ) );

    //Create the set of bboxes of the first set
    Vector<Box_with_id_2> bboxes_1=new Vector<Box_with_id_2>();
    int i=0;
    for(Segment_2 s : segments_1)
    {
      bboxes_1.add( new Box_with_id_2(s.bbox(),i) );
      ++i;
    }

    //Create the set of bboxes of the second set
    //Note that i is not reset to 0 as the id of each bbox should be unique
    Vector<Box_with_id_2> bboxes_2=new Vector<Box_with_id_2>();
    for(Segment_2 s : segments_2)
    {
      bboxes_2.add( new Box_with_id_2(s.bbox(),i) );
      ++i;
    }

    Collect_ids_callback_2 callback = new Collect_ids_callback_2();
    CGAL_Box_intersection_d.box_intersection_d(bboxes_1.iterator(), bboxes_2.iterator(), callback);

    int offset=bboxes_1.size();
    System.out.println("Ids of segments which bbox intersect");
    for (Pair_of_int p : callback.ids() )
    {
      System.out.println(p.getFirst()+" "+(p.getSecond()-offset));
    }

  }
}

