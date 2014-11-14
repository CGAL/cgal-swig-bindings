// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_POINT_3_DEF_H
#define SWIG_CGAL_KERNEL_POINT_3_DEF_H

#include <sstream>
#include <SWIG_CGAL/Kernel/include_conflicts_3.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>
#include <SWIG_CGAL/Common/Macros.h>
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
  Point_3(const Origin&):data(CGAL::ORIGIN){}
  Point_3(double x,double y,double z):data(x,y,z){}

//Operations   
  double x() const {return data.x();}
  double y() const {return data.y();}
  double z() const {return data.z();}
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_3,bbox)
//Set coordinates (forbidden in C++ CGAL for kernel objects)
  void set_coordinates(double x,double y,double z){
    data=cpp_base(x,y,z);
  };
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Operators
  inline Vector_3 operator-(Point_3&);
  inline Point_3 operator+(Vector_3&);
  inline Point_3 operator-(Vector_3&);
  inline Vector_3 operator-(const Origin&);
  inline bool operator==(const Origin&){return get_data()==CGAL::ORIGIN;}
  DEFINE_COMPARISON_OPERATORS(Point_3)
//Operators added for convenience
  inline Point_3& operator+=(Vector_3&);
  inline Point_3& operator-=(Vector_3&);
//Deep copy
  typedef Point_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_POINT_3_DEF_H
