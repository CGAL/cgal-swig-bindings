// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_CLASSIFICATION_LABEL_SET_H
#define SWIG_CGAL_CLASSIFICATION_LABEL_SET_H

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>

template <typename Label_base>
class Label_wrapper
{
  SWIG_CGAL_INIT_WRAPPER_CLASS (Label_base, data_sptr);

public:

  Label_wrapper (Label_base base) : data_sptr (new Label_base(base)) { }

  std::string name() const { return (*data_sptr)->name(); }
};

template <typename Set_base, typename Label_wrap>
class Label_set_wrapper
{
  SWIG_CGAL_INIT_WRAPPER_CLASS (Set_base, data_sptr);

public:

  typedef Label_wrap Label;

  Label_set_wrapper () : data_sptr (new Set_base()) { }

  Label add (const std::string& label)
  {
    return Label(data_sptr->add (label.c_str()));
  }

  bool remove (Label label)
  {
    return data_sptr->remove (label.get_data());
  }

  SWIG_CGAL_FORWARD_CALL_0(void, clear)
};


#endif // SWIG_CGAL_CLASSIFICATION_LABEL_SET_H
