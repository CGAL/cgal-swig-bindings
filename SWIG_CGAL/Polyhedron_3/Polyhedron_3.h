#ifndef CGAL_SWIG_POLYHEDRON_3_POLYHEDRON_3_H
#define CGAL_SWIG_POLYHEDRON_3_POLYHEDRON_3_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <fstream>

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Polyhedron_3/polyhedron_3_iterators.h>
#include <SWIG_CGAL/Polyhedron_3/Modifier_base.h>

template <class Polyhedron_base,class Vertex_handle,class Halfedge_handle,class Facet_handle>
class Polyhedron_3_wrapper{
  Polyhedron_base data;
 
public:
  #ifndef SWIG
  typedef Polyhedron_base cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref(){return data;}
  Polyhedron_3_wrapper(const cpp_base& base):data(base){}
  #endif
  
//Creation
  Polyhedron_3_wrapper():data(){}
  Polyhedron_3_wrapper(const char* off_filename){
    std::ifstream file(off_filename);
    file >> data;
    file.close();
  }
  //Polyhedron_3_wrapper<Traits> P ( Traits traits = Traits());
  //Polyhedron_3_wrapper<Traits> P ( size_type v, size_type h, size_type f, Traits traits = Traits());
  FORWARD_CALL_3(void,reserve,unsigned,unsigned,unsigned)
  FORWARD_CALL_AND_REF_0(Halfedge_handle,make_tetrahedron)
  FORWARD_CALL_AND_REF_4(Halfedge_handle,make_tetrahedron,Point_3,Point_3,Point_3,Point_3)
  FORWARD_CALL_AND_REF_0(Halfedge_handle,make_triangle)
  FORWARD_CALL_AND_REF_3(Halfedge_handle,make_triangle,Point_3,Point_3,Point_3)
    
//Access Member Functions
  FORWARD_CALL_0(bool,empty)
  FORWARD_CALL_0(unsigned,size_of_vertices)
  FORWARD_CALL_0(unsigned,size_of_halfedges)
  FORWARD_CALL_0(unsigned,size_of_facets)
  FORWARD_CALL_0(unsigned,capacity_of_vertices)
  FORWARD_CALL_0(unsigned,capacity_of_halfedges)
  FORWARD_CALL_0(unsigned,capacity_of_facets)
  FORWARD_CALL_0(unsigned,bytes)
  FORWARD_CALL_0(unsigned,bytes_reserved)

  //allocator_type P.get_allocator ()

  CGAL_Vertex_iterator<Polyhedron_base,Vertex_handle> vertices()     {return CGAL_Vertex_iterator<Polyhedron_base,Vertex_handle>(data.vertices_begin(),data.vertices_end());}
  CGAL_Halfedge_iterator<Polyhedron_base,Halfedge_handle> halfedges(){return CGAL_Halfedge_iterator<Polyhedron_base,Halfedge_handle>(data.halfedges_begin(),data.halfedges_end());}
  CGAL_Facet_iterator<Polyhedron_base,Facet_handle> facets()         {return CGAL_Facet_iterator<Polyhedron_base,Facet_handle>(data.facets_begin(),data.facets_end());}
  CGAL_Edge_iterator<Polyhedron_base,Halfedge_handle> edges()        {return CGAL_Edge_iterator<Polyhedron_base,Halfedge_handle>(data.edges_begin(),data.edges_end());}
  CGAL_Point_iterator<Polyhedron_base,Point_3> points()              {return CGAL_Point_iterator<Polyhedron_base,Point_3>(data.points_begin(),data.points_end());}
  #ifdef CGAL_SWIG_FACET_SUPPORTS_PLANE
  CGAL_Plane_iterator<Polyhedron_base,Plane_3> planes()              {return CGAL_Plane_iterator<Polyhedron_base,Plane_3>(data.planes_begin(),data.planes_end());}
  #endif
  
  //Traits P.traits ()

//Combinatorial Predicates
  FORWARD_CALL_0(bool,is_closed)
  FORWARD_CALL_0(bool,is_pure_bivalent)
  FORWARD_CALL_0(bool,is_pure_trivalent)
  FORWARD_CALL_0(bool,is_pure_triangle)
  FORWARD_CALL_0(bool,is_pure_quad)
  FORWARD_CALL_1(bool,is_triangle,Halfedge_handle)
  FORWARD_CALL_1(bool,is_tetrahedron,Halfedge_handle)

  FORWARD_CALL_AND_REF_2(Halfedge_handle,split_facet,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_AND_REF_1(Halfedge_handle,join_facet,Halfedge_handle)

  FORWARD_CALL_AND_REF_2(Halfedge_handle,split_vertex,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_AND_REF_1(Halfedge_handle,join_vertex,Halfedge_handle)
  FORWARD_CALL_AND_REF_1(Halfedge_handle,split_edge,Halfedge_handle)
  FORWARD_CALL_AND_REF_1(Halfedge_handle,flip_edge,Halfedge_handle)


  FORWARD_CALL_AND_REF_1(Halfedge_handle,create_center_vertex,Halfedge_handle)
  FORWARD_CALL_AND_REF_1(Halfedge_handle,erase_center_vertex,Halfedge_handle)

  FORWARD_CALL_AND_REF_3(Halfedge_handle,split_loop,Halfedge_handle,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_AND_REF_2(Halfedge_handle,join_loop,Halfedge_handle,Halfedge_handle)


  FORWARD_CALL_AND_REF_1(Halfedge_handle,make_hole,Halfedge_handle)
  FORWARD_CALL_AND_REF_1(Halfedge_handle,fill_hole,Halfedge_handle)


  FORWARD_CALL_AND_REF_2(Halfedge_handle,add_vertex_and_facet_to_border,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_AND_REF_2(Halfedge_handle,add_facet_to_border,Halfedge_handle,Halfedge_handle)

  FORWARD_CALL_1(void,erase_facet,Halfedge_handle)
  FORWARD_CALL_1(void,erase_connected_component,Halfedge_handle)
  FORWARD_CALL_1(unsigned,keep_largest_connected_components,unsigned)
  FORWARD_CALL_0(void,clear)

//Operations with Border Halfedges
  FORWARD_CALL_0(void,normalize_border)
  FORWARD_CALL_0(unsigned,size_of_border_halfedges)
  FORWARD_CALL_0(unsigned,size_of_border_edges)
  CGAL_Halfedge_iterator<Polyhedron_base,Halfedge_handle>   border_halfedges()      {return CGAL_Halfedge_iterator<Polyhedron_base,Halfedge_handle>(data.border_halfedges_begin(),data.halfedges_end());}
  CGAL_Halfedge_iterator<Polyhedron_base,Halfedge_handle>   non_border_halfedges()  {return CGAL_Halfedge_iterator<Polyhedron_base,Halfedge_handle>(data.halfedges_begin(),data.border_halfedges_begin());}      
  CGAL_Edge_iterator<Polyhedron_base,Halfedge_handle>       border_edges()          {return CGAL_Edge_iterator<Polyhedron_base,Halfedge_handle>(data.border_edges_begin(),data.edges_end());}
  CGAL_Edge_iterator<Polyhedron_base,Halfedge_handle>       non_border_edges()      {return CGAL_Edge_iterator<Polyhedron_base,Halfedge_handle>(data.edges_begin(),data.border_edges_begin());}
  
//Miscellaneous
  FORWARD_CALL_0(void,inside_out)
  FORWARD_CALL_0(bool,is_valid) //bool P.is_valid ( bool verbose = false, int level = 0)
  FORWARD_CALL_0(bool,normalized_border_is_valid)  //bool P.normalized_border_is_valid ( bool verbose = false)
  void delegate(Modifier_base<Polyhedron_base> modifier){data.delegate(modifier.get_data());}
  void write_to_file(const char* off_filename) const
  {
    std::ofstream file(off_filename);
    file << data;
    file.close();    
  }
};

#endif //CGAL_SWIG_POLYHEDRON_3_POLYHEDRON_3_H
