// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_SURFACE_MESHER_TYPEDEFS_H
#define SWIG_CGAL_SURFACE_MESHER_TYPEDEFS_H

#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/Complex_2_in_triangulation_3.h>
#include <CGAL/Surface_mesh_default_criteria_3.h>
#include <CGAL/Gray_level_image_3.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/Complex_2_in_triangulation_3_file_writer.h>
#include <CGAL/IO/facets_in_complex_2_to_triangle_mesh.h>
  
typedef CGAL::Surface_mesh_default_triangulation_3                      C2T3_DT;
typedef CGAL::Complex_2_in_triangulation_3<C2T3_DT>                     C2T3;
typedef CGAL::Surface_mesh_default_criteria_3<C2T3_DT>                  SMDC_3;
typedef CGAL::Gray_level_image_3<double, C2T3_DT::Point>                GLI_3;
typedef CGAL::Implicit_surface_3<C2T3_DT::Geom_traits, GLI_3>           IS_GLI_3;
  
#endif//SWIG_CGAL_SURFACE_MESHER_TYPEDEFS_H
