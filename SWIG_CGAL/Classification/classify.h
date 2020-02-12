// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_CLASSIFICATION_H
#define SWIG_CGAL_CLASSIFICATION_H

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>

#include <SWIG_CGAL/Point_set_3/Point_set_3.h>

#include <SWIG_CGAL/Classification/typedefs.h>
#include <SWIG_CGAL/Classification/Label_set.h>
#include <SWIG_CGAL/Classification/Feature_set.h>
#include <SWIG_CGAL/Classification/ETHZ_Random_forest_classifier.h>

#ifdef CGAL_LINKED_WITH_TBB
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif

void classify (Point_set_3_wrapper<CGAL_PS3> point_set,
               Label_set_wrapper<CGAL_Label_set, Label_wrapper<CGAL_Label> > labels,
               ETHZ_Random_forest_classifier_wrapper
               <CGAL_ETHZ_Random_forest,
               Label_set_wrapper<CGAL_Label_set, Label_wrapper<CGAL_Label> >,
               Feature_set_wrapper<CGAL_Feature_set, Feature_wrapper<CGAL_Feature> > > classifier,
               typename Point_set_3_wrapper<CGAL_PS3>::Int_map output)
{
  CGAL::Classification::classify<Concurrency_tag>
    (point_set.get_data(), labels.get_data(),
     classifier.get_data(), output.get_data());
}

void classify_with_local_smoothing (Point_set_3_wrapper<CGAL_PS3> point_set,
                                    Label_set_wrapper<CGAL_Label_set, Label_wrapper<CGAL_Label> > labels,
                                    ETHZ_Random_forest_classifier_wrapper
                                    <CGAL_ETHZ_Random_forest,
                                    Label_set_wrapper<CGAL_Label_set, Label_wrapper<CGAL_Label> >,
                                    Feature_set_wrapper<CGAL_Feature_set, Feature_wrapper<CGAL_Feature> > > classifier,
                                    Point_set_neighbor_query_wrapper<CGAL_Point_set_neighborhood> neighbor_query,
                                    typename Point_set_3_wrapper<CGAL_PS3>::Int_map output)
{
  if (neighbor_query.use_sphere())
  {
    CGAL::Classification::classify_with_local_smoothing<Concurrency_tag>
      (point_set.get_data(), point_set.get_data().point_map(), labels.get_data(),
       classifier.get_data(), neighbor_query.sphere_neighbor_query(), output.get_data());
  }
  else
  {
   CGAL::Classification::classify_with_local_smoothing<Concurrency_tag>
      (point_set.get_data(), point_set.get_data().point_map(), labels.get_data(),
       classifier.get_data(), neighbor_query.k_neighbor_query(), output.get_data());
  }
}

void classify_with_graphcut (Point_set_3_wrapper<CGAL_PS3> point_set,
                             Label_set_wrapper<CGAL_Label_set, Label_wrapper<CGAL_Label> > labels,
                             ETHZ_Random_forest_classifier_wrapper
                             <CGAL_ETHZ_Random_forest,
                             Label_set_wrapper<CGAL_Label_set, Label_wrapper<CGAL_Label> >,
                             Feature_set_wrapper<CGAL_Feature_set, Feature_wrapper<CGAL_Feature> > > classifier,
                             Point_set_neighbor_query_wrapper<CGAL_Point_set_neighborhood> neighbor_query,
                             double strength,
                             int min_number_of_subdivisions,
                             typename Point_set_3_wrapper<CGAL_PS3>::Int_map output)
{
  if (neighbor_query.use_sphere())
  {
    CGAL::Classification::classify_with_graphcut<Concurrency_tag>
      (point_set.get_data(), point_set.get_data().point_map(), labels.get_data(),
       classifier.get_data(), neighbor_query.sphere_neighbor_query(), strength,
       min_number_of_subdivisions, output.get_data());
  }
  else
  {
   CGAL::Classification::classify_with_graphcut<Concurrency_tag>
      (point_set.get_data(), point_set.get_data().point_map(), labels.get_data(),
       classifier.get_data(), neighbor_query.k_neighbor_query(), strength,
       min_number_of_subdivisions, output.get_data());
  }

}


#endif // SWIG_CGAL_CLASSIFICATION_H

