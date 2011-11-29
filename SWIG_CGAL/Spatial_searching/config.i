// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


//macros defining the underlying types used
%{
#include <CGAL/Orthogonal_incremental_neighbor_search.h>
#include <CGAL/Incremental_neighbor_search.h>
#include <CGAL/K_neighbor_search.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/Search_traits_2.h>
#include <CGAL/Search_traits_3.h>
#include <CGAL/Fuzzy_sphere.h>
#include <CGAL/Fuzzy_iso_box.h>


typedef CGAL::Search_traits_2<EPIC_Kernel>                        CGAL_ST_2;
typedef CGAL::Fuzzy_sphere <CGAL_ST_2>                            CGAL_FS_2;
typedef CGAL::Fuzzy_iso_box<CGAL_ST_2>                            CGAL_FB_2;
//2D search methods
typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_2>   CGAL_OI_S_2;
typedef CGAL::Incremental_neighbor_search<CGAL_ST_2>              CGAL_I_S_2;
typedef CGAL::K_neighbor_search<CGAL_ST_2>                        CGAL_K_S_2;
typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_2>             CGAL_OK_S_2;
//2D trees
typedef CGAL_OI_S_2::Tree                                         CGAL_OI_T_2;
typedef CGAL_I_S_2 ::Tree                                         CGAL_I_T_2;
typedef CGAL_K_S_2 ::Tree                                         CGAL_K_T_2;
typedef CGAL_OK_S_2::Tree                                         CGAL_OK_T_2;
  
  
typedef CGAL::Search_traits_3<EPIC_Kernel>                        CGAL_ST_3;  
typedef CGAL::Fuzzy_sphere <CGAL_ST_3>                            CGAL_FS_3;
typedef CGAL::Fuzzy_iso_box<CGAL_ST_3>                            CGAL_FB_3;
//3D search methods
typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_3>   CGAL_OI_S_3;
typedef CGAL::Incremental_neighbor_search<CGAL_ST_3>              CGAL_I_S_3;
typedef CGAL::K_neighbor_search<CGAL_ST_3>                        CGAL_K_S_3;
typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_3>             CGAL_OK_S_3;  
//3D trees
typedef CGAL_OI_S_3::Tree                                         CGAL_OI_T_3;
typedef CGAL_I_S_3 ::Tree                                         CGAL_I_T_3;
typedef CGAL_K_S_3 ::Tree                                         CGAL_K_T_3;
typedef CGAL_OK_S_3::Tree                                         CGAL_OK_T_3;

%}

#ifdef SWIGJAVA
%{
#include <CGAL/Search_traits_adapter.h>
#include <SWIG_CGAL/Spatial_searching/First_of_pair.h>
#include <SWIG_CGAL/Java/JavaData.h>

typedef First_of_pair<EPIC_Kernel::Point_2>                          PPmap_2;
typedef std::pair<EPIC_Kernel::Point_2,JavaData>                     Point_WI_2;
typedef CGAL::Search_traits_adapter<Point_WI_2,PPmap_2,CGAL_ST_2>  CGAL_ST_WI_2;
typedef CGAL::Fuzzy_sphere <CGAL_ST_WI_2>                            CGAL_FS_WI_2;
typedef CGAL::Fuzzy_iso_box<CGAL_ST_WI_2>                            CGAL_FB_WI_2;
//2D search methods
typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_WI_2>   CGAL_OI_S_WI_2;
typedef CGAL::Incremental_neighbor_search<CGAL_ST_WI_2>              CGAL_I_S_WI_2;
typedef CGAL::K_neighbor_search<CGAL_ST_WI_2>                        CGAL_K_S_WI_2;
typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_WI_2>             CGAL_OK_S_WI_2;
//2D trees
typedef CGAL_OI_S_WI_2::Tree                                         CGAL_OI_T_WI_2;
typedef CGAL_I_S_WI_2 ::Tree                                         CGAL_I_T_WI_2;
typedef CGAL_K_S_WI_2 ::Tree                                         CGAL_K_T_WI_2;
typedef CGAL_OK_S_WI_2::Tree                                         CGAL_OK_T_WI_2;
  
typedef First_of_pair<EPIC_Kernel::Point_3>                          PPmap_3;
typedef std::pair<EPIC_Kernel::Point_3,JavaData>                     Point_WI_3;
typedef CGAL::Search_traits_adapter<Point_WI_3,PPmap_3,CGAL_ST_3>  CGAL_ST_WI_3;
typedef CGAL::Fuzzy_sphere <CGAL_ST_WI_3>                            CGAL_FS_WI_3;
typedef CGAL::Fuzzy_iso_box<CGAL_ST_WI_3>                            CGAL_FB_WI_3;
//3D search methods
typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_WI_3>   CGAL_OI_S_WI_3;
typedef CGAL::Incremental_neighbor_search<CGAL_ST_WI_3>              CGAL_I_S_WI_3;
typedef CGAL::K_neighbor_search<CGAL_ST_WI_3>                        CGAL_K_S_WI_3;
typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_WI_3>             CGAL_OK_S_WI_3;  
//3D trees
typedef CGAL_OI_S_WI_3::Tree                                         CGAL_OI_T_WI_3;
typedef CGAL_I_S_WI_3 ::Tree                                         CGAL_I_T_WI_3;
typedef CGAL_K_S_WI_3 ::Tree                                         CGAL_K_T_WI_3;
typedef CGAL_OK_S_WI_3::Tree                                         CGAL_OK_T_WI_3;
%}
#endif
