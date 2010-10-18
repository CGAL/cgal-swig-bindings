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


#ifdef SWIGJAVA
//User defined test
template <class Triangulation,class Caller>
class Java_cell_criteria{
  Caller& caller;
public:
  typedef typename Triangulation::Cell_handle Cell_handle;
  typedef std::pair<int,double> Cell_quality;
  typedef boost::optional<Cell_quality> Cell_badness;
  
  Java_cell_criteria(Caller& call):caller(call){}
  Cell_badness operator()(Cell_handle c) const {
    return caller.run(c);
  }
};


template <class Triangulation>
class My_cell_criteria{
  CGAL::Mesh_cell_criteria_3<Triangulation> criteria;
public:
  typedef typename Triangulation::Cell_handle Cell_handle;
  typedef std::pair<int,double> Cell_quality;
  typedef boost::optional<Cell_quality> Cell_badness;
  
  My_cell_criteria():criteria(3,0){}
  Cell_badness operator()(Cell_handle c) const {return criteria(c);}
};

template <class Triangulation>
class My_facet_criteria{
  CGAL::Mesh_facet_criteria_3<Triangulation> criteria;
public:
  typedef typename Triangulation::Facet Facet;
  typedef typename Triangulation::Cell_handle Cell_handle;
  typedef std::pair<int,double> Facet_quality;
  typedef boost::optional<Facet_quality> Facet_badness;

  My_facet_criteria():criteria(0,0,0){}
  Facet_badness operator()(const Facet& f) const { return criteria(f);}
  Facet_badness operator()(Cell_handle c,int i) const { return criteria(c,i);}
};

//for user defined criteria
template <class Triangulation,class Caller>
class Mesh_criteria_wrapper
{
public:
  typedef My_facet_criteria<Triangulation>              Facet_criteria;
  typedef Java_cell_criteria<Triangulation,Caller>      Cell_criteria;
private:
  Facet_criteria fc;
  Cell_criteria  cc;
public:
  #ifndef SWIG
  typedef Mesh_criteria_wrapper<Triangulation,Caller> cpp_base;
  const cpp_base& get_data() const {return *this;}
  cpp_base& get_data() {return *this;}
  #endif

  Mesh_criteria_wrapper(Caller& call):cc(call){}
  #ifndef SWIG
  Mesh_criteria_wrapper(const Cell_criteria& cell_criteria,const Facet_criteria& facet_criteria):cc(cell_criteria),fc(facet_criteria){}
  const Cell_criteria&   cell_criteria() const {return cc;}
  const Facet_criteria&  facet_criteria() const {return fc;}
  #endif
};
#endif


#endif //SWIG_CGAL_MESH_3_MESH_CRITERIA_H
