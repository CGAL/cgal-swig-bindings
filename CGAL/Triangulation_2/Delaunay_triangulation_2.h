#ifndef SWIG_CGAL_TRIANGULATION_2_DELAUNAY_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_DELAUNAY_TRIANGULATION_2_H

#include "Triangulation_2.h"

template <class Triangulation,class Vertex_handle, class Face_handle>
class Delaunay_triangulation_2_wrapper: public Triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle>
{
  
};

#endif //SWIG_CGAL_TRIANGULATION_2_DELAUNAY_TRIANGULATION_2_H

// Creation
//   Delaunay_triangulation_2<Traits,Tds> dt ( Traits gt = Traits());
//   Delaunay_triangulation_2<Traits,Tds> dt ( tr);
// Insertion and Removal
//   Vertex_handle   dt.insert ( Point p, Face_handle f=Face_handle())
//   Vertex_handle   dt.insert ( Point p, Locate_type& lt, Face_handle loc, int li)
//   Vertex_handle   dt.push_back ( Point p)
//   template < class InputIterator >
//   int   dt.insert ( InputIterator first, InputIterator last)
//   void   dt.remove ( Vertex_handle v)
// Queries
//   Vertex_handle   dt.nearest_vertex ( Point p, Face_handle f=Face_handle())
//   template <class OutputItFaces, class OutputItBoundaryEdges>
//   std::pair<OutputItFaces,OutputItBoundaryEdges>
//   dt.get_conflicts_and_boundary (   Point p,
//   OutputItFaces fit,
//   OutputItBoundaryEdges eit,
//   Face_handle start)
//   template <class OutputItFaces>
//   OutputItFaces   dt.get_conflicts ( Point p, OutputItFaces fit, Face_handle start)
//   template <class OutputItBoundaryEdges>
//   OutputItBoundaryEdges   dt.get_boundary_of_conflicts ( Point p, OutputItBoundaryEdges eit, Face_handle start)
// Voronoi diagram
//   Point   dt.dual ( Face_handle f)
//   Object   dt.dual ( Edge e)
//   Object   dt.dual ( Edge_circulator ec)
//   Object   dt.dual ( Edge_iterator ei)
//   template < class Stream>
//   Stream&   dt.draw_dual ( Stream & ps)
// Predicates
//   Oriented_side   dt.side_of_oriented_circle ( Face_handle f, Point p)
// Miscellaneous
//   bool   dt.is_valid ( bool verbose = false, int level = 0)
