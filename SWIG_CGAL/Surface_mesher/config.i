// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#define IMPORT_ONLY_POLYHEDRON_TYPES
%include "SWIG_CGAL/Polyhedron_3/config.i"
#undef IMPORT_ONLY_POLYHEDRON_TYPES

//macros defining the underlying types used
%{
#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/Complex_2_in_triangulation_3.h>
#include <CGAL/Surface_mesh_default_criteria_3.h>
#include <CGAL/Gray_level_image_3.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/Complex_2_in_triangulation_3_file_writer.h>
#include <CGAL/IO/output_surface_facets_to_polyhedron.h>
  
typedef CGAL::Surface_mesh_default_triangulation_3                      C2T3_DT;
typedef CGAL::Complex_2_in_triangulation_3<C2T3_DT>                     C2T3;
typedef CGAL::Surface_mesh_default_criteria_3<C2T3_DT>                  SMDC_3;
typedef CGAL::Gray_level_image_3<double, C2T3_DT::Point>                GLI_3;
typedef CGAL::Implicit_surface_3<C2T3_DT::Geom_traits, GLI_3>           IS_GLI_3;
  
%}


