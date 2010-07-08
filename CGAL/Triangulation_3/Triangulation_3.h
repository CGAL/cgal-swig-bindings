#ifndef SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H

#include <boost/function_output_iterator.hpp>
#include <boost/static_assert.hpp>
#include <CGAL/Triangulation_3.h>

#include "triangulation_handles.h"
#include "triangulation_iterators.h"
#include "../Common/triple.h"
#include "../Common/Output_iterator.h"
#include "../Common/Reference_wrapper.h"
#include "../Common/Macros.h"
#include "../Kernel/Point_3.h"
#include "../Kernel/Weighted_point_3.h"

#ifdef SWIGPYTHON
#include "../Python/Input_iterator_wrapper.h"
#include "../Python/Output_iterator_wrapper.h"
#endif
#ifdef SWIGJAVA
#include "../Java/Input_iterator_wrapper.h"
#include "../Java/Output_iterator_wrapper.h"
#endif

enum Locate_type { VERTEX=0, EDGE, FACET, CELL, OUTSIDE_CONVEX_HULL, OUTSIDE_AFFINE_HULL};
enum Bounded_side{ ON_UNBOUNDED_SIDE = -1,ON_BOUNDARY,ON_BOUNDED_SIDE};


template <class Weighted_tag>
struct Weighting_helper_3{
  typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range;
};

template <>
struct Weighting_helper_3<CGAL::Tag_true>{
  typedef std::pair<Input_iterator_wrapper<Weighted_point_3,Weighted_point_3::cpp_base>,Input_iterator_wrapper<Weighted_point_3,Weighted_point_3::cpp_base> > Point_range;
};

template <class Triangulation,class Point,class Vertex_handle, class Cell_handle, class Weighted_tag>
class Triangulation_3_wrapper{
  
  #ifndef SWIG
  BOOST_STATIC_ASSERT( (boost::is_same<Weighted_tag,typename Triangulation::Weighted_tag>::value) );
  #endif  
  
protected:
  Triangulation data;
  const typename Triangulation::Cell_handle& convert (const Cell_handle& c) {return c.get_data();}
  typename Triangulation::Cell_handle& convert (Cell_handle& c) {return c.get_data_ref();}
  const typename Triangulation::Vertex_handle& convert (const Vertex_handle& v) {return v.get_data();}
  typename Triangulation::Vertex_handle& convert (Vertex_handle& v) {return v.get_data_ref();}
  template <class T> const T& convert(const Reference_wrapper<T>& ref){return ref.object();}
  template <class T> T& convert(Reference_wrapper<T>& ref){return ref.object_ref();}
public:
  typedef std::pair<Cell_handle,int>             Facet;
  typedef CGAL_SWIG::Triple<Cell_handle,int,int> Edge;  
  typedef Triangulation cpp_base;

//Iterator typedefs  
  typedef CGAL_Finite_vertices_iterator<Triangulation,Vertex_handle>            Finite_vertices_iterator;
  typedef CGAL_Finite_edges_iterator<Triangulation,Edge>                        Finite_edges_iterator;
  typedef CGAL_Finite_facets_iterator<Triangulation,Facet>                      Finite_facets_iterator;
  typedef CGAL_Finite_cells_iterator<Triangulation,Cell_handle>                 Finite_cells_iterator;
  typedef CGAL_All_vertices_iterator<Triangulation,Vertex_handle>               All_vertices_iterator;
  typedef CGAL_All_edges_iterator<Triangulation,Edge>                           All_edges_iterator;
  typedef CGAL_All_facets_iterator<Triangulation,Facet>                         All_facets_iterator;
  typedef CGAL_All_cells_iterator<Triangulation,Cell_handle>                    All_cells_iterator;
  typedef CGAL_Point_iterator<Triangulation,Point>                              Point_iterator;
  typedef CGAL_Cell_circulator<Triangulation,Cell_handle>                       Cell_circulator;
  typedef CGAL_Facet_circulator<Triangulation,Facet>                            Facet_circulator;
//Output iterator typedefs  
  typedef boost::function_output_iterator< Container_writer<Cell_handle,typename Triangulation::Cell_handle> >          Cell_handle_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Vertex_handle,typename Triangulation::Vertex_handle> >      Vertex_handle_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Facet,typename Triangulation::Facet> >                      Facet_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Edge,typename Triangulation::Edge> >                        Edge_output_iterator;

  Triangulation_3_wrapper(){}
  const Triangulation& get_data() const {return this->data;}

//Creation
//Assignment
  bool equal(const Triangulation_3_wrapper& t) {return t.get_data()==this->data;}
  bool equals(const Triangulation_3_wrapper& t) {return equal(t);}
  #ifdef SWIGPYTHON
  bool __ne__(const Triangulation_3_wrapper& dt) {return !equals(dt);}
  #endif
  FORWARD_CALL_0(void,clear)  
//Access Functions
//Non const access
  FORWARD_CALL_0(int, dimension)
  FORWARD_CALL_0(int, number_of_vertices)
  FORWARD_CALL_0(int, number_of_cells)
  FORWARD_CALL_0(Vertex_handle,infinite_vertex)
  FORWARD_CALL_0(Cell_handle,infinite_cell)  
//Non-constant-time access functions
  FORWARD_CALL_0(int, number_of_facets)
  FORWARD_CALL_0(int, number_of_edges)
  FORWARD_CALL_0(int, number_of_finite_cells)
  FORWARD_CALL_0(int, number_of_finite_facets)
  FORWARD_CALL_0(int, number_of_finite_edges)  
//Geometric access functions
//Tests for Finite and Infinite Vertices and Faces
  FORWARD_CALL_1(bool,is_infinite,Vertex_handle)
  FORWARD_CALL_1(bool,is_infinite,Cell_handle)
  FORWARD_CALL_2(bool,is_infinite,Cell_handle,int)
  FORWARD_CALL_1(bool,is_infinite,Facet)
  FORWARD_CALL_3(bool,is_infinite,Cell_handle,int,int)  
  FORWARD_CALL_1(bool,is_infinite,Edge)
//Queries
  FORWARD_CALL_1(bool,is_vertex,Vertex_handle)
  FORWARD_CALL_1(bool,is_cell,Cell_handle)
  FORWARD_CALL_2(bool,has_vertex,Facet,Vertex_handle)
  FORWARD_CALL_3(bool,has_vertex,Cell_handle,int,Vertex_handle)
  FORWARD_CALL_4(bool,are_equal,Cell_handle,int,Cell_handle,int)
  FORWARD_CALL_2(bool,are_equal,Facet,Facet)
  FORWARD_CALL_3(bool,are_equal,Facet,Cell_handle,int)
//Point location
  FORWARD_CALL_1(Cell_handle,locate,Point)
  FORWARD_CALL_2(Cell_handle,locate,Point,Cell_handle)
  FORWARD_CALL_2(Cell_handle,locate,Point,Vertex_handle)
//Flips
  FORWARD_CALL_1(bool,flip,Edge)
  FORWARD_CALL_3(bool,flip,Cell_handle,int,int)
  FORWARD_CALL_1(void,flip_flippable,Edge)
  FORWARD_CALL_3(void,flip_flippable,Cell_handle,int,int)
  FORWARD_CALL_1(bool,flip,Facet)
  FORWARD_CALL_2(bool,flip,Cell_handle,int)
  FORWARD_CALL_1(void,flip_flippable,Facet)
  FORWARD_CALL_2(void,flip_flippable,Cell_handle,int)
//Insertions
  FORWARD_CALL_1(Vertex_handle,insert,Point)
  FORWARD_CALL_2(Vertex_handle,insert,Point,Cell_handle)
  FORWARD_CALL_2(Vertex_handle,insert,Point,Vertex_handle)
  int insert_range(typename Weighting_helper_3<Weighted_tag>::Point_range range){ return this->data.insert(range.first,range.second); }
  FORWARD_CALL_2(Vertex_handle,insert_in_cell,Point,Cell_handle)
  FORWARD_CALL_2(Vertex_handle,insert_in_facet,Point,Facet)
  FORWARD_CALL_3(Vertex_handle,insert_in_facet,Point,Cell_handle,int)
  FORWARD_CALL_2(Vertex_handle,insert_in_edge,Point,Edge)
  FORWARD_CALL_4(Vertex_handle,insert_in_edge,Point,Cell_handle,int,int)
  FORWARD_CALL_2(Vertex_handle,insert_outside_convex_hull,Point,Cell_handle)
  FORWARD_CALL_1(Vertex_handle,insert_outside_affine_hull,Point)
//Traversal of the Triangulation
  Finite_vertices_iterator      finite_vertices(){return Finite_vertices_iterator(this->data.finite_vertices_begin(),this->data.finite_vertices_end());}
  Finite_edges_iterator         finite_edges(){return Finite_edges_iterator(this->data.finite_edges_begin(),this->data.finite_edges_end());}
  Finite_facets_iterator        finite_facets(){return Finite_facets_iterator(this->data.finite_facets_begin(),this->data.finite_facets_end());}
  Finite_cells_iterator         finite_cells(){return Finite_cells_iterator(this->data.finite_cells_begin(),this->data.finite_cells_end());}
  All_vertices_iterator         all_vertices(){return All_vertices_iterator(this->data.all_vertices_begin(),this->data.all_vertices_end());}
  All_edges_iterator            all_edges(){return All_edges_iterator(this->data.all_edges_begin(),this->data.all_edges_end());}
  All_facets_iterator           all_facets(){return All_facets_iterator(this->data.all_facets_begin(),this->data.all_facets_end());}
  All_cells_iterator            all_cells(){return All_cells_iterator(this->data.all_cells_begin(),this->data.all_cells_end());}
  Point_iterator                points(){return Point_iterator(this->data.points_begin(),this->data.points_end());}
//Cell and Facet Circulators
  FORWARD_CALL_1(Cell_circulator,incident_cells,Edge)
  FORWARD_CALL_3(Cell_circulator,incident_cells,Cell_handle,int,int)
  FORWARD_CALL_2(Cell_circulator,incident_cells,Edge,Cell_handle)
  FORWARD_CALL_4(Cell_circulator,incident_cells,Cell_handle,int,int,Cell_handle)
  FORWARD_CALL_1(Facet_circulator,incident_facets,Edge)
  FORWARD_CALL_3(Facet_circulator,incident_facets,Cell_handle,int,int)
  FORWARD_CALL_2(Facet_circulator,incident_facets,Edge,Facet)
  FORWARD_CALL_3(Facet_circulator,incident_facets,Edge,Cell_handle,int)
  FORWARD_CALL_4(Facet_circulator,incident_facets,Cell_handle,int,int,Facet)
  FORWARD_CALL_5(Facet_circulator,incident_facets,Cell_handle,int,int,Cell_handle,int)  
//Traversal of the incident cells, facets and edges, and the adjacent vertices of a given vertex
  void incident_cells(const Vertex_handle& v, Cell_handle_output_iterator out){this->data.incident_cells(v.get_data(),out);}
  void finite_incident_cells(const Vertex_handle& v, Cell_handle_output_iterator out){this->data.finite_incident_cells(v.get_data(),out);}
  void incident_facets(const Vertex_handle& v, Facet_output_iterator out){    this->data.incident_facets(v.get_data(),out);  }
  void finite_incident_facets(const Vertex_handle& v, Facet_output_iterator out){this->data.finite_incident_facets(v.get_data(),out);}
  void incident_edges(const Vertex_handle& v, Edge_output_iterator out){this->data.incident_edges(v.get_data(),out);}
  void finite_incident_edges(const Vertex_handle& v, Edge_output_iterator out){this->data.finite_incident_edges(v.get_data(),out);}
  void adjacent_vertices(const Vertex_handle& v, Vertex_handle_output_iterator out){this->data.adjacent_vertices(v.get_data(),out);}
  void finite_adjacent_vertices(const Vertex_handle& v, Vertex_handle_output_iterator out){this->data.finite_adjacent_vertices(v.get_data(),out);}
  FORWARD_CALL_1(int,degree,Vertex_handle)  
//Traversal between adjacent cells
  FORWARD_CALL_2(int,mirror_index,Cell_handle,int)
  FORWARD_CALL_2(Vertex_handle,mirror_vertex,Cell_handle,int)  
  FORWARD_CALL_1(Facet,mirror_facet,Facet)
//Checking
  FORWARD_CALL_0(bool,is_valid)
  FORWARD_CALL_1(bool,is_valid,bool)
  FORWARD_CALL_1(bool,is_valid,Cell_handle)
  FORWARD_CALL_2(bool,is_valid,Cell_handle,bool)
//I/O  


  FORWARD_CALL_2(Point,point,Cell_handle,int)
  FORWARD_CALL_1(Point,point,Vertex_handle)




  bool is_cell (Vertex_handle u,Vertex_handle v,Vertex_handle w,Vertex_handle x,Cell_handle & c,Reference_wrapper<int>& i,Reference_wrapper<int> & j,Reference_wrapper<int> & k,Reference_wrapper<int> & l){
    return this->data.is_cell(convert(u),convert(v),convert(w),convert(x),convert(c),convert(i),convert(j),convert(k),convert(l));
  }
  
};

//Creation
// template < class InputIterator> Triangulation_3<TriangulationTraits_3,TriangulationDataStructure_3> t ( InputIterator first,InputIterator last,TriangulationTraits_3 traits = TriangulationTraits_3());
//Assignment
//  Triangulation_3 & t = Triangulation_3 tr
//  void t.swap ( Triangulation_3 & tr)
//Access Functions
//  TriangulationTraits_3 t.geom_traits ()
//  TriangulationDataStructure_3 t.tds ()
//Non const access
//  TriangulationDataStructure_3 & t.tds()
//Geometric access functions
//  Tetrahedron t.tetrahedron ( Cell_handle c)
//  Triangle t.triangle ( Cell_handle c, int i)
//  Triangle t.triangle ( Facet f)
//  Segment t.segment ( Edge e)
//  Segment t.segment ( Cell_handle c, int i, int j)
//  Point t.point ( Cell_handle c, int i)
//  Point t.point ( Vertex_handle v)
//Queries
//  bool t.is_vertex ( Point p, Vertex_handle & v)  
//  bool t.is_edge ( Vertex_handle u, Vertex_handle v, Cell_handle & c, int & i, int & j)
//  bool t.is_facet ( Vertex_handle u,Vertex_handle v,Vertex_handle w,Cell_handle & c,int & i,int & j,int & k)
//  bool t.is_cell ( Vertex_handle u,Vertex_handle v,Vertex_handle w,Vertex_handle x,Cell_handle & c,int & i,int & j,int & k,int & l)
//  bool t.is_cell ( Vertex_handle u, Vertex_handle v, Vertex_handle w, Vertex_handle x, Cell_handle & c)
//  bool t.has_vertex ( Facet f, Vertex_handle v, int & j)
//  bool t.has_vertex ( Cell_handle c, int i, Vertex_handle v, int & j)
//Point location
//  Cell_handle t.locate ( Point query, Locate_type & lt, int & li, int & lj, Cell_handle start = Cell_handle())
//  Cell_handle t.locate ( Point query, Locate_type & lt, int & li, int & lj, Vertex_handle hint)
//  Bounded_side t.side_of_cell ( Point p, Cell_handle c, Locate_type & lt, int & li, int & lj)
//  Bounded_side t.side_of_facet ( Point p, Facet f, Locate_type & lt, int & li, int & lj)
//  Bounded_side t.side_of_edge ( Point p, Edge e, Locate_type & lt, int & li)
//  Bounded_side t.side_of_edge ( Point p, Cell_handle c, Locate_type & lt, int & li)
//Insertions
//  Vertex_handle t.insert ( Point p, Locate_type lt, Cell_handle loc, int li, int lj)  
//  template <class CellIt> Vertex_handle t.insert_in_hole ( Point p, CellIt cell_begin, CellIt cell_end, Cell_handle begin, int i)
//  template <class CellIt> Vertex_handle t.insert_in_hole ( Point p,CellIt cell_begin,CellIt cell_end,Cell_handle begin,int i,Vertex_handle newv)
//I/O
//  istream& istream& is >> Triangulation_3 &t
//  ostream& ostream& os << Triangulation_3 t Writes the triangulation t into os.


#endif //SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H
