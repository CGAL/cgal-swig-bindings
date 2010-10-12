#ifndef SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H
#define SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_2.h>

template <class Triangulation,class Point>
class CGAL_Vertex_handle{
  typename Triangulation::Vertex_handle data;
  
public:
  #ifndef SWIG
  typedef typename Triangulation::Vertex_handle cpp_base;
  const typename Triangulation::Vertex_handle& get_data() const {return data;}
  typename Triangulation::Vertex_handle& get_data_ref() {return data;}
  #endif
//Creation
  CGAL_Vertex_handle():data(NULL){}
  #ifndef SWIG
  CGAL_Vertex_handle(typename Triangulation::Vertex_handle v):data(v){}
  #endif
//Access Functions  
  FORWARD_CALL_0_PTR(Point,point)
//Setting
  FORWARD_CALL_1_PTR(void,set_point,Point)
  
  bool equals(const CGAL_Vertex_handle<Triangulation,Point>& v){
    return data==v.get_data();
  }
  
  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Vertex_handle<Triangulation,Point>& v){return !equals(v);}
  #endif
};




template <class Triangulation,class Point>
class CGAL_Face_handle{
  typename Triangulation::Face_handle data;
  
public:
  #ifndef SWIG
  typedef typename Triangulation::Face_handle cpp_base;
  #endif
  typedef CGAL_Vertex_handle<Triangulation,Point> Vertex_handle;

  CGAL_Face_handle():data(NULL){}
  #ifndef SWIG
  CGAL_Face_handle(typename Triangulation::Face_handle v):data(v){}
  const typename Triangulation::Face_handle& get_data() const {return data;}
  typename Triangulation::Face_handle& get_data_ref() {return data;}
  #endif

//Access Functions    
  FORWARD_CALL_0_PTR(int,dimension)
  FORWARD_CALL_1_PTR(Vertex_handle,vertex,int)
  FORWARD_CALL_1_PTR(bool,has_vertex,Vertex_handle)
  FORWARD_CALL_1_PTR(int,index,Vertex_handle)
  FORWARD_CALL_1_PTR(CGAL_Face_handle,neighbor,int)
  FORWARD_CALL_1_PTR(bool,has_neighbor,CGAL_Face_handle)
  FORWARD_CALL_1_PTR(int,index,CGAL_Face_handle)
//Setting
  FORWARD_CALL_2_PTR(void,set_vertex,int,Vertex_handle)
  FORWARD_CALL_0_PTR(void,set_vertices)
  FORWARD_CALL_3_PTR(void,set_vertices,Vertex_handle,Vertex_handle,Vertex_handle)
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
  
  bool equals(const CGAL_Face_handle<Triangulation,Point>& c){
    return data==c.get_data();
  }  

  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Face_handle<Triangulation,Point>& c){return !equals(c);}
  #endif  
};

//Access Functions
//  bool   f.has_neigbor ( Face_handle n, int& i)
//  bool   f.has_vertex ( Vertex_handle v, int& i)  




#endif //SWIG_CGAL_TRIANGULATION_2_TRIANGULATION_HANDLES_H
