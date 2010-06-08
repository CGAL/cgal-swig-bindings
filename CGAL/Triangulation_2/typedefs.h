#ifndef CGAL_SWIG_TRIANGULATION_2_TYPEDEFS_H
#define CGAL_SWIG_TRIANGULATION_2_TYPEDEFS_H

#include "../Kernel/typedefs.h"

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Triangulation_2.h>


typedef CGAL::Triangulation_2<EPIC_Kernel>                        EPIC_T2;
typedef CGAL::Constrained_triangulation_2<EPIC_Kernel>            EPIC_CT2;
typedef CGAL::Constrained_Delaunay_triangulation_2<EPIC_Kernel>   EPIC_CDT2;
typedef CGAL::Constrained_triangulation_plus_2<EPIC_CDT2>         EPIC_CDTplus2;




#endif //CGAL_SWIG_TRIANGULATION_2_TYPEDEFS_H
