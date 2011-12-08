// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_DECLARE_SPATIAL_SEARCHING_OBJECTS_I
#define SWIG_CGAL_DECLARE_SPATIAL_SEARCHING_OBJECTS_I


//Declare a tree, a search_method and their iterators: two versions fixed k and incremental
// --EXPOSEDNAMEPREFIX is the prefix use to expose objects
// --OTAG used to get C++ type and SWIG type as CGAL_##OTAG##_T_##DIM and SWIG_##OTAG##_T_##DIM respectively for the tree (replace T by S for the search)
// --POINT is the point type (should be any query but for now only point are supported)
// --DIM is the dimension of the point

%define SWIG_CGAL_declare_spatial_searching_objects(EXPOSEDNAMEPREFIX,OTAG,POINT,DIM,NN_SEARCH_WRAPPER)
%typemap(javaimports)       Kd_tree_wrapper%{import CGAL.Kernel.POINT;import java.util.Iterator; import java.util.Collection;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_##DIM) Kd_tree_wrapper<CGAL_##OTAG##_T_##DIM,POINT,SWIG_FS_##DIM,SWIG_FB_##DIM>;
%typemap(javaimports)       NN_SEARCH_WRAPPER%{import CGAL.Kernel.POINT;%}
%template(EXPOSEDNAMEPREFIX##_neighbor_search_##DIM) NN_SEARCH_WRAPPER<CGAL_##OTAG##_S_##DIM,POINT,SWIG_##OTAG##_T_##DIM>;

//typemaps for iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,POINT,import CGAL.Kernel.POINT;)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_tree_iterator_##DIM) SWIG_CGAL_Iterator<CGAL_##OTAG##_T_##DIM::iterator,POINT >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_with_transformed_distance_##DIM,import CGAL.Kernel.POINT;)
%template(EXPOSEDNAMEPREFIX##_neighbor_search_iterator_##DIM) SWIG_CGAL_Iterator<CGAL_##OTAG##_S_##DIM::iterator,SWIG_PTD_##DIM >;
%enddef

#endif
