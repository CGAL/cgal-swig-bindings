#ifndef SWIG_CGAL_KERNEL_DIRECTION_3_H
#define SWIG_CGAL_KERNEL_DIRECTION_3_H

#include <SWIG_CGAL/Kernel/include_conflicts_3.h>

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Line_3.h>
#include <SWIG_CGAL/Kernel/Ray_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>

class SWIG_CGAL_KERNEL_DECL Direction_3{
  EPIC_Kernel::Direction_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Direction_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Direction_3(const cpp_base& base):data(base){}
  #endif //SWIG
//Creation
  Direction_3(const Vector_3& v);
  Direction_3(const Line_3& l);
  Direction_3(const Ray_3& r);
  Direction_3(const Segment_3& s);
  Direction_3(double x, double y, double z);
//Operations
  SWIG_CGAL_FORWARD_CALL_1(double,delta,int)
  SWIG_CGAL_FORWARD_CALL_0(double,dx)
  SWIG_CGAL_FORWARD_CALL_0(double,dy)
  SWIG_CGAL_FORWARD_CALL_0(double,dz)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_3,vector)
//
  bool equals(const Direction_3&);
  std::string toString();
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Direction_3&);
  #endif    
};  

#endif //SWIG_CGAL_KERNEL_DIRECTION_3_H

//Direction_3<Kernel> d.operator- () The direction opposite to d.
//Direction_3<Kernel> d.transform ( Aff_transformation_3<Kernel> t)
