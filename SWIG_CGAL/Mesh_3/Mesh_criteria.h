#ifndef SWIG_CGAL_MESH_3_MESH_CRITERIA_H
#define SWIG_CGAL_MESH_3_MESH_CRITERIA_H

#include <CGAL/Mesh_criteria_3.h>

//default mesh criteria
template <class Base>
class Default_mesh_criteria_wrapper
{
  Base data;
public:
#ifndef SWIG
  typedef Base cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref(){return data;}
#endif
  
  Default_mesh_criteria_wrapper(  double facet_angle=0,
                                  double facet_size=0,
                                  double facet_distance=0,
                                  double cell_radius_edge=0,
                                  double cell_size=0)
  :data(facet_angle,facet_size,facet_distance,cell_radius_edge,cell_size){}
};

template <class Base, class Field1, class Field2, class Field3, class Field4>
class Mesh_criteria_with_fields_wrapper
{
  Base data;
public:
#ifndef SWIG
  typedef Base cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref(){return data;}
#endif
  
  Mesh_criteria_with_fields_wrapper(  double facet_angle=0,
                                      double facet_size=0,
                                      double facet_distance=0,
                                      double cell_radius_edge=0,
                                      double cell_size=0)
  :data(facet_angle,facet_size,facet_distance,cell_radius_edge,cell_size){}
    
    
  Mesh_criteria_with_fields_wrapper(  Field1 edge_size,
                                      double facet_angle,
                                      Field2 facet_size,
                                      //Field3 facet_distance,
                                      double facet_distance,
                                      double cell_radius_edge_ratio,
                                      Field4 cell_size
//                                    ,Mesh_facet_topology parameters::facet_topology
  ) :data(  CGAL::parameters::edge_sizing_field = edge_size.get_data(),
            CGAL::parameters::facet_angle = facet_angle,
            CGAL::parameters::facet_sizing_field = facet_size.get_data(),
            CGAL::parameters::facet_distance = facet_distance,
            //Mesh_facet_topology parameters::facet_topology = CGAL::FACET_VERTICES_ON_SURFACE,
            CGAL::parameters::cell_radius_edge_ratio = cell_radius_edge_ratio,
            CGAL::parameters::cell_sizing_field = cell_size.get_data()
    ){}
};



#ifdef SWIGJAVA
//User defined test
template <class Triangulation,class Caller>
class Java_cell_criteria{
  Caller caller;
public:
  typedef typename Triangulation::Cell_handle Cell_handle;
  typedef std::pair<int,double> Cell_quality;
  typedef boost::optional<Cell_quality> Cell_badness;
  
  Java_cell_criteria(Caller& call):caller(call){}
  Cell_badness operator()(Cell_handle c) const {
    return caller.run(c);
  }
};

template <class Triangulation,class Caller>
class Java_facet_criteria{
  Caller caller;
public:
  typedef typename Triangulation::Facet Facet;
  typedef typename Triangulation::Cell_handle Cell_handle;
  typedef std::pair<int,double> Facet_quality;
  typedef boost::optional<Facet_quality> Facet_badness;

  Java_facet_criteria(Caller& call):caller(call){}
  Facet_badness operator()(const Facet& f) const {return caller.run(f);}
  Facet_badness operator()(Cell_handle c,int i) const { return (*this)(f(c,i));}
};

//for user defined criteria
template <class Triangulation,class Cell_caller,class Facet_caller>
class Java_criteria_wrapper
{
public:
  typedef Java_facet_criteria<Triangulation,Facet_caller>       Facet_criteria;
  typedef Java_cell_criteria <Triangulation,Cell_caller>        Cell_criteria;
private:
  Cell_criteria  cc;
  Facet_criteria fc;
public:
  #ifndef SWIG
  typedef Java_criteria_wrapper<Triangulation,Cell_caller,Facet_caller> cpp_base;
  const cpp_base& get_data() const {return *this;}
  cpp_base& get_data() {return *this;}
  #endif

  Java_criteria_wrapper(Cell_caller& ccall,Facet_caller& fcall):cc(ccall),fc(fcall){}
  #ifndef SWIG
  const Cell_criteria&   cell_criteria_object() const {return cc;}
  const Facet_criteria&  facet_criteria_object() const {return fc;}
  #endif
};
#endif


#endif //SWIG_CGAL_MESH_3_MESH_CRITERIA_H
