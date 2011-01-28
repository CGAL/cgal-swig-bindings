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
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/branches/experimental-packages/Spatial_searching_with_info/Spatial_searching/include/CGAL/Euclidean_distance_sphere_point.h $
// $Id: Euclidean_distance_sphere_point.h 60456 2010-12-22 09:09:20Z sloriot $
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_EUCLIDEAN_DISTANCE_SPHERE_POINT_H
#define CGAL_EUCLIDEAN_DISTANCE_SPHERE_POINT_H
#include <CGAL/Kd_tree_rectangle.h>

namespace CGAL {

  template <class SearchTraits>
  class Euclidean_distance_sphere_point {
    SearchTraits traits;
    
    public:

    typedef typename SearchTraits::Point_d Point_d;
    typedef typename SearchTraits::Sphere_d Sphere_d;
    typedef typename SearchTraits::FT    FT;
    typedef typename SearchTraits::Construct_center_d Construct_center_d;
    typedef typename SearchTraits::Compute_squared_radius_d Compute_squared_radius_d;
    typedef typename SearchTraits::Construct_cartesian_const_iterator_d Construct_cartesian_const_iterator_d;
    typedef typename SearchTraits::Cartesian_const_iterator_d Cartesian_const_iterator_d;
    typedef Sphere_d Query_item;    
    public:

    	// default constructor
    	Euclidean_distance_sphere_point(const SearchTraits& traits_=SearchTraits()):traits(traits_) {}


	inline FT transformed_distance(const Sphere_d& q, const Point_d& p) const {
                Point_d c= Construct_center_d()(q);
		FT distance = FT(0);
		Construct_cartesian_const_iterator_d construct_it=traits.construct_cartesian_const_iterator_d_object();
                Cartesian_const_iterator_d cit = construct_it(c),
		  ce = construct_it(c,1), pit = construct_it(p);
		for(; cit != ce; cit++, pit++){
		  distance += ((*cit)-(*pit))*((*cit)-(*pit));
		}
                distance += - Compute_squared_radius_d()(q);
                if (distance<0) distance=FT(0);
        	return distance;
	}


	inline FT min_distance_to_rectangle(const Sphere_d& q,
					     const Kd_tree_rectangle<FT>& r) const {
                Point_d c= Construct_center_d()(q);
		FT distance = FT(0);
		Construct_cartesian_const_iterator_d construct_it=traits.construct_cartesian_const_iterator_d_object();
                Cartesian_const_iterator_d cit = construct_it(c),
		  ce = construct_it(c,1);
		for (unsigned int i = 0; cit != ce; ++i, ++cit) {
			if ((*cit) < r.min_coord(i))
				distance += 
				(r.min_coord(i)-(*cit))*(r.min_coord(i)-(*cit));
			else if ((*cit) > r.max_coord(i))
				distance +=  
				((*cit)-r.max_coord(i))*((*cit)-r.max_coord(i));
			
		};
                distance += - Compute_squared_radius_d()(q);
                if (distance<0) distance=FT(0);
		return distance;
	}

	inline FT max_distance_to_rectangle(const Sphere_d& q,
					      const Kd_tree_rectangle<FT>& r) const {
	  Construct_center_d construct_center_d;
                Point_d c = construct_center_d(q);
		FT distance=FT(0);
		Construct_cartesian_const_iterator_d construct_it=traits.construct_cartesian_const_iterator_d_object();
                Cartesian_const_iterator_d cit = construct_it(c),
		  ce = construct_it(c,1);
		for (unsigned int i = 0; cit != ce; ++i, ++cit) {
				if ((*cit) <= (r.min_coord(i)+r.max_coord(i))/FT(2.0))
					distance += (r.max_coord(i)-(*cit))*(r.max_coord(i)-(*cit));
				else
					distance += ((*cit)-r.min_coord(i))*((*cit)-r.min_coord(i));
		};
		distance += - Compute_squared_radius_d()(q);
                if (distance<0) distance=FT(0);
		return distance;
	}



  inline FT transformed_distance(FT d) const {
		return d*d;
	}

  inline FT inverse_of_transformed_distance(FT d) const {
		return CGAL::sqrt(d);
	}

  }; // class Euclidean_distance_sphere_point

} // namespace CGAL
#endif // EUCLIDEAN_DISTANCE_SPHERE_POINT_H
