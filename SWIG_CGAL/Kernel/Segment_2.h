#ifndef SWIG_CGAL_KERNEL_SEGMENT_2_H
#define SWIG_CGAL_KERNEL_SEGMENT_2_H

#include <SWIG_CGAL/Kernel/include_conflicts_2.h>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Vector_2.h>
#include <SWIG_CGAL/Kernel/Line_2.h>
#include <SWIG_CGAL/Kernel/Direction_2.h>
#include <SWIG_CGAL/Common/Macros.h>

class SWIG_CGAL_KERNEL_DECL Segment_2{
  EPIC_Kernel::Segment_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Segment_2 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Segment_2(const cpp_base& p);
  #endif

  Segment_2();
//Creation
  Segment_2(const Point_2& p,const Point_2& q);
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,source)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,target)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,min)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,max)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,vertex,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,point,int)
  SWIG_CGAL_FORWARD_CALL_0(double,squared_length)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Segment_2,opposite)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Direction_2,direction)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Vector_2,to_vector)
  SWIG_CGAL_DECLARE_CALL_AND_REF_0(Line_2,supporting_line)

//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_horizontal)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_vertical)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,collinear_has_on,Point_2)
  
  bool equals(const Segment_2&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Segment_2&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_SEGMENT_2_H

//Miscellaneous
//  Bbox_2   s.bbox ()   returns a bounding box containing s.
//  Segment_2<Kernel>   s.transform ( Aff_transformation_2<Kernel> t)
