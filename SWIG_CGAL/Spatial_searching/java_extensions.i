// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

%{
#include <CGAL/Search_traits_adapter.h>
#include <SWIG_CGAL/Spatial_searching/First_of_pair.h>
#include <SWIG_CGAL/Java/JavaData.h>

typedef First_of_pair<EPIC_Kernel::Point_2,JavaData>                 PPmap_2;
typedef std::pair<EPIC_Kernel::Point_2,JavaData>                     Point_WI_2;
typedef CGAL::Search_traits_adapter<Point_WI_2,PPmap_2,CGAL_ST_2>  CGAL_ST_WI_2;
typedef CGAL::Fuzzy_sphere <CGAL_ST_WI_2>                            CGAL_FS_WI_2;
typedef CGAL::Fuzzy_iso_box<CGAL_ST_WI_2>                            CGAL_FB_WI_2;
//2D search methods
typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_WI_2>   CGAL_OI_WI_S_2;
typedef CGAL::Incremental_neighbor_search<CGAL_ST_WI_2>              CGAL_I_WI_S_2;
typedef CGAL::K_neighbor_search<CGAL_ST_WI_2>                        CGAL_K_WI_S_2;
typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_WI_2>             CGAL_OK_WI_S_2;
//2D trees
typedef CGAL_OI_WI_S_2::Tree                                         CGAL_OI_WI_T_2;
typedef CGAL_I_WI_S_2 ::Tree                                         CGAL_I_WI_T_2;
typedef CGAL_K_WI_S_2 ::Tree                                         CGAL_K_WI_T_2;
typedef CGAL_OK_WI_S_2::Tree                                         CGAL_OK_WI_T_2;
  
typedef First_of_pair<EPIC_Kernel::Point_3,JavaData>                 PPmap_3;
typedef std::pair<EPIC_Kernel::Point_3,JavaData>                     Point_WI_3;
typedef CGAL::Search_traits_adapter<Point_WI_3,PPmap_3,CGAL_ST_3>  CGAL_ST_WI_3;
typedef CGAL::Fuzzy_sphere <CGAL_ST_WI_3>                            CGAL_FS_WI_3;
typedef CGAL::Fuzzy_iso_box<CGAL_ST_WI_3>                            CGAL_FB_WI_3;
//3D search methods
typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_WI_3>   CGAL_OI_WI_S_3;
typedef CGAL::Incremental_neighbor_search<CGAL_ST_WI_3>              CGAL_I_WI_S_3;
typedef CGAL::K_neighbor_search<CGAL_ST_WI_3>                        CGAL_K_WI_S_3;
typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_WI_3>             CGAL_OK_WI_S_3;  
//3D trees
typedef CGAL_OI_WI_S_3::Tree                                         CGAL_OI_WI_T_3;
typedef CGAL_I_WI_S_3 ::Tree                                         CGAL_I_WI_T_3;
typedef CGAL_K_WI_S_3 ::Tree                                         CGAL_K_WI_T_3;
typedef CGAL_OK_WI_S_3::Tree                                         CGAL_OK_WI_T_3;
%}

%inline %{
typedef std::pair<Point_2,JavaData> SWIG_Point_WI_2;
typedef std::pair<Point_3,JavaData> SWIG_Point_WI_3;
typedef Fuzzy_sphere_wrapper <CGAL_FS_WI_2,SWIG_Point_WI_2>  SWIG_FS_WI_2;
typedef Fuzzy_iso_box_wrapper<CGAL_FB_WI_2,SWIG_Point_WI_2>  SWIG_FB_WI_2;
typedef Fuzzy_sphere_wrapper <CGAL_FS_WI_3,SWIG_Point_WI_3>  SWIG_FS_WI_3;
typedef Fuzzy_iso_box_wrapper<CGAL_FB_WI_3,SWIG_Point_WI_3>  SWIG_FB_WI_3;
typedef std::pair<SWIG_Point_WI_2,double> SWIG_PTD_WI_2;
typedef std::pair<SWIG_Point_WI_3,double> SWIG_PTD_WI_3;
%}

%define SWIG_CGAL_spatial_searching_wrapper_with_info_typedefs(TAG,NN_SEARCH_WRAPPER)
%inline %{
  typedef Kd_tree_wrapper  <CGAL_##TAG##_WI_T_2,SWIG_Point_WI_2,SWIG_FS_WI_2,SWIG_FB_WI_2 >       SWIG_##TAG##_WI_T_2;
  typedef NN_SEARCH_WRAPPER<CGAL_##TAG##_WI_S_2,Point_2,SWIG_##TAG##_WI_T_2 >   SWIG_##TAG##_WI_S_2;
  typedef Kd_tree_wrapper  <CGAL_##TAG##_WI_T_3,SWIG_Point_WI_3,SWIG_FS_WI_3,SWIG_FB_WI_3 >       SWIG_##TAG##_WI_T_3;
  typedef NN_SEARCH_WRAPPER<CGAL_##TAG##_WI_S_3,Point_3,SWIG_##TAG##_WI_T_3 >   SWIG_##TAG##_WI_S_3;
%}
%enddef


//Orthogonal-incremental-nearest
SWIG_CGAL_spatial_searching_wrapper_with_info_typedefs(OI,NN_search_wrapper_incremental)
//Incremental-nearest
SWIG_CGAL_spatial_searching_wrapper_with_info_typedefs(I,NN_search_wrapper_incremental)
//Orthogonal-k-nearest
SWIG_CGAL_spatial_searching_wrapper_with_info_typedefs(OK,NN_search_wrapper)
//K-nearest
SWIG_CGAL_spatial_searching_wrapper_with_info_typedefs(K,NN_search_wrapper)

%import "SWIG_CGAL/Java/JavaData.h"

//typemap for point with info input iterator
%define SWIG_Point_WI_2 std::pair<Point_2,JavaData> %enddef
%define SWIG_Point_WI_3 std::pair<Point_3,JavaData> %enddef
SWIG_CGAL_input_iterator_typemap_in(Query_iterator_helper<SWIG_Point_WI_2>::input,SWIG_Point_WI_2,Point_with_info_2,internal::Converter<SWIG_Point_WI_2>::result_type,SWIGTYPE_p_Point_2,"(LCGAL/Spatial_searching/Point_with_info_2;)J",insert)
SWIG_CGAL_input_iterator_typemap_in(Query_iterator_helper<SWIG_Point_WI_3>::input,SWIG_Point_WI_3,Point_with_info_3,internal::Converter<SWIG_Point_WI_3>::result_type,SWIGTYPE_p_Point_3,"(LCGAL/Spatial_searching/Point_with_info_3;)J",insert)

//typemaps for output iterator
%define Kd_tree_output_iterator_WI_2 Query_iterator_helper<SWIG_Point_WI_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Kd_tree_output_iterator_WI_2,SWIG_Point_WI_2,Point_with_info_2,internal::Converter<SWIG_Point_WI_2>::result_type,SWIGTYPE_p_Point_2,"LCGAL/Spatial_searching/Point_with_info_2;")
%define Kd_tree_output_iterator_WI_3 Query_iterator_helper<SWIG_Point_WI_3>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Kd_tree_output_iterator_WI_3,SWIG_Point_WI_3,Point_with_info_3,internal::Converter<SWIG_Point_WI_3>::result_type,SWIGTYPE_p_Point_3,"LCGAL/Spatial_searching/Point_with_info_3;")


//Fuzzy objects
%typemap(javaimports)                 Fuzzy_sphere_wrapper%{import CGAL.Kernel.Point_2; import CGAL.Java.JavaData;%}
%template(Fuzzy_sphere_with_info_2)   Fuzzy_sphere_wrapper <CGAL_FS_WI_2,SWIG_Point_WI_2>;
%typemap(javaimports)                 Fuzzy_iso_box_wrapper%{import CGAL.Kernel.Point_2; import CGAL.Java.JavaData;%}
%template(Fuzzy_iso_box_with_info_2)  Fuzzy_iso_box_wrapper<CGAL_FB_WI_2,SWIG_Point_WI_2>;
%typemap(javaimports)                 Fuzzy_sphere_wrapper%{import CGAL.Kernel.Point_3; import CGAL.Java.JavaData;%}
%template(Fuzzy_sphere_with_info_3)   Fuzzy_sphere_wrapper <CGAL_FS_WI_3,SWIG_Point_WI_3>;
%typemap(javaimports)                 Fuzzy_iso_box_wrapper%{import CGAL.Kernel.Point_3; import CGAL.Java.JavaData;%}
%template(Fuzzy_iso_box_with_info_3)  Fuzzy_iso_box_wrapper<CGAL_FB_WI_3,SWIG_Point_WI_3>;

%typemap(javaimports)       std::pair<Point_2,JavaData> %{import CGAL.Kernel.Point_2; import CGAL.Java.JavaData;%}
%template(Point_with_info_2) std::pair<Point_2,JavaData>;
%typemap(javaimports)       std::pair<Point_3,JavaData> %{import CGAL.Kernel.Point_3; import CGAL.Java.JavaData;%}
%template(Point_with_info_3) std::pair<Point_3,JavaData>;

%template(Point_with_info_with_transformed_distance_2) std::pair<SWIG_Point_WI_2,double>;
%template(Point_with_info_with_transformed_distance_3) std::pair<SWIG_Point_WI_3,double>;

//macros with info
%define SWIG_CGAL_declare_spatial_searching_objects_with_info(EXPOSEDNAMEPREFIX,OTAG,POINT,DIM,NN_SEARCH_WRAPPER)
%typemap(javaimports)       Kd_tree_wrapper%{import CGAL.Kernel.POINT; import CGAL.Java.JavaData; import java.util.Iterator; import java.util.Collection;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_with_info_##DIM) Kd_tree_wrapper<CGAL_##OTAG##_WI_T_##DIM,std::pair<POINT,JavaData>,SWIG_FS_WI_##DIM,SWIG_FB_WI_##DIM>;
%typemap(javaimports)       NN_SEARCH_WRAPPER%{import CGAL.Kernel.POINT; import CGAL.Java.JavaData;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_with_info_##DIM) NN_SEARCH_WRAPPER<CGAL_##OTAG##_WI_S_##DIM,POINT,SWIG_##OTAG##_WI_T_##DIM>;

//typemaps for iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_with_info_##DIM,)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_iterator_with_info_##DIM) SWIG_CGAL_Iterator<CGAL_##OTAG##_WI_T_##DIM::iterator,std::pair<POINT,JavaData> >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_with_info_with_transformed_distance_##DIM,)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_iterator_with_info_##DIM) SWIG_CGAL_Iterator<CGAL_##OTAG##_WI_S_##DIM::iterator,SWIG_PTD_WI_##DIM >;
%enddef

SWIG_CGAL_declare_spatial_searching_objects_with_info(Orthogonal_incremental,OI,Point_2,2,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects_with_info(Incremental,I,Point_2,2,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects_with_info(K,K,Point_2,2,NN_search_wrapper)
SWIG_CGAL_declare_spatial_searching_objects_with_info(Orthogonal_k,OK,Point_2,2,NN_search_wrapper)

SWIG_CGAL_declare_spatial_searching_objects_with_info(Orthogonal_incremental,OI,Point_3,3,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects_with_info(Incremental,I,Point_3,3,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects_with_info(K,K,Point_3,3,NN_search_wrapper)
SWIG_CGAL_declare_spatial_searching_objects_with_info(Orthogonal_k,OK,Point_3,3,NN_search_wrapper)
