#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Triangle_2.h>
#include <sstream>

Triangle_2::Triangle_2():data(){}
Triangle_2::Triangle_2(const EPIC_Kernel::Triangle_2& t):data(t){}
Triangle_2::Triangle_2(const Point_2& p,const Point_2& q,const Point_2& r):data(p.get_data(),q.get_data(),r.get_data()){}

bool Triangle_2::equals(const Triangle_2& t){
  return data==t.get_data();
}

std::string Triangle_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Triangle_2::__ne__(const Triangle_2& t){return !equals(t);}
#endif
