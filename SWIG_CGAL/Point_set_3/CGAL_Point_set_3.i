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

%include "SWIG_CGAL/typemaps.i"
SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in
SWIG_CGAL_vector_of_string_to_array_of_string_typemap_out

//definitions
%include "SWIG_CGAL/Point_set_3/Point_set_3.h"
%include "SWIG_CGAL/Point_set_3/Point_set_3_Property_map.h"

 //template instantiation
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3,Point_set_3_wrapper< CGAL_PS3 >)

SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::const_iterator, int>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Point_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Point_range::const_iterator, Point_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Vector_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Vector_range::const_iterator, Vector_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Int_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Int_range::const_iterator, int>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Float_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Double_range::const_iterator, double>)
/* SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Int_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::template Property_range<int>::const_iterator, int>) */
/* SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Float_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::template Property_range<double>::const_iterator, double>) */

SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Point_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, Point_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Vector_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, Vector_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Int_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, int>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Float_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, double>)
