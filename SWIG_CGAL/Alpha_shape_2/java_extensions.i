// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

%include "SWIG_CGAL/Alpha_shape_2/config.h"

#ifdef ADD_JAVA_DATA_IN_FACE_AS2

%import "SWIG_CGAL/Java/JavaData.h"
%import "SWIG_CGAL/Java/Macro.i"

#define i_Face_handle_DT2 SWIG_Triangulation_2::CGAL_Face_handle<CGAL_AS2,Point_2>
SWIG_CGAL_add_JavaData_info_to_class(i_Face_handle_DT2,)
#define i_Face_handle_RT2 SWIG_Triangulation_2::CGAL_Face_handle<CGAL_WAS2,Weighted_point_2>
SWIG_CGAL_add_JavaData_info_to_class(i_Face_handle_RT2,)

#endif
