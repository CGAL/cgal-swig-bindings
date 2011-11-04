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

template <class T,class R> class CGAL_Halfedge_around_vertex_circulator;
template <class T,class R> class CGAL_Halfedge_around_facet_circulator;

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
  const typename Polyhedron_base::Halfedge_handle&  get_data() const {return data;}
  typename Polyhedron_base::Halfedge_handle& get_data_ref() {return data;}
  #endif

  CGAL_Halfedge_handle():data(NULL){}
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle,opposite)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle,next)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle,prev)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle,next_on_vertex)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle,prev_on_vertex)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_border)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_border_edge)

  CGAL_Halfedge_around_vertex_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> > vertex_begin(){return CGAL_Halfedge_around_vertex_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> >( data->vertex_begin() );}
  CGAL_Halfedge_around_facet_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> > facet_begin(){return CGAL_Halfedge_around_facet_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> >( data->facet_begin() );}
  
  SWIG_CGAL_FORWARD_CALL_0_PTR(unsigned,vertex_degree)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_bivalent)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_trivalent)

  SWIG_CGAL_FORWARD_CALL_0_PTR(unsigned,facet_degree)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_triangle)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_quad)

//Operations available if Supports_halfedge_vertex is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Vertex_handle<Polyhedron_base>,vertex)
//Operations available if Supports_halfedge_facet is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Facet_handle<Polyhedron_base>,facet)
  
  bool equals(const CGAL_Halfedge_handle<Polyhedron_base>& he){ return get_data()==he.get_data(); }
  int hashCode(){ return *reinterpret_cast<int*> (&*data);}

  int id(){return internal::Id<typename Polyhedron_base::Items>::get(data);}
  void set_id(int i){internal::Id<typename Polyhedron_base::Items>::set(data,i);}
};

template <class Polyhedron_base>
class CGAL_Vertex_handle{
  typename Polyhedron_base::Vertex_handle data;
  
public:
  #ifndef SWIG
  typedef typename Polyhedron_base::Vertex_handle cpp_base;
  CGAL_Vertex_handle(cpp_base h):data(h){}
  const cpp_base&  get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}
  #endif
  
  CGAL_Vertex_handle():data(NULL){}

//Operations available if Supports_vertex_point is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(Point_3,point)
//Operations available if Supports_vertex_halfedge is CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle<Polyhedron_base>,halfedge)
  CGAL_Halfedge_around_vertex_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> > vertex_begin(){return CGAL_Halfedge_around_vertex_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> >( data->vertex_begin() );}
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_halfedge,CGAL_Halfedge_handle<Polyhedron_base>)
  SWIG_CGAL_FORWARD_CALL_0_PTR(unsigned,vertex_degree)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_bivalent)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_trivalent)

  bool equals(const CGAL_Vertex_handle<Polyhedron_base>& v){ return get_data()==v.get_data(); }
  int hashCode(){ return *reinterpret_cast<int*> (&*data);}

  int id(){return internal::Id<typename Polyhedron_base::Items>::get(data);}
  void set_id(int i){internal::Id<typename Polyhedron_base::Items>::set(data,i);}  

  void set_point(const Point_3& p){ data->point() =  internal::Converter<Point_3>::convert(p);}  

};

template <class Polyhedron_base>
class CGAL_Facet_handle{
  typename Polyhedron_base::Facet_handle data;
  
public:
  #ifndef SWIG  
  typedef typename Polyhedron_base::Facet_handle cpp_base;
  CGAL_Facet_handle(cpp_base h):data(h){}
  const cpp_base&  get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}
  #endif
  
  CGAL_Facet_handle():data(NULL){}
//Operations available if Supports_facet_plane is CGAL::Tag_true
  #ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(Plane_3,plane)
  #endif
//Operations available if Supports_facet_halfedge ? CGAL::Tag_true
  SWIG_CGAL_FORWARD_CALL_AND_REF_0_PTR(CGAL_Halfedge_handle<Polyhedron_base>,halfedge)
  CGAL_Halfedge_around_facet_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> > facet_begin(){return CGAL_Halfedge_around_facet_circulator<Polyhedron_base,CGAL_Halfedge_handle<Polyhedron_base> >( data->facet_begin() );}
  SWIG_CGAL_FORWARD_CALL_1_PTR(void,set_halfedge,CGAL_Halfedge_handle<Polyhedron_base>)
  SWIG_CGAL_FORWARD_CALL_0_PTR(unsigned,facet_degree)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_triangle)
  SWIG_CGAL_FORWARD_CALL_0_PTR(bool,is_quad)

  bool equals(const CGAL_Facet_handle<Polyhedron_base>& f){ return get_data()==f.get_data(); }
  int hashCode(){ return *reinterpret_cast<int*> (&*data);}

  int id(){return internal::Id<typename Polyhedron_base::Items>::get(data);}
  void set_id(int i){internal::Id<typename Polyhedron_base::Items>::set(data,i);}  
};

} //namespace SWIG_Polyhedron_3

#endif //SWIG_CGAL_POLYHEDRON_3_HANDLES_H
