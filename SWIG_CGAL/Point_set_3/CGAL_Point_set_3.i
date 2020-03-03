// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

%define PS3_DOCSTRING
"SWIG wrapper for the CGAL 3D Point Set package provided under the GPL-3.0+ license"
%enddef
%module (package="CGAL", docstring=PS3_DOCSTRING) CGAL_Point_set_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Point_set_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%import  "SWIG_CGAL/Common/Iterator.h"

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
%types(Vector_3*,Vector_3);//needed so that the identifier SWIGTYPE_p_Vector_3 is generated

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
%typemap(javaimports) Point_set_3_wrapper %{import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; %}
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3,Point_set_3_wrapper< CGAL_PS3 >)

// iterators
%typemap(jstype) int "Integer"  //next() return type must be Integer
SWIG_CGAL_set_as_java_iterator_non_class(SWIG_CGAL_Iterator,Integer)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::const_iterator, int>)
%ignore SWIG_CGAL_Iterator<typename CGAL_PS3::const_iterator, int>::next(int&);
%typemap(jstype) int "int"  //restore to default

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_3,import CGAL.Kernel.Point_3;)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Point_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Point_range::const_iterator, Point_3>)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Vector_3,import CGAL.Kernel.Vector_3;)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Vector_iterator,SWIG_CGAL_Iterator<typename CGAL_PS3::Vector_range::const_iterator, Vector_3>)

%typemap(jstype) int "Integer"  //next() return type must be Integer
SWIG_CGAL_set_as_java_iterator_non_class(SWIG_CGAL_Iterator,Integer)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Int_iterator,SWIG_CGAL_Iterator<Nested_iterator_helper<CGAL_PS3, int>::type, int>)
%ignore SWIG_CGAL_Iterator<Nested_iterator_helper<CGAL_PS3, int>::type, int>::next(int&);
%typemap(jstype) int "int"  //restore to default

%typemap(jstype) double "Double"  //next() return type must be Double
SWIG_CGAL_set_as_java_iterator_non_class(SWIG_CGAL_Iterator,Double)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Float_iterator,SWIG_CGAL_Iterator<Nested_iterator_helper<CGAL_PS3, double>::type, double>)
%ignore SWIG_CGAL_Iterator<Nested_iterator_helper<CGAL_PS3, double>::type, double>::next(double&);
%typemap(jstype) double "double"  //restore to default

// property maps
%typemap(javaimports) SWIG_Point_set_3::CGAL_Property_map %{import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; %}
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Point_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, Point_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Vector_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, Vector_3>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Int_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, int>)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_3_Float_map,SWIG_Point_set_3::CGAL_Property_map<CGAL_PS3, double>)
