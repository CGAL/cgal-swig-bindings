#ifndef SWIG_CGAL_AABB_TREE_OBJECT_H
#define SWIG_CGAL_AABB_TREE_OBJECT_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Line_3.h>
#include <SWIG_CGAL/Kernel/Triangle_3.h>
#include <SWIG_CGAL/Kernel/Ray_3.h>
#include <SWIG_CGAL/AABB_tree/decl.h>


#include <CGAL/Object.h>

#define DECLARE_FCT_IS_AND_GET(TYPE) \
  bool is_##TYPE()  { return data.is<TYPE::cpp_base>(); } \
  TYPE get_##TYPE() { return TYPE ( CGAL::object_cast<TYPE::cpp_base>(data) ); }
  

class SWIG_CGAL_AABB_TREE_DECL Object
{
  CGAL::Object data;
public:
  #ifndef SWIG
  typedef CGAL::Object cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Object(const cpp_base& base);
  #endif

  Object();
    

  DECLARE_FCT_IS_AND_GET(Point_3)
  DECLARE_FCT_IS_AND_GET(Triangle_3)
  DECLARE_FCT_IS_AND_GET(Segment_3)
  DECLARE_FCT_IS_AND_GET(Line_3)
  DECLARE_FCT_IS_AND_GET(Plane_3)
  DECLARE_FCT_IS_AND_GET(Ray_3)
    
  SWIG_CGAL_FORWARD_CALL_0(bool,empty)
};

#undef DECLARE_FCT_IS_AND_GET

#endif //SWIG_CGAL_AABB_TREE_OBJECT_H
