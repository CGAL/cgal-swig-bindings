#ifndef SWIG_CGAL_KERNEL_PLANE_3_H
#define SWIG_CGAL_KERNEL_PLANE_3_H

#include <SWIG_CGAL/Kernel/include_conflicts_3.h>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Line_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Kernel/Direction_3.h>

class Plane_3{
  EPIC_Kernel::Plane_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Plane_3 cpp_base;  
  const EPIC_Kernel::Plane_3& get_data() const {return data;}
  EPIC_Kernel::Plane_3& get_data_ref() {return data;}
  Plane_3(const cpp_base& p):data(p){}
  #endif
//Creation
  Plane_3();
  Plane_3(double a,double b,double c,double d);
  Plane_3(const Point_3& p,const Point_3& q,const Point_3& r);
  Plane_3(const Point_3& p,const Vector_3& v);
  Plane_3(const Point_3& p,const Direction_3& d);
  Plane_3(const Line_3& l,const Point_3& p);
  Plane_3(const Ray_3& r,const Point_3& p);
  Plane_3(const Segment_3& s,const Point_3& p);
//Operations
  FORWARD_CALL_0(double,a)
  FORWARD_CALL_0(double,b)
  FORWARD_CALL_0(double,c)
  FORWARD_CALL_0(double,d)
  FORWARD_CALL_1(Point_3,projection,Point_3)
  FORWARD_CALL_0(Plane_3,opposite)
  FORWARD_CALL_0(Point_3,point)
  Vector_3 orthogonal_vector();
  Line_3 perpendicular_line(const Point_3& p);
  Direction_3 orthogonal_direction();
  Vector_3 base1();
  Vector_3 base2();
//2D Conversion
  FORWARD_CALL_1(Point_2,to_2d,Point_3)
  FORWARD_CALL_1(Point_3,to_3d,Point_2)
//Predicates
  FORWARD_CALL_1(Oriented_side,oriented_side,Point_3)
  FORWARD_CALL_1(bool,has_on,Point_3)
  FORWARD_CALL_1(bool,has_on_positive_side,Point_3)
  FORWARD_CALL_1(bool,has_on_negative_side,Point_3)
  bool has_on(const Line_3&);
  FORWARD_CALL_0(bool,is_degenerate)
//
  bool equals(const Plane_3&);
  std::string toString();
  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Plane_3&);
  #endif
};


#endif //SWIG_CGAL_KERNEL_PLANE_3_H

//Plane_3(const Circle_3& c);
//FORWARD_CALL_1(bool,has_on,Circle_3)
//Miscellaneous
//Plane_3<Kernel> h.transform ( Aff_transformation_3<Kernel> t)

