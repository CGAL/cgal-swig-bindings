#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Vector_2.h>
#include <sstream>


Vector_2::Vector_2():data(){}
Vector_2::Vector_2(const Point_2& a,const Point_2& b):data(a.get_data(),b.get_data()){}
Vector_2::Vector_2(const Segment_2& s):data(s.get_data()){}
Vector_2::Vector_2(const Ray_2& r):data(r.get_data()){}
Vector_2::Vector_2(const Line_2& l):data(l.get_data()){}
Vector_2::Vector_2(int x, int y):data(x,y){}
Vector_2::Vector_2(double x, double y):data(x,y){}
  
SWIG_CGAL_FORWARD_CALL_AND_REF_0(Direction_2,Vector_2::direction)

bool Vector_2::equals(const Vector_2& r){return data==r.get_data();}

std::string Vector_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Vector_2::__ne__(const Vector_2& r){return data!=r.get_data();}
#endif
