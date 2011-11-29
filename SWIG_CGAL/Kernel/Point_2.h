// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_POINT_2_H
#define SWIG_CGAL_KERNEL_POINT_2_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Point_2{
  EPIC_Kernel::Point_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Point_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Point_2(const cpp_base& base):data(base){}
  #endif

//Creation
  Point_2():data(){}
  Point_2(double x,double y):data(x,y){}
//Operations
  double x() const {return data.x();}
  double y() const {return data.y();}
//Set coordinates (forbidden in C++ CGAL for kernel objects)
  void set_coordinates(double x,double y){
    data=cpp_base(x,y);
  };
//equality functions
  bool equals(const Point_2& p){
    return data==p.get_data();
  }
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Point_2& p){return !equals(p);}
  #endif
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Point_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_POINT_2_H
