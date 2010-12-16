#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Line_2.h>
#include <sstream>


Line_2::Line_2(double a, double b, double c):data(a,b,c){}
Line_2::Line_2(const Point_2& p,const Point_2& q):data(p.get_data(),q.get_data()){}
Line_2::Line_2(const Point_2& p,const Direction_2& d):data(p.get_data(),d.get_data()){}
Line_2::Line_2(const Point_2& p,const Vector_2& v):data(p.get_data(),v.get_data()){}
Line_2::Line_2(const Segment_2& s):data(s.get_data()){}
Line_2::Line_2(const Ray_2& r):data(r.get_data()){}

FORWARD_CALL_AND_REF_0(Direction_2,Line_2::direction)
FORWARD_CALL_AND_REF_0(Vector_2,Line_2::to_vector)

bool Line_2::equals(const Line_2& r){return data==r.get_data();}

std::string Line_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Line_2::__ne__(const Line_2& r){return data!=r.get_data();}
#endif
