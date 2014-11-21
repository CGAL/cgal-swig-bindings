from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Segment_2
from CGAL.CGAL_Kernel import Bbox_2
from CGAL.CGAL_Box_intersection_d import Collect_ids_callback_2
from CGAL.CGAL_Box_intersection_d import Box_with_id_2
from CGAL.CGAL_Box_intersection_d import Pair_of_int
from CGAL import CGAL_Box_intersection_d

#First set of segments
segments_1=[]
segments_1.append( Segment_2(Point_2(1,2), Point_2(2,1) ) )
segments_1.append( Segment_2(Point_2(1,3), Point_2(2,3) ) )
segments_1.append( Segment_2(Point_2(5,2), Point_2(6,1) ) )

#Second set of segments
segments_2=[]
segments_2.append( Segment_2(Point_2(1,1), Point_2(2,2) ) )
segments_2.append( Segment_2(Point_2(5,1), Point_2(6,2) ) )
segments_2.append( Segment_2(Point_2(5,3), Point_2(6,3) ) )


#Create the set of bboxes of the first set
bboxes_1=[]
i=0
for s in segments_1:
  bboxes_1.append( Box_with_id_2(s.bbox(),i) )
  i+=1


#Create the set of bboxes of the second set
#Note that i is not reset to 0 as the id of each bbox should be unique
bboxes_2=[]
for s in segments_2:
  bboxes_2.append( Box_with_id_2(s.bbox(),i) )
  i+=1


callback = Collect_ids_callback_2()
CGAL_Box_intersection_d.box_intersection_d(bboxes_1, bboxes_2, callback)

offset=len(bboxes_1)
print("Ids of segments which bbox intersect")
for p in callback.ids():
  print(p[0],p[1]-offset)


