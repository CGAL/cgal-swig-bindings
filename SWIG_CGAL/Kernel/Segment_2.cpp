#include "Segment_2.h"
#include <sstream>

const EPIC_Kernel::Segment_2& Segment_2::get_data() const {return data;}
EPIC_Kernel::Segment_2& Segment_2::get_data_ref() {return data;}
Segment_2::Segment_2():data(){}
Segment_2::Segment_2(const Point_2& p,const Point_2& q):data(p.get_data(),q.get_data()){}
Segment_2::Segment_2(const EPIC_Kernel::Segment_2& s):data(s){}

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
