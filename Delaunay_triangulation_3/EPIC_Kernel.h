#ifndef CGAL_SWIG_EPIC_KERNEL_H
#define CGAL_SWIG_EPIC_KERNEL_H

#include "typedefs.h"

class EPIC_Point_3{
  EPIC_Kernel::Point_3 data;
public:
  EPIC_Kernel::Point_3 get_data() const;
  EPIC_Point_3();
  EPIC_Point_3(double x,double y,double z);
  EPIC_Point_3(const EPIC_Kernel::Point_3& p);
  double x();
  double y();
  double z();
  bool equals(const EPIC_Point_3&);
  #ifdef SWIGPYTHON
  bool __eq__(const EPIC_Point_3&);
  bool __ne__(const EPIC_Point_3&);
  #endif
};

#endif //CGAL_SWIG_EPIC_KERNEL_H
