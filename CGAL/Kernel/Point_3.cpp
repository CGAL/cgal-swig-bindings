#include "Point_3.h"
#include <sstream>

const EPIC_Kernel::Point_3& Point_3::get_data() const {return data;}
EPIC_Kernel::Point_3& Point_3::get_data_ref() {return data;}
Point_3::Point_3():data(){}
Point_3::Point_3(double x,double y,double z):data(x,y,z){}
Point_3::Point_3(const EPIC_Kernel::Point_3& p):data(p){}
double Point_3::x() {return data.x();}
double Point_3::y() {return data.y();}
double Point_3::z() {return data.z();}

bool Point_3::equals(const Point_3& p){
  return data==p.get_data();
}

std::string Point_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Point_3::__ne__(const Point_3& p){return !equals(p);}
#endif