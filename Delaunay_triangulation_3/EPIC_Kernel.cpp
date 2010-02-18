#include "EPIC_Kernel.h"

EPIC_Kernel::Point_3 EPIC_Point_3::get_data() const {return data;}
EPIC_Point_3::EPIC_Point_3():data(){}
EPIC_Point_3::EPIC_Point_3(double x,double y,double z):data(x,y,z){}
EPIC_Point_3::EPIC_Point_3(const EPIC_Kernel::Point_3& p):data(p){}
double EPIC_Point_3::x() {return data.x();}
double EPIC_Point_3::y() {return data.y();}
double EPIC_Point_3::z() {return data.z();}

bool EPIC_Point_3::equals(const EPIC_Point_3& p){
  return data==p.get_data();
}

#ifdef NO_SWIG_OR_PYTHON
bool EPIC_Point_3::__eq__(const EPIC_Point_3& p){return equals(p);}
bool EPIC_Point_3::__ne__(const EPIC_Point_3& p){return !equals(p);}
#endif