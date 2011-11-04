#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <sstream>

Plane_3::Plane_3(){}
Plane_3::Plane_3(double a,double b,double c,double d):data(a,b,c,d){}
Plane_3::Plane_3(const Point_3& p,const Point_3& q,const Point_3& r):data(p.get_data(),q.get_data(),r.get_data()){}
Plane_3::Plane_3(const Point_3& p,const Vector_3& v):data(p.get_data(),v.get_data()){}
Plane_3::Plane_3(const Point_3& p,const Direction_3& d):data(p.get_data(),d.get_data()){}
Plane_3::Plane_3(const Line_3& l,const Point_3& p):data(l.get_data(),p.get_data()){}
Plane_3::Plane_3(const Ray_3& r,const Point_3& p):data(r.get_data(),p.get_data()){}
Plane_3::Plane_3(const Segment_3& s,const Point_3& p):data(s.get_data(),p.get_data()){}
  
  

SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vector_3,Plane_3::orthogonal_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_1(Line_3,Plane_3::perpendicular_line,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Direction_3,Plane_3::orthogonal_direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vector_3,Plane_3::base1)
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vector_3,Plane_3::base2)  
SWIG_CGAL_FORWARD_CALL_1(bool,Plane_3::has_on,Line_3)
  
  
  
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
