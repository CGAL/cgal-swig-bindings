// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_CLASSIFICATION_FEATURE_SET_H
#define SWIG_CGAL_CLASSIFICATION_FEATURE_SET_H

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>

template <typename Feature_base>
class Feature_wrapper
{
  SWIG_CGAL_INIT_WRAPPER_CLASS (Feature_base, data_sptr);
public:
#ifndef SWIG
  Feature_wrapper (Feature_base base) : data_sptr (new Feature_base(base)) { }
#endif
  Feature_wrapper () : data_sptr (nullptr) {}

  std::string name() const { return (*data_sptr)->name(); }
  void set_name (const std::string& name) { (*data_sptr)->set_name (name); }

  double value (int index) { return (*data_sptr)->value(index); }
};

template <typename Set_base, typename Feature_wrap>
class Feature_set_wrapper
{
  SWIG_CGAL_INIT_WRAPPER_CLASS (Set_base, data_sptr);

public:

  typedef Feature_wrap Feature;

  Feature_set_wrapper () : data_sptr (new Set_base()) { }

  void begin_parallel_additions()
  {
#if defined(CGAL_LINKED_WITH_TBB)
    data_sptr->begin_parallel_additions();
#endif
  }

  void end_parallel_additions()
  {
#if defined(CGAL_LINKED_WITH_TBB)
    data_sptr->end_parallel_additions();
#endif
  }

  SWIG_CGAL_FORWARD_CALL_0(void, clear)
  SWIG_CGAL_FORWARD_CALL_0(int, size)

  Feature get (int index) { return Feature((*data_sptr)[index]); }

  bool remove (Feature feature)
  {
    return data_sptr->remove (feature.get_data());
  }
};



#endif // SWIG_CGAL_CLASSIFICATION_FEATURE_SET_H
