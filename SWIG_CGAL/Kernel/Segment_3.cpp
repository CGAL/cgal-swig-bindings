#include "Segment_3.h"
#include <sstream>

const EPIC_Kernel::Segment_3& Segment_3::get_data() const {return data;}
EPIC_Kernel::Segment_3& Segment_3::get_data_ref() {return data;}
Segment_3::Segment_3():data(){}
Segment_3::Segment_3(const EPIC_Kernel::Segment_3& s):data(s){}
Segment_3::Segment_3(const Point_3& p1, const Point_3& p2):data(p1.get_data(), p2.get_data()){}

Point_3 Segment_3::source() {return data.source();}
Point_3 Segment_3::target() {return data.target();}
Line_3 Segment_3::supporting_line(){return data.supporting_line();}


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
