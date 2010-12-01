#include <SWIG_CGAL/Kernel/Direction_3.h>
#include <sstream>


Direction_3::Direction_3(const Vector_3& v):data(v.get_data()){}
Direction_3::Direction_3(const Line_3& l):data(l.get_data()){}
Direction_3::Direction_3(const Ray_3& r):data(r.get_data()){}
Direction_3::Direction_3(const Segment_3& s):data(s.get_data()){}
Direction_3::Direction_3(double x, double y, double z):data(x,y,z){}

FORWARD_CALL_AND_REF_0(Vector_3,Direction_3::vector)

bool Direction_3::equals(const Direction_3& r){return data==r.get_data();}

std::string Direction_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Direction_3::__ne__(const Direction_3& r){return data!=r.get_data();}
#endif

