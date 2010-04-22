#ifndef CGAL_SWIG_POLYHEDRON_3_HANDLES_H
#define CGAL_SWIG_POLYHEDRON_3_HANDLES_H

#include "../Common/Macros.h"

template <class T> class CGAL_Halfedge_around_vertex_circulator;
template <class T> class CGAL_Halfedge_around_facet_circulator;

template <class Polyhedron_base>
class CGAL_Vertex_handle;

template <class Polyhedron_base>
class CGAL_Facet_handle;
  
template <class Polyhedron_base>
class CGAL_Halfedge_handle{
  typename Polyhedron_base::Halfedge_handle data;
  
public:
  typedef typename Polyhedron_base::Halfedge_handle cpp_base;

  CGAL_Halfedge_handle():data(NULL){}
  CGAL_Halfedge_handle(typename Polyhedron_base::Halfedge_handle h):data(h){}
  typename Polyhedron_base::Halfedge_handle  get_data() const {return data;}
  typename Polyhedron_base::Halfedge_handle& get_data_ref() {return data;}
//Operations
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle,opposite)
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle,next)
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle,prev)
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle,next_on_vertex)
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle,prev_on_vertex)
  FORWARD_CALL_0_PTR(bool,is_border)
  FORWARD_CALL_0_PTR(bool,is_border_edge)

  CGAL_Halfedge_around_vertex_circulator<Polyhedron_base> vertex_begin(){return CGAL_Halfedge_around_vertex_circulator<Polyhedron_base>( data->vertex_begin() );}
  CGAL_Halfedge_around_facet_circulator<Polyhedron_base> facet_begin(){return CGAL_Halfedge_around_facet_circulator<Polyhedron_base>( data->facet_begin() );}
  
  FORWARD_CALL_0_PTR(unsigned,vertex_degree)
  FORWARD_CALL_0_PTR(bool,is_bivalent)
  FORWARD_CALL_0_PTR(bool,is_trivalent)

  FORWARD_CALL_0_PTR(unsigned,facet_degree)
  FORWARD_CALL_0_PTR(bool,is_triangle)
  FORWARD_CALL_0_PTR(bool,is_quad)

//Operations available if Supports_halfedge_vertex is CGAL::Tag_true
  FORWARD_CALL_0_PTR(CGAL_Vertex_handle<Polyhedron_base>,vertex)
//Operations available if Supports_halfedge_facet is CGAL::Tag_true
  FORWARD_CALL_0_PTR(CGAL_Facet_handle<Polyhedron_base>,facet)
};

template <class Polyhedron_base>
class CGAL_Vertex_handle{
  typename Polyhedron_base::Vertex_handle data;
  
public:
  typedef typename Polyhedron_base::Vertex_handle cpp_base;

  CGAL_Vertex_handle():data(NULL){}
  CGAL_Vertex_handle(typename Polyhedron_base::Vertex_handle h):data(h){}

  typename Polyhedron_base::Vertex_handle  get_data() const {return data;}
  typename Polyhedron_base::Vertex_handle& get_data_ref() {return data;}
//Operations available if Supports_vertex_point is CGAL::Tag_true
  FORWARD_CALL_0_PTR(Point_3,point)
//Operations available if Supports_vertex_halfedge is CGAL::Tag_true
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle<Polyhedron_base>,halfedge)
  CGAL_Halfedge_around_vertex_circulator<Polyhedron_base> vertex_begin(){return CGAL_Halfedge_around_vertex_circulator<Polyhedron_base>( data->vertex_begin() );}
  FORWARD_CALL_1_PTR(void,set_halfedge,CGAL_Halfedge_handle<Polyhedron_base>)
  FORWARD_CALL_0_PTR(unsigned,vertex_degree)
  FORWARD_CALL_0_PTR(bool,is_bivalent)
  FORWARD_CALL_0_PTR(bool,is_trivalent)
    
};

template <class Polyhedron_base>
class CGAL_Facet_handle{
  typename Polyhedron_base::Facet_handle data;
  
public:
  typename Polyhedron_base::Facet_handle cpp_base;

  CGAL_Facet_handle():data(NULL){}
  CGAL_Facet_handle(typename Polyhedron_base::Facet_handle h):data(h){}
  typename Polyhedron_base::Facet_handle  get_data() const {return data;}
  typename Polyhedron_base::Facet_handle& get_data_ref() {return data;}
//Operations available if Supports_facet_plane is CGAL::Tag_true
  FORWARD_CALL_0_PTR(Plane_3,plane)
//Operations available if Supports_facet_halfedge ? CGAL::Tag_true
  FORWARD_CALL_0_PTR(CGAL_Halfedge_handle<Polyhedron_base>,halfedge)
  CGAL_Halfedge_around_facet_circulator<Polyhedron_base> facet_begin(){return CGAL_Halfedge_around_facet_circulator<Polyhedron_base>( data->facet_begin() );}
  FORWARD_CALL_1_PTR(void,set_halfedge,CGAL_Halfedge_handle<Polyhedron_base>)
  FORWARD_CALL_0_PTR(unsigned,facet_degree)
  FORWARD_CALL_0_PTR(bool,is_triangle)
  FORWARD_CALL_0_PTR(bool,is_quad)
  
};

#endif //CGAL_SWIG_POLYHEDRON_3_HANDLES_H
