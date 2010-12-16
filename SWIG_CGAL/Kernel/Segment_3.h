#ifndef SWIG_CGAL_KERNEL_SEGMENT_3_H
#define SWIG_CGAL_KERNEL_SEGMENT_3_H

#include <SWIG_CGAL/Kernel/include_conflicts_3.h>

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Line_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Kernel/Direction_3.h>

class SWIG_CGAL_KERNEL_DECL Segment_3{
  EPIC_Kernel::Segment_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Segment_3 cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}
  Segment_3(const cpp_base& s):data(s){}
  #endif

  Segment_3();
  Segment_3(const Point_3& p1, const Point_3& p2);

  FORWARD_CALL_AND_REF_0(Point_3,source)
  FORWARD_CALL_AND_REF_0(Point_3,target)
  FORWARD_CALL_AND_REF_0(Point_3,min)
  FORWARD_CALL_AND_REF_0(Point_3,max)
  FORWARD_CALL_AND_REF_1(Point_3,vertex,int)
  FORWARD_CALL_AND_REF_1(Point_3,point,int)
  FORWARD_CALL_0(double,squared_length)
  FORWARD_CALL_AND_REF_0(Segment_3,opposite)
  FORWARD_CALL_0(bool,is_degenerate)
  FORWARD_CALL_1(bool,has_on,Point_3)

  DECLARE_CALL_AND_REF_0(Vector_3,to_vector)
  DECLARE_CALL_AND_REF_0(Direction_3,direction)
  DECLARE_CALL_AND_REF_0(Line_3,supporting_line)
  
  bool equals(const Segment_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Segment_3&);
  #endif
};





#endif //SWIG_CGAL_KERNEL_SEGMENT_3_H

//Bbox_3 s.bbox () returns a bounding box containing s.
//Segment_3<Kernel> s.transform ( Aff_transformation_3<Kernel> t)
//Point_3<Kernel> s.operator[] ( int i)
