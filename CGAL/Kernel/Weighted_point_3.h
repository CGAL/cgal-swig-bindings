#ifndef SWIG_CGAL_KERNEL_WEIGHTED_POINT_3_H
#define SWIG_CGAL_KERNEL_WEIGHTED_POINT_3_H

#include <CGAL/Weighted_point.h>

#include "typedefs.h"
#include "Point_3.h"

#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Weighted_point_3{
  CGAL::Weighted_point<EPIC_Kernel::Point_3,double> data;
public:
  typedef CGAL::Weighted_point<EPIC_Kernel::Point_3,double> cpp_base;

  const cpp_base& get_data() const;
  cpp_base& get_data_ref();
  Weighted_point_3();
  Weighted_point_3(double x,double y,double z);
  Weighted_point_3(const Point_3&,double);
  Weighted_point_3(const cpp_base& p);
  Point_3 point() const;
  double weight() const;
  double x() const;
  double y() const;
  double z() const;
  bool equals(const Weighted_point_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Weighted_point_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_WEIGHTED_POINT_3_H
