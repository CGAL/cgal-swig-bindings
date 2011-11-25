#ifndef SWIG_CGAL_KERNEL_OBJECT_H
#define SWIG_CGAL_KERNEL_OBJECT_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Triangle_2.h>
#include <SWIG_CGAL/Kernel/Line_3.h>
#include <SWIG_CGAL/Kernel/Line_2.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Segment_2.h>
#include <SWIG_CGAL/Kernel/Triangle_3.h>
#include <SWIG_CGAL/Kernel/Ray_2.h>
#include <SWIG_CGAL/Kernel/Ray_3.h>


#include <CGAL/Object.h>

#define SWIG_CGAL_DECLARE_FCT_IS_AND_GET(TYPE) \
  bool is_##TYPE()  { return data.is<TYPE::cpp_base>(); } \
  TYPE get_##TYPE() { return TYPE ( CGAL::object_cast<TYPE::cpp_base>(data) ); }
  

class SWIG_CGAL_KERNEL_DECL CGAL_Object
{
  CGAL::Object data;
  typedef CGAL_Object Self;
  //disable deep copy (CGAL::Object is reference counted)
  Self deepcopy();
  void deepcopy(const Self&);  
public:
  #ifndef SWIG
  typedef CGAL::Object cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  CGAL_Object(const cpp_base& base):data(base){}
  #endif

//Creation
  CGAL_Object(){};
//function to set and get "stored" object
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Point_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Point_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Triangle_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Triangle_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Segment_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Segment_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Line_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Line_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Plane_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Ray_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Ray_3)
//Predicate    
  SWIG_CGAL_FORWARD_CALL_0(bool,empty)
};

#undef SWIG_CGAL_DECLARE_FCT_IS_AND_GET

#endif //SWIG_CGAL_KERNEL_OBJECT_H
