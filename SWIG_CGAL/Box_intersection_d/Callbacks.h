// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_BOX_INTERSECTION_D_CALLBACKS_H
#define SWIG_CGAL_BOX_INTERSECTION_D_CALLBACKS_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <utility>
#include <SWIG_CGAL/Common/Iterator.h>

struct Collect_ids_callback{
  typedef std::pair<int, int> Pair_of_int;
  typedef SWIG_CGAL_Iterator<std::vector< Pair_of_int >::iterator,Pair_of_int> Ids_iterator;
  #ifndef SWIG
  boost::shared_ptr< std::vector< Pair_of_int > > ids_ptr;

  Collect_ids_callback():ids_ptr(new std::vector< Pair_of_int >()){}
  template <class Box>
  void operator()( const Box& b1, const Box& b2)
  {
    ids_ptr->push_back( Pair_of_int(b1.id(), b2.id()) );
  }
  #endif
  SWIG_CGAL_Iterator<std::vector< std::pair<int, int> >::iterator,std::pair<int, int> >
  ids(){ return Ids_iterator(ids_ptr->begin(), ids_ptr->end()); }
};

#include <SWIG_CGAL/Kernel/Point_2.h>

struct Collect_polyline_intersection_points{
  typedef SWIG_CGAL_Iterator<std::vector< Point_2::cpp_base >::iterator,Point_2> Point_2_iterator;
  #ifndef SWIG
  typedef std::vector<Point_2::cpp_base> Vector_of_points;
  boost::shared_ptr< std::vector< Vector_of_points > > pts_vector_ptr;

  Collect_polyline_intersection_points():pts_vector_ptr(new std::vector< Vector_of_points >()){}
  template <class Box>
  void operator()( const Box& b1, const Box& b2)
  {
    if (b1.polyline_id()!=b2.polyline_id())
    {
      CGAL::Object inter_res = CGAL::intersection(b1.segment_2(), b2.segment_2());

      if ( const Point_2::cpp_base* pt_ptr = CGAL::object_cast<Point_2::cpp_base>(&inter_res) )
      {
        (*pts_vector_ptr)[b1.polyline_id()].push_back(*pt_ptr);
        (*pts_vector_ptr)[b2.polyline_id()].push_back(*pt_ptr);
      }
    }
  }
  #endif

  Collect_polyline_intersection_points(int nb_polylines):
    pts_vector_ptr(new std::vector< Vector_of_points >(nb_polylines))
  {}

  SWIG_CGAL_Iterator<std::vector< Point_2::cpp_base >::iterator,Point_2 >
  intersection_points(int polyline_id){
    return Point_2_iterator(
      (*pts_vector_ptr)[polyline_id].begin(),
      (*pts_vector_ptr)[polyline_id].end()
    );
  }
};



#endif //SWIG_CGAL_BOX_INTERSECTION_D_CALLBACKS_H
