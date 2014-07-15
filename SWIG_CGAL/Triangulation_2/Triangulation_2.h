// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_2_H

#include <CGAL/config.h>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Kernel/Weighted_point_2.h>
#include <SWIG_CGAL/Kernel/Segment_2.h>
#include <SWIG_CGAL/Kernel/Triangle_2.h>
#include <SWIG_CGAL/Kernel/enum.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <sstream>
#include <fstream>
#include <boost/shared_ptr.hpp>

#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Iterator.h>

#include <boost/static_assert.hpp>

#include <CGAL/Triangulation_2.h>

namespace SWIG_Triangulation_2{
enum Locate_type { VERTEX=0, EDGE, FACE, OUTSIDE_CONVEX_HULL, OUTSIDE_AFFINE_HULL};
} //namespace SWIG_Triangulation_2

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Weighted_tag>
struct Weighting_helper{
  typedef std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> > Point_range;
};

template <>
struct Weighting_helper<CGAL::Tag_true>{
  typedef std::pair<Input_iterator_wrapper<Weighted_point_2,Weighted_point_2::cpp_base>,Input_iterator_wrapper<Weighted_point_2,Weighted_point_2::cpp_base> > Point_range;
};
#endif

template <class Triangulation,class Point, class Vertex_handle, class Face_handle,class Weighted_tag>
class Triangulation_2_wrapper
{
  #ifndef SWIG
  BOOST_STATIC_ASSERT( (boost::is_same<Weighted_tag,typename Triangulation::Weighted_tag>::value) );
  #endif

  
protected :
  boost::shared_ptr<Triangulation> data_sptr;
public:

  typedef std::pair<Face_handle,int>                                   Edge;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_vertices_iterator,Vertex_handle>   Finite_vertices_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_edges_iterator,Edge>               Finite_edges_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Finite_faces_iterator,Face_handle>        Finite_faces_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_vertices_iterator,Vertex_handle>      All_vertices_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_edges_iterator,Edge>                  All_edges_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::All_faces_iterator,Face_handle>           All_faces_iterator;
  typedef SWIG_CGAL_Iterator<typename Triangulation::Point_iterator,Point>                     Point_iterator;
  typedef SWIG_CGAL_Circulator<typename Triangulation::Line_face_circulator,Face_handle>         Line_face_circulator;
  typedef SWIG_CGAL_Circulator<typename Triangulation::Face_circulator,Face_handle>              Face_circulator;
  typedef SWIG_CGAL_Circulator<typename Triangulation::Edge_circulator,Edge>                     Edge_circulator;
  typedef SWIG_CGAL_Circulator<typename Triangulation::Vertex_circulator,Vertex_handle>          Vertex_circulator;

  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Weighting_helper<Weighted_tag>::Point_range                                  Point_range;
  #else
  typedef Generic_input_iterator<Point>                                                         Point_range;
  #endif

  Triangulation_2_wrapper():data_sptr(new cpp_base()){}
  #ifndef SWIG
  typedef Triangulation cpp_base;
  const cpp_base& get_data() const {return *data_sptr;}
        cpp_base& get_data()       {return *data_sptr;}
  Triangulation_2_wrapper(const cpp_base& base):data_sptr(new cpp_base(base)){}
  boost::shared_ptr<cpp_base> shared_ptr() {return data_sptr;}
  #endif

// Creation 
  SWIG_CGAL_FORWARD_CALL_0(void, clear)
  SWIG_CGAL_FORWARD_CALL_0(int, dimension)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_faces)
// Access Functions  
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Face_handle,infinite_face)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vertex_handle,infinite_vertex)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vertex_handle,finite_vertex)
// Predicates
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Face_handle)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_infinite,Face_handle,int)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_edge,Vertex_handle,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_3(bool,is_face,Vertex_handle,Vertex_handle,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_infinite,Edge)

// Predicates
  bool is_edge(Vertex_handle va, Vertex_handle vb, Reference_wrapper<Face_handle>& fr, Reference_wrapper<int>& i)
  {
    typename Face_handle::cpp_base base_f;
    int base_i;
    bool res = get_data().is_edge(va.get_data(), vb.get_data(), base_f, base_i);
    fr.set(base_f);
    i.set(base_i);
    return res;
  }

  bool includes_edge(Vertex_handle va, Vertex_handle vb, Reference_wrapper<Vertex_handle>& vbr, Reference_wrapper<Face_handle>& fr, Reference_wrapper<int>& i)
  {
    typename Face_handle::cpp_base base_f;
    typename Vertex_handle::cpp_base base_v;
    int base_i;
    bool res = get_data().includes_edge(va.get_data(), vb.get_data(), base_v, base_f, base_i);
    fr.set(base_f);
    vbr.set(base_v);
    i.set(base_i);
    return res;
  }

  bool is_face (Vertex_handle v1, Vertex_handle v2, Vertex_handle v3, Reference_wrapper<Face_handle>& fr)
  {
    typename Face_handle::cpp_base base_f;
    bool res = get_data().is_face(v1.get_data(), v2.get_data(), v3.get_data(), base_f);
    fr.set(base_f);
    return res;
  }

// Queries
  SWIG_CGAL_FORWARD_CALL_1(Face_handle,locate,Point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Face_handle,locate,Point,Face_handle)
  SWIG_CGAL_FORWARD_CALL_2(Oriented_side,oriented_side,Face_handle,Point)
  SWIG_CGAL_FORWARD_CALL_2(Oriented_side,side_of_oriented_circle,Face_handle,Point)  
  Face_handle locate(const Point& query, Reference_wrapper<SWIG_Triangulation_2::Locate_type>& lt, Reference_wrapper<int>& li,Face_handle hint=Face_handle()) const {
    typename cpp_base::Locate_type cgal_lt;
    typename Face_handle::cpp_base res = get_data().locate(query.get_data(),cgal_lt,li.object(),hint.get_data());
    lt.set(CGAL::enum_cast<SWIG_Triangulation_2::Locate_type>(cgal_lt));
    return Face_handle(res);
  }
// Modifiers
//  SWIG_CGAL_FORWARD_CALL_2(void,flip,Face_handle,int) TODO: ambiguous call in CDT (their exist an overload with Face_handle&) 
#ifndef CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,insert,Point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert,Point,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,push_back,Point)
  SWIG_CGAL_FORWARD_CALL_1(void,remove,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,insert_first,Point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,insert_second,Point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert_in_face,Point,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Vertex_handle,insert_in_edge,Point,Face_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,insert_outside_convex_hull,Point,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,insert_outside_affine_hull,Point)
  SWIG_CGAL_FORWARD_CALL_1(void,remove_degree_3,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(void,remove_second,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(void,remove_first,Vertex_handle)
  Vertex_handle insert(const Point& p,SWIG_Triangulation_2::Locate_type l,const Face_handle& f,int i) {return get_data().insert(p.get_data(),CGAL::enum_cast<typename Triangulation::Locate_type>(l),f.get_data(),i);}
  int insert(Point_range range){
    return get_data().insert(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));
  }
#endif  
// Traversal of the Triangulation
  Finite_vertices_iterator finite_vertices(){return Finite_vertices_iterator(get_data().finite_vertices_begin(),get_data().finite_vertices_end());}
  Finite_edges_iterator finite_edges(){return Finite_edges_iterator(get_data().finite_edges_begin(),get_data().finite_edges_end());}
  Finite_faces_iterator finite_faces(){return Finite_faces_iterator(get_data().finite_faces_begin(),get_data().finite_faces_end());}
  All_vertices_iterator all_vertices(){return All_vertices_iterator(get_data().all_vertices_begin(),get_data().all_vertices_end());}
  All_edges_iterator all_edges(){return All_edges_iterator(get_data().all_edges_begin(),get_data().all_edges_end());}
  All_faces_iterator all_faces(){return All_faces_iterator(get_data().all_faces_begin(),get_data().all_faces_end());}
  Point_iterator points(){return Point_iterator(get_data().points_begin(),get_data().points_end());}
// Line Face Circulator
  Line_face_circulator line_walk(const Point& p,const Point& q){return Line_face_circulator(get_data().line_walk(p.get_data(),q.get_data()));}
  Line_face_circulator line_walk(const Point& p,const Point& q,const Face_handle& f){return Line_face_circulator(get_data().line_walk(p.get_data(),q.get_data(),f.get_data()));}
// Face, Edge and Vertex Circulators
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Face_circulator,incident_faces,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Face_circulator,incident_faces,Vertex_handle,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Edge_circulator,incident_edges,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Edge_circulator,incident_edges,Vertex_handle,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_circulator,incident_vertices,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_circulator,incident_vertices,Vertex_handle,Face_handle)
// Traversal between adjacent faces
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,mirror_vertex,Face_handle,int)
  SWIG_CGAL_FORWARD_CALL_2(int,mirror_index,Face_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(int,ccw,int)
  SWIG_CGAL_FORWARD_CALL_1(int,cw,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point,circumcenter,Face_handle)
// Setting
  SWIG_CGAL_FORWARD_CALL_1(void,set_infinite_vertex,Vertex_handle)
// Checking
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_valid,bool)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_valid,bool,int)
// Miscellaneous
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Triangle_2,triangle,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Segment_2,segment,Face_handle,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Segment_2,segment,Edge)
#ifndef CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << *data_sptr;
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
      in >> get_data();
    }
  }
//Deep copy
  #ifndef CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2
  typedef Triangulation_2_wrapper<Triangulation,Point,Vertex_handle,Face_handle,Weighted_tag> Self;
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){*this=Self(other.get_data());} // (the inheritance is not a problem here)
  #endif
//Special for SWIG
  bool same_internal_object(const Self& other) {return other.data_sptr.get()==data_sptr.get();}
#endif
};

#endif //SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_2_H


// Creation
//   Triangulation_2<Traits,Tds> t(Triangulation_2 tr)
//   t.swap ( Triangulation_2& tr)
// Access Functions
//   Geom_traits  t.geom_traits ()
//   TriangulationDataStructure_2  t.tds ()
//   TriangulationDataStructure_2 &  t.tds ()
//I/O
// ostream&  ostream& os << T  Inserts the triangulation t into the stream os.
// istream&  istream& is >> T  Reads a triangulation from stream is and assigns it to t.
