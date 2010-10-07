// Copyright (c) 2002 Utrecht University (The Netherlands).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)

#ifndef CGAL_INTERNAL_K_NEIGHBOR_SEARCH_H
#define CGAL_INTERNAL_K_NEIGHBOR_SEARCH_H

#include <cstring>
#include <set>
#include <memory>
#include <CGAL/Kd_tree_node.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/Euclidean_distance.h>
#include <CGAL/Splitters.h>
#include <CGAL/internal/bounded_priority_queue.h>
#include <boost/iterator/transform_iterator.hpp>

namespace CGAL {
namespace internal{
  
template <class SearchTraits, 
          class Distance_= Euclidean_distance<SearchTraits>,
          class Splitter_= Sliding_midpoint<SearchTraits> ,
          class Tree_= Kd_tree<SearchTraits, Splitter_, Tag_true> >
class K_neighbor_search {

public:

  typedef Splitter_ Splitter;
  typedef Tree_  Tree;
  typedef Distance_ Distance;
  typedef typename SearchTraits::Point_d Point_d;
  typedef typename Distance::Query_item Query_item;

  typedef typename SearchTraits::FT FT;
  typedef std::pair<Point_d,FT> Point_with_transformed_distance;

  typedef typename Tree::Node_handle Node_handle;

  typedef typename Tree::Point_d_iterator Point_d_iterator;

  //undocumented type
  typedef std::pair<Point_d*,FT>  Point_ptr_with_transformed_distance;
protected:

  // Comparison functor to sort a set of points
  // in increasing or decreasing order (key is distance).
  class Distance_larger 
  {
    bool search_nearest;

  public:

    Distance_larger(bool search_the_nearest_neighbour) 
      : search_nearest(search_the_nearest_neighbour)
    {}

    bool operator()(const Point_ptr_with_transformed_distance& p1, 
                    const Point_ptr_with_transformed_distance& p2) const  
    {
      if (search_nearest)
        return (p1.second < p2.second);
      else
        return (p2.second < p1.second);
    }
  };
  
  // Set of points, sorted by distance, in increasing or decreasing order.
  typedef internal::bounded_priority_queue<Point_ptr_with_transformed_distance,Distance_larger> BPqueue;

  struct Transform_pair{
    typedef Point_with_transformed_distance result_type;
    
    result_type operator()(const Point_ptr_with_transformed_distance& pair) const {
      CGAL_precondition(pair.first!=NULL);
      return std::make_pair(*(pair.first),pair.second);
    }
  };
  
public:
  //non-documented iterator
  typedef typename BPqueue::const_iterator                            advanced_iterator;
  typedef boost::transform_iterator<Transform_pair,advanced_iterator> iterator;

protected:

  int number_of_internal_nodes_visited;
  int number_of_leaf_nodes_visited;
  int number_of_items_visited;

  bool search_nearest;

  Distance distance_instance;
  FT multiplication_factor;
  Query_item query_object;

  BPqueue queue;// priority queue containing points, the top one is the search_nearest?:max:min
  
  

protected:

  // Test if we should continue searching 
  inline bool branch(FT distance) 
  {
    if (!queue.full()) 
      return true;
    else
      if (search_nearest) 
        return (distance*multiplication_factor < queue.top().second);
      else 
        return (distance > queue.top().second*multiplication_factor);      
  }

public:

  iterator begin() const
  {
    return iterator(queue.begin());
  }

  iterator end() const
  {
    return iterator(queue.end());
  }

  //non-documented iterator
  advanced_iterator advanced_begin() const  {return queue.begin();}
  advanced_iterator advanced_end()   const  {return queue.end();}  
  

  // constructor
  K_neighbor_search(const Query_item& q,  
    unsigned int k=1, FT Eps=FT(0.0), bool Search_nearest=true, const Distance& d=Distance())
    : number_of_internal_nodes_visited(0), number_of_leaf_nodes_visited(0), number_of_items_visited(0), 
      search_nearest(Search_nearest),distance_instance(d), multiplication_factor(distance_instance.transformed_distance(FT(1.0)+Eps)), query_object(q), 
     queue(k,Distance_larger(Search_nearest))
  {}


  // Prints statistics of the k_neighbor search process.
  std::ostream& statistics (std::ostream& s) 
  {
    s << "K_Neighbor search statistics:" << std::endl;
    s << "Number of internal nodes visited:" 
      << number_of_internal_nodes_visited << std::endl;
    s << "Number of leaf nodes visited:" 
      << number_of_leaf_nodes_visited << std::endl;
    s << "Number of items visited:" 
      << number_of_items_visited << std::endl;
    return s;
  }
    
}; // class 

}} // namespace CGAL::internal

#endif  // CGAL_INTERNAL_K_NEIGHBOR_SEARCH_H
