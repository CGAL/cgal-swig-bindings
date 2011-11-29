// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIPLE_H
#define SWIG_CGAL_TRIPLE_H

#include <CGAL/utility.h>

namespace SWIG_CGAL{

template <class T1, class T2, class T3>
class Triple
{
public:
  typedef Triple<T1,T2,T3> Self;
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;

  T1 first;
  T2 second;
  T3 third;

  Triple() {}

  Triple(const T1& a, const T2& b, const T3& c)
  : first(a), second(b), third(c)
  {}

  #ifndef SWIG
  template <class U, class V, class W>
  Triple(const U& a, const V& b, const W& c)
  : first(a), second(b), third(c)
  {}

  template <class U, class V, class W>
  Triple(const CGAL::Triple<U,V,W>& t)
  : first(t.first), second(t.second), third(t.third)
  {}

  template <class U, class V, class W>
  Triple& operator=(const Triple<U, V, W> &t) {
    first = t.first;
    second = t.second;
    third = t.third;
    return *this;
  }
  #endif
//Deep copy
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
};

template <class T1,class T2,class T3>
Triple<T1,T2,T3> make_triple(const T1& t1,const T2& t2,const T3& t3){
  return Triple<T1,T2,T3>(t1,t2,t3);
}

}

#endif //SWIG_CGAL_TRIPLE_H
