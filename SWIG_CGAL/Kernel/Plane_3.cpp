#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <sstream>

const EPIC_Kernel::Plane_3& Plane_3::get_data() const {return data;}
EPIC_Kernel::Plane_3& Plane_3::get_data_ref() {return data;}
Plane_3::Plane_3():data(){}
Plane_3::Plane_3(double a,double b,double c,double d):data(a,b,c,d){}
Plane_3::Plane_3(const EPIC_Kernel::Plane_3& p):data(p){}
Plane_3::Plane_3(const Segment_3& s, const Point_3& p):data(s.get_data(),p.get_data()){}
Plane_3::Plane_3(const Point_3& p, const Point_3& q, const Point_3& r):data(p.get_data(),q.get_data(),r.get_data()){}
double Plane_3::a() {return data.a();}
double Plane_3::b() {return data.b();}
double Plane_3::c() {return data.c();}
double Plane_3::d() {return data.d();}

Point_3 Plane_3::projection(const Point_3& p){return data.projection(p.get_data()); };

bool Plane_3::equals(const Plane_3& p){
  return data==p.get_data();
}

std::string Plane_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Plane_3::__ne__(const Plane_3& p){return !equals(p);}
#endif
