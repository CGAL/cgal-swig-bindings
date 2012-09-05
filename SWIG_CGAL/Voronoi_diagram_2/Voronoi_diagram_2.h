// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Voronoi_diagram_2/Voronoi_diagram_handles_2.h>
#include <SWIG_CGAL/Voronoi_diagram_2/Locate_result.h>
#include <fstream>

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Kernel_object>
struct Kernel_iterator_helper{
  typedef typename internal::Converter<Kernel_object>::result_type Base;
  typedef std::pair<Input_iterator_wrapper<Kernel_object,Base>,Input_iterator_wrapper<Kernel_object,Base> > input;
  typedef boost::function_output_iterator< Container_writer<Kernel_object,Base> >                                       output;
};

typedef Kernel_iterator_helper<Point_2>::input       Point_range; 
typedef Kernel_iterator_helper<Point_2>::output      Point_output_iterator; 
#else
typedef Generic_input_iterator<Point_2>  Point_range;
typedef Generic_output_iterator<Point_2>  Point_output_iterator;
#endif


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
  typedef typename Kernel_iterator_helper<SiteWrapper>::input SiteRange;

//Creation
  Voronoi_diagram_2_wrapper(){}
  Voronoi_diagram_2_wrapper(TriangulationWrapper& triangulation,bool swap_dg = false):data( triangulation.get_data(), swap_dg) {}
  Voronoi_diagram_2_wrapper(SiteRange range){ data.insert( SWIG_CGAL::get_begin(range), SWIG_CGAL::get_end(range) ); }
  
//Insertion
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Face_wrapper,insert,SiteWrapper)
  int insert ( SiteRange range ){ return data.insert( SWIG_CGAL::get_begin(range), SWIG_CGAL::get_end(range) ); }

//Access Methods
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(TriangulationWrapper,dual)
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
//Queries
  typedef Locate_result_wrapper<Vertex_wrapper, Halfedge_wrapper, Face_wrapper> Locate_result;
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Locate_result,locate, Point_2);
};

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_2_H


//Traversal of the Voronoi diagram
//  Iterators
//    Face_iterator  vd.faces_begin ()  Starts at an arbitrary Voronoi face.
//    Face_iterator  vd.faces_end ()  Past-the-end iterator.
//
//    Unbounded_faces_iterator  vd.unbounded_faces_begin ()
//    Unbounded_faces_iterator  vd.unbounded_faces_end ()
//
//    Bounded_faces_iterator  vd.bounded_faces_begin ()
//    Bounded_faces_iterator  vd.bounded_faces_end ()
//
//    Edge_iterator  vd.edges_begin ()
//    Edge_iterator  vd.edges_end ()
//
//    Halfedge_iterator  vd.halfedges_begin ()
//    Halfedge_iterator  vd.halfedges_end ()
//
//    Unbounded_halfedges_iterator  vd.unbounded_halfedges_begin ()
//    Unbounded_halfedges_iterator  vd.unbounded_halfedges_end ()
//
//    Bounded_halfedges_iterator  vd.bounded_halfedges_begin ()
//    Bounded_halfedges_iterator  vd.bounded_halfedges_end ()
//
//    Vertex_iterator  vd.vertices_begin ()
//    Vertex_iterator  vd.vertices_end ()
//
//    Site_iterator  vd.sites_begin ()
//    Site_iterator  vd.sites_end ()
//
//  Circulators
//
//    Ccb_halfedge_circulator  vd.ccb_halfedges ( Face_handle f)
//    Ccb_halfedge_circulator  vd.ccb_halfedges ( Face_handle f, Halfedge_handle h)
//
//    Halfedge_around_vertex_circulator  vd.incident_halfedges ( Vertex_handle v)
//    Halfedge_around_vertex_circulator  vd.incident_halfedges ( Vertex_handle v, Halfedge_handle h)
//
//

