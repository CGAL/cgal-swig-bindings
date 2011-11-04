#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Ray_2.h>
#include <sstream>

Ray_2::Ray_2(const Point_2& p,const Point_2& q):data(p.get_data(),q.get_data()){}
Ray_2::Ray_2(const Point_2& p,const Direction_2& d):data(p.get_data(),d.get_data()){}
Ray_2::Ray_2(const Point_2& p,const Vector_2& v):data(p.get_data(),v.get_data()){}
Ray_2::Ray_2(const Point_2& p,const Line_2& l):data(p.get_data(),l.get_data()){}

SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vector_2,Ray_2::to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Line_2,Ray_2::supporting_line)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Direction_2,Ray_2::direction)

bool Ray_2::equals(const Ray_2& r){return data==r.get_data();}

std::string Ray_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Ray_2::__ne__(const Ray_2& r){return data!=r.get_data();}
#endif
