#ifndef SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H
#define SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H

#include "../Common/Macros.h"
#include "../Kernel/Point_2.h"

template <class Triangulation>
class CGAL_Face_handle;

template <class Triangulation>
class CGAL_Vertex_handle{
  typename Triangulation::Vertex_handle data;
  
public:
  typedef typename Triangulation::Vertex_handle cpp_base;
  typename Triangulation::Vertex_handle get_data() const {return data;}
  typename Triangulation::Vertex_handle& get_data_ref() {return data;}
//Creation
  CGAL_Vertex_handle():data(NULL){}
  CGAL_Vertex_handle(typename Triangulation::Vertex_handle v):data(v){}
//Access Functions  
  FORWARD_CALL_0_PTR(Point_2,point)
//Setting
  FORWARD_CALL_1_PTR(void,set_point,Point_2)
  
  bool equals(const CGAL_Vertex_handle<Triangulation>& v){
    return data==v.get_data();
  }
  
  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Vertex_handle<Triangulation>& v){return !equals(v);}
  #endif
};




template <class Triangulation>
class CGAL_Face_handle{
  typename Triangulation::Face_handle data;
  
public:
  typedef typename Triangulation::Face_handle cpp_base;

  CGAL_Face_handle():data(NULL){}
  CGAL_Face_handle(typename Triangulation::Face_handle v):data(v){}
  typename Triangulation::Face_handle get_data() const {return data;}
  typename Triangulation::Face_handle& get_data_ref() {return data;}

//Access Functions    
  FORWARD_CALL_0_PTR(int,dimension)
  FORWARD_CALL_1_PTR(CGAL_Vertex_handle<Triangulation>,vertex,int)
  FORWARD_CALL_1_PTR(bool,has_vertex,CGAL_Vertex_handle<Triangulation>)
  FORWARD_CALL_1_PTR(int,index,CGAL_Vertex_handle<Triangulation>)
  FORWARD_CALL_1_PTR(CGAL_Face_handle,neighbor,int)
  FORWARD_CALL_1_PTR(bool,has_neighbor,CGAL_Face_handle)
  FORWARD_CALL_1_PTR(int,index,CGAL_Face_handle<Triangulation>)
//Setting
  FORWARD_CALL_2_PTR(void,set_vertex,int,CGAL_Vertex_handle<Triangulation>)
  FORWARD_CALL_0_PTR(void,set_vertices)
  FORWARD_CALL_3_PTR(void,set_vertices,CGAL_Vertex_handle<Triangulation>,CGAL_Vertex_handle<Triangulation>,CGAL_Vertex_handle<Triangulation>)
  FORWARD_CALL_2_PTR(void,set_neighbor,int,CGAL_Face_handle)
  FORWARD_CALL_0_PTR(void,set_neighbors)
  FORWARD_CALL_3_PTR(void,set_neighbors,CGAL_Face_handle,CGAL_Face_handle,CGAL_Face_handle)
//Orientation
  FORWARD_CALL_0_PTR(void,reorient)
  FORWARD_CALL_0_PTR(void,ccw_permute)
  FORWARD_CALL_0_PTR(void,cw_permute)
//Checking
  FORWARD_CALL_0_PTR(bool,is_valid)
  FORWARD_CALL_1_PTR(bool,is_valid,bool)
  
  bool equals(const CGAL_Face_handle<Triangulation>& c){
    return data==c.get_data();
  }  

  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Face_handle<Triangulation>& c){return !equals(c);}
  #endif  
};

//Access Functions
//  bool   f.has_neigbor ( Face_handle n, int& i)
//  bool   f.has_vertex ( Vertex_handle v, int& i)  




#endif //SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H
