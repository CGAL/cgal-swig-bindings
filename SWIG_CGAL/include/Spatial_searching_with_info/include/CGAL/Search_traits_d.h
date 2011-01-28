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
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/branches/experimental-packages/Spatial_searching_with_info/Spatial_searching/include/CGAL/Search_traits_d.h $
// $Id: Search_traits_d.h 60456 2010-12-22 09:09:20Z sloriot $
// 
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_SEARCH_TRAITS_D_H
#define CGAL_SEARCH_TRAITS_D_H

namespace CGAL {

  template <class K>
  class Search_traits_d {

  public:
    typedef typename K::Cartesian_const_iterator_d Cartesian_const_iterator_d;
    typedef typename K::Construct_cartesian_const_iterator_d Construct_cartesian_const_iterator_d;
    typedef typename K::Construct_iso_box_d Construct_iso_box_d;
    typedef typename K::Construct_min_vertex_d Construct_min_vertex_d;
    typedef typename K::Construct_max_vertex_d Construct_max_vertex_d;
    typedef typename K::Point_d Point_d;
    typedef typename K::Iso_box_d Iso_box_d;
    typedef typename K::FT FT;
    
    Construct_cartesian_const_iterator_d construct_cartesian_const_iterator_d_object() const {
       return Construct_cartesian_const_iterator_d();
    }  
  };

  
} // namespace CGAL
#endif // CGAL_SEARCH_TRAITS_D_H
