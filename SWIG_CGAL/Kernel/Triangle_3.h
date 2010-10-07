#ifndef SWIG_CGAL_KERNEL_TRIANGLE_3_H
#define SWIG_CGAL_KERNEL_TRIANGLE_3_H

#include "typedefs.h"
#include "Point_3.h"
#include "Plane_3.h"
#include "../Common/Macros.h"


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Triangle_3{
  EPIC_Kernel::Triangle_3 data;
public:
  typedef EPIC_Kernel::Triangle_3 cpp_base;

  const EPIC_Kernel::Triangle_3& get_data() const;
  EPIC_Kernel::Triangle_3& get_data_ref();
//Creation
  Triangle_3();
  Triangle_3(const Point_3& p,const Point_3& q,const Point_3& r);
  Triangle_3(const EPIC_Kernel::Triangle_3& p);
//Operations
  FORWARD_CALL_1(Point_3,vertex,int)
  FORWARD_CALL_0(Plane_3,supporting_plane)
//Predicates
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_1(bool,has_on,Point_3)
//Miscellaneous
  FORWARD_CALL_0(double,squared_area)
  bool equals(const Triangle_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Triangle_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_TRIANGLE_3_H

//Miscellaneous
//  Bbox_3  t.bbox ()  returns a bounding box containing t.
//  Triangle_3<Kernel>  t.transform ( Aff_transformation_3<Kernel> at)
