#ifndef SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H
#define SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H

template <class Point>
struct First_of_pair{
  template<class Info>
  const Point& operator[](const std::pair<Point,Info>& p) const {return p.first;}
};


#endif //SWIG_CGAL_SPATIAL_SORTING_FIRST_OF_PAIR_H
