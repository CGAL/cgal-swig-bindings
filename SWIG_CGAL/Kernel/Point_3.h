#ifndef SWIG_CGAL_KERNEL_POINT_3_H
#define SWIG_CGAL_KERNEL_POINT_3_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Point_3{
  EPIC_Kernel::Point_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Point_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Point_3(const cpp_base& base):data(base){}
  #endif

//Creation
  Point_3():data(){}
  Point_3(double x,double y,double z):data(x,y,z){}

//Operations   
  double x() const {return data.x();}
  double y() const {return data.y();}
  double z() const {return data.z();}
//Set coordinates (forbidden in C++ CGAL for kernel objects)
  void set_coordinates(double x,double y,double z){
    data=cpp_base(x,y,z);
  };
//equality functors
  bool equals(const Point_3& p){
    return data==p.get_data();
  }
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Point_3& p){return !equals(p);}
  #endif
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }  
};

#endif //SWIG_CGAL_KERNEL_POINT_3_H
