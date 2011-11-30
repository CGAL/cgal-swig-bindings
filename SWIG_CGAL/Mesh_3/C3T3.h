// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_3_C3T3_H
#define SWIG_CGAL_MESH_3_C3T3_H

#include <fstream>
#include <iostream>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <boost/shared_ptr.hpp>

template <class C3T3,class Triangulation,class Index,class Surface_index,class Subdomain_index>
class C3T3_wrapper{
  boost::shared_ptr<C3T3> data_sptr;
public:
  #ifndef SWIG
  typedef C3T3 cpp_base;
  const cpp_base& get_data() const {return *data_sptr;}
        cpp_base& get_data()       {return *data_sptr;}
  C3T3_wrapper(const cpp_base& data_):data_sptr(new C3T3(data_)){}
  #endif
  
  typedef C3T3_wrapper<C3T3,Triangulation,Index,Surface_index,Subdomain_index> Self;
    
  typedef typename Triangulation::Edge Edge;
  typedef typename Triangulation::Facet Facet;
  typedef typename Triangulation::Vertex_handle Vertex_handle;
  typedef typename Triangulation::Cell_handle Cell_handle;

  typedef SWIG_CGAL_Iterator<typename C3T3::Cell_iterator,Cell_handle>               Cell_iterator;
  typedef SWIG_CGAL_Iterator<typename C3T3::Facet_iterator,Facet>                    Facet_iterator;  
  
//Creation  
  C3T3_wrapper():data_sptr(new cpp_base()){}
  void swap(Self& other){get_data().swap(other.get_data());}
//Access Functions
  Triangulation triangulation() 
  {
    //the underlying triangulation is not copied, it's a reference.
    //Since the reference is ref. counted underlying cpp triangulation is valid
    //even if C3T3 is deleted
    return Triangulation(&(data_sptr->triangulation()),data_sptr);
  }

  void triangulation(Triangulation& ref)
  {ref = Triangulation(&(data_sptr->triangulation()),data_sptr);}

//Modifiers
  SWIG_CGAL_FORWARD_CALL_2(void,add_to_complex,Cell_handle,Subdomain_index)
  SWIG_CGAL_FORWARD_CALL_2(void,add_to_complex,Facet,Surface_index)
  SWIG_CGAL_FORWARD_CALL_3(void,add_to_complex,Cell_handle,int,Surface_index)
  SWIG_CGAL_FORWARD_CALL_1(void,remove_from_complex,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1(void,remove_from_complex,Facet)
  SWIG_CGAL_FORWARD_CALL_2(void,remove_from_complex,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_2(void,set_subdomain_index,Cell_handle,Subdomain_index)
  SWIG_CGAL_FORWARD_CALL_2(void,set_surface_index,Facet,Surface_index)
  SWIG_CGAL_FORWARD_CALL_3(void,set_surface_index,Cell_handle,int,Surface_index)
  SWIG_CGAL_FORWARD_CALL_2(void,set_index,Vertex_handle,Index)
  SWIG_CGAL_FORWARD_CALL_2(void,set_dimension,Vertex_handle,int)
//Queries
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_cells)
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_facets)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_in_complex,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_in_complex,Facet)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_in_complex,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(Subdomain_index,subdomain_index,Cell_handle)
  SWIG_CGAL_FORWARD_CALL_1(Surface_index,surface_index,Facet)
  SWIG_CGAL_FORWARD_CALL_2(Surface_index,surface_index,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(int,in_dimension,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(Index,index,Vertex_handle)
//Traversal of the complex
  Cell_iterator  cells() {return Cell_iterator(get_data().cells_begin(),get_data().cells_end());}
  Facet_iterator facets(){return Facet_iterator(get_data().facets_begin(),get_data().facets_end());}
//Operations
  void output_to_medit (const char* filename){
    std::ofstream outfile(filename);
    if (!outfile) std::cerr << "Error cannot create file: " << filename << std::endl;
    else  get_data().output_to_medit(outfile);
  }
//Deep copy
  Self deepcopy() const {return Self(get_data());}
  void deepcopy(const Self& other){data_sptr=boost::shared_ptr<cpp_base>( new cpp_base(other.get_data()) );}
//Special for SWIG
  bool same_internal_object(const Self& other) {return other.data_sptr.get()==data_sptr.get();}
};

#endif //SWIG_CGAL_MESH_3_C3T3_H

