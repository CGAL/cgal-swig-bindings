// Copyright (c) 2018 GeometryFactory (France).
// All rights reserved.
//
// This file if part of CGAL PolygonMesh java wrapper.
// It is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this file.  If not, see <https://www.gnu.org/licenses/>.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// $URL$
// $Id$
// SPDX-License-Identifier: AGPL-3.0+
//

#ifndef CGAL_POLYGON_MESH_PROPERTIES_POINTSET_H
#define CGAL_POLYGON_MESH_PROPERTIES_POINTSET_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPIC_kernel;

template <class Property, class Value>
struct PointSet_property
{
  Property* base_ptr;
  typedef int key_type;
  typedef Value value_type;
  typedef value_type reference;
  typedef boost::read_write_property_map_tag category;

  PointSet_property()
    : base_ptr(NULL)
  {}

  PointSet_property(Property& base)
    : base_ptr(&base)
  {}

  friend reference get(const PointSet_property& map, key_type k)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    return static_cast<Value>(map.base_ptr->values[k]);
  }

  friend void put(const PointSet_property& map, key_type k, const value_type& v)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    map.base_ptr->values[k] = v;
  }
};

template <class Property>
struct PointSet_property<Property, EPIC_kernel::Vector_3>
{
  Property* base_ptr;
  typedef int key_type;
  typedef EPIC_kernel::Vector_3 value_type;
  typedef value_type reference;
  typedef boost::read_write_property_map_tag category;

  PointSet_property()
    : base_ptr(NULL)
  {}

  PointSet_property(Property& base)
    : base_ptr(&base)
  {}

  friend reference get(const PointSet_property& map, key_type k)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    return EPIC_kernel::Vector_3(map.base_ptr->values[3*k],
                                 map.base_ptr->values[3*k+1],
                                 map.base_ptr->values[3*k+2]);
  }

  friend void put(const PointSet_property& map, key_type k, const value_type& v)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    map.base_ptr->values[3*k] = v[0];
    map.base_ptr->values[3*k+1] = v[1];
    map.base_ptr->values[3*k+2] = v[2];
  }
};

template <class PointSet, class Point>
struct PointSet_point_map
{
  PointSet* ps_ptr;
  typedef int key_type;
  typedef Point value_type;
  typedef Point reference;
  typedef boost::read_write_property_map_tag category;

  PointSet_point_map()
    : ps_ptr(NULL)
  {}

  PointSet_point_map(PointSet& ps)
    : ps_ptr(&ps)
  {}

  friend reference get(const PointSet_point_map& map, int k)
  {
    CGAL_assertion(map.ps_ptr!=NULL);
    return map.ps_ptr->template point_from_index<Point>(k);
  }

  friend void put(const PointSet_point_map& map, int k, const Point& pt)
  {
    CGAL_assertion(map.ps_ptr!=NULL);
    map.ps_ptr->set_point_from_index(k, pt);
  }
};

#endif //CGAL_POLYGON_MESH_PROPERTIES_POINTSET_H
