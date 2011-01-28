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
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/branches/experimental-packages/Spatial_searching_with_info/Spatial_searching/include/CGAL/Weighted_Minkowski_distance.h $
// $Id: Weighted_Minkowski_distance.h 60456 2010-12-22 09:09:20Z sloriot $
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)

// Note: Use p=0 to denote the weighted Linf-distance 
// For 0<p<1 Lp is not a metric

#ifndef CGAL_WEIGHTED_MINKOWSKI_DISTANCE_H
#define CGAL_WEIGHTED_MINKOWSKI_DISTANCE_H

#include <cmath>
#include <CGAL/Kd_tree_rectangle.h>

namespace CGAL {

  template <class SearchTraits>
  class Weighted_Minkowski_distance {
    SearchTraits traits;
    public:

    typedef typename SearchTraits::Point_d Point_d;
    typedef Point_d                        Query_item;
    typedef typename SearchTraits::FT      FT;
    typedef std::vector<FT>                Weight_vector;

    private:

    typedef typename SearchTraits::Cartesian_const_iterator_d Coord_iterator;
    FT power; 

    Weight_vector the_weights;

    public:


    // default constructor
    Weighted_Minkowski_distance(const SearchTraits& traits_=SearchTraits())
      : traits(traits_),power(2) 
    {}

    Weighted_Minkowski_distance(const int d,const SearchTraits& traits_=SearchTraits()) 
      : traits(traits_),power(2), the_weights(d)
    {
      for (unsigned int i = 0; i < d; ++i) the_weights[i]=FT(1);
    }

    //default copy constructor and destructor
    

    Weighted_Minkowski_distance (FT pow, int dim,
				 const Weight_vector& weights,
                                 const SearchTraits& traits_=SearchTraits()) 
      : traits(traits_),power(pow)
    {
      CGAL_assertion(power >= FT(0));
      CGAL_assertion(dim==weights.size());
      for (unsigned int i = 0; i < weights.size(); ++i)
	CGAL_assertion(weights[i]>=FT(0));
      the_weights.resize(weights.size());
      the_weights = weights;
    }

    template <class InputIterator>
    Weighted_Minkowski_distance (FT pow, int dim,
				 InputIterator begin, InputIterator end,
                                 const SearchTraits& traits_=SearchTraits()) 
      : traits(traits_),power(pow)
    {
      CGAL_assertion(power >= FT(0));
      the_weights.resize(dim);
      std::copy(begin, end, the_weights.begin());
      for (int i = 0; i < dim; ++i){
	the_weights[i] = *begin;
	++begin;
	CGAL_assertion(the_weights[i]>=FT(0));
      }
      CGAL_assertion(begin == end);
    }


    inline 
    FT 
    transformed_distance(const Query_item& q, const Point_d& p) 
    {
      FT distance = FT(0);
      typename SearchTraits::Construct_cartesian_const_iterator_d construct_it=
        traits.construct_cartesian_const_iterator_d_object();
      Coord_iterator qit = construct_it(q),
	             qe = construct_it(q,1), 
	             pit = construct_it(p);
      if (power == FT(0)) {
	for (unsigned int i = 0; qit != qe; ++qit, ++i)
	  if (the_weights[i] * std::fabs((*qit) - (*pit)) > distance)
	    distance = the_weights[i] * std::fabs((*qit)-(*pit));
      }
      else
	for (unsigned int i = 0; qit != qe; ++qit, ++i)
	  distance += 
	    the_weights[i] * std::pow(std::fabs((*qit)-(*pit)),power);
      return distance;
    }
    

    inline 
    FT 
    min_distance_to_rectangle(const Query_item& q,
			      const Kd_tree_rectangle<FT>& r) const 
    {
      FT distance = FT(0);
      typename SearchTraits::Construct_cartesian_const_iterator_d construct_it=
        traits.construct_cartesian_const_iterator_d_object();
      Coord_iterator qit = construct_it(q), qe = construct_it(q,1);
      if (power == FT(0))
	{
	  for (unsigned int i = 0; qit != qe; ++qit, ++i) {
	    if (the_weights[i]*(r.min_coord(i) - 
				(*qit)) > distance)
	      distance = the_weights[i] * (r.min_coord(i)-
					   (*qit));
	    if (the_weights[i] * ((*qit) - r.max_coord(i)) > 
		distance)
	      distance = the_weights[i] * 
		((*qit)-r.max_coord(i));
	  }
	}
      else
	{
	  for (unsigned int i = 0; qit != qe; ++qit, ++i) {
	    if ((*qit) < r.min_coord(i))
	      distance += the_weights[i] * 
		std::pow(r.min_coord(i)-(*qit),power);
	    if ((*qit) > r.max_coord(i))
	      distance += the_weights[i] * 
		std::pow((*qit)-r.max_coord(i),power);
	  }
	};
      return distance;
    }

    inline 
    FT
    max_distance_to_rectangle(const Query_item& q,
			      const Kd_tree_rectangle<FT>& r) const {
      FT distance=FT(0);
      typename SearchTraits::Construct_cartesian_const_iterator_d construct_it=
        traits.construct_cartesian_const_iterator_d_object();
      Coord_iterator qit = construct_it(q), qe = construct_it(q,1);
      if (power == FT(0))
	{
	  for (unsigned int i = 0; qit != qe; ++qit, ++i) {
	    if ((*qit) >= (r.min_coord(i) + 
			 r.max_coord(i))/FT(2.0)) {
	      if (the_weights[i] * ((*qit) - 
				    r.min_coord(i)) > distance)
		distance = the_weights[i] * 
		  ((*qit)-r.min_coord(i));
	      else
		if (the_weights[i] * 
		    (r.max_coord(i) - (*qit)) > distance)
		  distance = the_weights[i] * 
		    ( r.max_coord(i)-(*qit));
            }
	  }
	}
      else
	{
	  for (unsigned int i = 0; qit != qe; ++qit, ++i) {
	    if ((*qit) <= (r.min_coord(i)+r.max_coord(i))/FT(2.0))
	      distance += the_weights[i] * std::pow(r.max_coord(i)-(*qit),power);
	    else
	      distance += the_weights[i] * std::pow((*qit)-r.min_coord(i),power);
	  }
	};
      return distance;
    }
    
    inline 
    FT 
    new_distance(FT dist, FT old_off, FT new_off,
		 int cutting_dimension)  const 
    {
      FT new_dist;
      if (power == FT(0))
	{
	  if (the_weights[cutting_dimension]*std::fabs(new_off) 
	      > dist) 
	    new_dist= 
	      the_weights[cutting_dimension]*std::fabs(new_off);
	  else new_dist=dist;
	}
      else
	{
	  new_dist = dist + the_weights[cutting_dimension] * 
	    (std::pow(std::fabs(new_off),power)-std::pow(std::fabs(old_off),power));
	}
      return new_dist;
    }
    
    inline 
    FT 
    transformed_distance(FT d) const 
    {
      if (power <= FT(0)) return d;
      else return std::pow(d,power);
      
    }
    
    inline 
    FT 
    inverse_of_transformed_distance(FT d) const 
    {
      if (power <= FT(0)) return d;
      else return std::pow(d,1/power);
      
    }

  }; // class Weighted_Minkowski_distance

} // namespace CGAL

#endif // CGAL_WEIGHTED_MINKOWSKI_DISTANCE_H
