#ifndef SWIG_CGAL_KERNEL_POINT_2_H
#define SWIG_CGAL_KERNEL_POINT_2_H

#include <SWIG_CGAL/Kernel/typedefs.h>


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
  #ifndef SWIG
  typedef EPIC_Kernel::Point_2 cpp_base;
  const cpp_base& get_data() const;
  cpp_base& get_data_ref();
  Point_2(const cpp_base& p);
  #endif

  Point_2();
  Point_2(double x,double y);
  double x() const;
  double y() const;
  bool equals(const Point_2&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Point_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_POINT_2_H
