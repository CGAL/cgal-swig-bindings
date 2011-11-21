#ifndef SWIG_CGAL_KERNEL_TETRAHEDRON_3_H
#define SWIG_CGAL_KERNEL_TETRAHEDRON_3_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Common/Macros.h>


class SWIG_CGAL_KERNEL_DECL Tetrahedron_3{
  EPIC_Kernel::Tetrahedron_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Tetrahedron_3 cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Tetrahedron_3(const cpp_base& p);
  #endif

//Creation
  Tetrahedron_3();
  Tetrahedron_3(const Point_3& p,const Point_3& q,const Point_3& r,const Point_3& s);
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_3,vertex,int)
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_degenerate)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_positive_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_negative_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_0(Orientation,orientation)
  SWIG_CGAL_FORWARD_CALL_1(Oriented_side,oriented_side,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_3)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(double,volume)

  bool equals(const Tetrahedron_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Tetrahedron_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_TETRAHEDRON_3_H


//Miscellaneous
//  Bbox_3  t.bbox ()  returns a bounding box containing t.
//  Tetrahedron_3<Kernel>  t.transform ( Aff_transformation_3<Kernel> at)
