#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Line_3.h>
#include <sstream>

Line_3::Line_3(){}
Line_3::Line_3(const Point_3& p, Point_3& q):data(p.get_data(),q.get_data()){}
Line_3::Line_3(const Point_3& p, Direction_3& d):data(p.get_data(),d.get_data()){}
Line_3::Line_3(const Point_3& p, Vector_3& v):data(p.get_data(),v.get_data()){}
Line_3::Line_3(const Segment_3& s):data(s.get_data()){}
Line_3::Line_3(const Ray_3& r):data(r.get_data()){}

FORWARD_CALL_AND_REF_1(Plane_3,Line_3::perpendicular_plane,Point_3)
FORWARD_CALL_AND_REF_0(Line_3,Line_3::opposite)
FORWARD_CALL_AND_REF_0(Vector_3,Line_3::to_vector)
FORWARD_CALL_AND_REF_0(Direction_3,Line_3::direction)

bool Line_3::equals(const Line_3& p){
  return data==p.get_data();
}

std::string Line_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Line_3::__ne__(const Line_3& p){return !equals(p);}
#endif
