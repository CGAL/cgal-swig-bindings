#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Vector_2.h>

//member functions involving elements that are in include conflict
Vector_2::Vector_2(const Segment_2& s):data(s.get_data()){}
Vector_2::Vector_2(const Ray_2& r):data(r.get_data()){}
Vector_2::Vector_2(const Line_2& l):data(l.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_2,Vector_2::direction,direction)
