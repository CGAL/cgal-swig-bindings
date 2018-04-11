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

#ifndef SWIG_CGAL_POLYGON_MESH_UTILITIES_H
#define SWIG_CGAL_POLYGON_MESH_UTILITIES_H

template <class key_type>
struct Is_constrained_map{
  std::set<int>* m_set;
  typedef boost::read_write_property_map_tag category;
  typedef bool value_type;
  typedef bool reference;

  Is_constrained_map(std::set<int>& set_) : m_set(&set_) {}
  
  Is_constrained_map() {}

  friend bool get(const Is_constrained_map& map, const key_type& k)
  {
    return map.m_set->count(k);
  }

  friend void put(const Is_constrained_map& map, const key_type& k, bool v)
  {
    if (v)
      map.m_set->insert(k);
    else
      map.m_set->erase(k);
  }

  Is_constrained_map& operator=(const Is_constrained_map& other)
  {
    if(this != &other)
      m_set = other.m_set;
    return *this;
  }
};

typedef Is_constrained_map<PolygonMesh::Edge_descriptor> Constrained_edge_map;
typedef Is_constrained_map<PolygonMesh::Vertex_descriptor> Constrained_vertex_map;

template <class MultiPolyline>
struct Vector_of_points_putter
{
  MultiPolyline& multi_polyline;

  Vector_of_points_putter(MultiPolyline& mp)
    : multi_polyline(mp)
  {}

  template <class Point_3>
  void operator()(const std::vector<Point_3>& polyline)
  {
    multi_polyline.beginPolyline();
    BOOST_FOREACH(const Point_3& p, polyline)
      multi_polyline.push_back(p.x(), p.y(), p.z());
    multi_polyline.endPolyline();
  }
};


template <class MultiPolyline>
struct Points_putter
{
  MultiPolyline& multi_polyline;

  Points_putter(MultiPolyline& mp)
    : multi_polyline(mp)
  {}

  template <class Point_3>
  void operator()(const Point_3& p)
  {
    multi_polyline.push_back(p.x(), p.y(), p.z());
  }
};

static
CGAL::Iterator_range<int*>
make_range(const RangeIndexJNI& range)
{
  return CGAL::make_range(range.indices, range.indices+range.size);
}

static
bool same_java_meshes(const PolygonMesh& pm1, const PolygonMesh&pm2)
{
  return ((PolygonMeshJNI&) pm1).equals((PolygonMeshJNI&) pm2);
}

#endif
