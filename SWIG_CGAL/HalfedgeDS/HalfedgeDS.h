// ------------------------------------------------------------------------------
// Copyright (c) 2013 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_H
#define SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/HalfedgeDS/HalfedgeDS_handles.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/HalfedgeDS/General_modifier.h>
#include <boost/shared_ptr.hpp>

template < class HDS_cpp >
class HalfedgeDS_wrapper
{
  boost::shared_ptr<HDS_cpp> data_sptr;
public:
  typedef HDSVertex_wrapper<HDS_cpp>   Vertex_wrapper;
  typedef HDSHalfedge_wrapper<HDS_cpp> Hedge_wrapper;
  typedef HDSFace_wrapper<HDS_cpp>     Face_wrapper;

  //iterator types
  typedef SWIG_CGAL_Iterator<typename HDS_cpp::Vertex_iterator,Vertex_wrapper>  Vertex_range;
  typedef SWIG_CGAL_Iterator<typename HDS_cpp::Halfedge_iterator,Hedge_wrapper>  Halfedge_range;
  typedef SWIG_CGAL_Iterator<typename HDS_cpp::Face_iterator,Face_wrapper>  Face_range;

  #ifndef SWIG
  typedef HDS_cpp cpp_base;


  const cpp_base& get_data() const {return *data_sptr;}
        cpp_base& get_data()       {return *data_sptr;}
  HalfedgeDS_wrapper(const cpp_base& base):data_sptr(new cpp_base(base)){};
  boost::shared_ptr<cpp_base> shared_ptr() {return data_sptr;}
  #endif

//Construction
  HalfedgeDS_wrapper():data_sptr(new cpp_base()){};
  HalfedgeDS_wrapper(int v, int h, int f):data_sptr( new cpp_base(v,h,f) ){}
  HalfedgeDS_wrapper( const HalfedgeDS_wrapper& hds2):data_sptr( new cpp_base(hds2.get_data()) ){}

  SWIG_CGAL_FORWARD_CALL_3(void,reserve,int,int,int)
// Access Member Functions

  SWIG_CGAL_FORWARD_CALL_0(int,size_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(int,size_of_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(int,size_of_faces)
  SWIG_CGAL_FORWARD_CALL_0(int,capacity_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(int,capacity_of_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(int,capacity_of_faces);
  SWIG_CGAL_FORWARD_CALL_0(int,bytes);
  SWIG_CGAL_FORWARD_CALL_0(int,bytes_reserved)

  Vertex_range vertices() { return Vertex_range( get_data().vertices_begin(), get_data().vertices_end() ); }
  Halfedge_range halfedges() { return Halfedge_range( get_data().halfedges_begin(), get_data().halfedges_end() ); }
  Face_range faces() { return Face_range( get_data().faces_begin(), get_data().faces_end() ); }

// Insertion (I tweaked a little bit CGAL's function as the simplices classes are not exposed (only the handles)
  Vertex_wrapper vertices_push_back(){
    return Vertex_wrapper( get_data().vertices_push_back( typename cpp_base::Vertex() ) );
  }
  Vertex_wrapper vertices_push_back(const Point_2& p){
    return Vertex_wrapper( get_data().vertices_push_back( typename cpp_base::Vertex(p.get_data()) ) );
  }
  Hedge_wrapper edges_push_back() {
    return Hedge_wrapper(
              get_data().edges_push_back(typename cpp_base::Halfedge(),
                                         typename cpp_base::Halfedge()) );
  }
  Face_wrapper faces_push_back() {
    return Face_wrapper(
      get_data().faces_push_back(typename cpp_base::Face()) );
  }

// Removal
  SWIG_CGAL_FORWARD_CALL_0(void,vertices_pop_front)
  SWIG_CGAL_FORWARD_CALL_0(void,vertices_pop_back)
  SWIG_CGAL_FORWARD_CALL_1(void,vertices_erase,Vertex_wrapper)
  SWIG_CGAL_FORWARD_CALL_2(void,vertices_erase,Vertex_wrapper,Vertex_wrapper)
  SWIG_CGAL_FORWARD_CALL_0(void,edges_pop_front)
  SWIG_CGAL_FORWARD_CALL_0(void,edges_pop_back)
  SWIG_CGAL_FORWARD_CALL_1(void,edges_erase,Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_2(void,edges_erase,Hedge_wrapper,Hedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_0(void,faces_pop_front)
  SWIG_CGAL_FORWARD_CALL_0(void,faces_pop_back)
  SWIG_CGAL_FORWARD_CALL_1(void,faces_erase,Face_wrapper)
  SWIG_CGAL_FORWARD_CALL_2(void,faces_erase,Face_wrapper,Face_wrapper)
  SWIG_CGAL_FORWARD_CALL_0(void,vertices_clear)
  SWIG_CGAL_FORWARD_CALL_0(void,edges_clear)
  SWIG_CGAL_FORWARD_CALL_0(void,faces_clear)
  SWIG_CGAL_FORWARD_CALL_0(void,clear)


// Operations with Border Halfedges
  SWIG_CGAL_FORWARD_CALL_0(void,normalize_border)
  SWIG_CGAL_FORWARD_CALL_0(int,size_of_border_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(int,size_of_border_edges)
  Halfedge_range border_halfedges(){ return Halfedge_range(get_data().border_halfedges_begin(), get_data().halfedges_end()); }

//Deep copy
  typedef HalfedgeDS_wrapper<HDS_cpp> Self;
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){get_data()=other.get_data();}
//For convenience add the modifier mechanism
  void delegate(General_modifier<HDS_cpp> modifier){modifier(get_data());}

};

#endif //SWIG_CGAL_HALFEDGEDS_HALFEDGEDS_H
