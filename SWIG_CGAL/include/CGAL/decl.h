#ifndef CGAL_DECL_H
#define CGAL_DECL_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_DECLSPEC

#ifdef  CGAL_EXPORT
#define CGAL_DECL __declspec(dllexport) 
#else
#define CGAL_DECL __declspec(dllimport) 
#endif

#else
#define CGAL_DECL 
#endif



#endif // CGAL_DECL_H
