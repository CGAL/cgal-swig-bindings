// ------------------------------------------------------------------------------
// Copyright (c) 2013 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_HANDLE_H
#define SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_HANDLE_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_2.h>

template <class HDS_cpp>
class HDSHalfedge_wrapper;

template <class HDS_cpp>
class HDSVertex_wrapper;

template <class HDS_cpp>
class HDSFace_wrapper {
  typename HDS_cpp::Face_handle data;
public:
  #ifndef SWIG
  typedef typename HDS_cpp::Face_handle cpp_base;

  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  HDSFace_wrapper(const cpp_base& base):data(base){}
  #endif

// Creation
  HDSFace_wrapper():data(){}
// Operations available if Supports_face_halfedge == CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(HDSHalfedge_wrapper<HDS_cpp>,halfedge)
  SWIG_CGAL_FORWARD_CALL_1(void,set_halfedge,HDSHalfedge_wrapper<HDS_cpp>)

//Deep copy
  typedef HDSFace_wrapper<HDS_cpp> Self;
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){get_data()=other.get_data();}
//equality functions
  DEFINE_EQUALITY_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
};

template <class HDS_cpp>
class HDSHalfedge_wrapper {
  typename HDS_cpp::Halfedge_handle data;
public:
  #ifndef SWIG
  typedef typename HDS_cpp::Halfedge_handle cpp_base;

  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  HDSHalfedge_wrapper(const cpp_base& base):data(base){}
  #endif

/// Creation
  HDSHalfedge_wrapper():data(){}
/// Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(HDSHalfedge_wrapper<HDS_cpp>,opposite)
  //this does not exist and is a mistake in the concept
  //SWIG_CGAL_FORWARD_CALL_1(void,set_opposite,HDSHalfedge_wrapper<HDS_cpp>)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(HDSHalfedge_wrapper<HDS_cpp>,next)
  SWIG_CGAL_FORWARD_CALL_1(void,set_next,HDSHalfedge_wrapper<HDS_cpp>)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_border)
/// Operations available if Supports_halfedge_prev == CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(HDSHalfedge_wrapper<HDS_cpp>,prev)
  SWIG_CGAL_FORWARD_CALL_1(void,set_prev,HDSHalfedge_wrapper<HDS_cpp>)
// Operations available if Supports_halfedge_vertex == CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(HDSVertex_wrapper<HDS_cpp>,vertex)
  SWIG_CGAL_FORWARD_CALL_1(void,set_vertex,HDSVertex_wrapper<HDS_cpp>)
// Operations available if Supports_halfedge_face == CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_0(HDSFace_wrapper<HDS_cpp>,face)
  SWIG_CGAL_FORWARD_CALL_1(void,set_face,HDSFace_wrapper<HDS_cpp>);

//Deep copy
  typedef HDSHalfedge_wrapper<HDS_cpp> Self;
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){get_data()=other.get_data();}
//equality functions
  DEFINE_EQUALITY_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
};

template <class HDS_cpp>
class HDSVertex_wrapper{
  typename HDS_cpp::Vertex_handle data;
public:
  #ifndef SWIG
  typedef typename HDS_cpp::Vertex_handle cpp_base;

  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  HDSVertex_wrapper(const cpp_base& base):data(base){}
  #endif

// Creation
  HDSVertex_wrapper():data(){}
// Operations available if Supports_vertex_halfedge == CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(HDSHalfedge_wrapper<HDS_cpp>,halfedge)
  SWIG_CGAL_FORWARD_CALL_1(void,set_halfedge,HDSHalfedge_wrapper<HDS_cpp>)
// Operations with point
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,point)
  void set_point( const Point_2& p){get_data()->point()=p.get_data();}

//Deep copy
  typedef HDSVertex_wrapper<HDS_cpp> Self;
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){get_data()=other.get_data();}
//equality functions
  DEFINE_EQUALITY_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
};


#endif //SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_HANDLE_H
