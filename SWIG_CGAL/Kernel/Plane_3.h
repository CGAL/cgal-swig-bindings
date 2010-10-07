#ifndef SWIG_CGAL_KERNEL_PLANE_3_H
#define SWIG_CGAL_KERNEL_PLANE_3_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>

#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Segment_3;

class Plane_3{
  EPIC_Kernel::Plane_3 data;
public:
  typedef EPIC_Kernel::Plane_3 cpp_base;  

  const EPIC_Kernel::Plane_3& get_data() const;
  EPIC_Kernel::Plane_3& get_data_ref();
  Plane_3();
  Plane_3(double a,double b,double c,double d);
  Plane_3(const EPIC_Kernel::Plane_3& p);
  Plane_3(const Segment_3& s, const Point_3& p); 
  Plane_3(const Point_3& p, const Point_3& q, const Point_3& r); 
  double a();
  double b();
  double c();
  double d();

  Point_3 projection(const Point_3& p);

  bool equals(const Plane_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Plane_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_PLANE_3_H
