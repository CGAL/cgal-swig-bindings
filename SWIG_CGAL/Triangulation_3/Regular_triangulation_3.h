#ifndef SWIG_CGAL_TRIANGULATION_3_REGULAR_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_REGULAR_TRIANGULATION_3_H

#include <SWIG_CGAL/Triangulation_3/Triangulation_3.h>
#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Regular_triangulation_euclidean_traits_3.h>

template <class Triangulation,class Vertex_handle_, class Cell_handle_>
class Regular_triangulation_3_wrapper:public Triangulation_3_wrapper<Triangulation,Weighted_point_3,Vertex_handle_,Cell_handle_,CGAL::Tag_true>{
public:
  typedef Triangulation_3_wrapper<Triangulation,Weighted_point_3,Vertex_handle_,Cell_handle_,CGAL::Tag_true> Base;
  typedef typename Base::Facet Facet;
  typedef typename Base::Edge Edge;
  typedef Vertex_handle_ Vertex_handle;
  typedef Cell_handle_ Cell_handle;
//Creation
  Regular_triangulation_3_wrapper(){}
  #ifndef SWIG
  Regular_triangulation_3_wrapper(const Triangulation& base):Base(base){}
  #endif
//Removal
  FORWARD_CALL_1(void,remove,Vertex_handle)  
//Queries
  FORWARD_CALL_2(Bounded_side,side_of_power_sphere,Cell_handle,Weighted_point_3)
  FORWARD_CALL_2(Bounded_side,side_of_power_circle,Facet,Weighted_point_3)
  FORWARD_CALL_3(Bounded_side,side_of_power_circle,Cell_handle,int,Weighted_point_3)
  FORWARD_CALL_2(Bounded_side,side_of_power_segment,Cell_handle,Weighted_point_3)
  FORWARD_CALL_1(Vertex_handle,nearest_power_vertex,Weighted_point_3)
  FORWARD_CALL_2(Vertex_handle,nearest_power_vertex,Weighted_point_3,Cell_handle)
  FORWARD_CALL_2(Vertex_handle,nearest_power_vertex_in_cell,Weighted_point_3,Cell_handle)
  FORWARD_CALL_2(bool,is_Gabriel,Cell_handle,int)
  FORWARD_CALL_3(bool,is_Gabriel,Cell_handle,int,int)
  FORWARD_CALL_1(bool,is_Gabriel,Facet)
  FORWARD_CALL_1(bool,is_Gabriel,Edge)
  FORWARD_CALL_1(bool,is_Gabriel,Vertex_handle)
};

//Creation
// template < class InputIterator > Regular_triangulation_3<RegularTriangulationTraits_3,TriangulationDataStructure_3> rt ( InputIterator first,InputIterator last,RegularTriangulationTraits_3 traits = RegularTriangulationTraits_3());
//Queries
// template <class OutputIteratorBoundaryFacets, class OutputIteratorCells, class OutputIteratorInternalFacets> Triple<OutputIteratorBoundaryFacets, OutputIteratorCells, OutputIteratorInternalFacets> rt.find_conflicts ( const Weighted_point p, Cell_handle c,OutputIteratorBoundaryFacets bfit,OutputIteratorCells cit,OutputIteratorInternalFacets ifit)
// template <class OutputIterator> OutputIterator rt.vertices_in_conflict ( Point p, Cell_handle c, OutputIterator res)
//Power diagram
// Weighted_point_3 rt.dual ( Cell_handle c) Returns the weighted circumcenter of the four vertices of c.
// Object rt.dual ( Facet f) Returns the dual of facet f, which is
// Object rt.dual ( Cell_handle c, int i) same as the previous method for facet (c,i).
// template <class Stream> Stream & rt.draw_dual ( Stream & os) Sends the set of duals to all the facets of rt into os.

#endif //SWIG_CGAL_TRIANGULATION_3_REGULAR_TRIANGULATION_3_H
