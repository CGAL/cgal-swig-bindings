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
  

  CGAL_Vertex_handle():data(NULL){}
  
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(Point,point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(Cell_handle,cell)
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_cell,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_point,Point)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,is_valid,bool)

  
  bool equals(const CGAL_Vertex_handle<Triangulation,Point>& v){
    return data==v.get_data();
  }
  
  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Vertex_handle<Triangulation,Point>& v){return !equals(v);}
  #endif
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

  CGAL_Cell_handle():data(NULL){}
  
  
  SWIG_CGAL_FORWARD_CALL_AND_REF_1_PTR(Vertex_handle,vertex,int)
  SWIG_CGAL_FORWARD_CALL_1_PTR(int,index,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,has_vertex,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1_PTR(Cell_handle,neighbor,int)
  SWIG_CGAL_FORWARD_CALL_1_PTR(int,index,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,has_neighbor,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_2_PTR(void,set_vertex,int,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_4_PTR(void,set_vertices,Vertex_handle,Vertex_handle,Vertex_handle,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_2_PTR(void,set_neighbor,int,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_4_PTR(void,set_neighbors,Cell_handle,Cell_handle,Cell_handle,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,is_valid,bool)
  SWIG_CGAL_FORWARD_CALL_2_PTR(bool,is_valid,bool,int)
  
  bool equals(const CGAL_Cell_handle<Triangulation,Point>& c){
    return data==c.get_data();
  }  

  #ifdef SWIGPYTHON
  bool __ne__(const CGAL_Cell_handle<Triangulation,Point>& c){return !equals(c);}
  #endif  

  //SWIG_CGAL_FORWARD_CALL_2(bool has_vertex,Vertex_handle, int & i)  
  //bool has_neighbor ( Cell_handle n, int & i)  
};

} //namespace SWIG_Triangulation_3

#endif //SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_HANDLES_H
