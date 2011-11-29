// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_HANDLES_H
#define SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_HANDLES_H

#include <SWIG_CGAL/Common/Macros.h>

namespace SWIG_Triangulation_3{

template <class Triangulation,class Point>
class CGAL_Cell_handle;

template <class Triangulation,class Point>
class CGAL_Vertex_handle{
  typename Triangulation::Vertex_handle data;
public:
  #ifndef SWIG
  typedef typename Triangulation::Vertex_handle cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  CGAL_Vertex_handle(cpp_base v):data(v){}
  #endif
  typedef CGAL_Cell_handle<Triangulation,Point> Cell_handle;
  
//Creation
  CGAL_Vertex_handle():data(NULL){}
//Modifiers  
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point,point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Cell_handle,cell)
  SWIG_CGAL_FORWARD_CALL_1(void,set_cell,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1(void,set_point,Point)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_valid,bool)
//equality functions
  bool equals(const CGAL_Vertex_handle<Triangulation,Point>& v){
    return data==v.get_data();
  }
  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Vertex_handle<Triangulation,Point>& v){return !equals(v);}
  #endif
//Deep copy
  typedef CGAL_Vertex_handle<Triangulation,Point> Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};


template <class Triangulation,class Point>
class CGAL_Cell_handle{
  typename Triangulation::Cell_handle data;
  
public:
  #ifndef SWIG
  typedef typename Triangulation::Cell_handle cpp_base;
  CGAL_Cell_handle(cpp_base v):data(v){}
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  
  typedef CGAL_Vertex_handle<Triangulation,Point> Vertex_handle;
  typedef CGAL_Cell_handle<Triangulation,Point> Cell_handle;
//Creation
  CGAL_Cell_handle():data(NULL){}
//Modifiers
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,vertex,int)
  SWIG_CGAL_FORWARD_CALL_1(int,index,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_vertex,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Cell_handle,neighbor,int)
  SWIG_CGAL_FORWARD_CALL_1(int,index,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_neighbor,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_2(void,set_vertex,int,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_4(void,set_vertices,Vertex_handle,Vertex_handle,Vertex_handle,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_2(void,set_neighbor,int,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_4(void,set_neighbors,Cell_handle,Cell_handle,Cell_handle,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_valid,bool)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_valid,bool,int)
//Equality functions  
  bool equals(const CGAL_Cell_handle<Triangulation,Point>& c){
    return data==c.get_data();
  }  
  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Cell_handle<Triangulation,Point>& c){return !equals(c);}
  #endif  
//Deep copy
  typedef CGAL_Cell_handle<Triangulation,Point> Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
  
  //SWIG_CGAL_FORWARD_CALL_2(bool has_vertex,Vertex_handle, int & i)  
  //bool has_neighbor ( Cell_handle n, int & i)  
};

} //namespace SWIG_Triangulation_3

#endif //SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_HANDLES_H
