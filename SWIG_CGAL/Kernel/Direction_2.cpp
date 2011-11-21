#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Direction_2.h>

//member functions involving elements that are in include conflict
Direction_2::Direction_2(const Vector_2& v):data(v.get_data()){}
Direction_2::Direction_2(const Line_2& l):data(l.get_data()){}
Direction_2::Direction_2(const Ray_2& r):data(r.get_data()){}
Direction_2::Direction_2(const Segment_2& s):data(s.get_data()){}
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_2,Direction_2::vector,vector)
