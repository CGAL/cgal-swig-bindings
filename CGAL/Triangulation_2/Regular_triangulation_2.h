#ifndef SWIG_CGAL_TRIANGULATION_2_REGULAR_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_REGULAR_TRIANGULATION_2_H

#include "Triangulation_2.h"

#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>

template <class Triangulation,class Vertex_handle, class Face_handle>
class Regular_triangulation_2_wrapper: public Triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle>
{
  typedef Triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle> Base;
public:  
  typedef Triangulation cpp_base;
  Regular_triangulation_2_wrapper() : Base() {}
};

#endif //SWIG_CGAL_TRIANGULATION_2_REGULAR_TRIANGULATION_2_H


// Insertion and Removal
//   Vertex_handle   rt.insert ( Weighted_point p, Face_handle f=Face_handle())
//   Vertex_handle   rt.insert ( Weighted_point p, Locate_type lt, Face_handle loc, int li)
//   Vertex_handle   rt.push_back ( Point p)
//   template < class InputIterator >
//   int   rt.insert ( InputIterator first, InputIterator last)
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
// Access functions
//   int   rt.number_of_vertices ()
//   int   rt.number_of_hidden_vertices ()
//   Hidden_vertices_iterator   rt.hidden_vertices_begin ()
//   Hidden_vertices_iterator   rt.hidden_vertices_end ()
//   Finite_vertices_iterator   rt.finite_vertices_begin ()
//   Finite_vertices_iterator   rt.finite_vertices_end ()
//   All_vertices_iterator   rt.all_vertices_end ()
//   All_vertices_iterator   rt.all_vertices_begin ()
// Dual power diagram
//   Point   rt.weighted_circumcenter ( Face_handle f)
//   Point   rt.dual ( Face_handle f)
//   Object   rt.dual ( Edge e)
//   Object   rt.dual ( Edge_circulator ec)
//   Object   rt.dual ( Edge_iterator ei)
//   template < class Stream>
//   Stream&   rt.draw_dual ( Stream & ps)
// Predicates
//   Oriented_side   rt.power_test ( Face_handle f, Weighted_point p)
// Miscellaneous
//   bool   rt.is_valid ( bool verbose = false, int level = 0)
