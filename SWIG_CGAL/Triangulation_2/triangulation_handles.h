// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H
#define SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_2.h>

namespace SWIG_Triangulation_2{

template <class Triangulation,class Point>
class CGAL_Vertex_handle{
  typename Triangulation::Vertex_handle data;
public:
  typedef CGAL_Vertex_handle<Triangulation,Point> Self;
  #ifndef SWIG
  typedef typename Triangulation::Vertex_handle cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
//Creation
  CGAL_Vertex_handle():data(NULL){}
  #ifndef SWIG
  CGAL_Vertex_handle(typename Triangulation::Vertex_handle v):data(v){}
  #endif
//Access Functions  
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point,point)
//Setting
  SWIG_CGAL_FORWARD_CALL_1(void,set_point,Point)
//Comparision Functions
  DEFINE_COMPARISON_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE

//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();} 
};




template <class Triangulation,class Point>
class CGAL_Face_handle{
  typename Triangulation::Face_handle data;
public:
  typedef CGAL_Face_handle<Triangulation,Point> Self;
  typedef CGAL_Vertex_handle<Triangulation,Point> Vertex_handle;

  CGAL_Face_handle():data(NULL){}
  #ifndef SWIG
  typedef typename Triangulation::Face_handle cpp_base;
  CGAL_Face_handle(typename Triangulation::Face_handle v):data(v){}
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif

//Access Functions    
  SWIG_CGAL_FORWARD_CALL_0(int,dimension)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,vertex,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_vertex,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(int,index,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(CGAL_Face_handle,neighbor,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_neighbor,CGAL_Face_handle)
  SWIG_CGAL_FORWARD_CALL_1(int,index,CGAL_Face_handle)
//Setting
  SWIG_CGAL_FORWARD_CALL_2(void,set_vertex,int,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_0(void,set_vertices)
  SWIG_CGAL_FORWARD_CALL_3(void,set_vertices,Vertex_handle,Vertex_handle,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_2(void,set_neighbor,int,CGAL_Face_handle)
  SWIG_CGAL_FORWARD_CALL_0(void,set_neighbors)
  SWIG_CGAL_FORWARD_CALL_3(void,set_neighbors,CGAL_Face_handle,CGAL_Face_handle,CGAL_Face_handle)
//Orientation
  SWIG_CGAL_FORWARD_CALL_0(void,reorient)
  SWIG_CGAL_FORWARD_CALL_0(void,ccw_permute)
  SWIG_CGAL_FORWARD_CALL_0(void,cw_permute)
//Checking
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_valid,bool)
//Comparision Functions
  DEFINE_COMPARISON_OPERATORS(Self);
//hash function
  DEFINE_HASH_FUNCTION_FOR_HANDLE
 
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

} //namespace SWIG_Triangulation_2

//Access Functions
//  bool   f.has_neigbor ( Face_handle n, int& i)
//  bool   f.has_vertex ( Vertex_handle v, int& i)  




#endif //SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H
