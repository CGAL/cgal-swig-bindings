#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <sstream>

Segment_3::Segment_3():data(){}
Segment_3::Segment_3(const Point_3& p1, const Point_3& p2):data(p1.get_data(), p2.get_data()){}

FORWARD_CALL_0(Vector_3,Segment_3::to_vector)
FORWARD_CALL_0(Direction_3,Segment_3::direction)
FORWARD_CALL_0(Line_3,Segment_3::supporting_line)

bool Segment_3::equals(const Segment_3& p){
  return data==p.get_data();
}

std::string Segment_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Segment_3::__ne__(const Segment_3& p){return !equals(p);}
#endif
