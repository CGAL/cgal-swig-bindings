#ifndef SWIG_CGAL_KERNEL_TRIANGLE_2_H
#define SWIG_CGAL_KERNEL_TRIANGLE_2_H

#include "typedefs.h"
#include "Point_2.h"
#include "../Common/Macros.h"


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Triangle_2{
  EPIC_Kernel::Triangle_2 data;
public:
  typedef EPIC_Kernel::Triangle_2 cpp_base;

  const EPIC_Kernel::Triangle_2& get_data() const;
  EPIC_Kernel::Triangle_2& get_data_ref();
  Triangle_2();
  Triangle_2(const Point_2& p,const Point_2& q,const Point_2& r);
  Triangle_2(const EPIC_Kernel::Triangle_2& p);

//Operations
  FORWARD_CALL_1(Point_2,vertex,int)
//Predicates
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_1(bool,has_on_positive_side,Point_2)
  FORWARD_CALL_1(bool,has_on_negative_side,Point_2)
  FORWARD_CALL_1(bool,has_on_boundary,Point_2)
  FORWARD_CALL_1(bool,has_on_bounded_side,Point_2)
  FORWARD_CALL_1(bool,has_on_unbounded_side,Point_2)
//Miscellaneous
  FORWARD_CALL_0(Triangle_2,opposite)
  FORWARD_CALL_0(double,area)

  bool equals(const Triangle_2&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Triangle_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_TRIANGLE_2_H


//Predicates
//  Orientation   t.orientation ()   returns the orientation of t.
//  Oriented_side   t.oriented_side ( Point_2<Kernel> p)
//  Bounded_side   t.bounded_side ( Point_2<Kernel> p)
//Miscellaneous
// Bbox_2   t.bbox ()   returns a bounding box containing t.
// Triangle_2<Kernel>   t.transform ( Aff_transformation_2<Kernel> at)
