// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_CLASSIFICATION_TYPEDEFS_H
#define SWIG_CGAL_CLASSIFICATION_TYPEDEFS_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Point_set_3/typedefs.h>
#include <CGAL/Classification.h>

typedef CGAL::Classification::Label_handle CGAL_Label;
typedef CGAL::Classification::Label_set CGAL_Label_set;
typedef CGAL::Classification::Feature_handle CGAL_Feature;
typedef CGAL::Classification::Feature_set CGAL_Feature_set;
typedef CGAL::Classification::Point_set_neighborhood
<EPIC_Kernel, CGAL_PS3, typename CGAL_PS3::Point_map> CGAL_Point_set_neighborhood;
typedef CGAL::Classification::Point_set_feature_generator
<EPIC_Kernel, CGAL_PS3, typename CGAL_PS3::Point_map> CGAL_Point_set_feature_generator;
typedef CGAL::Classification::ETHZ::Random_forest_classifier CGAL_ETHZ_Random_forest;
typedef CGAL::Classification::Evaluation CGAL_Evaluation;

#endif //SWIG_CGAL_CLASSIFICATION_TYPEDEFS_H
