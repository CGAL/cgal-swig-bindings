// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_CLASSIFICATION_ETHZ_RANDOM_FOREST_CLASSIFIER_H
#define SWIG_CGAL_CLASSIFICATION_ETHZ_RANDOM_FOREST_CLASSIFIER_H

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Point_set_3/Point_set_3.h>

template <typename Classifier_base, typename Label_set, typename Feature_set>
class ETHZ_Random_forest_classifier_wrapper
{
  SWIG_CGAL_INIT_WRAPPER_CLASS (Classifier_base, data_sptr);

public:

  ETHZ_Random_forest_classifier_wrapper (Label_set labels,
                                         Feature_set features)
    : data_sptr (new Classifier_base (labels.get_data(), features.get_data()))
  { }

  void train (typename Point_set_3_wrapper<CGAL_PS3>::Int_iterator ground_truth,
              bool reset_trees = true, int num_trees = 25, int max_depth = 20)
  {
    data_sptr->train (CGAL::make_range(ground_truth.get_cur(), ground_truth.get_end()),
                      reset_trees, num_trees, max_depth);
  }

  void save_configuration (const std::string& filename) const
  {
#if defined(CGAL_LINKED_WITH_BOOST_IOSTREAMS) && \
  defined(CGAL_LINKED_WITH_BOOST_SERIALIZATION)
    std::ofstream ofile (filename);
    data_sptr->save_configuration (ofile);
#else
    CGAL_USE(filename);
    std::cerr<<"ERROR: You need boost::iostreams and boost::serialization to use this function. "<<std::endl;
#endif

  }

  void load_configuration (const std::string& filename)
  {
#if defined(CGAL_LINKED_WITH_BOOST_IOSTREAMS) && \
  defined(CGAL_LINKED_WITH_BOOST_SERIALIZATION)
    std::ifstream ifile (filename);
    data_sptr->load_configuration (ifile);
#else
    CGAL_USE(filename);
    std::cerr<<"ERROR: You need boost::iostreams and boost::serialization to use this function. "<<std::endl;
#endif
  }
};

#endif // SWIG_CGAL_CLASSIFICATION_ETHZ_RANDOM_FOREST_CLASSIFIER_H
