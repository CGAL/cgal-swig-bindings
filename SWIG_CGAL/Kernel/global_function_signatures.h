//squared_distance
//dimension 3
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Line_3)
FORWARD_CALL_GF_2(double,squared_distance,Point_3,Ray_3)

FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Line_3)
FORWARD_CALL_GF_2(double,squared_distance,Plane_3,Ray_3)

FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Line_3)
FORWARD_CALL_GF_2(double,squared_distance,Segment_3,Ray_3)

FORWARD_CALL_GF_2(double,squared_distance,Line_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Line_3)
FORWARD_CALL_GF_2(double,squared_distance,Line_3,Ray_3)

FORWARD_CALL_GF_2(double,squared_distance,Ray_3,Point_3)
FORWARD_CALL_GF_2(double,squared_distance,Ray_3,Plane_3)
FORWARD_CALL_GF_2(double,squared_distance,Ray_3,Segment_3)
FORWARD_CALL_GF_2(double,squared_distance,Ray_3,Line_3)
FORWARD_CALL_GF_2(double,squared_distance,Ray_3,Ray_3)

//dimension 2
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Triangle_2)
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Line_2)
FORWARD_CALL_GF_2(double,squared_distance,Point_2,Ray_2)

FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Triangle_2)
FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Line_2)
FORWARD_CALL_GF_2(double,squared_distance,Segment_2,Ray_2)

FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Triangle_2)
FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Line_2)
FORWARD_CALL_GF_2(double,squared_distance,Triangle_2,Ray_2)

FORWARD_CALL_GF_2(double,squared_distance,Line_2,Triangle_2)
FORWARD_CALL_GF_2(double,squared_distance,Line_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Line_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Line_2,Line_2)
FORWARD_CALL_GF_2(double,squared_distance,Line_2,Ray_2)

FORWARD_CALL_GF_2(double,squared_distance,Ray_2,Triangle_2)
FORWARD_CALL_GF_2(double,squared_distance,Ray_2,Point_2)
FORWARD_CALL_GF_2(double,squared_distance,Ray_2,Segment_2)
FORWARD_CALL_GF_2(double,squared_distance,Ray_2,Line_2)
FORWARD_CALL_GF_2(double,squared_distance,Ray_2,Ray_2)

//do_insertect
//dimension 3
FORWARD_CALL_GF_2(bool,do_intersect,Plane_3,Segment_3)
FORWARD_CALL_GF_2(bool,do_intersect,Plane_3,Line_3)
FORWARD_CALL_GF_2(bool,do_intersect,Plane_3,Plane_3)
FORWARD_CALL_GF_2(bool,do_intersect,Plane_3,Triangle_3)
FORWARD_CALL_GF_2(bool,do_intersect,Plane_3,Ray_3)

FORWARD_CALL_GF_2(bool,do_intersect,Segment_3,Plane_3)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_3,Segment_3)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_3,Line_3)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_3,Triangle_3)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_3,Ray_3)

FORWARD_CALL_GF_2(bool,do_intersect,Line_3,Plane_3)
FORWARD_CALL_GF_2(bool,do_intersect,Line_3,Segment_3)
FORWARD_CALL_GF_2(bool,do_intersect,Line_3,Line_3)
FORWARD_CALL_GF_2(bool,do_intersect,Line_3,Triangle_3)
FORWARD_CALL_GF_2(bool,do_intersect,Line_3,Ray_3)

FORWARD_CALL_GF_2(bool,do_intersect,Triangle_3,Plane_3)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_3,Segment_3)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_3,Line_3)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_3,Triangle_3)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_3,Ray_3)

FORWARD_CALL_GF_2(bool,do_intersect,Ray_3,Plane_3)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_3,Segment_3)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_3,Line_3)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_3,Triangle_3)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_3,Ray_3)

//dimension 2
FORWARD_CALL_GF_2(bool,do_intersect,Segment_2,Segment_2)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_2,Triangle_2)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_2,Ray_2)
FORWARD_CALL_GF_2(bool,do_intersect,Segment_2,Line_2)

FORWARD_CALL_GF_2(bool,do_intersect,Triangle_2,Triangle_2)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_2,Segment_2)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_2,Ray_2)
FORWARD_CALL_GF_2(bool,do_intersect,Triangle_2,Line_2)

FORWARD_CALL_GF_2(bool,do_intersect,Line_2,Triangle_2)
FORWARD_CALL_GF_2(bool,do_intersect,Line_2,Segment_2)
FORWARD_CALL_GF_2(bool,do_intersect,Line_2,Ray_2)
FORWARD_CALL_GF_2(bool,do_intersect,Line_2,Line_2)

FORWARD_CALL_GF_2(bool,do_intersect,Ray_2,Triangle_2)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_2,Segment_2)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_2,Ray_2)
FORWARD_CALL_GF_2(bool,do_intersect,Ray_2,Line_2)

//intersection
//dimension 3
FORWARD_CALL_GF_2(CGAL_Object,intersection,Plane_3,Segment_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Plane_3,Line_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Plane_3,Plane_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Plane_3,Triangle_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Plane_3,Ray_3)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_3,Plane_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_3,Segment_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_3,Triangle_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_3,Line_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_3,Ray_3)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_3,Plane_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_3,Segment_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_3,Triangle_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_3,Line_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_3,Ray_3)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_3,Plane_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_3,Segment_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_3,Line_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_3,Triangle_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_3,Ray_3)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_3,Plane_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_3,Segment_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_3,Line_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_3,Triangle_3)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_3,Ray_3)

//dimension 2
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_2,Segment_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_2,Triangle_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_2,Ray_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Segment_2,Line_2)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_2,Triangle_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_2,Segment_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_2,Ray_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Triangle_2,Line_2)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_2,Triangle_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_2,Segment_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_2,Ray_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Line_2,Line_2)

FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_2,Triangle_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_2,Segment_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_2,Ray_2)
FORWARD_CALL_GF_2(CGAL_Object,intersection,Ray_2,Line_2)
