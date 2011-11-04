#ifndef SWIG_CGAL_MESH_3_MESH_DOMAINS_H
#define SWIG_CGAL_MESH_3_MESH_DOMAINS_H

template <class Base,class Polyhedron_base,class Index,class Surface_index,class Subdomain_index>
class Polyhedral_mesh_domain_3_wrapper
{
  Base data;
public:
  #ifndef SWIG
  typedef Base cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}
  #endif
  
//Polyhedral_mesh_domain_3_wrapper(const cpp_base& base):data(base){} commented because requires copy cstr which is private
  Polyhedral_mesh_domain_3_wrapper(const Polyhedron_base& poly):data(poly.get_data()){}

  SWIG_CGAL_FORWARD_CALL_1(Index,index_from_surface_index,Surface_index)
  SWIG_CGAL_FORWARD_CALL_1(Index,index_from_subdomain_index,Subdomain_index)
  SWIG_CGAL_FORWARD_CALL_1(Surface_index,surface_index,Index)
  SWIG_CGAL_FORWARD_CALL_1(Subdomain_index,subdomain_index,Index)
};

#endif // SWIG_CGAL_MESH_3_MESH_DOMAINS_H


