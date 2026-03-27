// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_TRIANGULATION_3_TYPEDEFS_H
#define SWIG_CGAL_TRIANGULATION_3_TYPEDEFS_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/Regular_triangulation_3.h>

#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_vertex_base_with_info_3.h>
#include <CGAL/Delaunay_triangulation_cell_base_3.h>
#include <CGAL/Triangulation_data_structure_3.h>

typedef CGAL::Triangulation_vertex_base_with_info_3<double, EPIC_Kernel>  Vb_with_info;
typedef CGAL::Delaunay_triangulation_cell_base_3<EPIC_Kernel>             Cb;
typedef CGAL::Triangulation_data_structure_3<Vb_with_info, Cb>            Tds_with_info;
typedef CGAL::Delaunay_triangulation_3<EPIC_Kernel, Tds_with_info>        CGAL_DT3_with_info;

typedef CGAL::Triangulation_3<EPIC_Kernel>                              CGAL_T3;
typedef CGAL::Delaunay_triangulation_3<EPIC_Kernel>                     CGAL_DT3;

typedef EPIC_Kernel                                                     RT_traits;
typedef CGAL::Regular_triangulation_3< RT_traits >                      CGAL_RT3;

#endif //SWIG_CGAL_TRIANGULATION_3_TYPEDEFS_H
