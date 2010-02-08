#ifndef CGAL_SWIG_DELAUNAY_TRIANGULATION_3_H
#define CGAL_SWIG_DELAUNAY_TRIANGULATION_3_H

#include "EPIC_Kernel.h"
#include "triangulation_handles.h"
#include "triangulation_iterators.h"
#include "triple.h"
#include <CGAL/Delaunay_triangulation_3.h>

typedef CGAL::Delaunay_triangulation_3<CGAL::Exact_predicates_inexact_constructions_kernel> EPIC_DT3;
enum Locate_type { VERTEX=0, EDGE, FACET, CELL, OUTSIDE_CONVEX_HULL, OUTSIDE_AFFINE_HULL};
enum Bounded_side{ ON_UNBOUNDED_SIDE = -1,ON_BOUNDARY,ON_BOUNDED_SIDE};

typedef std::pair<CGAL_Cell_handle<EPIC_DT3>,int> DT3_Facet;
typedef CGAL_SWIG::Triple<CGAL_Cell_handle<EPIC_DT3>,int,int> DT3_Edge;

template <class Triangulation>
class Delaunay_triangulation_3{
  Triangulation data;
  
  typename Triangulation::Cell_handle convert (const CGAL_Cell_handle<Triangulation>& c) {return c.get_data();}
  typename Triangulation::Vertex_handle convert (const CGAL_Vertex_handle<Triangulation>& v) {return v.get_data();}
  typename Triangulation::Facet convert(const DT3_Facet& f){return std::make_pair(convert(f.first),f.second);}
  typename Triangulation::Edge convert(const DT3_Edge& e){return CGAL::make_tuple(convert(e.first),e.second,e.third);}
  typename Triangulation::Point convert (const EPIC_Point_3& p){return p.get_data();}
  const int& convert (const int& i){return i;}
  
public:
  const Triangulation& get_data() const {return data;}
#define MAP_FUNC(RET,NAME) RET NAME() {return RET(data.NAME());}
#define MAP_FUNC_WRAP_IN_ONE(RET,NAME,IN_TYPE) RET NAME(const IN_TYPE& c){return RET(data.NAME(convert(c)));}
#define MAP_FUNC_WRAP_IN_TWO(RET,NAME,IN_TYPE_1,IN_TYPE_2) RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2){return RET(data.NAME(convert(c1),convert(c2)));}
#define MAP_FUNC_WRAP_IN_THREE(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3){return RET(data.NAME(convert(c1),convert(c2),convert(c3)));}
#define MAP_FUNC_WRAP_IN_FOUR(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4){return RET(data.NAME(convert(c1),convert(c2),convert(c3),convert(c4)));}
#define MAP_FUNC_WRAP_IN_FIVE(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5) RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5){return RET(data.NAME(convert(c1),convert(c2),convert(c3),convert(c4),convert(c5)));}

Delaunay_triangulation_3():data(){}
  
MAP_FUNC(int, dimension)
MAP_FUNC(int, number_of_vertices)
MAP_FUNC(int, number_of_cells)
MAP_FUNC(int, number_of_facets)
MAP_FUNC(int, number_of_edges)
MAP_FUNC(int, number_of_finite_cells)
MAP_FUNC(int, number_of_finite_facets)
MAP_FUNC(int, number_of_finite_edges)
MAP_FUNC(CGAL_Vertex_handle<Triangulation>,infinite_vertex)
MAP_FUNC(CGAL_Cell_handle<Triangulation>,infinite_cell)
MAP_FUNC_WRAP_IN_ONE(bool,is_infinite,CGAL_Vertex_handle<Triangulation>)
MAP_FUNC_WRAP_IN_ONE(bool,is_infinite,CGAL_Cell_handle<Triangulation>)
MAP_FUNC_WRAP_IN_ONE(bool,is_infinite,DT3_Facet)
MAP_FUNC_WRAP_IN_ONE(bool,is_infinite,DT3_Edge)
MAP_FUNC_WRAP_IN_TWO(bool,is_infinite,CGAL_Cell_handle<Triangulation>,int)
MAP_FUNC_WRAP_IN_THREE(bool,is_infinite,CGAL_Cell_handle<Triangulation>,int,int)
MAP_FUNC_WRAP_IN_ONE(bool,is_vertex,CGAL_Vertex_handle<Triangulation>)
MAP_FUNC_WRAP_IN_ONE(bool,is_cell,CGAL_Cell_handle<Triangulation>)
MAP_FUNC_WRAP_IN_ONE(CGAL_Cell_handle<Triangulation>,locate,EPIC_Point_3)
MAP_FUNC_WRAP_IN_TWO(CGAL_Cell_handle<Triangulation>,locate,EPIC_Point_3,CGAL_Cell_handle<Triangulation>)
MAP_FUNC_WRAP_IN_TWO(CGAL_Cell_handle<Triangulation>,locate,EPIC_Point_3,CGAL_Vertex_handle<Triangulation>)
MAP_FUNC(bool,is_valid)
MAP_FUNC_WRAP_IN_ONE(bool,is_valid,bool)
MAP_FUNC_WRAP_IN_ONE(bool,is_valid,CGAL_Cell_handle<Triangulation>)
MAP_FUNC_WRAP_IN_TWO(bool,is_valid,CGAL_Cell_handle<Triangulation>,bool)
MAP_FUNC_WRAP_IN_ONE(DT3_Facet,mirror_facet,DT3_Facet)
MAP_FUNC_WRAP_IN_TWO(EPIC_Point_3,point,CGAL_Cell_handle<Triangulation>,int)
MAP_FUNC_WRAP_IN_ONE(EPIC_Point_3,point,CGAL_Vertex_handle<Triangulation>)
void clear(){data.clear();}
Delaunay_triangulation_3(const Delaunay_triangulation_3& dt):data(dt.get_data()){};
bool equal(const Delaunay_triangulation_3& dt) {return dt.get_data()==data;}
bool equals(const Delaunay_triangulation_3& dt) {return equal(dt);}
#ifdef SWIGPYTHON
bool __eq__(const Delaunay_triangulation_3& dt) {return equal(dt);}
bool __ne__(const Delaunay_triangulation_3& dt) {return !__eq__(dt);}
#endif

Finite_vertices_iterator<Triangulation> finite_vertices(){return Finite_vertices_iterator<Triangulation>(data.finite_vertices_begin(),data.finite_vertices_end());}
Finite_edges_iterator<Triangulation> finite_edges(){return Finite_edges_iterator<Triangulation>(data.finite_edges_begin(),data.finite_edges_end());}
Finite_facets_iterator<Triangulation> finite_facets(){return Finite_facets_iterator<Triangulation>(data.finite_facets_begin(),data.finite_facets_end());}
Finite_cells_iterator<Triangulation> finite_cells(){return Finite_cells_iterator<Triangulation>(data.finite_cells_begin(),data.finite_cells_end());}
All_vertices_iterator<Triangulation> all_vertices(){return All_vertices_iterator<Triangulation>(data.all_vertices_begin(),data.all_vertices_end());}
All_edges_iterator<Triangulation> all_edges(){return All_edges_iterator<Triangulation>(data.all_edges_begin(),data.all_edges_end());}
All_facets_iterator<Triangulation> all_facets(){return All_facets_iterator<Triangulation>(data.all_facets_begin(),data.all_facets_end());}
All_cells_iterator<Triangulation> all_cells(){return All_cells_iterator<Triangulation>(data.all_cells_begin(),data.all_cells_end());}
Point_iterator<Triangulation> points(){return Point_iterator<Triangulation>(data.points_begin(),data.points_end());}

CGAL_Vertex_handle<Triangulation> insert(const EPIC_Point_3& p){return  CGAL_Vertex_handle<Triangulation>(data.insert(p.get_data()));}
MAP_FUNC_WRAP_IN_TWO(CGAL_Vertex_handle<Triangulation>,insert,EPIC_Point_3,CGAL_Cell_handle<Triangulation>) 
MAP_FUNC_WRAP_IN_TWO(CGAL_Vertex_handle<Triangulation>,insert,EPIC_Point_3,CGAL_Vertex_handle<Triangulation>) 

//----------------------------------
//Triangulation_3 interface wrapping
//----------------------------------
//template < class InputIterator> Triangulation_3<TriangulationTraits_3,TriangulationDataStructure_3> t (InputIterator first,InputIterator last,);
 

//Vertex_handle t.insert ( Point p, Locate_type lt, Cell_handle loc, int li, int lj) 
//template < class InputIterator >int 	t.insert ( InputIterator first, InputIterator last) 

//bool t.is_edge ( Vertex_handle u, Vertex_handle v, Cell_handle & c, int & i, int & j) 
//bool  	t.is_facet ( 	Vertex_handle u,Vertex_handle v,Vertex_handle w,Cell_handle & c,int & i,int & j,int & k)
//bool  	t.is_cell ( 	Vertex_handle u,Vertex_handle v,Vertex_handle w,Vertex_handle x,Cell_handle & c,int & i,int & j,int & k,int & l)
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



MAP_FUNC_WRAP_IN_ONE(Cell_circulator<Triangulation>,incident_cells,DT3_Edge)
MAP_FUNC_WRAP_IN_THREE(Cell_circulator<Triangulation>,incident_cells,CGAL_Cell_handle<Triangulation>,int,int)
MAP_FUNC_WRAP_IN_TWO(Cell_circulator<Triangulation>,incident_cells,DT3_Edge,CGAL_Cell_handle<Triangulation>)
MAP_FUNC_WRAP_IN_FOUR(Cell_circulator<Triangulation>,incident_cells,CGAL_Cell_handle<Triangulation>,int,int,CGAL_Cell_handle<Triangulation>)
MAP_FUNC_WRAP_IN_ONE(Facet_circulator<Triangulation>,incident_facets,DT3_Edge)
MAP_FUNC_WRAP_IN_THREE(Facet_circulator<Triangulation>,incident_facets,CGAL_Cell_handle<Triangulation>,int,int)
MAP_FUNC_WRAP_IN_TWO(Facet_circulator<Triangulation>,incident_facets,DT3_Edge,DT3_Facet)
MAP_FUNC_WRAP_IN_THREE(Facet_circulator<Triangulation>,incident_facets,DT3_Edge,CGAL_Cell_handle<Triangulation>,int)
MAP_FUNC_WRAP_IN_FOUR(Facet_circulator<Triangulation>,incident_facets,CGAL_Cell_handle<Triangulation>,int,int,DT3_Facet)
MAP_FUNC_WRAP_IN_FIVE(Facet_circulator<Triangulation>,incident_facets,CGAL_Cell_handle<Triangulation>,int,int,CGAL_Cell_handle<Triangulation>,int)

MAP_FUNC_WRAP_IN_TWO(bool,has_vertex,DT3_Facet,CGAL_Vertex_handle<Triangulation>)
MAP_FUNC_WRAP_IN_THREE(bool,has_vertex,CGAL_Cell_handle<Triangulation>,int,CGAL_Vertex_handle<Triangulation>)
MAP_FUNC_WRAP_IN_FOUR(bool,are_equal,CGAL_Cell_handle<Triangulation>,int,CGAL_Cell_handle<Triangulation>,int)
MAP_FUNC_WRAP_IN_TWO(bool,are_equal,DT3_Facet,DT3_Facet)
MAP_FUNC_WRAP_IN_THREE(bool,are_equal,DT3_Facet,CGAL_Cell_handle<Triangulation>,int)

MAP_FUNC_WRAP_IN_ONE(int,degree,CGAL_Vertex_handle<Triangulation>)
MAP_FUNC_WRAP_IN_TWO(int,mirror_index,CGAL_Cell_handle<Triangulation>,int)
MAP_FUNC_WRAP_IN_TWO(CGAL_Vertex_handle<Triangulation>,mirror_vertex,CGAL_Cell_handle<Triangulation>,int)


//template <class OutputIterator> OutputIterator 	t.incident_cells ( Vertex_handle v, OutputIterator cells)
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

//---------------------------------
//Delaunay_triangulation_3 wrapping
//---------------------------------
void remove(CGAL_Vertex_handle<Triangulation> v){data.remove(convert(v));}
MAP_FUNC_WRAP_IN_TWO(CGAL_Vertex_handle<Triangulation>,move_point,CGAL_Vertex_handle<Triangulation>,EPIC_Point_3);
MAP_FUNC_WRAP_IN_TWO(Bounded_side,side_of_sphere,CGAL_Cell_handle<Triangulation>,EPIC_Point_3)
MAP_FUNC_WRAP_IN_TWO(Bounded_side,side_of_circle,DT3_Facet,EPIC_Point_3)
MAP_FUNC_WRAP_IN_THREE(Bounded_side,side_of_circle,CGAL_Cell_handle<Triangulation>,int,EPIC_Point_3)

MAP_FUNC_WRAP_IN_ONE(CGAL_Vertex_handle<Triangulation>,nearest_vertex,EPIC_Point_3)
MAP_FUNC_WRAP_IN_TWO(CGAL_Vertex_handle<Triangulation>,nearest_vertex,EPIC_Point_3,CGAL_Cell_handle<Triangulation>)

MAP_FUNC_WRAP_IN_TWO(bool,is_Gabriel,CGAL_Cell_handle<Triangulation>,int)
MAP_FUNC_WRAP_IN_THREE(bool,is_Gabriel,CGAL_Cell_handle<Triangulation>,int,int)
MAP_FUNC_WRAP_IN_ONE(bool,is_Gabriel,DT3_Facet)
MAP_FUNC_WRAP_IN_ONE(bool,is_Gabriel,DT3_Edge)

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


#endif //CGAL_SWIG_DELAUNAY_TRIANGULATION_3_H
