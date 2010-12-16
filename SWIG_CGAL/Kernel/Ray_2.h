#ifndef SWIG_CGAL_KERNEL_RAY_2_H
#define SWIG_CGAL_KERNEL_RAY_2_H

#include <SWIG_CGAL/Kernel/include_conflicts_2.h>

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Vector_2.h>
#include <SWIG_CGAL/Kernel/Line_2.h>
#include <SWIG_CGAL/Kernel/Direction_2.h>


class SWIG_CGAL_KERNEL_DECL Ray_2{
  EPIC_Kernel::Ray_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Ray_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Ray_2(const cpp_base& base):data(base){}
  #endif //SWIG
//Creation
  Ray_2(const Point_2& p,const Point_2& q);
  Ray_2(const Point_2& p,const Direction_2& d);
  Ray_2(const Point_2& p,const Vector_2& v);
  Ray_2(const Point_2& p,const Line_2& l);
//Operations
  FORWARD_CALL_AND_REF_0(Point_2,source)
  FORWARD_CALL_AND_REF_1(Point_2,point,int)
  DECLARE_CALL_AND_REF_0(Direction_2,direction)
  DECLARE_CALL_AND_REF_0(Vector_2,to_vector)
  DECLARE_CALL_AND_REF_0(Line_2,supporting_line)
    
  FORWARD_CALL_AND_REF_0(Ray_2,opposite)
//Predicates
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_0(bool,is_horizontal)
  FORWARD_CALL_0(bool,is_vertical)
  FORWARD_CALL_1(bool,has_on,Point_2)
  FORWARD_CALL_1(bool,collinear_has_on,Point_2)    
//
  bool equals(const Ray_2&);
  std::string toString();
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Ray_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_RAY_2_H

//Miscellaneous
// Ray_2<Kernel>  r.transform ( Aff_transformation_2<Kernel> t)

