#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Line_3.h>

//member functions involving elements that are in include conflict
Line_3::Line_3(const Point_3& p, Direction_3& d):data(p.get_data(),d.get_data()){}
Line_3::Line_3(const Point_3& p, Vector_3& v):data(p.get_data(),v.get_data()){}
Line_3::Line_3(const Segment_3& s):data(s.get_data()){}
Line_3::Line_3(const Ray_3& r):data(r.get_data()){}
  
SWIG_CGAL_FORWARD_CALL_AND_REF_1(Plane_3,Line_3::perpendicular_plane,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Line_3,Line_3::opposite,opposite)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Line_3::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Line_3::direction,direction)
