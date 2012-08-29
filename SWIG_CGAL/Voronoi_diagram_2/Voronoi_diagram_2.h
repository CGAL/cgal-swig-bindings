// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H

template <class CppBase, class SiteWrapper, class TriangulationWrapper>
class Voronoi_diagram_wrapper_2{
  #ifndef SWIG
  CppBase data;
  typedef CppBase cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
public:
//Creation
  Voronoi_diagram_wrapper_2(){}
  Voronoi_diagram_wrapper_2(TriangulationWrapper& triangulation,bool swap_dg = false):data( triangulation.get_data(), swap_dg) {}
  //~ Voronoi_diagram_wrapper_2(SiteRange range) : data( SWIG_CGAL::get_begin(range), SWIG_CGAL::get_end(range) ){}
};

template <class CppBase, class SiteWrapper, class TriangulationWrapper>
class Voronoi_diagram_wrapper_with_insert_2
  : public Voronoi_diagram_wrapper_2< CppBase, SiteWrapper, TriangulationWrapper>
{
};

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H




//
//Access Methods
//  Delaunay_graph  vd.dual()
//  Halfedge_handle  vd.dual(Delaunay_edge e)
//  Face_handle  vd.dual ( Delaunay_vertex_handle v)
//  Vertex_handle  vd.dual ( Delaunay_face_handle f)
//  Adaptation_traits  vd.adaptation_traits ()
//  Adaptation_policy  vd.adaptation_policy ()
//  size_type  vd.number_of_vertices ()
//  size_type  vd.number_of_faces ()
//  size_type  vd.number_of_halfedges ()
//  size_type  vd.number_of_connected_components ()
//  Face_handle  vd.unbounded_face ()
//  Face_handle  vd.bounded_face ()
//  Halfedge_handle  vd.unbounded_halfedge ()
//  Halfedge_handle  vd.bounded_halfedge ()
//
//Traversal of the Voronoi diagram
//  Iterators
//    Face_iterator  vd.faces_begin ()  Starts at an arbitrary Voronoi face.
//    Face_iterator  vd.faces_end ()  Past-the-end iterator.
//
//    Unbounded_faces_iterator  vd.unbounded_faces_begin ()
//    Unbounded_faces_iterator  vd.unbounded_faces_end ()
//
//    Bounded_faces_iterator  vd.bounded_faces_begin ()
//    Bounded_faces_iterator  vd.bounded_faces_end ()
//
//    Edge_iterator  vd.edges_begin ()
//    Edge_iterator  vd.edges_end ()
//
//    Halfedge_iterator  vd.halfedges_begin ()
//    Halfedge_iterator  vd.halfedges_end ()
//
//    Unbounded_halfedges_iterator  vd.unbounded_halfedges_begin ()
//    Unbounded_halfedges_iterator  vd.unbounded_halfedges_end ()
//
//    Bounded_halfedges_iterator  vd.bounded_halfedges_begin ()
//    Bounded_halfedges_iterator  vd.bounded_halfedges_end ()
//
//    Vertex_iterator  vd.vertices_begin ()
//    Vertex_iterator  vd.vertices_end ()
//
//    Site_iterator  vd.sites_begin ()
//    Site_iterator  vd.sites_end ()
//
//  Circulators
//
//    Ccb_halfedge_circulator  vd.ccb_halfedges ( Face_handle f)
//    Ccb_halfedge_circulator  vd.ccb_halfedges ( Face_handle f, Halfedge_handle h)
//
//    Halfedge_around_vertex_circulator  vd.incident_halfedges ( Vertex_handle v)
//    Halfedge_around_vertex_circulator  vd.incident_halfedges ( Vertex_handle v, Halfedge_handle h)
//
//Insertion
//  Face_handle  vd.insert ( Site_2 t)
//  template<class Iterator>  size_type  vd.insert ( Iterator first, Iterator beyond)
//
//Queries
//  Locate_result  vd.locate ( Point_2 p)
//I/O
//  void  vd.file_output ( std::ostream& os)
//  std::ostream& operator<<(std::ostream&, Delaunay_graph)
//  void  vd.file_input ( std::istream& is)
//  std::istream& operator>>(std::istream&, Delaunay_graph)
//
//  std::ostream&  std::ostream& os << vd
//  The following operator must be defined:
//  std::ostream& operator<<(std::ostream&, Delaunay_graph)
//  std::istream&  std::istream& is >> vd
//  The following operator must be defined:
//  std::istream& operator>>(std::istream&, Delaunay_graph)
//
//Validity check
//  bool  vd.is_valid ()
//
//Miscellaneous
//  void  vd.clear ()
//  void  vd.swap ( other)
