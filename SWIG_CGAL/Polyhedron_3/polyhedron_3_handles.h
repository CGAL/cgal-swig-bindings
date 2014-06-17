// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POLYHEDRON_3_HANDLES_H
#define SWIG_CGAL_POLYHEDRON_3_HANDLES_H

#include <SWIG_CGAL/Common/Macros.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <SWIG_CGAL/Polyhedron_3/Polyhedron_items_with_id_and_info_3.h>

namespace internal{
  
  template <class Items>
  struct Id{
    template <class T>
    static int get(const T&){return -1;};
    template <class T>
    static void set(const T&,int){};
  };

  template <>
  struct Id<CGAL::Polyhedron_items_with_id_3>{
    template <class T>
    static int get(const T& data){return data->id();};
    template <class T>
    static void set(T& data,int i){data->id()=i;};
  };

  template <class I>
  struct Id<CGAL::Polyhedron_items_with_id_and_info_3<I> >{
    template <class T>
    static int get(const T& data){return data->id();};
    template <class T>
    static void set(T& data,int i){data->id()=i;};
  };
  
  
} //namespace internal

namespace SWIG_Polyhedron_3
{

template <class Polyhedron_base>
class CGAL_Vertex_handle;

template <class Polyhedron_base>
class CGAL_Facet_handle;
  
template <class Polyhedron_base>
class CGAL_Halfedge_handle{
  typename Polyhedron_base::Halfedge_handle data;
  
public:
  #ifndef SWIG
  typedef typename Polyhedron_base::Halfedge_handle cpp_base;
  CGAL_Halfedge_handle(cpp_base h):data(h){}
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  typedef SWIG_CGAL_Circulator<typename Polyhedron_base::Halfedge_around_vertex_circulator,CGAL_Halfedge_handle<Polyhedron_base> > Halfedge_around_vertex_circulator;
  typedef SWIG_CGAL_Circulator<typename Polyhedron_base::Halfedge_around_facet_circulator,CGAL_Halfedge_handle<Polyhedron_base> >  Halfedge_around_facet_circulator;
  typedef CGAL_Halfedge_handle<Polyhedron_base> Self;

  CGAL_Halfedge_handle():data(NULL){}
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle,opposite)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle,next)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle,prev)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle,next_on_vertex)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle,prev_on_vertex)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_border)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_border_edge)

  Halfedge_around_vertex_circulator vertex_begin(){return Halfedge_around_vertex_circulator( data->vertex_begin() );}
  Halfedge_around_facet_circulator facet_begin(){return Halfedge_around_facet_circulator( data->facet_begin() );}
  
  SWIG_CGAL_FORWARD_CALL_0(unsigned,vertex_degree)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_bivalent)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_trivalent)

  SWIG_CGAL_FORWARD_CALL_0(unsigned,facet_degree)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_triangle)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_quad)

//Operations available if Supports_halfedge_vertex is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Vertex_handle<Polyhedron_base>,vertex)
//Operations available if Supports_halfedge_facet is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Facet_handle<Polyhedron_base>,facet)
  
  DEFINE_COMPARISON_OPERATORS(Self);
  DEFINE_HASH_FUNCTION_FOR_HANDLE

  int id(){return internal::Id<typename Polyhedron_base::Items>::get(data);}
  void set_id(int i){internal::Id<typename Polyhedron_base::Items>::set(data,i);}
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

template <class Polyhedron_base>
class CGAL_Vertex_handle{
  typename Polyhedron_base::Vertex_handle data;
  
public:
  #ifndef SWIG
  typedef typename Polyhedron_base::Vertex_handle cpp_base;
  CGAL_Vertex_handle(cpp_base h):data(h){}
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  typedef SWIG_CGAL_Circulator<typename Polyhedron_base::Halfedge_around_vertex_circulator,CGAL_Halfedge_handle<Polyhedron_base> > Halfedge_around_vertex_circulator;
  typedef SWIG_CGAL_Circulator<typename Polyhedron_base::Halfedge_around_facet_circulator,CGAL_Halfedge_handle<Polyhedron_base> >  Halfedge_around_facet_circulator;
  typedef CGAL_Vertex_handle<Polyhedron_base> Self;
        
  CGAL_Vertex_handle():data(NULL){}

//Operations available if Supports_vertex_point is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Point_3,point)
//Operations available if Supports_vertex_halfedge is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle<Polyhedron_base>,halfedge)
  Halfedge_around_vertex_circulator vertex_begin(){return Halfedge_around_vertex_circulator( data->vertex_begin() );}
  SWIG_CGAL_FORWARD_CALL_1(void,set_halfedge,CGAL_Halfedge_handle<Polyhedron_base>)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,vertex_degree)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_bivalent)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_trivalent)

  DEFINE_COMPARISON_OPERATORS(Self);
  DEFINE_HASH_FUNCTION_FOR_HANDLE

  int id(){return internal::Id<typename Polyhedron_base::Items>::get(data);}
  void set_id(int i){internal::Id<typename Polyhedron_base::Items>::set(data,i);}  
  
  void set_point(const Point_3& p){ data->point() =  internal::Converter<Point_3>::convert(p);}  
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

template <class Polyhedron_base>
class CGAL_Facet_handle{
  typename Polyhedron_base::Facet_handle data;
  
public:
  #ifndef SWIG  
  typedef typename Polyhedron_base::Facet_handle cpp_base;
  CGAL_Facet_handle(cpp_base h):data(h){}
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif

  typedef SWIG_CGAL_Circulator<typename Polyhedron_base::Halfedge_around_facet_circulator,CGAL_Halfedge_handle<Polyhedron_base> >  Halfedge_around_facet_circulator;
  typedef CGAL_Facet_handle<Polyhedron_base> Self;

  CGAL_Facet_handle():data(NULL){}
//Operations available if Supports_facet_plane is CGAL::Tag_true
  #ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Plane_3,plane)
  #endif
//Operations available if Supports_facet_halfedge ? CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(CGAL_Halfedge_handle<Polyhedron_base>,halfedge)
  Halfedge_around_facet_circulator facet_begin(){return Halfedge_around_facet_circulator( data->facet_begin() );}
  SWIG_CGAL_FORWARD_CALL_1(void,set_halfedge,CGAL_Halfedge_handle<Polyhedron_base>)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,facet_degree)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_triangle)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_quad)

  DEFINE_COMPARISON_OPERATORS(Self);
  DEFINE_HASH_FUNCTION_FOR_HANDLE
  
  int id(){return internal::Id<typename Polyhedron_base::Items>::get(data);}
  void set_id(int i){internal::Id<typename Polyhedron_base::Items>::set(data,i);}
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

} //namespace SWIG_Polyhedron_3

#endif //SWIG_CGAL_POLYHEDRON_3_HANDLES_H
