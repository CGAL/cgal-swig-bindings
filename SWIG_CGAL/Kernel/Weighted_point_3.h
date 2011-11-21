#ifndef SWIG_CGAL_KERNEL_WEIGHTED_POINT_3_H
#define SWIG_CGAL_KERNEL_WEIGHTED_POINT_3_H

#include <CGAL/Weighted_point.h>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>

class SWIG_CGAL_KERNEL_DECL Weighted_point_3{
  CGAL::Weighted_point<EPIC_Kernel::Point_3,double> data;
public:
  #ifndef SWIG
  typedef CGAL::Weighted_point<EPIC_Kernel::Point_3,double> cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Weighted_point_3(const cpp_base& p);
  #endif

  Weighted_point_3();
  Weighted_point_3(double x,double y,double z);
  Weighted_point_3(const Point_3&,double);
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
