#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Tetrahedron_3.h>
#include <sstream>

const EPIC_Kernel::Tetrahedron_3& Tetrahedron_3::get_data() const {return data;}
EPIC_Kernel::Tetrahedron_3& Tetrahedron_3::get_data_ref() {return data;}
Tetrahedron_3::Tetrahedron_3():data(){}
Tetrahedron_3::Tetrahedron_3(const EPIC_Kernel::Tetrahedron_3& t):data(t){}
Tetrahedron_3::Tetrahedron_3(const Point_3& p,const Point_3& q,const Point_3& r,const Point_3& s):data(p.get_data(),q.get_data(),r.get_data(),s.get_data()){}

bool Tetrahedron_3::equals(const Tetrahedron_3& t){
  return data==t.get_data();
}

std::string Tetrahedron_3::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Tetrahedron_3::__ne__(const Tetrahedron_3& t){return !equals(t);}
#endif
