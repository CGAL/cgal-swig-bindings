// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Classification

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Classification)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%import  "SWIG_CGAL/Point_set_3/CGAL_Point_set_3.i"

%pragma(java) jniclassimports=%{
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Point_set_3.Point_set_3_Int_map;
import CGAL.Point_set_3.Point_set_3_Vector_map;
import CGAL.Point_set_3.Point_set_3_Int_iterator;
import java.util.Iterator;
import java.util.Collection;
%}

%pragma(java) moduleimports=%{
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Point_set_3.Point_set_3_Int_map;
import CGAL.Point_set_3.Point_set_3_Vector_map;
import CGAL.Point_set_3.Point_set_3_Int_iterator;
import java.util.Iterator;
import java.util.Collection;
%};

%types(Point_3*,Point_3);//needed so that the identifier SWIGTYPE_p_Point_3 is generated
%types(Vector_3*,Vector_3);//needed so that the identifier SWIGTYPE_p_Vector_3 is generated


%{ 
#include <SWIG_CGAL/Classification/all_includes.h> 
%}


%include "SWIG_CGAL/Classification/Label_set.h"
SWIG_CGAL_declare_identifier_of_template_class(Label,Label_wrapper< CGAL_Label >)
SWIG_CGAL_declare_identifier_of_template_class(Label_set,Label_set_wrapper< CGAL_Label_set, Label_wrapper< CGAL_Label > >)

%include "SWIG_CGAL/Classification/Feature_set.h"
SWIG_CGAL_declare_identifier_of_template_class(Feature,Feature_wrapper< CGAL_Feature >)
SWIG_CGAL_declare_identifier_of_template_class(Feature_set,Feature_set_wrapper< CGAL_Feature_set, Feature_wrapper< CGAL_Feature > >)

%include "SWIG_CGAL/Classification/Point_set_feature_generator.h"
SWIG_CGAL_declare_identifier_of_template_class(Point_set_neighbor_query, Point_set_neighbor_query_wrapper< CGAL_Point_set_neighborhood >)
SWIG_CGAL_declare_identifier_of_template_class(Point_set_neighborhood, Point_set_neighborhood_wrapper< CGAL_Point_set_neighborhood >) %typemap(javaimports) Point_set_feature_generator_wrapper< CGAL_Point_set_feature_generator, Feature_set_wrapper< CGAL_Feature_set, Feature_wrapper< CGAL_Feature > >, Point_set_neighborhood_wrapper< CGAL_Point_set_neighborhood> > %{ import CGAL.Point_set_3.Point_set_3; import CGAL.Point_set_3.Point_set_3_Vector_map; import CGAL.Point_set_3.Point_set_3_Int_map; %}
SWIG_CGAL_declare_identifier_of_template_class(Point_set_feature_generator, Point_set_feature_generator_wrapper< CGAL_Point_set_feature_generator, Feature_set_wrapper< CGAL_Feature_set, Feature_wrapper< CGAL_Feature > >, Point_set_neighborhood_wrapper< CGAL_Point_set_neighborhood> >)

%include "SWIG_CGAL/Classification/ETHZ_Random_forest_classifier.h"
%typemap(javaimports) ETHZ_Random_forest_classifier_wrapper< CGAL_ETHZ_Random_forest, Label_set_wrapper< CGAL_Label_set, Label_wrapper< CGAL_Label > >, Feature_set_wrapper< CGAL_Feature_set, Feature_wrapper< CGAL_Feature > > > %{ import CGAL.Point_set_3.Point_set_3_Int_iterator; %}
SWIG_CGAL_declare_identifier_of_template_class(ETHZ_Random_forest_classifier, ETHZ_Random_forest_classifier_wrapper< CGAL_ETHZ_Random_forest, Label_set_wrapper< CGAL_Label_set, Label_wrapper< CGAL_Label > >, Feature_set_wrapper< CGAL_Feature_set, Feature_wrapper< CGAL_Feature > > >)

%include "SWIG_CGAL/Classification/Evaluation.h"
%typemap(javaimports) Evaluation_wrapper< CGAL_Evaluation, Label_set_wrapper< CGAL_Label_set, Label_wrapper< CGAL_Label > > > %{ import CGAL.Point_set_3.Point_set_3_Int_iterator; %}
SWIG_CGAL_declare_identifier_of_template_class(Evaluation, Evaluation_wrapper< CGAL_Evaluation, Label_set_wrapper< CGAL_Label_set, Label_wrapper< CGAL_Label > > >)

%include "SWIG_CGAL/Classification/classify.h"





