#ifndef SWIG_CGAL_KERNEL_SEGMENT_2_H
#define SWIG_CGAL_KERNEL_SEGMENT_2_H

#include <SWIG_CGAL/Kernel/include_conflicts_2.h>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Vector_2.h>
#include <SWIG_CGAL/Kernel/Line_2.h>
#include <SWIG_CGAL/Kernel/Direction_2.h>
#include <SWIG_CGAL/Common/Macros.h>

class Segment_2{
  EPIC_Kernel::Segment_2 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Segment_2 cpp_base;
  const cpp_base& get_data() const;
  cpp_base& get_data_ref();
  Segment_2(const cpp_base& p);
  #endif

  Segment_2();
//Creation
  Segment_2(const Point_2& p,const Point_2& q);
//Operations
  FORWARD_CALL_AND_REF_0(Point_2,source)
  FORWARD_CALL_AND_REF_0(Point_2,target)
  FORWARD_CALL_AND_REF_0(Point_2,min)
  FORWARD_CALL_AND_REF_0(Point_2,max)
  FORWARD_CALL_AND_REF_1(Point_2,vertex,int)
  FORWARD_CALL_AND_REF_1(Point_2,point,int)
  FORWARD_CALL_0(double,squared_length)
  FORWARD_CALL_AND_REF_0(Segment_2,opposite)
  DECLARE_CALL_AND_REF_0(Direction_2,direction)
  DECLARE_CALL_AND_REF_0(Vector_2,to_vector)
  DECLARE_CALL_AND_REF_0(Line_2,supporting_line)

//Predicates
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_0(bool,is_horizontal)
  FORWARD_CALL_0(bool,is_vertical)
  FORWARD_CALL_1(bool,has_on,Point_2)
  FORWARD_CALL_1(bool,collinear_has_on,Point_2)
  
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
