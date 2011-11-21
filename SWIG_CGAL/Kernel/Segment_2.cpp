#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Segment_2.h>
#include <sstream>

Segment_2::Segment_2():data(){}
Segment_2::Segment_2(const Point_2& p,const Point_2& q):data(p.get_data(),q.get_data()){}
Segment_2::Segment_2(const EPIC_Kernel::Segment_2& s):data(s){}

SWIG_CGAL_FORWARD_CALL_AND_REF_0(Direction_2,Segment_2::direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vector_2,Segment_2::to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Line_2,Segment_2::supporting_line)
  
bool Segment_2::equals(const Segment_2& s){
  return data==s.get_data();
}

std::string Segment_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Segment_2::__ne__(const Segment_2& s){return !equals(s);}
#endif
