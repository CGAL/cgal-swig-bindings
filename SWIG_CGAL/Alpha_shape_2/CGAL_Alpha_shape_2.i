// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Alpha_shape_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Alpha_shape_2");
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Alpha_shape_2 failed to load. \n" + e);
      throw e;
    }
  }
%}


#define CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2

//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif


%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/Point_2.h"
%import  "SWIG_CGAL/Kernel/Segment_2.h"
%import  "SWIG_CGAL/Kernel/Triangle_2.h"
%import  "SWIG_CGAL/Kernel/Weighted_point_2.h"
%import  "SWIG_CGAL/Kernel/enum.h"
%import  "SWIG_CGAL/Kernel/Reference_wrappers.i"
%import  "SWIG_CGAL/Triangulation_2/Reference_wrappers.i"
%include "SWIG_CGAL/Common/Iterator.h"

//include files
%{
  #include <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Alpha_shape_2/Alpha_shape_2.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
  #include <SWIG_CGAL/Common/Iterator.h>
%}

%include "SWIG_CGAL/Alpha_shape_2/config.i"

//definitions
%include "SWIG_CGAL/Alpha_shape_2/Alpha_shape_2.h"
%include "SWIG_CGAL/Triangulation_2/triangulation_handles.h"
%import  "SWIG_CGAL/Triangulation_2/Triangulation_2.h"
%import  "SWIG_CGAL/Triangulation_2/Delaunay_triangulation_2.h"
%import  "SWIG_CGAL/Triangulation_2/Regular_triangulation_2.h"


//vertex range
%include "std_pair.i"
%template(Vertex_range) std::pair<double,double>;

//Face Interval_3
%include "SWIG_CGAL/Common/triple.h"
%template(Face_Interval_3)  SWIG_CGAL::Triple<double,double,double>;

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Ref_int; import CGAL.Triangulation_2.Ref_Locate_type; import CGAL.Kernel.Weighted_point_2; import CGAL.Kernel.Triangle_2; import CGAL.Kernel.Segment_2;  import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper<CGAL::Tag_false>::Point_range,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",make_alpha_shape)
//typemap for weighted point input iterator
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper<CGAL::Tag_true>::Point_range,Weighted_point_2,Weighted_point_2,Weighted_point_2::cpp_base,SWIGTYPE_p_Weighted_point_2,"(LCGAL/Kernel/Weighted_point_2;)J",make_alpha_shape)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Alpha_shape_2_wrapper::Alpha_shape_2_wrapper)
#endif
%import "SWIG_CGAL/Alpha_shape_2/declare_alpha_shape_2.i"

#ifdef   SWIG_EXPOSE_ALPHA_SHAPE_2
Declare_alpha_shape_2(Alpha_shape_2,CGAL_AS2)
#endif //SWIG_EXPOSE_ALPHA_SHAPE_2
#ifdef   SWIG_EXPOSE_WEIGHTED_ALPHA_SHAPE_2
Declare_weighted_alpha_shape_2(Weighted_alpha_shape_2,CGAL_WAS2)
#endif //SWIG_EXPOSE_WEIGHTED_ALPHA_SHAPE_2

