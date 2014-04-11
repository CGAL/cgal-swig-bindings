// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H
#define SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H

#include <CGAL/property_map.h>

template <class Point, class Info>
struct First_of_pair{
  const Point& operator[](const std::pair<Point,Info>& p) const {return p.first;}
  typedef Point value_type;
  typedef const value_type& reference;
  typedef std::pair<Point,Info> key_type;
  typedef boost::lvalue_property_map_tag category;
};

template <class Point,class Info>
const Point& get(First_of_pair<Point,Info>,const std::pair<Point,Info>& p){return p.first;}


#endif //SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H
