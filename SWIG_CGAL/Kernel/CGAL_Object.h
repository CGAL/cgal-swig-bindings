#ifndef SWIG_CGAL_KERNEL_OBJECT_H
#define SWIG_CGAL_KERNEL_OBJECT_H

#include "../Common/Macros.h"
#include "Plane_3.h"
#include "Point_3.h"
#include "Segment_3.h"
#include "Triangle_2.h"
#include "Line_3.h"
#include "Point_2.h"
#include "Segment_2.h"
#include "Triangle_3.h"

#include <CGAL/Object.h>

#define DECLARE_FCT_IS_AND_GET(TYPE) \
  bool is_##TYPE()  { return data.is<TYPE::cpp_base>(); } \
  TYPE get_##TYPE() { return TYPE ( CGAL::object_cast<TYPE::cpp_base>(data) ); }
  

class CGAL_Object
{
  CGAL::Object data;
public:
  typedef CGAL::Object cpp_base;
  const cpp_base& get_data(){return data;}
  cpp_base& get_data_ref(){return data;}
  
  CGAL_Object(){}
  CGAL_Object(const cpp_base& base):data(base){}
    
  DECLARE_FCT_IS_AND_GET(Point_2)
  DECLARE_FCT_IS_AND_GET(Point_3)
  DECLARE_FCT_IS_AND_GET(Triangle_2)
  DECLARE_FCT_IS_AND_GET(Triangle_3)
  DECLARE_FCT_IS_AND_GET(Segment_3)
  DECLARE_FCT_IS_AND_GET(Segment_2)
  DECLARE_FCT_IS_AND_GET(Line_3)
  DECLARE_FCT_IS_AND_GET(Plane_3)
    
  FORWARD_CALL_0(bool,empty)
};


#endif //SWIG_CGAL_KERNEL_OBJECT_H
