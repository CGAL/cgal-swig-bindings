// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_COMMON_OPTIONAL_H
#define SWIG_CGAL_COMMON_OPTIONAL_H

#if CGAL_VERSION_NR >= 1060000000
#include <optional>
template <class T>
using optional_class = std::optional<T>;
#else
#include <boost/optional.hpp>
template <class T>
using optional_class = boost::optional<T>;
#endif

template <class T>
class Optional
{
  optional_class<T> data;
  bool empty_;
public:
  typedef Optional<T> Self;
  #ifndef SWIG
  typedef optional_class<T> cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Optional(const cpp_base& base):data(base){}
  Optional(const T& t):data(t){}
  #endif

  Optional():data(){}
  bool empty() const {return data?false:true;}
  const T& value() const {return *data;}
//Deep copy
//  std::optional copy constructor is already a deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_COMMON_OPTIONAL_H
