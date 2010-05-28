#ifndef SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H

#include <boost/function_output_iterator.hpp>

#include "../Kernel/Point_3.h"
#include "typedefs.h"
#include "triangulation_handles.h"
#include "triangulation_iterators.h"
#include "../Common/triple.h"
#include "../Common/Output_iterator.h"
#include "../Common/Reference_wrapper.h"
#include "../Common/Macros.h"


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

typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range;
#ifdef SWIGJAVA
typedef boost::function_output_iterator< Container_writer<Point_3,Point_3::cpp_base> > Point_output_iterator;
#endif
#ifdef SWIGPYTHON
typedef boost::function_output_iterator< Container_writer<Point_3,Point_3::cpp_base> > Point_output_iterator;
#endif


template <class Triangulation,class Vertex_handle, class Cell_handle>
class Triangulation_3_wrapper{
protected:
  Triangulation data;
  typename Triangulation::Cell_handle convert (const Cell_handle& c) {return c.get_data();}
  typename Triangulation::Cell_handle& convert (Cell_handle& c) {return c.get_data_ref();}
  typename Triangulation::Vertex_handle convert (const Vertex_handle& v) {return v.get_data();}
  typename Triangulation::Vertex_handle& convert (Vertex_handle& v) {return v.get_data_ref();}
  template <class T> const T& convert(const Reference_wrapper<T>& ref){return ref.object();}
  template <class T> T& convert(Reference_wrapper<T>& ref){return ref.object_ref();}
public:
  typedef std::pair<Cell_handle,int>             Facet;
  typedef CGAL_SWIG::Triple<Cell_handle,int,int> Edge;  

  Triangulation_3_wrapper(){}
  const Triangulation& get_data() const {return this->data;}

  FORWARD_CALL_0(int, dimension)
  FORWARD_CALL_0(int, number_of_vertices)
  FORWARD_CALL_0(int, number_of_cells)
  FORWARD_CALL_0(int, number_of_facets)
  FORWARD_CALL_0(int, number_of_edges)
  FORWARD_CALL_0(int, number_of_finite_cells)
  FORWARD_CALL_0(int, number_of_finite_facets)
  FORWARD_CALL_0(int, number_of_finite_edges)
  FORWARD_CALL_0(Vertex_handle,infinite_vertex)
  FORWARD_CALL_0(Cell_handle,infinite_cell)
  FORWARD_CALL_1(bool,is_infinite,Vertex_handle)
  FORWARD_CALL_1(bool,is_infinite,Cell_handle)
  FORWARD_CALL_1(bool,is_infinite,Facet)
  FORWARD_CALL_1(bool,is_infinite,Edge)
  FORWARD_CALL_2(bool,is_infinite,Cell_handle,int)
  FORWARD_CALL_3(bool,is_infinite,Cell_handle,int,int)
  FORWARD_CALL_1(bool,is_vertex,Vertex_handle)
  FORWARD_CALL_1(bool,is_cell,Cell_handle)
  FORWARD_CALL_1(Cell_handle,locate,Point_3)
  FORWARD_CALL_2(Cell_handle,locate,Point_3,Cell_handle)
  FORWARD_CALL_2(Cell_handle,locate,Point_3,Vertex_handle)
  FORWARD_CALL_0(bool,is_valid)
  FORWARD_CALL_1(bool,is_valid,bool)
  FORWARD_CALL_1(bool,is_valid,Cell_handle)
  FORWARD_CALL_2(bool,is_valid,Cell_handle,bool)
  FORWARD_CALL_1(Facet,mirror_facet,Facet)
  FORWARD_CALL_2(Point_3,point,Cell_handle,int)
  FORWARD_CALL_1(Point_3,point,Vertex_handle)
  FORWARD_CALL_0(void,clear)


  bool equal(const Triangulation_3_wrapper& t) {return t.get_data()==this->data;}
  bool equals(const Triangulation_3_wrapper& t) {return equal(t);}
  #ifdef SWIGPYTHON
  bool __ne__(const Triangulation_3_wrapper& dt) {return !equals(dt);}
  #endif

  CGAL_Finite_vertices_iterator<Triangulation,Vertex_handle> finite_vertices(){return CGAL_Finite_vertices_iterator<Triangulation,Vertex_handle>(this->data.finite_vertices_begin(),this->data.finite_vertices_end());}
  CGAL_Finite_edges_iterator<Triangulation,Edge> finite_edges(){return CGAL_Finite_edges_iterator<Triangulation,Edge>(this->data.finite_edges_begin(),this->data.finite_edges_end());}
  CGAL_Finite_facets_iterator<Triangulation,Facet> finite_facets(){return CGAL_Finite_facets_iterator<Triangulation,Facet>(this->data.finite_facets_begin(),this->data.finite_facets_end());}
  CGAL_Finite_cells_iterator<Triangulation,Cell_handle> finite_cells(){return CGAL_Finite_cells_iterator<Triangulation,Cell_handle>(this->data.finite_cells_begin(),this->data.finite_cells_end());}
  CGAL_All_vertices_iterator<Triangulation,Vertex_handle> all_vertices(){return CGAL_All_vertices_iterator<Triangulation,Vertex_handle>(this->data.all_vertices_begin(),this->data.all_vertices_end());}
  CGAL_All_edges_iterator<Triangulation,Edge> all_edges(){return CGAL_All_edges_iterator<Triangulation,Edge>(this->data.all_edges_begin(),this->data.all_edges_end());}
  CGAL_All_facets_iterator<Triangulation,Facet> all_facets(){return CGAL_All_facets_iterator<Triangulation,Facet>(this->data.all_facets_begin(),this->data.all_facets_end());}
  CGAL_All_cells_iterator<Triangulation,Cell_handle> all_cells(){return CGAL_All_cells_iterator<Triangulation,Cell_handle>(this->data.all_cells_begin(),this->data.all_cells_end());}
  CGAL_Point_iterator<Triangulation,Point_3> points(){return CGAL_Point_iterator<Triangulation,Point_3>(this->data.points_begin(),this->data.points_end());}

  FORWARD_CALL_1(Vertex_handle,insert,Point_3)
  FORWARD_CALL_2(Vertex_handle,insert,Point_3,Cell_handle)
  FORWARD_CALL_2(Vertex_handle,insert,Point_3,Vertex_handle)

  //----------------------------------
  //Triangulation_3 interface wrapping
  //----------------------------------
  //template < class InputIterator> Triangulation_3<TriangulationTraits_3,TriangulationDataStructure_3> t (InputIterator first,InputIterator last,);
  //Vertex_handle t.insert ( Point p, Locate_type lt, Cell_handle loc, int li, int lj)
  //template < class InputIterator >int 	t.insert ( InputIterator first, InputIterator last)
  //~ typedef std::vector<typename Triangulation::Point*> Point_range;

  int insert_range(Point_range range){
    return this->data.insert(range.first,range.second);
  }

  //bool t.is_edge ( Vertex_handle u, Vertex_handle v, Cell_handle & c, int & i, int & j)
  //bool  	t.is_facet ( 	Vertex_handle u,Vertex_handle v,Vertex_handle w,Cell_handle & c,int & i,int & j,int & k)
  //bool  	t.is_cell ( 	Vertex_handle u,Vertex_handle v,Vertex_handle w,Vertex_handle x,Cell_handle & c,int & i,int & j,int & k,int & l)

  bool is_cell (Vertex_handle u,Vertex_handle v,Vertex_handle w,Vertex_handle x,Cell_handle & c,Reference_wrapper<int>& i,Reference_wrapper<int> & j,Reference_wrapper<int> & k,Reference_wrapper<int> & l){
    return this->data.is_cell(convert(u),convert(v),convert(w),convert(x),convert(c),convert(i),convert(j),convert(k),convert(l));
  }

  //bool t.is_cell ( Vertex_handle u, Vertex_handle v, Vertex_handle w, Vertex_handle x, Cell_handle & c)
  //bool t.has_vertex ( Facet f, Vertex_handle v, int & j)
  //bool t.has_vertex ( Cell_handle c, int i, Vertex_handle v, int & j)
  //Cell_handle t.locate ( Point query, Locate_type & lt, int & li, int & lj, Cell_handle start = Cell_handle())
  //Cell_handle 	t.locate ( Point query, Locate_type & lt, int & li, int & lj, Vertex_handle hint)
  //Bounded_side 	t.side_of_cell ( Point p, Cell_handle c, Locate_type & lt, int & li, int & lj)
  //Bounded_side t.side_of_facet ( Point p, Facet f, Locate_type & lt, int & li, int & lj)
  //Bounded_side t.side_of_facet ( Point p, Cell_handle c, Locate_type & lt, int & li, int & lj)
  //Bounded_side t.side_of_edge ( Point p, Edge e, Locate_type & lt, int & li)
  //Bounded_side t.side_of_edge ( Point p, Cell_handle c, Locate_type & lt, int & li)

  typedef CGAL_Cell_circulator<Triangulation,Cell_handle> iCell_circulator;
  typedef CGAL_Facet_circulator<Triangulation,Facet>  iFacet_circulator;

  FORWARD_CALL_1(iCell_circulator,incident_cells,Edge)
  FORWARD_CALL_3(iCell_circulator,incident_cells,Cell_handle,int,int)
  FORWARD_CALL_2(iCell_circulator,incident_cells,Edge,Cell_handle)
  FORWARD_CALL_4(iCell_circulator,incident_cells,Cell_handle,int,int,Cell_handle)
  FORWARD_CALL_1(iFacet_circulator,incident_facets,Edge)
  FORWARD_CALL_3(iFacet_circulator,incident_facets,Cell_handle,int,int)
  FORWARD_CALL_2(iFacet_circulator,incident_facets,Edge,Facet)
  FORWARD_CALL_3(iFacet_circulator,incident_facets,Edge,Cell_handle,int)
  FORWARD_CALL_4(iFacet_circulator,incident_facets,Cell_handle,int,int,Facet)
  FORWARD_CALL_5(iFacet_circulator,incident_facets,Cell_handle,int,int,Cell_handle,int)

  FORWARD_CALL_2(bool,has_vertex,Facet,Vertex_handle)
  FORWARD_CALL_3(bool,has_vertex,Cell_handle,int,Vertex_handle)
  FORWARD_CALL_4(bool,are_equal,Cell_handle,int,Cell_handle,int)
  FORWARD_CALL_2(bool,are_equal,Facet,Facet)
  FORWARD_CALL_3(bool,are_equal,Facet,Cell_handle,int)

  FORWARD_CALL_1(int,degree,Vertex_handle)
  FORWARD_CALL_2(int,mirror_index,Cell_handle,int)
  FORWARD_CALL_2(Vertex_handle,mirror_vertex,Cell_handle,int)


  void incident_cells(const Vertex_handle& v,Output_iterator<Cell_handle>& out){ this->data.incident_cells(convert(v),std::back_inserter(out.get_data())); }
  #ifdef SWIGJAVA
  void test_outputit(Point_output_iterator out){*out++=typename Triangulation::Point(1,2,3);}
  void test_outputit2(jobject container){ *boost::make_function_output_iterator( Container_writer<Point_3,Point_3::cpp_base>(container,"LCGAL/Kernel/Point_3;") )++=typename Triangulation::Point(1,2,3); }
  #endif
  #ifdef SWIGPYTHON
  void test_outputit(Point_output_iterator out){*out++=typename Triangulation::Point(1,2,3);}
  #endif


  //template <class OutputIterator> OutputIterator 	t.finite_incident_cells ( Vertex_handle v, OutputIterator cells)
  //template <class OutputIterator> OutputIterator 	t.incident_facets ( Vertex_handle v, OutputIterator facets)
  //template <class OutputIterator> OutputIterator 	t.finite_incident_facets ( Vertex_handle v, OutputIterator facets)
  //template <class OutputIterator> OutputIterator 	t.incident_edges ( Vertex_handle v, OutputIterator edges)
  //template <class OutputIterator> OutputIterator 	t.finite_incident_edges ( Vertex_handle v, OutputIterator edges)
  //template <class OutputIterator> OutputIterator 	t.adjacent_vertices ( Vertex_handle v, OutputIterator vertices)
  //template <class OutputIterator> OutputIterator 	t.finite_adjacent_vertices ( Vertex_handle v, OutputIterator vertices)
  //istream& 	istream& is >> Triangulation_3 &t
  //ostream& 	ostream& os << Triangulation_3 t
  //bool t.is_vertex ( Point p, Vertex_handle & v)

  //Tetrahedron t.tetrahedron ( Cell_handle c)
  //Triangle t.triangle ( Cell_handle c, int i)
  //Triangle t.triangle ( Facet f)
  //Segment t.segment ( Edge e)
  //Segment t.segment ( Cell_handle c, int i, int j)
  //void t.swap ( Triangulation_3 & tr)
  //bool t.flip ( Edge e)
  //bool t.flip ( Cell_handle c, int i, int j)
  //void t.flip_flippable ( Edge e)
  //void t.flip_flippable ( Cell_handle c, int i, int j)
  //bool t.flip ( Facet f)
  //bool t.flip ( Cell_handle c, int i)
  //void t.flip_flippable ( Facet f)
  //void t.flip_flippable ( Cell_handle c, int i)
  //TriangulationTraits_3  t.geom_traits ()
  //Vertex_handle t.insert_in_cell ( Point p, Cell_handle c)
  //Vertex_handle t.insert_in_facet ( Point p, Facet f)
  //Vertex_handle t.insert_in_facet ( Point p, Cell_handle c, int i)
  //Vertex_handle 	t.insert_in_edge ( Point p, Edge e)
  //Vertex_handle t.insert_in_edge ( Point p, Cell_handle c, int i, int j)
  //Vertex_handle t.insert_outside_convex_hull ( Point p, Cell_handle c)
  //Vertex_handle t.insert_outside_affine_hull ( Point p)
  //template <class CellIt> Vertex_handle 	t.insert_in_hole ( Point p, CellIt cell_begin, CellIt cell_end, Cell_handle begin, int i)
  //template <class CellIt> Vertex_handle 	t.insert_in_hole ( 	Point p,CellIt cell_begin,CellIt cell_end,Cell_handle begin,int i,Vertex_handle newv)
  //TriangulationDataStructure_3 t.tds ()
};


#endif //SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H
