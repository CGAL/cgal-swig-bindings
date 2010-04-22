#ifndef CGAL_SWIG_POLYHEDRON_3_HANDLES_H
#define CGAL_SWIG_POLYHEDRON_3_HANDLES_H

template <class Polyhedron_base>
class CGAL_Halfedge_handle{
  typename Polyhedron_base::Halfedge_handle data;
  
public:
  CGAL_Halfedge_handle():data(NULL){}
  CGAL_Halfedge_handle(typename Polyhedron_base::Halfedge_handle h):data(h){}
  typename Polyhedron_base::Halfedge_handle  get_data() const {return data;}
  typename Polyhedron_base::Halfedge_handle& get_data_ref() {return data;}
  
  
  #warning add halfedge function
};

template <class Polyhedron_base>
class CGAL_Vertex_handle{
  typename Polyhedron_base::Vertex_handle data;
  
public:
  CGAL_Vertex_handle():data(NULL){}
  CGAL_Vertex_handle(typename Polyhedron_base::Vertex_handle h):data(h){}
  typename Polyhedron_base::Vertex_handle  get_data() const {return data;}
  typename Polyhedron_base::Vertex_handle& get_data_ref() {return data;}
  
  
  #warning add vertex function
};

template <class Polyhedron_base>
class CGAL_Facet_handle{
  typename Polyhedron_base::Facet_handle data;
  
public:
  CGAL_Facet_handle():data(NULL){}
  CGAL_Facet_handle(typename Polyhedron_base::Facet_handle h):data(h){}
  typename Polyhedron_base::Facet_handle  get_data() const {return data;}
  typename Polyhedron_base::Facet_handle& get_data_ref() {return data;}
  
  
  #warning add facet function
};

#endif //CGAL_SWIG_POLYHEDRON_3_HANDLES_H
