#ifndef SWIG_CGAL_BOX_INTERSECTION_D_BOX_WITH_ID
#define SWIG_CGAL_BOX_INTERSECTION_D_BOX_WITH_ID

#include <CGAL/Box_intersection_d/Box_d.h>
#include <SWIG_CGAL/Kernel/Bbox_2.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>

#ifndef SWIG
template <int DIM>
struct Box_with_id :
  public CGAL::Box_intersection_d::Box_d< double, DIM, CGAL::Box_intersection_d::ID_NONE>
{
  typedef CGAL::Box_intersection_d::Box_d< double, DIM, CGAL::Box_intersection_d::ID_NONE> base;
  int id_;
  Box_with_id(): id_(-1) {}
  template <class BBox>
  Box_with_id(const BBox& bbox, int i) : base(bbox), id_(i) {}
  int id() const {return id_;}
};
#endif

struct Box_with_id_2{
  #ifndef SWIG
  typedef Box_with_id<2> cpp_base;
  cpp_base data;
  cpp_base& get_data() { return data; }
  const cpp_base& get_data() const { return data; }
  Box_with_id_2( const cpp_base& base):data(base) {}
  #endif
  Box_with_id_2(const Bbox_2& bbox ,unsigned int id) : data(bbox.get_data(), id)  {}
};

struct Box_with_id_3{
  #ifndef SWIG
  typedef Box_with_id<3> cpp_base;
  cpp_base data;
  cpp_base& get_data() { return data; }
  const cpp_base& get_data() const { return data; }
  Box_with_id_3( const cpp_base& base):data(base) {}
  #endif
  Box_with_id_3(const Bbox_3& bbox ,unsigned int id) : data(bbox.get_data(), id)  {}
};

#endif // SWIG_CGAL_BOX_INTERSECTION_D_BOX_WITH_ID
