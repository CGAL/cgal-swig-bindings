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
};

#endif //CGAL_SWIG_POLYHEDRON_3_HANDLES_H
