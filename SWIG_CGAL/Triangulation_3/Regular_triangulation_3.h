// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_3_REGULAR_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_REGULAR_TRIANGULATION_3_H

#include <SWIG_CGAL/Triangulation_3/Triangulation_3.h>

template <class Triangulation,class Vertex_handle_, class Cell_handle_,
class Memory_holder
#ifndef SWIG
=void*
#endif
>
class Regular_triangulation_3_wrapper:public Triangulation_3_wrapper<Triangulation,Weighted_point_3,Vertex_handle_,Cell_handle_,CGAL::Tag_true,Memory_holder>{
public:
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Weighting_helper_3<CGAL::Tag_true>::Point_range Point_range;
  #else
  typedef Generic_input_iterator<Weighted_point_3> Point_range;
  #endif  

  typedef Triangulation_3_wrapper<Triangulation,Weighted_point_3,Vertex_handle_,Cell_handle_,CGAL::Tag_true,Memory_holder> Base;
  typedef typename Base::Facet Facet;
  typedef typename Base::Edge Edge;
  typedef Vertex_handle_ Vertex_handle;
  typedef Cell_handle_ Cell_handle;
//Creation
  Regular_triangulation_3_wrapper(){}
  Regular_triangulation_3_wrapper(Point_range range):Base(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range)){}    
  #ifndef SWIG
  Regular_triangulation_3_wrapper(const Triangulation& base):Base(base){}
  //constructor using a triangulation stored outside the wrapper class ( introduced for C3T3::triangulation() )
  Regular_triangulation_3_wrapper(typename Base::cpp_base* base,Memory_holder mh):Base(base,mh){}
  #endif
//Removal
  SWIG_CGAL_FORWARD_CALL_1(void,remove,Vertex_handle)  
//Queries
  SWIG_CGAL_FORWARD_CALL_2(Bounded_side,side_of_power_sphere,Cell_handle,Weighted_point_3)
  SWIG_CGAL_FORWARD_CALL_2(Bounded_side,side_of_power_circle,Facet,Weighted_point_3)
  SWIG_CGAL_FORWARD_CALL_3(Bounded_side,side_of_power_circle,Cell_handle,int,Weighted_point_3)
  SWIG_CGAL_FORWARD_CALL_2(Bounded_side,side_of_power_segment,Cell_handle,Weighted_point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,nearest_power_vertex,Weighted_point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,nearest_power_vertex,Weighted_point_3,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,nearest_power_vertex_in_cell,Weighted_point_3,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_Gabriel,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_3(bool,is_Gabriel,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_Gabriel,Facet)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_Gabriel,Edge)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_Gabriel,Vertex_handle)
//Power diagram
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Weighted_point_3,dual,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Object,dual,Facet)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Object,dual,Cell_handle,int)
};

//Queries
// template <class OutputIteratorBoundaryFacets, class OutputIteratorCells, class OutputIteratorInternalFacets> Triple<OutputIteratorBoundaryFacets, OutputIteratorCells, OutputIteratorInternalFacets> rt.find_conflicts ( const Weighted_point p, Cell_handle c,OutputIteratorBoundaryFacets bfit,OutputIteratorCells cit,OutputIteratorInternalFacets ifit)
// template <class OutputIterator> OutputIterator rt.vertices_in_conflict ( Point p, Cell_handle c, OutputIterator res)
//Power diagram
// template <class Stream> Stream & rt.draw_dual ( Stream & os) Sends the set of duals to all the facets of rt into os.

#endif //SWIG_CGAL_TRIANGULATION_3_REGULAR_TRIANGULATION_3_H
