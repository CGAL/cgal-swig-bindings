#ifndef SWIG_CGAL_BOX_INTERSECTION_D_BOX_WITH_ID
#define SWIG_CGAL_BOX_INTERSECTION_D_BOX_WITH_ID

#include <CGAL/Box_intersection_d/Box_d.h>
#include <SWIG_CGAL/Kernel/Bbox_2.h>
#include <SWIG_CGAL/Kernel/Bbox_3.h>
#include <SWIG_CGAL/Kernel/Segment_2.h>

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

template <int DIM>
struct Box_with_id_and_polyline_id :
  public CGAL::Box_intersection_d::Box_d< double, DIM, CGAL::Box_intersection_d::ID_NONE>
{
  typedef CGAL::Box_intersection_d::Box_d< double, DIM, CGAL::Box_intersection_d::ID_NONE> base;
  int id_;
  int polyline_id_;
  Segment_2::cpp_base segment_2_;

  Box_with_id_and_polyline_id(): id_(-1) {}
  Box_with_id_and_polyline_id(const Segment_2::cpp_base& s, int polyline_id, int i)
    : base(s.bbox()), id_(i), polyline_id_(polyline_id), segment_2_(s) {}
  int id() const {return id_;}
  int polyline_id() const { return polyline_id_; }
  const Segment_2::cpp_base& segment_2() const { return segment_2_; }
};


#endif

struct Box_for_segment_polyline_2{
  #ifndef SWIG
  typedef Box_with_id_and_polyline_id<2> cpp_base;
  cpp_base data;
  cpp_base& get_data() { return data; }
  const cpp_base& get_data() const { return data; }
  Box_for_segment_polyline_2( const cpp_base& base):data(base) {}
  #endif
  Box_for_segment_polyline_2(const Segment_2& s, int polyline_id, int id)
    : data(s.get_data(), polyline_id, id)  {}
};

struct Box_with_id_2{
  #ifndef SWIG
  typedef Box_with_id<2> cpp_base;
  cpp_base data;
  cpp_base& get_data() { return data; }
  const cpp_base& get_data() const { return data; }
  Box_with_id_2( const cpp_base& base):data(base) {}
  #endif
  Box_with_id_2(const Bbox_2& bbox, int id) : data(bbox.get_data(), id)  {}
};

struct Box_with_id_3{
  #ifndef SWIG
  typedef Box_with_id<3> cpp_base;
  cpp_base data;
  cpp_base& get_data() { return data; }
  const cpp_base& get_data() const { return data; }
  Box_with_id_3( const cpp_base& base):data(base) {}
  #endif
  Box_with_id_3(const Bbox_3& bbox ,int id) : data(bbox.get_data(), id)  {}
};

#endif // SWIG_CGAL_BOX_INTERSECTION_D_BOX_WITH_ID
