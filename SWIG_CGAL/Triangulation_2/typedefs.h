// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_TYPEDEFS_H
#define SWIG_CGAL_TRIANGULATION_2_TYPEDEFS_H

#include <SWIG_CGAL/Triangulation_2/config.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>  

#if defined(ADD_JAVA_DATA_IN_FACET_CDT_2) || defined(ADD_JAVA_DATA_IN_SIMPLICES_DT2)
#include <SWIG_CGAL/Java/JavaData.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#endif

typedef CGAL::Triangulation_2<EPIC_Kernel>                                  CGAL_T2;
#ifdef ADD_JAVA_DATA_IN_SIMPLICES_DT2
typedef CGAL::Triangulation_vertex_base_with_info_2<JavaData,EPIC_Kernel>   Vbase_DT2;
typedef CGAL::Triangulation_face_base_with_info_2<JavaData,EPIC_Kernel>     Fbase_DT2;
typedef CGAL::Triangulation_data_structure_2<Vbase_DT2,Fbase_DT2>           TDS_DT2;
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel,TDS_DT2>                 CGAL_DT2;
#else
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel>                         CGAL_DT2;
#endif
typedef CGAL::Regular_triangulation_euclidean_traits_2<EPIC_Kernel>         CGAL_regular_traits;
typedef CGAL::Regular_triangulation_2<CGAL_regular_traits>                  CGAL_RT2;
#ifndef ADD_JAVA_DATA_IN_FACET_CDT_2
typedef CGAL::Triangulation_data_structure_2 <
    CGAL::Triangulation_vertex_base_2<EPIC_Kernel>,
		CGAL::Constrained_triangulation_face_base_2<EPIC_Kernel> >              CDT_TDS;
#else
#include  <CGAL/Triangulation_face_base_with_info_2.h>  
typedef CGAL::Triangulation_vertex_base_with_info_2<JavaData,EPIC_Kernel>   Vbase_CDT2_plus;
typedef CGAL::Triangulation_face_base_with_info_2<JavaData,EPIC_Kernel>     Fbi;
typedef CGAL::Constrained_triangulation_face_base_2<EPIC_Kernel, Fbi>       Fb;
typedef CGAL::Triangulation_data_structure_2<Vbase_CDT2_plus,Fb>            CDT_TDS;
#endif
   
typedef CGAL::Exact_predicates_tag                                          EP_tag;
typedef CGAL::Constrained_triangulation_2<EPIC_Kernel,CDT_TDS,EP_tag>               CGAL_CT2;
typedef CGAL::Constrained_Delaunay_triangulation_2<EPIC_Kernel,CDT_TDS,EP_tag>      CGAL_CDT2;
typedef CGAL::Constrained_triangulation_plus_2<CGAL_CDT2>                   CGAL_CDTplus2;

typedef std::pair<EPIC_Kernel::Point_2,EPIC_Kernel::Point_2>                iConstraint;

#endif //SWIG_CGAL_TRIANGULATION_2_TYPEDEFS_H
