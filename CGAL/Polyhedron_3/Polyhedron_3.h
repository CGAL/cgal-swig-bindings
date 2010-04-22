#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>

#include "../Kernel/Point_3.h"
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

  //~ Vertex_iterator 	P.vertices_begin ()
  //~ Vertex_iterator 	P.vertices_end ()
  //~ Halfedge_iterator P.halfedges_begin ()
  //~ Halfedge_iterator P.halfedges_end ()
  CGAL_Halfedge_iterator<Polyhedron_base> halfedges(){return CGAL_Halfedge_iterator<Polyhedron_base>(data.halfedges_begin(),data.halfedges_end());}
  
  //~ Facet_iterator    P.facets_begin ()
  //~ Facet_iterator    P.facets_end ()

  //~ Edge_iterator     P.edges_begin ()
  //~ Edge_iterator     P.edges_end ()

  //~ Point_iterator    P.points_begin ()
  //~ Point_iterator    P.points_end ()

  //~ Plane_iterator    P.planes_begin ()
  //~ Plane_iterator    P.planes_end ()

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
  //~ Halfedge_iterator 	P.border_halfedges_begin ()
  //~ Edge_iterator 	P.border_edges_begin ()
//Miscellaneous
  FORWARD_CALL_0(void,inside_out)  //bool P.normalized_border_is_valid ( bool verbose = false)
  FORWARD_CALL_0(bool,is_valid) //bool P.is_valid ( bool verbose = false, int level = 0)
  FORWARD_CALL_0(bool,normalized_border_is_valid)
  
  //~ FORWARD_CALL_1(void,delegate ( CGAL::Modifier_base<HDS>& m)

  
  
};