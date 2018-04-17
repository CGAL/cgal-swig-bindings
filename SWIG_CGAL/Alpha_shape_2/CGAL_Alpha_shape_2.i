// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Alpha_shape_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Alpha_shape_2)
SWIG_CGAL_package_common()

#define CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%import  "SWIG_CGAL/Triangulation_2/Reference_wrappers.i"
%include "SWIG_CGAL/Common/Iterator.h"

%include "CGAL/version.h"

//include files
%{
  #include <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Alpha_shape_2/Object.h>
  #include <SWIG_CGAL/Alpha_shape_2/all_includes.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
  #include <SWIG_CGAL/Common/Iterator.h>
%}

#ifdef SWIGJAVA
%include "SWIG_CGAL/Alpha_shape_2/java_extensions.i"
#endif

//definitions
%include "SWIG_CGAL/Alpha_shape_2/Alpha_shape_2.h"
%include "SWIG_CGAL/Triangulation_2/triangulation_handles.h"
%import  "SWIG_CGAL/Triangulation_2/Triangulation_2.h"
%import  "SWIG_CGAL/Triangulation_2/Delaunay_triangulation_2.h"
%import  "SWIG_CGAL/Triangulation_2/Regular_triangulation_2.h"

//local Object class: we cannot use the class from Kernel module as CGAL::Object uses RTTI
#ifdef SWIG_CGAL_Alpha_shape_2_MODULE
%include "SWIG_CGAL/Common/Object.i"
#endif

//vertex range
%include "std_pair.i"
SWIG_CGAL_declare_identifier_of_template_class(Vertex_range,std::pair<double,double>)

//Face Interval_3
%include "SWIG_CGAL/Common/triple.h"
SWIG_CGAL_declare_identifier_of_template_class(Face_Interval_3,SWIG_CGAL::Triple<double,double,double>)

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Ref_int; import CGAL.Triangulation_2.Ref_Locate_type_2; import CGAL.Kernel.Weighted_point_2; import CGAL.Kernel.Triangle_2; import CGAL.Kernel.Segment_2;  import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper<CGAL::Tag_false>::Point_range,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",make_alpha_shape)
//typemap for weighted point input iterator
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper<CGAL::Tag_true>::Point_range,Weighted_point_2,Weighted_point_2,Weighted_point_2::cpp_base,SWIGTYPE_p_Weighted_point_2,"(LCGAL/Kernel/Weighted_point_2;)J",make_alpha_shape)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Alpha_shape_2_wrapper::Alpha_shape_2_wrapper)
#endif
#endif //SWIG_CGAL_NON_SUPPORTED
%import "SWIG_CGAL/Alpha_shape_2/declare_alpha_shape_2.i"

SWIG_CGAL_declare_alpha_shape_2(Alpha_shape_2,CGAL_AS2)
SWIG_CGAL_declare_weighted_alpha_shape_2(Weighted_alpha_shape_2,CGAL_WAS2)

#ifdef SWIG_CGAL_HAS_Alpha_shape_2_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Alpha_shape_2/extensions.i"
#endif
