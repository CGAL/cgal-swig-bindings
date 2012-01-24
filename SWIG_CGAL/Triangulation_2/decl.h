// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_DECL_H
#define SWIG_CGAL_TRIANGULATION_2_DECL_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_DECLSPEC

#ifdef  SWIG_CGAL_TRIANGULATION_2_EXPORT
#define SWIG_CGAL_TRIANGULATION_2_DECL __declspec(dllexport) 
#else
#define SWIG_CGAL_TRIANGULATION_2_DECL __declspec(dllimport) 
#endif

#else
#define SWIG_CGAL_TRIANGULATION_2_DECL 
#endif



#endif // SWIG_CGAL_TRIANGULATION_2_DECL_H
