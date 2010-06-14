#ifndef SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_2_H

//WARNING Point_2 vs Traits::Point (handle weighted points)

#include <CGAL/config.h>
#include <CGAL/Triangulation_2.h>

#include "../Kernel/typedefs.h"
#include "triangulation_iterators.h"
#include "../Kernel/Point_2.h"
#include "../Kernel/Segment_2.h"
#include "../Kernel/Triangle_2.h"
#include "../Common/Macros.h"

#ifdef SWIGPYTHON
#include "../Python/Input_iterator_wrapper.h"
#endif
#ifdef SWIGJAVA
#include "../Java/Input_iterator_wrapper.h"
#endif

enum Locate_type { VERTEX=0, EDGE, FACE, OUTSIDE_CONVEX_HULL, OUTSIDE_AFFINE_HULL};
enum Oriented_side { ON_NEGATIVE_SIDE, ON_ORIENTED_BOUNDARY, ON_POSITIVE_SIDE};

typedef std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> > Point_range;

template <class Triangulation,class Vertex_handle, class Face_handle>
class Triangulation_2_wrapper
{
protected :
  Triangulation data;
public:
  typedef Triangulation cpp_base;

  typedef std::pair<Face_handle,int>                                   Edge;
  typedef CGAL_Finite_vertices_iterator<Triangulation,Vertex_handle>   Finite_vertices_iterator;
  typedef CGAL_Finite_edges_iterator<Triangulation,Edge>               Finite_edges_iterator;
  typedef CGAL_Finite_faces_iterator<Triangulation,Face_handle>        Finite_faces_iterator;
  typedef CGAL_All_vertices_iterator<Triangulation,Vertex_handle>      All_vertices_iterator;
  typedef CGAL_All_edges_iterator<Triangulation,Edge>                  All_edges_iterator;
  typedef CGAL_All_faces_iterator<Triangulation,Face_handle>           All_faces_iterator;
  typedef CGAL_Point_iterator<Triangulation,Point_2>                   Point_iterator;
  typedef CGAL_Line_face_circulator<Triangulation,Face_handle>         Line_face_circulator;
  typedef CGAL_Face_circulator<Triangulation,Face_handle>              Face_circulator;
  typedef CGAL_Edge_circulator<Triangulation,Edge>                     Edge_circulator;
  typedef CGAL_Vertex_circulator<Triangulation,Vertex_handle>          Vertex_circulator;


  Triangulation_2_wrapper(){}
  const Triangulation& get_data() const {return this->data;}

// Creation 
  FORWARD_CALL_0(void, clear)
  FORWARD_CALL_0(int, dimension)
  FORWARD_CALL_0(int, number_of_vertices)
  FORWARD_CALL_0(int, number_of_faces)
// Access Functions  
  FORWARD_CALL_0(Face_handle,infinite_face)
  FORWARD_CALL_0(Vertex_handle,infinite_vertex)
  FORWARD_CALL_0(Vertex_handle,finite_vertex)
// Predicates
  FORWARD_CALL_1(bool,is_infinite,Vertex_handle)
  FORWARD_CALL_1(bool,is_infinite,Face_handle)
  FORWARD_CALL_2(bool,is_infinite,Face_handle,int)
  FORWARD_CALL_2(bool,is_edge,Vertex_handle,Vertex_handle)
  FORWARD_CALL_3(bool,is_face,Vertex_handle,Vertex_handle,Vertex_handle)
  FORWARD_CALL_1(bool,is_infinite,Edge)
// Queries
  FORWARD_CALL_1(Face_handle,locate,Point_2)
  FORWARD_CALL_2(Face_handle,locate,Point_2,Face_handle)
  //FORWARD_CALL_2(Oriented_side,oriented_side,Face_handle,Point)
  //FORWARD_CALL_2(Oriented_side,side_of_oriented_circle,Face_handle,Point)  
// Modifiers
//  FORWARD_CALL_2(void,flip,Face_handle,int) TODO: ambiguous call in CDT (their exist an overload with Face_handle&) 
  FORWARD_CALL_1(Vertex_handle,insert,Point_2)
  FORWARD_CALL_2(Vertex_handle,insert,Point_2,Face_handle)
  FORWARD_CALL_1(Vertex_handle,push_back,Point_2)
  FORWARD_CALL_1(void,remove,Vertex_handle)
  FORWARD_CALL_1(Vertex_handle,insert_first,Point_2)
  FORWARD_CALL_1(Vertex_handle,insert_second,Point_2)
  FORWARD_CALL_2(Vertex_handle,insert_in_face,Point_2,Face_handle)
  FORWARD_CALL_3(Vertex_handle,insert_in_edge,Point_2,Face_handle,int)
  FORWARD_CALL_2(Vertex_handle,insert_outside_convex_hull,Point_2,Face_handle)
  FORWARD_CALL_1(Vertex_handle,insert_outside_affine_hull,Point_2)
  FORWARD_CALL_1(void,remove_degree_3,Vertex_handle)
  FORWARD_CALL_1(void,remove_second,Vertex_handle)
  FORWARD_CALL_1(void,remove_first,Vertex_handle)
  //FORWARD_CALL_4(Vertex_handle,insert,Point,Locate_type,Face_handle,int)
  int insert_range(Point_range range){
    return this->data.insert(range.first,range.second);
  }  
// Traversal of the Triangulation
  Finite_vertices_iterator finite_vertices(){return Finite_vertices_iterator(this->data.finite_vertices_begin(),this->data.finite_vertices_end());}
  Finite_edges_iterator finite_edges(){return Finite_edges_iterator(this->data.finite_edges_begin(),this->data.finite_edges_end());}
  Finite_faces_iterator finite_faces(){return Finite_faces_iterator(this->data.finite_faces_begin(),this->data.finite_faces_end());}
  All_vertices_iterator all_vertices(){return All_vertices_iterator(this->data.all_vertices_begin(),this->data.all_vertices_end());}
  All_edges_iterator all_edges(){return All_edges_iterator(this->data.all_edges_begin(),this->data.all_edges_end());}
  All_faces_iterator all_faces(){return All_faces_iterator(this->data.all_faces_begin(),this->data.all_faces_end());}
  Point_iterator points(){return Point_iterator(this->data.points_begin(),this->data.points_end());}
// Line Face Circulator
  Line_face_circulator line_walk(const Point_2& p,const Point_2& q){return Line_face_circulator(this->data.line_walk(p.get_data(),q.get_data()));}
  Line_face_circulator line_walk(const Point_2& p,const Point_2& q,const Face_handle& f){return Line_face_circulator(this->data.line_walk(p.get_data(),q.get_data(),f.get_data()));}
// Face, Edge and Vertex Circulators
  Face_circulator incident_faces(const Vertex_handle& v){return Face_circulator(this->data.incident_faces(v.get_data()));}
  Face_circulator incident_faces(const Vertex_handle& v,const Face_handle& f){return Face_circulator(this->data.incident_faces(v.get_data(),f.get_data()));}
  Edge_circulator incident_edges(const Vertex_handle& v){return Edge_circulator(this->data.incident_edges(v.get_data()));}
  Edge_circulator incident_edges(const Vertex_handle& v,const Face_handle& f){return Edge_circulator(this->data.incident_edges(v.get_data(),f.get_data()));}  
  Vertex_circulator incident_vertices(const Vertex_handle& v){return Vertex_circulator(this->data.incident_vertices(v.get_data()));}
  Vertex_circulator incident_vertices(const Vertex_handle& v,const Face_handle& f){return Vertex_circulator(this->data.incident_vertices(v.get_data(),f.get_data()));}    
// Traversal between adjacent faces
  FORWARD_CALL_2(Vertex_handle,mirror_vertex,Face_handle,int)
  FORWARD_CALL_2(int,mirror_index,Face_handle,int)
  FORWARD_CALL_1(int,ccw,int)
  FORWARD_CALL_1(int,cw,int)
  FORWARD_CALL_1(Point_2,circumcenter,Face_handle)
// Setting
  FORWARD_CALL_1(void,set_infinite_vertex,Vertex_handle)
// Checking
  FORWARD_CALL_0(bool,is_valid)
  FORWARD_CALL_1(bool,is_valid,bool)
  FORWARD_CALL_2(bool,is_valid,bool,int)
// Miscellaneous
  FORWARD_CALL_1(Triangle_2,triangle,Face_handle)
  FORWARD_CALL_2(Segment_2,segment,Face_handle,int)
  FORWARD_CALL_1(Segment_2,segment,Edge)
};

#endif //SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_2_H


// Creation
//   Triangulation_2<Traits,Tds> t(Triangulation_2 tr)
//   t.swap ( Triangulation_2& tr)
// Access Functions
//   Geom_traits  t.geom_traits ()
//   TriangulationDataStructure_2  t.tds ()
//   TriangulationDataStructure_2 &  t.tds ()
// Predicates
//   bool  t.is_edge ( Vertex_handle va, Vertex_handle vb, Face_handle& fr, int & i)
//   bool  t.includes_edge ( Vertex_handle va, Vertex_handle & vb, Face_handle& fr, int & i)
//   bool  t.is_face ( Vertex_handle v1, Vertex_handle v2, Vertex_handle v3, Face_handle &fr)
// Queries
//   Face_handle  t.locate ( Point query, Locate_type& lt, int& li, Face_handle h =Face_handle())
//I/O
// ostream&  ostream& os << T  Inserts the triangulation t into the stream os.
// istream&  istream& is >> T  Reads a triangulation from stream is and assigns it to t.
