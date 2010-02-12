#ifndef CGAL_SWIG_TYPEDEFS_H
#define CGAL_SWIG_TYPEDEFS_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPIC_Kernel;

#ifdef SWIGJAVA
#include <CGAL/Triangulation_vertex_base_with_info_3.h>
#include "JavaData.h"
typedef CGAL::Triangulation_vertex_base_with_info_3<JavaData, EPIC_Kernel> Vb;
typedef CGAL::Triangulation_data_structure_3<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_3<EPIC_Kernel,Tds> EPIC_DT3;
#else
typedef CGAL::Delaunay_triangulation_3<EPIC_Kernel> EPIC_DT3;
#endif



#endif //CGAL_SWIG_TYPEDEFS_H
