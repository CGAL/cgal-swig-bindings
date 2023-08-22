// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_LOCATE_RESULT_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_LOCATE_RESULT_H

#if CGAL_VERSION_NR >= 1060000000
#include <variant>
#else // CGAL < 6.0
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#endif

template <class Vertex_wrapper, class Halfedge_wrapper, class Face_wrapper>
class Locate_result_wrapper{
public:
  #ifndef SWIG
#if CGAL_VERSION_NR >= 1060000000
  typedef   std::variant<typename Face_wrapper::cpp_base,typename Halfedge_wrapper::cpp_base,typename Vertex_wrapper::cpp_base> cpp_base;
#else
  typedef boost::variant<typename Face_wrapper::cpp_base,typename Halfedge_wrapper::cpp_base,typename Vertex_wrapper::cpp_base> cpp_base;
#endif
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Locate_result_wrapper(const cpp_base& base):data(base){}
  #endif

  Locate_result_wrapper(){}
  
#if CGAL_VERSION_NR >= 1060000000
  Vertex_wrapper get_vertex_handle() const {return Vertex_wrapper( std::get< typename Vertex_wrapper::cpp_base > ( data ) ); }
  Halfedge_wrapper get_halfedge_handle() const {return Halfedge_wrapper( std::get< typename Halfedge_wrapper::cpp_base > ( data ) ); }
  Face_wrapper get_face_handle() const {return Face_wrapper( std::get< typename Face_wrapper::cpp_base > ( data ) ); }

  bool is_vertex_handle() const { return std::get_if< typename Vertex_wrapper::cpp_base > ( &data ); }
  bool is_halfedge_handle() const { return std::get_if< typename Halfedge_wrapper::cpp_base > ( &data ); }
  bool is_face_handle() const { return std::get_if< typename Face_wrapper::cpp_base > ( &data ); }
#else
  Vertex_wrapper get_vertex_handle() const {return Vertex_wrapper( boost::get< typename Vertex_wrapper::cpp_base > ( data ) ); }
  Halfedge_wrapper get_halfedge_handle() const {return Halfedge_wrapper( boost::get< typename Halfedge_wrapper::cpp_base > ( data ) ); }
  Face_wrapper get_face_handle() const {return Face_wrapper( boost::get< typename Face_wrapper::cpp_base > ( data ) ); }

  bool is_vertex_handle() const { return boost::get < typename Vertex_wrapper::cpp_base > ( &data ); }
  bool is_halfedge_handle() const { return boost::get< typename Halfedge_wrapper::cpp_base > ( &data ); }
  bool is_face_handle() const { return boost::get< typename Face_wrapper::cpp_base > ( &data ); }
#endif
private:
  #ifndef SWIG
  cpp_base data;
  #endif
};

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_LOCATE_RESULT_H
