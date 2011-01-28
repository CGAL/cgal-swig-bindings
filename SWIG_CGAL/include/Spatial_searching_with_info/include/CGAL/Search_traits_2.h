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
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/branches/experimental-packages/Spatial_searching_with_info/Spatial_searching/include/CGAL/Search_traits_2.h $
// $Id: Search_traits_2.h 60456 2010-12-22 09:09:20Z sloriot $
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_SEARCH_TRAITS_2_H
#define CGAL_SEARCH_TRAITS_2_H

namespace CGAL {


  template <class K > 

  class Search_traits_2 {

  public:
    typedef typename K::Point_2 Point_d;
    typedef typename K::Iso_rectangle_2 Iso_box_d;
    typedef typename K::Circle_2 Sphere_d;
    typedef typename K::Cartesian_const_iterator_2 Cartesian_const_iterator_d;
    typedef typename K::Construct_cartesian_const_iterator_2 Construct_cartesian_const_iterator_d;

    typedef typename K::Construct_min_vertex_2 Construct_min_vertex_d;
    typedef typename K::Construct_max_vertex_2 Construct_max_vertex_d;
    typedef typename K::Construct_center_2 Construct_center_d;
    typedef typename K::Compute_squared_radius_2 Compute_squared_radius_d;

    typedef typename K::Construct_iso_rectangle_2 Construct_iso_box_d;
    typedef typename K::FT FT;
  
    Construct_cartesian_const_iterator_d construct_cartesian_const_iterator_d_object() const {
       return Construct_cartesian_const_iterator_d();
    }  
  };

  
} // namespace CGAL
#endif // CGAL_SEARCH_TRAITS_2_H
