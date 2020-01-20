// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Point_set_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Point_set_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%import  "SWIG_CGAL/Common/Iterator.h"

%{ 
#include <SWIG_CGAL/Point_set_3/all_includes.h> 
%}


//definitions
%include "SWIG_CGAL/Point_set_3/Point_set_3.h"
 //%include "SWIG_CGAL/Point_set_3/Point_set_3_Index.h"

 //template instantiation
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3,Point_set_3_wrapper< CGAL_PS3 >)

SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::const_iterator, unsigned int>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Point_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Point_range::const_iterator, Point_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Vector_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Vector_range::const_iterator, Vector_3>)
