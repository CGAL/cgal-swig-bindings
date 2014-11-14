// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_KERNEL_BBOX_2_DEF_H
#define SWIG_CGAL_KERNEL_BBOX_2_DEF_H

#include <sstream>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>

class SWIG_CGAL_KERNEL_DECL Bbox_2{
  CGAL::Bbox_2 data;
public:
  #ifndef SWIG
  typedef CGAL::Bbox_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Bbox_2(const cpp_base& base):data(base){}
  #endif
//Creation
  Bbox_2(){}
  Bbox_2 (double x_min, double y_min, double x_max, double y_max):data(x_min,y_min,x_max,y_max){}
//Operations
  int dimension () const {return 2;}
  double xmin () const {return data.xmin();}
  double ymin () const {return data.ymin();}
  double xmax () const {return data.xmax();}
  double ymax () const {return data.ymax();}
  double min (int i) const {return data.min(i);}
  double max (int i) const {return data.max(i);}
// Operators
  inline Bbox_2 operator+ (const Bbox_2 &c) const;
  inline Bbox_2& operator+= (const Bbox_2 &c);
  DEFINE_EQUALITY_OPERATORS(Bbox_2)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Bbox_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_BBOX_2_DEF_H
