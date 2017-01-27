// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

%module CGAL_Polyline_simplification_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Polyline_simplification_2)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include  "SWIG_CGAL/Common/Wrapper_iterator_helper.h"
%include  "SWIG_CGAL/Common/Output_iterator_wrapper.h"
%include "SWIG_CGAL/Common/Iterator.h"

//include files
%{
  #include <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Triangulation_2/Object.h>
  #include <SWIG_CGAL/Triangulation_2/all_includes.h>
  #include <SWIG_CGAL/Common/Iterator.h>
  #include <SWIG_CGAL/Kernel/Point_2.h>
  #include <SWIG_CGAL/Kernel/Polygon_2.h>
  #include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
  #include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
  #include <SWIG_CGAL/Triangulation_2/Constrained_triangulation_plus_2.h>
  #include <SWIG_CGAL/Polyline_simplification_2/typedefs.h>
  #include <SWIG_CGAL/Polyline_simplification_2/Polyline_simplification_2.h>
%}

%pragma(java) jniclassimports=%{
  import CGAL.Kernel.Ref_int;
   import CGAL.Triangulation_2.Ref_Locate_type_2;
  import CGAL.Triangulation_2.Constraint;
  import CGAL.Kernel.Point_2;
  import CGAL.Kernel.Polygon_2;
  import CGAL.Kernel.Segment_2;
  import CGAL.Kernel.Triangle_2;
  import java.util.Iterator;
  import java.util.Collection;
  import CGAL.Java.JavaData;
%}

%pragma(java) moduleimports=%{
  import CGAL.Kernel.Point_2;
  import CGAL.Kernel.Polygon_2;
  import java.util.Iterator;
  import java.util.Collection;
%}

%include "SWIG_CGAL/Polyline_simplification_2/Polyline_simplification_2.h"

// define a new CDT_plus_2 matching vertex requirements
%include "SWIG_CGAL/Triangulation_2/declare_constrained_Delaunay_triangulation_plus_2.i"
%import  "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"

#ifdef SWIGJAVA
%include "SWIG_CGAL/Triangulation_2/config.h"
#if defined(ADD_JAVA_DATA_IN_FACET_CDT_2) || defined(ADD_JAVA_DATA_IN_SIMPLICES_DT2)
%import "SWIG_CGAL/Java/JavaData.h"
%import "SWIG_CGAL/Java/Macro.i"
#endif
#endif

%extend SWIG_Triangulation_2::CGAL_Vertex_handle{
  bool is_removable() const
  {
    return $self->get_data()->is_removable();
  }

  void set_removable(bool b)
  {
    $self->get_data()->set_removable(b);
  }
#ifdef ADD_JAVA_DATA_IN_FACET_CDT_2
  JavaData& info(){
    return $self->get_data()->info();
  }
  void get_info(JavaData& jd){
    jd=$self->get_data()->info();
  }
  void set_info(const JavaData& jd){
    $self->get_data()->info()=jd;
  }
#endif
}

%typemap(javaimports) SWIG_Triangulation_2::CGAL_Vertex_handle<PS_CDTP2,Point_2> %{import CGAL.Java.JavaData; import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_constrained_Delaunay_triangulation_plus_2(PS2_Constrained_Delaunay_triangulation_plus_2,PS_CDTP2,Polyline_simplification_2)

SWIG_CGAL_set_wrapper_iterator_helper_input(Point_2)
SWIG_CGAL_set_wrapper_iterator_helper_output(Point_2)

// Cost and Stop functors
%template(Hybrid_squared_distance_cost) Hybrid_squared_distance_cost_wrapper<PS_CDTP2>;
%template(Scaled_squared_distance_cost) Scaled_squared_distance_cost_wrapper<PS_CDTP2>;
%template(Squared_distance_cost) Squared_distance_cost_wrapper<PS_CDTP2>;
%template(Stop_above_cost_threshold) Stop_above_cost_threshold_wrapper<PS_CDTP2>;
%template(Stop_below_count_ratio_threshold) Stop_below_count_ratio_threshold_wrapper<PS_CDTP2>;
%template(Stop_below_count_threshold) Stop_below_count_threshold_wrapper<PS_CDTP2>;

%include "SWIG_CGAL/Polyline_simplification_2/macros.i"
declare_simply_functions(Hybrid_squared_distance_cost_wrapper<PS_CDTP2>,Stop_above_cost_threshold_wrapper<PS_CDTP2>)
declare_simply_functions(Hybrid_squared_distance_cost_wrapper<PS_CDTP2>,Stop_below_count_ratio_threshold_wrapper<PS_CDTP2>)
declare_simply_functions(Hybrid_squared_distance_cost_wrapper<PS_CDTP2>,Stop_below_count_threshold_wrapper<PS_CDTP2>)

declare_simply_functions(Scaled_squared_distance_cost_wrapper<PS_CDTP2>,Stop_above_cost_threshold_wrapper<PS_CDTP2>)
declare_simply_functions(Scaled_squared_distance_cost_wrapper<PS_CDTP2>,Stop_below_count_ratio_threshold_wrapper<PS_CDTP2>)
declare_simply_functions(Scaled_squared_distance_cost_wrapper<PS_CDTP2>,Stop_below_count_threshold_wrapper<PS_CDTP2>)

declare_simply_functions(Squared_distance_cost_wrapper<PS_CDTP2>,Stop_above_cost_threshold_wrapper<PS_CDTP2>)
declare_simply_functions(Squared_distance_cost_wrapper<PS_CDTP2>,Stop_below_count_ratio_threshold_wrapper<PS_CDTP2>)
declare_simply_functions(Squared_distance_cost_wrapper<PS_CDTP2>,Stop_below_count_threshold_wrapper<PS_CDTP2>)
