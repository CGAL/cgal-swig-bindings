#include <SWIG_CGAL/Kernel/Line_3.h>
#include <sstream>

const EPIC_Kernel::Line_3& Line_3::get_data() const {return data;}
EPIC_Kernel::Line_3& Line_3::get_data_ref() {return data;}
Line_3::Line_3():data(){}
Line_3::Line_3(const EPIC_Kernel::Line_3& l):data(l){}
Line_3::Line_3(const Point_3& p1, const Point_3& p2):data(p1.get_data(), p2.get_data()){}

Point_3 Line_3::projection(const Point_3& p){ return data.projection(p.get_data()); }
Plane_3 Line_3::perpendicular_plane(const Point_3& p){ return data.perpendicular_plane(p.get_data()); }
Line_3 Line_3::opposite(){ return data.opposite(); }


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
