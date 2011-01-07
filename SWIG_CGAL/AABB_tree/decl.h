#ifndef SWIG_CGAL_AABB_TREE_DECL_H
#define SWIG_CGAL_AABB_TREE_DECL_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_DECLSPEC

#ifdef  SWIG_CGAL_AABB_TREE_EXPORT
#define SWIG_CGAL_AABB_TREE_DECL __declspec(dllexport) 
#else
#define SWIG_CGAL_AABB_TREE_DECL __declspec(dllimport) 
#endif

#else
#define SWIG_CGAL_AABB_TREE_DECL 
#endif



#endif // SWIG_CGAL_AABB_TREE_DECL_H
