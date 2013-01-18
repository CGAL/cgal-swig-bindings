// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_3_MESH_CRITERIA_H
#define SWIG_CGAL_MESH_3_MESH_CRITERIA_H

#include <CGAL/Mesh_criteria_3.h>
#include <SWIG_CGAL/Common/Macros.h>

enum Mesh_facet_topology {
  FACET_VERTICES_ON_SURFACE = 1,
  FACET_VERTICES_ON_SAME_SURFACE_PATCH,
  FACET_VERTICES_ON_SAME_SURFACE_PATCH_WITH_ADJACENCY_CHECK
};



template <class Base, class Field1, class Field2, class Field3, class Field4>
class Mesh_criteria_with_fields_wrapper
{
  
  #ifndef SWIG
  template <class Field,class Dummy=int>
  struct Default{ static Field get(){return Field();} };
  template<class Dummy> struct Default<double,Dummy>{ static double get(){return 0;} };
  #endif  
 
  Field1 m_edge_size;
  double m_facet_angle;
  Field2 m_facet_size;
  Field3 m_facet_distance;
  CGAL::Mesh_facet_topology m_facet_topology;
  double m_cell_radius_edge_ratio;
  Field4 m_cell_size;
public:
#ifndef SWIG
  typedef Base cpp_base;
  cpp_base get_data() const {
    return cpp_base(
      CGAL::parameters::edge_size=internal::make_conversion(m_edge_size),
      CGAL::parameters::facet_angle=m_facet_angle,
      CGAL::parameters::facet_size=internal::make_conversion(m_facet_size),
      CGAL::parameters::facet_distance=internal::make_conversion(m_facet_distance),
      CGAL::parameters::facet_topology=m_facet_topology,
      CGAL::parameters::cell_radius_edge_ratio=m_cell_radius_edge_ratio,
      CGAL::parameters::cell_size=internal::make_conversion(m_cell_size)
    );
  }
#endif
  
  Mesh_criteria_with_fields_wrapper()
  : m_edge_size(Default<Field1>::get()),m_facet_angle(0),
    m_facet_size(Default<Field2>::get()),m_facet_distance(Default<Field3>::get()),
    m_facet_topology(CGAL::FACET_VERTICES_ON_SURFACE),m_cell_radius_edge_ratio(0),m_cell_size(Default<Field4>::get())
  {}
    
  typedef Mesh_criteria_with_fields_wrapper<Base,Field1,Field2,Field3,Field4> Self;  
    
  //set criteria
  Self& edge_size(const Field1& v){ m_edge_size=v; return *this; }
  Self& facet_angle(double v){m_facet_angle=v; return *this;}
  Self& facet_size(const Field2& v){m_facet_size=v; return *this;}
  Self& facet_distance(const Field3& v){m_facet_distance=v; return *this;}
  Self& facet_topology(Mesh_facet_topology v){m_facet_topology=CGAL::enum_cast<CGAL::Mesh_facet_topology>(v); return *this;}
  Self& cell_radius_edge_ratio(double v){m_cell_radius_edge_ratio=v; return *this;}
  Self& cell_size(const Field4& v){m_cell_size=v; return *this;}
    
  
  //deep copy
  Self deepcopy(){return *this;}
  void deepcopy(const Self& other){*this=other;}
};

namespace internal{
  template <class Base, class Field1, class Field2, class Field3, class Field4>
  struct Converter<Mesh_criteria_with_fields_wrapper<Base, Field1, Field2, Field3, Field4> >
  {
    typedef Mesh_criteria_with_fields_wrapper<Base, Field1, Field2, Field3, Field4> Input;
    typedef typename Input::cpp_base  result_type;
    static const bool is_reference=false;
    static result_type convert(const Input& t){return t.get_data();}
  };
}

//Mesh_criteria_3<Tr> mc ( Facet_criteria facet_criteria, Cell_criteria cell_criteria);
//Mesh_criteria_3<Tr> mc ( Edge_criteria edge_criteria, Facet_criteria facet_criteria, Cell_criteria cell_criteria); 


#ifdef SWIGJAVA
//User defined test
template <class Triangulation,class Caller>
class Java_cell_criteria{
  Caller caller;
  typedef Java_cell_criteria<Triangulation,Caller> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
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
  typedef Java_criteria_wrapper<Triangulation,Cell_caller,Facet_caller> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
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
