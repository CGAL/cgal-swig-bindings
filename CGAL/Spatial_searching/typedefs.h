#ifndef SWIG_CGAL_SPATIAL_SEARCHING_TYPEDEFS_H
#define SWIG_CGAL_SPATIAL_SEARCHING_TYPEDEFS_H
 
#include "../Kernel/Point_2.h"

typedef Fuzzy_sphere_wrapper <CGAL_FS_2,Point_2>  SWIG_FS_2;
typedef Fuzzy_iso_box_wrapper<CGAL_FB_2,Point_2>  SWIG_FB_2;
typedef Kd_tree_wrapper<CGAL_OI_T_2,Point_2,SWIG_FS_2,SWIG_FB_2 > SWIG_OI_T_2;
typedef NN_search_wrapper<CGAL_OI_S_2,Point_2,SWIG_OI_T_2 > SWIG_OI_S_2;
typedef std::pair<Point_2,double> SWIG_PTD_2;


#endif //SWIG_CGAL_SPATIAL_SEARCHING_TYPEDEFS_H
