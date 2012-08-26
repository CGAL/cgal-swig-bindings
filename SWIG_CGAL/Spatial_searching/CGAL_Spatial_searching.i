// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Spatial_searching

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Spatial_searching)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"

//include files
%{
  #include <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Kernel/Point_2.h>
  #include <SWIG_CGAL/Kernel/Point_3.h>
  #include <SWIG_CGAL/Spatial_searching/all_includes.h>
%}

//definitions
%include "SWIG_CGAL/Spatial_searching/Kd_tree.h"
%include "SWIG_CGAL/Spatial_searching/NN_search.h"
%include "SWIG_CGAL/Spatial_searching/Fuzzy_objects.h"

//wrapper typedefs
%inline %{
typedef Fuzzy_sphere_wrapper <CGAL_FS_2,Point_2>  SWIG_FS_2;
typedef Fuzzy_iso_box_wrapper<CGAL_FB_2,Point_2>  SWIG_FB_2;
typedef Fuzzy_sphere_wrapper <CGAL_FS_3,Point_3>  SWIG_FS_3;
typedef Fuzzy_iso_box_wrapper<CGAL_FB_3,Point_3>  SWIG_FB_3;
typedef std::pair<Point_2,double> SWIG_PTD_2;
typedef std::pair<Point_3,double> SWIG_PTD_3;
%}

%define SWIG_CGAL_spatial_searching_wrapper_typedefs(TAG,NN_SEARCH_WRAPPER)
%inline %{
  typedef Kd_tree_wrapper  <CGAL_##TAG##_T_2,Point_2,SWIG_FS_2,SWIG_FB_2 >       SWIG_##TAG##_T_2;
  typedef NN_SEARCH_WRAPPER<CGAL_##TAG##_S_2,Point_2,SWIG_##TAG##_T_2 >   SWIG_##TAG##_S_2;
  typedef Kd_tree_wrapper  <CGAL_##TAG##_T_3,Point_3,SWIG_FS_3,SWIG_FB_3 >       SWIG_##TAG##_T_3;
  typedef NN_SEARCH_WRAPPER<CGAL_##TAG##_S_3,Point_3,SWIG_##TAG##_T_3 >   SWIG_##TAG##_S_3;
%}
%enddef

//Orthogonal-incremental-nearest
SWIG_CGAL_spatial_searching_wrapper_typedefs(OI,NN_search_wrapper_incremental)
//Incremental-nearest
SWIG_CGAL_spatial_searching_wrapper_typedefs(I,NN_search_wrapper_incremental)
//Orthogonal-k-nearest
SWIG_CGAL_spatial_searching_wrapper_typedefs(OK,NN_search_wrapper)
//K-nearest
SWIG_CGAL_spatial_searching_wrapper_typedefs(K,NN_search_wrapper)


%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3;  import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

%include "std_pair.i"
%typemap(javaimports)       std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
%template(Point_with_transformed_distance_2) std::pair<Point_2,double>;
%typemap(javaimports)       std::pair<Point_3,double> %{import CGAL.Kernel.Point_3;%}
%template(Point_with_transformed_distance_3) std::pair<Point_3,double>;

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Query_iterator_helper<Point_2>::input,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
SWIG_CGAL_input_iterator_typemap_in(Query_iterator_helper<Point_3>::input,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Kd_tree_wrapper::Kd_tree_wrapper)
#endif
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE

//Fuzzy objects
%typemap(javaimports)       Fuzzy_sphere_wrapper%{import CGAL.Kernel.Point_2;%}
%template(Fuzzy_sphere_2)   Fuzzy_sphere_wrapper <CGAL_FS_2,Point_2>;
%typemap(javaimports)       Fuzzy_iso_box_wrapper%{import CGAL.Kernel.Point_2;%}
%template(Fuzzy_iso_box_2)  Fuzzy_iso_box_wrapper<CGAL_FB_2,Point_2>;
%typemap(javaimports)       Fuzzy_sphere_wrapper%{import CGAL.Kernel.Point_3;%}
%template(Fuzzy_sphere_3)   Fuzzy_sphere_wrapper <CGAL_FS_3,Point_3>;
%typemap(javaimports)       Fuzzy_iso_box_wrapper%{import CGAL.Kernel.Point_3;%}
%template(Fuzzy_iso_box_3)  Fuzzy_iso_box_wrapper<CGAL_FB_3,Point_3>;

//typemaps for output iterator
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Kd_tree_output_iterator_2 Query_iterator_helper<Point_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Kd_tree_output_iterator_2,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"LCGAL/Kernel/Point_2;")
%define Kd_tree_output_iterator_3 Query_iterator_helper<Point_3>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Kd_tree_output_iterator_3,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"LCGAL/Kernel/Point_3;")
#else
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
SWIG_CGAL_declare_generic_output_iterator(Point_2_output_iterator,Point_2_output_iterator_nested_iterator,Point_2)
SWIG_CGAL_declare_generic_output_iterator(Point_3_output_iterator,Point_3_output_iterator_nested_iterator,Point_3)
#endif

%include "SWIG_CGAL/Spatial_searching/declare_spatial_searching_objects.i"
SWIG_CGAL_declare_spatial_searching_objects(Orthogonal_incremental,OI,Point_2,2,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects(Incremental,I,Point_2,2,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects(K,K,Point_2,2,NN_search_wrapper)
SWIG_CGAL_declare_spatial_searching_objects(Orthogonal_k,OK,Point_2,2,NN_search_wrapper)

SWIG_CGAL_declare_spatial_searching_objects(Orthogonal_incremental,OI,Point_3,3,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects(Incremental,I,Point_3,3,NN_search_wrapper_incremental)
SWIG_CGAL_declare_spatial_searching_objects(K,K,Point_3,3,NN_search_wrapper)
SWIG_CGAL_declare_spatial_searching_objects(Orthogonal_k,OK,Point_3,3,NN_search_wrapper)

#ifdef SWIGJAVA
%include "SWIG_CGAL/Spatial_searching/java_extensions.i"
#endif
