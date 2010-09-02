#ifndef SWIG_CGAL_KERNEL_TETRAHEDRON_3_H
#define SWIG_CGAL_KERNEL_TETRAHEDRON_3_H

#include "typedefs.h"
#include "Point_3.h"
#include "enum.h"
#include "../Common/Macros.h"


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Tetrahedron_3{
  EPIC_Kernel::Tetrahedron_3 data;
public:
  typedef EPIC_Kernel::Tetrahedron_3 cpp_base;

  const EPIC_Kernel::Tetrahedron_3& get_data() const;
  EPIC_Kernel::Tetrahedron_3& get_data_ref();
//Creation
  Tetrahedron_3();
  Tetrahedron_3(const Point_3& p,const Point_3& q,const Point_3& r,const Point_3& s);
  Tetrahedron_3(const EPIC_Kernel::Tetrahedron_3& p);

//Operations
  FORWARD_CALL_1(Point_3,vertex,int)
//Predicates
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_1(bool,has_on_positive_side,Point_3)
  FORWARD_CALL_1(bool,has_on_negative_side,Point_3)
  FORWARD_CALL_1(bool,has_on_boundary,Point_3)
  FORWARD_CALL_1(bool,has_on_bounded_side,Point_3)
  FORWARD_CALL_1(bool,has_on_unbounded_side,Point_3)
  FORWARD_CALL_0(Orientation,orientation)
  FORWARD_CALL_1(Oriented_side,oriented_side,Point_3)
  FORWARD_CALL_1(Bounded_side,bounded_side,Point_3)
//Miscellaneous
  FORWARD_CALL_0(double,volume)

  bool equals(const Tetrahedron_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Tetrahedron_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_TETRAHEDRON_3_H


//Miscellaneous
//  Bbox_3  t.bbox ()  returns a bounding box containing t.
//  Tetrahedron_3<Kernel>  t.transform ( Aff_transformation_3<Kernel> at)
