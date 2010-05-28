#ifndef SWIG_CGAL_TRIANGULATION_3_DELAUNAY_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_DELAUNAY_TRIANGULATION_3_H

#include "Triangulation_3.h"

template <class Triangulation,class Vertex_handle, class Cell_handle>
class Delaunay_triangulation_3_wrapper:public Triangulation_3_wrapper<Triangulation,Vertex_handle,Cell_handle>{
 
public:
  typedef typename Triangulation_3_wrapper<Triangulation,Vertex_handle,Cell_handle>::Edge Edge;
  typedef typename Triangulation_3_wrapper<Triangulation,Vertex_handle,Cell_handle>::Facet Facet;

  Delaunay_triangulation_3_wrapper():Triangulation_3_wrapper<Triangulation,Vertex_handle,Cell_handle>(){}
  Delaunay_triangulation_3_wrapper(const Delaunay_triangulation_3_wrapper& dt):Triangulation_3_wrapper<Triangulation,Vertex_handle,Cell_handle>(static_cast<const Triangulation_3_wrapper<Triangulation,Vertex_handle,Cell_handle>&>(dt)){};


  //---------------------------------
  //Delaunay_triangulation_3 wrapping
  //---------------------------------
  FORWARD_CALL_1(void,remove,Vertex_handle)

  FORWARD_CALL_2(Vertex_handle,move_point,Vertex_handle,Point_3);
  FORWARD_CALL_2(Bounded_side,side_of_sphere,Cell_handle,Point_3)
  FORWARD_CALL_2(Bounded_side,side_of_circle,Facet,Point_3)
  FORWARD_CALL_3(Bounded_side,side_of_circle,Cell_handle,int,Point_3)

  FORWARD_CALL_1(Vertex_handle,nearest_vertex,Point_3)
  FORWARD_CALL_2(Vertex_handle,nearest_vertex,Point_3,Cell_handle)

  FORWARD_CALL_2(bool,is_Gabriel,Cell_handle,int)
  FORWARD_CALL_3(bool,is_Gabriel,Cell_handle,int,int)
  FORWARD_CALL_1(bool,is_Gabriel,Facet)
  FORWARD_CALL_1(bool,is_Gabriel,Edge)

  //template < typename InputIterator > int 	dt.remove ( InputIterator first, InputIterator beyond)
  //template <class OutputIteratorBoundaryFacets, class OutputIteratorCells> std::pair<OutputIteratorBoundaryFacets, OutputIteratorCells>
  //dt.find_conflicts ( 	Point p,Cell_handle c,OutputIteratorBoundaryFacets bfit,OutputIteratorCells cit)
  //template <class OutputIteratorBoundaryFacets, class OutputIteratorCells, class OutputIteratorInternalFacets> Triple<OutputIteratorBoundaryFacets, OutputIteratorCells, OutputIteratorInternalFacets>  dt.find_conflicts ( 	Point p, Cell_handle c, OutputIteratorBoundaryFacets bfit, OutputIteratorCells cit, OutputIteratorInternalFacets ifit) 
  //template <class OutputIterator> OutputIterator 	dt.vertices_in_conflict ( Point p, Cell_handle c, OutputIterator res)

  //Point 	dt.dual ( Cell_handle c)
  //Object 	dt.dual ( Facet f)
  //Object 	dt.dual ( Cell_handle c, int i)
  //Line 	dt.dual_support ( Cell_handle c, int i)
  //template <class Stream> Stream & 	dt.draw_dual ( Stream & os)



};


#endif //SWIG_CGAL_TRIANGULATION_3_DELAUNAY_TRIANGULATION_3_H
