// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H
#define SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H

#include <boost/static_assert.hpp>

#include <SWIG_CGAL/Triangulation_3/triangulation_handles.h>
#include <SWIG_CGAL/Common/triple.h>
#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Weighted_point_3.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Triangle_3.h>
#include <SWIG_CGAL/Kernel/Tetrahedron_3.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Kernel/enum.h>

#include <sstream>
#include <fstream>

namespace SWIG_Triangulation_3 {
enum Locate_type { VERTEX=0, EDGE, FACET, CELL, OUTSIDE_CONVEX_HULL, OUTSIDE_AFFINE_HULL};
} //namespace SWIG_Triangulation_3

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Weighted_tag>
struct Weighting_helper_3{
  typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range;
};

template <>
struct Weighting_helper_3<CGAL::Tag_true>{
  typedef std::pair<Input_iterator_wrapper<Weighted_point_3,Weighted_point_3::cpp_base>,Input_iterator_wrapper<Weighted_point_3,Weighted_point_3::cpp_base> > Point_range;
};
#endif

//we use Memory_holder when the triangulation pointer is internally member of a class that should not
//be deleted while the triangulation exists. Usually it should be a shared_ptr.
template <class Triangulation,class Point,class Vertex_handle, class Cell_handle, class Weighted_tag,
class Memory_holder
#ifndef SWIG
=void*
#endif
>
class Triangulation_3_wrapper{
  #ifndef SWIG
  BOOST_STATIC_ASSERT( (boost::is_same<Weighted_tag,typename Triangulation::Weighted_tag>::value) );
  template<class T>
  void reset(T& shared_ptr) {shared_ptr.reset();}
  void reset(void*){}
  #endif  
protected:
  Triangulation* data_ptr;
  Memory_holder mem_holder;
  bool own_triangulation;
  const typename Triangulation::Cell_handle& convert (const Cell_handle& c) {return c.get_data();}
  typename Triangulation::Cell_handle& convert (Cell_handle& c) {return c.get_data();}
  const typename Triangulation::Vertex_handle& convert (const Vertex_handle& v) {return v.get_data();}
  typename Triangulation::Vertex_handle& convert (Vertex_handle& v) {return v.get_data();}
  template <class T> const T& convert(const Reference_wrapper<T>& ref){return ref.object();}
  template <class T> T& convert(Reference_wrapper<T>& ref){return ref.object();}
public:
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Weighting_helper_3<Weighted_tag>::Point_range Point_range;
  #else
  typedef Generic_input_iterator<Point> Point_range;
  #endif

  #ifndef SWIG
  typedef Triangulation cpp_base;
  const cpp_base& get_data() const {return *data_ptr;}
        cpp_base& get_data()       {return *data_ptr;}
  Triangulation_3_wrapper(const cpp_base& base):data_ptr(new cpp_base(base)),own_triangulation(true){}
  //constructor using a triangulation stored outside the wrapper class ( introduced for C3T3::triangulation() )
  Triangulation_3_wrapper(cpp_base* base,Memory_holder mh):data_ptr(base),mem_holder(mh),own_triangulation(false){}
  void share_ownership(Memory_holder mh){own_triangulation=false; mem_holder=mh;}
  //constructor used by inheriting classes  
  template <class PointIterator>
  Triangulation_3_wrapper(PointIterator first,PointIterator end):data_ptr(new cpp_base(first,end)){}
  #endif
  Triangulation_3_wrapper():data_ptr(new cpp_base()),own_triangulation(true){}
  ~Triangulation_3_wrapper(){if (own_triangulation) delete data_ptr;}
  Triangulation_3_wrapper(Point_range range):data_ptr(new cpp_base(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range))){}
  
  typedef Triangulation_3_wrapper<Triangulation,Point,Vertex_handle,Cell_handle,Weighted_tag,Memory_holder> Self;
  typedef std::pair<Cell_handle,int>             Facet;
  typedef SWIG_CGAL::Triple<Cell_handle,int,int> Edge;  
//Iterator typedefs  
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_vertices_iterator,Vertex_handle>            Finite_vertices_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_edges_iterator,Edge>                        Finite_edges_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_facets_iterator,Facet>                      Finite_facets_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_cells_iterator,Cell_handle>                 Finite_cells_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_vertices_iterator,Vertex_handle>               All_vertices_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_edges_iterator,Edge>                           All_edges_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_facets_iterator,Facet>                         All_facets_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_cells_iterator,Cell_handle>                    All_cells_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Point_iterator,Point>                              Point_iterator;
  typedef SWIG_CGAL_Circulator<typename Triangulation::Cell_circulator,Cell_handle>                     Cell_circulator;
  typedef SWIG_CGAL_Circulator<typename Triangulation::Facet_circulator,Facet>                          Facet_circulator;
//Output iterator typedefs  
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef boost::function_output_iterator< Container_writer<Cell_handle,typename Triangulation::Cell_handle> >          Cell_handle_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Vertex_handle,typename Triangulation::Vertex_handle> >      Vertex_handle_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Facet,typename Triangulation::Facet> >                      Facet_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Edge,typename Triangulation::Edge> >                        Edge_output_iterator;
  #else
  typedef Generic_output_iterator< Cell_handle >                                 Cell_handle_output_iterator;
  typedef Generic_output_iterator< Vertex_handle >                               Vertex_handle_output_iterator;
  typedef Generic_output_iterator< std::pair<Cell_handle,int> >                  Facet_output_iterator;
  typedef Generic_output_iterator< SWIG_CGAL::Triple<Cell_handle,int,int> >      Edge_output_iterator;  
  #endif
//Modifiers
  SWIG_CGAL_FORWARD_CALL_0(void,clear)  
//Access Functions
//Non const access
  SWIG_CGAL_FORWARD_CALL_0(int, dimension)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_cells)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vertex_handle,infinite_vertex)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Cell_handle,infinite_cell)  
//Non-constant-time access functions
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_facets)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_edges)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_finite_cells)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_finite_facets)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_finite_edges)  
//Geometric access functions
//Tests for Finite and Infinite Vertices and Faces
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_infinite,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Facet)
  SWIG_CGAL_FORWARD_CALL_3(bool,is_infinite,Cell_handle,int,int)  
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Edge)
//Queries
  SWIG_CGAL_FORWARD_CALL_1(bool,is_vertex,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_cell,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_2(bool,has_vertex,Facet,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_3(bool,has_vertex,Cell_handle,int,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_4(bool,are_equal,Cell_handle,int,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_2(bool,are_equal,Facet,Facet)
  SWIG_CGAL_FORWARD_CALL_3(bool,are_equal,Facet,Cell_handle,int)
//Point location
  SWIG_CGAL_FORWARD_CALL_1(Cell_handle,locate,Point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Cell_handle,locate,Point,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Cell_handle,locate,Point,Vertex_handle)
  Cell_handle locate (const Point& query, Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li, Reference_wrapper<int>& lj){
    return get_data().locate(query.get_data(),(typename cpp_base::Locate_type&) lt.object(),convert(li),convert(lj));
  }
  Cell_handle locate (const Point& query, Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li, Reference_wrapper<int>& lj,const Cell_handle& cell){
    return get_data().locate(query.get_data(),(typename cpp_base::Locate_type&) lt.object(),convert(li),convert(lj),cell.get_data());
  }
  Cell_handle locate (const Point& query, Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li, Reference_wrapper<int>& lj,const Vertex_handle& hint){
    return get_data().locate(query.get_data(),(typename cpp_base::Locate_type&) lt.object(),convert(li),convert(lj),hint.get_data());
  }
  Bounded_side side_of_cell (const Point& p,const Cell_handle& c,Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li, Reference_wrapper<int>& lj){
    return CGAL::enum_cast<Bounded_side>( get_data().side_of_cell(p.get_data(),c.get_data(),(typename cpp_base::Locate_type&) lt.object(),convert(li),convert(lj)) );
  }
  Bounded_side side_of_facet (const Point& p,const Facet& f, Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li, Reference_wrapper<int>& lj){
    return CGAL::enum_cast<Bounded_side>( get_data().side_of_facet(p.get_data(),internal::make_conversion(f),(typename cpp_base::Locate_type&) lt.object(),convert(li),convert(lj)) );
  }
  Bounded_side side_of_edge (const Point& p, const Edge& e, Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li){
    return CGAL::enum_cast<Bounded_side>( get_data().side_of_edge(p.get_data(),internal::make_conversion(e),(typename cpp_base::Locate_type&) lt.object(),convert(li)) );    
  }
  Bounded_side side_of_edge (const Point& p, const Cell_handle& c, Reference_wrapper<SWIG_Triangulation_3::Locate_type> & lt, Reference_wrapper<int>& li){
    return CGAL::enum_cast<Bounded_side>( get_data().side_of_edge(p.get_data(),c.get_data(),(typename cpp_base::Locate_type&) lt.object(),convert(li)) );    
  }
//Flips
  SWIG_CGAL_FORWARD_CALL_1(bool,flip,Edge)
  SWIG_CGAL_FORWARD_CALL_3(bool,flip,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_1(void,flip_flippable,Edge)
  SWIG_CGAL_FORWARD_CALL_3(void,flip_flippable,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,flip,Facet)
  SWIG_CGAL_FORWARD_CALL_2(bool,flip,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(void,flip_flippable,Facet)
  SWIG_CGAL_FORWARD_CALL_2(void,flip_flippable,Cell_handle,int)
//Insertions
  SWIG_CGAL_FORWARD_CALL_1(Vertex_handle,insert,Point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert,Point,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert,Point,Vertex_handle)
  int insert(Point_range range){ return get_data().insert(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range)); }
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert_in_cell,Point,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert_in_facet,Point,Facet)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Vertex_handle,insert_in_facet,Point,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert_in_edge,Point,Edge)
  SWIG_CGAL_FORWARD_CALL_AND_REF_4(Vertex_handle,insert_in_edge,Point,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert_outside_convex_hull,Point,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,insert_outside_affine_hull,Point)
//Traversal of the Triangulation
  Finite_vertices_iterator      finite_vertices(){return Finite_vertices_iterator(get_data().finite_vertices_begin(),get_data().finite_vertices_end());}
  Finite_edges_iterator         finite_edges(){return Finite_edges_iterator(get_data().finite_edges_begin(),get_data().finite_edges_end());}
  Finite_facets_iterator        finite_facets(){return Finite_facets_iterator(get_data().finite_facets_begin(),get_data().finite_facets_end());}
  Finite_cells_iterator         finite_cells(){return Finite_cells_iterator(get_data().finite_cells_begin(),get_data().finite_cells_end());}
  All_vertices_iterator         all_vertices(){return All_vertices_iterator(get_data().all_vertices_begin(),get_data().all_vertices_end());}
  All_edges_iterator            all_edges(){return All_edges_iterator(get_data().all_edges_begin(),get_data().all_edges_end());}
  All_facets_iterator           all_facets(){return All_facets_iterator(get_data().all_facets_begin(),get_data().all_facets_end());}
  All_cells_iterator            all_cells(){return All_cells_iterator(get_data().all_cells_begin(),get_data().all_cells_end());}
  Point_iterator                points(){return Point_iterator(get_data().points_begin(),get_data().points_end());}
//Cell and Facet Circulators
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Cell_circulator,incident_cells,Edge)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Cell_circulator,incident_cells,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Cell_circulator,incident_cells,Edge,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_4(Cell_circulator,incident_cells,Cell_handle,int,int,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Facet_circulator,incident_facets,Edge)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Facet_circulator,incident_facets,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Facet_circulator,incident_facets,Edge,Facet)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Facet_circulator,incident_facets,Edge,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_4(Facet_circulator,incident_facets,Cell_handle,int,int,Facet)
  SWIG_CGAL_FORWARD_CALL_5(Facet_circulator,incident_facets,Cell_handle,int,int,Cell_handle,int)  
//Traversal of the incident cells, facets and edges, and the adjacent vertices of a given vertex
  void incident_cells(const Vertex_handle& v, Cell_handle_output_iterator out){get_data().incident_cells(v.get_data(),out);}
  void finite_incident_cells(const Vertex_handle& v, Cell_handle_output_iterator out){get_data().finite_incident_cells(v.get_data(),out);}
  void incident_facets(const Vertex_handle& v, Facet_output_iterator out){    get_data().incident_facets(v.get_data(),out);  }
  void finite_incident_facets(const Vertex_handle& v, Facet_output_iterator out){get_data().finite_incident_facets(v.get_data(),out);}
  void incident_edges(const Vertex_handle& v, Edge_output_iterator out){get_data().incident_edges(v.get_data(),out);}
  void finite_incident_edges(const Vertex_handle& v, Edge_output_iterator out){get_data().finite_incident_edges(v.get_data(),out);}
  void adjacent_vertices(const Vertex_handle& v, Vertex_handle_output_iterator out){get_data().adjacent_vertices(v.get_data(),out);}
  void finite_adjacent_vertices(const Vertex_handle& v, Vertex_handle_output_iterator out){get_data().finite_adjacent_vertices(v.get_data(),out);}
  SWIG_CGAL_FORWARD_CALL_1(int,degree,Vertex_handle)  
//Traversal between adjacent cells
  SWIG_CGAL_FORWARD_CALL_2(int,mirror_index,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,mirror_vertex,Cell_handle,int)  
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Facet,mirror_facet,Facet)
//Geometric access functions
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Tetrahedron_3,tetrahedron,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Triangle_3,triangle,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Triangle_3,triangle,Facet)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Segment_3,segment,Edge)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Segment_3,segment,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Point,point,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point,point,Vertex_handle)
//Checking
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_valid,bool)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_valid,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_valid,Cell_handle,bool)
//I/O
  #ifndef SWIG_CGAL_NO_TRIANGULATION_STRING_OUTPUT
  std::string toString(){
    std::stringstream sstr;
    sstr << get_data();
    return sstr.str();
  }
  void write_to_file(const char* fname, int prec=5){
    std::ofstream out(fname);
    if (!out) std::cerr << "Error cannot create file: " << fname << std::endl;
    else out << std::setprecision(prec) << get_data();
  }
  void read_from_file(const char* fname){
    std::ifstream in(fname);
    if (!in) std::cerr << "Error cannot open file: " << fname << std::endl;
    else{
      if (!own_triangulation){
        data_ptr=new Triangulation();
        reset(mem_holder);
      }
      in >> get_data();
    }
  }
  #endif
//Queries
  bool is_cell (Vertex_handle u,Vertex_handle v,Vertex_handle w,Vertex_handle x,Cell_handle & c,Reference_wrapper<int>& i,Reference_wrapper<int> & j,Reference_wrapper<int> & k,Reference_wrapper<int> & l){
    return get_data().is_cell(convert(u),convert(v),convert(w),convert(x),convert(c),convert(i),convert(j),convert(k),convert(l));
  }
//Equality functions
  bool equal(const Triangulation_3_wrapper& t) {return t.get_data()==this->get_data();}
  DEFINE_EQUALITY_OPERATORS(Self);
//Deep copy
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){
    if (!own_triangulation){
      data_ptr=new Triangulation();
      reset(mem_holder);
    }
    *this=Self(other.get_data());
  }
  #ifndef SWIG
  Self& operator=(const Self& other)
  {
    if (own_triangulation)
      delete data_ptr;

    if (!other.own_triangulation)
    {
      own_triangulation=false;
      mem_holder=other.mem_holder;
      data_ptr=other.data_ptr;
    }
    else{
      own_triangulation=true;
      data_ptr=new Triangulation(other.get_data());
      reset(mem_holder);
    }
    return *this;
  }
  #endif
//Special for SWIG
  bool same_internal_object(const Self& other) {return other.data_ptr==data_ptr;}
};

//Assignment
//  Triangulation_3 & t = Triangulation_3 tr
//  void t.swap ( Triangulation_3 & tr)
//Access Functions
//  TriangulationTraits_3 t.geom_traits ()
//  TriangulationDataStructure_3 t.tds ()
//Non const access
//  TriangulationDataStructure_3 & t.tds()
//Queries
//  bool t.is_vertex ( Point p, Vertex_handle & v)  
//  bool t.is_edge ( Vertex_handle u, Vertex_handle v, Cell_handle & c, int & i, int & j)
//  bool t.is_facet ( Vertex_handle u,Vertex_handle v,Vertex_handle w,Cell_handle & c,int & i,int & j,int & k)
//  bool t.is_cell ( Vertex_handle u, Vertex_handle v, Vertex_handle w, Vertex_handle x, Cell_handle & c)
//  bool t.has_vertex ( Facet f, Vertex_handle v, int & j)
//  bool t.has_vertex ( Cell_handle c, int i, Vertex_handle v, int & j)
//Insertions
//  Vertex_handle t.insert ( Point p, Locate_type lt, Cell_handle loc, int li, int lj)  
//  template <class CellIt> Vertex_handle t.insert_in_hole ( Point p, CellIt cell_begin, CellIt cell_end, Cell_handle begin, int i)
//  template <class CellIt> Vertex_handle t.insert_in_hole ( Point p,CellIt cell_begin,CellIt cell_end,Cell_handle begin,int i,Vertex_handle newv)
//I/O
//  istream& istream& is >> Triangulation_3 &t
//  ostream& ostream& os << Triangulation_3 t Writes the triangulation t into os.


#endif //SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_3_H
