// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H
#define SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H

template <class Point>
struct First_of_pair{
  template<class Info>
  const Point& operator[](const std::pair<Point,Info>& p) const {return p.first;}
};

template <class Point,class Info>
const Point& get(First_of_pair<Point>,const std::pair<Point,Info>& p){return p.first;}


#endif //SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H
