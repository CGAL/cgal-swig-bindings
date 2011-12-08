// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_ALPHA_SHAPE_2_TYPEDEFS_H
#define SWIG_CGAL_ALPHA_SHAPE_2_TYPEDEFS_H

#include <SWIG_CGAL/Alpha_shape_2/config.h>
#include <CGAL/Alpha_shape_2.h>
#include <CGAL/Weighted_point.h>
#include <CGAL/Weighted_alpha_shape_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>

#ifdef ADD_JAVA_DATA_IN_FACE_AS2
#include <SWIG_CGAL/Java/JavaData.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#endif

//typedefs for Alpha_shape_2
typedef CGAL::Alpha_shape_vertex_base_2<EPIC_Kernel>                    CGAL_AS_vb;
typedef CGAL::Triangulation_face_base_2<EPIC_Kernel>                    CGAL_AS_fbb;
#ifndef ADD_JAVA_DATA_IN_FACE_AS2
typedef CGAL::Alpha_shape_face_base_2<EPIC_Kernel,CGAL_AS_fbb>          CGAL_AS_fb;
#else
typedef CGAL::Alpha_shape_face_base_2<EPIC_Kernel,CGAL_AS_fbb>          CGAL_AS_fbbb;
typedef CGAL::Triangulation_face_base_with_info_2<JavaData,EPIC_Kernel,CGAL_AS_fbbb>     CGAL_AS_fb;
#endif  
typedef CGAL::Triangulation_data_structure_2<CGAL_AS_vb,CGAL_AS_fb>     CGAL_AS_Tds;
typedef CGAL::Delaunay_triangulation_2<EPIC_Kernel,CGAL_AS_Tds>         CGAL_DT2;
typedef CGAL::Alpha_shape_2<CGAL_DT2>                                   CGAL_AS2;
//typedefs for Weighted_alpha_shape_2 
typedef CGAL::Weighted_alpha_shape_euclidean_traits_2<EPIC_Kernel>      CGAL_WAS_Gt;
typedef CGAL::Regular_triangulation_vertex_base_2<CGAL_WAS_Gt>          CGAL_WAS_vbb;
typedef CGAL::Alpha_shape_vertex_base_2<CGAL_WAS_Gt,CGAL_WAS_vbb>       CGAL_WAS_vb;
typedef CGAL::Regular_triangulation_face_base_2<CGAL_WAS_Gt>            CGAL_WAS_fbb;
#ifndef ADD_JAVA_DATA_IN_FACE_AS2  
typedef CGAL::Alpha_shape_face_base_2<CGAL_WAS_Gt, CGAL_WAS_fbb>        CGAL_WAS_fb;
#else
typedef CGAL::Alpha_shape_face_base_2<CGAL_WAS_Gt, CGAL_WAS_fbb>        CGAL_WAS_fbbb;
typedef CGAL::Triangulation_face_base_with_info_2<JavaData,CGAL_WAS_Gt,CGAL_WAS_fbbb>     CGAL_WAS_fb;
#endif  
typedef CGAL::Triangulation_data_structure_2<CGAL_WAS_vb,CGAL_WAS_fb>   CGAL_WAS_Tds;
typedef CGAL::Regular_triangulation_2<CGAL_WAS_Gt,CGAL_WAS_Tds>         CGAL_RT2;
typedef CGAL::Alpha_shape_2<CGAL_RT2>                                   CGAL_WAS2;  

#endif //SWIG_CGAL_ALPHA_SHAPE_2_TYPEDEFS_H
