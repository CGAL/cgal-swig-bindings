#ifndef SWIG_CGAL_KERNEL_SPHERE_3_H
#define SWIG_CGAL_KERNEL_SPHERE_3_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/enum.h>


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Sphere_3{
  EPIC_Kernel::Sphere_3 data;
public:
  typedef EPIC_Kernel::Sphere_3 cpp_base;  

  const cpp_base& get_data() const{return data;}
  cpp_base& get_data_ref() {return data;}

  bool equals(const Sphere_3& s){return data==s.get_data();}
  
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();    
  }

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Sphere_3& s){return !equals(s);}
  #endif  
  
  Sphere_3(const cpp_base& base):data(base){}
  
//Creation
  Sphere_3(const Point_3& center, double squared_radius, Orientation o):data(center.get_data(),squared_radius,internal::make_conversion(o)){}
  Sphere_3(const Point_3& center, double squared_radius):data(center.get_data(),squared_radius){}
    
  Sphere_3(Point_3 p, Point_3 q, Point_3 r, Point_3 s):data(p.get_data(),q.get_data(),r.get_data(),s.get_data()){}
    
  Sphere_3(Point_3 p, Point_3 q, Point_3 r, Orientation o):data(p.get_data(),q.get_data(),r.get_data(),internal::make_conversion(o)){}
  Sphere_3(Point_3 p, Point_3 q, Point_3 r):data(p.get_data(),q.get_data(),r.get_data()){}
    
  Sphere_3(Point_3 p, Point_3 q, Orientation o):data(p.get_data(),q.get_data(),internal::make_conversion(o)){}
  Sphere_3(Point_3 p, Point_3 q):data(p.get_data(),q.get_data()){}
    
  Sphere_3(Point_3 center, Orientation o):data(center.get_data(),internal::make_conversion(o)){}  
  Sphere_3(Point_3 center):data(center.get_data()){}
//Access Functions
  FORWARD_CALL_0(Point_3,center)
  FORWARD_CALL_0(double,squared_radius)
  FORWARD_CALL_0(Orientation,orientation)  
//Predicates
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_1(Oriented_side,oriented_side,Point_3)
  FORWARD_CALL_1(Bounded_side,bounded_side,Point_3)
  FORWARD_CALL_1(bool,has_on_positive_side,Point_3)
  FORWARD_CALL_1(bool,has_on_negative_side,Point_3)
  FORWARD_CALL_1(bool,has_on_boundary,Point_3)
  FORWARD_CALL_1(bool,has_on_bounded_side,Point_3)
  FORWARD_CALL_1(bool,has_on_unbounded_side,Point_3)
  FORWARD_CALL_1(bool,has_on,Point_3)
//  FORWARD_CALL_1(bool,has_on ( Circle_3<Kernel> p)
//Miscellaneous
  FORWARD_CALL_0(Sphere_3,opposite)
};

#endif //SWIG_CGAL_KERNEL_SPHERE_3_H


//Creation
// Sphere_3<Kernel> c ( Circle_3<Kernel> c);
//Miscellaneous
//  Sphere_3<Kernel>  c.orthogonal_transform ( Aff_transformation_3<Kernel> at)  
//  Bbox_3  c.bbox ()  returns a bounding box containing c.
