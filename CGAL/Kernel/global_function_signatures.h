//dimension 3
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Line_3)

FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Line_3)

FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Line_3)

FORWARD_CALL_GF_2(double,squared_distance,Line_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Line_3)

//dimension 2
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Triangle_2)

FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Triangle_2)

FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Triangle_2)
FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Segment_2)
