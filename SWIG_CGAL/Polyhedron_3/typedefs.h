// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_POLYHEDRON_3_TYPEDEFS_H
#define SWIG_CGAL_POLYHEDRON_3_TYPEDEFS_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <CGAL/Polyhedron_3.h>

#ifndef SWIGJAVA
#include <CGAL/Polyhedron_items_with_id_3.h>
#define SWIG_CGAL_FACET_SUPPORTS_PLANE
typedef CGAL::Polyhedron_3<EPIC_Kernel, CGAL::Polyhedron_items_with_id_3>     Polyhedron_3_;
#else
#include "SWIG_CGAL/Java/JavaData.h"
#include "SWIG_CGAL/Polyhedron_3/Polyhedron_items_with_id_and_info_3.h"
typedef CGAL::Polyhedron_3<EPIC_Kernel,CGAL::Polyhedron_items_with_id_and_info_3<JavaData> > Polyhedron_3_;
#endif //SWIGJAVA

#endif //SWIG_CGAL_POLYHEDRON_3_TYPEDEFS_H
