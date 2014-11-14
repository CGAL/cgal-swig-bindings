// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_POINT_2_DEF_H
#define SWIG_CGAL_KERNEL_POINT_2_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_2.h>
#include <SWIG_CGAL/Kernel/Bbox_2.h>
#include <SWIG_CGAL/Common/Macros.h>
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
  Point_2(const Origin&):data(CGAL::ORIGIN){}
  Point_2(double x,double y):data(x,y){}
//Operations
  double x() const {return data.x();}
  double y() const {return data.y();}
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_2,bbox)
//Set coordinates (forbidden in C++ CGAL for kernel objects)
  void set_coordinates(double x,double y){
    data=cpp_base(x,y);
  };
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Operators
  inline Vector_2 operator-(Point_2&);
  inline Point_2 operator+(Vector_2&);
  inline Point_2 operator-(Vector_2&);
  inline Vector_2 operator-(const Origin&);
  inline bool operator==(const Origin&){return get_data()==CGAL::ORIGIN;}
  DEFINE_COMPARISON_OPERATORS(Point_2)
//Operators added for convenience
  inline Point_2& operator+=(Vector_2&);
  inline Point_2& operator-=(Vector_2&);
//Deep copy
  typedef Point_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_POINT_2_DEF_H
