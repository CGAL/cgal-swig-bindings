#ifndef SWIG_CGAL_KERNEL_WEIGHTED_POINT_2_H
#define SWIG_CGAL_KERNEL_WEIGHTED_POINT_2_H

#include <CGAL/Weighted_point.h>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>

class SWIG_CGAL_KERNEL_DECL Weighted_point_2{
  CGAL::Weighted_point<EPIC_Kernel::Point_2,double> data;
public:
  #ifndef SWIG
  typedef CGAL::Weighted_point<EPIC_Kernel::Point_2,double> cpp_base;
  const cpp_base& get_data() const;
  cpp_base& get_data_ref();
  Weighted_point_2(const cpp_base& p);
  #endif

  Weighted_point_2();
  Weighted_point_2(double x,double y);
  Weighted_point_2(const Point_2&,double);
  Point_2 point() const;
  double weight() const;
  double x() const;
  double y() const;
  bool equals(const Weighted_point_2&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Weighted_point_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_WEIGHTED_POINT_2_H
