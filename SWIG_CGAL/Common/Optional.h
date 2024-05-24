// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_COMMON_OPTIONAL_H
#define SWIG_CGAL_COMMON_OPTIONAL_H

#include <optional>

template <class T>
class Optional
{
  std::optional<T> data;
  bool empty_;
public:
  typedef Optional<T> Self;
  #ifndef SWIG
  typedef std::optional<T> cpp_base;
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
