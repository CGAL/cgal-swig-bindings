// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_3_PARAMETERS_H
#define SWIG_CGAL_MESH_3_PARAMETERS_H

#include <CGAL/make_mesh_3.h>
#include <CGAL/exude_mesh_3.h>
#include <CGAL/perturb_mesh_3.h>
#include <CGAL/lloyd_optimize_mesh_3.h>
#include <CGAL/odt_optimize_mesh_3.h>
#include <CGAL/refine_mesh_3.h>

enum Mesh_optimization_return_code { BOUND_REACHED = 0,TIME_LIMIT_REACHED,CANT_IMPROVE_ANYMORE,CONVERGENCE_REACHED,MAX_ITERATION_NUMBER_REACHED};

class Mesh_3_parameters
{
  bool lloyd_set,odt_set,perturb_set,exude_set;
  //lloyd parameters
  double lloyd_time_limit;
  int lloyd_max_iteration_number;
  double lloyd_convergence;
  double lloyd_freeze_bound;
  //odt parameters
  double odt_time_limit;
  int odt_max_iteration_number;
  double odt_convergence;
  double odt_freeze_bound;
  //perturb parameters
  double perturb_time_limit;
  double perturb_sliver_bound;
  //exude parameters
  double exude_time_limit;
  double exude_sliver_bound;
public:
  Mesh_3_parameters():lloyd_set(false),odt_set(false),perturb_set(true),exude_set(true),perturb_time_limit(0),perturb_sliver_bound(0),exude_time_limit(0),exude_sliver_bound(0){}

  void set_lloyd(double time_limit,int max_iteration_number,double convergence,double freeze_bound)
  {
    lloyd_set=true;
    lloyd_time_limit=time_limit;
    lloyd_max_iteration_number=max_iteration_number;
    lloyd_convergence=convergence;
    lloyd_freeze_bound=freeze_bound;    
  }
  
  void set_odt(double time_limit,int max_iteration_number,double convergence,double freeze_bound)
  {
    odt_set=true;
    odt_time_limit=time_limit;
    odt_max_iteration_number=max_iteration_number;
    odt_convergence=convergence;
    odt_freeze_bound=freeze_bound;
  }

  void set_perturb(double time_limit,double sliver_bound)
  {
    perturb_set=true;
    perturb_time_limit=time_limit;
    perturb_sliver_bound=sliver_bound;    
  }

  void set_exude(double time_limit,double sliver_bound)
  {
    exude_set=true;
    exude_time_limit=time_limit;
    exude_sliver_bound=sliver_bound;    
  }
//Deep copy
  typedef Mesh_3_parameters Self;
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
//internal
  #ifndef SWIG
  CGAL::parameters::internal::Lloyd_options get_lloyd_parameters() const
  {
    return lloyd_set?
      CGAL::parameters::lloyd(lloyd_time_limit,lloyd_max_iteration_number,lloyd_convergence,lloyd_freeze_bound):
      CGAL::parameters::no_lloyd();
  }
  
  CGAL::parameters::internal::Odt_options get_odt_parameters() const
  {
    return odt_set?
      CGAL::parameters::odt(odt_time_limit,odt_max_iteration_number,odt_convergence,odt_freeze_bound):
      CGAL::parameters::no_odt();
  }
  
  CGAL::parameters::internal::Perturb_options get_perturb_parameters() const
  {
    return perturb_set?
      CGAL::parameters::perturb(perturb_time_limit,perturb_sliver_bound):
      CGAL::parameters::no_perturb();
  }
  
  CGAL::parameters::internal::Exude_options get_exude_parameters() const
  {
    return exude_set?
      CGAL::parameters::exude(exude_time_limit,exude_sliver_bound):
      CGAL::parameters::no_exude();
  }
  #endif
};

#endif //SWIG_CGAL_MESH_3_PARAMETERS_H
