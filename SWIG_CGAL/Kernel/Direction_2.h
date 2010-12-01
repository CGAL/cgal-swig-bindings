#ifndef SWIG_CGAL_KERNEL_DIRECTION_2_H
#define SWIG_CGAL_KERNEL_DIRECTION_2_H

#include <SWIG_CGAL/Kernel/include_conflicts_2.h>

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Segment_2.h>
#include <SWIG_CGAL/Kernel/Line_2.h>
#include <SWIG_CGAL/Kernel/Ray_2.h>

class Direction_2{
  EPIC_Kernel::Direction_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Direction_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Direction_2(const cpp_base& base):data(base){}
  #endif //SWIG

//Creation
  Direction_2(const Vector_2& v);
  Direction_2(const Line_2& l);
  Direction_2(const Ray_2& r);
  Direction_2(const Segment_2& s);
  Direction_2(double x,double y);
//Operations
  FORWARD_CALL_1(double,delta,int)
  FORWARD_CALL_0(double,dx)
  FORWARD_CALL_0(double,dy)
  FORWARD_CALL_2(bool,counterclockwise_in_between,Direction_2,Direction_2)
//Miscellaneous
  DECLARE_CALL_AND_REF_0(Vector_2,vector)
//
  bool equals(const Direction_2&);
  std::string toString();
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Direction_2&);
  #endif    
};  

#endif //SWIG_CGAL_KERNEL_DIRECTION_2_H

//Operations
//  bool  d.operator== ( e)
//  bool  d.operator!= ( e)
//  bool  d.operator< ( e)
//  bool  d.operator> ( e)
//  bool  d.operator<= ( e)
//  bool  d.operator>= ( e)
//  Direction_2<Kernel>  d.operator- ()  The direction opposite to d.
//Miscellaneous
//  Direction_2<Kernel>  d.transform ( Aff_transformation_2<Kernel> t)
