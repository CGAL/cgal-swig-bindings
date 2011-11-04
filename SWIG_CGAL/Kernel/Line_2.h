#ifndef SWIG_CGAL_KERNEL_LINE_2_H
#define SWIG_CGAL_KERNEL_LINE_2_H

#include <SWIG_CGAL/Kernel/include_conflicts_2.h>

#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Vector_2.h>
#include <SWIG_CGAL/Kernel/Ray_2.h>
#include <SWIG_CGAL/Kernel/Direction_2.h>


class SWIG_CGAL_KERNEL_DECL Line_2{
  EPIC_Kernel::Line_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Line_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Line_2(const cpp_base& base):data(base){}
  #endif //SWIG
//Creation
  Line_2(double a, double b, double c);
  Line_2(const Point_2& p,const Point_2& q);
  Line_2(const Point_2& p,const Direction_2& d);
  Line_2(const Point_2& p,const Vector_2& v);
  Line_2(const Segment_2& s);
  Line_2(const Ray_2& r);    
//Operations
  SWIG_CGAL_FORWARD_CALL_0(double,a)
  SWIG_CGAL_FORWARD_CALL_0(double,b)
  SWIG_CGAL_FORWARD_CALL_0(double,c)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,point,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,projection,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(double,x_at_y,double)
  SWIG_CGAL_FORWARD_CALL_1(double,y_at_x,double)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_horizontal)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_vertical)
  SWIG_CGAL_FORWARD_CALL_1(Oriented_side,oriented_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_positive_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_negative_side,Point_2)
//Miscellaneous
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_2,to_vector)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_2,direction)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Line_2,opposite)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Line_2,perpendicular,Point_2)
//
  bool equals(const Line_2&);
  std::string toString();
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Line_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_LINE_2_H

//SWIG_CGAL_FORWARD_CALL_0(Line_2,transform,Aff_transformation_2)


