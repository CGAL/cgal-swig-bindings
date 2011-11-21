#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Vector_3.h>

//member functions involving elements that are in include conflict
Vector_3::Vector_3(const Segment_3& s):data(s.get_data()){}
Vector_3::Vector_3(const Ray_3& r):data(r.get_data()){}
Vector_3::Vector_3(const Line_3& l):data(l.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Vector_3::direction,direction)
