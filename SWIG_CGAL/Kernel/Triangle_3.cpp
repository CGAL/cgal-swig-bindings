#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Triangle_3.h>
#include <sstream>

const EPIC_Kernel::Triangle_3& Triangle_3::get_data() const {return data;}
EPIC_Kernel::Triangle_3& Triangle_3::get_data_ref() {return data;}
Triangle_3::Triangle_3():data(){}
Triangle_3::Triangle_3(const EPIC_Kernel::Triangle_3& t):data(t){}
Triangle_3::Triangle_3(const Point_3& p,const Point_3& q,const Point_3& r):data(p.get_data(),q.get_data(),r.get_data()){}

bool Triangle_3::equals(const Triangle_3& t){
  return data==t.get_data();
}

std::string Triangle_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Triangle_3::__ne__(const Triangle_3& t){return !equals(t);}
#endif
