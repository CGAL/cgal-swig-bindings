// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_OUTPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_COMMON_OUTPUT_ITERATOR_WRAPPER_H

#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/Output_iterator_wrapper.h>
#endif
#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/Output_iterator_wrapper.h>
#endif

#if SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
#include <SWIG_CGAL/Common/Generic_iterators.h>
#endif

#endif //SWIG_CGAL_COMMON_OUTPUT_ITERATOR_WRAPPER_H
