#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <sstream>

Vector_3::Vector_3(){}
Vector_3::Vector_3(const Point_3& a,const Point_3& b):data(a.get_data(),b.get_data()){}
Vector_3::Vector_3(const Segment_3& s):data(s.get_data()){}
Vector_3::Vector_3(const Ray_3& r):data(r.get_data()){}
Vector_3::Vector_3(const Line_3& l):data(l.get_data()){}
Vector_3::Vector_3(int x, int y, int z):data(x,y,z){}
Vector_3::Vector_3(double x, double y, double z):data(x,y,z){}
  
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Direction_3,Vector_3::direction)

bool Vector_3::equals(const Vector_3& r){return data==r.get_data();}

std::string Vector_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Vector_3::__ne__(const Vector_3& r){return data!=r.get_data();}
#endif
