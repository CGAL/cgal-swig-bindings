#ifndef SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_HANDLES_H
#define SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_HANDLES_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_2.h>
#include <SWIG_CGAL/Common/triple.h>

template <class Triangulation,class Point>
class CGAL_Vertex_handle{
  typename Triangulation::Vertex_handle data;
  
public:
  typedef std::pair<double,double> Range;
  #ifndef SWIG
  typedef typename Triangulation::Vertex_handle cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  CGAL_Vertex_handle(cpp_base v):data(v){}
  #endif
//Creation
  CGAL_Vertex_handle():data(NULL){}
//Access Functions  
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(Point,point)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(Range,get_range)
//Setting
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_point,Point)
//Modifiers
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_range,Range)
    
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
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  CGAL_Face_handle(cpp_base v):data(v){}
  #endif
  typedef CGAL_Vertex_handle<Triangulation,Point> Vertex_handle;
  typedef SWIG_CGAL::Triple<double,double,double> Interval_3;
    
  CGAL_Face_handle():data(NULL){}


//Access Functions    
  SWIG_CGAL_FORWARD_CALL_0_PTR(int,dimension)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1_PTR(Vertex_handle,vertex,int)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,has_vertex,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1_PTR(int,index,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1_PTR(CGAL_Face_handle,neighbor,int)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,has_neighbor,CGAL_Face_handle)
  SWIG_CGAL_FORWARD_CALL_1_PTR(int,index,CGAL_Face_handle)
  SWIG_CGAL_FORWARD_CALL_0_PTR(double,get_alpha)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1_PTR(Interval_3,get_ranges,int)
//Setting
  SWIG_CGAL_FORWARD_CALL_2_PTR(void,set_vertex,int,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_0_PTR(void,set_vertices)
  SWIG_CGAL_FORWARD_CALL_3_PTR(void,set_vertices,Vertex_handle,Vertex_handle,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_2_PTR(void,set_neighbor,int,CGAL_Face_handle)
  SWIG_CGAL_FORWARD_CALL_0_PTR(void,set_neighbors)
  SWIG_CGAL_FORWARD_CALL_3_PTR(void,set_neighbors,CGAL_Face_handle,CGAL_Face_handle,CGAL_Face_handle)
//Orientation
  SWIG_CGAL_FORWARD_CALL_0_PTR(void,reorient)
  SWIG_CGAL_FORWARD_CALL_0_PTR(void,ccw_permute)
  SWIG_CGAL_FORWARD_CALL_0_PTR(void,cw_permute)
//Modifiers
  SWIG_CGAL_FORWARD_CALL_2_PTR(void,set_ranges,int,Interval_3)
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_alpha,double)
//Checking
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_valid)
  SWIG_CGAL_FORWARD_CALL_1_PTR(bool,is_valid,bool)
  
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




#endif //SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_HANDLES_H
