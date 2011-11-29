// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_OPTIONAL_H
#define SWIG_CGAL_COMMON_OPTIONAL_H

#include <boost/optional.hpp>

template <class T>
class Optional
{
  boost::optional<T> data;
  bool empty_;
public:
  typedef Optional<T> Self;
  #ifndef SWIG
  typedef boost::optional<T> cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Optional(const cpp_base& base):data(base){}
  Optional(const T& t):data(t){}
  #endif

  Optional():data(){}
  bool empty() const {return data?false:true;}
  const T& value() const {return *data;}  
//Deep copy
//  boost::optinal copy constructor is already a deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_COMMON_OPTIONAL_H
