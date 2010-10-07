#include "Weighted_point_2.h"
#include <sstream>

Weighted_point_2::Weighted_point_2():data(){}
Weighted_point_2::Weighted_point_2(double x,double y):data(x,y){}
Weighted_point_2::Weighted_point_2(const Point_2& p,double w):data(p.get_data(),w){}
Weighted_point_2::Weighted_point_2(const CGAL::Weighted_point<EPIC_Kernel::Point_2,double>& p):data(p){}
  
const CGAL::Weighted_point<EPIC_Kernel::Point_2,double>& Weighted_point_2::get_data() const {return data;}
CGAL::Weighted_point<EPIC_Kernel::Point_2,double>& Weighted_point_2::get_data_ref() {return data;}  
double Weighted_point_2::weight() const {return data.weight();}
double Weighted_point_2::x() const {return data.x();}
double Weighted_point_2::y() const {return data.y();}
Point_2 Weighted_point_2::point() const {return Point_2(data.point());}

bool Weighted_point_2::equals(const Weighted_point_2& p){
  return data==p.get_data();
}

std::string Weighted_point_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Weighted_point_2::__ne__(const Weighted_point_2& p){return !equals(p);}
#endif
