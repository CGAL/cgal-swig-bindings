// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_DELAUNAY_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_DELAUNAY_TRIANGULATION_2_H

#include <SWIG_CGAL/Triangulation_2/Constrained_triangulation_2.h>

#include <CGAL/Constrained_Delaunay_triangulation_2.h>

template <class Triangulation,class Vertex_handle, class Face_handle>
class Constrained_Delaunay_triangulation_2_wrapper: public Constrained_triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle>
{
  typedef Constrained_triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle> Base;
public:
  typedef Triangulation cpp_base;  

  Constrained_Delaunay_triangulation_2_wrapper():Base(){}
  Constrained_Delaunay_triangulation_2_wrapper(Constraint_range range):Base(){
    for (Input_constraint_iterator it=SWIG_CGAL::get_begin(range);it!=SWIG_CGAL::get_end(range);++it)
      this->get_data().push_back(*it);
  }
  #ifndef SWIG
  Constrained_Delaunay_triangulation_2_wrapper(const cpp_base& cbase):Base(cbase){}
  #endif
//Deep copy
  typedef Constrained_Delaunay_triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle> Self;
  Self deepcopy() const {return Self(this->get_data());}
};

#endif //SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_DELAUNAY_TRIANGULATION_2_H


// Creation
//   Constrained_Delaunay_triangulation_2<Traits,Tds,Itag> cdt ( Constrained_Delaunay_triangulation_2 cdt1)
// Queries
//   template <class OutputItFaces, class OutputItBoundaryEdges>
//   std::pair<OutputItFaces,OutputItBoundaryEdges>
//   cdt.get_conflicts_and_boundary (Point p,OutputItFaces fit,OutputItBoundaryEdges eit,Face_handle start)
//   template <class OutputItFaces>
//   OutputItFaces   cdt.get_conflicts ( Point p, OutputItFaces fit, Face_handle start)
//   template <class OutputItBoundaryEdges>
//   OutputItBoundaryEdges   cdt.get_boundary_of_conflicts ( Point p, OutputItBoundaryEdges eit, Face_handle start)
// Flips
//   bool   cdt.is_flipable ( Face_handle f, int i)
//   void   cdt.flip ( Face_handle& f, int i)
//   void   cdt.propagating_flip ( List_edges & edges)
