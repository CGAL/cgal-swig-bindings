// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_REGULAR_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_REGULAR_TRIANGULATION_2_H

#include <SWIG_CGAL/Triangulation_2/Triangulation_2.h>

#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>


template <class Triangulation,class Vertex_handle, class Face_handle>
class Regular_triangulation_2_wrapper: public Triangulation_2_wrapper<Triangulation,Weighted_point_2,Vertex_handle,Face_handle,CGAL::Tag_true>
{
  typedef Triangulation_2_wrapper<Triangulation,Weighted_point_2,Vertex_handle,Face_handle,CGAL::Tag_true> Base;
public:
  #ifndef SWIG  
  typedef Triangulation cpp_base;
  Regular_triangulation_2_wrapper(const cpp_base& base) : Base(base) {}
  #endif
  typedef std::pair<Face_handle,int> Edge;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Hidden_vertices_iterator,Vertex_handle> Hidden_vertices_iterator;
  Regular_triangulation_2_wrapper() : Base() {}
// Access functions
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_hidden_vertices)
  Hidden_vertices_iterator hidden_vertices() {return Hidden_vertices_iterator(this->get_data().hidden_vertices_begin(),this->get_data().hidden_vertices_end());}
// Dual power diagram    
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Weighted_point_2,weighted_circumcenter,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Weighted_point_2,dual,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Object,dual,Edge)
// Predicates
  SWIG_CGAL_FORWARD_CALL_2(Oriented_side,power_test,Face_handle,Weighted_point_2)
//Deep copy
  #ifndef CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2
  typedef Regular_triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle> Self;
  Self deepcopy() const {return Self(this->get_data());}
  #endif
};

#endif //SWIG_CGAL_TRIANGULATION_2_REGULAR_TRIANGULATION_2_H

// Queries
//   template <class OutputItFaces, class OutputItBoundaryEdges, class OutputItHiddenVertices>
//   CGAL::Triple<OutputItFaces,OutputItBoundaryEdges,OutputItHiddenVertices>
//   rt.get_conflicts_and_boundary_and_hidden_vertices (Weighted_point p,OutputItFaces fit,OutputItBoundaryEdges eit,OutputItHiddenVertices vit,Face_handle start)
//   template <class OutputItFaces, class OutputItBoundaryEdges>
//   std::pair<OutputItFaces,OutputItBoundaryEdges>
//   rt.get_conflicts_and_boundary (Weighted_point p,OutputItFaces fit,OutputItBoundaryEdges eit,Face_handle start)
//   template <class OutputItFaces, class OutputItHiddenVertices>
//   std::pair<OutputItFaces,OutputItHiddenVertices>
//   rt.get_conflicts_and_hidden_vertices (   Weighted_point p,OutputItFaces fit,OutputItHiddenVertices vit,Face_handle start)
//   template <class OutputItBoundaryEdges, class OutputItHiddenVertices>
//   std::pair<OutputItBoundaryEdges,OutputItHiddenVertices>
//   rt.get_boundary_of_conflicts_and_hidden_vertices (Weighted_point p,OutputItBoundaryEdges eit,OutputItHiddenVertices vit,Face_handle start)
//   template <class OutputItFaces>
//   OutputItFaces   rt.get_conflicts ( Point p, OutputItFaces fit, Face_handle start)
//   template <class OutputItBoundaryEdges>
//   OutputItBoundaryEdges   rt.get_boundary_of_conflicts ( Point p, OutputItBoundaryEdges eit, Face_handle start)
//   template <class OutputItHiddenVertices>
//   OutputItHiddenVertices   rt.get_hidden_vertices ( Point p, OutputItHiddenVertices vit, Face_handle start)
//   Vertex_handle   rt.nearest_power_vertex ( Bare_point p)
// Dual power diagram
//   Object   rt.dual ( Edge_circulator ec)
//   Object   rt.dual ( Edge_iterator ei)
//   template < class Stream>
//   Stream&   rt.draw_dual ( Stream & ps)

