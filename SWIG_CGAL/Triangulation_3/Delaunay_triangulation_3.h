// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_3_DELAUNAY_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_DELAUNAY_TRIANGULATION_3_H

#include <SWIG_CGAL/Triangulation_3/Triangulation_3.h>

template <class Triangulation,class Vertex_handle_, class Cell_handle_, 
class Memory_holder
#ifndef SWIG
=void*
#endif
>
class Delaunay_triangulation_3_wrapper:public Triangulation_3_wrapper<Triangulation,Point_3,Vertex_handle_,Cell_handle_,CGAL::Tag_false,Memory_holder>{
 
public:
  typedef Triangulation_3_wrapper<Triangulation,Point_3,Vertex_handle_,Cell_handle_,CGAL::Tag_false,Memory_holder> Base;
  typedef Delaunay_triangulation_3_wrapper<Triangulation,Vertex_handle_,Cell_handle_,Memory_holder> Self;
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Weighting_helper_3<CGAL::Tag_false>::Point_range Point_range;
  #else
  typedef Generic_input_iterator<Point_3> Point_range;
  #endif

  #ifndef SWIG
  typedef typename Base::cpp_base cpp_base;
  Delaunay_triangulation_3_wrapper(const cpp_base& base):Base(base){}
  //constructor using a triangulation stored outside the wrapper class (by symmetry with regular triangulation)
  Delaunay_triangulation_3_wrapper(typename Base::cpp_base* base,Memory_holder mh):Base(base,mh){} 
  #endif

  typedef typename Base::Edge Edge;
  typedef typename Base::Facet Facet;
  typedef Vertex_handle_ Vertex_handle;
  typedef Cell_handle_ Cell_handle;

//Creation
  Delaunay_triangulation_3_wrapper():Base(){}
  Delaunay_triangulation_3_wrapper(const Delaunay_triangulation_3_wrapper& dt):Base(static_cast<const Base&>(dt)){};
  Delaunay_triangulation_3_wrapper(Point_range range):Base(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range)){}
//Point moving
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,move,Vertex_handle,Point_3);
//Removal
  SWIG_CGAL_FORWARD_CALL_1(void,remove,Vertex_handle)
//Queries
  SWIG_CGAL_FORWARD_CALL_2(Bounded_side,side_of_sphere,Cell_handle,Point_3)
  SWIG_CGAL_FORWARD_CALL_2(Bounded_side,side_of_circle,Facet,Point_3)
  SWIG_CGAL_FORWARD_CALL_3(Bounded_side,side_of_circle,Cell_handle,int,Point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,nearest_vertex,Point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,nearest_vertex,Point_3,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,nearest_vertex_in_cell,Point_3,Cell_handle)    
  SWIG_CGAL_FORWARD_CALL_2(bool,is_Gabriel,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_3(bool,is_Gabriel,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_Gabriel,Facet)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_Gabriel,Edge)
//Voronoi diagram
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_3,dual,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Object,dual,Facet) 
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Object,dual,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Line_3,dual_support,Cell_handle,int)
//overload dual for convenience
  Self deepcopy() const {
    Self ret;
    static_cast<Base&>(ret).deepcopy(
      static_cast<const Base&>(*this));
    return ret;
  }
  void deepcopy(const Self& other){
    this->deepcopy(other);
  }
};

//Removal
// template < typename InputIterator > int dt.remove ( InputIterator first, InputIterator beyond)
//Queries
// template <class OutputIteratorBoundaryFacets, class OutputIteratorCells> std::pair<OutputIteratorBoundaryFacets, OutputIteratorCells> dt.find_conflicts ( Point p,Cell_handle c,OutputIteratorBoundaryFacets bfit,OutputIteratorCells cit)
// template <class OutputIteratorBoundaryFacets, class OutputIteratorCells, class OutputIteratorInternalFacets> Triple<OutputIteratorBoundaryFacets, OutputIteratorCells, OutputIteratorInternalFacets> dt.find_conflicts ( Point p,Cell_handle c,OutputIteratorBoundaryFacets bfit,OutputIteratorCells cit,OutputIteratorInternalFacets ifit)
// template <class OutputIterator> OutputIterator dt.vertices_in_conflict ( Point p, Cell_handle c, OutputIterator res)
//Voronoi diagram
// template <class Stream> Stream & dt.draw_dual ( Stream & os) Sends the set of duals to all the facets of dt into os.


#endif //SWIG_CGAL_TRIANGULATION_3_DELAUNAY_TRIANGULATION_3_H


