#include <SWIG_CGAL/Kernel/Weighted_point_3.h>
#include <sstream>

Weighted_point_3::Weighted_point_3():data(){}
Weighted_point_3::Weighted_point_3(double x,double y,double z):data(x,y,z){}
Weighted_point_3::Weighted_point_3(const Point_3& p,double w):data(p.get_data(),w){}
Weighted_point_3::Weighted_point_3(const CGAL::Weighted_point<EPIC_Kernel::Point_3,double>& p):data(p){}
  
const CGAL::Weighted_point<EPIC_Kernel::Point_3,double>& Weighted_point_3::get_data() const {return data;}
CGAL::Weighted_point<EPIC_Kernel::Point_3,double>& Weighted_point_3::get_data_ref() {return data;}  
double Weighted_point_3::weight() const {return data.weight();}
double Weighted_point_3::x() const {return data.x();}
double Weighted_point_3::y() const {return data.y();}
double Weighted_point_3::z() const {return data.z();}
Point_3 Weighted_point_3::point() const {return Point_3(data.point());}

bool Weighted_point_3::equals(const Weighted_point_3& p){
  return data==p.get_data();
}

std::string Weighted_point_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Weighted_point_3::__ne__(const Weighted_point_3& p){return !equals(p);}
#endif
