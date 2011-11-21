#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Ray_2.h>

//member functions involving elements that are in include conflict
Ray_2::Ray_2(const Point_2& p,const Direction_2& d):data(p.get_data(),d.get_data()){}
Ray_2::Ray_2(const Point_2& p,const Vector_2& v):data(p.get_data(),v.get_data()){}
Ray_2::Ray_2(const Point_2& p,const Line_2& l):data(p.get_data(),l.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_2,Ray_2::direction,direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_2,Ray_2::to_vector,to_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Line_2,Ray_2::supporting_line,supporting_line)
