#include <SWIG_CGAL/Kernel/Point_2.h>
#include <sstream>

const EPIC_Kernel::Point_2& Point_2::get_data() const {return data;}
EPIC_Kernel::Point_2& Point_2::get_data_ref() {return data;}
Point_2::Point_2():data(){}
Point_2::Point_2(double x,double y):data(x,y){}
Point_2::Point_2(const EPIC_Kernel::Point_2& p):data(p){}
double Point_2::x() const {return data.x();}
double Point_2::y() const {return data.y();}

bool Point_2::equals(const Point_2& p){
  return data==p.get_data();
}

std::string Point_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Point_2::__ne__(const Point_2& p){return !equals(p);}
#endif
