// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_LOCATE_RESULT_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_LOCATE_RESULT_H


template <class Vertex_wrapper, class Halfedge_wrapper, class Face_wrapper>
class Locate_result_wrapper{
public:
  #ifndef SWIG
  typedef boost::variant<typename Face_wrapper::cpp_base,typename Halfedge_wrapper::cpp_base,typename Vertex_wrapper::cpp_base> cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Locate_result_wrapper(const cpp_base& base):data(base){}
  #endif

  Locate_result_wrapper(){}
  
  Vertex_wrapper get_vertex_handle() const {return Vertex_wrapper( boost::get< typename Vertex_wrapper::cpp_base > ( data ) ); }
  Halfedge_wrapper get_halfedge_handle() const {return Halfedge_wrapper( boost::get< typename Halfedge_wrapper::cpp_base > ( data ) ); }
  Face_wrapper get_face_handle() const {return Face_wrapper( boost::get< typename Face_wrapper::cpp_base > ( data ) ); }
  
  bool is_vertex_handle() const { return boost::get < typename Vertex_wrapper::cpp_base > ( &data ); }
  bool is_halfedge_handle() const { return boost::get< typename Halfedge_wrapper::cpp_base > ( &data ); }
  bool is_face_handle() const { return boost::get< typename Face_wrapper::cpp_base > ( &data ); }
  
private:
  #ifndef SWIG
  cpp_base data;
  #endif
};

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_LOCATE_RESULT_H
