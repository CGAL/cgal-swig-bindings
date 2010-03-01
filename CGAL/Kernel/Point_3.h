#ifndef SWIG_CGAL_KERNEL_POINT_3_H
#define SWIG_CGAL_KERNEL_POINT_3_H

#include "typedefs.h"


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Point_3{
  EPIC_Kernel::Point_3 data;
public:
  EPIC_Kernel::Point_3 get_data() const;
  EPIC_Kernel::Point_3& get_data_ref();
  Point_3();
  Point_3(double x,double y,double z);
  Point_3(const EPIC_Kernel::Point_3& p);
  double x();
  double y();
  double z();
  bool equals(const Point_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Point_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_POINT_3_H
