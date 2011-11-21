#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Ray_3.h>

//member functions involving elements that are in include conflict
Ray_3::Ray_3(const Point_3& p,const Direction_3& d):data(p.get_data(),d.get_data()){}
Ray_3::Ray_3(const Point_3& p,const Vector_3& v):data(p.get_data(),v.get_data()){}
Ray_3::Ray_3(const Point_3& p,const Line_3& l):data(p.get_data(),l.get_data()){}

SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Ray_3::direction,direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Ray_3::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Line_3,Ray_3::supporting_line,supporting_line)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Ray_3,Ray_3::opposite,opposite)
