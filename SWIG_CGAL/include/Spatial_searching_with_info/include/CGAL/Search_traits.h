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
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/branches/experimental-packages/Spatial_searching_with_info/Spatial_searching/include/CGAL/Search_traits.h $
// $Id: Search_traits.h 60490 2010-12-23 14:05:42Z sloriot $
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_KD_TREE_TRAITS_POINT_H
#define CGAL_KD_TREE_TRAITS_POINT_H


namespace CGAL {
  template <class FT_, class Point, class CartesianCoordinateIterator, class ConstructCartesianCoordinateIterator>
  class Search_traits {
    
  public:
    typedef CartesianCoordinateIterator Cartesian_const_iterator_d;
    typedef ConstructCartesianCoordinateIterator Construct_cartesian_const_iterator_d;
    typedef Point Point_d;
    typedef FT_ FT;
    
    Construct_cartesian_const_iterator_d construct_cartesian_const_iterator_d_object() const {
       return Construct_cartesian_const_iterator_d();
    }
  
  };

  
} // namespace CGAL
#endif //  KD_TREE_TRAITS_POINT_H
