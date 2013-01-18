// ------------------------------------------------------------------------------
// Copyright (c) 2013 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#include <CGAL/HalfedgeDS_decorator.h>
#include <SWIG_CGAL/HalfedgeDS/HalfedgeDS.h>

#ifndef SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_DECORATOR_H
#define SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_DECORATOR_H

template <class HDS_cpp>
class HalfedgeDS_decorator_wrapper
{
  CGAL::HalfedgeDS_decorator<HDS_cpp> data;
  boost::shared_ptr<HDS_cpp> hds_sptr;
public:
  typedef HalfedgeDS_wrapper<HDS_cpp>    HDS_wrapper;
  typedef HDSVertex_wrapper<HDS_cpp>     Vertex_wrapper;
  typedef HDSHalfedge_wrapper<HDS_cpp>   Hedge_wrapper;
  typedef HDSFace_wrapper<HDS_cpp>       Face_wrapper;

  #ifndef SWIG
  typedef CGAL::HalfedgeDS_decorator<HDS_cpp> cpp_base;

  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
// Creation
  HalfedgeDS_decorator_wrapper(HDS_wrapper& hds)
    : data(hds.get_data()), hds_sptr(hds.shared_ptr() ) {}

// Creation of New Items (a little tweaked as simplices are not exposed)
  Vertex_wrapper vertices_push_back( const Point_2& p){
    return Vertex_wrapper(
      get_data().vertices_push_back( typename HDS_cpp::Vertex(p.get_data() ) ) );
  }
  Vertex_wrapper vertices_push_back(){
    return Vertex_wrapper(
      get_data().vertices_push_back( typename HDS_cpp::Vertex() ) );
  }
  Face_wrapper faces_push_back(){
    return Face_wrapper(
      get_data().faces_push_back( typename HDS_cpp::Face() ) );
  }

// Creation of New Composed Items
  SWIG_CGAL_FORWARD_CALL_0(Hedge_wrapper, create_loop)
  SWIG_CGAL_FORWARD_CALL_0(Hedge_wrapper, create_segment)

// Removal of Elements
  SWIG_CGAL_FORWARD_CALL_0(void, vertices_pop_front)
  SWIG_CGAL_FORWARD_CALL_0(void, vertices_pop_back)
  SWIG_CGAL_FORWARD_CALL_1(void, vertices_erase, Vertex_wrapper)
  SWIG_CGAL_FORWARD_CALL_2(void, vertices_erase, Vertex_wrapper, Vertex_wrapper)
  SWIG_CGAL_FORWARD_CALL_0(void, faces_pop_front)
  SWIG_CGAL_FORWARD_CALL_0(void, faces_pop_back)
  SWIG_CGAL_FORWARD_CALL_1(void, faces_erase, Face_wrapper)
  SWIG_CGAL_FORWARD_CALL_2(void, faces_erase, Face_wrapper , Face_wrapper)
  SWIG_CGAL_FORWARD_CALL_1(void, erase_face, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_1(void, erase_connected_component, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_1(int, keep_largest_connected_components, int)

// Modifying Functions (For Border Halfedges)
  SWIG_CGAL_FORWARD_CALL_1(void, make_hole, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_1(Hedge_wrapper, fill_hole, Hedge_wrapper)
  // Halfedge_handle fill_hole( Halfedge_handle h, const Face& f) not enabled as Face is not exposed
  SWIG_CGAL_FORWARD_CALL_2(Hedge_wrapper, add_face_to_border, Hedge_wrapper, Hedge_wrapper)
  // Halfedge_handle add_face_to_border( Halfedge_handle h, Halfedge_handle g, const Face& f) not enabled as Face is not exposed

// Modifying Functions (Euler Operators)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Hedge_wrapper, split_face, Hedge_wrapper, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Hedge_wrapper, join_face, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Hedge_wrapper, split_vertex, Hedge_wrapper, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Hedge_wrapper, join_vertex, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Hedge_wrapper, create_center_vertex, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Hedge_wrapper, erase_center_vertex, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Hedge_wrapper, split_loop, Hedge_wrapper, Hedge_wrapper, Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Hedge_wrapper, join_loop, Hedge_wrapper, Hedge_wrapper)

// Validness Checks
  SWIG_CGAL_FORWARD_CALL_2(bool, is_valid, bool, int)
  SWIG_CGAL_FORWARD_CALL_1(bool, is_valid, bool)
  SWIG_CGAL_FORWARD_CALL_0(bool, is_valid)
  SWIG_CGAL_FORWARD_CALL_1(bool, normalized_border_is_valid, bool)
  SWIG_CGAL_FORWARD_CALL_0(bool, normalized_border_is_valid)

// Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(void,inside_out)

};

#endif //SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_DECORATOR_H
