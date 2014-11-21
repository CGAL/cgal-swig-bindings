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

// the template parameter is not needed but in java to avoid a type erasure issue with generics
template <int DIM>
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

#endif //SWIG_CGAL_BOX_INTERSECTION_D_CALLBACKS_H
