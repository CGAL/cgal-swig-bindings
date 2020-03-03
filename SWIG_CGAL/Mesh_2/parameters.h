// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_2_PARAMETERS_H
#define SWIG_CGAL_MESH_2_PARAMETERS_H

#include <CGAL/lloyd_optimize_mesh_2.h>

enum Mesh_optimization_return_code { BOUND_REACHED = 0,TIME_LIMIT_REACHED,CANT_IMPROVE_ANYMORE,CONVERGENCE_REACHED,MAX_ITERATION_NUMBER_REACHED};

class Mesh_2_parameters
{
  bool seeds_set;

  double time_limit;
  int max_iteration_number;
  double convergence;
  double freeze_bound;
  Point_range seeds;
  bool mark;

public:

  Mesh_2_parameters()
    : seeds_set(false)
    , time_limit(0)
    , max_iteration_number(0)
    , convergence(0.001)
    , freeze_bound(0.001)
    , mark(false)
  {}

  void set_time_limit(double limit)
  {
    time_limit=limit;
  }

  void set_max_iteration_number(int mi)
  {
    max_iteration_number=mi;
  }

  void set_convergence(double c)
  {
    convergence=c;
  }

  void set_freeze_bound(double b)
  {
    freeze_bound=b;
  }

  void set_seeds(Point_range r)
  {
    seeds_set=true;
    seeds=r;
  } 

  void set_mark(bool m)
  {
    mark=m;
  }
  

//Deep copy
  typedef Mesh_2_parameters Self;
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
//internal
  #ifndef SWIG
  double get_time_limit() const
  {
    return time_limit;
  }

  int get_max_iteration_number() const
  {
    return max_iteration_number;
  }

  double get_convergence() const
  {
    return convergence;
  }

  double get_freeze_bound() const
  {
    return freeze_bound;
  }

  Point_range get_seeds() const
  {
    return seeds;
  } 

  bool get_mark() const
  {
    return mark;
  }
  
  bool seeds_provided() const
  {
    return seeds_set;
  }
  #endif
};

#endif //SWIG_CGAL_MESH_2_PARAMETERS_H
