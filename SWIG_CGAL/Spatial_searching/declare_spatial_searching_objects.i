#ifndef SWIG_CGAL_DECLARE_SPATIAL_SEARCHING_OBJECTS_I
#define SWIG_CGAL_DECLARE_SPATIAL_SEARCHING_OBJECTS_I


//Declare a tree, a search_method and their iterators: two versions fixed k and incremental
// --EXPOSEDNAMEPREFIX is the prefix use to expose objects
// --OTAG used to get C++ type and SWIG type as CGAL_##OTAG##_T_##DIM and SWIG_##OTAG##_T_##DIM respectively for the tree (replace T by S for the search)
// --POINT is the point type (should be any query but for now only point are supported)
// --DIM is the dimension of the point

%define Declare_spatial_searching_objects(EXPOSEDNAMEPREFIX,OTAG,POINT,DIM)
%typemap(javaimports)       Kd_tree_wrapper%{import CGAL.Kernel.POINT;import java.util.Iterator; import java.util.Collection;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_##DIM) Kd_tree_wrapper<CGAL_##OTAG##_T_##DIM,POINT,SWIG_FS_##DIM,SWIG_FB_##DIM>;
%typemap(javaimports)       NN_search_wrapper%{import CGAL.Kernel.POINT;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_##DIM) NN_search_wrapper<CGAL_##OTAG##_S_##DIM,POINT,SWIG_##OTAG##_T_##DIM>;

//typemaps for iterators
Iterator_for_java(Kd_tree_iterator,POINT,import CGAL.Kernel.POINT;)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_iterator_##DIM) Kd_tree_iterator<CGAL_##OTAG##_T_##DIM,POINT >;

Iterator_for_java(NN_search_iterator,Point_with_transformed_distance_##DIM,import CGAL.Kernel.POINT;)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_iterator_##DIM) NN_search_iterator<CGAL_##OTAG##_S_##DIM,SWIG_PTD_##DIM >;
%enddef

%define Declare_spatial_searching_objects_incremental(EXPOSEDNAMEPREFIX,OTAG,POINT,DIM)
%typemap(javaimports)       Kd_tree_wrapper%{import CGAL.Kernel.POINT;import java.util.Iterator; import java.util.Collection;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_##DIM) Kd_tree_wrapper<CGAL_##OTAG##_T_##DIM,POINT,SWIG_FS_##DIM,SWIG_FB_##DIM>;
%typemap(javaimports)       NN_search_wrapper_incremental%{import CGAL.Kernel.POINT;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_##DIM) NN_search_wrapper_incremental<CGAL_##OTAG##_S_##DIM,POINT,SWIG_##OTAG##_T_##DIM>;

//typemaps for iterators
Iterator_for_java(Kd_tree_iterator,POINT,import CGAL.Kernel.POINT;)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_iterator_##DIM) Kd_tree_iterator<CGAL_##OTAG##_T_##DIM,POINT >;

Iterator_for_java(NN_search_iterator,Point_with_transformed_distance_##DIM,import CGAL.Kernel.POINT;)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_iterator_##DIM) NN_search_iterator<CGAL_##OTAG##_S_##DIM,SWIG_PTD_##DIM >;
%enddef

#endif
