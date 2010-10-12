#ifndef SWIG_CGAL_KERNEL_TRIANGLE_3_H
#define SWIG_CGAL_KERNEL_TRIANGLE_3_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <SWIG_CGAL/Common/Macros.h>


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
  #ifndef SWIG
  typedef EPIC_Kernel::Triangle_3 cpp_base;
  const cpp_base& get_data() const;
  cpp_base& get_data_ref();
  Triangle_3(const cpp_base& p);
  #endif
//Creation
  Triangle_3();
  Triangle_3(const Point_3& p,const Point_3& q,const Point_3& r);
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
