// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_HANDLES_2_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_HANDLES_2_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Voronoi_diagram_2/typedefs.h>

#include <CGAL/Voronoi_diagram_2/Handle_adaptor.h>

#ifndef SWIG
//overload to be used in FORWARD macros
template <class T>
T&
SWIG_CGAL_extract_data(CGAL::VoronoiDiagram_2::Internal::Handle_adaptor<T>& t)
{return *t;}

template <class T>
const T&
SWIG_CGAL_extract_data(const CGAL::VoronoiDiagram_2::Internal::Handle_adaptor<T>& t)
{return *t;}
#endif


template < class VD_2, class Delaunay_vertex_handle_wrapper, class Delaunay_face_handle_wrapper >
class Voronoi_face_wrapper_2;

template < class VD_2, class Delaunay_vertex_handle_wrapper, class Delaunay_face_handle_wrapper>
class Voronoi_halfedge_wrapper_2;

template < class VD_2, class Delaunay_vertex_handle_wrapper, class Delaunay_face_handle_wrapper >
class Voronoi_vertex_wrapper_2{
  typename VD_2::Vertex_handle data;
public:
  #ifndef SWIG
  typedef typename VD_2::Vertex_handle cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Voronoi_vertex_wrapper_2(const cpp_base& base):data(base){}
  #endif

  typedef Voronoi_vertex_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Self;
  typedef Voronoi_halfedge_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Halfedge_wrapper;
  typedef Voronoi_face_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Face_wrapper;

//Creation
  Voronoi_vertex_wrapper_2():data(NULL){}    
//Access Methods
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Halfedge_wrapper,halfedge)
  SWIG_CGAL_FORWARD_CALL_0(int,degree)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_2,point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_face_handle_wrapper,dual)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Delaunay_vertex_handle_wrapper,site,int)
  //TODO Halfedge_around_vertex_circulator incident_halfedges

//Predicate Methods
  SWIG_CGAL_FORWARD_CALL_1(bool,is_incident_edge,Halfedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_incident_face,Face_wrapper)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
//Equality Functions  
  DEFINE_EQUALITY_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();} 
};

template < class VD_2, class Delaunay_vertex_handle_wrapper, class Delaunay_face_handle_wrapper >
class Voronoi_face_wrapper_2{
  typename VD_2::Face_handle data;
public:
  #ifndef SWIG
  typedef typename VD_2::Face_handle cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Voronoi_face_wrapper_2(const cpp_base& base):data(base){}
  #endif

  typedef Voronoi_face_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Self;
  typedef Voronoi_halfedge_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Halfedge_wrapper;
  typedef SWIG_CGAL_Circulator< typename VD_2::Ccb_halfedge_circulator, Halfedge_wrapper > Ccb_halfedge_circulator;
//Creation
  Voronoi_face_wrapper_2():data(NULL){}    
//Access Methods
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Halfedge_wrapper,halfedge)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Ccb_halfedge_circulator,outer_ccb)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_vertex_handle_wrapper,dual)
    
//Predicate Methods
  SWIG_CGAL_FORWARD_CALL_0(bool,is_unbounded)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_halfedge_on_ccb,Halfedge_wrapper)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
//Equality Functions  
  DEFINE_EQUALITY_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();} 
};

template < class VD_2, class Delaunay_vertex_handle_wrapper, class Delaunay_face_handle_wrapper >
class Voronoi_halfedge_wrapper_2{
  typename VD_2::Halfedge_handle  data;
public:
  #ifndef SWIG
  typedef typename VD_2::Halfedge_handle cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Voronoi_halfedge_wrapper_2(const cpp_base& base):data(base){}
  #endif

  typedef Voronoi_halfedge_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Self;
  typedef Voronoi_face_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Face_wrapper;
  typedef Voronoi_vertex_wrapper_2<VD_2,Delaunay_vertex_handle_wrapper, Delaunay_face_handle_wrapper> Vertex_wrapper;
  typedef std::pair<Delaunay_face_handle_wrapper,int> Delaunay_edge;
  typedef SWIG_CGAL_Circulator< typename VD_2::Ccb_halfedge_circulator, Self > Ccb_halfedge_circulator;
//Creation
  Voronoi_halfedge_wrapper_2():data(NULL){}    
//Access Methods
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Self,twin)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Self,opposite)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Self,next)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Self,previous)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Face_wrapper,face)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vertex_wrapper,source)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Vertex_wrapper,target)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Ccb_halfedge_circulator,ccb)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_edge,dual)


  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_vertex_handle_wrapper,up)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_vertex_handle_wrapper,down)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_vertex_handle_wrapper,left)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Delaunay_vertex_handle_wrapper,right)
  

//Predicate Methods
  SWIG_CGAL_FORWARD_CALL_0(bool,has_source)
  SWIG_CGAL_FORWARD_CALL_0(bool,has_target)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_unbounded)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_bisector)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_segment)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_ray)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
//Equality Functions  
  DEFINE_EQUALITY_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();} 
};

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_VORONOI_DIAGRAM_HANDLES_2_H
