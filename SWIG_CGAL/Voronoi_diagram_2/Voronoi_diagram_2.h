// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Voronoi_diagram_2/Voronoi_diagram_handles_2.h>
#include <SWIG_CGAL/Voronoi_diagram_2/Locate_result.h>
#include <fstream>


template <class CppBase, class SiteWrapper, class TriangulationWrapper, class TriangulationVertexWrapper, class TriangulationFaceWrapper, class Vertex_wrapper, class Halfedge_wrapper, class Face_wrapper >
class Voronoi_diagram_2_wrapper{
public:
  #ifndef SWIG
  CppBase data;
  typedef CppBase cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Voronoi_diagram_2_wrapper(const cpp_base& base):data(base){}
  #endif

  typedef Voronoi_diagram_2_wrapper<CppBase, SiteWrapper, TriangulationWrapper,TriangulationVertexWrapper, TriangulationFaceWrapper, Vertex_wrapper, Halfedge_wrapper, Face_wrapper> Self;
  typedef std::pair<TriangulationFaceWrapper,int> TriangulationEdgeWrapper;
  typedef typename Wrapper_iterator_helper<SiteWrapper>::input SiteRange;

  //iterator types
  typedef SWIG_CGAL_Iterator<typename CppBase::Vertex_iterator,Vertex_wrapper>  Vertex_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Face_iterator, Face_wrapper> Face_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Unbounded_faces_iterator, Face_wrapper> Unbounded_faces_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Bounded_faces_iterator, Face_wrapper> Bounded_faces_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Edge_iterator, Halfedge_wrapper> Edge_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Halfedge_iterator, Halfedge_wrapper> Halfedge_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Unbounded_halfedges_iterator, Halfedge_wrapper> Unbounded_halfedges_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Bounded_halfedges_iterator, Halfedge_wrapper> Bounded_halfedges_iterator;
  typedef SWIG_CGAL_Iterator<typename CppBase::Site_iterator, SiteWrapper>  Site_iterator;
  //circulator types
  typedef SWIG_CGAL_Circulator< typename CppBase::Ccb_halfedge_circulator, Halfedge_wrapper > Ccb_halfedge_circulator;
  typedef SWIG_CGAL_Circulator< typename CppBase::Halfedge_around_vertex_circulator, Halfedge_wrapper > Halfedge_around_vertex_circulator;
  
    
//Creation
  Voronoi_diagram_2_wrapper(){}
  Voronoi_diagram_2_wrapper(TriangulationWrapper& triangulation,bool swap_dg = false):data( triangulation.get_data(), swap_dg) {}
  Voronoi_diagram_2_wrapper(SiteRange range){ data.insert( SWIG_CGAL::get_begin(range), SWIG_CGAL::get_end(range) ); }
  
//Insertion
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Face_wrapper,insert,SiteWrapper)
  int insert ( SiteRange range ){ return data.insert( SWIG_CGAL::get_begin(range), SWIG_CGAL::get_end(range) ); }

//Access Methods
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(TriangulationWrapper,dual)
//TriangulationWrapper dual()
//{ return TriangulationWrapper( this->get_data().dual() ); }
//void dual(TriangulationWrapper& ref)
//{ref = TriangulationWrapper(SWIG_CGAL_extract_data(this->get_data()).dual());}

  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_wrapper,dual,TriangulationEdgeWrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_wrapper,dual,TriangulationFaceWrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Face_wrapper,dual,TriangulationVertexWrapper)
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_faces)
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_connected_components)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Face_wrapper,unbounded_face)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Face_wrapper,bounded_face)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Halfedge_wrapper,unbounded_halfedge)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Halfedge_wrapper,bounded_halfedge)
  
//Validity check
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(void,clear)
  void swap(Self& other){ get_data().swap(other.get_data()); }
//I/O
  void  file_output ( const char* fname ){
    std::ofstream out(fname);
    if (out) out << data;
  }
  void  file_input ( const char* fname ){
    std::ifstream in(fname);
    if (in) in >> data;    
  }
//Traversal of the Voronoi diagram
//  Iterators
  Face_iterator faces() { return Face_iterator(get_data().faces_begin(),get_data().faces_end()); }
  Unbounded_faces_iterator  unbounded_faces(){ return Unbounded_faces_iterator(get_data().unbounded_faces_begin(), get_data().unbounded_faces_end()); }
  Bounded_faces_iterator  bounded_faces() {return Bounded_faces_iterator(get_data().bounded_faces_begin(), get_data().bounded_faces_end ()); }

  Edge_iterator edges() { return  Edge_iterator(get_data().edges_begin(), get_data().edges_end() ); }
  Halfedge_iterator halfedges() { return Halfedge_iterator( get_data().halfedges_begin(), get_data().halfedges_end() ); }
  Unbounded_halfedges_iterator unbounded_halfedges(){ return Unbounded_halfedges_iterator( get_data().unbounded_halfedges_begin(), get_data().unbounded_halfedges_end() ); }
  Bounded_halfedges_iterator bounded_halfedges() {return Bounded_halfedges_iterator(get_data().bounded_halfedges_begin(), get_data().bounded_halfedges_end() ); }

  Vertex_iterator  vertices() { return Vertex_iterator( get_data().vertices_begin(), get_data().vertices_end() ); }
  Site_iterator  sites() { return Site_iterator( get_data().sites_begin(), get_data().sites_end() ); }

//  Circulators
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Ccb_halfedge_circulator,ccb_halfedges,Face_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Ccb_halfedge_circulator,ccb_halfedges,Face_wrapper,Halfedge_wrapper)

  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_around_vertex_circulator,incident_halfedges,Vertex_wrapper)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Halfedge_around_vertex_circulator,incident_halfedges,Vertex_wrapper,Halfedge_wrapper)
  
//Queries
  typedef Locate_result_wrapper<Vertex_wrapper, Halfedge_wrapper, Face_wrapper> Locate_result;
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Locate_result,locate, Point_2);
};

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H
