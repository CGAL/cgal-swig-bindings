// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Triangulation_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Triangulation_2)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"

%include "SWIG_CGAL/Common/Iterator.h"
#ifdef SWIGJAVA
%include "SWIG_CGAL/Triangulation_2/java_extensions.i"
#endif

%include "CGAL/version.h"

//include files
%{
  #include <SWIG_CGAL/Triangulation_2/Object.h>
  #include <SWIG_CGAL/Triangulation_2/all_includes.h>
  #include <SWIG_CGAL/Common/Iterator.h>
%}


//definitions
%include "SWIG_CGAL/Triangulation_2/Triangulation_2.h"
%include "SWIG_CGAL/Triangulation_2/Delaunay_triangulation_2.h"
%include "SWIG_CGAL/Triangulation_2/Regular_triangulation_2.h"
%include "SWIG_CGAL/Triangulation_2/Constrained_triangulation_2.h"
%include "SWIG_CGAL/Triangulation_2/Constrained_Delaunay_triangulation_2.h"
%include "SWIG_CGAL/Triangulation_2/Constrained_triangulation_plus_2.h"
%include "SWIG_CGAL/Triangulation_2/triangulation_handles.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Polygon_2; import CGAL.Kernel.Ref_int; import CGAL.Kernel.Weighted_point_2; import CGAL.Kernel.Segment_2;  import CGAL.Kernel.Triangle_2;  import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

//References
%include "SWIG_CGAL/Triangulation_2/Reference_wrappers.i"

//Constraint
%typemap(javaimports) std::pair<Point_2,Point_2> %{ import CGAL.Kernel.Point_2;%}
%include "std_pair.i"
SWIG_CGAL_declare_identifier_of_template_class(Constraint,std::pair<Point_2,Point_2>)

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper<CGAL::Tag_false>::Point_range,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
//typemap for weighted point input iterator
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper<CGAL::Tag_true>::Point_range,Weighted_point_2,Weighted_point_2,Weighted_point_2::cpp_base,SWIGTYPE_p_Weighted_point_2,"(LCGAL/Kernel/Weighted_point_2;)J",insert)

//typemap for Constaints input iterator
SWIG_CGAL_input_iterator_typemap_in(Constraint_range,Constraint,Constraint,iConstraint,SWIGTYPE_p_std__pairT_Point_2_Point_2_t,"(LCGAL/Triangulation_2/Constraint;)J",insert_constraint_range)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Constrained_triangulation_2_wrapper::Constrained_triangulation_2_wrapper)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Constrained_Delaunay_triangulation_2_wrapper::Constrained_Delaunay_triangulation_2_wrapper)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Constrained_triangulation_plus_2_wrapper::Constrained_triangulation_plus_2_wrapper)
#endif
#else //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//nothing to do for Point_2 and Point_3 ranges, already done in the kernel
SWIG_CGAL_declare_identifier_of_template_class(Constraint_input_iterator,Generic_input_iterator< std::pair<Point_2,Point_2> >)
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE

SWIG_CGAL_set_wrapper_iterator_helper_input(Point_2)

//local Object class: we cannot use the class from Kernel module as CGAL::Object uses RTTI
#ifdef SWIG_CGAL_Triangulation_2_MODULE
%include "SWIG_CGAL/Common/Object.i"
#endif

%import "SWIG_CGAL/Triangulation_2/declare_triangulation_2.i"
SWIG_CGAL_declare_triangulation_2(Triangulation_2,CGAL_T2,Point_2,CGAL::Tag_false)

%import "SWIG_CGAL/Triangulation_2/declare_Delaunay_triangulation_2.i"
SWIG_CGAL_declare_Delaunay_triangulation_2(Delaunay_triangulation_2,CGAL_DT2)

%import "SWIG_CGAL/Triangulation_2/declare_regular_triangulation_2.i"
SWIG_CGAL_declare_regular_triangulation_2(Regular_triangulation_2,CGAL_RT2)

%import "SWIG_CGAL/Triangulation_2/declare_constrained_triangulation_2.i"
SWIG_CGAL_declare_constrained_triangulation_2(Constrained_triangulation_2,CGAL_CT2, Triangulation_2)

%import "SWIG_CGAL/Triangulation_2/declare_constrained_Delaunay_triangulation_2.i"
SWIG_CGAL_declare_constrained_Delaunay_triangulation_2(Constrained_Delaunay_triangulation_2,CGAL_CDT2, Triangulation_2)

%import "SWIG_CGAL/Triangulation_2/declare_constrained_Delaunay_triangulation_plus_2.i"
SWIG_CGAL_declare_constrained_Delaunay_triangulation_plus_2(Constrained_Delaunay_triangulation_plus_2,CGAL_CDTplus2, Triangulation_2)

#ifdef SWIG_CGAL_HAS_Triangulation_2_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Triangulation_2/extensions.i"
#endif
