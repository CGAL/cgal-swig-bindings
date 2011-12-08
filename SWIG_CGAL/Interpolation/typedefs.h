// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_INTERPOLATION_TYPEDEFS_H
#define SWIG_CGAL_INTERPOLATION_TYPEDEFS_H

#include <CGAL/natural_neighbor_coordinates_2.h>
#include <CGAL/regular_neighbor_coordinates_2.h>
#include <CGAL/surface_neighbors_3.h>
#include <CGAL/surface_neighbor_coordinates_3.h>
#include <CGAL/interpolation_functions.h>
#include <CGAL/Interpolation_traits_2.h>
#include <CGAL/sibson_gradient_fitting.h>
#include <CGAL/Interpolation_gradient_fitting_traits_2.h>
//typedefs for the package
#include <map>
typedef std::map<EPIC_Kernel::Point_2,double,EPIC_Kernel::Less_xy_2> I_MPD;
typedef CGAL::Data_access<I_MPD> I_DA_PD;
typedef std::map<EPIC_Kernel::Point_2,EPIC_Kernel::Vector_2,EPIC_Kernel::Less_xy_2> I_MPV2;
typedef CGAL::Data_access<I_MPV2> I_DA_PV2;

#ifndef SWIG
namespace internal{
  template <class T1,class T2,class T3>
  std::pair<T2,T3> extract_pair(const CGAL::Triple<T1,T2,T3>& triple){return std::make_pair(triple.second,triple.third);}
  
  template <class T1,class T2,class T3,class T4>
  SWIG_CGAL::Triple<T2,T3,T4> extract_triple(const CGAL::Quadruple<T1,T2,T3,T4>& quad){return SWIG_CGAL::Triple<T2,T3,T4>(quad.second,quad.third,quad.fourth);}
}
#endif

#endif //SWIG_CGAL_INTERPOLATION_TYPEDEFS_H
