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

struct Collect_ids_callback{
  #ifndef SWIG
  typedef std::pair<int, int> Pair_of_ids;
  boost::shared_ptr< std::vector< Pair_of_ids > > ids_ptr;

  Collect_ids_callback():ids_ptr(new std::vector< Pair_of_ids >()){}
  template <class Box>
  void operator()( const Box& b1, const Box& b2)
  {
    ids_ptr->push_back( Pair_of_ids(b1.id(), b2.id()) );
  }
  #endif
};

#endif //SWIG_CGAL_BOX_INTERSECTION_D_CALLBACKS_H
