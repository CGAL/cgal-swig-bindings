// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POLYHEDRON_3_POLYHEDRON_3_H
#define SWIG_CGAL_POLYHEDRON_3_POLYHEDRON_3_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <fstream>


#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <SWIG_CGAL/Polyhedron_3/Modifier_base.h>
#include <SWIG_CGAL/Polyhedron_3/general_modifier.h>
#include <boost/shared_ptr.hpp>

template <class Polyhedron_base,class Vertex_handle,class Halfedge_handle,class Facet_handle>
class Polyhedron_3_wrapper{
  boost::shared_ptr<Polyhedron_base> data_sptr;
 
public:
  #ifndef SWIG
  typedef Polyhedron_base cpp_base;
  const cpp_base& get_data() const {return *data_sptr;}
        cpp_base& get_data()       {return *data_sptr;}
  boost::shared_ptr<cpp_base> shared_ptr() {return data_sptr;}      
  Polyhedron_3_wrapper(const cpp_base& base):data_sptr(new cpp_base(base)){}
  #endif
  
  typedef SWIG_CGAL_Iterator<typename Polyhedron_base::Vertex_iterator,Vertex_handle>     Vertex_iterator;
  typedef SWIG_CGAL_Iterator<typename Polyhedron_base::Halfedge_iterator,Halfedge_handle> Halfedge_iterator;
  typedef SWIG_CGAL_Iterator<typename Polyhedron_base::Facet_iterator,Facet_handle>       Facet_iterator;
  typedef SWIG_CGAL_Iterator<typename Polyhedron_base::Edge_iterator,Halfedge_handle>     Edge_iterator;
  typedef SWIG_CGAL_Iterator<typename Polyhedron_base::Point_iterator,Point_3>            Point_iterator;
  #ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
  typedef SWIG_CGAL_Iterator<typename Polyhedron_base::Plane_iterator,Plane_3>            Plane_iterator;
  #endif    
    
//Creation
  Polyhedron_3_wrapper():data_sptr(new cpp_base()){}
  Polyhedron_3_wrapper(const char* off_filename):data_sptr(new cpp_base()){
    std::ifstream file(off_filename);
    if (!file) std::cerr << "Error cannot open file: " << off_filename << std::endl;
    else{
      file >> get_data();
      file.close();
    }
  }
  Polyhedron_3_wrapper(unsigned v, unsigned h, unsigned f):data_sptr(new cpp_base(v,h,f)){}
  SWIG_CGAL_FORWARD_CALL_3(void,reserve,unsigned,unsigned,unsigned)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Halfedge_handle,make_tetrahedron)
  SWIG_CGAL_FORWARD_CALL_AND_REF_4(Halfedge_handle,make_tetrahedron,Point_3,Point_3,Point_3,Point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Halfedge_handle,make_triangle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Halfedge_handle,make_triangle,Point_3,Point_3,Point_3)
//Access Member Functions
  SWIG_CGAL_FORWARD_CALL_0(bool,empty)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,size_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,size_of_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,size_of_facets)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,capacity_of_vertices)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,capacity_of_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,capacity_of_facets)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,bytes)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,bytes_reserved)
//Iterators
  Vertex_iterator vertices()     {return Vertex_iterator(get_data().vertices_begin(),get_data().vertices_end());}
  Halfedge_iterator halfedges(){return Halfedge_iterator(get_data().halfedges_begin(),get_data().halfedges_end());}
  Facet_iterator facets()         {return Facet_iterator(get_data().facets_begin(),get_data().facets_end());}
  Edge_iterator edges()        {return Edge_iterator(get_data().edges_begin(),get_data().edges_end());}
  Point_iterator points()              {return Point_iterator(get_data().points_begin(),get_data().points_end());}
  #ifdef SWIG_CGAL_FACET_SUPPORTS_PLANE
  Plane_iterator planes()              {return Plane_iterator(get_data().planes_begin(),get_data().planes_end());}
  #endif
//Combinatorial Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_closed)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_pure_bivalent)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_pure_trivalent)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_pure_triangle)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_pure_quad)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_triangle,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_tetrahedron,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Halfedge_handle,split_facet,Halfedge_handle,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,join_facet,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Halfedge_handle,split_vertex,Halfedge_handle,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,join_vertex,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,split_edge,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,flip_edge,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,create_center_vertex,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,erase_center_vertex,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Halfedge_handle,split_loop,Halfedge_handle,Halfedge_handle,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Halfedge_handle,join_loop,Halfedge_handle,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,make_hole,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Halfedge_handle,fill_hole,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Halfedge_handle,add_vertex_and_facet_to_border,Halfedge_handle,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Halfedge_handle,add_facet_to_border,Halfedge_handle,Halfedge_handle)

  SWIG_CGAL_FORWARD_CALL_1(void,erase_facet,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_1(void,erase_connected_component,Halfedge_handle)
  SWIG_CGAL_FORWARD_CALL_1(unsigned,keep_largest_connected_components,unsigned)
  SWIG_CGAL_FORWARD_CALL_0(void,clear)

//Operations with Border Halfedges
  SWIG_CGAL_FORWARD_CALL_0(void,normalize_border)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,size_of_border_halfedges)
  SWIG_CGAL_FORWARD_CALL_0(unsigned,size_of_border_edges)
  Halfedge_iterator   border_halfedges()      {return Halfedge_iterator(get_data().border_halfedges_begin(),get_data().halfedges_end());}
  Halfedge_iterator   non_border_halfedges()  {return Halfedge_iterator(get_data().halfedges_begin(),get_data().border_halfedges_begin());}      
  Edge_iterator       border_edges()          {return Edge_iterator(get_data().border_edges_begin(),get_data().edges_end());}
  Edge_iterator       non_border_edges()      {return Edge_iterator(get_data().edges_begin(),get_data().border_edges_begin());}
  
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(void,inside_out)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_valid) //bool P.is_valid ( bool verbose = false, int level = 0)
  SWIG_CGAL_FORWARD_CALL_0(bool,normalized_border_is_valid)  //bool P.normalized_border_is_valid ( bool verbose = false)
  void delegate(Modifier_base<Polyhedron_base> modifier){get_data().delegate(modifier.get_data());}
  void delegate(General_modifier<typename Polyhedron_base::HalfedgeDS> modifier){get_data().delegate(modifier);}
  void write_to_file(const char* off_filename, int prec=5) const
  {
    std::ofstream file(off_filename);
    if (!off_filename) std::cerr << "Error cannot create file: " << off_filename << std::endl;    
    else{
      file << std::setprecision(prec) << get_data();
      file.close();
    }
  }
//Deep copy
  typedef Polyhedron_3_wrapper<Polyhedron_base,Vertex_handle,Halfedge_handle,Facet_handle> Self;
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
};

#endif //SWIG_CGAL_POLYHEDRON_3_POLYHEDRON_3_H
