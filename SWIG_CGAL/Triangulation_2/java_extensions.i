// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

%include "SWIG_CGAL/Triangulation_2/config.h"

#if defined(ADD_JAVA_DATA_IN_FACET_CDT_2) || defined(ADD_JAVA_DATA_IN_SIMPLICES_DT2)
%import "SWIG_CGAL/Java/JavaData.h"
%import "SWIG_CGAL/Java/Macro.i"
#endif

#ifdef ADD_JAVA_DATA_IN_FACET_CDT_2
//assign JavaData to Face_handle of CGAL_CDTplus2
#define i_Face_handle_CDT2_plus   SWIG_Triangulation_2::CGAL_Face_handle<CGAL_CDTplus2,Point_2>
#define i_Vertex_handle_CDT2_plus SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_CDTplus2,Point_2>
SWIG_CGAL_add_JavaData_info_to_class(i_Face_handle_CDT2_plus,)
SWIG_CGAL_add_JavaData_info_to_class(i_Vertex_handle_CDT2_plus,import CGAL.Kernel.Point_2;)
#define i_Face_handle_CDT2 SWIG_Triangulation_2::CGAL_Face_handle<CGAL_CDT2,Point_2>
#define i_Vertex_handle_CDT2 SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_CDT2,Point_2>
SWIG_CGAL_add_JavaData_info_to_class(i_Face_handle_CDT2,)
SWIG_CGAL_add_JavaData_info_to_class(i_Vertex_handle_CDT2,import CGAL.Kernel.Point_2;)
#endif

#ifdef ADD_JAVA_DATA_IN_SIMPLICES_DT2
//assign JavaData to Face_handle of CGAL_CDTplus2
#define i_Face_handle_DT2 SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>
#define i_Vertex_handle_DT2 SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>
SWIG_CGAL_add_JavaData_info_to_class(i_Face_handle_DT2,)
SWIG_CGAL_add_JavaData_info_to_class(i_Vertex_handle_DT2,import CGAL.Kernel.Point_2;)
#endif

