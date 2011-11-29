// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_REFERENCE_WRAPPER_H
#define SWIG_CGAL_COMMON_REFERENCE_WRAPPER_H

template <class Object>
class Reference_wrapper{
  Object i;
public:
  typedef Reference_wrapper<Object> Self;
  Reference_wrapper(){}
  Reference_wrapper(const Object& k):i(k){}
  #ifndef SWIG
  Object& object(){return i;}
  #endif
  void set(Object t){i=t;}
  Object object() const {return i;}
//Deep copy
  Self deepcopy() const {return Self(*this);}
  void deepcopy(const Self& other){*this=other;}
};

#endif //SWIG_CGAL_COMMON_REFERENCE_WRAPPER_H
