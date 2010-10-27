#include <SWIG_CGAL/Kernel/Ray_3.h>
#include <sstream>


Ray_3::Ray_3(const Point_3& p,const Point_3& q):data(p.get_data(),q.get_data()){}
Ray_3::Ray_3(const Point_3& p,const Direction_3& d):data(p.get_data(),d.get_data()){}
Ray_3::Ray_3(const Point_3& p,const Vector_3& v):data(p.get_data(),v.get_data()){}
Ray_3::Ray_3(const Point_3& p,const Line_3& l):data(p.get_data(),l.get_data()){}

FORWARD_CALL_0(Direction_3,Ray_3::direction)
FORWARD_CALL_0(Vector_3,Ray_3::to_vector)
FORWARD_CALL_0(Line_3,Ray_3::supporting_line)

bool Ray_3::equals(const Ray_3& r){return data==r.get_data();}

std::string Ray_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Ray_3::__ne__(const Ray_3& r){return data!=r.get_data();}
#endif

