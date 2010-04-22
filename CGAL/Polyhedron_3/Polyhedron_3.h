#ifndef CGAL_SWIG_POLYHEDRON_3_POLYHEDRON_3_H
#define CGAL_SWIG_POLYHEDRON_3_POLYHEDRON_3_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>

#include "../Kernel/typedefs.h"
#include "../Common/Macros.h"
#include "polyhedron_3_iterators.h"

typedef CGAL::Polyhedron_3<EPIC_Kernel>         Polyhedron;


template <class Polyhedron_base,class Halfedge_handle>
class Polyhedron_3{
  Polyhedron_base data;
  typename Polyhedron_base::Halfedge_handle convert (Halfedge_handle h) {return h.get_data();}
  typename Polyhedron_base::Traits::Point_3 convert (const Point_3& p){return p.get_data();}
  const unsigned& convert (const unsigned& i){return i;}
  
public:  
//Creation
  Polyhedron_3():data(){}
  //Polyhedron_3<Traits> P ( Traits traits = Traits());
  //Polyhedron_3<Traits> P ( size_type v, size_type h, size_type f, Traits traits = Traits());
  //~ IMPORT FROM OFF
  FORWARD_CALL_3(void,reserve,unsigned,unsigned,unsigned)
  FORWARD_CALL_0(Halfedge_handle,make_tetrahedron)
  FORWARD_CALL_4(Halfedge_handle,make_tetrahedron,Point_3,Point_3,Point_3,Point_3)
  FORWARD_CALL_0(Halfedge_handle,make_triangle)
  FORWARD_CALL_3(Halfedge_handle,make_triangle,Point_3,Point_3,Point_3)
    
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

  CGAL_Vertex_iterator<Polyhedron_base> vertices(){return CGAL_Vertex_iterator<Polyhedron_base>(data.vertices_begin(),data.vertices_end());}
  CGAL_Halfedge_iterator<Polyhedron_base> halfedges(){return CGAL_Halfedge_iterator<Polyhedron_base>(data.halfedges_begin(),data.halfedges_end());}
  CGAL_Facet_iterator<Polyhedron_base> facets(){return CGAL_Facet_iterator<Polyhedron_base>(data.facets_begin(),data.facets_end());}
  CGAL_Edge_iterator<Polyhedron_base> edges(){return CGAL_Edge_iterator<Polyhedron_base>(data.edges_begin(),data.edges_end());}
  CGAL_Point_iterator<Polyhedron_base> points(){return CGAL_Point_iterator<Polyhedron_base>(data.points_begin(),data.points_end());}
  CGAL_Plane_iterator<Polyhedron_base> planes(){return CGAL_Plane_iterator<Polyhedron_base>(data.planes_begin(),data.planes_end());}

  //Traits P.traits ()

//Combinatorial Predicates
  FORWARD_CALL_0(bool,is_closed)
  FORWARD_CALL_0(bool,is_pure_bivalent)
  FORWARD_CALL_0(bool,is_pure_trivalent)
  FORWARD_CALL_0(bool,is_pure_triangle)
  FORWARD_CALL_0(bool,is_pure_quad)
  FORWARD_CALL_1(bool,is_triangle,Halfedge_handle)
  FORWARD_CALL_1(bool,is_tetrahedron,Halfedge_handle)

  FORWARD_CALL_2(Halfedge_handle,split_facet,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_1(Halfedge_handle,join_facet,Halfedge_handle)

  FORWARD_CALL_2(Halfedge_handle,split_vertex,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_1(Halfedge_handle,join_vertex,Halfedge_handle)
  FORWARD_CALL_1(Halfedge_handle,split_edge,Halfedge_handle)
  FORWARD_CALL_1(Halfedge_handle,flip_edge,Halfedge_handle)


  FORWARD_CALL_1(Halfedge_handle,create_center_vertex,Halfedge_handle)
  FORWARD_CALL_1(Halfedge_handle,erase_center_vertex,Halfedge_handle)

  FORWARD_CALL_3(Halfedge_handle,split_loop,Halfedge_handle,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_2(Halfedge_handle,join_loop,Halfedge_handle,Halfedge_handle)


  FORWARD_CALL_1(Halfedge_handle,make_hole,Halfedge_handle)
  FORWARD_CALL_1(Halfedge_handle,fill_hole,Halfedge_handle)


  FORWARD_CALL_2(Halfedge_handle,add_vertex_and_facet_to_border,Halfedge_handle,Halfedge_handle)
  FORWARD_CALL_2(Halfedge_handle,add_facet_to_border,Halfedge_handle,Halfedge_handle)

  FORWARD_CALL_1(void,erase_facet,Halfedge_handle)
  FORWARD_CALL_1(void,erase_connected_component,Halfedge_handle)
  FORWARD_CALL_1(unsigned,keep_largest_connected_components,unsigned)
  FORWARD_CALL_0(void,clear)

//Operations with Border Halfedges
  FORWARD_CALL_0(void,normalize_border)
  FORWARD_CALL_0(unsigned,size_of_border_halfedges)
  FORWARD_CALL_0(unsigned,size_of_border_edges)
  CGAL_Halfedge_iterator<Polyhedron_base>   border_halfedges()      {return CGAL_Halfedge_iterator<Polyhedron_base>(data.border_halfedges_begin(),data.halfedges_end());}
  CGAL_Halfedge_iterator<Polyhedron_base>   non_border_halfedges()  {return CGAL_Halfedge_iterator<Polyhedron_base>(data.halfedges_begin(),data.border_halfedges_begin());}      
  CGAL_Edge_iterator<Polyhedron_base>   border_edges()      {return CGAL_Edge_iterator<Polyhedron_base>(data.border_edges_begin(),data.edges_end());}
  CGAL_Edge_iterator<Polyhedron_base>   non_border_edges()  {return CGAL_Edge_iterator<Polyhedron_base>(data.edges_begin(),data.border_edges_begin());}
  
//Miscellaneous
  FORWARD_CALL_0(void,inside_out)
  FORWARD_CALL_0(bool,is_valid) //bool P.is_valid ( bool verbose = false, int level = 0)
  FORWARD_CALL_0(bool,normalized_border_is_valid)  //bool P.normalized_border_is_valid ( bool verbose = false)
  
  //~ FORWARD_CALL_1(void,delegate ( CGAL::Modifier_base<HDS>& m)

  
  
};

#endif //CGAL_SWIG_POLYHEDRON_3_POLYHEDRON_3_H
