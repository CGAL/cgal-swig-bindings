// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Convex_hull_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Convex_hull_2)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection; %}
%pragma(java) moduleimports=%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection; %}

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Kernel_iterator_helper<Point_2>::input,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Kd_tree_wrapper::Kd_tree_wrapper)
#endif
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE



//typemaps for output iterator
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Pt_2_output_iterator Kernel_iterator_helper<Point_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Pt_2_output_iterator,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"LCGAL/Kernel/Point_2;")
#else
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
SWIG_CGAL_declare_generic_output_iterator(Point_2_output_iterator,Point_2_output_iterator_nested_iterator,Point_2)
#endif



%include "SWIG_CGAL/Convex_hull_2/convex_hull_2.h"

//include files
%{
  #include <SWIG_CGAL/Kernel/Point_2.h>
  #include <SWIG_CGAL/Convex_hull_2/all_includes.h>
%}

