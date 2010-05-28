#ifndef SWIG_CGAL_KERNEL_POINT_2_H
#define SWIG_CGAL_KERNEL_POINT_2_H

#include "typedefs.h"


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Point_2{
  EPIC_Kernel::Point_2 data;
public:
  typedef EPIC_Kernel::Point_2 cpp_base;

  const EPIC_Kernel::Point_2& get_data() const;
  EPIC_Kernel::Point_2& get_data_ref();
  Point_2();
  Point_2(double x,double y);
  Point_2(const EPIC_Kernel::Point_2& p);
  double x();
  double y();
  bool equals(const Point_2&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Point_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_POINT_2_H
