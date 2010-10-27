#include <SWIG_CGAL/Kernel/Direction_2.h>
#include <sstream>

Direction_2::Direction_2(const Vector_2& v):data(v.get_data()){}
Direction_2::Direction_2(const Line_2& l):data(l.get_data()){}
Direction_2::Direction_2(const Ray_2& r):data(r.get_data()){}
Direction_2::Direction_2(const Segment_2& s):data(s.get_data()){}
Direction_2::Direction_2(double x,double y):data(x,y){}

bool Direction_2::equals(const Direction_2& r){return data==r.get_data();}

FORWARD_CALL_0(Vector_2,Direction_2::vector)

std::string Direction_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Direction_2::__ne__(const Direction_2& r){return data!=r.get_data();}
#endif  

