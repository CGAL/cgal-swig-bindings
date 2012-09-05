// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_TYPEDEFS_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_TYPEDEFS_H
//import Delaunay and regular triangulation typedefs
#include <SWIG_CGAL/Triangulation_2/typedefs.h>

#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Regular_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/Regular_triangulation_adaptation_policies_2.h>
#include <CGAL/Identity_policy_2.h>


//typedefs for Delaunay triangulation
//  Traits
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<CGAL_DT2>                 V2_DT_AT;
//  Policies
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<CGAL_DT2> V2_DT_CAP;
typedef CGAL::Delaunay_triangulation_degeneracy_removal_policy_2<CGAL_DT2>         V2_DT_AP;
typedef CGAL::Identity_policy_2<CGAL_DT2,V2_DT_CAP>                                V2_DT_I_CAP;
typedef CGAL::Identity_policy_2<CGAL_DT2,V2_DT_AP>                                 V2_DT_IAP;
//  Voronoi diagrams
typedef CGAL::Voronoi_diagram_2< CGAL_DT2,V2_DT_AT,V2_DT_CAP >                     V2_DT_AT_CAP;
typedef CGAL::Voronoi_diagram_2< CGAL_DT2,V2_DT_AT,V2_DT_AP >                      V2_DT_AT_AP;
typedef CGAL::Voronoi_diagram_2< CGAL_DT2,V2_DT_AT,V2_DT_I_CAP >                   V2_DT_AT_ICAP;
typedef CGAL::Voronoi_diagram_2< CGAL_DT2,V2_DT_AT,V2_DT_IAP >                     V2_DT_AT_IAP;

//typedef for Regular triangulation
//  Traits
typedef CGAL::Regular_triangulation_adaptation_traits_2<CGAL_RT2>                  V2_RT_AT;
//  Policies
typedef CGAL::Regular_triangulation_caching_degeneracy_removal_policy_2<CGAL_RT2>  V2_RT_CAP;
typedef CGAL::Regular_triangulation_degeneracy_removal_policy_2<CGAL_RT2>          V2_RT_AP;
typedef CGAL::Identity_policy_2<CGAL_RT2,V2_RT_CAP>                                V2_RT_I_CAP;
typedef CGAL::Identity_policy_2<CGAL_RT2,V2_RT_AP>                                 V2_RT_IAP;
//  Voronoi diagrams
typedef CGAL::Voronoi_diagram_2< CGAL_RT2,V2_RT_AT,V2_RT_CAP >                     V2_RT_AT_CAP;
typedef CGAL::Voronoi_diagram_2< CGAL_RT2,V2_RT_AT,V2_RT_AP >                      V2_RT_AT_AP;
typedef CGAL::Voronoi_diagram_2< CGAL_RT2,V2_RT_AT,V2_RT_I_CAP >                   V2_RT_AT_ICAP;
typedef CGAL::Voronoi_diagram_2< CGAL_RT2,V2_RT_AT,V2_RT_IAP >                     V2_RT_AT_IAP;



#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_TYPEDEFS_H

