#ifndef SWIG_CGAL_MESH_3_MESH_CRITERIA_H
#define SWIG_CGAL_MESH_3_MESH_CRITERIA_H

//for user defined criteria
template <class Facet_criteria_,class Cell_criteria_>
class Mesh_criteria_wrapper
{
  Facet_criteria_ fc;
  Cell_criteria_  cc;
public:
  typedef Facet_criteria_ Facet_criteria;
  typedef Cell_criteria_  Cell_criteria;

  Mesh_criteria_wrapper(const Cell_criteria& cell_criteria,const Facet_criteria& facet_criteria):cc(cell_criteria),fc(facet_criteria){}

  const Cell_criteria&   cell_criteria_object() {return fc;}
  const Facet_criteria&  facet_criteria_object(){return cc;}
};

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



#endif //SWIG_CGAL_MESH_3_MESH_CRITERIA_H
