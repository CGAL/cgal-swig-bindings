#ifndef SWIG_CGAL_KERNEL_LINE_3_H
#define SWIG_CGAL_KERNEL_LINE_3_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Plane_3;

class Line_3{
  EPIC_Kernel::Line_3 data;
public:
  typedef EPIC_Kernel::Line_3 cpp_base;

  const EPIC_Kernel::Line_3& get_data() const;
  EPIC_Kernel::Line_3& get_data_ref();
  Line_3();
  Line_3(const EPIC_Kernel::Line_3& l);
  Line_3(const Point_3& p1, const Point_3& p2);

  Point_3 projection(const Point_3& p);
  Plane_3 perpendicular_plane(const Point_3& p);
  Line_3 opposite();

  bool equals(const Line_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Line_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_LINE_3_H
