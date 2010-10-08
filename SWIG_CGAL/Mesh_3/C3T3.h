#ifndef SWIG_CGAL_MESH_3_C3T3_H
#define SWIG_CGAL_MESH_3_C3T3_H

#include <fstream>
#include <SWIG_CGAL/Common/Input_iterator.h>
#include <SWIG_CGAL/Kernel/Point_3.h>

template <class Vertex_wrapper_base,class Index,class Surface_index,class Subdomain_index>
class Mesh_vertex_wrapper;

template <class Cell_wrapper_base,class Index,class Surface_index,class Subdomain_index>
class Mesh_cell_wrapper: public Cell_wrapper_base
{
public:
  typedef Mesh_vertex_wrapper<typename Cell_wrapper_base::Vertex_handle,Index,Surface_index,Subdomain_index>    Vertex_handle;
  typedef Mesh_cell_wrapper<Cell_wrapper_base,Index,Surface_index,Subdomain_index>                              Cell_handle;

  Mesh_cell_wrapper():Cell_wrapper_base(){}
  Mesh_cell_wrapper(const typename Cell_wrapper_base::cpp_base base):Cell_wrapper_base(base){}

  FORWARD_CALL_0(Subdomain_index,subdomain_index)
  FORWARD_CALL_1(void,set_subdomain_index,Subdomain_index)
  FORWARD_CALL_1(bool,is_facet_on_surface,int)
  FORWARD_CALL_2(void,set_facet_on_surface,int,Surface_index)
  FORWARD_CALL_1(bool,is_facet_visited,int)
  FORWARD_CALL_2(void,set_facet_visited,int,bool)
  FORWARD_CALL_1(Point_3,facet_surface_center,int)
  FORWARD_CALL_2(void,set_facet_surface_center,int,Point_3)
//Overloaded method to get correct type
  FORWARD_CALL_1_PTR(Cell_handle,neighbor,int)
  FORWARD_CALL_1_PTR(Vertex_handle,vertex,int)
};

template <class Vertex_wrapper_base,class Index,class Surface_index,class Subdomain_index>
class Mesh_vertex_wrapper : public Vertex_wrapper_base
{
public:
  typedef Mesh_cell_wrapper<typename Vertex_wrapper_base::Cell_handle,Index,Surface_index,Subdomain_index> Cell_handle;

  Mesh_vertex_wrapper():Vertex_wrapper_base(){}
  Mesh_vertex_wrapper(const typename Vertex_wrapper_base::cpp_base base):Vertex_wrapper_base(base){}

  FORWARD_CALL_0(int,in_dimension)
  FORWARD_CALL_1(void,set_dimension,int)
  FORWARD_CALL_0(Index,index)
  FORWARD_CALL_1(void,set_index,Index)
//Internal
  FORWARD_CALL_0(double,meshing_info)
  FORWARD_CALL_1(void,set_meshing_info,double) 
//Overloaded method to get correct type
  FORWARD_CALL_0_PTR(Cell_handle,cell)
};



template <class C3T3,class Triangulation,class Index,class Surface_index,class Subdomain_index>
class C3T3_wrapper{
  C3T3 data;
  Triangulation triangulation_wrapper_ref;
public:
  typedef C3T3 cpp_base;
  typedef C3T3_wrapper<C3T3,Triangulation,Index,Surface_index,Subdomain_index> Self;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}
  
  typedef typename Triangulation::Edge Edge;
  typedef typename Triangulation::Facet Facet;
  typedef typename Triangulation::Vertex_handle Vertex_handle;
  typedef typename Triangulation::Cell_handle Cell_handle;

  typedef CGAL_Cell_iterator<C3T3,Cell_handle>               Cell_iterator;
  typedef CGAL_Facet_iterator<C3T3,Facet>                    Facet_iterator;  
  
//Creation  
  C3T3_wrapper(){}
  C3T3_wrapper(const C3T3& data_):data(data_){}
  void swap(Self& other){data.swap(other.get_data_ref());}
//Access Functions
  FORWARD_CALL_0(Triangulation,triangulation)
//Non const access
  Triangulation&  triangulation_ref(){
    triangulation_wrapper_ref=Triangulation(data.triangulation());
    return triangulation_wrapper_ref;
  }
//Modifiers
  FORWARD_CALL_2(void,add_to_complex,Cell_handle,Subdomain_index)
  FORWARD_CALL_2(void,add_to_complex,Facet,Surface_index)
  FORWARD_CALL_3(void,add_to_complex,Cell_handle,int,Surface_index)
  FORWARD_CALL_1(void,remove_from_complex,Cell_handle)
  FORWARD_CALL_1(void,remove_from_complex,Facet)
  FORWARD_CALL_2(void,remove_from_complex,Cell_handle,int)
  FORWARD_CALL_2(void,set_subdomain_index,Cell_handle,Subdomain_index)
  FORWARD_CALL_2(void,set_surface_index,Facet,Surface_index)
  FORWARD_CALL_3(void,set_surface_index,Cell_handle,int,Surface_index)
//  FORWARD_CALL_2(void,set_index,Vertex_handle,Index)
  FORWARD_CALL_2(void,set_dimension,Vertex_handle,int)
//Queries
  FORWARD_CALL_0(int,number_of_cells)
  FORWARD_CALL_0(int,number_of_facets)
  FORWARD_CALL_1(bool,is_in_complex,Cell_handle)
  FORWARD_CALL_1(bool,is_in_complex,Facet)
  FORWARD_CALL_2(bool,is_in_complex,Cell_handle,int)
  FORWARD_CALL_1(Subdomain_index,subdomain_index,Cell_handle)
  FORWARD_CALL_1(Surface_index,surface_index,Facet)
  FORWARD_CALL_2(Surface_index,surface_index,Cell_handle,int)
  FORWARD_CALL_1(int,in_dimension,Vertex_handle)
//  FORWARD_CALL_1(Index,index,Vertex_handle)
//Traversal of the complex
  Cell_iterator  cells() {return Cell_iterator(data.cells_begin(),data.cells_end());}
  Facet_iterator facets(){return Facet_iterator(data.facets_begin(),data.facets_end());}
//Operations
  void output_to_medit (const char* filename){
    std::ofstream outfile(filename);
    if (!outfile) std::cerr << "Error cannot create file: " << filename << std::endl;
    else  data.output_to_medit(outfile);
  }
};

#endif //SWIG_CGAL_MESH_3_C3T3_H

