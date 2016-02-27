// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Triangulation_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Triangulation_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"

//include files
%{
  #include <SWIG_CGAL/Triangulation_3/Object.h>
  #include <SWIG_CGAL/Triangulation_3/all_includes.h>
  #include <SWIG_CGAL/Common/triple.h>
  #include <SWIG_CGAL/Common/Iterator.h>
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import CGAL.Kernel.Line_3; import CGAL.Kernel.Weighted_point_3; import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Tetrahedron_3; import CGAL.Kernel.Ref_int; import java.util.Iterator; import java.util.Collection;%}


//definitions
%include "SWIG_CGAL/Triangulation_3/Triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/Delaunay_triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/Regular_triangulation_3.h"
%include "SWIG_CGAL/Triangulation_3/triangulation_handles.h"
%include "SWIG_CGAL/Common/triple.h"
%include "SWIG_CGAL/Triangulation_3/Reference_wrappers.i"


#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemaps for Input iterator(s)
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper_3<CGAL::Tag_false>::Point_range,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",insert)
SWIG_CGAL_input_iterator_typemap_in(Weighting_helper_3<CGAL::Tag_true>::Point_range,Weighted_point_3,Weighted_point_3,Weighted_point_3::cpp_base,SWIGTYPE_p_Weighted_point_3,"(LCGAL/Kernel/Weighted_point_3;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Triangulation_3_wrapper::Triangulation_3_wrapper)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Delaunay_triangulation_3_wrapper::Delaunay_triangulation_3_wrapper)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Regular_triangulation_3_wrapper::Regular_triangulation_3_wrapper)
#endif
#endif//!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE

//local Object class: we cannot use the class from Kernel module as CGAL::Object uses RTTI
#ifdef SWIG_CGAL_Triangulation_3_MODULE
%include "SWIG_CGAL/Common/Object.i"
#endif

%import "SWIG_CGAL/Triangulation_3/declare_triangulation_3.i"
SWIG_CGAL_declare_triangulation_3(Triangulation_3,CGAL_T3)

%import "SWIG_CGAL/Triangulation_3/declare_Delaunay_triangulation_3.i"
SWIG_CGAL_declare_Delaunay_triangulation_3(Delaunay_triangulation_3,CGAL_DT3)

%import "SWIG_CGAL/Triangulation_3/declare_regular_triangulation_3.i"
SWIG_CGAL_declare_regular_triangulation_3(Regular_triangulation_3,CGAL_RT3)

#ifdef SWIG_CGAL_HAS_Triangulation_3_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Triangulation_3/extensions.i"
#endif
