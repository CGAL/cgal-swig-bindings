// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Convex_hull_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Convex_hull_2)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection; %}
%pragma(java) moduleimports=%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection; %}

SWIG_CGAL_set_wrapper_iterator_helper_input(Point_2)
SWIG_CGAL_set_wrapper_iterator_helper_output(Point_2)


%include "SWIG_CGAL/Convex_hull_2/convex_hull_2.h"

//include files
%{
  #include <SWIG_CGAL/Convex_hull_2/typedefs.h>
  #include <SWIG_CGAL/Convex_hull_2/all_includes.h>
%}

#ifdef SWIG_CGAL_HAS_Convex_hull_2_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Convex_hull_2/extensions.i"
#endif
