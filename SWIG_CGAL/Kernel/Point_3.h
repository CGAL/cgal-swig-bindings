#ifndef SWIG_CGAL_KERNEL_POINT_3_H
#define SWIG_CGAL_KERNEL_POINT_3_H

#include <SWIG_CGAL/Kernel/typedefs.h>


class SWIG_CGAL_KERNEL_DECL Point_3{
  EPIC_Kernel::Point_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Point_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Point_3(const cpp_base& p);
  #endif




  Point_3();
  Point_3(double x,double y,double z);
  double x() const;
  double y() const;
  double z() const;
  bool equals(const Point_3&);
  void set_coordinates(double x,double y,double z){
    data=cpp_base(x,y,z);
  };
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Point_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_POINT_3_H
