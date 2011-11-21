#define SWIG_CGAL_KERNEL_EXPORT

#include <SWIG_CGAL/Kernel/Plane_3.h>

//member functions involving elements that are in include conflict
Plane_3::Plane_3(const Point_3& p,const Vector_3& v):data(p.get_data(),v.get_data()){}
Plane_3::Plane_3(const Point_3& p,const Direction_3& d):data(p.get_data(),d.get_data()){}
Plane_3::Plane_3(const Line_3& l,const Point_3& p):data(l.get_data(),p.get_data()){}
Plane_3::Plane_3(const Ray_3& r,const Point_3& p):data(r.get_data(),p.get_data()){}
Plane_3::Plane_3(const Segment_3& s,const Point_3& p):data(s.get_data(),p.get_data()){}
  
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Plane_3,Plane_3::opposite,opposite)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Point_3,Plane_3::point,point)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Plane_3::orthogonal_vector,orthogonal_vector)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(Line_3,Plane_3::perpendicular_line,perpendicular_line,Point_3)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Direction_3,Plane_3::orthogonal_direction,orthogonal_direction)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Plane_3::base1,base1)
SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(Vector_3,Plane_3::base2,base2)
