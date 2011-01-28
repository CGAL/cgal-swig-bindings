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
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/branches/experimental-packages/Spatial_searching_with_info/Spatial_searching/include/CGAL/Euclidean_distance.h $
// $Id: Euclidean_distance.h 60975 2011-01-28 13:09:56Z sloriot $
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_EUCLIDEAN_DISTANCE_H
#define CGAL_EUCLIDEAN_DISTANCE_H
#include <CGAL/Kd_tree_rectangle.h>

namespace CGAL {

  template <class SearchTraits>
  class Euclidean_distance;
  
  namespace internal{
    template <class SearchTraits>
    struct Spatial_searching_default_distance{
      typedef ::CGAL::Euclidean_distance<SearchTraits> type;
    };
  } //namespace internal

  template <class SearchTraits>
  class Euclidean_distance {
    
    SearchTraits traits;
    
    public:

    typedef typename SearchTraits::FT    FT;
    typedef typename SearchTraits::Point_d Point_d;
    typedef Point_d Query_item;

    	// default constructor
    	Euclidean_distance(const SearchTraits& traits_=SearchTraits()):traits(traits_) {}


	inline FT transformed_distance(const Query_item& q, const Point_d& p) const {
	        FT distance = FT(0);
		typename SearchTraits::Construct_cartesian_const_iterator_d construct_it=traits.construct_cartesian_const_iterator_d_object();
                typename SearchTraits::Cartesian_const_iterator_d qit = construct_it(q),
		  qe = construct_it(q,1), pit = construct_it(p);
		for(; qit != qe; qit++, pit++){
		  distance += ((*qit)-(*pit))*((*qit)-(*pit));
		}
        	return distance;
	}


	inline FT min_distance_to_rectangle(const Query_item& q,
					    const Kd_tree_rectangle<FT>& r) const {
		FT distance = FT(0);
		typename SearchTraits::Construct_cartesian_const_iterator_d construct_it=traits.construct_cartesian_const_iterator_d_object();
                typename SearchTraits::Cartesian_const_iterator_d qit = construct_it(q),
		  qe = construct_it(q,1);
		for(unsigned int i = 0;qit != qe; i++, qit++){
		  if((*qit) < r.min_coord(i))
				distance += 
				(r.min_coord(i)-(*qit))*(r.min_coord(i)-(*qit));
		  else if ((*qit) > r.max_coord(i))
				distance +=  
				((*qit)-r.max_coord(i))*((*qit)-r.max_coord(i));
			
		}
		return distance;
	}

	inline FT max_distance_to_rectangle(const Query_item& q,
					     const Kd_tree_rectangle<FT>& r) const {
		FT distance=FT(0);
		typename SearchTraits::Construct_cartesian_const_iterator_d construct_it=traits.construct_cartesian_const_iterator_d_object();
                typename SearchTraits::Cartesian_const_iterator_d qit = construct_it(q),
		  qe = construct_it(q,1);
		for(unsigned int i = 0;qit != qe; i++, qit++){
				if ((*qit) <= (r.min_coord(i)+r.max_coord(i))/FT(2.0))
					distance += (r.max_coord(i)-(*qit))*(r.max_coord(i)-(*qit));
				else
					distance += ((*qit)-r.min_coord(i))*((*qit)-r.min_coord(i));
		};
		return distance;
	}

	inline FT new_distance(FT dist, FT old_off, FT new_off,
			       int /* cutting_dimension */)  const {
		
		FT new_dist = dist + (new_off*new_off - old_off*old_off);
                return new_dist;
	}

  inline FT transformed_distance(FT d) const {
		return d*d;
	}

  inline FT inverse_of_transformed_distance(FT d) const {
		return CGAL::sqrt(d);
	}

  }; // class Euclidean_distance

} // namespace CGAL
#endif // EUCLIDEAN_DISTANCE_H
