// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Point_set_processing_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Point_set_processing_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"

%pragma(java) jniclassimports=%{
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import java.util.Iterator;
import java.util.Collection;
%}

%pragma(java) moduleimports=%{
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import java.util.Iterator;
import java.util.Collection;
%};

%types(Point_3*,Point_3);//needed so that the identifier SWIGTYPE_p_Point_3 is generated
SWIG_CGAL_set_wrapper_iterator_helper_input(Point_3)
%types(Vector_3*,Vector_3);//needed so that the identifier SWIGTYPE_p_Vector_3 is generated
SWIG_CGAL_set_wrapper_iterator_helper_input(Vector_3)

//  typemaps for output iterator of Point_3
SWIG_CGAL_set_wrapper_iterator_helper_output(Point_3)
//  typemaps for output iterator of Point_3
SWIG_CGAL_set_wrapper_iterator_helper_output(Vector_3)

%include "SWIG_CGAL/Point_set_processing_3/functions.h"

%{
  #include <SWIG_CGAL/Point_set_processing_3/functions.h>
%}

#ifdef SWIG_CGAL_HAS_Point_set_processing_3_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Point_set_processing_3/extensions.i"
#endif
