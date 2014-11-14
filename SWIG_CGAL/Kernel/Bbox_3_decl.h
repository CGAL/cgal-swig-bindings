// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_KERNEL_BBOX_3_DEF_H
#define SWIG_CGAL_KERNEL_BBOX_3_DEF_H

#include <sstream>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Bbox_3{
  CGAL::Bbox_3 data;
public:
  #ifndef SWIG
  typedef CGAL::Bbox_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Bbox_3(const cpp_base& base):data(base){}
  #endif
//Creation
  Bbox_3(){}
  Bbox_3 (double x_min, double y_min, double z_min,
          double x_max, double y_max, double z_max)
    : data(x_min,y_min,z_min,x_max,y_max,z_max)
  {}
//Operations
  int dimension () const {return 3;}
  double xmin () const {return data.xmin();}
  double ymin () const {return data.ymin();}
  double zmin () const {return data.zmin();}
  double xmax () const {return data.xmax();}
  double ymax () const {return data.ymax();}
  double zmax () const {return data.zmax();}
  double min (int i) const {return data.min(i);}
  double max (int i) const {return data.max(i);}
// Operators
  inline Bbox_3 operator+ (const Bbox_3 &c) const;
  inline Bbox_3& operator+= (const Bbox_3 &c);
  DEFINE_EQUALITY_OPERATORS(Bbox_3)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Bbox_3 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_BBOX_3_DEF_H
