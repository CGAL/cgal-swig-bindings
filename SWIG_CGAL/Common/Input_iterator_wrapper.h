// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_INPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_COMMON_INPUT_ITERATOR_WRAPPER_H

#include <SWIG_CGAL/Common/Macros.h>

#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/Input_iterator_wrapper.h>
#endif
#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/Input_iterator_wrapper.h>
#endif

namespace SWIG_CGAL{
  template <class T> inline T& get_begin(std::pair<T,T>& p){return p.first;}
  template <class T> inline T& get_end(std::pair<T,T>& p){return p.second;}
}

#endif //SWIG_CGAL_COMMON_INPUT_ITERATOR_WRAPPER_H
