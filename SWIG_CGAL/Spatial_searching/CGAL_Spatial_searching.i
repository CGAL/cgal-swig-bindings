// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Spatial_searching

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Spatial_searching");
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Spatial_searching failed to load. \n" + e);
      throw e;
    }
  }
%}


%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"

//include files
%{
  #include <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Kernel/Point_2.h>
  #include <SWIG_CGAL/Kernel/Point_3.h>
  #include <SWIG_CGAL/Spatial_searching/Kd_tree.h>
  #include <SWIG_CGAL/Spatial_searching/NN_search.h>
  #include <SWIG_CGAL/Spatial_searching/Fuzzy_objects.h>
%}

%include "SWIG_CGAL/Spatial_searching/config.i"

//definitions
%include "SWIG_CGAL/Spatial_searching/Kd_tree.h"
%include "SWIG_CGAL/Spatial_searching/NN_search.h"
%include "SWIG_CGAL/Spatial_searching/Fuzzy_objects.h"


%{
  #include <SWIG_CGAL/Spatial_searching/typedefs.h>
%}
%include "SWIG_CGAL/Spatial_searching/typedefs.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3;  import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

%include "std_pair.i"
%typemap(javaimports)       std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
%template(Point_with_transformed_distance_2) std::pair<Point_2,double>;
%typemap(javaimports)       std::pair<Point_3,double> %{import CGAL.Kernel.Point_3;%}
%template(Point_with_transformed_distance_3) std::pair<Point_3,double>;

//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Query_iterator_helper<Point_2>::input,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
SWIG_CGAL_input_iterator_typemap_in(Query_iterator_helper<Point_3>::input,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Kd_tree_wrapper::Kd_tree_wrapper)
#endif

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
%define Kd_tree_output_iterator_2 Query_iterator_helper<Point_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Kd_tree_output_iterator_2,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"LCGAL/Kernel/Point_2;")
%define Kd_tree_output_iterator_3 Query_iterator_helper<Point_3>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Kd_tree_output_iterator_3,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"LCGAL/Kernel/Point_3;")

%include "SWIG_CGAL/Spatial_searching/declare_spatial_searching_objects.i"
Declare_spatial_searching_objects_incremental(Orthogonal_incremental,OI,Point_2,2)
Declare_spatial_searching_objects_incremental(Incremental,I,Point_2,2)
Declare_spatial_searching_objects(K,K,Point_2,2)
Declare_spatial_searching_objects(Orthogonal_k,OK,Point_2,2)

Declare_spatial_searching_objects_incremental(Orthogonal_incremental,OI,Point_3,3)
Declare_spatial_searching_objects_incremental(Incremental,I,Point_3,3)
Declare_spatial_searching_objects(K,K,Point_3,3)
Declare_spatial_searching_objects(Orthogonal_k,OK,Point_3,3)

#ifdef SWIGJAVA
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

Declare_spatial_searching_objects_incremental_with_info(Orthogonal_incremental,OI,Point_2,2)
Declare_spatial_searching_objects_incremental_with_info(Incremental,I,Point_2,2)
Declare_spatial_searching_objects_with_info(K,K,Point_2,2)
Declare_spatial_searching_objects_with_info(Orthogonal_k,OK,Point_2,2)

Declare_spatial_searching_objects_incremental_with_info(Orthogonal_incremental,OI,Point_3,3)
Declare_spatial_searching_objects_incremental_with_info(Incremental,I,Point_3,3)
Declare_spatial_searching_objects_with_info(K,K,Point_3,3)
Declare_spatial_searching_objects_with_info(Orthogonal_k,OK,Point_3,3)
#endif
